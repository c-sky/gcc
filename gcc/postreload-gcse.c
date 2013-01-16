/* Post reload partially redundant load elimination
   Copyright (C) 2004-2013 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "diagnostic-core.h"

#include "hash-table.h"
#include "rtl.h"
#include "tree.h"
#include "tm_p.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "flags.h"
#include "insn-config.h"
#include "recog.h"
#include "basic-block.h"
#include "function.h"
#include "expr.h"
#include "except.h"
#include "intl.h"
#include "obstack.h"
#include "hashtab.h"
#include "params.h"
#include "target.h"
#include "tree-pass.h"
#include "dbgcnt.h"

/* The following code implements gcse after reload, the purpose of this
   pass is to cleanup redundant loads generated by reload and other
   optimizations that come after gcse. It searches for simple inter-block
   redundancies and tries to eliminate them by adding moves and loads
   in cold places.

   Perform partially redundant load elimination, try to eliminate redundant
   loads created by the reload pass.  We try to look for full or partial
   redundant loads fed by one or more loads/stores in predecessor BBs,
   and try adding loads to make them fully redundant.  We also check if
   it's worth adding loads to be able to delete the redundant load.

   Algorithm:
   1. Build available expressions hash table:
       For each load/store instruction, if the loaded/stored memory didn't
       change until the end of the basic block add this memory expression to
       the hash table.
   2. Perform Redundancy elimination:
      For each load instruction do the following:
	 perform partial redundancy elimination, check if it's worth adding
	 loads to make the load fully redundant.  If so add loads and
	 register copies and delete the load.
   3. Delete instructions made redundant in step 2.

   Future enhancement:
     If the loaded register is used/defined between load and some store,
     look for some other free register between load and all its stores,
     and replace the load with a copy from this register to the loaded
     register.
*/


/* Keep statistics of this pass.  */
static struct
{
  int moves_inserted;
  int copies_inserted;
  int insns_deleted;
} stats;

/* We need to keep a hash table of expressions.  The table entries are of
   type 'struct expr', and for each expression there is a single linked
   list of occurrences.  */

/* Expression elements in the hash table.  */
struct expr
{
  /* The expression (SET_SRC for expressions, PATTERN for assignments).  */
  rtx expr;

  /* The same hash for this entry.  */
  hashval_t hash;

  /* List of available occurrence in basic blocks in the function.  */
  struct occr *avail_occr;
};

/* Hashtable helpers.  */

struct expr_hasher : typed_noop_remove <expr>
{
  typedef expr value_type;
  typedef expr compare_type;
  static inline hashval_t hash (const value_type *);
  static inline bool equal (const value_type *, const compare_type *);
};


/* Hash expression X.
   DO_NOT_RECORD_P is a boolean indicating if a volatile operand is found
   or if the expression contains something we don't want to insert in the
   table.  */

static hashval_t
hash_expr (rtx x, int *do_not_record_p)
{
  *do_not_record_p = 0;
  return hash_rtx (x, GET_MODE (x), do_not_record_p,
		   NULL,  /*have_reg_qty=*/false);
}

/* Callback for hashtab.
   Return the hash value for expression EXP.  We don't actually hash
   here, we just return the cached hash value.  */

inline hashval_t
expr_hasher::hash (const value_type *exp)
{
  return exp->hash;
}

/* Callback for hashtab.
   Return nonzero if exp1 is equivalent to exp2.  */

inline bool
expr_hasher::equal (const value_type *exp1, const compare_type *exp2)
{
  int equiv_p = exp_equiv_p (exp1->expr, exp2->expr, 0, true);

  gcc_assert (!equiv_p || exp1->hash == exp2->hash);
  return equiv_p;
}

/* The table itself.  */
static hash_table <expr_hasher> expr_table;


static struct obstack expr_obstack;

/* Occurrence of an expression.
   There is at most one occurrence per basic block.  If a pattern appears
   more than once, the last appearance is used.  */

struct occr
{
  /* Next occurrence of this expression.  */
  struct occr *next;
  /* The insn that computes the expression.  */
  rtx insn;
  /* Nonzero if this [anticipatable] occurrence has been deleted.  */
  char deleted_p;
};

static struct obstack occr_obstack;

/* The following structure holds the information about the occurrences of
   the redundant instructions.  */
struct unoccr
{
  struct unoccr *next;
  edge pred;
  rtx insn;
};

static struct obstack unoccr_obstack;

/* Array where each element is the CUID if the insn that last set the hard
   register with the number of the element, since the start of the current
   basic block.

   This array is used during the building of the hash table (step 1) to
   determine if a reg is killed before the end of a basic block.

   It is also used when eliminating partial redundancies (step 2) to see
   if a reg was modified since the start of a basic block.  */
static int *reg_avail_info;

/* A list of insns that may modify memory within the current basic block.  */
struct modifies_mem
{
  rtx insn;
  struct modifies_mem *next;
};
static struct modifies_mem *modifies_mem_list;

/* The modifies_mem structs also go on an obstack, only this obstack is
   freed each time after completing the analysis or transformations on
   a basic block.  So we allocate a dummy modifies_mem_obstack_bottom
   object on the obstack to keep track of the bottom of the obstack.  */
static struct obstack modifies_mem_obstack;
static struct modifies_mem  *modifies_mem_obstack_bottom;

/* Mapping of insn UIDs to CUIDs.
   CUIDs are like UIDs except they increase monotonically in each basic
   block, have no gaps, and only apply to real insns.  */
static int *uid_cuid;
#define INSN_CUID(INSN) (uid_cuid[INSN_UID (INSN)])


/* Helpers for memory allocation/freeing.  */
static void alloc_mem (void);
static void free_mem (void);

/* Support for hash table construction and transformations.  */
static bool oprs_unchanged_p (rtx, rtx, bool);
static void record_last_reg_set_info (rtx, rtx);
static void record_last_reg_set_info_regno (rtx, int);
static void record_last_mem_set_info (rtx);
static void record_last_set_info (rtx, const_rtx, void *);
static void record_opr_changes (rtx);

static void find_mem_conflicts (rtx, const_rtx, void *);
static int load_killed_in_block_p (int, rtx, bool);
static void reset_opr_set_tables (void);

/* Hash table support.  */
static hashval_t hash_expr (rtx, int *);
static void insert_expr_in_table (rtx, rtx);
static struct expr *lookup_expr_in_table (rtx);
static void dump_hash_table (FILE *);

/* Helpers for eliminate_partially_redundant_load.  */
static bool reg_killed_on_edge (rtx, edge);
static bool reg_used_on_edge (rtx, edge);

static rtx get_avail_load_store_reg (rtx);

static bool bb_has_well_behaved_predecessors (basic_block);
static struct occr* get_bb_avail_insn (basic_block, struct occr *);
static void hash_scan_set (rtx);
static void compute_hash_table (void);

/* The work horses of this pass.  */
static void eliminate_partially_redundant_load (basic_block,
						rtx,
						struct expr *);
static void eliminate_partially_redundant_loads (void);


/* Allocate memory for the CUID mapping array and register/memory
   tracking tables.  */

static void
alloc_mem (void)
{
  int i;
  basic_block bb;
  rtx insn;

  /* Find the largest UID and create a mapping from UIDs to CUIDs.  */
  uid_cuid = XCNEWVEC (int, get_max_uid () + 1);
  i = 1;
  FOR_EACH_BB (bb)
    FOR_BB_INSNS (bb, insn)
      {
        if (INSN_P (insn))
	  uid_cuid[INSN_UID (insn)] = i++;
	else
	  uid_cuid[INSN_UID (insn)] = i;
      }

  /* Allocate the available expressions hash table.  We don't want to
     make the hash table too small, but unnecessarily making it too large
     also doesn't help.  The i/4 is a gcse.c relic, and seems like a
     reasonable choice.  */
  expr_table.create (MAX (i / 4, 13));

  /* We allocate everything on obstacks because we often can roll back
     the whole obstack to some point.  Freeing obstacks is very fast.  */
  gcc_obstack_init (&expr_obstack);
  gcc_obstack_init (&occr_obstack);
  gcc_obstack_init (&unoccr_obstack);
  gcc_obstack_init (&modifies_mem_obstack);

  /* Working array used to track the last set for each register
     in the current block.  */
  reg_avail_info = (int *) xmalloc (FIRST_PSEUDO_REGISTER * sizeof (int));

  /* Put a dummy modifies_mem object on the modifies_mem_obstack, so we
     can roll it back in reset_opr_set_tables.  */
  modifies_mem_obstack_bottom =
    (struct modifies_mem *) obstack_alloc (&modifies_mem_obstack,
					   sizeof (struct modifies_mem));
}

/* Free memory allocated by alloc_mem.  */

static void
free_mem (void)
{
  free (uid_cuid);

  expr_table.dispose ();

  obstack_free (&expr_obstack, NULL);
  obstack_free (&occr_obstack, NULL);
  obstack_free (&unoccr_obstack, NULL);
  obstack_free (&modifies_mem_obstack, NULL);

  free (reg_avail_info);
}


/* Insert expression X in INSN in the hash TABLE.
   If it is already present, record it as the last occurrence in INSN's
   basic block.  */

static void
insert_expr_in_table (rtx x, rtx insn)
{
  int do_not_record_p;
  hashval_t hash;
  struct expr *cur_expr, **slot;
  struct occr *avail_occr, *last_occr = NULL;

  hash = hash_expr (x, &do_not_record_p);

  /* Do not insert expression in the table if it contains volatile operands,
     or if hash_expr determines the expression is something we don't want
     to or can't handle.  */
  if (do_not_record_p)
    return;

  /* We anticipate that redundant expressions are rare, so for convenience
     allocate a new hash table element here already and set its fields.
     If we don't do this, we need a hack with a static struct expr.  Anyway,
     obstack_free is really fast and one more obstack_alloc doesn't hurt if
     we're going to see more expressions later on.  */
  cur_expr = (struct expr *) obstack_alloc (&expr_obstack,
					    sizeof (struct expr));
  cur_expr->expr = x;
  cur_expr->hash = hash;
  cur_expr->avail_occr = NULL;

  slot = expr_table.find_slot_with_hash (cur_expr, hash, INSERT);

  if (! (*slot))
    /* The expression isn't found, so insert it.  */
    *slot = cur_expr;
  else
    {
      /* The expression is already in the table, so roll back the
	 obstack and use the existing table entry.  */
      obstack_free (&expr_obstack, cur_expr);
      cur_expr = *slot;
    }

  /* Search for another occurrence in the same basic block.  */
  avail_occr = cur_expr->avail_occr;
  while (avail_occr
	 && BLOCK_FOR_INSN (avail_occr->insn) != BLOCK_FOR_INSN (insn))
    {
      /* If an occurrence isn't found, save a pointer to the end of
	 the list.  */
      last_occr = avail_occr;
      avail_occr = avail_occr->next;
    }

  if (avail_occr)
    /* Found another instance of the expression in the same basic block.
       Prefer this occurrence to the currently recorded one.  We want
       the last one in the block and the block is scanned from start
       to end.  */
    avail_occr->insn = insn;
  else
    {
      /* First occurrence of this expression in this basic block.  */
      avail_occr = (struct occr *) obstack_alloc (&occr_obstack,
						  sizeof (struct occr));

      /* First occurrence of this expression in any block?  */
      if (cur_expr->avail_occr == NULL)
        cur_expr->avail_occr = avail_occr;
      else
        last_occr->next = avail_occr;

      avail_occr->insn = insn;
      avail_occr->next = NULL;
      avail_occr->deleted_p = 0;
    }
}


/* Lookup pattern PAT in the expression hash table.
   The result is a pointer to the table entry, or NULL if not found.  */

static struct expr *
lookup_expr_in_table (rtx pat)
{
  int do_not_record_p;
  struct expr **slot, *tmp_expr;
  hashval_t hash = hash_expr (pat, &do_not_record_p);

  if (do_not_record_p)
    return NULL;

  tmp_expr = (struct expr *) obstack_alloc (&expr_obstack,
					    sizeof (struct expr));
  tmp_expr->expr = pat;
  tmp_expr->hash = hash;
  tmp_expr->avail_occr = NULL;

  slot = expr_table.find_slot_with_hash (tmp_expr, hash, INSERT);
  obstack_free (&expr_obstack, tmp_expr);

  if (!slot)
    return NULL;
  else
    return (*slot);
}


/* Dump all expressions and occurrences that are currently in the
   expression hash table to FILE.  */

/* This helper is called via htab_traverse.  */
int
dump_expr_hash_table_entry (expr **slot, FILE *file)
{
  struct expr *exprs = *slot;
  struct occr *occr;

  fprintf (file, "expr: ");
  print_rtl (file, exprs->expr);
  fprintf (file,"\nhashcode: %u\n", exprs->hash);
  fprintf (file,"list of occurrences:\n");
  occr = exprs->avail_occr;
  while (occr)
    {
      rtx insn = occr->insn;
      print_rtl_single (file, insn);
      fprintf (file, "\n");
      occr = occr->next;
    }
  fprintf (file, "\n");
  return 1;
}

static void
dump_hash_table (FILE *file)
{
  fprintf (file, "\n\nexpression hash table\n");
  fprintf (file, "size %ld, %ld elements, %f collision/search ratio\n",
           (long) expr_table.size (),
           (long) expr_table.elements (),
           expr_table.collisions ());
  if (expr_table.elements () > 0)
    {
      fprintf (file, "\n\ntable entries:\n");
      expr_table.traverse <FILE *, dump_expr_hash_table_entry> (file);
    }
  fprintf (file, "\n");
}

/* Return true if register X is recorded as being set by an instruction
   whose CUID is greater than the one given.  */

static bool
reg_changed_after_insn_p (rtx x, int cuid)
{
  unsigned int regno, end_regno;

  regno = REGNO (x);
  end_regno = END_HARD_REGNO (x);
  do
    if (reg_avail_info[regno] > cuid)
      return true;
  while (++regno < end_regno);
  return false;
}

/* Return nonzero if the operands of expression X are unchanged
   1) from the start of INSN's basic block up to but not including INSN
      if AFTER_INSN is false, or
   2) from INSN to the end of INSN's basic block if AFTER_INSN is true.  */

static bool
oprs_unchanged_p (rtx x, rtx insn, bool after_insn)
{
  int i, j;
  enum rtx_code code;
  const char *fmt;

  if (x == 0)
    return 1;

  code = GET_CODE (x);
  switch (code)
    {
    case REG:
      /* We are called after register allocation.  */
      gcc_assert (REGNO (x) < FIRST_PSEUDO_REGISTER);
      if (after_insn)
	return !reg_changed_after_insn_p (x, INSN_CUID (insn) - 1);
      else
	return !reg_changed_after_insn_p (x, 0);

    case MEM:
      if (load_killed_in_block_p (INSN_CUID (insn), x, after_insn))
	return 0;
      else
	return oprs_unchanged_p (XEXP (x, 0), insn, after_insn);

    case PC:
    case CC0: /*FIXME*/
    case CONST:
    CASE_CONST_ANY:
    case SYMBOL_REF:
    case LABEL_REF:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
      return 1;

    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
    case PRE_MODIFY:
    case POST_MODIFY:
      if (after_insn)
	return 0;
      break;

    default:
      break;
    }

  for (i = GET_RTX_LENGTH (code) - 1, fmt = GET_RTX_FORMAT (code); i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  if (! oprs_unchanged_p (XEXP (x, i), insn, after_insn))
	    return 0;
	}
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (! oprs_unchanged_p (XVECEXP (x, i, j), insn, after_insn))
	    return 0;
    }

  return 1;
}


/* Used for communication between find_mem_conflicts and
   load_killed_in_block_p.  Nonzero if find_mem_conflicts finds a
   conflict between two memory references.
   This is a bit of a hack to work around the limitations of note_stores.  */
static int mems_conflict_p;

/* DEST is the output of an instruction.  If it is a memory reference, and
   possibly conflicts with the load found in DATA, then set mems_conflict_p
   to a nonzero value.  */

static void
find_mem_conflicts (rtx dest, const_rtx setter ATTRIBUTE_UNUSED,
		    void *data)
{
  rtx mem_op = (rtx) data;

  while (GET_CODE (dest) == SUBREG
	 || GET_CODE (dest) == ZERO_EXTRACT
	 || GET_CODE (dest) == STRICT_LOW_PART)
    dest = XEXP (dest, 0);

  /* If DEST is not a MEM, then it will not conflict with the load.  Note
     that function calls are assumed to clobber memory, but are handled
     elsewhere.  */
  if (! MEM_P (dest))
    return;

  if (true_dependence (dest, GET_MODE (dest), mem_op))
    mems_conflict_p = 1;
}


/* Return nonzero if the expression in X (a memory reference) is killed
   in the current basic block before (if AFTER_INSN is false) or after
   (if AFTER_INSN is true) the insn with the CUID in UID_LIMIT.

   This function assumes that the modifies_mem table is flushed when
   the hash table construction or redundancy elimination phases start
   processing a new basic block.  */

static int
load_killed_in_block_p (int uid_limit, rtx x, bool after_insn)
{
  struct modifies_mem *list_entry = modifies_mem_list;

  while (list_entry)
    {
      rtx setter = list_entry->insn;

      /* Ignore entries in the list that do not apply.  */
      if ((after_insn
	   && INSN_CUID (setter) < uid_limit)
	  || (! after_insn
	      && INSN_CUID (setter) > uid_limit))
	{
	  list_entry = list_entry->next;
	  continue;
	}

      /* If SETTER is a call everything is clobbered.  Note that calls
	 to pure functions are never put on the list, so we need not
	 worry about them.  */
      if (CALL_P (setter))
	return 1;

      /* SETTER must be an insn of some kind that sets memory.  Call
	 note_stores to examine each hunk of memory that is modified.
	 It will set mems_conflict_p to nonzero if there may be a
	 conflict between X and SETTER.  */
      mems_conflict_p = 0;
      note_stores (PATTERN (setter), find_mem_conflicts, x);
      if (mems_conflict_p)
	return 1;

      list_entry = list_entry->next;
    }
  return 0;
}


/* Record register first/last/block set information for REGNO in INSN.  */

static inline void
record_last_reg_set_info (rtx insn, rtx reg)
{
  unsigned int regno, end_regno;

  regno = REGNO (reg);
  end_regno = END_HARD_REGNO (reg);
  do
    reg_avail_info[regno] = INSN_CUID (insn);
  while (++regno < end_regno);
}

static inline void
record_last_reg_set_info_regno (rtx insn, int regno)
{
  reg_avail_info[regno] = INSN_CUID (insn);
}


/* Record memory modification information for INSN.  We do not actually care
   about the memory location(s) that are set, or even how they are set (consider
   a CALL_INSN).  We merely need to record which insns modify memory.  */

static void
record_last_mem_set_info (rtx insn)
{
  struct modifies_mem *list_entry;

  list_entry = (struct modifies_mem *) obstack_alloc (&modifies_mem_obstack,
						      sizeof (struct modifies_mem));
  list_entry->insn = insn;
  list_entry->next = modifies_mem_list;
  modifies_mem_list = list_entry;
}

/* Called from compute_hash_table via note_stores to handle one
   SET or CLOBBER in an insn.  DATA is really the instruction in which
   the SET is taking place.  */

static void
record_last_set_info (rtx dest, const_rtx setter ATTRIBUTE_UNUSED, void *data)
{
  rtx last_set_insn = (rtx) data;

  if (GET_CODE (dest) == SUBREG)
    dest = SUBREG_REG (dest);

  if (REG_P (dest))
    record_last_reg_set_info (last_set_insn, dest);
  else if (MEM_P (dest))
    {
      /* Ignore pushes, they don't clobber memory.  They may still
	 clobber the stack pointer though.  Some targets do argument
	 pushes without adding REG_INC notes.  See e.g. PR25196,
	 where a pushsi2 on i386 doesn't have REG_INC notes.  Note
	 such changes here too.  */
      if (! push_operand (dest, GET_MODE (dest)))
	record_last_mem_set_info (last_set_insn);
      else
	record_last_reg_set_info_regno (last_set_insn, STACK_POINTER_REGNUM);
    }
}


/* Reset tables used to keep track of what's still available since the
   start of the block.  */

static void
reset_opr_set_tables (void)
{
  memset (reg_avail_info, 0, FIRST_PSEUDO_REGISTER * sizeof (int));
  obstack_free (&modifies_mem_obstack, modifies_mem_obstack_bottom);
  modifies_mem_list = NULL;
}


/* Record things set by INSN.
   This data is used by oprs_unchanged_p.  */

static void
record_opr_changes (rtx insn)
{
  rtx note;

  /* Find all stores and record them.  */
  note_stores (PATTERN (insn), record_last_set_info, insn);

  /* Also record autoincremented REGs for this insn as changed.  */
  for (note = REG_NOTES (insn); note; note = XEXP (note, 1))
    if (REG_NOTE_KIND (note) == REG_INC)
      record_last_reg_set_info (insn, XEXP (note, 0));

  /* Finally, if this is a call, record all call clobbers.  */
  if (CALL_P (insn))
    {
      unsigned int regno;
      rtx link, x;
      hard_reg_set_iterator hrsi;
      EXECUTE_IF_SET_IN_HARD_REG_SET (regs_invalidated_by_call, 0, regno, hrsi)
	record_last_reg_set_info_regno (insn, regno);

      for (link = CALL_INSN_FUNCTION_USAGE (insn); link; link = XEXP (link, 1))
	if (GET_CODE (XEXP (link, 0)) == CLOBBER)
	  {
	    x = XEXP (XEXP (link, 0), 0);
	    if (REG_P (x))
	      {
		gcc_assert (HARD_REGISTER_P (x));
		record_last_reg_set_info (insn, x);
	      }
	  }

      if (! RTL_CONST_OR_PURE_CALL_P (insn))
	record_last_mem_set_info (insn);
    }
}


/* Scan the pattern of INSN and add an entry to the hash TABLE.
   After reload we are interested in loads/stores only.  */

static void
hash_scan_set (rtx insn)
{
  rtx pat = PATTERN (insn);
  rtx src = SET_SRC (pat);
  rtx dest = SET_DEST (pat);

  /* We are only interested in loads and stores.  */
  if (! MEM_P (src) && ! MEM_P (dest))
    return;

  /* Don't mess with jumps and nops.  */
  if (JUMP_P (insn) || set_noop_p (pat))
    return;

  if (REG_P (dest))
    {
      if (/* Don't CSE something if we can't do a reg/reg copy.  */
	  can_copy_p (GET_MODE (dest))
	  /* Is SET_SRC something we want to gcse?  */
	  && general_operand (src, GET_MODE (src))
#ifdef STACK_REGS
	  /* Never consider insns touching the register stack.  It may
	     create situations that reg-stack cannot handle (e.g. a stack
	     register live across an abnormal edge).  */
	  && (REGNO (dest) < FIRST_STACK_REG || REGNO (dest) > LAST_STACK_REG)
#endif
	  /* An expression is not available if its operands are
	     subsequently modified, including this insn.  */
	  && oprs_unchanged_p (src, insn, true))
	{
	  insert_expr_in_table (src, insn);
	}
    }
  else if (REG_P (src))
    {
      /* Only record sets of pseudo-regs in the hash table.  */
      if (/* Don't CSE something if we can't do a reg/reg copy.  */
	  can_copy_p (GET_MODE (src))
	  /* Is SET_DEST something we want to gcse?  */
	  && general_operand (dest, GET_MODE (dest))
#ifdef STACK_REGS
	  /* As above for STACK_REGS.  */
	  && (REGNO (src) < FIRST_STACK_REG || REGNO (src) > LAST_STACK_REG)
#endif
	  && ! (flag_float_store && FLOAT_MODE_P (GET_MODE (dest)))
	  /* Check if the memory expression is killed after insn.  */
	  && ! load_killed_in_block_p (INSN_CUID (insn) + 1, dest, true)
	  && oprs_unchanged_p (XEXP (dest, 0), insn, true))
	{
	  insert_expr_in_table (dest, insn);
	}
    }
}


/* Create hash table of memory expressions available at end of basic
   blocks.  Basically you should think of this hash table as the
   representation of AVAIL_OUT.  This is the set of expressions that
   is generated in a basic block and not killed before the end of the
   same basic block.  Notice that this is really a local computation.  */

static void
compute_hash_table (void)
{
  basic_block bb;

  FOR_EACH_BB (bb)
    {
      rtx insn;

      /* First pass over the instructions records information used to
	 determine when registers and memory are last set.
	 Since we compute a "local" AVAIL_OUT, reset the tables that
	 help us keep track of what has been modified since the start
	 of the block.  */
      reset_opr_set_tables ();
      FOR_BB_INSNS (bb, insn)
	{
	  if (INSN_P (insn))
            record_opr_changes (insn);
	}

      /* The next pass actually builds the hash table.  */
      FOR_BB_INSNS (bb, insn)
	if (INSN_P (insn) && GET_CODE (PATTERN (insn)) == SET)
	  hash_scan_set (insn);
    }
}


/* Check if register REG is killed in any insn waiting to be inserted on
   edge E.  This function is required to check that our data flow analysis
   is still valid prior to commit_edge_insertions.  */

static bool
reg_killed_on_edge (rtx reg, edge e)
{
  rtx insn;

  for (insn = e->insns.r; insn; insn = NEXT_INSN (insn))
    if (INSN_P (insn) && reg_set_p (reg, insn))
      return true;

  return false;
}

/* Similar to above - check if register REG is used in any insn waiting
   to be inserted on edge E.
   Assumes no such insn can be a CALL_INSN; if so call reg_used_between_p
   with PREV(insn),NEXT(insn) instead of calling reg_overlap_mentioned_p.  */

static bool
reg_used_on_edge (rtx reg, edge e)
{
  rtx insn;

  for (insn = e->insns.r; insn; insn = NEXT_INSN (insn))
    if (INSN_P (insn) && reg_overlap_mentioned_p (reg, PATTERN (insn)))
      return true;

  return false;
}

/* Return the loaded/stored register of a load/store instruction.  */

static rtx
get_avail_load_store_reg (rtx insn)
{
  if (REG_P (SET_DEST (PATTERN (insn))))
    /* A load.  */
    return SET_DEST(PATTERN(insn));
  else
    {
      /* A store.  */
      gcc_assert (REG_P (SET_SRC (PATTERN (insn))));
      return SET_SRC (PATTERN (insn));
    }
}

/* Return nonzero if the predecessors of BB are "well behaved".  */

static bool
bb_has_well_behaved_predecessors (basic_block bb)
{
  edge pred;
  edge_iterator ei;

  if (EDGE_COUNT (bb->preds) == 0)
    return false;

  FOR_EACH_EDGE (pred, ei, bb->preds)
    {
      if ((pred->flags & EDGE_ABNORMAL) && EDGE_CRITICAL_P (pred))
	return false;

      if ((pred->flags & EDGE_ABNORMAL_CALL) && cfun->has_nonlocal_label)
	return false;

      if (JUMP_TABLE_DATA_P (BB_END (pred->src)))
	return false;
    }
  return true;
}


/* Search for the occurrences of expression in BB.  */

static struct occr*
get_bb_avail_insn (basic_block bb, struct occr *occr)
{
  for (; occr != NULL; occr = occr->next)
    if (BLOCK_FOR_INSN (occr->insn) == bb)
      return occr;
  return NULL;
}


/* This handles the case where several stores feed a partially redundant
   load. It checks if the redundancy elimination is possible and if it's
   worth it.

   Redundancy elimination is possible if,
   1) None of the operands of an insn have been modified since the start
      of the current basic block.
   2) In any predecessor of the current basic block, the same expression
      is generated.

   See the function body for the heuristics that determine if eliminating
   a redundancy is also worth doing, assuming it is possible.  */

static void
eliminate_partially_redundant_load (basic_block bb, rtx insn,
				    struct expr *expr)
{
  edge pred;
  rtx avail_insn = NULL_RTX;
  rtx avail_reg;
  rtx dest, pat;
  struct occr *a_occr;
  struct unoccr *occr, *avail_occrs = NULL;
  struct unoccr *unoccr, *unavail_occrs = NULL, *rollback_unoccr = NULL;
  int npred_ok = 0;
  gcov_type ok_count = 0; /* Redundant load execution count.  */
  gcov_type critical_count = 0; /* Execution count of critical edges.  */
  edge_iterator ei;
  bool critical_edge_split = false;

  /* The execution count of the loads to be added to make the
     load fully redundant.  */
  gcov_type not_ok_count = 0;
  basic_block pred_bb;

  pat = PATTERN (insn);
  dest = SET_DEST (pat);

  /* Check that the loaded register is not used, set, or killed from the
     beginning of the block.  */
  if (reg_changed_after_insn_p (dest, 0)
      || reg_used_between_p (dest, PREV_INSN (BB_HEAD (bb)), insn))
    return;

  /* Check potential for replacing load with copy for predecessors.  */
  FOR_EACH_EDGE (pred, ei, bb->preds)
    {
      rtx next_pred_bb_end;

      avail_insn = NULL_RTX;
      avail_reg = NULL_RTX;
      pred_bb = pred->src;
      next_pred_bb_end = NEXT_INSN (BB_END (pred_bb));
      for (a_occr = get_bb_avail_insn (pred_bb, expr->avail_occr); a_occr;
	   a_occr = get_bb_avail_insn (pred_bb, a_occr->next))
	{
	  /* Check if the loaded register is not used.  */
	  avail_insn = a_occr->insn;
	  avail_reg = get_avail_load_store_reg (avail_insn);
	  gcc_assert (avail_reg);

	  /* Make sure we can generate a move from register avail_reg to
	     dest.  */
	  extract_insn (gen_move_insn (copy_rtx (dest),
				       copy_rtx (avail_reg)));
	  if (! constrain_operands (1)
	      || reg_killed_on_edge (avail_reg, pred)
	      || reg_used_on_edge (dest, pred))
	    {
	      avail_insn = NULL;
	      continue;
	    }
	  if (!reg_set_between_p (avail_reg, avail_insn, next_pred_bb_end))
	    /* AVAIL_INSN remains non-null.  */
	    break;
	  else
	    avail_insn = NULL;
	}

      if (EDGE_CRITICAL_P (pred))
	critical_count += pred->count;

      if (avail_insn != NULL_RTX)
	{
	  npred_ok++;
	  ok_count += pred->count;
	  if (! set_noop_p (PATTERN (gen_move_insn (copy_rtx (dest),
						    copy_rtx (avail_reg)))))
	    {
	      /* Check if there is going to be a split.  */
	      if (EDGE_CRITICAL_P (pred))
		critical_edge_split = true;
	    }
	  else /* Its a dead move no need to generate.  */
	    continue;
	  occr = (struct unoccr *) obstack_alloc (&unoccr_obstack,
						  sizeof (struct unoccr));
	  occr->insn = avail_insn;
	  occr->pred = pred;
	  occr->next = avail_occrs;
	  avail_occrs = occr;
	  if (! rollback_unoccr)
	    rollback_unoccr = occr;
	}
      else
	{
	  /* Adding a load on a critical edge will cause a split.  */
	  if (EDGE_CRITICAL_P (pred))
	    critical_edge_split = true;
	  not_ok_count += pred->count;
	  unoccr = (struct unoccr *) obstack_alloc (&unoccr_obstack,
						    sizeof (struct unoccr));
	  unoccr->insn = NULL_RTX;
	  unoccr->pred = pred;
	  unoccr->next = unavail_occrs;
	  unavail_occrs = unoccr;
	  if (! rollback_unoccr)
	    rollback_unoccr = unoccr;
	}
    }

  if (/* No load can be replaced by copy.  */
      npred_ok == 0
      /* Prevent exploding the code.  */
      || (optimize_bb_for_size_p (bb) && npred_ok > 1)
      /* If we don't have profile information we cannot tell if splitting
         a critical edge is profitable or not so don't do it.  */
      || ((! profile_info || ! flag_branch_probabilities
	   || targetm.cannot_modify_jumps_p ())
	  && critical_edge_split))
    goto cleanup;

  /* Check if it's worth applying the partial redundancy elimination.  */
  if (ok_count < GCSE_AFTER_RELOAD_PARTIAL_FRACTION * not_ok_count)
    goto cleanup;
  if (ok_count < GCSE_AFTER_RELOAD_CRITICAL_FRACTION * critical_count)
    goto cleanup;

  /* Generate moves to the loaded register from where
     the memory is available.  */
  for (occr = avail_occrs; occr; occr = occr->next)
    {
      avail_insn = occr->insn;
      pred = occr->pred;
      /* Set avail_reg to be the register having the value of the
	 memory.  */
      avail_reg = get_avail_load_store_reg (avail_insn);
      gcc_assert (avail_reg);

      insert_insn_on_edge (gen_move_insn (copy_rtx (dest),
					  copy_rtx (avail_reg)),
			   pred);
      stats.moves_inserted++;

      if (dump_file)
	fprintf (dump_file,
		 "generating move from %d to %d on edge from %d to %d\n",
		 REGNO (avail_reg),
		 REGNO (dest),
		 pred->src->index,
		 pred->dest->index);
    }

  /* Regenerate loads where the memory is unavailable.  */
  for (unoccr = unavail_occrs; unoccr; unoccr = unoccr->next)
    {
      pred = unoccr->pred;
      insert_insn_on_edge (copy_insn (PATTERN (insn)), pred);
      stats.copies_inserted++;

      if (dump_file)
	{
	  fprintf (dump_file,
		   "generating on edge from %d to %d a copy of load: ",
		   pred->src->index,
		   pred->dest->index);
	  print_rtl (dump_file, PATTERN (insn));
	  fprintf (dump_file, "\n");
	}
    }

  /* Delete the insn if it is not available in this block and mark it
     for deletion if it is available. If insn is available it may help
     discover additional redundancies, so mark it for later deletion.  */
  for (a_occr = get_bb_avail_insn (bb, expr->avail_occr);
       a_occr && (a_occr->insn != insn);
       a_occr = get_bb_avail_insn (bb, a_occr->next))
    ;

  if (!a_occr)
    {
      stats.insns_deleted++;

      if (dump_file)
	{
	  fprintf (dump_file, "deleting insn:\n");
          print_rtl_single (dump_file, insn);
          fprintf (dump_file, "\n");
	}
      delete_insn (insn);
    }
  else
    a_occr->deleted_p = 1;

cleanup:
  if (rollback_unoccr)
    obstack_free (&unoccr_obstack, rollback_unoccr);
}

/* Performing the redundancy elimination as described before.  */

static void
eliminate_partially_redundant_loads (void)
{
  rtx insn;
  basic_block bb;

  /* Note we start at block 1.  */

  if (ENTRY_BLOCK_PTR->next_bb == EXIT_BLOCK_PTR)
    return;

  FOR_BB_BETWEEN (bb,
		  ENTRY_BLOCK_PTR->next_bb->next_bb,
		  EXIT_BLOCK_PTR,
		  next_bb)
    {
      /* Don't try anything on basic blocks with strange predecessors.  */
      if (! bb_has_well_behaved_predecessors (bb))
	continue;

      /* Do not try anything on cold basic blocks.  */
      if (optimize_bb_for_size_p (bb))
	continue;

      /* Reset the table of things changed since the start of the current
	 basic block.  */
      reset_opr_set_tables ();

      /* Look at all insns in the current basic block and see if there are
	 any loads in it that we can record.  */
      FOR_BB_INSNS (bb, insn)
	{
	  /* Is it a load - of the form (set (reg) (mem))?  */
	  if (NONJUMP_INSN_P (insn)
              && GET_CODE (PATTERN (insn)) == SET
	      && REG_P (SET_DEST (PATTERN (insn)))
	      && MEM_P (SET_SRC (PATTERN (insn))))
	    {
	      rtx pat = PATTERN (insn);
	      rtx src = SET_SRC (pat);
	      struct expr *expr;

	      if (!MEM_VOLATILE_P (src)
		  && GET_MODE (src) != BLKmode
		  && general_operand (src, GET_MODE (src))
		  /* Are the operands unchanged since the start of the
		     block?  */
		  && oprs_unchanged_p (src, insn, false)
		  && !(cfun->can_throw_non_call_exceptions && may_trap_p (src))
		  && !side_effects_p (src)
		  /* Is the expression recorded?  */
		  && (expr = lookup_expr_in_table (src)) != NULL)
		{
		  /* We now have a load (insn) and an available memory at
		     its BB start (expr). Try to remove the loads if it is
		     redundant.  */
		  eliminate_partially_redundant_load (bb, insn, expr);
		}
	    }

	  /* Keep track of everything modified by this insn, so that we
	     know what has been modified since the start of the current
	     basic block.  */
	  if (INSN_P (insn))
	    record_opr_changes (insn);
	}
    }

  commit_edge_insertions ();
}

/* Go over the expression hash table and delete insns that were
   marked for later deletion.  */

/* This helper is called via htab_traverse.  */
int
delete_redundant_insns_1 (expr **slot, void *data ATTRIBUTE_UNUSED)
{
  struct expr *exprs = *slot;
  struct occr *occr;

  for (occr = exprs->avail_occr; occr != NULL; occr = occr->next)
    {
      if (occr->deleted_p && dbg_cnt (gcse2_delete))
	{
	  delete_insn (occr->insn);
	  stats.insns_deleted++;

	  if (dump_file)
	    {
	      fprintf (dump_file, "deleting insn:\n");
	      print_rtl_single (dump_file, occr->insn);
	      fprintf (dump_file, "\n");
	    }
	}
    }

  return 1;
}

static void
delete_redundant_insns (void)
{
  expr_table.traverse <void *, delete_redundant_insns_1> (NULL);
  if (dump_file)
    fprintf (dump_file, "\n");
}

/* Main entry point of the GCSE after reload - clean some redundant loads
   due to spilling.  */

static void
gcse_after_reload_main (rtx f ATTRIBUTE_UNUSED)
{

  memset (&stats, 0, sizeof (stats));

  /* Allocate memory for this pass.
     Also computes and initializes the insns' CUIDs.  */
  alloc_mem ();

  /* We need alias analysis.  */
  init_alias_analysis ();

  compute_hash_table ();

  if (dump_file)
    dump_hash_table (dump_file);

  if (expr_table.elements () > 0)
    {
      eliminate_partially_redundant_loads ();
      delete_redundant_insns ();

      if (dump_file)
	{
	  fprintf (dump_file, "GCSE AFTER RELOAD stats:\n");
	  fprintf (dump_file, "copies inserted: %d\n", stats.copies_inserted);
	  fprintf (dump_file, "moves inserted:  %d\n", stats.moves_inserted);
	  fprintf (dump_file, "insns deleted:   %d\n", stats.insns_deleted);
	  fprintf (dump_file, "\n\n");
	}

      statistics_counter_event (cfun, "copies inserted",
				stats.copies_inserted);
      statistics_counter_event (cfun, "moves inserted",
				stats.moves_inserted);
      statistics_counter_event (cfun, "insns deleted",
				stats.insns_deleted);
    }

  /* We are finished with alias.  */
  end_alias_analysis ();

  free_mem ();
}


static bool
gate_handle_gcse2 (void)
{
  return (optimize > 0 && flag_gcse_after_reload
	  && optimize_function_for_speed_p (cfun));
}


static unsigned int
rest_of_handle_gcse2 (void)
{
  gcse_after_reload_main (get_insns ());
  rebuild_jump_labels (get_insns ());
  return 0;
}

struct rtl_opt_pass pass_gcse2 =
{
 {
  RTL_PASS,
  "gcse2",                              /* name */
  OPTGROUP_NONE,                        /* optinfo_flags */
  gate_handle_gcse2,                    /* gate */
  rest_of_handle_gcse2,                 /* execute */
  NULL,                                 /* sub */
  NULL,                                 /* next */
  0,                                    /* static_pass_number */
  TV_GCSE_AFTER_RELOAD,                 /* tv_id */
  0,                                    /* properties_required */
  0,                                    /* properties_provided */
  0,                                    /* properties_destroyed */
  0,                                    /* todo_flags_start */
  TODO_verify_rtl_sharing
  | TODO_verify_flow | TODO_ggc_collect /* todo_flags_finish */
 }
};
