
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "backend.h"
#include "target.h"
#include "rtl.h"
#include "tree.h"
#include "cfghooks.h"
#include "df.h"
#include "tm_p.h"
#include "stringpool.h"
#include "optabs.h"
#include "regs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "cgraph.h"
#include "diagnostic-core.h"
#include "alias.h"
#include "fold-const.h"
#include "stor-layout.h"
#include "calls.h"
#include "varasm.h"
#include "output.h"
#include "insn-attr.h"
#include "flags.h"
#include "reload.h"
#include "explow.h"
#include "expr.h"
#include "cfgrtl.h"
#include "sched-int.h"
#include "common/common-target.h"
#include "langhooks.h"
#include "intl.h"
#include "libfuncs.h"
#include "params.h"
#include "opts.h"
#include "dumpfile.h"
#include "target-globals.h"
#include "builtins.h"
#include "tm-constrs.h"
#include "rtl-iter.h"
#include "pass_manager.h"
#include "tree-pass.h"
#include "context.h"
#include "cfgloop.h"

#include "abiv2_csky_internal.h"

/* This file should be included last.  */
#include "target-def.h"


/* Array of the smallest class containing reg number REGNO, indexed by
   REGNO.  Used by REGNO_REG_CLASS.  */
enum reg_class regno_reg_class[FIRST_PSEUDO_REGISTER] =
{
  /* Registers r0-r7.  */
  MINI_REGS,     MINI_REGS,     MINI_REGS,     MINI_REGS,
  MINI_REGS,     MINI_REGS,     MINI_REGS,     MINI_REGS,
  /* Registers r8-r15.  */
  LOW_REGS,      LOW_REGS,      LOW_REGS,      LOW_REGS,
  LOW_REGS,      LOW_REGS,      SP_REGS,       LOW_REGS,
  /* Registers r16-r31.  */
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  /* Reserved.  */
  RESERVE_REGS,
  /* CC,HI,LO registers.  */
  C_REGS,      HI_REGS,      LO_REGS,
  /* Reserved.  */
  RESERVE_REGS, RESERVE_REGS, RESERVE_REGS, RESERVE_REGS,
  RESERVE_REGS, RESERVE_REGS, RESERVE_REGS, RESERVE_REGS,
  RESERVE_REGS, RESERVE_REGS, RESERVE_REGS, RESERVE_REGS,
  RESERVE_REGS, RESERVE_REGS, RESERVE_REGS, RESERVE_REGS,
  /* Vec registers.  */
  V_REGS,       V_REGS,       V_REGS,       V_REGS,
  V_REGS,       V_REGS,       V_REGS,       V_REGS,
  V_REGS,       V_REGS,       V_REGS,       V_REGS,
  V_REGS,       V_REGS,       V_REGS,       V_REGS,
  /* Reserved.  */
  RESERVE_REGS, RESERVE_REGS,
  /* Register epc.  */
  OTHER_REGS
};

/* Arrays that map GCC register numbers to debugger register numbers,
   '-1' means that is INVALID_REGNUM.
   TODO: which rules according to here ?  */
const int csky_dbx_regno[FIRST_PSEUDO_REGISTER] =
{
  0,  1,  2,  3,  4,  5,  6,  7,
  8,  9,  10, 11, 12, 13, 14, 15,
  16, 17, 18, 19, 20, 21, 22, 23,
  24, 25, 26, 27, 28, 29, 30, 31,
  -1, -1, 36, 37, 35, 38, 39, 40,
  41, 42, 43, 44, 45, 46, 47, 48,
  49, 50, 51, 52, 53, 54, 55, 56,
  57, 58, 59, 60, 61, 62, 63, 64,
  65, 66, 67, 68, -1, -1, 72
};

/* Table of machine attributes.  */
static tree csky_handle_fndecl_attribute (tree *, tree, tree, int, bool *);
static tree csky_handle_isr_attribute (tree *, tree, tree, int, bool *);
static const struct attribute_spec csky_attribute_table[] =
{
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req, handler,
       affects_type_identity } */
  { "naked",     0, 0, true,  false, false, csky_handle_fndecl_attribute, false },
  /* Interrupt Service Routines have special prologue and epilogue requirements.  */
  { "interrupt", 0, 1, false, false, false, csky_handle_isr_attribute,    false },
  { "isr",       0, 1, false, false, false, csky_handle_isr_attribute,    false },
  { NULL,        0, 0, false, false, false, NULL,                         false }
};

/* This function added here for enable lra by default.
   JianPing Zeng comments.  */
static bool csky_abiv2_lra_p(void)
{
  return flag_lra;
}

#undef  TARGET_LRA_P
#define TARGET_LRA_P csky_abiv2_lra_p

/******************************************************************
 *                         Storage Layout                         *
 ******************************************************************/


#undef  TARGET_PROMOTE_FUNCTION_MODE
#define TARGET_PROMOTE_FUNCTION_MODE \
  csky_promote_function_mode


/******************************************************************
 *              Stack Layout and Calling Conventions              *
 ******************************************************************/


#undef  TARGET_FUNCTION_ARG
#define TARGET_FUNCTION_ARG csky_function_arg

#undef  TARGET_FUNCTION_ARG_ADVANCE
#define TARGET_FUNCTION_ARG_ADVANCE csky_function_arg_advance

#undef  TARGET_FUNCTION_ARG_BOUNDARY
#define TARGET_FUNCTION_ARG_BOUNDARY csky_function_arg_boundary

#undef  TARGET_FUNCTION_VALUE
#define TARGET_FUNCTION_VALUE csky_function_value

#undef  TARGET_LIBCALL_VALUE
#define TARGET_LIBCALL_VALUE csky_libcall_value

#undef  TARGET_FUNCTION_VALUE_REGNO_P
#define TARGET_FUNCTION_VALUE_REGNO_P csky_function_value_regno_p

#undef  TARGET_SPLIT_COMPLEX_ARG
#define TARGET_SPLIT_COMPLEX_ARG hook_bool_const_tree_true

/* So far, no benefit has been found for promoting prototype.
#undef  TARGET_PROMOTE_PROTOTYPES
#define TARGET_PROMOTE_PROTOTYPES hook_bool_const_tree_true
*/

#undef  TARGET_MUST_PASS_IN_STACK
#define TARGET_MUST_PASS_IN_STACK must_pass_in_stack_var_size

#undef  TARGET_ARG_PARTIAL_BYTES
#define TARGET_ARG_PARTIAL_BYTES csky_arg_partial_bytes

#undef  TARGET_PASS_BY_REFERENCE
#define TARGET_PASS_BY_REFERENCE hook_pass_by_reference_must_pass_in_stack

#undef  TARGET_ASM_OUTPUT_MI_THUNK
#define TARGET_ASM_OUTPUT_MI_THUNK csky_output_mi_thunk

#undef  TARGET_ASM_CAN_OUTPUT_MI_THUNK
#define TARGET_ASM_CAN_OUTPUT_MI_THUNK \
  hook_bool_const_tree_hwi_hwi_const_tree_true

#undef  TARGET_ASM_FUNCTION_PROLOGUE
#define TARGET_ASM_FUNCTION_PROLOGUE csky_output_function_prologue

#undef  TARGET_ASM_FUNCTION_EPILOGUE
#define TARGET_ASM_FUNCTION_EPILOGUE csky_output_function_epilogue

#undef  TARGET_WARN_FUNC_RETURN
#define TARGET_WARN_FUNC_RETURN csky_warn_func_return

#undef  TARGET_RETURN_IN_MEMORY
#define TARGET_RETURN_IN_MEMORY csky_return_in_memory


/******************************************************************
 *                Implementing the Varargs Macros                 *
 ******************************************************************/


#undef  TARGET_SETUP_INCOMING_VARARGS
#define TARGET_SETUP_INCOMING_VARARGS csky_setup_incoming_varargs


/******************************************************************
 *               Implicit Calls to Library Routines               *
 ******************************************************************/


#undef TARGET_INIT_LIBFUNCS
#define TARGET_INIT_LIBFUNCS csky_init_libfuncs


/******************************************************************
 *    Dividing the Output into Sections (Texts, Data, . . . )     *
 ******************************************************************/


#undef TARGET_HAVE_TLS
#define TARGET_HAVE_TLS true
#define CSKY_HAVE_TLS (TARGET_HAVE_TLS && CSKY_ISA_FEATURE(tls))


/******************************************************************
 *         Defining target-specific uses of __attribute__         *
 ******************************************************************/


#undef TARGET_ATTRIBUTE_TABLE
#define TARGET_ATTRIBUTE_TABLE csky_attribute_table

#undef  TARGET_OPTION_OVERRIDE
#define TARGET_OPTION_OVERRIDE csky_option_override


static int
csky_default_branch_cost (bool speed_p, bool predictable_p ATTRIBUTE_UNUSED)
{
  return 1;
}

static bool
csky_default_logical_op_non_short_circuit(void)
{
  return BRANCH_COST (optimize_function_for_speed_p (cfun), false) >= 2;
}

#include "abiv2_csky_tune_tables.h"

static struct csky_processors all_cores[] =
{
#undef CSKY_CORE
#define CSKY_CORE(NAME, CORE, X, ARCH, ISA, TUNE)  \
  {NAME, TARGET_CPU_##CORE, #ARCH, CSKY_BASE_ARCH_##ARCH, \
  {ISA CSKY_ISA_FEATURE_GET(none)}, TUNE},
#include "abiv2_csky_cores.def"
#undef CSKY_CORE
  {NULL, TARGET_CPU_csky_none, NULL, CSKY_BASE_ARCH_NONE, \
  {CSKY_ISA_FEATURE_GET(none)}, NULL}
};

static struct csky_processors all_architectures[] =
{
#undef CSKY_ARCH
#define CSKY_ARCH(NAME, CORE, ARCH, ISA)     \
  {NAME, TARGET_CPU_##CORE, #ARCH, CSKY_BASE_ARCH_##ARCH,  \
  {ISA CSKY_ISA_FEATURE_GET(none)}, NULL},
#include "abiv2_csky_cores.def"
#undef CSKY_ARCH
  {NULL, TARGET_CPU_csky_none, NULL, CSKY_BASE_ARCH_NONE, \
  {CSKY_ISA_FEATURE_GET(none)}, NULL}
};

static const struct csky_fpu_desc all_fpus[] =
{
#undef CSKY_FPU
#define CSKY_FPU(NAME, CNAME, ISA) \
  {NAME, {ISA CSKY_ISA_FEATURE_GET(none)}},
#include "abiv2_csky_cores.def"
#undef CSKY_FPU
};

static const struct csky_option2isa all_opt2isa[] =
{
#undef CSKY_OPTION
#define CSKY_OPTION(MASK, ISA) \
  {MASK, {ISA CSKY_ISA_FEATURE_GET(none)}},
#include "abiv2_csky_cores.def"
#undef CSKY_OPTION
};

/* Active target architecture.  */
struct csky_build_target csky_active_target;

/* The following are used in the .md file as equivalents to bits.  */
int csky_arch_isa_features[CSKY_ISA_FEATURE_GET(max)] = {0};

/* The highest CSKY architecture version supported by the target.  */
enum csky_base_architecture csky_base_arch = CSKY_TARGET_ARCH_GET(NONE);

/* The current tuning set.  */
const struct tune_params *current_tune = NULL;

const char *csky_arch_name = NULL;

/* Maximum size we are allowed to grow the stack in a single operation.
   If we want more, we must do it in increments of at most this size.
   If this value is 0, we don't check at all.  */
int csky_stack_increment = CSKY_STACK_UNITS_MAXSTEP;

/* Forward definitions of types.  */
typedef struct minipool_node    Mnode;
typedef struct minipool_fixup   Mfix;

static GTY(()) int tls_labelno;


#define CSKY_ADDISP_MAX_STEP  508
#define CSKY_SUBISP_MAX_STEP  508

#define CSKY_ADDI_MAX_STEP    ((CSKY_TARGET_ARCH(CK801)) \
                               ? (CSKY_ADDISP_MAX_STEP) : 4096)
#define CSKY_SUBI_MAX_STEP    ((CSKY_TARGET_ARCH(CK801)) \
                               ? (CSKY_SUBISP_MAX_STEP) : 4096)


/******************************************************************
 *                         Register Usage                         *
 ******************************************************************/

#undef  TARGET_CONDITIONAL_REGISTER_USAGE
#define TARGET_CONDITIONAL_REGISTER_USAGE csky_conditional_register_usage

#undef TARGET_CLASS_LIKELY_SPILLED_P
#define TARGET_CLASS_LIKELY_SPILLED_P csky_class_likely_spilled_p

#undef TARGET_PREFERRED_RELOAD_CLASS
#define TARGET_PREFERRED_RELOAD_CLASS csky_preferred_reload_class

#undef TARGET_CLASS_MAX_NREGS
#define TARGET_CLASS_MAX_NREGS csky_class_max_nregs

#undef  TARGET_SECONDARY_RELOAD
#define TARGET_SECONDARY_RELOAD  csky_secondary_reload


/******************************************************************
 *                        Addressing Modes                        *
 ******************************************************************/


#undef TARGET_CANNOT_FORCE_CONST_MEM
#define TARGET_CANNOT_FORCE_CONST_MEM csky_cannot_force_const_mem

#undef TARGET_LEGITIMATE_CONSTANT_P
#define TARGET_LEGITIMATE_CONSTANT_P csky_legitimate_constant_p

#undef TARGET_LEGITIMIZE_ADDRESS
#define TARGET_LEGITIMIZE_ADDRESS csky_legitimize_address

#undef TARGET_LEGITIMATE_ADDRESS_P
#define TARGET_LEGITIMATE_ADDRESS_P csky_legitimate_address_p


/******************************************************************
 *                             Others                             *
 ******************************************************************/


#undef  TARGET_CANNOT_COPY_INSN_P
#define TARGET_CANNOT_COPY_INSN_P csky_cannot_copy_insn_p


/******************************************************************
 *                      Assembler Format                          *
 ******************************************************************/


#undef TARGET_PRINT_OPERAND
#define TARGET_PRINT_OPERAND csky_print_operand

#undef TARGET_PRINT_OPERAND_ADDRESS
#define TARGET_PRINT_OPERAND_ADDRESS csky_print_operand_address

#undef  TARGET_ASM_UNALIGNED_HI_OP
#define TARGET_ASM_UNALIGNED_HI_OP "\t.short\t"

#undef  TARGET_ASM_UNALIGNED_SI_OP
#define TARGET_ASM_UNALIGNED_SI_OP "\t.long\t"

#undef  TARGET_DWARF_REGISTER_SPAN
#define TARGET_DWARF_REGISTER_SPAN csky_dwarf_register_span


/******************************************************************
 *                    Miscellaneous Parameters                    *
 ******************************************************************/


#undef  TARGET_MACHINE_DEPENDENT_REORG
#define TARGET_MACHINE_DEPENDENT_REORG csky_reorg

#undef  TARGET_ALLOCATE_STACK_SLOTS_FOR_ARGS
#define TARGET_ALLOCATE_STACK_SLOTS_FOR_ARGS csky_allocate_stack_slots_for_args

#undef TARGET_CAN_USE_DOLOOP_P
#define TARGET_CAN_USE_DOLOOP_P csky_can_use_doloop_p

#undef TARGET_INVALID_WITHIN_DOLOOP
#define TARGET_INVALID_WITHIN_DOLOOP csky_invalid_within_doloop


/******************************************************************
 *                Trampolines for Nested Functions                *
 ******************************************************************/


#undef  TARGET_ASM_TRAMPOLINE_TEMPLATE
#define TARGET_ASM_TRAMPOLINE_TEMPLATE  csky_asm_trampoline_template
#undef  TARGET_TRAMPOLINE_INIT
#define TARGET_TRAMPOLINE_INIT          csky_trampoline_init


/******************************************************************
 *            Describing Relative Costs of Operations             *
 ******************************************************************/


#undef  TARGET_REGISTER_MOVE_COST
#define TARGET_REGISTER_MOVE_COST csky_register_move_cost

#undef  TARGET_MEMORY_MOVE_COST
#define TARGET_MEMORY_MOVE_COST   csky_memory_move_cost

#undef  TARGET_RTX_COSTS
#define TARGET_RTX_COSTS          csky_rtx_costs

#undef  TARGET_ADDRESS_COST
#define TARGET_ADDRESS_COST       csky_address_cost


/******************************************************************
 *                        Anchor address                          *
 ******************************************************************/

/* FIXME the max offset is related to mode size, the follow is
   defined according to SImode. How to deal with HImode and
   QImode, and should the min offset be defined?  */
#undef  TARGET_MAX_ANCHOR_OFFSET
#define TARGET_MAX_ANCHOR_OFFSET  (((CSKY_ISA_FEATURE(smart)        \
                                     || CSKY_TARGET_ARCH(CK801))    \
                                    && optimize_size) ? 127 : 4095)


/******************************************************************
 *                     Condition Code Status                      *
 ******************************************************************/


#undef  TARGET_FIXED_CONDITION_CODE_REGS
#define TARGET_FIXED_CONDITION_CODE_REGS csky_fixed_condition_code_regs


/******************************************************************
 *           Adjusting the Instruction Scheduler                  *
 ******************************************************************/


#undef  TARGET_SCHED_ISSUE_RATE
#define TARGET_SCHED_ISSUE_RATE csky_sched_issue_rate

#undef  TARGET_SCHED_ADJUST_COST
#define  TARGET_SCHED_ADJUST_COST csky_sched_adjust_cost

#undef  TARGET_SCHED_EXTRA_RESOURCE_CONFILICT
#define  TARGET_SCHED_EXTRA_RESOURCE_CONFILICT \
  csky_sched_extra_resource_confilict

/******************************************************************
 *           Construct VDSP Type and Builtin Function                  *
 ******************************************************************/

#undef  TARGET_INIT_BUILTINS
#define TARGET_INIT_BUILTINS  csky_init_builtins

#undef  TARGET_EXPAND_BUILTIN
#define TARGET_EXPAND_BUILTIN csky_expand_builtin

#undef  TARGET_BUILTIN_DECL
#define TARGET_BUILTIN_DECL csky_builtin_decl

#undef TARGET_VECTOR_MODE_SUPPORTED_P
#define TARGET_VECTOR_MODE_SUPPORTED_P csky_vector_mode_supported_p

#undef TARGET_VECTORIZE_PREFERRED_SIMD_MODE
#define TARGET_VECTORIZE_PREFERRED_SIMD_MODE csky_preferred_simd_mode

#undef  TARGET_FIXED_POINT_SUPPORTED_P
#define TARGET_FIXED_POINT_SUPPORTED_P hook_bool_void_true

#undef TARGET_SCALAR_MODE_SUPPORTED_P
#define TARGET_SCALAR_MODE_SUPPORTED_P csky_scalar_mode_supported_p

/******************************************************************
 *           Conditional Execution                                *
 ******************************************************************/

#undef TARGET_HAVE_CONDITIONAL_EXECUTION
#define TARGET_HAVE_CONDITIONAL_EXECUTION csky_have_conditional_execution

/* The number of conditionally executed insns, including the current insn. */
int csky_condexec_count = 0;
/* A bitmask specifying the patterns for the SCE block.
   Zero means do not output an SCE block before this insn. */
int csky_condexec_mask = 0;
/* The number of bits used in csky_condexec_mask. */
int csky_condexec_masklen = 0;

/* csky_current_cc is also used for cond_exec blocks. */
enum csky_cond_code csky_current_cc;

/* The declaration of functions.  */
static void get_csky_frame_layout (csky_stack_frame *);
static unsigned long get_csky_isr_type(tree);
static void push_csky_minipool_fix (rtx_insn *, HOST_WIDE_INT, rtx *,
                                    machine_mode, rtx);
void csky_print_operand_address (FILE * stream, machine_mode mode, rtx x);
void csky_print_operand (FILE * stream, rtx x, int code);
static enum csky_inline_const_type
try_csky_constant_tricks (HOST_WIDE_INT value, HOST_WIDE_INT * x,
                          HOST_WIDE_INT * y);
static bool is_pushpop_from_csky_live_regs(int mask);
static bool is_stm_from_csky_live_regs(int mask, int *br, int *er);
static void csky_add_gc_roots (void);

/* Used for lra eliminates regs.  */
static bool csky_can_eliminate (const int, const int);

/* Added by JianPing Zeng on 2018/1/5 copied from abiv1_csky.  */
#undef  TARGET_CAN_ELIMINATE
#define TARGET_CAN_ELIMINATE csky_can_eliminate


static unsigned long
compute_csky_func_type(void)
{
  unsigned long type = CSKY_FT_UNKNOWN;
  tree a;
  tree attr;

  gcc_assert(TREE_CODE(current_function_decl) == FUNCTION_DECL);

  attr = DECL_ATTRIBUTES(current_function_decl);

  a = lookup_attribute("naked", attr);
  if(a != NULL_TREE)
    type |= CSKY_FT_NAKED;

  a = lookup_attribute("isr", attr);
  if(a == NULL_TREE)
    a = lookup_attribute("interrupt", attr);

  if(a == NULL_TREE)
    type |= CSKY_FT_NORMAL;
  else
    type |= get_csky_isr_type(TREE_VALUE(a));

  return type;
}


static unsigned long
get_csky_current_func_type(void)
{
  if(CSKY_FUNCTION_TYPE(cfun->machine->func_type) == CSKY_FT_UNKNOWN)
    cfun->machine->func_type = compute_csky_func_type();

  return cfun->machine->func_type;
}


/* These typedefs are located at the start of this file, so that
   they can be used in the prototypes there.  This comment is to
   remind readers of that fact so that the following structures
   can be understood more easily.

     typedef struct minipool_node    Mnode;
     typedef struct minipool_fixup   Mfix;  */

struct minipool_node
{
  /* Doubly linked chain of entries.  */
  Mnode * next;
  Mnode * prev;
  /* The maximum offset into the code that this entry can be placed.  While
     pushing fixes for forward references, all entries are sorted in order
     of increasing max_address.  */
  HOST_WIDE_INT max_address;
  /* Similarly for an entry inserted for a backwards ref.  */
  HOST_WIDE_INT min_address;
  /* The number of fixes referencing this entry.  This can become zero
     if we "unpush" an entry.  In this case we ignore the entry when we
     come to emit the code.  */
  int refcount;
  /* The offset from the start of the minipool.  */
  HOST_WIDE_INT offset;
  /* The value in table.  */
  rtx value;
  /* The mode of value.  */
  enum machine_mode mode;
  /* The size of the value.  With iWMMXt enabled
     sizes > 4 also imply an alignment of 8-bytes.  */
  int fix_size;
};

struct minipool_fixup
{
  Mfix *            next;
  rtx_insn *        insn;
  HOST_WIDE_INT     address;
  rtx *             loc;
  enum machine_mode mode;
  int               fix_size;
  rtx               value;
  Mnode *           minipool;
  HOST_WIDE_INT     forwards;
  HOST_WIDE_INT     backwards;
};

static Mnode *  minipool_vector_head;
static Mnode *  minipool_vector_tail;
static rtx  minipool_vector_label;
static HOST_WIDE_INT constpool_label_no = 0;

/* Obstack for minipool constant handling.  */
static struct obstack minipool_obstack;
static char *minipool_startobj;
/* The linked list of all minipool fixes required for this function.  */
Mfix *      minipool_fix_head;
Mfix *      minipool_fix_tail;
/* The fix entry for the current minipool, once it has been placed.  */
Mfix *      minipool_barrier;


/* Record that there is a natural barrier in the insn stream at
   ADDRESS.  */

static void
push_csky_minipool_barrier (rtx_insn *insn, HOST_WIDE_INT address)
{
  Mfix * fix = (Mfix *) obstack_alloc (&minipool_obstack, sizeof (* fix));

  fix->insn = insn;
  fix->address = address;

  fix->next = NULL;
  if (minipool_fix_head != NULL)
    minipool_fix_tail->next = fix;
  else
    minipool_fix_head = fix;

  minipool_fix_tail = fix;
}


static HOST_WIDE_INT
get_csky_jump_table_size (rtx insn)
{
#ifndef JUMP_TABLES_IN_TEXT_SECTION
#define JUMP_TABLES_IN_TEXT_SECTION 0
#endif
  /* ADDR_VECs only take room if read-only data does into the text
     section.  */
  if (JUMP_TABLES_IN_TEXT_SECTION || readonly_data_section == text_section)
    {
      rtx body = PATTERN (insn);
      int elt = GET_CODE (body) == ADDR_DIFF_VEC ? 1 : 0;
      HOST_WIDE_INT size;
      HOST_WIDE_INT modesize;

      modesize = GET_MODE_SIZE (GET_MODE (body));
      size = modesize * XVECLEN (body, elt);
      switch (modesize)
        {
        case 1:
          /* Round up size  of TBB table to a halfword boundary.  */
          size = (size + 1) & ~(HOST_WIDE_INT)1;
          break;
        case 2:
          /* No padding necessary for TBH.  */
          break;
        case 4:
          break;
        default:
          gcc_unreachable ();
        }
      return size;
    }

  return 0;
}


/* Scan INSN and note any of its operands that need fixing.
   If DO_PUSHES is false we do not actually push any of the fixups
   needed.  The function returns TRUE if any fixups were needed/pushed.  */

static bool
note_csky_invalid_constants (rtx_insn *insn, HOST_WIDE_INT address, int do_pushes)
{
  bool result = false;
  int opno;

  extract_constrain_insn (insn);

  if (recog_data.n_alternatives == 0)
    return false;

  /* Fill in recog_op_alt with information about the constraints of
     this insn.  */
  preprocess_constraints (insn);

  const operand_alternative *op_alt = which_op_alt ();
  for (opno = 0; opno < recog_data.n_operands; opno++)
    {
      /* Things we need to fix can only occur in inputs.  */
      if (recog_data.operand_type[opno] != OP_IN)
        continue;

      /* If this alternative is a memory reference, then any mention
         of constants in this alternative is really to fool reload
         into allowing us to accept one there.  We need to fix them up
         now so that we output the right code.  */
      if (op_alt[opno].memory_ok)
        {
          rtx op = recog_data.operand[opno];

          if (CONSTANT_P (op))
            {
              if (do_pushes)
                push_csky_minipool_fix (insn, address,
                                        recog_data.operand_loc[opno],
                                        recog_data.operand_mode[opno], op);
              result = true;
            }
        }
    }

  return result;
}


/* Add a constant to the minipool for a forward reference.  Returns the
   node added or NULL if the constant will not fit in this pool.  */

static Mnode *
add_csky_minipool_forward_ref (Mfix *fix)
{
  /* If set, max_mp is the first pool_entry that has a lower
     constraint than the one we are trying to add.  */
  Mnode *       max_mp = NULL;
  HOST_WIDE_INT max_address = fix->address + fix->forwards;
  Mnode *       mp;

  /* If the minipool starts before the end of FIX->INSN then this FIX
     can not be placed into the current pool.  Furthermore, adding the
     new constant pool entry may cause the pool to start FIX_SIZE bytes
     earlier.  */
  if (minipool_vector_head
      && (fix->address + get_attr_length (fix->insn)
          >= minipool_vector_head->max_address - fix->fix_size))
    return NULL;

  /* Scan the pool to see if a constant with the same value has
     already been added.  While we are doing this, also note the
     location where we must insert the constant if it doesn't already
     exist.  */
  for (mp = minipool_vector_head; mp != NULL; mp = mp->next)
    {
      if (GET_CODE (fix->value) == GET_CODE (mp->value)
          && fix->mode == mp->mode
          && (GET_CODE (fix->value) != CODE_LABEL
              || (CODE_LABEL_NUMBER (fix->value)
                  == CODE_LABEL_NUMBER (mp->value)))
          && rtx_equal_p (fix->value, mp->value))
        {
          /* More than one fix references this entry.  */
          mp->refcount++;
          return mp;
        }

      /* Note the insertion point if necessary.  */
      if (max_mp == NULL && mp->max_address > max_address)
        max_mp = mp;
    }

  /* The value is not currently in the minipool, so we need to create
     a new entry for it.  If MAX_MP is NULL, the entry will be put on
     the end of the list since the placement is less constrained than
     any existing entry.  Otherwise, we insert the new fix before
     MAX_MP and, if necessary, adjust the constraints on the other
     entries.  */
  mp = XNEW (Mnode);
  mp->fix_size = fix->fix_size;
  mp->mode = fix->mode;
  mp->value = fix->value;
  mp->refcount = 1;
  /* Not yet required for a backwards ref.  */
  mp->min_address = -65536;

  if (max_mp == NULL)
    {
      mp->max_address = max_address;
      mp->next = NULL;
      mp->prev = minipool_vector_tail;

      if (mp->prev == NULL)
        {
          minipool_vector_head = mp;
          minipool_vector_label = gen_csky_constpool_label(
            gen_rtx_CONST_INT(VOIDmode, constpool_label_no++));
        }
      else
        mp->prev->next = mp;

      minipool_vector_tail = mp;
    }
  else
    {
      if (max_address > max_mp->max_address - mp->fix_size)
        mp->max_address = max_mp->max_address - mp->fix_size;
      else
        mp->max_address = max_address;

      mp->next = max_mp;
      mp->prev = max_mp->prev;
      max_mp->prev = mp;
      if (mp->prev != NULL)
        mp->prev->next = mp;
      else
        minipool_vector_head = mp;
    }

  /* Save the new entry.  */
  max_mp = mp;

  /* Scan over the preceding entries and adjust their addresses as
     required.  */
  while (mp->prev != NULL
         && mp->prev->max_address > mp->max_address - mp->prev->fix_size)
    {
      mp->prev->max_address = mp->max_address - mp->prev->fix_size;
      mp = mp->prev;
    }

  return max_mp;
}


/* Return the cost of forcibly inserting a barrier after INSN.  */

static int
get_csky_barrier_cost (rtx_insn *insn)
{
  /* Basing the location of the pool on the loop depth is preferable,
     but at the moment, the basic block information seems to be
     corrupt by this stage of the compilation.  */
  int base_cost = 50;
  rtx next = next_nonnote_insn (insn);

  if (next != NULL && GET_CODE (next) == CODE_LABEL)
    base_cost -= 20;

  switch (GET_CODE (insn))
    {
    case CODE_LABEL:
      /* It will always be better to place the table before the label, rather
     than after it.  */
      return 50;

    case INSN:
    case CALL_INSN:
      return base_cost;

    case JUMP_INSN:
      return base_cost - 10;

    default:
      return base_cost + 10;
    }
}


/* Find the best place in the insn stream in the range
   (FIX->address,MAX_ADDRESS) to forcibly insert a minipool barrier.
   Create the barrier by inserting a jump and add a new fix entry for
   it.  */
static Mfix *
create_csky_fix_barrier (Mfix *fix, Mfix *fix_next,
                         HOST_WIDE_INT max_address)
{
  rtx_barrier *barrier;
  rtx_insn *from;
  if (fix)
    from = fix->insn;
  else
    from = get_insns();
  /* The instruction after which we will insert the jump.  */
  rtx_insn *selected = NULL;
  int selected_cost;
  /* The address at which the jump instruction will be placed.  */
  HOST_WIDE_INT selected_address;
  Mfix * new_fix;
  HOST_WIDE_INT count = 0;
  if (fix)
    count = fix->address;
  HOST_WIDE_INT max_count = max_address;
  rtx label = gen_label_rtx ();

  selected_cost = get_csky_barrier_cost (from);

  while (from && count < max_count)
    {
      int new_cost;
      rtx_jump_table_data *table;

      /* Count the length of this insn.  */
      count += get_attr_length (from);

      /* If there is a jump table, add its length.  */
      if (tablejump_p (from, NULL, &table))
        {
          count += get_csky_jump_table_size (table);

          /* Jump tables aren't in a basic block, so base the cost on
             the dispatch insn.  If we select this location, we will
             still put the pool after the table.  */
          new_cost = get_csky_barrier_cost (from);

          if (count < max_count
              && (!selected || new_cost <= selected_cost))
            {
              selected = table;
              selected_cost = new_cost;
              selected_address = count;
            }

          /* Continue after the dispatch table.  */
          from = NEXT_INSN (table);
          continue;
        }

      new_cost = get_csky_barrier_cost (from);

      if (count < max_count
          && (!selected || new_cost <= selected_cost))
        {
          selected = from;
          selected_cost = new_cost;
          selected_address = count;
        }

      from = NEXT_INSN (from);
    }

  /* Make sure that we found a place to insert the jump.  */
  gcc_assert (selected);

  /* Make sure we do not split a call and its corresponding
     CALL_ARG_LOCATION note.  */
  if (CALL_P (selected))
    {
      rtx_insn *next = NEXT_INSN (selected);
      if (next && NOTE_P (next)
          && NOTE_KIND (next) == NOTE_INSN_CALL_ARG_LOCATION)
        selected = next;
    }

  /* Create a new JUMP_INSN that branches around a barrier.  */
  from = emit_jump_insn_after (gen_jump (label), selected);
  JUMP_LABEL (from) = label;
  barrier = emit_barrier_after (from);
  emit_label_after (label, barrier);

  /* Create a minipool barrier entry for the new barrier.  */
  new_fix = (Mfix *) obstack_alloc (&minipool_obstack, sizeof (* new_fix));
  new_fix->insn = barrier;
  new_fix->address = selected_address;
  if (fix)
    {
      new_fix->next = fix->next;
      fix->next = new_fix;
    }
  else
    new_fix->next = fix_next;

  return new_fix;
}


/* Print a symbolic form of X to the debug file, F.  */

static void
print_csky_value (FILE *f, rtx x)
{
  switch (GET_CODE (x))
    {
    case CONST_INT:
      fprintf (f, HOST_WIDE_INT_PRINT_HEX, INTVAL (x));
      return;

    case CONST_DOUBLE:
      fprintf (f, "<0x%lx,0x%lx>", (long)XWINT (x, 2), (long)XWINT (x, 3));
      return;

    case CONST_VECTOR:
      {
        int i;

        fprintf (f, "<");
        for (i = 0; i < CONST_VECTOR_NUNITS (x); i++)
          {
            fprintf (f, HOST_WIDE_INT_PRINT_HEX,
                     INTVAL (CONST_VECTOR_ELT (x, i)));
            if (i < (CONST_VECTOR_NUNITS (x) - 1))
              fputc (',', f);
          }
        fprintf (f, ">");
      }
      return;

    case CONST_STRING:
      fprintf (f, "\"%s\"", XSTR (x, 0));
      return;

    case SYMBOL_REF:
      fprintf (f, "`%s'", XSTR (x, 0));
      return;

    case LABEL_REF:
      fprintf (f, "L%d", INSN_UID (XEXP (x, 0)));
      return;

    case CONST:
      print_csky_value (f, XEXP (x, 0));
      return;

    case PLUS:
      print_csky_value (f, XEXP (x, 0));
      fprintf (f, "+");
      print_csky_value (f, XEXP (x, 1));
      return;

    case PC:
      fprintf (f, "pc");
      return;

    default:
      fprintf (f, "????");
      return;
    }
}


/* Record INSN, which will need fixing up to load a value from the
   minipool.  ADDRESS is the offset of the insn since the start of the
   function; LOC is a pointer to the part of the insn which requires
   fixing; VALUE is the constant that must be loaded, which is of type
   MODE.  */

static void
push_csky_minipool_fix (rtx_insn *insn, HOST_WIDE_INT address, rtx *loc,
                        machine_mode mode, rtx value)
{
  #define CSKY_ELRW16_RANGE  1400
  #define CSKY_LRW16_RANGE   700
  #define CSKY_CONSTANT_POOL_RANGE (TARGET_ELRW ? CSKY_ELRW16_RANGE \
                                                : CSKY_LRW16_RANGE)

  /* Fixes less than a word need padding out to a word boundary.  */
  #define CSKY_MINIPOOL_FIX_SIZE(mode) \
    (GET_MODE_SIZE ((mode)) >= 4 ? GET_MODE_SIZE ((mode)) : 4)

  Mfix * fix = (Mfix *) obstack_alloc (&minipool_obstack, sizeof (* fix));

  fix->insn = insn;
  fix->address = address;
  fix->loc = loc;
  fix->mode = mode;
  fix->fix_size = CSKY_MINIPOOL_FIX_SIZE (mode);
  fix->value = value;
  fix->forwards = CSKY_CONSTANT_POOL_RANGE;
  fix->backwards = 0;
  fix->minipool = NULL;

  /* If an insn doesn't have a range defined for it, then it isn't
     expecting to be reworked by this code.  Better to stop now than
     to generate duff assembly code.  */
  gcc_assert (fix->forwards || fix->backwards);

  if (dump_file)
    {
      fprintf (dump_file,
               ";; %smode fixup for i%d; addr %lu, range (%ld,%ld): ",
               GET_MODE_NAME (mode),
               INSN_UID (insn), (unsigned long) address,
               -1 * (long)fix->backwards, (long)fix->forwards);
      print_csky_value (dump_file, fix->value);
      fprintf (dump_file, "\n");
    }

  /* Add it to the chain of fixes.  */
  fix->next = NULL;

  if (minipool_fix_head != NULL)
    minipool_fix_tail->next = fix;
  else
    minipool_fix_head = fix;

  minipool_fix_tail = fix;
}


static void
assign_csky_minipool_offsets (Mfix *barrier)
{
  HOST_WIDE_INT offset = 0;
  Mnode *mp;

  minipool_barrier = barrier;

  for (mp = minipool_vector_head; mp != NULL; mp = mp->next)
    {
      mp->offset = offset;

      if (mp->refcount > 0)
        offset += mp->fix_size;
    }
}


/* Output the literal table.  */

static HOST_WIDE_INT
dump_csky_minipool (rtx_insn *scan)
{
  Mnode * mp;
  Mnode * nmp;
  HOST_WIDE_INT pool_length = 0;

  if (dump_file)
    fprintf (dump_file,
             ";; Emitting minipool after insn %u;\
              address %ld; align %d (bytes)\n",
             INSN_UID (scan), (unsigned long) minipool_barrier->address, 4);

  scan = emit_insn_after (gen_align_4 (), scan);
  scan = emit_insn_after (minipool_vector_label, scan);

  for (mp = minipool_vector_head; mp != NULL; mp = nmp)
    {
      if (mp->refcount > 0)
        {
          if (dump_file)
            {
              fprintf (dump_file, ";;  Offset %u, min %ld, max %ld ",
                       (unsigned) mp->offset, (unsigned long) mp->min_address,
                       (unsigned long) mp->max_address);
              print_csky_value (dump_file, mp->value);
              fputc ('\n', dump_file);
            }

          switch (mp->fix_size)
            {
#ifdef HAVE_consttable_4
            case 4:
              scan = emit_insn_after (gen_consttable_4 (mp->value), scan);
              pool_length += 4;
              break;
#endif
#ifdef HAVE_consttable_8
            case 8:
              scan = emit_insn_after (gen_consttable_8 (mp->value), scan);
              pool_length += 8;
              break;
#endif
            default:
              gcc_unreachable ();
            }
        }

      nmp = mp->next;
      free (mp);
    }

  minipool_vector_head = minipool_vector_tail = NULL;
  scan = emit_barrier_after (scan);

  return pool_length;
}


static void
adjust_csky_minipool_address(HOST_WIDE_INT func_size)
{
  Mnode * mp;
  for (mp = minipool_vector_head; mp; mp = mp->next)
    mp->max_address -= func_size;

  return;
}


/* Compute the attribute "length" of push or pop insn, according to
   the registers it used.  */

int
get_csky_pushpop_length (rtx *operands)
{
  rtx parallel_op = operands[2];
  /* Initialize to elements number of PARALLEL.  */
  unsigned indx = XVECLEN (parallel_op, 0) - 1;
  unsigned first_indx = 0;
  unsigned regno = REGNO (operands[1]);

  if (regno > CSKY_LR_REGNUM)
    return 4;

  /* Check each register in the list.  */
  for (; indx > first_indx; indx--)
    {
      regno = REGNO (XEXP (XVECEXP (parallel_op, 0, indx), 0));
      /* For the registers to push or pop, if it has the register
         number large than 15, it will emit 32bits insn.  */
      if (regno > CSKY_LR_REGNUM)
        return 4;
    }

  return 2;
}

static void
csky_reorg (void)
{
  /* Restore the warn_return_type if it has been altered. */
  /* TODO it is related to naked attribute.  */
#if 0
  if (saved_warn_return_type != -1)
    {
      if (--saved_warn_return_type_count == 0)
        {
          warn_return_type =saved_warn_return_type;
          saved_warn_return_type = -1;
        }
    }
#endif

    /* TODO */
    if (!(CSKY_TARGET_ARCH(CK802)
          || CSKY_TARGET_ARCH(CK801))
        || !TARGET_CONSTANT_POOL)
      return;

    /* The following algorithm dumps constant pool to the right point. */
    rtx_insn *insn;
    HOST_WIDE_INT address = 0;
    Mfix * fix;

    minipool_fix_head = minipool_fix_tail = NULL;

#ifdef TARGET_FUNCS_SHARE_CONSTANT_POOL
    int insn_prologue_len = 0;
    insn = get_insns ();
    for (insn = NEXT_INSN (insn); ; insn = NEXT_INSN (insn))
      {
        if (NOTE_P (insn) && NOTE_KIND (insn) == NOTE_INSN_PROLOGUE_END)
          break;
        if (INSN_P (insn))
          insn_prologue_len += get_attr_length (insn);
      }
#endif

    /* The first insn must always be a note, or the code below won't
       scan it properly.  */
    insn = get_insns ();
    gcc_assert (NOTE_P (insn));

    /* Scan the insns and record the operands that will need fixing.  */
    for (insn = next_nonnote_insn (insn); insn; insn = next_nonnote_insn (insn))
      {
        if (BARRIER_P (insn))
          push_csky_minipool_barrier (insn, address);
        else if (INSN_P (insn))
          {
            rtx_jump_table_data *table;

            note_csky_invalid_constants (insn, address, true);
            address += get_attr_length (insn);

            /* If the insn is a vector jump, add the size of the table
             and skip the table.  */
            if (tablejump_p (insn, NULL, &table))
              {
                address += get_csky_jump_table_size (table);
                insn = table;
              }
          }
      }

    fix = minipool_fix_head;

    /* Now scan the fixups and perform the required changes.  */
    while (fix)
      {
        Mfix * ftmp;
        Mfix * last_added_fix;
        Mfix * last_barrier = NULL;
        Mfix * this_fix;
        Mnode * mp;
        bool reach_end = false;
        bool has_pending_const = false;

        /* check if there is any pending constant not processd */
        for (mp = minipool_vector_head; mp; mp = mp->next)
          {
            if (mp->refcount > 0)
              {
                has_pending_const = true;
                break;
              }
          }

        /* if no pending constant, jump over barrier insn at the beginning */
        if (has_pending_const == false)
          {
            while (fix && BARRIER_P (fix->insn))
              fix = fix->next;
            if (fix == NULL)
              break;
          }

        last_added_fix = NULL;

        for (ftmp = fix; ftmp; ftmp = ftmp->next)
          {
            if (BARRIER_P (ftmp->insn))
              {
                if (minipool_vector_head
                    && ftmp->address >= minipool_vector_head->max_address)
                  break;

                last_barrier = ftmp;
              }
            else if ((ftmp->minipool = add_csky_minipool_forward_ref (ftmp)) == NULL)
              break;

            last_added_fix = ftmp;  /* Keep track of the last fix added.  */
          }

        if (ftmp == NULL) reach_end = true;

        /* If the last added fix is a barrier, dump minipool after it.  */
        if (last_added_fix && BARRIER_P (last_added_fix->insn))
          {
            ftmp = last_barrier;
          }
        else
          {
            /* ftmp is first fix that we can't fit into this pool.
               Insert a new barrier in the code somewhere between the previous
               fix and this one, and arrange to jump around it.  */
            HOST_WIDE_INT max_address;

            /* The last item on the list of fixes must be a barrier, so
               we can never run off the end of the list of fixes without
               last_barrier being set.  */
            gcc_assert (ftmp);

            max_address = minipool_vector_head->max_address;
            /* Check that there isn't another fix that is in range that
               we couldn't fit into this pool because the pool was
               already too large: we need to put the pool before such an
               instruction.  The pool itself may come just after the
               fix because create_csky_fix_barrier also allows space for a
               jump instruction.  */
            if (ftmp->address < max_address)
              max_address = ftmp->address + 1;
            last_barrier = create_csky_fix_barrier (last_added_fix, ftmp,
                                                    max_address);
          }

        assign_csky_minipool_offsets (last_barrier);

        /* Scan over the fixes we have identified for this pool, fixing them
           up and adding the constants to the pool itself.  */
        for (this_fix = fix; this_fix && ftmp != this_fix;
             this_fix = this_fix->next)
          {
            if (GET_CODE (this_fix->insn) != BARRIER)
              {
                rtx addr = plus_constant (Pmode,
                        gen_rtx_LABEL_REF (VOIDmode, minipool_vector_label),
                        this_fix->minipool->offset);
                rtx insn_body = PATTERN (this_fix->insn);
                rtx src = XEXP(insn_body, 1);
                *this_fix->loc = gen_rtx_MEM (this_fix->mode, addr);
                if (GET_CODE(this_fix->value) == SYMBOL_REF)
                  {
                    emit_insn_after (gen_rtx_UNSPEC_VOLATILE (VOIDmode,
                                     gen_rtvec (1, src),
                                     VUNSPEC_SYMBOL_REF),
                                     this_fix->insn);
                  }
              }
          }

        /* TODO csky_will_change_section and csky_is_last_func should be added to
           cgraphunit.c file. Try to find a solution don't edit gcc file.*/
#ifdef TARGET_FUNCS_SHARE_CONSTANT_POOL
        if (TARGET_FUNCS_SHARE_CONSTANT_POOL)
          {
            extern bool csky_is_last_func;
            extern bool csky_will_change_section;

            /* if the current insn list is the last part of internal function, only
             * need to modify the address constraint; Otherwise, dump the minipool. */
            if (!minipool_vector_head)
              {
              }
            else if (reach_end == true
                    && minipool_vector_head->max_address <= (last_barrier->address
                                                             + insn_prologue_len))
              {
                dump_csky_minipool (last_barrier->insn);
              }
            else if (reach_end == true && csky_will_change_section == true)
              {
                dump_csky_minipool (last_barrier->insn);
              }
            else if (reach_end == true && csky_is_last_func == true)
              {
                dump_csky_minipool (last_barrier->insn);
              }
            else if (reach_end == false)
              {
                HOST_WIDE_INT pool_len;
                pool_len = dump_csky_minipool (last_barrier->insn);
                /* the branch instruction "br .L" inserted.  */
                address += pool_len + 4;

                for (this_fix = ftmp; this_fix; this_fix = this_fix->next)
                  this_fix->address += pool_len + 4;
              }
            else
              {
                adjust_csky_minipool_address(address);
              }
          }
        else
          dump_csky_minipool (last_barrier->insn);
#else
        dump_csky_minipool (last_barrier->insn);
#endif
        fix = ftmp;
        if (fix->next == NULL)
          break;
      }

    /* Free the minipool memory.  */
    obstack_free (&minipool_obstack, minipool_startobj);
}

static bool
insn_far_jump_used_p(void)
{
  rtx_insn *insn;
  if (cfun->machine->far_jump_used)
    return true;

  /* If this function is not being called from the prologue/epilogue
     generation code then it must be being called from the
     INITIAL_ELIMINATION_OFFSET macro.  */
  if (!reload_completed)
    {
      /* In this case we know that we are being asked about the elimination
         of the arg pointer register.  If that register is not being used,
         then there are no arguments on the stack, and we do not have to
         worry that a far jump might force the prologue to push the link
         register, changing the stack offsets.  In this case we can just
         return false, since the presence of far jumps in the function will
         not affect stack offsets.

         If the arg pointer is live (or if it was live, but has now been
         eliminated and so set to dead) then we do have to test to see if
         the function might contain a far jump.  This test can lead to some
         false negatives, since before reload is completed, then length of
         branch instructions is not known, so gcc defaults to returning their
         longest length, which in turn sets the far jump attribute to true.

         A false negative will not result in bad code being generated, but it
         will result in a needless push and pop of the link register.  We
         hope that this does not occur too often.  */
      if (df_regs_ever_live_p (ARG_POINTER_REGNUM))
        cfun->machine->arg_pointer_live = 1;
      else if (!cfun->machine->arg_pointer_live)
        return 0;
    }

  /* We should not change far_jump_used during or after reload, as there is
     no chance to change stack frame layout.  */
  if (reload_in_progress || reload_completed)
    return 0;

  /* Check to see if the function contains a branch
     insn with the far jump attribute set.  */
  for (insn = get_insns (); insn; insn = NEXT_INSN (insn))
    {
      if (GET_CODE (insn) == JUMP_INSN
          /* Ignore tablejump patterns.  */
          && GET_CODE (PATTERN (insn)) != ADDR_VEC
          && GET_CODE (PATTERN (insn)) != ADDR_DIFF_VEC
          && get_attr_far_jump (insn) == FAR_JUMP_YES)
        {
          cfun->machine->far_jump_used = 1;
          return true;
        }
    }
  return false;
}

static bool
csky_force_lr_save(void)
{
  return (!leaf_function_p() || insn_far_jump_used_p());
}

/* The COUNT will be set as the living general register number,
   The FRCOUNT will be set as the living float register number.  */

static int
get_csky_live_regs (int *count, int *frcount, int *freg_mask)
{
  int reg;
  int live_regs_mask = 0, live_fregs_mask = 0;
  *count = 0;
  *frcount = 0;

  /* FIXME: we should set live regs in one please
     and use interface of gcc to detect all readlly used regs ?  */
  if (frame_pointer_needed)
    {
      (*count)++;
      live_regs_mask |= (1 << HARD_FRAME_POINTER_REGNUM);
    }

  /* use bsr insn instead of long jump insn in some arches
     which do not have that.  */
  if ((CSKY_TARGET_ARCH (CK801) || CSKY_TARGET_ARCH (CK802))
      && csky_force_lr_save())
    {
      (*count)++;
      live_regs_mask |= (1 << CSKY_LR_REGNUM);
    }

  for (reg = 0; reg < CSKY_NGPR_REGS; reg++)
    {
      if (df_regs_ever_live_p (reg) && !call_really_used_regs[reg]
          && !(live_regs_mask & (1 << reg)))
        {
          (*count)++;
          live_regs_mask |= (1 << reg);
        }
    }

  if (crtl->calls_eh_return)
    {
      unsigned int i;
      for (i = 0; EH_RETURN_DATA_REGNO (i) != INVALID_REGNUM; i++)
        {
          if(0 == (live_regs_mask & (1 << EH_RETURN_DATA_REGNO (i))))
            (*count)++;

          live_regs_mask |= (1 << EH_RETURN_DATA_REGNO (i));
        }
    }

  if (TARGET_SUPPORT_VREGS)
    {
      for (reg = CSKY_FIRST_VFP_REGNUM; reg <= CSKY_LAST_VFP_REGNUM; reg++)
        {
          if (df_regs_ever_live_p (reg) && !call_really_used_regs[reg]
              && !(live_fregs_mask & (1 << (reg - CSKY_FIRST_VFP_REGNUM))))
            {
              (*frcount)++;
              live_fregs_mask |= (1 << (reg - CSKY_FIRST_VFP_REGNUM));
            }
        }
    }
  *freg_mask = live_fregs_mask;

  return live_regs_mask;
}


static void
get_csky_frame_layout (csky_stack_frame *infp)
{
  int arg_size, reg_size, local_size, outbound_size, freg_size;
  int pad_arg, pad_reg, pad_local, pad_outbound;
  int spill_size; /* the size of args we need to spill ourselves */
  int reg_mask, reg_count, freg_count;
  int freg_mask;
  int mod = 0;

  memset(infp, 0, sizeof(*infp));

  spill_size = 0;
  if (cfun->machine->uses_anonymous_args && crtl->args.pretend_args_size == 0)
    spill_size = (CSKY_NPARM_REGS
                  - cfun->machine->number_of_regs_before_varargs)
                 * UNITS_PER_WORD;

  arg_size = spill_size ? spill_size : crtl->args.pretend_args_size;
  mod = arg_size % CSKY_STACK_BOUNDARY_BYTES;
  pad_arg = mod ? (CSKY_STACK_BOUNDARY_BYTES - mod) : 0;

  local_size = get_frame_size();
  mod = local_size % CSKY_STACK_BOUNDARY_BYTES;
  pad_local = mod ? (CSKY_STACK_BOUNDARY_BYTES - mod) : 0;

  outbound_size = crtl->outgoing_args_size;
  mod = outbound_size % CSKY_STACK_BOUNDARY_BYTES;
  pad_outbound = mod ? (CSKY_STACK_BOUNDARY_BYTES - mod) : 0;

  if ((local_size + pad_local + outbound_size + pad_outbound)
      > (CSKY_ADDI_MAX_STEP * 2))
    df_set_regs_ever_live(4, true); /* need r4 as tmp reg for adjust sp */

  reg_mask = get_csky_live_regs (&reg_count, &freg_count, &freg_mask);
  freg_size = freg_count * (CSKY_ISA_FEATURE(vdsp128) ? 16 :
    (csky_fpu_index == TARGET_FPU_fpv2_sf ? 4 : 8));
  reg_size = reg_count * 4 + freg_size;

  mod = reg_size % CSKY_STACK_BOUNDARY_BYTES;
  pad_reg = mod ? (CSKY_STACK_BOUNDARY_BYTES - mod) : 0;

  infp->arg_size = arg_size;
  infp->reg_size = reg_size;
  infp->freg_size = freg_size;
  infp->reg_mask = reg_mask;
  infp->freg_mask = freg_mask;
  infp->local_size = local_size;
  infp->outbound_size = outbound_size;
}


/* Define the offset between two registers, one to be eliminated, and
   the other its replacement, at the start of a routine.  */
HOST_WIDE_INT
csky_initial_elimination_offset (int from, int to)
{
  int ap2fp_offset;
  int fp2sp_offset;
  csky_stack_frame fi;

  get_csky_frame_layout (&fi);

  ap2fp_offset = fi.reg_size + fi.pad_reg + fi.pad_arg;

  fp2sp_offset = fi.local_size + fi.pad_local
                 + fi.outbound_size + fi.pad_outbound;

  if (from == ARG_POINTER_REGNUM && to == FRAME_POINTER_REGNUM)
    return ap2fp_offset;

  if (from == ARG_POINTER_REGNUM && to == HARD_FRAME_POINTER_REGNUM)
      return ap2fp_offset;

  if (from == ARG_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    return ap2fp_offset + fp2sp_offset;

  if (from == FRAME_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    return fp2sp_offset;

  if (from == FRAME_POINTER_REGNUM && to == HARD_FRAME_POINTER_REGNUM)
      return 0;

  gcc_unreachable ();
}

/* Given FROM and TO register numbers, say whether this elimination is
   allowed.  Frame pointer elimination is automatically handled.

   All eliminations are permissible.  Note that ARG_POINTER_REGNUM and
   HARD_FRAME_POINTER_REGNUM are in fact the same thing.  If we need a frame
   pointer, we must eliminate FRAME_POINTER_REGNUM into
   HARD_FRAME_POINTER_REGNUM and not into STACK_POINTER_REGNUM or
   ARG_POINTER_REGNUM.

   Added by JianPing Zeng on 2018/1/5 copied from abiv1_csky.  */

bool
csky_can_eliminate (const int from, const int to)
{
  return ((to == FRAME_POINTER_REGNUM
           && from == ARG_POINTER_REGNUM) ? false : (to ==
                                                     STACK_POINTER_REGNUM
                                                     &&
                                                     frame_pointer_needed) ?
          false : true);
}

/* Determine where to put an argument to a function.
   Value is zero to push the argument on the stack,
   or a hard register in which to store the argument.

   MODE is the argument's machine mode.
   TYPE is the data type of the argument (as a tree).
    This is null for libcalls where that information may
    not be available.
   CUM is a variable of type CUMULATIVE_ARGS which gives info about
    the preceding args and about the function being called.
   NAMED is nonzero if this argument is a named parameter
    (otherwise it is an extra parameter matching an ellipsis).  */
static rtx
csky_function_arg (cumulative_args_t pcum_v, machine_mode mode,
                   const_tree type, bool named)
{
  CUMULATIVE_ARGS *pcum = get_cumulative_args (pcum_v);
  int arg_reg = pcum->reg;

  if (!named || mode == VOIDmode)
    return NULL_RTX;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return NULL_RTX;

  if (TARGET_HARD_FLOAT_ABI
      && (mode == SFmode || mode == DFmode
          || (CSKY_ISA_FEATURE(vdsp)
              && csky_vector_mode_supported_p(mode)))
      && !pcum->is_stdarg
      && !(mode == DFmode && csky_fpu_index == TARGET_FPU_fpv2_sf))
    {
      int arg_reg = pcum->freg;
      if (!IN_RANGE (arg_reg, 0, 3))
        return NULL_RTX;

      return gen_rtx_REG (mode, arg_reg + CSKY_FIRST_VFP_REGNUM);
    }

  if (arg_reg < CSKY_NPARM_REGS)
    return gen_rtx_REG (mode, CSKY_FIRST_PARM_REG + arg_reg);

  return NULL_RTX;
}


static int
get_csky_arg_regs_num (enum machine_mode mode, const_tree type, bool is_stdarg)
{
  int size;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return 0;

  if (type && mode == BLKmode)
    size = int_size_in_bytes (type);
  else
    size = GET_MODE_SIZE (mode);

  if (TARGET_HARD_FLOAT_ABI
      && !is_stdarg)
    {
      if (CSKY_ISA_FEATURE(vdsp128)
          && csky_vector_mode_supported_p(mode))
        return ((CSKY_NUM_WORDS (size) + 3) / 4);
      else if ((mode == SFmode || mode == DFmode)
               && csky_fpu_index != TARGET_FPU_fpv2_sf)
        return ((CSKY_NUM_WORDS (size) + 1) / 2);
      else
        return CSKY_NUM_WORDS (size);
    }
  else
    return CSKY_NUM_WORDS (size);
}


/* Update the data in PCUM to advance over an argument
   of mode MODE and data type TYPE.
   (TYPE is null for libcalls where that information may not be available.)  */
static void
csky_function_arg_advance (cumulative_args_t pcum_v, machine_mode mode,
                           const_tree type, bool named)
{
  CUMULATIVE_ARGS *pcum = get_cumulative_args (pcum_v);
  int *reg = &pcum->reg;

  if (TARGET_HARD_FLOAT_ABI
      && (mode == SFmode || mode == DFmode
          || (CSKY_ISA_FEATURE(vdsp)
              && csky_vector_mode_supported_p(mode)))
      && !pcum->is_stdarg
      && !(mode == DFmode && csky_fpu_index == TARGET_FPU_fpv2_sf))
    {
      int *reg = &pcum->freg;
      *reg = *reg + named * get_csky_arg_regs_num(mode, type, pcum->is_stdarg);
      return;
    }
  *reg = *reg + named * get_csky_arg_regs_num(mode, type, pcum->is_stdarg);
}


static unsigned int
csky_function_arg_boundary (machine_mode mode ATTRIBUTE_UNUSED,
                            const_tree type ATTRIBUTE_UNUSED)
{
  return PARM_BOUNDARY;
}


/* Define how to find the value returned by a function.  */
static rtx
csky_function_value(const_tree type, const_tree func,
       bool outgoing ATTRIBUTE_UNUSED)
{
  machine_mode mode;
  int unsignedp ATTRIBUTE_UNUSED;
  int size;

  mode = TYPE_MODE (type);
  size = int_size_in_bytes (type);

  if (TARGET_HARD_FLOAT_ABI
      && (mode == SFmode || mode == DFmode
          || (CSKY_ISA_FEATURE(vdsp)
              && csky_vector_mode_supported_p(mode)))
      && !(mode == DFmode && csky_fpu_index == TARGET_FPU_fpv2_sf))
    {
      mode = promote_function_mode (type, mode, &unsignedp, func, 1);
      return gen_rtx_REG (mode, CSKY_FIRST_VFP_REGNUM);
    }

  /* Since we promote return types, we must promote the mode here too.  */
  if (INTEGRAL_TYPE_P (type))
    {
      mode = promote_function_mode (type, mode, &unsignedp, func, 1);
      return gen_rtx_REG (mode, CSKY_FIRST_RET_REG);
    }

  if (mode == BLKmode && size > UNITS_PER_WORD
      && size <= UNITS_PER_WORD * 2)
    {
      rtx ret_regs[2];
      ret_regs[0] = gen_rtx_EXPR_LIST (SImode,
                                       gen_rtx_REG (SImode,
                                                    CSKY_FIRST_RET_REG),
                                       GEN_INT (0 * UNITS_PER_WORD));
      ret_regs[1] = gen_rtx_EXPR_LIST (SImode,
                                       gen_rtx_REG (SImode,
                                                    CSKY_FIRST_RET_REG + 1),
                                       GEN_INT (1 * UNITS_PER_WORD));

      rtvec vec = gen_rtvec (2, ret_regs[0], ret_regs[1]);

      return gen_rtx_PARALLEL (mode, vec);
    }

    return gen_rtx_REG (mode, CSKY_FIRST_RET_REG);
}


/* Define how to find the value returned by a library function
   assuming the value has mode MODE.  */
static rtx
csky_libcall_value (machine_mode mode,
                    const_rtx libcall ATTRIBUTE_UNUSED)
{
  if (TARGET_HARD_FLOAT_ABI
      && (mode == SFmode || mode == DFmode
          || (CSKY_ISA_FEATURE(vdsp)
              && csky_vector_mode_supported_p(mode)))
      && !(mode == DFmode && csky_fpu_index == TARGET_FPU_fpv2_sf))
    {
      return gen_rtx_REG (mode, CSKY_FIRST_VFP_REGNUM);
    }
  return gen_rtx_REG (mode, CSKY_FIRST_RET_REG);
}


/* 1 if N is a possible register number for a function value.
   On the CSKY, only r0 can return results.  */
static bool
csky_function_value_regno_p (const unsigned int regno)
{
  if (regno == CSKY_FIRST_RET_REG
      || (TARGET_HARD_FLOAT_ABI
          && regno == CSKY_FIRST_VFP_REGNUM))
    return true;
  return false;
}


/* Return an RTX indicating where the return address to the
   calling function can be found.  */
rtx
csky_return_addr (int count, rtx frame ATTRIBUTE_UNUSED)
{
  if (count != 0)
    return NULL_RTX;

  return get_hard_reg_initial_val (Pmode, CSKY_LR_REGNUM);
}


/* return the number of bytes at the beginning of an argument
   that must be put in registers. The value must be zero for arguments
   that are passed entirely in registers or
   that are entirely pushed on the stack.  */
static int
csky_arg_partial_bytes (cumulative_args_t pcum_v, enum machine_mode mode,
                        tree type, bool named)
{
  CUMULATIVE_ARGS *pcum = get_cumulative_args (pcum_v);

  int reg = pcum->reg;

  if (named == 0)
    return 0;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return 0;

  if (TARGET_HARD_FLOAT_ABI
      && (mode == SFmode || mode == DFmode
          || (CSKY_ISA_FEATURE(vdsp)
              && csky_vector_mode_supported_p(mode)))
      && !pcum->is_stdarg
      && !(mode == DFmode && csky_fpu_index == TARGET_FPU_fpv2_sf))
    {
      int reg = pcum->freg;

      if (!IN_RANGE (reg, 0, 3))
        return 0;

      int size = get_csky_arg_regs_num(mode, type, pcum->is_stdarg);

      if (reg + size <= CSKY_NPARM_FREGS)
        return 0;

      /* TODO: need to split param */
      return 0;
    }

  /* REG is not the *hardware* register number of the register that holds
     the argument, it is the *argument* register number.  So for example,
     the first argument to a function goes in argument register 0, which
     translates (for the cskyv1) into hardware register 2.  The second
     argument goes into argument register 1, which translates into hardware
     register 3, and so on.  */
  if (reg >= CSKY_NPARM_REGS)
    return 0;

  /* If the argument fits entirely in registers, return 0.  */
  int size = get_csky_arg_regs_num (mode, type, pcum->is_stdarg);
  if (reg + size <= CSKY_NPARM_REGS)
    return 0;

  /* The argument overflows the number of available argument registers.
     Compute how many argument registers have not yet been assigned to
     hold an argument.  */
  reg = CSKY_NPARM_REGS - reg;

  return reg * UNITS_PER_WORD;
}


/* Keep track of some information about varargs for the prolog.  */
static void
csky_setup_incoming_varargs (cumulative_args_t pcum_v,
                             machine_mode mode ATTRIBUTE_UNUSED,
                             tree type ATTRIBUTE_UNUSED,
                             int *pretend_size ATTRIBUTE_UNUSED,
                             int second_time ATTRIBUTE_UNUSED)
{
  CUMULATIVE_ARGS *pcum = get_cumulative_args (pcum_v);
  int reg = pcum->reg;

  cfun->machine->uses_anonymous_args = 1;

  /* FIXME: There is a bug somewhere in the arg handling code.
     Until we can find it this workaround always pushes the
     last named argument onto the stack.  */
  cfun->machine->number_of_regs_before_varargs = reg;

  /* The last named argument may be split between argument registers
     and the stack.  Allow for this here.  */
  if (cfun->machine->number_of_regs_before_varargs > CSKY_NPARM_REGS)
    cfun->machine->number_of_regs_before_varargs = CSKY_NPARM_REGS;
}


/* Output code to add DELTA to the first argument, and then jump
   to FUNCTION.  Used for C++ multiple inheritance.  */

static void
csky_output_mi_thunk (FILE *file, tree thunk ATTRIBUTE_UNUSED,
                      HOST_WIDE_INT delta,
                      HOST_WIDE_INT vcall_offset,
                      tree function)
{
  const char *thiz = "a0";
  const char *reg0 = "t0";
  const char *reg1 = "t1";

  final_start_function (emit_barrier (), file, 1);

  rtx fnaddr = XEXP (DECL_RTL (function), 0);

  if (CSKY_TARGET_ARCH (CK801))
    {
      reg0 = "l0";
      reg1 = "l1";
      if (vcall_offset > CSKY_ADDI_MAX_STEP
          || vcall_offset < -CSKY_ADDI_MAX_STEP)
        {
          fprintf (file, "\tpush l0, l1\n");
        }
      else
        {
          fprintf (file, "\tpush l0\n");
        }
    }

  if (aggregate_value_p (TREE_TYPE (TREE_TYPE (function)), function))
    thiz = "a1";

  /* Add delta to this_rtx.  */
  if (delta != 0)
    {
      if (delta > CSKY_ADDI_MAX_STEP || delta < -CSKY_ADDI_MAX_STEP)
        {
          fprintf(file, "\tlrw\t%s, %ld\n", reg0, delta);
          fprintf(file, "\taddu\t%s, %s, %s\n", thiz, thiz, reg0);
        }
      else
        {
          fprintf(file, "\t%s\t%s, %s, %ld\n",
                  (delta > 0 ? "addi" : "subi"), thiz,
                  thiz,
                  (delta > 0 ? delta : -delta));
        }
    }

  /* If needed, add *(*this_rtx + vcall_offset) to this_rtx.  */
  if (vcall_offset != 0)
    {
      fprintf(file, "\tld.w\t%s, (%s, 0)\n", reg0, thiz);

      if (vcall_offset > CSKY_ADDI_MAX_STEP
          || vcall_offset < -CSKY_ADDI_MAX_STEP)
        {
          fprintf(file, "\tlrw\t%s, %ld\n", reg1, vcall_offset);
          fprintf(file, "\taddu\t%s, %s, %s\n", reg0, reg0, reg1);
        }
      else
        {
          fprintf(file, "\t%s\t%s, %s, %ld\n",
                  (vcall_offset > 0 ? "addi" : "subi"), reg0,
                  reg0,
                  (vcall_offset > 0 ? vcall_offset : -vcall_offset));
        }

      /* Load the offset and add it to this_rtx  */
      fprintf(file, "\tld.w\t%s, (%s, 0)\n", reg0, reg0);
      fprintf(file, "\taddu\t%s, %s, %s\n", thiz, thiz, reg0);
    }

  if (CSKY_TARGET_ARCH (CK801))
    {
      if (vcall_offset > CSKY_ADDI_MAX_STEP || vcall_offset < -CSKY_ADDI_MAX_STEP)
        {
          fprintf (file, "\tpop l0, l1\n");
        }
      else
        {
          fprintf (file, "\tpop l0\n");
        }
    }

  fprintf(file, "\tjbr \t");
  output_addr_const(file, fnaddr);
  fprintf(file, "\n");

  final_end_function ();
}


/* Conditionally modify five variables fixed_regs, call_used_regs, global_regs,
   reg_names, and reg_class_contents, to take into account any dependence of
   these register sets on target flags.

   On csky, ck801 has registers r0-r7,r13,r14,r15.
   ck802 & ck803 has registers r0-r15.
   Other cpu has registers r0-r31 when -mhigh-registers, otherwise it has
   only r0-r15, ck803 default close this option, others default open.  */

static void
csky_conditional_register_usage (void)
{
  /* Only use mini registers in smart mode or 801.  */
  if (CSKY_ISA_FEATURE(smart) || CSKY_TARGET_ARCH(CK801))
    {
      int i;

      for (i = (CSKY_LAST_MINI_REGNUM + 1); i < 32; i++)
        {
          fixed_regs[i] = 1;
          call_used_regs[i] = 1;
          call_really_used_regs[i] = 1;
        }
        call_really_used_regs[CSKY_LR_REGNUM] = 0;
    }
  /* For some targets, the high regitser is not supported.
     Expect ck801 & ck802, other cpu use high registers
     depend on -mhigh-registers option(ck803 is default off,
     others are default on).  */
  else if (CSKY_TARGET_ARCH(CK802)
           || !CSKY_ISA_FEATURE(hreg))
   {
      int i;

      for (i = CSKY_FIRST_HIGH_REGNUM; i <= CSKY_LAST_HIGH_REGNUM; i++)
      {
        fixed_regs[i] = 1;
        call_used_regs[i] = 1;
        call_really_used_regs[i] = 1;
      }
   }


  /* The hi,lo register is only supported in dsp mode.  */
  if (!CSKY_ISA_FEATURE(dsp))
    {
      fixed_regs[CSKY_HI_REGNUM] = 1;
      call_used_regs[CSKY_HI_REGNUM] = 1;
      call_really_used_regs[CSKY_HI_REGNUM] = 1;

      fixed_regs[CSKY_LO_REGNUM] = 1;
      call_used_regs[CSKY_LO_REGNUM] = 1;
      call_really_used_regs[CSKY_LO_REGNUM] = 1;
    }

  /* The V_REGS is only suported on hard float mode.  */
  if (!TARGET_SUPPORT_VREGS)
    {
      int regno;

      for (regno = CSKY_FIRST_VFP_REGNUM;
           regno <= CSKY_LAST_VFP_REGNUM; regno++)
        {
          fixed_regs[regno] = 1;
          call_used_regs[regno] = 1;
          call_really_used_regs[regno] = 1;
        }
    }

  /* On the pic mode, the gb is not avilable for register
     allocator.  Since the gb is not clobbered by function
     call, set the call_really_used_regs to 0.  */
  if (flag_pic)
    {
      fixed_regs[PIC_OFFSET_TABLE_REGNUM] = 1;
      call_used_regs[PIC_OFFSET_TABLE_REGNUM] = 1;
      call_really_used_regs[PIC_OFFSET_TABLE_REGNUM] = 0;
    }
}


/* Return true if REGNO is a valid register for holding
   a quantity of type MODE.  */

int
csky_hard_regno_mode_ok (unsigned int regno, enum machine_mode mode)
{
  /* General register always return 1 if mode is one word size,
     when the size is larger than one word size, there should
     be enough successive two register to put the data.  */
  if (regno < CSKY_NGPR_REGS)
    {
      if (CSKY_NUM_REGS(mode) < 2)
        return 1;
      else
        {
          if (CSKY_ISA_FEATURE(smart) || CSKY_TARGET_ARCH(CK801))
            return (regno < CSKY_LAST_MINI_REGNUM);
          else if (CSKY_TARGET_ARCH(CK802)
                   || !CSKY_ISA_FEATURE(hreg))
            {
              /* Without high register, r15 cannot hold two word size data.  */
              return (regno < (CSKY_SP_REGNUM - 1));
            }
          else if (VECTOR_MODE_P (mode))
            {
              int word_num = GET_MODE_SIZE (mode) / 4;
              return ((regno < (CSKY_SP_REGNUM - word_num + 1))
                      || ((regno >= CSKY_LR_REGNUM)
                          && (regno <= (CSKY_LAST_HIGH_UNFIXED_REGNUM
                                        - word_num + 1))));
            }
          else
            return ((regno < (CSKY_SP_REGNUM - 1))
                    || ((regno >= CSKY_LR_REGNUM)
                        && (regno < CSKY_LAST_HIGH_UNFIXED_REGNUM)));
        }
    }
  else if (regno == CSKY_CC_REGNUM)
    {
      return (mode == CCmode);
    }
  else if (regno == CSKY_HI_REGNUM || regno == CSKY_LO_REGNUM)
    {
      /* Don't allocate hi,lo register for float data even
         if in dsp mode, because it will cause high cost
         to reload data from hi,lo register.  */
      if (!CSKY_ISA_FEATURE(dsp) || mode == SFmode || mode == DFmode)
        return 0;
      else if (CSKY_NUM_REGS(mode) == 2)
        return (regno == CSKY_HI_REGNUM);
      else
        return 1;
    }
  else if (CSKY_VREG_P (regno))
    {
      if (CSKY_ISA_FEATURE(vdsp)
          && csky_vector_mode_supported_p(mode))
        return 1;
      if (TARGET_HARD_FLOAT)
        {
          if (!TARGET_HARD_FLOAT_ABI)
            return 1;
          if (mode == SFmode || mode == SImode || mode == DFmode)
            return 1;
        }
    }

  return 0;
}


/* We need to define this for MINI_REGS when we only use r0 - r7.
   Otherwise we can end up using r0-r4 for function arguments,and don't
   have enough left over to do doubleword arithmetic.  */

static bool
csky_class_likely_spilled_p (reg_class_t rclass)
{
  if (((CSKY_ISA_FEATURE(smart) || CSKY_TARGET_ARCH(CK801))
       && rclass == MINI_REGS)
      || rclass == C_REGS)
    return true;

  return false;
}


/* Given an rtx X being reloaded into a reg required to be
   in class CLASS, return the class of reg to actually use.
   In general this is just CLASS.  */

static reg_class_t
csky_preferred_reload_class (rtx x ATTRIBUTE_UNUSED, reg_class_t rclass)
{
  if (TARGET_SUPPORT_VREGS)
    {
      if (CONST_DOUBLE_P (x)
          && (GET_MODE (x) == DFmode || GET_MODE (x) == SFmode)
          && rclass == NO_REGS)
        return GENERAL_REGS;
      if (MEM_P (x) && VECTOR_MODE_P(GET_MODE (x)))
        return V_REGS;
    }
  return rclass;
}


/* Return the maximum number of consecutive registers of class rclass needed
   to hold a value of mode mode.

   On the csky, this is the size of MODE in words,
   except in the FP regs, where a single reg is always enough.  */

static unsigned char
csky_class_max_nregs (reg_class_t rclass, machine_mode mode)
{
  if (rclass == V_REGS)
    return 1;
  else
    return CSKY_NUM_REGS (mode);
}


/*  For input reloads, this target hook is called with nonzero IN_P, and X is
    an rtx that needs to be copied to a register of class RCLASS in MODE
    reload mode. For output reloads, this target hook is called with zero IN_P,
    and a register of class RCLASS needs to be copied to rtx X in MODE reload
    mode.
    If copying a register of RCALSS from/to X requires an intermediate register,
    the hook should return the REGISTER_CLASS required for this intermediate register.
    If no intermediate register is required, it should return NO_REGS. If more than
    one intermediate register is required, describe the one that is closest in the
    copy chain to the reload register.  */

reg_class_t
csky_secondary_reload (bool in_p ATTRIBUTE_UNUSED, rtx x,
                       reg_class_t rclass,
                       enum machine_mode mode ATTRIBUTE_UNUSED,
                       secondary_reload_info * sri ATTRIBUTE_UNUSED)
{
  int regno = -1;

  if (GET_CODE (x) == SIGN_EXTEND)
    {
      int off = 0;

      x = XEXP (x, 0);

      if (reg_renumber)
        regno = true_regnum (x);
      else
        {
          while (GET_CODE (x) == SUBREG)
            {
              off += subreg_regno_offset (REGNO (SUBREG_REG (x)),
              GET_MODE (SUBREG_REG (x)),
              SUBREG_BYTE (x), GET_MODE (x));
              x = SUBREG_REG (x);
            }

            if (GET_CODE (x) == REG)
              regno = REGNO (x) + off;
        }
    }
  else if (GET_CODE (x) == REG || GET_CODE (x) == SUBREG)
    regno = true_regnum (x);

  /* We always require a general register when copying anything to
     HI/LO_REGNUM, except when copying an SImode value from HI/LO_REGNUM
     to a general register, or when copying from register 0.  */
  if ((rclass == HILO_REGS || rclass == LO_REGS || rclass == HI_REGS)
      && !CSKY_GENERAL_REGNO_P (regno))
    return GENERAL_REGS;

  if (rclass == V_REGS && CSKY_VREG_P (regno))
    {
      /* Reload between Vector reg and Memory do not need
         intermediate register.  */
      if (MEM_P (x) && (mode == SFmode || mode == DFmode))
        {
          if (GET_CODE (XEXP (x, 0)) == POST_INC)
            return GENERAL_REGS;
          else
            return NO_REGS;
        }
      else if (csky_vector_mode_supported_p (mode))
        return NO_REGS;
      else
        return GENERAL_REGS;
    }

  return NO_REGS;
}


/* Handler of common condition code set expression elimination pass.  */

static unsigned int
rest_of_handle_cse_cc (void)
{
  unsigned int cc_regno_1;
  unsigned int cc_regno_2;
  rtx cc_reg_1;
  rtx cc_reg_2 ATTRIBUTE_UNUSED;
  basic_block bb;

  /* Get the condition code register number and emit the codition
     code rtl expression.  */
  if (! targetm.fixed_condition_code_regs (&cc_regno_1, &cc_regno_2))
    return 0;

  cc_reg_1 = gen_rtx_REG (CCmode, cc_regno_1);
  if (cc_regno_2 != INVALID_REGNUM)
    cc_reg_2 = gen_rtx_REG (CCmode, cc_regno_2);
  else
    cc_reg_2 = NULL_RTX;

  /* Scan every basic block to pick all condition code set insns,
     if the source of condtion code set insns are same and continuous
     in one basic block, only keep the first insn.  */
  FOR_EACH_BB_FN (bb, cfun)
    {
      rtx_insn *last_insn;
      rtx_insn *insn;
      rtx cc_reg;

      if (dump_file)
        {
          fprintf (dump_file, "---Scan basic block %d ---\n",
                   bb->index);
        }
      last_insn = BB_END (bb);
      cc_reg = cc_reg_1;

      rtx_insn *cc_src_insn = NULL;
      /* Scan insn from bottom of basic block to the top.  */
      for (insn = PREV_INSN (last_insn);
           insn && insn != PREV_INSN (BB_HEAD (bb));
           insn = PREV_INSN (insn))
        {
          rtx cc_src;
          rtx set;
          rtx_insn *prev_insn = NULL;

          if (dump_file)
            {
              fprintf (dump_file, "Scan insn %d\n",
                       INSN_UID (insn));
            }
          if (! INSN_P (insn))
            continue;
          set = single_set (insn);
          if (set
              && REG_P (SET_DEST (set))
              && REGNO (SET_DEST (set)) == REGNO (cc_reg))
            {
              cc_src_insn = insn;
              cc_src = SET_SRC (set);
              if (dump_file)
                {
                  fprintf (dump_file,
                           "Pick insn %d as the second write CC insn.\n",
                           INSN_UID (insn));
                }
            }

          if (! cc_src_insn)
            continue;

          /* CC_SRC_INSN is the lastest condition code set insn,
             NULL means having not found one condition code set insn,
             if it is not NULL, then find the next condition code set
             insn. If two insns have same set source, delete the
             previous one and set CC_SRC_INSN to current insn; if
             they have different source, just set CC_SRC_INSN to
             current insn.  */
          for (prev_insn = PREV_INSN (cc_src_insn);
               prev_insn && prev_insn != PREV_INSN (BB_HEAD (bb));
               prev_insn = PREV_INSN (prev_insn))
            {
              rtx prev_cc_src = NULL_RTX;

              if (dump_file)
                {
                  fprintf (dump_file,
                           "\tScan for first CC writing insn, insn %d\n",
                           INSN_UID (prev_insn));
                }
              if (! INSN_P (prev_insn))
                continue;
              set = single_set (prev_insn);
              if (set
                  && REG_P (SET_DEST (set))
                  && REGNO (SET_DEST (set)) == REGNO (cc_reg))
                {
                  prev_cc_src = SET_SRC (set);
                  if (dump_file)
                    {
                      fprintf
                        (dump_file,
                         "\tPick insn %d as the first write CC insn.\n",
                         INSN_UID (prev_insn));
                    }
                }
              if (prev_cc_src != NULL_RTX)
                {
                  if (dump_file)
                    {
                      fprintf (dump_file,
                               "\tCompare the source part between "\
                               "insn %d and %d\n",
                               INSN_UID (cc_src_insn),
                               INSN_UID (prev_insn));
                    }
                  if (rtx_equal_p(cc_src, prev_cc_src))
                    {
                      delete_insn_and_edges (cc_src_insn);
                      if (dump_file)
                        {
                          fprintf (dump_file,
                                   "\tSame source, delete insn %d\n",
                                   INSN_UID (cc_src_insn));
                        }
                    }
                  cc_src_insn = prev_insn;
                  set = single_set (prev_insn);
                  cc_src = SET_SRC (set);
                  if (dump_file)
                    {
                      fprintf (dump_file,
                               "\tDifferet source, regard insn %d "\
                               "as the first write CC insn.\n",
                               INSN_UID (cc_src_insn));
                    }
                  continue;
                }
              else if (reg_set_p (cc_reg, prev_insn))
                {
                  insn = prev_insn;
                  cc_src_insn = NULL;
                  break;
                }
            }
          if (prev_insn == PREV_INSN (BB_HEAD (bb)))
            break;
        }
    }
  if (dump_file)
    {
      fprintf (dump_file, "-------------------------\n");
      fprintf (dump_file, "Scan complete!\n");
    }
  return 0;
}

namespace {

const pass_data pass_data_cse_cc =
{
    RTL_PASS, /* type */
    "cse_cc", /* name */
    OPTGROUP_NONE, /* optinfo_flags */
    TV_NONE, /* tv_id */
    0, /* properties_required */
    0, /* properties_provided */
    0, /* properties_destroyed */
    0, /* todo_flags_start */
    TODO_df_finish, /* todo_flags_finish */
};

class pass_cse_cc : public rtl_opt_pass
{
  public:
      pass_cse_cc (gcc::context *ctxt)
            : rtl_opt_pass (pass_data_cse_cc, ctxt)
                {}

        /* opt_pass methods: */
     virtual bool gate (function *)
              { return flag_cse_cc; }

      virtual unsigned int execute (function *)
      {  return rest_of_handle_cse_cc ();}
}; // class pass_cse_cc

}


rtl_opt_pass *
make_pass_cse_cc (gcc::context *ctxt)
{
  return new pass_cse_cc (ctxt);
}

/* Convert a static initializer array of feature bits to sbitmap
   representation.  */
static void
csky_initialize_isa (sbitmap isa, const enum csky_isa_feature *isa_bits)
{
  bitmap_clear (isa);
  while (*isa_bits != CSKY_ISA_FEATURE_GET(none))
    bitmap_set_bit (isa, *(isa_bits++));
}


/* Configure a build target TARGET from the user-specified options OPTS and
   OPTS_SET.  If WARN_COMPATIBLE, emit a diagnostic if both the CPU and
   architecture have been specified, but the two are not identical.  */
void
csky_configure_build_target (struct csky_build_target *target,
                             struct cl_target_option *opts,
                             struct gcc_options *opts_set,
                             bool warn_compatible)
{
  const struct csky_processors *csky_selected_tune = NULL;
  struct csky_processors *csky_selected_cpu = NULL;
  struct csky_processors *csky_selected_arch = NULL;
  sbitmap all_sbits = sbitmap_alloc (CSKY_ISA_FEATURE_GET(max));
  bitmap_clear(all_sbits);

  bitmap_clear (target->isa);
  target->core_name = NULL;
  target->arch_name = NULL;

  if (opts_set->x_csky_arch_option)
    csky_selected_arch = &all_architectures[opts->x_csky_arch_option];

  if (opts_set->x_csky_cpu_option)
    {
      csky_selected_cpu = &all_cores[opts->x_csky_cpu_option];
      csky_selected_tune = &all_cores[opts->x_csky_cpu_option];
    }

  if (csky_selected_cpu)
    {
      /* TODO: support combination of features
         between different cpu & arch, should based on arch.   */
      if (csky_selected_arch
          && (csky_selected_cpu->base_arch != csky_selected_arch->base_arch))
        {
          warning (0, "cpu %s is not based on arch %s, ignore the arch",
                   csky_selected_cpu->name, csky_selected_arch->name);
        }
      if (!csky_selected_arch)
        csky_selected_arch = &all_architectures[csky_selected_cpu->base_arch];
      csky_initialize_isa (all_sbits, csky_selected_arch->isa_bits);
      target->core_name = csky_selected_cpu->name;
    }
  else if (csky_selected_arch)
    {
      csky_selected_cpu = csky_selected_arch;
      target->arch_name = csky_selected_arch->name;
    }
  else /* If the user did not specify a processor, choose one for them.  */
    {
      csky_selected_cpu = &all_cores[TARGET_CPU_DEFAULT];
      csky_selected_arch = &all_architectures[csky_selected_cpu->base_arch];
      csky_initialize_isa (all_sbits, csky_selected_arch->isa_bits);
      target->core_name = csky_selected_cpu->name;
    }

  /* The selected cpu may be an architecture, so lookup tuning by core ID.  */
  if (!csky_selected_tune)
    csky_selected_tune = &all_cores[csky_selected_cpu->core];
  gcc_assert (csky_selected_tune);

  gcc_assert (csky_selected_arch);
  gcc_assert (csky_selected_cpu);
  csky_initialize_isa (target->isa, csky_selected_cpu->isa_bits);
  bitmap_ior (target->isa, target->isa, all_sbits);

  /* Finish initializing the target structure.  */
  target->arch_pp_name = csky_selected_cpu->arch;
  target->base_arch = csky_selected_cpu->base_arch;
  target->arch_core = csky_selected_cpu->core;
  target->tune = csky_selected_tune->tune;

  /* Setting isa features if there is no default
     which are controlled by the option.  */
  unsigned int i = 0;
  for (i = 0; i < sizeof(all_opt2isa)/sizeof(all_opt2isa[0]); i++)
    {
      if (target_flags & all_opt2isa[i].flag)
        {
          if (!bitmap_bit_p(target->isa, all_opt2isa[i].isa_bits[0]))
            {
              csky_initialize_isa (all_sbits, all_opt2isa[i].isa_bits);
              bitmap_ior (target->isa, target->isa, all_sbits);
            }
        }
      else
        {
          if (global_options_set.x_target_flags & all_opt2isa[i].flag)
            {
              csky_initialize_isa (all_sbits, all_opt2isa[i].isa_bits);
              bitmap_and_compl (target->isa, target->isa, all_sbits);
            }
        }
    }

  sbitmap_free(all_sbits);
}


static void
csky_configure_build_special_isa(struct csky_build_target *target)
{
  if (flag_pic && !(CSKY_TARGET_ARCH(CK810) || CSKY_TARGET_ARCH(CK807) || CSKY_TARGET_ARCH(CK860)))
    {
      flag_pic = 0;
      warning (0, "-fPIC is not supported by arch %s", target->arch_pp_name);
    }

  if (TARGET_HAVE_TLS && (CSKY_TARGET_ARCH(CK810) || CSKY_TARGET_ARCH(CK807) || CSKY_TARGET_ARCH(CK860)))
    bitmap_set_bit(target->isa, CSKY_ISA_FEATURE_GET(tls));

  if (TARGET_CONSTANT_POOL
      && (CSKY_TARGET_ARCH(CK802) || CSKY_TARGET_ARCH(CK801)))
    {
      bitmap_set_bit(target->isa, CSKY_ISA_FEATURE_GET(casesi));
    }
  if (CSKY_TARGET_ARCH(CK810)
      && csky_active_target.core_name != NULL
      && strchr (csky_active_target.core_name, 'v'))
    {
      vdsp_noisa |= BIT_NOT_EXPR;
      if (flag_csky_vdsp_width == 64)
        bitmap_set_bit(target->isa, CSKY_ISA_FEATURE_GET(vdsp64));
      else if (flag_csky_vdsp_width == 128)
        bitmap_set_bit(target->isa, CSKY_ISA_FEATURE_GET(vdsp128));
      else
        {
          warning (0, "The value of the option -mvdsp-width= can only be 64 or 128,\
                       now set to 64.");
          bitmap_set_bit(target->isa, CSKY_ISA_FEATURE_GET(vdsp64));
        }
    }

}


static void
csky_option_override (void)
{
  csky_active_target.isa = sbitmap_alloc (CSKY_ISA_FEATURE_GET(max));

  /* Create the default target_options structure.  We need this early
     to configure the overall build target.  */
  target_option_default_node = target_option_current_node
                             = build_target_option_node (&global_options);

  csky_configure_build_target (&csky_active_target,
                              TREE_TARGET_OPTION (target_option_default_node),
                              &global_options_set, true);

#ifdef SUBTARGET_OVERRIDE_OPTIONS
  SUBTARGET_OVERRIDE_OPTIONS;
#endif

  csky_arch_name = csky_active_target.arch_pp_name;
  csky_base_arch = csky_active_target.base_arch;
  current_tune = csky_active_target.tune;

  csky_configure_build_special_isa(&csky_active_target);

  if (TARGET_HARD_FLOAT)
    {
      if (TARGET_HARD_FLOAT_ABI && TARGET_LIBCCRT)
        error ("-mccrt and hard float are incompatible");

      const struct csky_fpu_desc *csky_selected_fpu = NULL;

      if (csky_fpu_index == TARGET_FPU_auto)
        {
          const char *target_fpu_name;
          bool ok;
          int fpu_index;

#ifdef CSKY_FPUTYPE_DEFAULT
          target_fpu_name = CSKY_FPUTYPE_DEFAULT;
#else
          target_fpu_name = "fpv2";
#endif

          if (csky_active_target.core_name != NULL
              && !strchr (csky_active_target.core_name, 'f'))
            target_fpu_name = "auto";
          else if (CSKY_TARGET_ARCH (CK803) || !TARGET_DOUBLE_FLOAT)
            target_fpu_name = "fpv2_sf";
          else if (TARGET_DOUBLE_FLOAT && TARGET_FDIVDU)
            target_fpu_name = "fpv2_divd";

          ok = opt_enum_arg_to_value (OPT_mfpu_, target_fpu_name, &fpu_index,
                                      CL_TARGET);
          gcc_assert (ok);
          csky_fpu_index = (enum csky_fpu_type) fpu_index;
        }

      if (csky_fpu_index != TARGET_FPU_auto)
        {
          csky_selected_fpu = &all_fpus[csky_fpu_index];
          sbitmap fpu_bits = sbitmap_alloc (CSKY_ISA_FEATURE_GET(max));
          csky_initialize_isa (fpu_bits, csky_selected_fpu->isa_bits);

          bitmap_ior (csky_active_target.isa, csky_active_target.isa,
                      fpu_bits);

          sbitmap_free(fpu_bits);
        }
      else
        {
          warning (0, "-mfloat-abi=softfp/hard is not supported in current CPU.");
          csky_float_abi = CSKY_FLOAT_ABI_SOFT;
        }
    }

  /* Initialize boolean versions of the architectural flags, for use
     in the .md file.  */

#undef  CSKY_ISA
#define CSKY_ISA(IDENT, DESC)                                             \
  {                                                                       \
    csky_arch_isa_features[CSKY_ISA_FEATURE_GET(IDENT)] =                 \
      bitmap_bit_p (csky_active_target.isa, CSKY_ISA_FEATURE_GET(IDENT)); \
  }
#include "abiv2_csky_isa.def"
#undef  CSKY_ISA

  /* TODO  */

  /* Resynchronize the saved target options.  */
  cl_target_option_save (TREE_TARGET_OPTION (target_option_default_node),
                         &global_options);

  /* Don't emit DWARF4 unless specifically selected.  The TPF
     debuggers do not yet support DWARF 3/4.  */
  if (!global_options_set.x_dwarf_strict)
    dwarf_strict = 1;
  if (!global_options_set.x_dwarf_version)
    dwarf_version = 3;
  /* Open optimization pass cse-cc by default when
     optimization level is greater than 1.  */
  if (!global_options_set.x_flag_cse_cc
      && (optimize > 1))
    flag_cse_cc = 1;
  /* enable the option of -fschedule-insns and -fsched-pressure
     by default when target has 32 regs.  */
  /* FIXME Temporarily close -fschedule-insns because it will
     cause helix performance to decline, the better way is to
     use schedule pressure algorithm: SCHED_PRESSURE_MODEL,
     it can be optimized after completion of the full assessment.  */
#if 0
  if (!global_options_set.x_flag_schedule_insns && !CSKY_ISA_FEATURE(hreg))
    {
      flag_schedule_insns = 0;
    }
  if (!global_options_set.x_flag_sched_pressure && !CSKY_ISA_FEATURE(hreg))
    {
      flag_sched_pressure = 0;
    }
#else
  if (!global_options_set.x_flag_schedule_insns)
    {
      flag_schedule_insns = 0;
    }
  if (!global_options_set.x_flag_sched_pressure)
    {
      flag_sched_pressure = 0;
    }
#endif

  /* Backtrace need use frame pointer reg */
  if (TARGET_BACKTRACE)
      flag_omit_frame_pointer = 0;

  if (!TARGET_CSKY_LINUX)
    {
      /* Don't open optimization isolate_erroneous_paths_dereference
         by default in elf gcc.  */
      if (!global_options_set.x_flag_isolate_erroneous_paths_dereference)
        flag_isolate_erroneous_paths_dereference = 0;
    }

  /* Enabled some flags to improve performance for ck802 in Os,
     and code size will been increased.  */
  if (CSKY_TARGET_ARCH(CK802) && optimize_size)
    {
      struct gcc_options *opts = &global_options;
      struct gcc_options *opts_set = &global_options_set;

      if (!opts_set->x_align_loops)
        opts->x_align_loops = 0;
      if (!opts_set->x_align_jumps)
        opts->x_align_jumps = 0;
      if (!opts_set->x_align_labels)
        opts->x_align_labels = 0;
      if (!opts_set->x_align_functions)
        opts->x_align_functions = 0;

      if (!opts_set->x_flag_reorder_blocks_and_partition)
        opts->x_flag_reorder_blocks_and_partition = 1;
      if (!opts_set->x_flag_reorder_blocks)
        opts->x_flag_reorder_blocks = 1;

      /* The optimization to partition hot and cold basic blocks into separate
         sections of the .o and executable files does not work (currently)
         with exception handling.  This is because there is no support for
         generating unwind info.  If opts->x_flag_exceptions is turned on
         we need to turn off the partitioning optimization.  */

      enum unwind_info_type ui_except = targetm_common.except_unwind_info (opts);
      location_t loc = UNKNOWN_LOCATION;

      if (opts->x_flag_exceptions
          && opts->x_flag_reorder_blocks_and_partition
          && (ui_except == UI_SJLJ || ui_except >= UI_TARGET))
        {
          if (opts_set->x_flag_reorder_blocks_and_partition)
            inform (loc,
                    "-freorder-blocks-and-partition does not work "
                    "with exceptions on this architecture");
          opts->x_flag_reorder_blocks_and_partition = 0;
          opts->x_flag_reorder_blocks = 1;
        }

      /* If user requested unwind info, then turn off the partitioning
         optimization.  */

      if (opts->x_flag_unwind_tables
          && !targetm_common.unwind_tables_default
          && opts->x_flag_reorder_blocks_and_partition
          && (ui_except == UI_SJLJ || ui_except >= UI_TARGET))
        {
          if (opts_set->x_flag_reorder_blocks_and_partition)
            inform (loc,
                    "-freorder-blocks-and-partition does not support "
                    "unwind info on this architecture");
          opts->x_flag_reorder_blocks_and_partition = 0;
          opts->x_flag_reorder_blocks = 1;
        }

      /* If the target requested unwind info, then turn off the partitioning
         optimization with a different message.  Likewise, if the target does not
         support named sections.  */

      if (opts->x_flag_reorder_blocks_and_partition
          && (!targetm_common.have_named_sections
          || (opts->x_flag_unwind_tables
              && targetm_common.unwind_tables_default
              && (ui_except == UI_SJLJ || ui_except >= UI_TARGET))))
        {
          if (opts_set->x_flag_reorder_blocks_and_partition)
            inform (loc,
                    "-freorder-blocks-and-partition does not work "
                    "on this architecture");
          opts->x_flag_reorder_blocks_and_partition = 0;
          opts->x_flag_reorder_blocks = 1;
        }
    }

  csky_add_gc_roots ();

  /* Register machine-specific passes. */
  opt_pass *pass_cse_cc = make_pass_cse_cc (g);
  struct register_pass_info cse_cc_info
        = { pass_cse_cc, "cse1",
            1, PASS_POS_INSERT_AFTER};
  register_pass (&cse_cc_info);
}


/* Return TRUE if X contains any TLS symbol references.  */

bool
csky_tls_referenced_p (rtx x)
{
  if (!CSKY_HAVE_TLS)
    return false;

  subrtx_iterator::array_type array;
  FOR_EACH_SUBRTX (iter, array, x, ALL)
    {
      const_rtx x = *iter;
      if (GET_CODE (x) == SYMBOL_REF && SYMBOL_REF_TLS_MODEL (x) != 0)
        return true;

      /* Don't recurse into UNSPEC_TLS looking for TLS symbols; these are
         TLS offsets, not real symbol references.  */
      if (GET_CODE (x) == UNSPEC && XINT (x, 1) == UNSPEC_TLS)
        iter.skip_subrtxes ();
    }
  return false;
}


/* Determine if it's legal to put X into the constant pool.  This
   is not possible for the address of thread-local symbols, which
   is checked above.  */

static bool
csky_cannot_force_const_mem (machine_mode mode ATTRIBUTE_UNUSED,
                             rtx x)
{
  return csky_tls_referenced_p (x);
}


/* Nonzero if the constant value X is a legitimate general operand.
   It is given that X satisfies CONSTANT_P or is a CONST_DOUBLE.  */

static bool
csky_legitimate_constant_p (machine_mode mode, rtx x)
{
  return (!csky_cannot_force_const_mem (mode, x)
          && !VECTOR_MODE_P (mode)
          && CONSTANT_P (x));
}


/* Return true if X is valid as an CSKY addressing register.  */

static bool
is_csky_address_register_rtx_p (rtx x, int strict_p)
{
  int regno;

  if (!x)
    return false;
  if (!REG_P (x))
    return false;

  regno = REGNO (x);

  if (strict_p)
    return CSKY_GENERAL_REGNO_P (regno) || CSKY_GENERAL_REGNO_P (reg_renumber[regno]);
  else
    return CSKY_GENERAL_REGNO_P (regno) || regno >= FIRST_PSEUDO_REGISTER;
}


/* Return TRUE if X is a thread-local symbol.  */

static bool
csky_tls_symbol_p (rtx x)
{
  if (! CSKY_HAVE_TLS)
    return false;

  if (GET_CODE (x) != SYMBOL_REF)
    return false;

  return SYMBOL_REF_TLS_MODEL (x) != 0;
}


static GTY(()) rtx tls_get_addr_libfunc;

static rtx
get_tls_get_addr (void)
{
  if (!tls_get_addr_libfunc)
    tls_get_addr_libfunc = init_one_libfunc ("__tls_get_addr");
  return tls_get_addr_libfunc;
}


static rtx
csky_load_tp (rtx target)
{
  if (!target)
    target = gen_reg_rtx (SImode);

  if (TARGET_HARD_TP)
    {
      /* Can return in any reg.  */
      emit_insn (gen_load_tp_hard (target));
    }
  else
    {
      /* Always returned in r0.  Immediately copy the result into a pseudo,
         otherwise other uses of r0 (e.g. setting up function arguments) may
         clobber the value.  */
      if (flag_pic)
        emit_insn (gen_load_tp_soft_pic ());
      else
        emit_insn (gen_load_tp_soft ());
      emit_move_insn (target, gen_rtx_REG (SImode, 0));
    }
  return target;
}


static rtx
load_tls_operand (rtx x, rtx reg)
{
  if (reg == NULL_RTX)
    reg = gen_reg_rtx (SImode);

  emit_move_insn (reg, x);
  return reg;
}


static rtx
csky_call_tls_get_addr (rtx x, rtx reg, rtx *valuep, int reloc)
{
  rtx insns, label, labelno, sum;

  start_sequence ();

  labelno = GEN_INT (tls_labelno++);

  label = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, labelno), UNSPEC_TLS_LABEL);

  sum = gen_rtx_UNSPEC (Pmode,
                        gen_rtvec (3, x, GEN_INT (reloc), label),
                        UNSPEC_TLS);

  reg = load_tls_operand (sum, reg);

  emit_insn (gen_tls_do_add_pc (reg, reg, labelno));

  *valuep = emit_library_call_value (get_tls_get_addr (),
                                     NULL_RTX, LCT_PURE, /* LCT_CONST?  */
                                     Pmode, 1, reg, Pmode);
  insns = get_insns ();
  end_sequence ();

  return insns;
}


rtx
legitimize_tls_address (rtx x, rtx reg)
{
  rtx dest, tp, label, labelno, sum, insns, ret, eqv, addend;
  unsigned int model = SYMBOL_REF_TLS_MODEL (x);

  switch (model)
    {
    case TLS_MODEL_GLOBAL_DYNAMIC:
      insns = csky_call_tls_get_addr (x, reg, &ret, TLS_GD32);
      dest = gen_reg_rtx (Pmode);
      emit_libcall_block (insns, dest, ret, x);
      return dest;

    case TLS_MODEL_LOCAL_DYNAMIC:
      insns = csky_call_tls_get_addr (x, reg, &ret, TLS_LDM32);

      /* Attach a unique REG_EQUIV, to allow the RTL optimizers to
     share the LDM result with other LD model accesses.  */
      eqv = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, const1_rtx), UNSPEC_TLS);
      dest = gen_reg_rtx (Pmode);
      emit_libcall_block (insns, dest, ret, eqv);

      /* Load the addend.  */
      addend = gen_rtx_UNSPEC (Pmode,
                               gen_rtvec (2, x, GEN_INT (TLS_LDO32)),
                               UNSPEC_TLS);
      addend = force_reg (SImode, addend);
      return gen_rtx_PLUS (Pmode, dest, addend);

    case TLS_MODEL_INITIAL_EXEC:
      labelno = GEN_INT (tls_labelno++);
      label = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, labelno), UNSPEC_TLS_LABEL);
      sum = gen_rtx_UNSPEC (Pmode,
                            gen_rtvec (3, x, GEN_INT (TLS_IE32), label),
                            UNSPEC_TLS);
      reg = load_tls_operand (sum, reg);

      emit_insn (gen_tls_do_add_pc (reg, reg, labelno));
      emit_move_insn (reg, gen_const_mem (Pmode, reg));

      tp = csky_load_tp (NULL_RTX);

      return gen_rtx_PLUS (Pmode, tp, reg);

    case TLS_MODEL_LOCAL_EXEC:
      tp = csky_load_tp (NULL_RTX);

      reg = gen_rtx_UNSPEC (Pmode,
                            gen_rtvec (2, x, GEN_INT (TLS_LE32)),
                            UNSPEC_TLS);
      reg = force_reg (SImode, reg);

      return gen_rtx_PLUS (Pmode, tp, reg);

    default:
      abort ();
    }
}


/* Try machine-dependent ways of modifying an illegitimate address
   to be legitimate.  If we find one, return the new, valid address.  */

static rtx
csky_legitimize_address (rtx x, rtx orig_x ATTRIBUTE_UNUSED,
                         enum machine_mode mode)
{
  if (csky_tls_symbol_p (x))
    return legitimize_tls_address (x, NULL_RTX);

  if (GET_CODE (x) == PLUS)
    {
      rtx xop0 = XEXP (x, 0);
      rtx xop1 = XEXP (x, 1);

      if (is_csky_address_register_rtx_p (xop0, 0)
          && CONST_INT_P (xop1))
        {
          HOST_WIDE_INT offset = INTVAL (xop1);

          /* Try to replace ld32 rx,(ry, offset), to addi16 rz, oimm8
             and ld16 rx,(rz, new_ld_offset) to avoid emit 32bit ld,
             but this addi has it limition.  */
          if (optimize_size
              && offset > CSKY_LD16_MAX_OFFSET (mode)
              && offset <= (CSKY_ADDI16_MAX_IMM
                           + CSKY_LD16_MAX_OFFSET (mode)))
            {
              HOST_WIDE_INT new_ld_offset = offset
                & CSKY_LD16_OFFSET_MASK (mode);

              xop0 = force_operand (plus_constant (Pmode, xop0,
                                                   offset - new_ld_offset),
                                    NULL_RTX);
              x = plus_constant (Pmode, xop0, new_ld_offset);
            }
          else if (offset < 0 && offset >= (-CSKY_SUBI16_MAX_IMM))
            x = force_operand (x, NULL_RTX);
          else if (offset > CSKY_LD16_MAX_OFFSET (mode)
                   || offset < 0)
            {
              /* For the remaining cases, force the constant into a register.  */
              xop1 = force_reg (SImode, xop1);
              x = gen_rtx_PLUS (SImode, xop0, xop1);
            }
        }

      /* If the index is store in register, force the
         base to register.  */
      if (is_csky_address_register_rtx_p (xop1, 0)
          && !is_csky_address_register_rtx_p (xop0, 0))
        {
          xop0 = force_operand (xop0, NULL_RTX);
          x = gen_rtx_PLUS (SImode, xop0, xop1);
        }
    }
  /* Make sure to take full advantage of the pre-indexed addressing mode
     with absolute addresses which often allows for the base register to
     be factorized for multiple adjacent memory references, and it might
     even allows for the mini pool to be avoided entirely. */
  else if (CONST_INT_P (x)  && optimize > 0)
    {
      HOST_WIDE_INT mask, base, index;
      rtx base_reg;

      mask = CSKY_LD16_OFFSET_MASK (mode);;
      base = INTVAL (x) & ~mask;
      index = INTVAL (x) & mask;
      base_reg = force_reg (SImode, GEN_INT (base));
      x = plus_constant (Pmode, base_reg, index);
    }

  return x;
}


/* Return nonzero if INDEX is valid for an address index operand.
   ck801 use 16 bits ld
   ck802 use 16 and 32 bits ld
   others use ld and ldr.  */

static int
ck801_legitimate_index_p (enum machine_mode mode, rtx index,
                          int strict_p ATTRIBUTE_UNUSED)
{
  enum rtx_code code = GET_CODE (index);

  /* When the mode size is larger than 4, we may use two ld instruction
     to get data, the index and (index+1) should be valid.  */
  if (GET_MODE_SIZE (mode) >= 8)
    return (code == CONST_INT
            && INTVAL (index) <  CSKY_LD16_MAX_OFFSET (SImode)
            && INTVAL (index) >= 0 && (INTVAL (index) & 3) == 0);

  if (code == CONST_INT && GET_MODE_SIZE (mode) > 0
      && INTVAL (index) <= CSKY_LD16_MAX_OFFSET (mode)
      && INTVAL (index) >= 0)
    return ((INTVAL (index) % GET_MODE_SIZE (mode)) == 0);

  return 0;
}


static int
ck802_legitimate_index_p (enum machine_mode mode, rtx index,
                          int strict_p ATTRIBUTE_UNUSED)
{
  enum rtx_code code = GET_CODE (index);

  /* When the mode size is larger than 4, we may use two ld instruction
     to get data, the index and (index+1) should be valid.  */
  if (GET_MODE_SIZE (mode) >= 8)
    return (code == CONST_INT
            && INTVAL (index) < CSKY_LD32_MAX_OFFSET (SImode)
            && INTVAL (index) >= 0 && (INTVAL (index) & 3) == 0);

  if (code == CONST_INT && GET_MODE_SIZE (mode) > 0
      && INTVAL (index) <= CSKY_LD32_MAX_OFFSET(mode)
      && INTVAL (index) >= 0)
    return ((INTVAL (index) % GET_MODE_SIZE (mode)) == 0);

  return 0;
}


/* The instruction ldr rz, (rx, ry << i), i can be 0,1,2,3.
   Checkout the SHIFT is whether valid, if the code is MULT,
   the shift should be 1<<i.  */
static bool
is_ldr_shift_p (HOST_WIDE_INT shift, enum rtx_code code)
{
  if (code == ASHIFT)
    return (shift >= 0 && shift <=3);
  else if (code == MULT)
    return (shift == 1
            || shift == 2
            || shift == 4
            || shift == 8);
  else
    return false;
}


static int
ck810_legitimate_index_p (enum machine_mode mode, rtx index, int strict_p)
{
  enum rtx_code code = GET_CODE (index);

  if (TARGET_HARD_FLOAT
      && (mode == SFmode || mode == DFmode)
      && code == CONST_INT)
    return (INTVAL (index) < 1024
            && INTVAL (index) >= 0
            && (INTVAL (index) & 3) == 0);

  if (code == CONST_INT)
    {
      if (VECTOR_MODE_P (mode)
          && INTVAL (index) <= CSKY_VLD_MAX_OFFSET (mode)
          && INTVAL (index) >= 0)
        return ((INTVAL (index) % GET_MODE_SIZE (mode)) == 0);

      /* When the mode size is larger than 4, we may use two ld instruction
         to get data, the index and (index+1) should be valid.  */
      if (GET_MODE_SIZE (mode) >= 8)
        return (INTVAL (index) < CSKY_LD32_MAX_OFFSET (SImode)
                && INTVAL (index) >= 0 && (INTVAL (index) & 3) == 0);

      if (GET_MODE_SIZE (mode) > 0
          && INTVAL (index) <= CSKY_LD32_MAX_OFFSET (mode)
          && INTVAL (index) >= 0)
        return ((INTVAL (index) % GET_MODE_SIZE (mode)) == 0);
    }
  /* Allow ld.w rx, (gb, sym@got) when -fpic specially.  */
  else if (code == UNSPEC)
    {
      return (flag_pic == 1
              && (XINT (index, 1) == PIC_SYMBOL_PLT
                  || XINT (index, 1) == PIC_SYMBOL_GOT));
    }
  /* The follow index is for ldr instruction, the ldr cannot
     load dword data if no vector, so the mode size should
     not be larger than 4.  */
  else if (GET_MODE_SIZE (mode) <= 4 || VECTOR_MODE_P (mode))
    {
      if (is_csky_address_register_rtx_p (index, strict_p))
        return 1;
      else if (code == MULT || code == ASHIFT)
        {
          rtx xiop0 = XEXP (index, 0);
          rtx xiop1 = XEXP (index, 1);

          /* FIXME can the xiop1 be the reg and xiop0 be the int when mult?  */
          return (is_csky_address_register_rtx_p (xiop0, strict_p)
                  && CONST_INT_P (xiop1)
                  && is_ldr_shift_p (INTVAL (xiop1), code));
        }
    }

  return 0;
}

static int
csky_legitimate_index_p (machine_mode mode, rtx index, int strict_p)
{
  if (CSKY_TARGET_ARCH(CK801))
    return ck801_legitimate_index_p (mode, index, strict_p);
  else if (CSKY_TARGET_ARCH(CK802))
    return ck802_legitimate_index_p (mode, index, strict_p);
  else
    return ck810_legitimate_index_p (mode, index, strict_p);
}

/* Recognizes RTL expressions that are valid memory addresses for an
   instruction.  The MODE argument is the machine mode for the MEM
   expression that wants to use this address.

   It only recognizes address in canonical form.  LEGITIMIZE_ADDRESS should
   convert common non-canonical forms to canonical form so that they will
   be recognized.  */

bool
csky_legitimate_address_p (machine_mode mode, rtx addr, bool strict_p)
{
  enum rtx_code code = GET_CODE (addr);

  /* This is to fit the address emit by const pool.
     After reload constants split into minipools will have addresses
     from a LABEL_REF.  */
  if (reload_completed
      && ((code == LABEL_REF)
           || (code == CONST
               && GET_CODE (XEXP (addr, 0)) == PLUS
               && GET_CODE (XEXP (XEXP (addr, 0), 0)) == LABEL_REF
               && CONST_INT_P (XEXP (XEXP (addr, 0), 1)))))
    return 1;

  if (is_csky_address_register_rtx_p (addr, strict_p))
    return 1;
  /* It is a pc-relative load, may be generated for constpool.  */
  else if (GET_CODE (addr) == LABEL_REF)
    {
      rtx x = XEXP (addr, 0);
      if (x != NULL
          && GET_CODE (x) == UNSPEC_VOLATILE
          && XINT (x, 1) == VUNSPEC_POOL_LABEL)
        return 1;
      else
        return 0;
    }

  if (code == PLUS)
    {
      rtx xop0 = XEXP (addr, 0);
      rtx xop1 = XEXP (addr, 1);

      return ((is_csky_address_register_rtx_p (xop0, strict_p)
               && csky_legitimate_index_p (mode, xop1, strict_p))
              || (is_csky_address_register_rtx_p (xop1, strict_p)
                  && csky_legitimate_index_p (mode, xop0, strict_p)));
    }
  else if (CSKY_ISA_FEATURE(dspv2) && code == POST_INC
           && GET_MODE_CLASS (mode) == MODE_INT
           && GET_MODE_SIZE (mode) <= 4)
    {
      int regno;

      if (!REG_P (XEXP(addr, 0)))
        return 0;

      regno = REGNO (XEXP (addr, 0));

      if (strict_p)
        return (CSKY_GENERAL_REGNO_P(regno)
                || CSKY_GENERAL_REGNO_P(reg_renumber[regno]));

      return (CSKY_GENERAL_REGNO_P(regno)
              || regno >= FIRST_PSEUDO_REGISTER);
    }
  return 0;
}


/* Functions to save and restore machine-specific function data.  */

static struct machine_function *
csky_init_machine_status (void)
{
  struct machine_function *machine;

  machine = ggc_cleared_alloc<machine_function> ();

#if CSKY_FT_UNKNOWN != 0
  machine->func_type = CSKY_FT_UNKNOWN;
#endif
  return machine;
}


/* Return an RTX indicating where the return address to the
   calling function can be found.  */

void
csky_init_expanders (void)
{
  /* Arrange to initialize and mark the machine per-function status.  */
  init_machine_status = csky_init_machine_status;
}


/* Must not copy any rtx that uses a pc-relative address.  */

static bool
csky_cannot_copy_insn_p (rtx_insn *insn)
{
  subrtx_iterator::array_type array;
  FOR_EACH_SUBRTX (iter, array, PATTERN (insn), ALL)
    {
      const_rtx x = *iter;
      if (GET_CODE (x) == UNSPEC
          && (XINT (x, 1) == UNSPEC_TLS_LABEL
              || XINT (x, 1) == PIC_SYMBOL_GOTPC_GRS))
        return true;
    }
  return false;
}


/* Extract the parts of an RTL expression that is a valid memory address
   for an instruction.  Return FALSE if it is a invalid memory address.  */

bool
decompose_csky_address (rtx addr, struct csky_address * out)
{
  rtx base = NULL_RTX, index = NULL_RTX, disp = NULL_RTX;
  HOST_WIDE_INT scale = 1;
  rtx scale_rtx = NULL_RTX;
  int i;

  out->base = out->index = out->symbol = out->label = out->disp
    = out->post_inc_reg = NULL_RTX;
  out->scale = 0;

  if (CSKY_ISA_FEATURE(dspv2) && GET_CODE (addr) == POST_INC)
    {
      out->post_inc_reg = XEXP (addr, 0);
      return true;
    }

  if (REG_P (addr))
    {
      out->base = addr;
      return true;
    }

  if (GET_CODE (addr) == LABEL_REF)
    {
      out->label = addr;
      return true;
    }

  if (GET_CODE (addr) == CONST)
    {
      addr = XEXP (addr, 0);
    }

  if (GET_CODE (addr) == PLUS)
    {
      rtx addends[2], op;

      addends[0] = XEXP (addr, 0);
      addends[1] = XEXP (addr, 1);

      if (GET_CODE (addends[0]) == LABEL_REF && CONST_INT_P (addends[1]))
        {
          out->label = addends[0];
          out->disp = addends[1];
          return true;
        }

      if (!REG_P (addends[0]))
        std::swap (addends[0], addends[1]);

      for (i = 0; i < 2; ++i)
        {
          op = addends[i];
          switch (GET_CODE (op))
            {
            case REG:
              if (!base)
                base = op;
              else if (!index)
                index = op;
              else
                return false;
              break;
            case CONST_INT:
            case UNSPEC:
              if (disp)
                return false;
              disp = op;
              break;
            case MULT:
              if (index)
                return false;
              index = XEXP (op, 0);
              scale_rtx = XEXP (op, 1);
              if (!CONST_INT_P (index) && !CONST_INT_P (scale_rtx))
                return false;
              else if (CONST_INT_P (index))
                std::swap (index, scale_rtx);
              scale = INTVAL (scale_rtx);
              break;
            case ASHIFT:
              if (index)
                return false;
              index = XEXP (op, 0);
              scale_rtx = XEXP (op, 1);
              if (!CONST_INT_P (scale_rtx))
                return false;
              scale = scale << INTVAL (scale_rtx);
              break;
            default:
              return false;
            }
        }
    }

  if (!base)
    return false;

  out->base = base;
  out->index = index;
  out->disp = disp;
  out->scale = scale;

  return true;
}


/* Print the UNSPEC operand in X to the STREAM.  */

static void
csky_output_pic_addr_const (FILE * stream, rtx x, int code)
{

  if (GET_CODE (x) != UNSPEC)
    return;

  if (UNSPEC_TLS == XINT (x, 1))
    {
      /* FIXME It is not reached */

      return;
    }

  csky_print_operand (stream, XVECEXP (x, 0, 0), code);

  switch (XINT (x, 1))
    {
    case PIC_SYMBOL_GOTOFF:
      fputs ("@GOTOFF", stream);
      break;
    case PIC_SYMBOL_PLT:
      fputs ("@PLT", stream);
      break;
    case PIC_SYMBOL_GOT:
      fputs ("@GOT", stream);
      break;
    case PIC_SYMBOL_GOTPC:
      fputs ("@GOTPC", stream);
      break;
    case PIC_SYMBOL_BSR:
      break;
    default:
      break;
    }
}


/* Output the constpool label according to the rtx expression X.  */

void
csky_output_constpool_label (FILE * stream, rtx x)
{
  char buf[15];

  gcc_assert (GET_CODE (x) == LABEL_REF);
  x = XEXP (x, 0);

  if (GET_CODE (x) == UNSPEC_VOLATILE && XINT (x, 1) == VUNSPEC_POOL_LABEL)
    {
      ASM_GENERATE_INTERNAL_LABEL (buf, CSKY_CONSTPOOL_LABEL_PREFIX,
                                   INTVAL (XVECEXP (x, 0, 0)));
      assemble_name (stream, buf);
    }

}


/* Print the operand address in X to the STREAM.  */

void
csky_print_operand_address (FILE * stream,
                            machine_mode mode ATTRIBUTE_UNUSED,
                            rtx x)
{

  struct csky_address addr;

  decompose_csky_address (x, &addr);

  if (addr.label && addr.disp && GET_CODE (addr.disp) == CONST_INT)
    {
      fprintf (stream, "[");
      csky_output_constpool_label (stream, addr.label);
      fprintf (stream, "+%d]", (int) INTVAL (addr.disp));
    }
  else if (addr.label)
    {
      fprintf (stream, "[");
      csky_output_constpool_label (stream, addr.label);
      fprintf (stream, "]");
    }
  else if (addr.symbol && addr.disp && GET_CODE (addr.disp) == CONST_INT)
    {
      fprintf (stream, "[");
      output_addr_const (stream, addr.symbol);
      fprintf (stream, "+%d]", (int) INTVAL (addr.disp));
    }
  else if (addr.symbol)
    {
      fprintf (stream, "[");
      output_addr_const (stream, addr.symbol);
      fprintf (stream, "]");
    }
  else if (addr.disp && GET_CODE (addr.disp) == CONST_INT)
    {
      fprintf (stream, "(%s, %d)",
               reg_names[REGNO (addr.base)], (int) INTVAL (addr.disp));
    }
  else if (addr.disp && GET_CODE (addr.disp) == UNSPEC)
    {
      if (REGNO (addr.base) != CSKY_GB_REGNUM)
        fprintf (stream, "(%s, ", reg_names[REGNO (addr.base)]);
      else
        fprintf (stream, "[");
      csky_output_pic_addr_const (stream, addr.disp, 0);
      fprintf (stream, "%s", (REGNO (addr.base) != CSKY_GB_REGNUM)
               ? ")" : "]");
    }
  else if (addr.index)
    {
      fprintf (stream, "(%s, %s << %d)",
               reg_names[REGNO (addr.base)], reg_names[REGNO (addr.index)],
               exact_log2 ((int) (addr.scale)));
    }
  else if (addr.post_inc_reg)
    {
      fprintf (stream, "(%s)", reg_names[REGNO (addr.post_inc_reg)]);
    }
  else
    {
      fprintf (stream, "(%s, 0)", reg_names[REGNO (addr.base)]);
    }

}


/* Print operand X (an rtx) in assembler syntax to file STEAM
   according to modifier CODE.

   'N'  print the log2(X+1), mainly used for bmaski
   'P'  print the log2(X)
   'Q'  print the log2(~X)
   'O'  print a decimal number
   'M'  print a decimal number as its negative
   'R'  print the next register or memory location along, i.e. the lsw in
   a double word value
   'H'  print the high 16 bits of a constant.  */

void
csky_print_operand (FILE * stream, rtx x, int code)
{
  switch (code)
    {
    case 'N':
      if ((INTVAL (x) & 0xffffffff) == 0xffffffff)
        fprintf (stream, "0");
      else
        fprintf (stream, "%d",
                 (int) exact_log2 ((INTVAL (x) & 0xffffffff) + 1) % 32);
      break;
    case 'P':
      fprintf (stream, "%d",
               (int) exact_log2 (INTVAL (x) & 0xffffffff));
      break;
    case 'Q':
      fprintf (stream, "%d",
               (int) exact_log2 (~INTVAL (x) & 0xffffffff));
      break;
    case 'O':
      fprintf (stream, "%d", (int) INTVAL (x));
      break;
    case 'M':
      fprintf (stream, "%d", (int) (-INTVAL (x)));
      break;
    case 'R':
      /* Next location along in memory or register.  */
      switch (GET_CODE (x))
        {
        case REG:
          fputs (reg_names[REGNO (x) + 1], stream);
          break;
        case MEM:
          csky_print_operand_address
            (stream, GET_MODE (x), XEXP (adjust_address (x, SImode, 4), 0));
          break;
        default:
          gcc_unreachable ();
        }
      break;
    case 'S':
      /* Second location along in register.  */
      switch (GET_CODE (x))
        {
        case REG:
          fputs (reg_names[REGNO (x) + 2], stream);
          break;
        default:
          gcc_unreachable ();
        }
      break;
    case 'T':
      /* Third location along in register.  */
      switch (GET_CODE (x))
        {
        case REG:
          fputs (reg_names[REGNO (x) + 3], stream);
          break;
        default:
          gcc_unreachable ();
        }
      break;
    case 'H':
      fprintf (stream, "%ld", ((INTVAL (x)) & 0xFFFF0000) >> 16);
      break;
    default:
      switch (GET_CODE (x))
        {
        case REG:
          fputs (reg_names[REGNO (x)], stream);
          break;
        case MEM:
          output_address (GET_MODE (x), XEXP (x, 0));
          break;
        case UNSPEC:
          csky_output_pic_addr_const (stream, x, code);
          break;
        default:
          output_addr_const (stream, x);
          break;
        }
      break;
    }
}


/* Define a table to map arguement and funtion type.  */
typedef struct
{
  const char *const arg;
  const unsigned long return_value;
} isr_attribute_arg;

static const isr_attribute_arg isr_attribute_args[] =
{
  {"irq", CSKY_FT_ISR },
  {"IRQ", CSKY_FT_ISR },
  {"fiq", CSKY_FT_FIQ },
  {"FIQ", CSKY_FT_FIQ },
  {NULL, CSKY_FT_NORMAL }
};


/* Return the function type of the current function, if it has not been
   determined, return CSKY_FT_UNKNOWN.  */

static unsigned long
get_csky_isr_type(tree argument)
{
  const isr_attribute_arg *ptr;
  const char *arg;

  /* if arguement is NULL, set default value ISR.  */
  if(argument == NULL_TREE)
    return CSKY_FT_ISR;

  if(TREE_VALUE(argument) == NULL_TREE
     || TREE_CODE(TREE_VALUE(argument)) != STRING_CST)
    return CSKY_FT_UNKNOWN;

  arg = TREE_STRING_POINTER(TREE_VALUE(argument));

  for(ptr = isr_attribute_args; ptr->arg != NULL; ptr++)
    {
      if(strcmp(arg, ptr->arg) == 0)
        return ptr->return_value;
    }

  return CSKY_FT_UNKNOWN;
}


bool
csky_allocate_stack_slots_for_args(void)
{
  /* naked functions should not allocate stack slots for arguments.  */
  return !CSKY_FUNCTION_IS_NAKED(get_csky_current_func_type());
}


/* Can we generate a constant with a single instruction(Donot use lrw).  */

int
const_ok_for_cskyv2 (HOST_WIDE_INT value)
{
  /* Try exact power of two. It can be generated by bgeni.  */
  if (CSKY_CONST_OK_FOR_Ub (value))
    return 1;

  /* Try exact power of two - 1. It can be generated by bmaksi.  */
  if (CSKY_CONST_OK_FOR_Uc (value) && value != -1)
    return 1;

  /* Try if it can be generated by movi.  */
  if (CSKY_CONST_OK_FOR_I (value))
    return 1;

  /* The constant can be generated by movih.
     Notice the movih is a 32bits intruction.  */
  if (CSKY_CONST_OK_FOR_MOVIH (value))
    return 1;

  return 0;
}


int
constant_csky_inlinable (HOST_WIDE_INT value)
{
  HOST_WIDE_INT x, y;
  return !(CSKY_TARGET_ARCH(CK802) || CSKY_TARGET_ARCH(CK801))
    && try_csky_constant_tricks (value, &x, &y);
}


/* Try tricks to load a constant inline and return the trick number if
   success (0 is non-inlinable). More information look the comment of
   enum csky_inline_const_type defination.  */

static enum csky_inline_const_type
try_csky_constant_tricks (HOST_WIDE_INT value, HOST_WIDE_INT * x,
                     HOST_WIDE_INT * y)
{
  HOST_WIDE_INT i, value_invert;
  unsigned HOST_WIDE_INT bit, shf, rot;

  value &= 0xffffffff;
  value_invert = ~value & 0xffffffff;

  if (const_ok_for_cskyv2 (value))
    {
      *x = value;
      return IC_SINGLE;
    }

  /* Since movih is 32bits, do not use it here, better code may generate later.  */
  if (const_ok_for_cskyv2 (value_invert) && !CSKY_CONST_OK_FOR_MOVIH (value_invert))
    {
      *x = value_invert;
      return IC_APPEND_NOT;
    }

  /* One immediate generate instruction, and one 16bits subi or addi.  */
  for (i = 1; i <= 32; i++)
    {
      if (const_ok_for_cskyv2 (value - i) && !CSKY_CONST_OK_FOR_MOVIH (value - i))
        {
          *x = value - i;
          *y = i;
          return IC_APPEND_ADDI;
        }

      if (const_ok_for_cskyv2 (value + i) && !CSKY_CONST_OK_FOR_MOVIH (value - i))
        {
          *x = value + i;
          *y = i;
          return IC_APPEND_SUBI;
        }
    }

  /* Generate bgeni + addi.  */
  if (CSKY_CONST_OK_FOR_Ub (value & 0xfffff000))
    {
      *x = (value & 0xfffff000);
      *y = (value & 0xfff);
      return IC_BGENI_ADDI;
    }

  /* Generate bgeni + subi.  */
  if (CSKY_CONST_OK_FOR_BS (value))
    {
      *x = ((value & 0xfffff000) + (1 << 12));
      *y = (0x1000 - (value & 0xfff));
      return IC_BGENI_SUBI;
    }

  /* One immediate generate instruction, and one bseti or bclri.  */
  bit = 0x80000000ULL;
  for (i = 0; i <= 31; i++)
    {
      if (const_ok_for_cskyv2 (value & ~bit)
          && !CSKY_CONST_OK_FOR_MOVIH (value & ~bit))
        {
          *y = bit;
          *x = (value & ~bit);
          return IC_APPEND_BSETI;
        }

      if (const_ok_for_cskyv2 (value | bit)
          && !CSKY_CONST_OK_FOR_MOVIH (value | bit))
        {
          *y = ~bit & 0xffffffff;
          *x = value | bit;
          return IC_APPEND_BCLRI;
        }

      bit >>= 1;
    }

  /* One immediate generate instruction, and one rotli or lsli.  */
  shf = value;
  rot = value;
  for (i = 1; i < 31; i++)
    {
      int c;

      /* Rotate left.  */
      c = rot << 31;
      rot >>= 1;
      rot &= 0x7FFFFFFF;
      rot |= c;

      if (const_ok_for_cskyv2 (rot) && !CSKY_CONST_OK_FOR_MOVIH (rot))
        {
          *y = i;
          *x = rot;
          return IC_APPEND_ROTLI;
        }

      /* Can't use logical shift when low order bit is one.  */
      if (shf & 1)
        shf = 0;
      else
        shf >>= 1;

      if (shf != 0 && const_ok_for_cskyv2 (shf)
          && !CSKY_CONST_OK_FOR_MOVIH (shf))
        {
          *y = i;
          *x = shf;
          return IC_APPEND_LSLI;
        }
    }

  /* One immediate generate instruction, and one ixh.  */
  if ((value % 3) == 0 && const_ok_for_cskyv2 (value / 3)
      && !CSKY_CONST_OK_FOR_MOVIH (value / 3))
    {
      *x = value / 3;
      return IC_APPEND_IXH;
    }

  /* One immediate generate instruction, and one ixw.  */
  if ((value % 5) == 0 && const_ok_for_cskyv2 (value / 5)
      && !CSKY_CONST_OK_FOR_MOVIH (value / 5))
    {
      *x = value / 5;
      return IC_APPEND_IXW;
    }

  /* Generate movih + bseti.  */
  if (CSKY_CONST_OK_FOR_Ub (value & 0xffff))
    {
      *x = value & 0xffff0000;
      *y = value & 0xffff;
      return IC_APPEND_BSETI;
    }

  /* Generate movih + not.  */
  if (CSKY_CONST_OK_FOR_MOVIH (value_invert))
    {
      *x = value_invert;
      return IC_APPEND_NOT;
    }

  /* One movih, and one 16bits addi or subi.  */
  for (i = 1; i <= 32; i++)
    {
      if (CSKY_CONST_OK_FOR_MOVIH (value - i))
        {
          *x = value - i;
          *y = i;

          return IC_APPEND_ADDI;
        }

      if (CSKY_CONST_OK_FOR_MOVIH (value + i))
        {
          *x = value + i;
          *y = i;

          return IC_APPEND_SUBI;
        }
    }

  /* One movih, and one bseti or bclri.  */
  bit = 0x80000000ULL;
  for (i = 0; i <= 31; i++)
    {
      if (CSKY_CONST_OK_FOR_MOVIH (value & ~bit))
        {
          *y = bit;
          *x = value & ~bit;
          return IC_APPEND_BSETI;
        }

      if (CSKY_CONST_OK_FOR_MOVIH (value | bit))
        {
          *y = ~bit & 0xffffffff;
          *x = value | bit;

          return IC_APPEND_BCLRI;
        }

       bit >>= 1;
    }

  /* One movih, and one rotli or lsli.  */
  shf = value;
  rot = value;
  for (i = 1; i < 31; i++)
    {
      int c;

      /* Rotate left.  */
      c = rot << 31;
      rot >>= 1;
      rot &= 0x7FFFFFFF;
      rot |= c;

      if (CSKY_CONST_OK_FOR_MOVIH (rot))
        {
          *y = i;
          *x = rot;

          return IC_APPEND_ROTLI;
        }

      /* Can't use logical shift when low order bit is one.  */
      if (shf & 1)
        shf = 0;
      else
        shf >>= 1;

      if (shf != 0 && CSKY_CONST_OK_FOR_MOVIH (shf))
        {
          *y = i;
          *x = shf;
          return IC_APPEND_LSLI;
        }
    }

  return IC_UNINLINABLE;
}


/* Output an inline constant, accoraing to the number get from
   funtion 'try_csky_constant_tricks', there are serveral combinations.

   The first single load instruction can be: movi,bmaski,movih
   (bgeni is a pseudo instruction of movi or movih).
   The second signle instruction can be: not,subi,addi,rsubi,bseti,
   bclri,rotli,lsli,ixh,ixw.
   The second instruction may not be generated if not needed.  */

static const char *
output_csky_inline_const (enum machine_mode mode, rtx operands[])
{
  HOST_WIDE_INT x = 0, y = 0;
  enum csky_inline_const_type trick_type;
  rtx out_operands[3];
  char buf[256];
  char load_op[256];
  const char *dst_fmt;
  HOST_WIDE_INT value = INTVAL (operands[1]);

  trick_type = try_csky_constant_tricks (value, &x, &y);
  /* lrw's are handled separately: Large inlinable constants never get
     turned into lrw's.  Our caller uses try_csky_constant_tricks to back
     off to an lrw rather than calling this routine.  */
  gcc_assert (trick_type != IC_UNINLINABLE);

  /* Operands: 0 = dst, 1 = load immedate., 2 = adjust immedate.  */
  out_operands[0] = operands[0];
  out_operands[1] = GEN_INT (x);
  if (trick_type != IC_SINGLE && trick_type != IC_APPEND_NOT)
    out_operands[2] = GEN_INT (y);

  /* Select dst format based on mode.  */
  if (mode == DImode && TARGET_BIG_ENDIAN)
    dst_fmt = "%R0";
  else
    dst_fmt = "%0";

  /* Try movi16: 0~31,movi32: 0~65535.  */
  if (CSKY_CONST_OK_FOR_I (x))
    sprintf (load_op, "movi\t%s, %%1", dst_fmt);
  /* Try exact power of two - 1.  */
  else if (CSKY_CONST_OK_FOR_Uc (x))
    sprintf (load_op, "bmaski\t%s, %%N1", dst_fmt);
  /* Try movih.  */
  else if (CSKY_CONST_OK_FOR_MOVIH (x))
    sprintf (load_op, "movih\t%s, %%H1", dst_fmt);
  else
    {
      sprintf (load_op, "BADMOVI-inline_const %s, %%1", dst_fmt);
      gcc_unreachable ();
    }

  switch (trick_type)
    {
    case IC_SINGLE:
      strcpy (buf, load_op);
      break;
    /* Add instruction 'not'.  */
    case IC_APPEND_NOT:
      sprintf (buf, "%s\n\tnot\t%s, %s\t// %ld 0x%x", load_op, dst_fmt,
               dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'addi'.  */
    case IC_APPEND_ADDI:
      sprintf (buf, "%s\n\taddi\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'subi'.  */
    case IC_APPEND_SUBI:
      sprintf (buf, "%s\n\tsubi\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'addi', the last instruction is bgeni.  */
    case IC_BGENI_ADDI:
      sprintf (buf, "%s\n\taddi\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'subi', the last instruction is bgeni.  */
    case IC_BGENI_SUBI:
      sprintf (buf, "%s\n\tsubi\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'bseti'.  */
    case IC_APPEND_BSETI:
      sprintf (buf, "%s\n\tbseti\t%s, %s, %%P2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'movi'.  */
    case IC_APPEND_MOVI:
      sprintf (buf, "%s\n\tmovi\t%s, %%2\t// %ld 0x%x", load_op, dst_fmt,
               value, (unsigned int)value);
      break;
    /* Add instruction 'bclri'.  */
    case IC_APPEND_BCLRI:
      sprintf (buf, "%s\n\tbclri\t%s, %s, %%Q2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'rotli'.  */
    case IC_APPEND_ROTLI:
      sprintf (buf, "%s\n\trotli\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'lsli'.  */
    case IC_APPEND_LSLI:
      sprintf (buf, "%s\n\tlsli\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'ixh'.  */
    case IC_APPEND_IXH:
      sprintf (buf, "%s\n\tixh\t%s, %s, %s\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    /* Add instruction 'ixw'.  */
    case IC_APPEND_IXW:
      sprintf (buf, "%s\n\tixw\t%s, %s, %s\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, dst_fmt, value, (unsigned int)value);
      break;
    default:
      return "";
    }

  output_asm_insn (buf, out_operands);

  return "";
}


/* The VAL can be generated by shift a 8bit immedate.  */

bool
shiftable_csky_imm8_const (unsigned HOST_WIDE_INT val)
{
  unsigned HOST_WIDE_INT mask = 0xff;
  int i;

  val = val & (unsigned HOST_WIDE_INT) 0xffffffffu;
  if (val == 0)
    return 0;

  for (i = 0; i < 25; i++)
    if ((val & (mask << i)) == val)
      return 1;

  return 0;
}


/* Output a move of a word or less value.  */

const char *
output_csky_move (rtx insn ATTRIBUTE_UNUSED, rtx operands[],
                  enum machine_mode mode ATTRIBUTE_UNUSED)
{
  rtx dst = operands[0];
  rtx src = operands[1];
  struct csky_address op0, op1;

  if (REG_P (dst))
    {
      /* The situation mov reg to reg.  */
      if (REG_P (src))
        {
          int dstreg = REGNO (dst);
          int srcreg = REGNO (src);

          /* hilo registers exchange their places,
             and their order of Dimode as same as other
             general registers in LITTLE_ENDIAN mode.  */
          if (TARGET_BIG_ENDIAN)
            {
              if (dstreg == CSKY_HI_REGNUM)
                return "mthi\t%1";
              else if (dstreg == CSKY_LO_REGNUM)
                return "mtlo\t%1";
              else if (srcreg == CSKY_HI_REGNUM)
                return "mfhi\t%0";
              else if (srcreg == CSKY_LO_REGNUM)
                return "mflo\t%0";
            }
          else
            {
              if (dstreg == CSKY_HI_REGNUM)
                return "mtlo\t%1";
              else if (dstreg == CSKY_LO_REGNUM)
                return "mthi\t%1";
              else if (srcreg == CSKY_HI_REGNUM)
                return "mflo\t%0";
              else if (srcreg == CSKY_LO_REGNUM)
                return "mfhi\t%0";
            }

            if (CSKY_VREG_P (dstreg) && CSKY_VREG_P (srcreg))
              return "fmovs\t%0, %1";
            if (CSKY_VREG_P (dstreg))
              return "fmtvrl\t%0, %1";
            if (CSKY_VREG_P (srcreg))
              return "fmfvrl\t%0, %1";

            if (REGNO (src) == CSKY_CC_REGNUM)
              return "mvc\t%0";
            else
              return "mov\t%0, %1";
        }
      /* The situation mov memory to reg.  */
      else if (GET_CODE (src) == MEM)
        {
          decompose_csky_address (XEXP (src, 0), &op1);

          if (op1.post_inc_reg)
            {
              switch (GET_MODE (src))
                {
                case HImode:
                  return "ldbi.h\t%0, %1";
                case QImode:
                  return "ldbi.b\t%0, %1";
                case SImode:
                case SFmode:
                  return "ldbi.w\t%0, %1";
                case V4QImode:
                case V2HImode:
                  return "ldbi.w\t%0, %1";
                default:
                  gcc_unreachable ();
               }
            }
          else if (op1.index)
            {
              switch (GET_MODE (src))
                {
                case HImode:
                  return "ldr.h\t%0, %1";
                case QImode:
                  return "ldr.b\t%0, %1";
                case V4QImode:
                case V2HImode:
                  return "ldr.w\t%0, %1";
                case SImode:
                case SFmode:
                  if (CSKY_VREG_P (REGNO (dst)))
                    return "fldrs\t%0, %1";
                  else
                    return "ldr.w\t%0, %1";
                default:
                  gcc_unreachable ();
                }
            }
          /* Generate lrw rx, [LABEL], it is happened when compiler generates
             constant pool and use lrw to get the const in memory.  */
          else if (op1.label)
            {
              return "lrw\t%0, %1";
            }
          /* Generate lrs.w rx, [symbol@GOT/PLT].  */
          else if (flag_pic == 1 && op1.disp && GET_CODE (op1.disp) == UNSPEC)
            {
              return "lrs.w\t%0, %1";
            }
          else
            {
              switch (GET_MODE (src))
                {
                case HImode:
                  return "ld.h\t%0, %1";
                case QImode:
                  return "ld.b\t%0, %1";
                case SFmode:
                case SImode:
                  if (CSKY_VREG_P (REGNO (dst)))
                    return "flds\t%0, %1";
                  else
                    return "ld.w\t%0, %1";
                case V4QImode:
                case V2HImode:
                  return "ld.w\t%0, %1";
                default:
                  gcc_unreachable ();
                }
            }
        }
      /* The situation mov integer to reg.  */
      else if (GET_CODE (src) == CONST_INT ||
               (GET_CODE (src) == CONST_DOUBLE && GET_MODE (src) == SFmode))
        {
          HOST_WIDE_INT x, y;
          const REAL_VALUE_TYPE *d;
          long l;

          if (GET_CODE (src) == CONST_DOUBLE && GET_MODE (src) == SFmode)
            {
              d = CONST_DOUBLE_REAL_VALUE (src);
              REAL_VALUE_TO_TARGET_SINGLE (*d, l);
              operands[1] = GEN_INT (l);
              src = operands[1];
            }

          if (try_csky_constant_tricks (INTVAL (src), &x, &y))
            return output_csky_inline_const (SImode, operands);
          /* Return '#' to split it.  */
          else if (CSKY_CONST_OK_FOR_T (INTVAL (src)))
            return "#";
          else
            return "lrw\t%0, %x1\t";
        }
      else if (TARGET_ANCHOR && GET_CODE (src) == SYMBOL_REF)
        {
          if (SYMBOL_REF_FUNCTION_P (src))
            return "lrw\t%0, %1@BTEXT";
          else
            return "lrw\t%0, %1@BDATA";
        }
      else if (GET_CODE (src) == UNSPEC && XINT (src, 1) == PIC_SYMBOL_GRS)
        return "grs\t%0, %1";
      else
        return "lrw\t%0, %1";
    }
  else if (GET_CODE (dst) == MEM)
    {
      decompose_csky_address (XEXP (dst, 0), &op0);

      if (op0.post_inc_reg)
        {
          switch (GET_MODE (src))
            {
            case HImode:
              return "stbi.h\t%1, %0";
            case QImode:
              return "stbi.b\t%1, %0";
            case SFmode:
            case SImode:
              return "stbi.w\t%1, %0";
            case V4QImode:
            case V2HImode:
              return "stbi.w\t%1, %0";
            default:
              gcc_unreachable ();
            }
        }
      else if (op0.index)
        {
          switch (GET_MODE (src))
            {
            case HImode:
              return "str.h\t%1, %0";
            case QImode:
              return "str.b\t%1, %0";
            case V4QImode:
            case V2HImode:
              return "str.w\t%1, %0";
            case SFmode:
            case SImode:
              if (CSKY_VREG_P (REGNO (src)))
                return "fstrs\t%1, %0";
              else
                return "str.w\t%1, %0";
            default:
              gcc_unreachable ();
            }
        }
      switch (GET_MODE (dst))
        {
        case HImode:
          return "st.h\t%1, %0";
        case QImode:
          return "st.b\t%1, %0";
        case SImode:
        case SFmode:
          if (CSKY_VREG_P (REGNO (src)))
            return "fsts\t%1, %0";
          else
            return "st.w\t%1, %0";
        case V4QImode:
        case V2HImode:
          return "st.w\t%1, %0";
        default:
          gcc_unreachable ();
        }
    }

  gcc_unreachable ();
}


/* Output a move of a word or less value.  Specific for ck801.  */

const char *
output_ck801_move (rtx insn ATTRIBUTE_UNUSED, rtx operands[],
                   enum machine_mode mode ATTRIBUTE_UNUSED)
{
  rtx dst = operands[0];
  rtx src = operands[1];

  struct csky_address op1;

  if (REG_P (dst))
    {
      if (REG_P (src))
        {
          return "mov\t%0, %1";
        }
      else if (GET_CODE (src) == MEM)
        {
          decompose_csky_address (XEXP (src, 0), &op1);

          /* Generate lrw rx, [LABEL], it is happened when compiler generates
             constant pool and use lrw to get the const in memory.  */
          if (op1.label)
            {
              return "lrw\t%0, %1";
            }
          else
            {
              switch (GET_MODE (src))
              {
              case HImode:
                return "ld.h\t%0, %1";
              case QImode:
                return "ld.b\t%0, %1";
              case SFmode:
              case SImode:
                return "ld.w\t%0, %1";
              default:
                gcc_unreachable ();
              }
            }
        }
      else if (GET_CODE (src) == CONST_INT)
        {
          if (REGNO (dst) <= 7)
            {
              if (CSKY_CONST_OK_FOR_N (INTVAL (src) + 1))
                return "movi\t%0, %1";
              /* Return '#' to split it.  */
              else if (CSKY_CONST_OK_FOR_T (INTVAL (src)))
                return "#";
              else if (shiftable_csky_imm8_const (INTVAL (src)))
                return "#";
              else
                return "lrw\t%0, %x1\t";
            }
          else
            return "lrw\t%0, %x1\t";
        }
      else if (GET_CODE (src) == CONST_DOUBLE && GET_MODE (src) == SFmode)
        {
          const REAL_VALUE_TYPE *d;
          long l;

          d = CONST_DOUBLE_REAL_VALUE (src);
          REAL_VALUE_TO_TARGET_SINGLE (*d, l);
          operands[1] = GEN_INT (l);
          src = operands[1];

          if (CSKY_CONST_OK_FOR_N (INTVAL (src) + 1))
            return "movi\t%0, %1";
          else
            return "lrw\t%0, %x1\t";
        }
      else if (TARGET_ANCHOR && GET_CODE (src) == SYMBOL_REF)
        {
          if (SYMBOL_REF_FUNCTION_P (src))
            return "lrw\t%0, %1@BTEXT";
          else
            return "lrw\t%0, %1@BDATA";
        }
      else
        return "lrw\t%0, %1";
    }
  else if (GET_CODE (dst) == MEM)
    {
      switch (GET_MODE (dst))
        {
        case HImode:
          return "st.h\t%1, %0";
        case QImode:
          return "st.b\t%1, %0";
        case SImode:
        case SFmode:
          return "st.w\t%1, %0";
        default:
          gcc_unreachable ();
        }
    }

  gcc_unreachable ();
}


/* Return a sequence of instructions to perform DI or DF move.
   Since the CSKY cannot move a DI or DF in one instruction, we have
   to take care when we see overlapping source and dest registers.  */

const int get_output_csky_movedouble_length(rtx operands[])
{
  rtx dst = operands[0];
  rtx src = operands[1];

  if (REG_P (dst))
    {
      if (REG_P (src))
        {
          int dstreg = REGNO (dst);
          int srcreg = REGNO (src);

          if (CSKY_VREG_P (srcreg) && CSKY_VREG_P (dstreg))
            return 4;
          else
            return 8;
        }
      else if (GET_CODE (src) == MEM)
        {
          rtx memexp = XEXP (src, 0);
          int dstreg = REGNO (dst);
          int basereg = -1;
          struct csky_address op0;
          decompose_csky_address (XEXP (src, 0), &op0);

          if (GET_CODE (memexp) == LABEL_REF)
            return 8;
          if (CSKY_VREG_P (dstreg))
            return 4;
          return 8;
        }
      else if (GET_CODE (src) == CONST_INT || GET_CODE (src) == CONST_DOUBLE)
        {
          split_double (src, operands + 2, operands + 3);
          if (CSKY_CONST_OK_FOR_N (INTVAL (operands[2]) + 1)
              && CSKY_CONST_OK_FOR_N (INTVAL (operands[3]) + 1)
              && REGNO (operands[0]) < 6)
            return 4;
          else
            return 8;
        }
    }
  else if (GET_CODE (dst) == MEM && GET_CODE (src) == REG)
    {
      rtx memexp = XEXP (dst, 0);
      int srcreg = REGNO (src);
      int offset = -1;
      if (CSKY_VREG_P (srcreg))
        return 4;

      if (GET_CODE (memexp) == REG)
        offset = 0;
      else if (GET_CODE (memexp) == PLUS)
        {
          if (GET_CODE (XEXP (memexp, 0)) == REG)
            offset = INTVAL (XEXP (memexp, 1));
          else if (GET_CODE (XEXP (memexp, 1)) == REG)
            offset = INTVAL (XEXP (memexp, 0));
          else
            gcc_unreachable ();
        }
      else
        gcc_unreachable ();

      if (srcreg <= 6 && offset <= 1020)
        return 4;
      else if ((srcreg == 7 && offset <= 1024) || (srcreg <= 7 && offset == 1024))
        return 6;
      else
        return 8;
    }
  else
    gcc_unreachable ();
}

const char *
output_csky_movedouble (rtx operands[],
                        enum machine_mode mode ATTRIBUTE_UNUSED)
{
  rtx dst = operands[0];
  rtx src = operands[1];

  if (REG_P (dst))
    {
      if (REG_P (src))
        {
          int dstreg = REGNO (dst);
          int srcreg = REGNO (src);

          if (CSKY_HILO_REG_P (srcreg))
            {
              if (TARGET_BIG_ENDIAN)
                return "mfhi\t%0\n\tmflo\t%R0";
              else
                return "mfhi\t%R0\n\tmflo\t%0";
            }
          else if (CSKY_HILO_REG_P (dstreg))
            {
              if (TARGET_BIG_ENDIAN)
                return "mthi\t%1\n\tmtlo\t%R1";
              else
                return "mthi\t%R1\n\tmtlo\t%1";
            }
          else if (CSKY_VREG_P (srcreg) && CSKY_VREG_P (dstreg))
            {
              return "fmovd\t%0, %1";
            }
          else if (CSKY_VREG_P (srcreg))
            {
              /* Since the vector registers in fpuv2_soft like ck803f
                 are 32bits width, it just need one insn to complete the
                 move operator.  */
              if (TARGET_SINGLE_FPU)
                {
                  return "fmfvrl\t%0, %1";
                }
              else
                {
                  if (TARGET_BIG_ENDIAN)
                    return "fmfvrh\t%0, %1\n\tfmfvrl\t%R0, %1";
                  else
                    return "fmfvrh\t%R0, %1\n\tfmfvrl\t%0, %1";
                }
            }
          else if (CSKY_VREG_P (dstreg))
            {
              if (TARGET_SINGLE_FPU)
                {
                  return "fmtvrl\t%0, %1";
                }
              else
                {
                  if (TARGET_BIG_ENDIAN)
                    return "fmtvrh\t%0, %1\n\tfmtvrl\t%0, %R1";
                  else
                    return "fmtvrh\t%0, %R1\n\tfmtvrl\t%0, %1";
                }
            }

          /* Ensure the second source not overwritten.  */
          if (srcreg + 1 == dstreg)
            return "mov\t%R0, %R1\n\tmov\t%0, %1";
          else
            return "mov\t%0, %1\n\tmov\t%R0, %R1";
        }
      else if (GET_CODE (src) == MEM)
        {
          rtx memexp = XEXP (src, 0);
          int dstreg = REGNO (dst);
          int basereg = -1;
          struct csky_address op0;

          decompose_csky_address (XEXP (src, 0), &op0);

          if (GET_CODE (memexp) == LABEL_REF)
            return "lrw\t%0, [%1]\n\tlrw\t%R0, [%R1]";
          else if (GET_CODE (memexp) == REG)
            basereg = REGNO (memexp);
          else if (GET_CODE (memexp) == PLUS)
            {
              if (GET_CODE (XEXP (memexp, 0)) == REG)
                basereg = REGNO (XEXP (memexp, 0));
              else if (GET_CODE (XEXP (memexp, 1)) == REG)
                basereg = REGNO (XEXP (memexp, 1));
              else
                gcc_unreachable ();
            }
          else
            gcc_unreachable ();


          /* When FPUV2.  */
          if (CSKY_VREG_P (dstreg))
            {
              if (op0.index)
                return "fldrd\t%0, %1";
              else
                return "fldd\t%0, %1";
            }
          /* FIXME length attribute is wrong here.  */
          if (dstreg == basereg)
            {
              /* Just load them in reverse order.  */
              return "ld.w\t%R0, %R1\n\tld.w\t%0, %1";
            }
          else
            return "ld.w\t%0, %1\n\tld.w\t%R0, %R1";
        }
      else if (GET_CODE (src) == CONST_INT || GET_CODE (src) == CONST_DOUBLE)
        {
          split_double (src, operands + 2, operands + 3);

          if (CSKY_CONST_OK_FOR_I (INTVAL (operands[2])))
            output_asm_insn ("movi\t%0, %2", operands);
          else if (CSKY_CONST_OK_FOR_Uc (INTVAL (operands[2])))
            output_asm_insn ("bmaski\t%0, %N2", operands);
          else if (CSKY_CONST_OK_FOR_Ub (INTVAL (operands[2])))
            output_asm_insn ("bgeni\t%0, %P2", operands);
          else
            output_asm_insn ("lrw\t%0, %2", operands);

          if (CSKY_CONST_OK_FOR_I (INTVAL (operands[3])))
            output_asm_insn ("movi\t%R0, %3", operands);
          else if (CSKY_CONST_OK_FOR_Uc (INTVAL (operands[3])))
            output_asm_insn ("bmaski\t%R0, %N3", operands);

          else if (CSKY_CONST_OK_FOR_Ub (INTVAL (operands[3])))
            output_asm_insn ("bgeni\t%R0, %P3", operands);
          else
            output_asm_insn ("lrw\t%R0, %3", operands);

          return "";
        }
      else
        gcc_unreachable ();
    }
  else if (GET_CODE (dst) == MEM && GET_CODE (src) == REG)
    {
      rtx memexp = XEXP (dst, 0);
      int srcreg = REGNO (src);
      int basereg = -1;
      struct csky_address op0;

      decompose_csky_address (XEXP (dst, 0), &op0);

      if (GET_CODE (memexp) == REG)
        basereg = REGNO (memexp);
      else if (GET_CODE (memexp) == PLUS)
        {
          if (GET_CODE (XEXP (memexp, 0)) == REG)
            basereg = REGNO (XEXP (memexp, 0));
          else if (GET_CODE (XEXP (memexp, 1)) == REG)
            basereg = REGNO (XEXP (memexp, 1));
          else
            gcc_unreachable ();
        }
      else
        gcc_unreachable ();

      /* When FPUV2.  */
      if (CSKY_VREG_P (srcreg))
        {
          if (op0.index)
            return "fstrd\t%1, %0";
          else
            return "fstd\t%1, %0";
        }
      /* FIXME length attribute is wrong here.  */
      if (srcreg == basereg)
        {
          /* Just load them in reverse order.  */
          return "st.w\t%R1, %R0\n\tst.w\t%1, %0";
        }
      else
        return "st.w\t%1, %0\n\tst.w\t%R1, %R0";
    }
  else
    gcc_unreachable ();
}


const char *
output_ck801_movedouble (rtx operands[],
                         enum machine_mode mode ATTRIBUTE_UNUSED)
{
  rtx dst = operands[0];
  rtx src = operands[1];

  if (REG_P (dst))
    {
      if (REG_P (src))
        {
          int dstreg = REGNO (dst);
          int srcreg = REGNO (src);

          /* Ensure the second source not overwritten.  */
          if (srcreg + 1 == dstreg)
            return "mov\t%R0, %R1\n\tmov\t%0, %1";
          else
            return "mov\t%0, %1\n\tmov\t%R0, %R1";
        }
      else if (GET_CODE (src) == MEM)
        {
          rtx memexp = XEXP (src, 0);
          int dstreg = REGNO (dst);
          int basereg = -1;
          struct csky_address op0;

          decompose_csky_address (XEXP (src, 0), &op0);

          if (GET_CODE (memexp) == LABEL_REF
              || GET_CODE (memexp) == CONST)
            return "lrw\t%0, %1\n\tlrw\t%R0, %R1";
          else if (GET_CODE (memexp) == REG)
            basereg = REGNO (memexp);
          else if (GET_CODE (memexp) == PLUS)
            {
              if (GET_CODE (XEXP (memexp, 0)) == REG)
                basereg = REGNO (XEXP (memexp, 0));
              else if (GET_CODE (XEXP (memexp, 1)) == REG)
                basereg = REGNO (XEXP (memexp, 1));
              else
                gcc_unreachable ();
            }
          else
            gcc_unreachable ();

          /* FIXME length attribute is wrong here.  */
          if (dstreg == basereg)
            {
              /* Just load them in reverse order.  */
              return "ld.w\t%R0, %R1\n\tld.w\t%0, %1";
            }
          else
            return "ld.w\t%0, %1\n\tld.w\t%R0, %R1";
        }
      else if (GET_CODE (src) == CONST_INT || GET_CODE (src) == CONST_DOUBLE)
        {
          split_double (src, operands + 2, operands + 3);

          if (REGNO (dst) <= 7
              && CSKY_CONST_OK_FOR_N (INTVAL (operands[2]) + 1))
            output_asm_insn ("movi\t%0, %2", operands);
          else
            output_asm_insn ("lrw\t%0, %2", operands);


          if (REGNO (dst) <= 6 && CSKY_CONST_OK_FOR_N (INTVAL (operands[3]) + 1))
            output_asm_insn ("movi\t%R0, %3", operands);
          else
            output_asm_insn ("lrw\t%R0, %3", operands);

          return "";


        }
      else
        gcc_unreachable ();
    }
  else if (GET_CODE (dst) == MEM && GET_CODE (src) == REG)
    {
      rtx memexp = XEXP (dst, 0);
      int srcreg = REGNO (src);
      int basereg = -1;
      struct csky_address op0;

      decompose_csky_address (XEXP (dst, 0), &op0);

      if (GET_CODE (memexp) == REG)
        basereg = REGNO (memexp);
      else if (GET_CODE (memexp) == PLUS)
        {
          if (GET_CODE (XEXP (memexp, 0)) == REG)
            basereg = REGNO (XEXP (memexp, 0));
          else if (GET_CODE (XEXP (memexp, 1)) == REG)
            basereg = REGNO (XEXP (memexp, 1));
          else
            gcc_unreachable ();
        }
      else
        gcc_unreachable ();

      /* FIXME length attribute is wrong here.  */
      if (srcreg == basereg)
        {
          /* Just load them in reverse order.  */
          return "st.w\t%R1, %R0\n\tst.w\t%1, %0";
        }
      else
        return "st.w\t%1, %0\n\tst.w\t%R1, %R0";
    }
  else
    gcc_unreachable ();
}


/* Transform UP into lowercase and write the result to LO.
   You must provide enough space for LO.  Return LO.  */

char *
csky_tolower (char *lo, const char *up)
{
  char *lo0 = lo;

  for (; *up; up++, lo++)
    *lo = TOLOWER (*up);

  *lo = '\0';

  return lo0;
}


/* TODO this symbolic judge makes the scope too wide.  */
int
symbolic_csky_address_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case SYMBOL_REF:
    case LABEL_REF:
      return 1;
    case CONST:
      x = XEXP (x, 0);
      return ((GET_CODE (XEXP (x, 0)) == SYMBOL_REF
               || GET_CODE (XEXP (x, 0)) == LABEL_REF)
              && GET_CODE (XEXP (x, 1)) == CONST_INT);
    default:
      return 0;
    }
}


/* Generate compare rtl insn for comparison instruction.
   Retrun true if the comparison CODE has turn to negative
   side. For example, it will return ture when LEU turns
   to GTU.  */

bool
gen_csky_compare (enum rtx_code code, rtx op0, rtx op1)
{
  bool invert;  /* Return this value to declare whether the
                   comparison CODE has turn to negative side.  */
  rtx cc_reg = gen_rtx_REG (CCmode, CSKY_CC_REGNUM);

  if (GET_CODE (op1) == CONST_INT)
    {
      HOST_WIDE_INT val = INTVAL (op1);

      switch (code)
        {
        case GTU:
          /* Unsigned (GTU 0) is the same as (NE 0); everything else is converted
             below to LEU (reversed cmphs).  */
          if (val == 0)
            code = NE;
          /* Check whether (GTU A imm) can become (GEU A  imm + 1).  */
          else
            if (((CSKY_TARGET_ARCH(CK801) || CSKY_ISA_FEATURE(smart))
                 && CSKY_CONST_OK_FOR_J (val + 1))
                || (!(CSKY_TARGET_ARCH(CK801) && !CSKY_ISA_FEATURE(smart))
                    && CSKY_CONST_OK_FOR_Uk (val + 1)))
            {
              op1 = GEN_INT (val + 1);
              code = GEU;
            }
          break;
        /* Check whether (LE A imm) can become (LT A imm + 1),
           or (GT A imm) can become (GE A imm + 1).  */
        case GT:
        case LE:
          if (((CSKY_TARGET_ARCH(CK801) || CSKY_ISA_FEATURE(smart))
               && CSKY_CONST_OK_FOR_J (val + 1))
              || (!CSKY_TARGET_ARCH(CK801) && !CSKY_ISA_FEATURE(smart)
                  && CSKY_CONST_OK_FOR_Uk (val + 1)))
            {
              op1 = GEN_INT (val + 1);
              code = code == LE ? LT : GE;
            }
          break;

        default:
          break;
        }
    }

  if (CONSTANT_P (op1) && GET_CODE (op1) != CONST_INT)
    op1 = force_reg (GET_MODE (op1), op1);

  /* cmpnei: 0-31 (K immediate)
     ti: 1-32 (J immediate, 0 using btsti x,31).  */
  invert = false;
  switch (code)
    {
      /* Use inverted condition, cmpne.  */
      case EQ:
        code = NE;
        invert = true;
      /* Use normal condition, cmpne.  */
      case NE:
        if (GET_CODE (op1) == CONST_INT
            && (((CSKY_TARGET_ARCH(CK801) || CSKY_ISA_FEATURE(smart))
                 && !csky_literal_K_operand (op1, SImode))
                || ((!CSKY_TARGET_ARCH(CK801) && !CSKY_ISA_FEATURE(smart))
                    && !csky_literal_I_operand (op1, SImode))))
          op1 = force_reg (SImode, op1);
      break;

      /* Use inverted condition, reversed cmplt.  */
      case LE:
        code = GT;
        invert = true;
      /* Use normal condition, reversed cmplt.  */
      case GT:
        if (GET_CODE (op1) == CONST_INT)
          op1 = force_reg (SImode, op1);
      break;

      /* Use inverted condition, cmplt.  */
      case GE:
        code = LT;
        invert = true;
      /* Use normal condition, cmplt.  */
      case LT:
        /* covered by btsti x,31.  */
        if (GET_CODE (op1) == CONST_INT && INTVAL (op1) != 0)
          {
            if (((CSKY_TARGET_ARCH(CK801) || CSKY_ISA_FEATURE(smart))
                 && !csky_literal_J_operand (op1, SImode))
                || ((!CSKY_TARGET_ARCH(CK801) && !CSKY_ISA_FEATURE(smart))
                    && !csky_literal_Uk_operand (op1, SImode)))
              {
                op1 = force_reg (SImode, op1);
              }
          }
        break;

      /* Use inverted condition, cmple.  */
      case GTU:
        /* We coped with unsigned > 0 above.  */
        gcc_assert (GET_CODE (op1) != CONST_INT || INTVAL (op1) != 0);
        code = LEU;
        invert = true;
      /* Use normal condition, reversed cmphs.  */
      case LEU:
        if (GET_CODE (op1) == CONST_INT && INTVAL (op1) != 0)
          op1 = force_reg (SImode, op1);
        break;

      /* Use inverted condition, cmphs.  */
      case LTU:
        code = GEU;
        invert = true;
      /* Use normal condition, cmphs.  */
      case GEU:
        if (GET_CODE (op1) == CONST_INT && INTVAL (op1) != 0)
          {
            if (((CSKY_TARGET_ARCH(CK801) || CSKY_ISA_FEATURE(smart))
                 && !csky_literal_J_operand (op1, SImode))
                || ((!CSKY_TARGET_ARCH(CK801) && !CSKY_ISA_FEATURE(smart))
                    && !csky_literal_Uk_operand (op1, SImode)))
              {
                op1 = force_reg (SImode, op1);
              }
          }
      break;

    default:
      break;
    }

  emit_insn (gen_rtx_SET (cc_reg,
                          gen_rtx_fmt_ee (code, CCmode, op0, op1)));
  return invert;
}


const char *
output_csky_return_instruction(void)
{
  unsigned long func_type = get_csky_current_func_type();

  if (CSKY_FUNCTION_IS_NAKED(func_type))
    return "";

  csky_stack_frame fi;
  get_csky_frame_layout(&fi);
  if (!TARGET_BACKTRACE && TARGET_PUSHPOP
      && is_pushpop_from_csky_live_regs(fi.reg_mask)
      && fi.arg_size == 0 && !CSKY_FUNCTION_IS_INTERRUPT(func_type))
    return "";

  if (CSKY_FUNCTION_IS_INTERRUPT(func_type))
    {
      if (TARGET_SINGLE_FPU)
        {
          asm_fprintf (asm_out_file, "\tfldms\tvr0-vr7, (sp)\n");
          asm_fprintf (asm_out_file, "\taddi\tsp, 32\n");
        }
      else if (TARGET_DOUBLE_FPU)
        {
          asm_fprintf (asm_out_file, "\tfldmd\tvr0-vr7, (sp)\n");
          asm_fprintf (asm_out_file, "\taddi\tsp, 64\n");
        }
      if (CSKY_ISA_FEATURE(hreg))
        {
          asm_fprintf (asm_out_file, "\tldm\tr18-r31, (sp)\n");
          asm_fprintf (asm_out_file, "\taddi\tsp, 56\n");
        }
      return "ipop\n\tnir\n";
    }
  else
    return "rts\n";
}


static bool is_pushpop_from_csky_live_regs(int mask)
{
  int i, num_regs;
  int end_reg = -1;

  for (i = 0, num_regs = 0; i <= 32; i++)
    if(mask & (1 << i))
      num_regs++;

  if(num_regs == 0)
    return false;

  for(i = 11; i >= 4; i--)
    {
      if (end_reg == -1 && (mask & (1 << i)))
        end_reg = i;

      if ((end_reg != -1) && !(mask & (1 << i)))
        return false;
    }

  end_reg = -1;
  for(i = 17; i >= 16; i--)
    {
      if (end_reg == -1 && (mask & (1 << i)))
        end_reg = i;

      if ((end_reg != -1) && !(mask & (1 << i)))
        return false;
    }

  for(i = 0; i <= 3; i++)
    if ((mask & (1 << i)))
      return false;

  for(i = 12; i <= 14; i++)
    if ((mask & (1 << i)))
      return false;

  /* r15 in the list */

  for(i = 18; i <= 27; i++)
    if ((mask & (1 << i)))
      return false;

  /* r28 in the list */

  for(i = 29; i <= 31; i++)
    if ((mask & (1 << i)))
      return false;

  return true;
}

/* FIXME debug information should be added in this function. */
/* Adjust the stack and return the number of bytes taken to do it
    for targer v2.  */

static void
expand_csky_stack_adjust (int direction, int size)
{
  rtx insn;

  /* FIXME 810 can use movih and ori to replace lrw to improve
     performance.  */
  /* Use lrw & add or sub insn to adjust stack when the adjust
     size cannot be handled by to addi or subi insn.  */
  if (size > CSKY_ADDI_MAX_STEP * 2)
    {
      struct csky_stack_frame fi;

      get_csky_frame_layout (&fi);

      if (fi.reg_size != 0)
        {
          rtx tmp;
          rtx dwarf;

          if (!(fi.reg_mask & (1 << 4)))
            df_set_regs_ever_live (4, true);

          tmp = gen_rtx_REG (SImode, 4);
          insn = emit_insn (gen_movsi (tmp, GEN_INT (size)));

          if (direction > 0)
            {
              insn = gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx, tmp);
              dwarf = gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx,
                                  GEN_INT (size));
            }
          else
            {
              insn = gen_subsi3 (stack_pointer_rtx, stack_pointer_rtx, tmp);
              dwarf = gen_subsi3 (stack_pointer_rtx, stack_pointer_rtx,
                                  GEN_INT (size));
            }

          insn = emit_insn (insn);
          add_reg_note (insn, REG_FRAME_RELATED_EXPR, dwarf);
          RTX_FRAME_RELATED_P (insn) = 1;
        }
    }
  /* Use one or two addi or subi insn to adjust stack.  */
  else
    {
      if (direction > 0 && size > CSKY_ADDI_MAX_STEP)
        {
          rtx tmp = GEN_INT (CSKY_ADDI_MAX_STEP);

          do
            {
              insn = emit_insn (gen_addsi3 (stack_pointer_rtx,
                                            stack_pointer_rtx,
                                            tmp));
              RTX_FRAME_RELATED_P (insn) = 1;
              size -= CSKY_ADDI_MAX_STEP;
            }
          while (size > CSKY_ADDI_MAX_STEP);
        }

      if (direction < 0 && size > CSKY_SUBI_MAX_STEP)
        {
          rtx tmp = GEN_INT (CSKY_SUBI_MAX_STEP);

          do
            {
              insn = emit_insn (gen_subsi3 (stack_pointer_rtx,
                                            stack_pointer_rtx,
                                            tmp));
              RTX_FRAME_RELATED_P (insn) = 1;
              size -= CSKY_SUBI_MAX_STEP;
            }
          while (size > CSKY_SUBI_MAX_STEP);
        }

      if (size)
        {
          rtx insn;
          rtx val = GEN_INT (size);

          if (direction > 0)
            insn = gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx, val);
          else
            insn = gen_subsi3 (stack_pointer_rtx, stack_pointer_rtx, val);

          insn = emit_insn (insn);
          RTX_FRAME_RELATED_P (insn) = 1;
        }
    }
}


/* Generate and emit an insn that we will recognize as a push_multi.
   Unfortunately, since this insn does not reflect very well the actual
   semantics of the operation, we need to annotate the insn for the benefit
   of DWARF2 frame unwind information.  DWARF_REGS_MASK is a subset of
   MASK for registers that should be annotated for DWARF2 frame unwind
   information.  */

static rtx
emit_csky_regs_push (unsigned long mask)
{
  int num_regs = 0;
  int i, j;
  rtx par;
  rtx dwarf;
  int dwarf_par_index;
  rtx tmp, reg;

  for (i = 0; i < CSKY_NGPR_REGS; i++)
    {
      if (mask & (1 << i))
        num_regs++;
    }

  /* The reg range for push is:r4-r11,r15-r17,r28.  */
  gcc_assert (num_regs && num_regs <= 12);

  /* For the body of the insn we are going to generate an UNSPEC in
     parallel with several USEs.  This allows the insn to be recognized
     by the push_multi pattern in the arm.md file.

     The body of the insn looks something like this:

       (parallel [
           (set (mem:BLK (pre_modify:SI (reg:SI sp)
                                        (const_int:SI <num>)))
                (unspec:BLK [(reg:SI r4)] UNSPEC_PUSHPOP_MULT))
           (use (reg:SI XX))
           (use (reg:SI YY))
           ...
        ])

     For the frame note however, we try to be more explicit and actually
     show each register being stored into the stack frame, plus a (single)
     decrement of the stack pointer.  We do it this way in order to be
     friendly to the stack unwinding code, which only wants to see a single
     stack decrement per instruction.  The RTL we generate for the note looks
     something like this:

      (sequence [
           (set (reg:SI sp) (plus:SI (reg:SI sp) (const_int -20)))
           (set (mem:SI (reg:SI sp)) (reg:SI r4))
           (set (mem:SI (plus:SI (reg:SI sp) (const_int 4))) (reg:SI XX))
           (set (mem:SI (plus:SI (reg:SI sp) (const_int 8))) (reg:SI YY))
           ...
        ])

     FIXME:: In an ideal world the PRE_MODIFY would not exist and
     instead we'd have a parallel expression detailing all
     the stores to the various memory addresses so that debug
     information is more up-to-date. Remember however while writing
     this to take care of the constraints with the push instruction.

     Note also that this has to be taken care of for the VFP registers.

     For more see PR43399.  */

  par = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (num_regs));
  dwarf = gen_rtx_SEQUENCE (VOIDmode, rtvec_alloc (num_regs + 1));
  dwarf_par_index = 1;

  for (i = 0; i < CSKY_NGPR_REGS; i++)
    {
      if (mask & (1 << i))
        {
          reg = gen_rtx_REG (SImode, i);

          XVECEXP (par, 0, 0)
            = gen_rtx_SET (gen_frame_mem
                           (BLKmode,
                            gen_rtx_PRE_MODIFY (Pmode,
                                                stack_pointer_rtx,
                                                plus_constant
                                                (Pmode, stack_pointer_rtx,
                                                 -4 * num_regs))
                            ),
                           gen_rtx_UNSPEC (BLKmode,
                                           gen_rtvec (1, reg),
                                           UNSPEC_PUSHPOP_MULT));

          tmp = gen_rtx_SET (gen_frame_mem (SImode, stack_pointer_rtx),
                             reg);
          RTX_FRAME_RELATED_P (tmp) = 1;
          XVECEXP (dwarf, 0, dwarf_par_index++) = tmp;

          break;
        }
    }

  for (j = 1, i++; j < num_regs; i++)
    {
      if (mask & (1 << i))
        {
          reg = gen_rtx_REG (SImode, i);

          XVECEXP (par, 0, j) = gen_rtx_USE (VOIDmode, reg);

          tmp
            = gen_rtx_SET (gen_frame_mem
                           (SImode,
                            plus_constant (Pmode, stack_pointer_rtx,
                                           4 * j)),
                           reg);
          RTX_FRAME_RELATED_P (tmp) = 1;
          XVECEXP (dwarf, 0, dwarf_par_index++) = tmp;

          j++;
        }
    }

  par = emit_insn (par);

  tmp = gen_rtx_SET (stack_pointer_rtx,
                     plus_constant (Pmode, stack_pointer_rtx, -4 * num_regs));
  RTX_FRAME_RELATED_P (tmp) = 1;
  XVECEXP (dwarf, 0, 0) = tmp;

  add_reg_note (par, REG_FRAME_RELATED_EXPR, dwarf);
  RTX_FRAME_RELATED_P (par) = 1;

  return par;
}


/* Generate and emit an insn pattern that we will recognize as a pop_multi.
   SAVED_REGS_MASK shows which registers need to be restored.

   Unfortunately, since this insn does not reflect very well the actual
   semantics of the operation, we need to annotate the insn for the benefit
   of DWARF2 frame unwind information.  */
/* FIXME is the debug information should be added in epilogue?  */

static void
emit_csky_regs_pop (unsigned long mask)
{
  int num_regs = 0;
  int i, j;
  rtx par;
  rtx tmp, reg;

  for (i = 0; i < CSKY_NGPR_REGS; i++)
    {
      if (mask & (1 << i))
        num_regs++;
    }

  /* The reg range for push is:r4-r11,r15-r17,r28.  */
  gcc_assert (num_regs && num_regs <= 12);

  /* The first element is (return),
     the second element is
       (set (reg:SI 'first reg number')
            (unspec:SI [(mem)] UNSPEC_PUSHPOP_MULT),
     the rest elements is (use (reg:SI 'rest reg number')),
     so the length should be number of register to be poped
     plus one.  */
  par = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (num_regs + 1));

  XVECEXP (par, 0, 0) = ret_rtx;

  for (i = 0; i < CSKY_NGPR_REGS; i++)
    {
      if (mask & (1 << i))
        {
          reg = gen_rtx_REG (SImode, i);
          tmp = gen_frame_mem
            (SImode,
             gen_rtx_POST_MODIFY (Pmode,
                                  stack_pointer_rtx,
                                  plus_constant (Pmode, stack_pointer_rtx,
                                                 4 * num_regs)));

          XVECEXP (par, 0, 1)
            = gen_rtx_SET (reg,
                           gen_rtx_UNSPEC (SImode,
                                           gen_rtvec (1, tmp),
                                           UNSPEC_PUSHPOP_MULT));

          break;
        }
    }

  for (j = 2, i++; j < (num_regs + 1); i++)
    {
      if (mask & (1 << i))
        {
          reg = gen_rtx_REG (SImode, i);

          XVECEXP (par, 0, j) = gen_rtx_USE (VOIDmode, reg);

          j++;
        }
    }

  par = emit_jump_insn (par);
}

enum reg_type {
  GENERAL_REG,
  VECTOR_REG
};

enum mov_type {
  LOAD_STACK,
  STORE_STACK
};

/* Generate series stack load or store rtl in prologue and
   epilogue, the REMAIN is the total reg size to load or
   store, the REG_MASK indicates which regs, the OFFSET_P
   is the first offset to stack, AREG_TYPE indicates the
   reg class, and AMOV_TYPE distinguish load or store.  */

static void
emit_series_stack_ldst (int remain,
                        int reg_mask,
                        int *offset_p,
                        enum reg_type areg_type,
                        enum mov_type amov_type)
{
  int rn, rn_load;
  int offset = *offset_p;
  machine_mode mode;
  int regnumber_offset;
  int step;
  rtx insn;

  if (areg_type == GENERAL_REG)
    {
      mode = SImode;
      regnumber_offset = 0;
      step = 4;
      rn = -1;
      rn_load = 31;
    }
  else if (areg_type == VECTOR_REG)
    {
      if (CSKY_ISA_FEATURE(vdsp128))
        mode = V4SImode;
      else if (CSKY_ISA_FEATURE(vdsp64))
        mode = V2SImode;
      else
        mode = (csky_fpu_index == TARGET_FPU_fpv2_sf ? SFmode : DFmode);
      regnumber_offset = -CSKY_FIRST_VFP_REGNUM;
      step = (CSKY_ISA_FEATURE(vdsp128) ? 16 :
        (csky_fpu_index == TARGET_FPU_fpv2_sf ? 4 : 8));
      rn = CSKY_FIRST_VFP_REGNUM - 1;
      rn_load = CSKY_LAST_VFP_REGNUM + 1;
    }
  else
    {
      abort ();
    }
  if (amov_type == STORE_STACK)
    {
      for (; remain > 0; offset += step, remain -= step)
        {
          while (!(reg_mask & (1 << (++rn + regnumber_offset))));

          rtx dst = gen_rtx_MEM (mode,
                                 plus_constant (Pmode,
                                                stack_pointer_rtx,
                                                offset));
          insn = emit_insn (gen_movsi (dst, gen_rtx_REG (mode, rn)));
          RTX_FRAME_RELATED_P (insn) = 1;
        }
    }
  else if (amov_type == LOAD_STACK)
    {
      for (offset -= step;
           remain > 0;
           offset -= step, remain -= step)
        {
          while (!(reg_mask & (1 << (--rn_load + regnumber_offset))));

          rtx src = gen_rtx_MEM (mode,
                                 plus_constant (Pmode,
                                                stack_pointer_rtx,
                                                offset));
          emit_insn (gen_movsi (gen_rtx_REG (mode, rn_load), src));
        }
    }
  else
    {
      abort ();
    }
  *offset_p = offset;

  return;
}

void csky_expand_prologue(void)
{
  rtx insn;
  int offset = 0;
  unsigned long func_type = get_csky_current_func_type();

  if (CSKY_FUNCTION_IS_NAKED(func_type))
    {
      if (flag_stack_usage_info)
        current_function_static_stack_size = 0;
      return;
    }

  csky_stack_frame fi;
  get_csky_frame_layout(&fi);

  if (fi.arg_size != 0)
    {
      offset = fi.arg_size + fi.pad_arg;
      insn = emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                                  GEN_INT(-offset)));
      RTX_FRAME_RELATED_P (insn) = 1;
    }

  /* If we have a parameter passed partially in regs and partially in memory,
     the registers will have been stored to memory already in function.c.  So
     we only need to do something here for varargs functions.  */
  if (fi.arg_size != 0 && crtl->args.pretend_args_size == 0)
    {
      int rn = CSKY_FIRST_PARM_REG + CSKY_NPARM_REGS - 1;
      int remain = fi.arg_size;

      for (offset -= 4; remain >= 4; offset -= 4, rn--, remain -= 4)
        {
          rtx dst = gen_rtx_MEM (SImode,
                                 plus_constant (Pmode,
                                                stack_pointer_rtx,
                                                offset));
          insn = emit_insn (gen_movsi (dst, gen_rtx_REG (SImode, rn)));
          RTX_FRAME_RELATED_P (insn) = 1;
        }
    }

  if (TARGET_BACKTRACE)
    {
      int remain_loc_reg = fi.reg_size - fi.freg_size;
      int remain_lr_fp = 0;
      int loc_reg_mask = fi.reg_mask;
      int lr_fp_mask = 0;
      int remain;
      int rn;

      if (fi.reg_mask & (1 << HARD_FRAME_POINTER_REGNUM))
        {
          remain_loc_reg -= 4;
          remain_lr_fp += 4;
          loc_reg_mask &= ~(1 << HARD_FRAME_POINTER_REGNUM);
          lr_fp_mask |= (1 << HARD_FRAME_POINTER_REGNUM);
        }
      if (fi.reg_mask & (1 << CSKY_LR_REGNUM))
        {
          remain_loc_reg -= 4;
          remain_lr_fp += 4;
          loc_reg_mask &= ~(1 << CSKY_LR_REGNUM);
          lr_fp_mask |= (1 << CSKY_LR_REGNUM);
        }

      if (remain_loc_reg > 4 && is_pushpop_from_csky_live_regs (loc_reg_mask))
        {
          emit_csky_regs_push (loc_reg_mask);
          offset = fi.reg_size + fi.pad_reg - fi.freg_size - remain_loc_reg;
          gcc_assert (offset > 0);

          insn = emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                                      GEN_INT(-offset)));
          RTX_FRAME_RELATED_P (insn) = 1;
        }
      else
        {
          offset = fi.reg_size + fi.pad_reg - fi.freg_size;

          /* FIXME Add the condition of greater than zero is to
             avoid internal error when add -flto, deep reasons
             to be examined.  */
          if (offset > 0)
          {
            insn = emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                                        GEN_INT(-offset)));
            RTX_FRAME_RELATED_P (insn) = 1;
          }
        }

      offset = 0;
      emit_series_stack_ldst (remain_lr_fp, lr_fp_mask, &offset,
                              GENERAL_REG, STORE_STACK);

      if (!(remain_loc_reg > 4 && is_pushpop_from_csky_live_regs (loc_reg_mask)))
        {
          emit_series_stack_ldst (remain_loc_reg, loc_reg_mask, &offset,
                                  GENERAL_REG, STORE_STACK);
        }
    }
  else if (TARGET_PUSHPOP && is_pushpop_from_csky_live_regs(fi.reg_mask))
    {
      emit_csky_regs_push (fi.reg_mask);
    }
  else if ((fi.reg_size - fi.freg_size) > 0)
    {
      gcc_assert(fi.reg_mask != 0);

      offset = fi.reg_size + fi.pad_reg - fi.freg_size;

      insn = emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                                  GEN_INT(-offset)));
      RTX_FRAME_RELATED_P (insn) = 1;

      offset = 0;
      emit_series_stack_ldst (fi.reg_size - fi.freg_size,
                              fi.reg_mask,
                              &offset,
                              GENERAL_REG,
                              STORE_STACK);
    }
  if (TARGET_SUPPORT_VREGS && fi.freg_size > 0)
    {
      offset = fi.freg_size;

      insn = emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                                  GEN_INT(-offset)));
      RTX_FRAME_RELATED_P (insn) = 1;

      offset = 0;
      emit_series_stack_ldst (fi.freg_size,
                              fi.freg_mask,
                              &offset,
                              VECTOR_REG,
                              STORE_STACK);
    }

  if (frame_pointer_needed)
    {
      /* substitutes hard_frame_pointer_rtx for frame_pointer_rtx when enable lra.  */
      insn = emit_insn(gen_movsi(hard_frame_pointer_rtx, stack_pointer_rtx));
      RTX_FRAME_RELATED_P (insn) = 1;
    }

  if (fi.local_size + fi.outbound_size)
    {
      offset = fi.local_size + fi.outbound_size;
      expand_csky_stack_adjust (-1, offset);
    }

  if (flag_pic && fi.reg_mask & (1 << PIC_OFFSET_TABLE_REGNUM))
    {
      rtx l1 = gen_label_rtx();
      rtx grs_label = gen_rtx_LABEL_REF(SImode, l1);
      rtx reg_gb = gen_rtx_REG(SImode, PIC_OFFSET_TABLE_REGNUM);
      /* FIXME R12 is the static_chain reg */
      rtx reg_temp = gen_rtx_REG(SImode, 13);

      rtx tmp0_unspec = gen_rtx_UNSPEC (Pmode,
                                        gen_rtvec (1, grs_label),
                                        PIC_SYMBOL_GOTPC_GRS);
      rtx tmp1_unspec = gen_rtx_UNSPEC (Pmode,
                                        gen_rtvec (1, grs_label),
                                        PIC_SYMBOL_GOTPC);

      emit_insn(gen_prologue_get_pc(tmp0_unspec));
      emit_move_insn(reg_temp, tmp1_unspec);
      emit_insn(gen_addsi3(reg_gb, reg_gb, reg_temp));
    }

  if (flag_stack_usage_info)
    {
      int space_allocated = fi.arg_size + fi.reg_size
                            + fi.local_size
                            + fi.outbound_size
                            + fi.pad_outbound
                            + fi.pad_local + fi.pad_reg;
      current_function_static_stack_size = space_allocated;
    }

  if (!flag_sched_prolog)
    emit_insn (gen_blockage ());
}


void csky_expand_epilogue(void)
{
  int sreg, ereg;
  int offset = 0;
  unsigned long func_type = get_csky_current_func_type();
  bool return_with_pc = false;

  if (!flag_sched_prolog)
    emit_insn (gen_blockage ());

  if (CSKY_FUNCTION_IS_NAKED(func_type))
    {
      emit_jump_insn (gen_rtx_UNSPEC_VOLATILE
                        (VOIDmode,
                         gen_rtvec (1, ret_rtx),
                         FLAG_EPILOGUE));
      return;
    }

  csky_stack_frame fi;
  get_csky_frame_layout(&fi);

  if (frame_pointer_needed)
    {
      /* replace frame_pointer_rtx with hard_frame_pointer_rtx when enable lra.  */
      emit_insn (gen_movsi (stack_pointer_rtx, hard_frame_pointer_rtx));
    }
  else
    {
      offset = fi.local_size + fi.outbound_size;
      if (offset > 0)
        {
          expand_csky_stack_adjust (1, offset);
        }
    }

  if (TARGET_SUPPORT_VREGS && fi.freg_size > 0)
    {
      offset = fi.freg_size;
      if (offset)
        {
          emit_series_stack_ldst (fi.freg_size,
                                  fi.freg_mask,
                                  &offset,
                                  VECTOR_REG,
                                  LOAD_STACK);
          emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                               GEN_INT(fi.freg_size)));
        }
    }

  if (TARGET_BACKTRACE)
    {
      int offset = fi.reg_size + fi.pad_reg - fi.freg_size;
      int adjust = fi.arg_size + fi.pad_arg + offset;
      int remain_loc_reg = fi.reg_size - fi.freg_size;
      int remain_lr_fp = 0;
      int loc_reg_mask = fi.reg_mask;
      int lr_fp_mask = 0;
      int rn;
      int remain;

      if (fi.reg_mask & (1 << HARD_FRAME_POINTER_REGNUM))
        {
          remain_loc_reg -= 4;
          remain_lr_fp += 4;
          loc_reg_mask &= ~(1 << HARD_FRAME_POINTER_REGNUM);
          lr_fp_mask |= (1 << HARD_FRAME_POINTER_REGNUM);
        }
      if (fi.reg_mask & (1 << CSKY_LR_REGNUM))
        {
          remain_loc_reg -= 4;
          remain_lr_fp += 4;
          loc_reg_mask &= ~(1 << CSKY_LR_REGNUM);
          lr_fp_mask |= (1 << CSKY_LR_REGNUM);
        }

      if (offset > 0)
        {
          offset -= fi.pad_reg;

          if (remain_loc_reg > 4
              && is_pushpop_from_csky_live_regs (loc_reg_mask)
              && fi.arg_size == 0
              && (!(func_type & CSKY_FT_INTERRUPT)))
            {
              int offset_lr_fp = offset - remain_loc_reg;

              emit_series_stack_ldst (remain_lr_fp,
                                      lr_fp_mask,
                                      &offset_lr_fp,
                                      GENERAL_REG,
                                      LOAD_STACK);
              emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                                   GEN_INT(adjust - remain_loc_reg)));

              emit_csky_regs_pop (loc_reg_mask);
              return_with_pc = true;
            }
          else
            {
              emit_series_stack_ldst (remain_loc_reg,
                                      loc_reg_mask,
                                      &offset,
                                      GENERAL_REG,
                                      LOAD_STACK);
              /* Add 4 here to counteract the first
                 subtraction in this function.  */
              offset += 4;
              emit_series_stack_ldst (remain_lr_fp,
                                      lr_fp_mask,
                                      &offset,
                                      GENERAL_REG,
                                      LOAD_STACK);
              emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                                   GEN_INT(adjust)));
            }
        }
      else if (adjust)
        {
          emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                               GEN_INT(adjust)));
        }
    }
  else if (TARGET_PUSHPOP && is_pushpop_from_csky_live_regs(fi.reg_mask)
           && fi.arg_size == 0 && !CSKY_FUNCTION_IS_INTERRUPT(func_type))
    {
      emit_csky_regs_pop (fi.reg_mask);
      return_with_pc = true;
    }
  /* TODO: stm */
  else if (is_stm_from_csky_live_regs(fi.reg_mask, &sreg, &ereg))
    {

    }
  else
    {
      offset = fi.reg_size + fi.pad_reg - fi.freg_size;
      int adjust = fi.arg_size + fi.pad_arg + offset;
      int remain = fi.reg_size - fi.freg_size;

      if (offset)
        {
          offset -= fi.pad_reg;
          emit_series_stack_ldst (remain,
                                  fi.reg_mask,
                                  &offset,
                                  GENERAL_REG,
                                  LOAD_STACK);
        }
      if (adjust)
        {
          emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                               GEN_INT(adjust)));
        }
    }

  #if 0
  if(crtl->calls_eh_return)
    {
      emit_insn(gen_addsi3(stack_pointer_rtx, stack_pointer_rtx,
                           EH_RETURN_STACKADJ_RTX));
    }
  #endif
   if (!return_with_pc)
      emit_jump_insn (gen_rtx_UNSPEC_VOLATILE
                        (VOIDmode,
                         gen_rtvec (1, ret_rtx),
                         FLAG_EPILOGUE));
}


static void
csky_output_function_prologue (FILE *f,
                               HOST_WIDE_INT frame_size ATTRIBUTE_UNUSED)
{
  unsigned long func_type = get_csky_current_func_type ();

  switch ((int) CSKY_FUNCTION_TYPE (func_type))
    {
    default:
    case CSKY_FT_NORMAL:
      break;
    case CSKY_FT_INTERRUPT:
      {
        asm_fprintf (f, "\t# Interrupt Service Routine.\n");
        asm_fprintf (f, "\tnie\n\tipush\n");
        if (CSKY_ISA_FEATURE(hreg))
          {
            asm_fprintf (f, "\tsubi\tsp, 56\n");
            asm_fprintf (f, "\tstm\tr18-r31, (sp)\n");
          }
        if (TARGET_SINGLE_FPU)
          {
            asm_fprintf (f, "\tsubi\tsp, 32\n");
            asm_fprintf (f, "\tfstms\tvr0-vr7, (sp)\n");
          }
        else if (TARGET_DOUBLE_FPU)
          {
            asm_fprintf (f, "\tsubi\tsp, 64\n");
            asm_fprintf (f, "\tfstmd\tvr0-vr7, (sp)\n");
          }
        break;
      }
    case CSKY_FT_FIQ:
      asm_fprintf (f, "\t# Fast Interrupt Service Routine.\n");
      break;
    case CSKY_FT_EXCEPTION:
      asm_fprintf (f, "\t# CSKY Exception Handler.\n");
      break;
    case CSKY_FT_NAKED:
      asm_fprintf (f, "\t# Naked Function: prologue and epilogue \
                      provided by programmer.\n");
      return;
    }

  csky_stack_frame fi;
  get_csky_frame_layout(&fi);

#if 0
  int offset = 0;
  if (fi.arg_size != 0)
    {
      offset = fi.arg_size + fi.pad_arg;
      asm_fprintf (f, "\tsubi\t%s, %d\n", reg_names[CSKY_SP_REGNUM], offset);
    }
  if (fi.arg_size != 0 && crtl->args.pretend_args_size == 0)
    {
      int rn = CSKY_FIRST_PARM_REG + CSKY_NPARM_REGS - 1;
      int remain = fi.arg_size;

      for (offset -= 4; remain >= 4; offset -= 4, rn--, remain -= 4)
        {
          asm_fprintf (f, "\tst.w\t%s, (%s, %d)\n", reg_names[rn],
                       reg_names[CSKY_SP_REGNUM], offset);
        }
    }
#endif

  if (TARGET_PUSHPOP && is_pushpop_from_csky_live_regs(fi.reg_mask))
    {
#if 0
      int rn = 4;
      int reg_end = 31;
      asm_fprintf (f, "\tpush\t");

      /* Find the first reg and output the name.  */
      while (!(fi.reg_mask & (1 << rn)))
        {
          rn++;
        }
      asm_fprintf (f, "%s", reg_names[rn++]);

      /* Find and output the rest regs.  */
      for (; rn <= reg_end; rn++)
        {
          if (!(fi.reg_mask & (1 << rn)))
            continue;
          asm_fprintf (f, ", %s", reg_names[rn]);
        }
      asm_fprintf (f, "\n");
#endif
    }

  int space_allocated = fi.arg_size + fi.reg_size + fi.local_size
                        + fi.outbound_size + fi.pad_outbound
                        + fi.pad_local + fi.pad_reg;

  /* generate .stack_size function-name, size for callgraph,
   * the default stack size is 0.  */
  if ((target_flags & MASK_STACK_SIZE) && (space_allocated > 0))
    {
      gcc_assert (current_function_decl != NULL);
      const char * func_name =
          IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (current_function_decl));
      int extra_length = 0;
      if (CSKY_FUNCTION_IS_INTERRUPT(func_type))
        {
          extra_length = 24;
          if (CSKY_ISA_FEATURE(hreg))
            extra_length += 56;
          if (TARGET_SINGLE_FPU)
            extra_length += 32;
          else if (TARGET_DOUBLE_FPU)
            extra_length += 64;
        }
      if (func_name[0] == '*')
        asm_fprintf (f, "\t.stack_size %s, %d\n",
                     &func_name[1], space_allocated + extra_length);
      else
        asm_fprintf (f, "\t.stack_size %s, %d\n", func_name,
                     space_allocated + extra_length);
    }
}


static void
csky_output_function_epilogue (FILE *file ATTRIBUTE_UNUSED,
                               HOST_WIDE_INT frame_size ATTRIBUTE_UNUSED)
{

}


static bool
is_stm_from_csky_live_regs(int mask, int *br, int *er)
{
  int i = 4;
  int begin_reg, end_reg;
  bool begin = false;
  bool end = false;
  int count = 0;

  if (!TARGET_MULTIPLE_STLD)
    return false;

  for (; i <= 11; i++)
    {
      if (!begin && (mask & 1 << i))
        {
          begin_reg = i;
          begin = true;
          count++;
          continue;
        }
      else if (begin && !end && (mask & 1 << i))
        {
          count++;
        }
      else if (begin && !end && !(mask & 1 << i))
        {
          end_reg = i - 1;
          end = true;
          continue;
        }
      /* FIXME by yanwb, the allocation order my not be continuous */
      else if (end && (mask & 1 << i))
        {
          return false;
        }
    }

  if (begin && !end && i == 12)
    {
      end_reg = 11;
      end = true;
    }

  if (count >= CSKY_MULTIPLE_LDST_THRESHOLD && count <= CSKY_MAX_MULTIPLE_STLD)
    {
      if (br)
        *br = begin_reg;
      if (er)
        *er = end_reg;
      return true;
    }
  return false;
}

const int csky_get_unexpanded_epilogue_length(void)
{
  unsigned long func_type = get_csky_current_func_type();
  if (CSKY_FUNCTION_IS_NAKED(func_type))
    return 4;

  int len = 0;
  int sreg = 0, ereg = 0;
  csky_stack_frame fi;
  get_csky_frame_layout(&fi);

  if (is_stm_from_csky_live_regs(fi.reg_mask, &sreg, &ereg))
    {
      int off = fi.reg_size - (ereg - sreg + 1 ) * 4;
      if (off) off = fi.reg_size - 4;

      int i = 31;
      for (; i > ereg; i--)
        {
          if (!(fi.reg_mask & (1 << i)))
            continue;
          asm_fprintf (asm_out_file, "\tld.w\t%s, (%s, %d)\n",
                       reg_names[i], reg_names[CSKY_SP_REGNUM], off);

          if (i < 7 && off < 1024)
            len += 2;
          else
            len += 4;

          off -= 4;
        }
        len += 6;
    }

  if(crtl->calls_eh_return)
    len += 2;

  len += 4;

  return len;
}

const char *csky_unexpanded_epilogue(void)
{
  int sreg, ereg;
  unsigned long func_type = get_csky_current_func_type();

  if (CSKY_FUNCTION_IS_NAKED(func_type))
    return output_csky_return_instruction ();

  csky_stack_frame fi;
  get_csky_frame_layout(&fi);

  if (TARGET_PUSHPOP && is_pushpop_from_csky_live_regs(fi.reg_mask)
      && fi.arg_size == 0)
    {
#if 0
      int rn = 4;
      int reg_end = 31;
      asm_fprintf (asm_out_file, "\tpop\t");

      /* Find the first reg and output the name.  */
      while (!(fi.reg_mask & (1 << rn)))
        {
          rn++;
        }
      asm_fprintf (asm_out_file, "%s", reg_names[rn++]);

      /* Find and output the rest regs.  */
      for (; rn <= reg_end; rn++)
        {
          if (!(fi.reg_mask & (1 << rn)))
            continue;
          asm_fprintf (asm_out_file, ", %s", reg_names[rn]);
        }
      asm_fprintf (asm_out_file, "\n");
#endif
    }
  else if (is_stm_from_csky_live_regs(fi.reg_mask, &sreg, &ereg))
    {
      int off = fi.reg_size - (ereg - sreg + 1 ) * 4;
      if (off) off = fi.reg_size - 4;

      int i = 31;
      for (; i > ereg; i--)
        {
          if (!(fi.reg_mask & (1 << i)))
            continue;
          asm_fprintf (asm_out_file, "\tld.w\t%s, (%s, %d)\n",
                       reg_names[i], reg_names[CSKY_SP_REGNUM], off);
          off -= 4;
        }

      asm_fprintf (asm_out_file, "\tldm\t%s - %s, (%s)\n",
                   reg_names[sreg], reg_names[ereg],
                   reg_names[CSKY_SP_REGNUM]);
      asm_fprintf (asm_out_file, "\taddi\t%s, 0x%x\n",
                   reg_names[CSKY_SP_REGNUM],
                   fi.reg_size + fi.pad_reg + fi.arg_size + fi.pad_arg);
    }

  if(crtl->calls_eh_return)
    {
      asm_fprintf (asm_out_file, "\taddu\t%s, %s\n", reg_names[CSKY_SP_REGNUM],
                   reg_names[CSKY_EH_STACKADJ_REGNUM]);
    }

  return output_csky_return_instruction ();
}


/* Set the caller frame exceptions handler address as lr.  */

void
set_csky_return_address (rtx source, rtx scratch)
{
  csky_stack_frame fi;
  get_csky_frame_layout(&fi);
  HOST_WIDE_INT delta = 0;
  rtx addr;
  unsigned long saved_regs = fi.reg_mask;

  if ((saved_regs & ((1 << CSKY_LR_REGNUM))) == 0)
    emit_move_insn (gen_rtx_REG (Pmode, CSKY_LR_REGNUM), source);
  else
    {
      /* LR will be the toppest saved register.  */
      int i = 0;
      delta = 0;

      delta += fi.reg_size;
      delta -= fi.pad_reg + 4 /* lr self size */;

      delta += fi.local_size + fi.outbound_size
            + fi.pad_outbound + fi.pad_local;

      for (i = 16; i < 32; i++)
        if(saved_regs & (1 << i)) delta -= 4;

      if(delta > 0x1000)
        {
          emit_insn (gen_movsi(scratch, GEN_INT (delta)));
          emit_insn (gen_addsi3 (scratch, scratch, stack_pointer_rtx));
          addr = scratch;
        }
      else
        {
          addr = plus_constant (Pmode, stack_pointer_rtx, delta);
        }
      emit_move_insn (gen_frame_mem (Pmode, addr), source);
    }
}


/* Output multipe bclri instructions according to how many
   zero bits in MASK.  */

const char *
output_csky_bclri (rtx dst, rtx src, int mask)
{
  rtx out_operands[3];
  int bit;
  bool first_set = true;

  out_operands[0] = dst;
  out_operands[1] = src;

  for (bit = 0; bit < 32; bit++)
    {
      if ((mask & 0x1) == 0x0)
        {
          out_operands[2] = GEN_INT (bit);

          if (first_set)
            {
              output_asm_insn ("bclri\t%0, %1, %2", out_operands);
              first_set = false;
            }
          else
           output_asm_insn ("bclri\t%0, %0, %2", out_operands);
        }

      mask >>= 1;
    }

  return "";
}


/* Output multipe bseti instructions according to how many
   one bits in MASK.  */

const char *
output_csky_bseti (rtx dst, rtx src, int mask)
{
  rtx out_operands[3];
  int bit;
  bool first_set = true;

  out_operands[0] = dst;
  out_operands[1] = src;

  for (bit = 0; bit < 32; bit++)
    {
      if ((mask & 0x1) == 0x1)
        {
          out_operands[2] = GEN_INT (bit);

          if (first_set)
            {
              output_asm_insn ("bseti\t%0, %1, %2", out_operands);
              first_set = false;
            }
          else
            output_asm_insn ("bseti\t%0, %0, %2", out_operands);
        }

      mask >>= 1;
    }

  return "";
}

/* Count the bits number of one in MASK.  */

int
get_csky_int_ones (HOST_WIDE_INT mask)
{
  /* A trick to count set bits recently posted on comp.compilers.  */
  mask = (mask >> 1 & 0x55555555) + (mask & 0x55555555);
  mask = ((mask >> 2) & 0x33333333) + (mask & 0x33333333);
  mask = ((mask >> 4) + mask) & 0x0f0f0f0f;
  mask = ((mask >> 8) + mask);

  return (mask + (mask >> 16)) & 0xff;
}


/* Count the bits number of zero in MASK.  */

int
get_csky_int_zeros (HOST_WIDE_INT mask)
{
  return 32 - get_csky_int_ones (mask);
}


/* Return 1 if the VAL has continuous nonzero bits, and the
   first nozero bit is begin at the top or the last nonzero
   bit is end at the bottom.
   Return 1 means some operation like and can be transformed
   to lsli and lsri.  */

bool
can_trans_by_csky_shlshr (unsigned HOST_WIDE_INT val)
{
  int i;
  for (i = 13; i <= 31; i++)
    {
      if ((unsigned)((((HOST_WIDE_INT) 1) << i) - 1) == val
          || (unsigned)((((HOST_WIDE_INT) 1) << i) - 1) == ~val)
        {
          return 1;
        }
    }
  return 0;
}


/* Return TRUE if X references a SYMBOL_REF.  */

int
symbol_mentioned_p (rtx x)
{
  const char * fmt;
  int i;

  if (GET_CODE (x) == SYMBOL_REF)
    return 1;

  fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'E')
        {
          int j;

          for (j = XVECLEN (x, i) - 1; j >= 0; j--)
            if (symbol_mentioned_p (XVECEXP (x, i, j)))
              return 1;
        }
      else if (fmt[i] == 'e' && symbol_mentioned_p (XEXP (x, i)))
        return 1;
    }
  return 0;
}


/* Return TRUE if X references a LABEL_REF.  */

int
label_mentioned_p (rtx x)
{
  const char * fmt;
  int i;

  if (GET_CODE (x) == LABEL_REF)
    return 1;

  fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'E')
        {
          int j;

          for (j = XVECLEN (x, i) - 1; j >= 0; j--)
            if (label_mentioned_p (XVECEXP (x, i, j)))
              return 1;
        }
      else if (fmt[i] == 'e' && label_mentioned_p (XEXP (x, i)))
        return 1;
    }

  return 0;
}


int
tls_mentioned_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case CONST:
      return tls_mentioned_p (XEXP (x, 0));

    case UNSPEC:
      if (XINT (x, 1) == UNSPEC_TLS)
        return 1;

    /* Fall through.  */
    default:
      return 0;
    }
}


rtx
legitimize_pic_address (rtx orig, rtx reg, int flag)
{
  rtx pic_reg = gen_rtx_REG(SImode, PIC_OFFSET_TABLE_REGNUM);
  int flag_optimize = 0;

  if (GET_CODE (orig) == SYMBOL_REF
      || GET_CODE (orig) == LABEL_REF)
    {
      rtx pic_ref, address, rtx_tmp;
      rtx insn;
      rtx pic_reg = gen_rtx_REG(SImode, PIC_OFFSET_TABLE_REGNUM);
      int subregs = 0;

      if (reg == 0)
        {
          gcc_assert (can_create_pseudo_p ());
          reg = gen_reg_rtx (Pmode);
          subregs = 1;
        }

      if (subregs)
        address = gen_reg_rtx (Pmode);
      else
        address = reg;

      if (GET_CODE (orig) == LABEL_REF
          || ((GET_CODE (orig) == SYMBOL_REF
              && SYMBOL_REF_LOCAL_P (orig))))
        {
          /* bsr symbol */
          if (flag_pic == 1 && flag == 0)
            {
              pic_ref = gen_rtx_UNSPEC (Pmode,
                                        gen_rtvec (1, orig),
                                        PIC_SYMBOL_BSR);
              return pic_ref;
            }
          /* grs rx, symbol */
          else if (flag_pic == 1 && (GET_CODE (orig) == SYMBOL_REF)
                   && SYMBOL_REF_FUNCTION_P (orig))
            {
              pic_ref = gen_rtx_UNSPEC (Pmode,
                                        gen_rtvec (1, orig),
                                        PIC_SYMBOL_GRS);
              return pic_ref;
            }
          /* lrw rx, symbol@GOTOFF; add rx, rx, gb */
          else
            {
              rtx_tmp = gen_rtx_UNSPEC (Pmode,
                                        gen_rtvec (1, orig),
                                        PIC_SYMBOL_GOTOFF);
              emit_move_insn (address, rtx_tmp);

              pic_ref = gen_rtx_PLUS (Pmode, address, pic_reg);

              flag_optimize = 1;
            }
        }
      else
        {
          /* when flag != 0 generate sym@GOT, otherwise generate sym@PLT */
          rtx_tmp = gen_rtx_UNSPEC (Pmode,
                                    gen_rtvec (1, orig),
                                    flag != 0 ? PIC_SYMBOL_GOT:PIC_SYMBOL_PLT);
          flag_optimize = flag;

          if (flag_pic == 1)
            {
              pic_ref = gen_const_mem(Pmode,
                          gen_rtx_PLUS (Pmode, pic_reg, rtx_tmp));
            }
          else
            {
              emit_move_insn (address, rtx_tmp);
              pic_ref = gen_const_mem(Pmode,
                                      gen_rtx_PLUS (Pmode,
                                                    pic_reg,
                                                    gen_rtx_MULT (Pmode,
                                                                  address,
                                                                  GEN_INT(1))));
            }
        }

      insn = emit_move_insn(reg, pic_ref);
      /* Put a REG_EQUAL note on this insn,
         so that it can be optimized by loop.  */
      if (flag_optimize)
        set_unique_reg_note (insn, REG_EQUAL, orig);

      return reg;
    }
  else if (GET_CODE (orig) == CONST)
    {
      rtx base, offset;

      if(GET_CODE (XEXP (orig, 0)) == PLUS
         && XEXP (XEXP (orig, 0), 1) == pic_reg)
        return orig;

      if (reg == 0)
        {
          gcc_assert (can_create_pseudo_p());
          reg = gen_reg_rtx (Pmode);
        }

      gcc_assert (GET_CODE (XEXP(orig, 0)) == PLUS);

      base = legitimize_pic_address (XEXP (XEXP (orig, 0), 0),
                                     reg,
                                     flag);
      offset = legitimize_pic_address (XEXP (XEXP (orig, 0), 1),
                                       base == reg ? 0 : reg, flag);

      if (GET_CODE (offset) == CONST_INT)
        return plus_constant (Pmode, base, INTVAL (offset));

      return gen_rtx_PLUS (Pmode, base, offset);
    }

  return orig;
}


/* Functions to output assembly code for a function call.  */

char *
csky_output_call (rtx operands[], int index)
{
  static char buffer[20];
  rtx addr = operands[index];

  if (REG_P (addr))
    sprintf (buffer, "jsr\t%%%d", index);
  else if (flag_pic && (GET_CODE (addr) == UNSPEC))
    sprintf (buffer, "bsr\t%%%d", index);
  else
    sprintf (buffer, "jbsr\t%%%d", index);

  return buffer;
}


/* Worker function for TARGET_ASM_TRAMPOLINE_TEMPLATE.
   Output assembler code for a block containing the constant parts
   of a trampoline, leaving space for the variable parts.  */

static void
csky_asm_trampoline_template (FILE *f)
{
  if (CSKY_ISA_FEATURE(2E3))
    {
      fprintf (f, "\tlrw\t%s, [.Lstatic_chain]\n",
               reg_names[STATIC_CHAIN_REGNUM]);
      fprintf (f, "\tjmpi\t[.Lfunc_address]\n");
    }
  else
    {
      /* Ck801 does't support nested function trampolines well.*/
      if (CSKY_TARGET_ARCH(CK801))
        {
          fprintf (f, "\tpush\tr4, lr\n");
          fprintf (f, "\tlrw\tr4, [.Lfunc_address]\n");
          fprintf (f, "\tlrw\t%s, [.Lstatic_chain]\n",
                   reg_names[STATIC_CHAIN_REGNUM]);
          fprintf (f, "\tjsr\tr4\n");
          fprintf (f, "\tpop\tr4, lr\n");
        }
      else
        {
          fprintf (f, "\tlrw\tt1, [.Lfunc_address]\n");
          fprintf (f, "\tlrw\t%s, [.Lstatic_chain]\n",
                   reg_names[STATIC_CHAIN_REGNUM]);
          fprintf (f, "\tjmp\tt1\n");
        }

      /* To align 32bits for lrw.  */
      fprintf (f, "\t.align 2\n");
    }
  fprintf (f, ".Lstatic_chain:\n");
  fprintf (f, "\t.long 0\n");
  fprintf (f, ".Lfunc_address:\n");
  fprintf (f, "\t.long 0\n");
}

/* Worker function for TARGET_TRAMPOLINE_INIT.  */

static void
csky_trampoline_init (rtx m_tramp, tree fndecl, rtx chain_value)
{
  rtx fnaddr = XEXP (DECL_RTL (fndecl), 0);
  rtx mem, a_tramp;

  emit_block_move (m_tramp, assemble_trampoline_template (),
                   GEN_INT (TRAMPOLINE_SIZE), BLOCK_OP_NORMAL);

  mem = adjust_address (m_tramp, SImode,
                        CSKY_ISA_FEATURE(2E3) ? 8 : 12);
  emit_move_insn (mem, chain_value);
  mem = adjust_address (m_tramp, SImode,
                        CSKY_ISA_FEATURE(2E3) ? 12 : 16);
  emit_move_insn (mem, fnaddr);

  a_tramp = XEXP (m_tramp, 0);
  emit_library_call (gen_rtx_SYMBOL_REF (Pmode, "__clear_cache"),
                     LCT_NORMAL, VOIDmode, 2, a_tramp, Pmode,
                     plus_constant (Pmode, a_tramp, TRAMPOLINE_SIZE), Pmode);
}


/* Accept the floating point constant 1 in the appropriate mode.  */

int
is_csky_const_float_1 (rtx op, enum machine_mode mode)
{
  const REAL_VALUE_TYPE *d;
  static REAL_VALUE_TYPE onedf;
  static REAL_VALUE_TYPE onesf;
  static int one_initialized;

  if (mode != GET_MODE (op)
      || (mode != DFmode && mode != SFmode))
    {
      return 0;
    }

  if (GET_CODE (op) != CONST_DOUBLE)
    {
      return 0;
    }
  d = CONST_DOUBLE_REAL_VALUE (op);

  /* We only initialize these values if we need them, since we will
     never get called unless mips_isa >= 4.  */
  if (! one_initialized)
    {
      onedf = REAL_VALUE_ATOF ("1.0", DFmode);
      onesf = REAL_VALUE_ATOF ("1.0", SFmode);
      one_initialized = 1;
    }
  if (mode == DFmode)
    return real_equal (d, &onedf);
  else
    return real_equal (d, &onesf);
}

/* Accept the floating point constant 1 in the appropriate mode.  */

int
is_csky_const_float_0 (rtx op, enum machine_mode mode)
{
  const REAL_VALUE_TYPE *d;
  static REAL_VALUE_TYPE zerodf;
  static REAL_VALUE_TYPE zerosf;
  static int zero_initialized;

  if (GET_CODE (op) != CONST_DOUBLE
      || mode != GET_MODE (op)
      || (mode != DFmode && mode != SFmode))
    return 0;

  d = CONST_DOUBLE_REAL_VALUE (op);

  /* We only initialize these values if we need them, since we will
     never get called unless mips_isa >= 4.  */
  if (!zero_initialized)
    {
      zerodf = REAL_VALUE_ATOF ("0", DFmode);
      zerosf = REAL_VALUE_ATOF ("0", SFmode);
      zero_initialized = 1;
    }

  if (mode == DFmode)
    return real_equal (d, &zerodf);
  else
    return real_equal (d, &zerosf);
}


/* Generate compare rtl insn for float comparison instruction.
   Retrun true if the comparison CODE has turn to negative
   side.  */

bool
gen_csky_compare_float (enum rtx_code code, rtx op0, rtx op1)
{
  rtx cc_reg = gen_rtx_REG (CCmode, CSKY_CC_REGNUM);
  bool invert;

  if (!is_csky_const_float_0 (op1, GET_MODE (op1)))
    op1 = force_reg (GET_MODE (op1), op1);

  invert = false;
  switch (code)
    {
    case EQ:
      code = NE;
      invert = true;
      break;

    case NE:
      break;
    case LE:
      if (is_csky_const_float_0 (op1, GET_MODE (op1)))
        op1 = force_reg (GET_MODE (op1), op1);
      break;
    case GT:
      if (is_csky_const_float_0 (op1, GET_MODE (op1)))
        {
          op1 = force_reg (GET_MODE (op1), op1);
        }
      break;
    case GE:
      break;
    case LT:
      if ((is_csky_const_float_0 (op1, GET_MODE (op1))))
        {
          code = GE;
          invert = true;
        }
      break;
    case UNORDERED:
      break;
    case ORDERED:
      code = UNORDERED;
      invert = true;
      break;

    default:
      break;
    }

  emit_insn (gen_rtx_SET (cc_reg, gen_rtx_fmt_ee (code, CCmode, op0, op1)));

  return invert;
}


int
get_cskyv2_mem_constraint (const char *str, rtx op)
{
  if (GET_CODE (op) != MEM)
    return false;
  if (*str == 'Q')
    {
      struct csky_address addr;

      if (!decompose_csky_address (XEXP (op, 0), &addr))
        return false;

      /* Verify base register. */
      if (!is_csky_address_register_rtx_p (addr.base, 0))
        return false;

      /* Verify index operand. */
      if (addr.index)
        {
          if (!is_csky_address_register_rtx_p (addr.index, 0))
            return false;

          if (addr.scale == 1 || addr.scale == 2 || addr.scale == 4
              || addr.scale == 8)
            return true;

          return false;
        }
      /* verify disp operand */
      else if (addr.disp)
        {
          rtx disp = addr.disp;

          if (!CONST_INT_P (disp))
            return false;

          if ((((unsigned) INTVAL (disp)) % 4) == 0 &&
              ((unsigned) INTVAL (disp)) <= (unsigned) 1020)
            return true;

          return false;
        }

      return true;
    }
  else if (*str == 'W')
    {
      struct csky_address addr;

      if (!decompose_csky_address (XEXP (op, 0), &addr))
        return false;

      /* Verify base register. */
      if (!is_csky_address_register_rtx_p (addr.base, 0))
        return false;

      /* Verify index operand. */
      if (addr.index)
        {
          if (!is_csky_address_register_rtx_p (addr.index, 0))
            return false;

          if (addr.scale == 1 || addr.scale == 2 || addr.scale == 4
              || addr.scale == 8)
            return true;

          return false;
        }
    }

  return false;
}


/* Returns the (interrupt) function type of the current
   function, or CSKY_FT_UNKNOWN if the type cannot be determined.  */

static unsigned long
csky_isr_value (tree argument)
{
  const isr_attribute_arg *ptr;
  const char *arg;

  /* No argument - default to IRQ.  */
  if (argument == NULL_TREE)
    return CSKY_FT_ISR;

  /* Get the value of the argument.  */
  if (TREE_VALUE(argument) == NULL_TREE
      || TREE_CODE(TREE_VALUE(argument)) != STRING_CST)
    return CSKY_FT_UNKNOWN;

  arg = TREE_STRING_POINTER(TREE_VALUE(argument));

  /* Check it against the list of known arguments.  */
  for(ptr = isr_attribute_args; ptr->arg != NULL; ptr++)
    {
      if(strcmp(arg, ptr->arg) == 0)
        return ptr->return_value;
    }

  /* An unrecognized interrupt type.  */
  return CSKY_FT_UNKNOWN;
}

/* Handle an attribute requiring a FUNCTION_DECL;
   arguments as in struct attribute_spec.handler.  */

static tree
csky_handle_fndecl_attribute (tree *node, tree name, tree args ATTRIBUTE_UNUSED,
                              int flags ATTRIBUTE_UNUSED, bool *no_add_attrs)
{
  if (TREE_CODE (*node) != FUNCTION_DECL)
    {
      warning (OPT_Wattributes, "%qE attribute only applies to functions",
         name);
      *no_add_attrs = true;
    }

  return NULL_TREE;
}

/* Handle an "interrupt" or "isr" attribute;
   arguments as in struct attribute_spec.handler.  */

static tree
csky_handle_isr_attribute (tree *node, tree name, tree args, int flags,
                           bool *no_add_attrs)
{
  if(!CSKY_ISA_FEATURE(isr))
    {
      warning(OPT_Wattributes, "%qE attribute ignored", name);
      *no_add_attrs = true;
      return NULL_TREE;
    }

  if(DECL_P(*node))
    {
      if(TREE_CODE(*node) != FUNCTION_DECL)
        {
          warning(OPT_Wattributes, "%qE attribute only applies to function",
                  name);
          *no_add_attrs = true;
        }
    }
  else
    {
      if (TREE_CODE(*node) == FUNCTION_TYPE
          || TREE_CODE(*node) == METHOD_TYPE)
        {
          if(csky_isr_value(args) == CSKY_FT_UNKNOWN)
            {
              warning(OPT_Wattributes, "%qE attribute ignored", name);
              *no_add_attrs = true;
            }
        }
      else if (TREE_CODE(*node) == POINTER_TYPE
               && (TREE_CODE(TREE_TYPE(*node)) == FUNCTION_TYPE
                   || TREE_CODE(TREE_TYPE(*node)) == METHOD_TYPE)
               && csky_isr_value(args) != CSKY_FT_UNKNOWN)
        {
          *node = build_variant_type_copy(*node);
          TREE_TYPE(*node) = build_type_attribute_variant (TREE_TYPE(*node),
            tree_cons(name, args, TYPE_ATTRIBUTES(TREE_TYPE(*node))));
          *no_add_attrs = true;
        }
      else
        {
          if (flags & ((int)ATTR_FLAG_DECL_NEXT
                       | (int)ATTR_FLAG_FUNCTION_NEXT
                       | (int)ATTR_FLAG_ARRAY_NEXT))
            {
              *no_add_attrs = true;
              return tree_cons(name, args, NULL_TREE);
            }
          else
            {
              warning(OPT_Wattributes, "%qE attribute ignored", name);
            }
        }
    }
  return NULL_TREE;
}


/* Compute extra cost of moving data between one register class
   and another.  */

int
csky_register_move_cost (machine_mode mode,
                         reg_class_t from, reg_class_t to)
{
#define GR_REG_CLASS_P(CLASS) \
  ((CLASS) == GENERAL_REGS || (CLASS) == MINI_REGS || (CLASS) == SP_REGS)

#define HILO_REG_CLASS_P(CLASS) \
  ((CLASS) == HI_REGS || (CLASS) == LO_REGS || (CLASS) == HILO_REGS)

#define V_REG_CLASS_P(CLASS) \
  ((CLASS) == V_REGS)

  if (V_REG_CLASS_P (from) && V_REG_CLASS_P (to))
    return 2;

  if ((V_REG_CLASS_P (from) && GR_REG_CLASS_P (to))
      || (GR_REG_CLASS_P (from) && V_REG_CLASS_P (to)))
    return 16;

  if ((HILO_REG_CLASS_P (from) && GR_REG_CLASS_P (to))
      || (GR_REG_CLASS_P (from) && HILO_REG_CLASS_P (to)))
    return 16;

  if (HILO_REG_CLASS_P (from) && HILO_REG_CLASS_P (to))
    return 32;

  if ((HILO_REG_CLASS_P (from) && V_REG_CLASS_P (to))
      || (V_REG_CLASS_P (from) && HILO_REG_CLASS_P (to)))
    return 64;

  return 2;
}


/* Compute the cost of moving data between registers and memory.  */

int
csky_memory_move_cost (machine_mode mode, reg_class_t rclass,
                       bool in ATTRIBUTE_UNUSED)
{
  int cost = 4;

  if (TARGET_SUPPORT_VREGS)
    {
      if (mode == DFmode || mode == SFmode
          || VECTOR_MODE_P (mode))
        {
          cost += 4;
        }
    }
  return (cost + memory_move_secondary_cost(mode, rclass, in));
}


static bool
ck802_ck801_rtx_costs (rtx x, int code, int outer_code, int *total,
                       bool speed ATTRIBUTE_UNUSED)
{
  enum machine_mode mode = GET_MODE (x);
  switch (code)
    {
      /*Accessing memrory costs quite a lot for first word */
    case MEM:
      *total = COSTS_N_INSNS (1 + CSKY_NUM_REGS (mode));
      return false;
    case DIV:
    case UDIV:
    case MOD:
    case UMOD:
      *total = 100;
      return true;

    case ROTATE:
    case ROTATERT:
    case ASHIFT:
    case LSHIFTRT:
    case ASHIFTRT:
      if (speed)
        *total = 2;
      else
        *total = COSTS_N_INSNS (1);
      return false;

    case MINUS:
    case PLUS:
      *total = COSTS_N_INSNS (CSKY_NUM_REGS (mode));
      return false;

    case AND:
      {
        enum rtx_code subcode = GET_CODE (XEXP (x, 1));

        /*if subcode is "not", try to conbime it such as "andn"
           instruction, so let AND itself not to costs insns */
        if (subcode == NOT)
          {
            *total = 0;
            return false;
          }
      }
      /*fall through */
    case XOR:
    case IOR:
      *total = COSTS_N_INSNS (CSKY_NUM_REGS (mode));
      return false;

    case MULT:
      /*we can use "ix.h/w" insn to repalce multed by 3 or 5
         "ix.h/w" is a 32-bits insn, so let it be little less than
         "mult" insn */
      if (REG_P (XEXP (x, 0)) && CONST_INT_P (XEXP (x, 1)))
        {
          unsigned HOST_WIDE_INT m;
          m = (unsigned HOST_WIDE_INT) (INTVAL (XEXP (x, 1)));
          if ((m == 2 || m == 4) && outer_code == PLUS)
            {
              *total = 2;
              return true;
            }
          else
            {
              /*because mult is relatively slower than other operation, so
                 if speeding ,we try to using other insns to optimazing mult,
                 so let the mult insn relatively large. And if we consider about
                 size, a mult insn seems much simpler */
              if (speed)
                {
                  *total = COSTS_N_INSNS (10 * CSKY_NUM_REGS (mode));
                  return true;
                }
              int cycle = 0;
              while (m)
                {
                  m >>= 2;
                  cycle++;
                }
              *total = COSTS_N_INSNS (1) + cycle;
              return false;
            }
        }
      if (!speed)
        *total = COSTS_N_INSNS (1);
      return false;

    case NEG:
      /*Usually, we use minused by 0 to substutite for neg, but we must cost
         1 insn to move 0 to a register, so it si the extra cost */
      *total = COSTS_N_INSNS (2 * CSKY_NUM_REGS (mode));
      return false;

    case NOT:
      *total = COSTS_N_INSNS (CSKY_NUM_REGS (mode));
      return false;

    case COMPARE:
      *total = COSTS_N_INSNS (1);
      return false;

    case SIGN_EXTEND:
    case ZERO_EXTEND:
      *total = COSTS_N_INSNS (CSKY_NUM_REGS (mode));
      return false;

    case SIGN_EXTRACT:
    case ZERO_EXTRACT:
      if (REG_P (XEXP (x, 0)) && CONST_INT_P (XEXP (x, 1))
          && CONST_INT_P (XEXP (x, 2)) && INTVAL (XEXP (x, 1)) == 8
          && (INTVAL (XEXP (x, 2)) % 8 == 0))
        {
          *total = 4;
          return true;
        }
      *total = COSTS_N_INSNS (CSKY_NUM_REGS (mode));
      return false;

    case CONST_INT:
      {
        unsigned HOST_WIDE_INT t;
        t = (unsigned HOST_WIDE_INT) (INTVAL (x));

        if (outer_code == COMPARE)
          {
            if (t < 0x10000)
              *total = 0;
            else
              *total = COSTS_N_INSNS (2);
          }
        else if (outer_code == AND || outer_code == IOR || outer_code == XOR)
          {
            /*"andi,xori,ori" arn 32-bits insn, so let it costs a little more */
            if (t < 0x1000)
              {
                /*try replace "andi" by "sextb/h", so let it cost more */
                if (outer_code == AND && (t == 0xff || t == 0xffff))
                  {
                    *total = 8;
                    return true;
                  }
                *total = 2;
              }
            else if (t < 0x10000)
              *total = COSTS_N_INSNS (1);
            else
              *total = COSTS_N_INSNS (2);
          }
        else if (outer_code == PLUS || outer_code == MINUS)
          {
            /*"addi/subi rx,ry,imm", id imm<9, it more often be a 16-bits insn
               if imm>=9, use "movi" insn probably be less than "addi/subi" */
            if (t < 9)
              *total = 0;
            else if (t < 0x1000)
              *total = 2;
            else if (t < 0x10000)
              *total = COSTS_N_INSNS (1);
            else
              *total = COSTS_N_INSNS (2);
          }
        else if (outer_code == ROTATE || outer_code == ROTATERT
                 || outer_code == LSHIFTRT || outer_code == ASHIFTRT
                 || outer_code == ASHIFT)
          {
            if (t < 32)
              *total = 0;
            else
              *total = COSTS_N_INSNS (2);
          }
        else
          {
            if (t < 0x10000)
              if (outer_code == SET && t < 256)
                *total = 0;
              else
                *total = COSTS_N_INSNS (1);
            else
              *total = COSTS_N_INSNS (2);
          }
      }
      return true;

    case CONST:
    case LABEL_REF:
    case SYMBOL_REF:
      *total = COSTS_N_INSNS (3);
      return true;
    default:
      return false;
    }
}


static bool
ck803_rtx_costs (rtx x, int code, int outer_code, int *total,
                       bool speed ATTRIBUTE_UNUSED)
{
  switch (code)
    {
    case SET:
      if (MEM_P (XEXP (x, 1)))
        {
          struct csky_address op1;
          bool address_valid;

          address_valid = decompose_csky_address
                            (XEXP (XEXP (x, 1), 0), &op1);
          if (op1.index)
            {
              *total = COSTS_N_INSNS (3);
              return true;
            }
          else if (address_valid)
            {
              *total = COSTS_N_INSNS (1);
              return true;
            }
        }
      if (REG_P (XEXP (x, 0)) && (GET_CODE (XEXP (x, 1)) == PLUS))
       {
         rtx sub_exp = XEXP (x, 1);
         if (REG_P (XEXP (sub_exp, 0)) && REG_P (XEXP (sub_exp, 1)))
         {
           *total = COSTS_N_INSNS (1);
           return true;
         }
       }
      return false;
    case MULT:
      if (REG_P (XEXP (x, 0)) && CONST_INT_P (XEXP (x, 1)))
        {
          if (INTVAL (XEXP (x, 1)) < 0xffffffff
              && INTVAL (XEXP (x, 1)) > 0)
            {
              *total = COSTS_N_INSNS (1);
              return true;
            }
        }
      return false;

    case CONST:
    case LABEL_REF:
    case SYMBOL_REF:
      *total = COSTS_N_INSNS (3);
      return true;
    default:
      return false;
    }
}

/* Compute a (partial) cost for rtx X.  Return true if the complete
   cost has been computed, and false if subexpressions should be
   scanned.  In either case, *TOTAL contains the cost result.  */

static bool
csky_rtx_costs_internal (rtx x, enum rtx_code code, enum rtx_code outer_code,
                         const struct cpu_cost_table *extra_cost,
                         int *total, bool speed)
{
  machine_mode mode;

  if (CSKY_TARGET_ARCH(CK802) || CSKY_TARGET_ARCH(CK801))
    {
      return ck802_ck801_rtx_costs (x, code, outer_code, total, speed);
    }

  if (CSKY_TARGET_ARCH(CK803))
    {
      return ck803_rtx_costs (x, code, outer_code, total, speed);
    }

  switch (code)
    {
    case MULT:
      if (REG_P (XEXP (x, 0)) && CONST_INT_P (XEXP (x, 1)))
        {
          if (INTVAL (XEXP (x, 1)) % 2 == 0
              && INTVAL (XEXP (x, 1)) < 0xffffffff
              && INTVAL (XEXP (x, 1)) > 0)
            {
              *total = 4;
              return true;
            }
        }
      return false;

    case CONST:
    case LABEL_REF:
    case SYMBOL_REF:
      *total = COSTS_N_INSNS (3);
      return true;
    case SET:
      mode = GET_MODE (SET_DEST (x));
      if (REG_P (SET_SRC (x)) && REG_P (SET_DEST (x)))
        {
          if (VECTOR_MODE_P (mode) || GET_MODE_SIZE (mode) <= 4
              || (TARGET_HARD_FLOAT && (mode == DFmode
                                        || mode == SFmode)))
            {
              *total = COSTS_N_INSNS (1);
              return true;
            }

        }
      return false;
    default:
      return false;
    }
}


/* RTX costs entry point.  */

static bool
csky_rtx_costs (rtx x, machine_mode mode ATTRIBUTE_UNUSED, int outer_code,
                int opno ATTRIBUTE_UNUSED, int *total, bool speed)
{
  bool result;
  int code = GET_CODE (x);
  gcc_assert (current_tune->insn_extra_cost);

  result =  csky_rtx_costs_internal (x, (enum rtx_code) code,
                                     (enum rtx_code) outer_code,
                                     current_tune->insn_extra_cost,
                                     total, speed);

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      print_rtl_single (dump_file, x);
      fprintf (dump_file, "\n%s cost: %d (%s)\n", speed ? "Hot" : "Cold",
               *total, result ? "final" : "partial");
    }
  return result;
}


static void
csky_add_gc_roots (void)
{
  gcc_obstack_init (&minipool_obstack);
  minipool_startobj = (char *) obstack_alloc (&minipool_obstack, 0);
}


/* switch case optimize.  */

const char *
csky_output_casesi (rtx *operands)
{
  rtx diff_vec = PATTERN (NEXT_INSN (as_a <rtx_insn *> (operands[0])));

  gcc_assert (GET_CODE (diff_vec) == ADDR_DIFF_VEC);

  switch (GET_MODE(diff_vec))
    {
    case QImode:
      return (ADDR_DIFF_VEC_FLAGS (diff_vec).offset_unsigned ?
              "jbsr\t___gnu_csky_case_uqi" :
              "jbsr\t___gnu_csky_case_sqi");
    case HImode:
      return (ADDR_DIFF_VEC_FLAGS (diff_vec).offset_unsigned ?
              "jbsr\t___gnu_csky_case_uhi" :
              "jbsr\t___gnu_csky_case_shi");
    case SImode:
      return "jbsr\t___gnu_csky_case_si";
    default:
      gcc_unreachable();
    }
}

/* Implement TARGET_SCHED_ISSUE_RATE.  Lookup the issue rate in the
   per-core tuning structs.  */
static int
csky_sched_issue_rate (void)
{
  if (CSKY_TARGET_ARCH (CK810))
    return 2;
  else
    return 1;
}


/* This function implements the target macro TARGET_SCHED_ADJUST_COST.
   It corrects the value of COST based on the relationship between
   INSN and DEP through the dependence LINK.  It returns the new
   value. There is a per-core adjust_cost hook to adjust scheduler costs
   and the per-core hook can choose to completely override the generic
   adjust_cost function.  */

static int
csky_sched_adjust_cost (rtx_insn *insn ATTRIBUTE_UNUSED,
                        rtx link,
                        rtx_insn *dep ATTRIBUTE_UNUSED,
                        int cost ATTRIBUTE_UNUSED)
{
  if (REG_NOTE_KIND (link) == REG_DEP_ANTI
      || REG_NOTE_KIND (link) == REG_DEP_OUTPUT)
    return 0;
  /* The REG_DEP_TURE situation.  */
  else if (recog_memoized (insn) >= 0
           && recog_memoized (dep) >= 0)
    {
      enum attr_type insn_type = get_attr_type (insn);
      if (CSKY_TARGET_ARCH(CK803))
        {
          /* The ld or st's base reg is depending the pre insn,
             it will delay 1 cycle.  */
          if (insn_type == TYPE_LOAD
              || insn_type == TYPE_STORE)
            {
              rtx pattern = PATTERN (insn);

              gcc_assert (GET_CODE (pattern) == SET);
              rtx addr = (insn_type == TYPE_LOAD) ?
                SET_SRC (pattern) : SET_DEST (pattern);

              enum rtx_code code = GET_CODE (addr);
              if (code == ZERO_EXTEND
                  || code == SIGN_EXTEND)
                {
                  addr = XEXP (addr, 0);
                }
              else if (code == SYMBOL_REF)
                {
                  return cost;
                }
              gcc_assert (GET_CODE (addr) == MEM);

              rtx base =  XEXP (addr, 0);
              rtx reg = NULL_RTX;
              if (REG_P(base))
                {
                  reg = base;
                }
              if (GET_CODE (base) == PLUS
                  && GET_CODE (XEXP (base, 0)) == REG)
                {
                  reg = XEXP (base, 0);
                }
              if ((reg != NULL_RTX) && reg_set_p(reg, PATTERN(dep)))
                return 2;
            }
        }
      else if (CSKY_TARGET_ARCH(CK802))
        {
          if ((insn_type == TYPE_CALL_JSR || insn_type == TYPE_BRANCH_JMP)
              && get_attr_type (dep) != TYPE_LOAD)
            return 1;

          if (insn_type == TYPE_LOAD
              || insn_type == TYPE_STORE)
            {
              rtx pattern = PATTERN (insn);

              gcc_assert (GET_CODE (pattern) == SET);

              rtx addr = (insn_type == TYPE_LOAD) ? SET_SRC (pattern)
                         : SET_DEST(pattern);

              enum rtx_code code = GET_CODE (addr);
              if (code == ZERO_EXTEND
                  || code == SIGN_EXTEND)
                {
                  addr = XEXP (addr, 0);
                }
              gcc_assert (GET_CODE (addr) == MEM);

              rtx base =  XEXP (addr, 0);
              rtx reg = NULL_RTX;
              if (REG_P(base))
                {
                  reg = base;
                }
              if (GET_CODE (base) == PLUS
                  && GET_CODE (XEXP (base, 0)) == REG)
                {
                  reg = XEXP (base, 0);
                }
              if ((reg != NULL_RTX) && reg_set_p(reg, PATTERN(dep))
                  && get_attr_type (dep) != TYPE_LOAD)
                return 1;

              if (insn_type == TYPE_STORE
                  && reg_referenced_p(SET_SRC(pattern), PATTERN(dep)))
                {
                  return 1;
                }
            }
        }
    }
  return cost;
}

static bool
csky_warn_func_return (tree decl)
{
  /* Naked functions are implemented entirely in assembly, including the
     return sequence, so suppress warnings about this.  */
  return lookup_attribute ("naked", DECL_ATTRIBUTES (decl)) == NULL_TREE;
}


/* Decide whether TYPE should be returned in memory (true)
   or in a register (false).  FNTYPE is the type of the function making
   the call.  */
static bool
csky_return_in_memory (const_tree type,
                       const_tree fntype ATTRIBUTE_UNUSED)
{
  const HOST_WIDE_INT size = int_size_in_bytes (type);

  if (TARGET_HARD_FLOAT_ABI && CSKY_ISA_FEATURE(vdsp)
      && TREE_CODE (type) == VECTOR_TYPE)
    {
      int vector_byte = flag_csky_vdsp_width / 8;

      gcc_assert (vector_byte == 8 || vector_byte == 16);
      return (size == -1 || size > vector_byte);
    }
  else
    return (size == -1 || size > 2 * UNITS_PER_WORD);
}


/* Dwarf models VFP registers as  64-bit or 128-bit registers default.
   GCC models tham as 32-bit registers, so we need to describe this to
   the DWARF generation code.  Other registers can use the default.  */
static rtx
csky_dwarf_register_span (rtx rtl)
{
  machine_mode mode;
  unsigned regno;
  rtx parts[16];
  int nregs;
  int i;

  regno = REGNO (rtl);
  if (!CSKY_VREG_P (regno))
    return NULL_RTX;

  mode = GET_MODE (rtl);
  if (GET_MODE_SIZE (mode) < 8)
    return NULL_RTX;
  /* FIXME 128bits register cannot be handled now,
     some other method should be used to fix it,
     such as define the DWARF FRMAE information by ourself.  */
  if (CSKY_ISA_FEATURE (vdsp128)
      && csky_vector_mode_supported_p (mode))
    return NULL_RTX;

  if (TARGET_SINGLE_FPU)
    {
      nregs = GET_MODE_SIZE (mode) / 4;
      for (i = 0; i < nregs; i += 2)
      if (TARGET_BIG_ENDIAN)
        {
          parts[i] = gen_rtx_REG (SImode, regno + i + 1);
          parts[i + 1] = gen_rtx_REG (SImode, regno + i);
        }
      else
        {
          parts[i] = gen_rtx_REG (SImode, regno + i);
          parts[i + 1] = gen_rtx_REG (SImode, regno + i + 1);
        }
    }
  else
    {
      /* FIXME dwarf2 consider all general registers are the same
         as the CPU bit width. Transform the 64bits FPU register to
         32bits here, and we will modify the unwind processing to
         fit CSKY architecture later.  */
      nregs = GET_MODE_SIZE (mode) / 4;
      for (i = 0; i < nregs; i += 2)
      if (TARGET_BIG_ENDIAN)
        {
          parts[i] = gen_rtx_REG (SImode, regno + i - 16);
          parts[i + 1] = gen_rtx_REG (SImode, regno + i);
        }
      else
        {
          parts[i] = gen_rtx_REG (SImode, regno + i);
          parts[i + 1] = gen_rtx_REG (SImode, regno + i - 16);
        }
    }

  return gen_rtx_PARALLEL (VOIDmode, gen_rtvec_v (nregs , parts));
}

/* Set up library functions unique to CSKY.  */

static void
csky_init_libfuncs(void)
{
  if (TARGET_CSKY_LINUX)
    init_sync_libfuncs (UNITS_PER_WORD);
}


/* Return cost of the memory address x.
   For csky, it is same cost between (register) and (register + offset).
   Other situations will cost more.  */

static int
csky_address_cost (rtx x, machine_mode mode ATTRIBUTE_UNUSED,
                   addr_space_t as ATTRIBUTE_UNUSED, bool speed ATTRIBUTE_UNUSED)
{
  enum rtx_code code = GET_CODE (x);

  if (code == POST_INC)
    return 0;
  if (code == REG)
    return COSTS_N_INSNS (1);
  if (code == PLUS
      && REG_P (XEXP (x, 0))
      && CONST_INT_P (XEXP (x, 1)))
    return COSTS_N_INSNS (1);

  return COSTS_N_INSNS (3);
}


/* Return the fixed registers used for condition codes.  */

static bool
csky_fixed_condition_code_regs (unsigned int *p1, unsigned int *p2)
{
  *p1 = CSKY_CC_REGNUM;
  *p2 = INVALID_REGNUM;
  return true;
}


/* Insn fetch status used to detect insn fetch confilict when
   scheduling, lrw will set the fetch status to FETCH_TEXT,
   ld/st will set the fetch status to FETCH_DATA.  */
enum insn_fetch_status
{
    NONE,
    FETCH_TEXT,
    FETCH_DATA
};


/* According to CURR_STATUS and INSN, change the CURR_STATUS and
   return true if the INSN will cause the insn fetch conflict.  */

static bool
check_insn_fetch_conflict (rtx_insn *insn, enum insn_fetch_status *curr_status)
{
  gcc_assert (insn && INSN_P (insn));

  if (DEBUG_INSN_P (insn))
    return false;

  if (GET_CODE (PATTERN (insn)) == SET)
  {
    /* Find the lrw and set the insn fetch status to FETCH_TEXT.  */
    if (GET_CODE (XEXP(PATTERN(insn), 0)) == REG
        && GET_CODE (XEXP(PATTERN(insn), 1)) == SYMBOL_REF)
    {
      switch (*curr_status)
        {
        case NONE:
          *curr_status = FETCH_TEXT;
          break;
        case FETCH_DATA:
          return true;
        case FETCH_TEXT:
          return false;
        }
    }
    /* Find the ld/st and set the insn fetch status to FETCH_DATA.  */
    else if ((GET_CODE (XEXP(PATTERN(insn), 0)) == REG
                && GET_CODE (XEXP(PATTERN(insn), 1)) == MEM)
            || (GET_CODE (XEXP(PATTERN(insn), 0)) == MEM
                && GET_CODE (XEXP(PATTERN(insn), 1)) == REG))
    {
      switch (*curr_status)
        {
        case NONE:
          *curr_status = FETCH_DATA;
          break;
        case FETCH_DATA:
          return false;
        case FETCH_TEXT:
          return true;
        }
    }
    /* Other insn set insn fetch status to NONE.  */
    else
    {
      *curr_status = NONE;
    }
    return false;
  }
  else
  {
    *curr_status = NONE;
    return false;
  }
}


/* To check extra resource confilict before issue insns in
   schedule ready list, if the INSN will cause resource
   confilict, return true so that the insn will be queued
   for COST cycles. LAST_SCHED_INSN is the last scheduled
   no debug instruction.  */

static bool
csky_sched_extra_resource_confilict (rtx_insn *insn,
                                     int *cost,
                                     rtx_insn *last_sched_insn)
{
  enum insn_fetch_status current_insn_fetch_status = NONE;

  if (!reload_completed)
    return false;

  if (CSKY_TARGET_ARCH(CK801)
      || CSKY_TARGET_ARCH(CK802)
      || CSKY_TARGET_ARCH(CK803))
    {
      /* Use LAST_SCHED_INSN to initialize fetch status.  */
      if ((last_sched_insn != NULL) && INSN_P(last_sched_insn))
        check_insn_fetch_conflict (last_sched_insn, &current_insn_fetch_status);
      /* If INSN do cause fetch conflict, queue for 1 cycle.  */
      if (check_insn_fetch_conflict (insn, &current_insn_fetch_status))
        {
          *cost = 1;
          return true;
        }
      else
        return false;
    }

  return false;
}

void
csky_init_cumulative_args (CUMULATIVE_ARGS *pcum, tree fntype,
        rtx libname,
        tree fndecl ATTRIBUTE_UNUSED)
{
  memset(pcum, 0, sizeof(*pcum));
  if (stdarg_p (fntype))
    pcum->is_stdarg = true;
}


/* Return true if VALUE is the constants can be currently split
   by csky_split_constant, else return false.  */

bool
csky_can_split_constant (enum rtx_code code,
                         rtx insn,
                         HOST_WIDE_INT value)
{
  enum csky_inline_const_type trick_type;
  HOST_WIDE_INT x = 0, y = 0;
  rtx cond;

  if (insn && GET_CODE (PATTERN (insn)) == COND_EXEC)
    cond = COND_EXEC_TEST (PATTERN (insn));
  else
    cond = NULL_RTX;

  trick_type = try_csky_constant_tricks (value, &x, &y);

  if (trick_type == IC_APPEND_SUBI && code == SET && !cond)
    return true;
  else
    return false;
}

/* Emit a sequence of insns to handle a large constant.
   CODE is the code of the operation required, it can be any of SET, PLUS,
   IOR, AND, XOR, MINUS;
   MODE is the mode in which the operation is being performed;
   VAL is the integer to operate on;
   SOURCE is the other operand (a register, or a null-pointer for SET);
   SUBTARGETS means it is safe to create scratch registers if that will
   either produce a simpler sequence, or we will want to cse the values.
   Return value is the number of insns emitted.  */

int
csky_split_constant (enum rtx_code code, machine_mode mode, rtx insn,
                     HOST_WIDE_INT val, rtx target, rtx source,
                     int subtargets)
{
  enum csky_inline_const_type trick_type;
  HOST_WIDE_INT x = 0, y = 0;
  rtx cond;

  if (insn && GET_CODE (PATTERN (insn)) == COND_EXEC)
    cond = COND_EXEC_TEST (PATTERN (insn));
  else
    cond = NULL_RTX;

  trick_type = try_csky_constant_tricks (val, &x, &y);

  if (trick_type == IC_APPEND_SUBI && code == SET && !cond)
    {
      x = trunc_int_for_mode (x, SImode);
      y = trunc_int_for_mode (y, SImode);
      emit_insn (gen_rtx_SET (target, GEN_INT (x)));
      emit_insn (gen_subsi3 (target, target, GEN_INT (y)));
    }
  /*TODO supplement other const values and codes.  */
  else
    {
      rtx pattern = gen_rtx_SET (target, GEN_INT (val));
      if (cond)
        pattern = gen_rtx_COND_EXEC (VOIDmode, copy_rtx (cond), pattern);
      emit_insn (pattern);
    }
}

/* Implement TARGET_CAN_USE_DOLOOP_P.  */

static bool
csky_can_use_doloop_p (const widest_int &iterations, const widest_int & iterations_max,
                         unsigned int loop_level, bool entered_at_top)
{
  if (!(CSKY_ISA_FEATURE(dspv2) || CSKY_ISA_FEATURE(3E3r2)))
    return false;

  /* Considering limitations in the hardware, only use doloop
     for innermost loops which must be entered from the top.  */
  if (!entered_at_top || (CSKY_ISA_FEATURE(dspv2)) && loop_level > 1)
      return false;
  return !(CSKY_ISA_FEATURE(dspv2)) || (wi::gtu_p (iterations, 0) && wi::leu_p (iterations, 0x10000));
}


/* NULL if INSN insn is valid within a low-overhead loop.
   Otherwise return why doloop cannot be applied.  */

static const char *
csky_invalid_within_doloop (const rtx_insn *insn)
{
  basic_block bb = BLOCK_FOR_INSN (insn);

  if (CALL_P (insn))
    return "Function call in the loop.";
  loop* l = bb->loop_father;
  if (CSKY_ISA_FEATURE(dspv2) && !CSKY_ISA_FEATURE(3E3r2) && l->num_nodes > 2)
    return "Jump instruction in the loop.";

  if (tablejump_p (insn, NULL, NULL) || computed_jump_p (insn))
    return "Computed branch in the loop.";

  /* This checking only be enabled on those kind of CPU features:
     any serial of CK803 CPU with R2 feature but no hreg feature.  */
  if (CSKY_ISA_FEATURE(dspv2) || CSKY_ISA_FEATURE(3E3r2))
    {
      if (loop_depth(l) > 5)
        return "Nesting too deeply for this loop.";
    }
  return NULL;
}

enum csky_cond_code
maybe_get_csky_condition_code (rtx comparison)
{
  machine_mode mode = GET_MODE (XEXP (comparison, 0));
  enum csky_cond_code code;
  enum rtx_code comp_code = GET_CODE (comparison);

  switch (comp_code)
    {
      case NE: return CSKY_NE;
      case EQ: return CSKY_EQ;
      case GE: return CSKY_GE;
      case GT: return CSKY_GT;
      case LE: return CSKY_LE;
      case LT: return CSKY_LT;
      case GEU: return CSKY_GEU;
      case GTU: return CSKY_GTU;
      case LEU: return CSKY_LEU;
      case LTU: return CSKY_LTU;
      default: return CSKY_NV;
    }
}

/* Like maybe_get_csky_condition_code, but never return CSKY_NV.  */
static enum csky_cond_code
get_csky_condition_code (rtx comparison)
{
  enum csky_cond_code code = maybe_get_csky_condition_code (comparison);
  gcc_assert (code != CSKY_NV);
  return code;
}

/* Tell csky_asm_output_opcode to output SCE blocks for conditionally executed
   instructions.  */
void
csky_final_prescan_insn (rtx_insn *insn)
{
  rtx_insn *first_insn = insn;
  rtx body = PATTERN (insn);
  rtx predicate;
  enum csky_cond_code code;
  int n;
  int mask;
  int fixed_num;

  /* max_insns_skipped in the tune was already taken into account in the
     cost model of ifcvt pass when generating COND_EXEC insns.  At this stage
     just emit the SCE blocks as we can.  It does not make sense to split
     the SCE blocks.  */
  fixed_num = FIXED_CONDITIONAL_EXECUTE;

  /* Remove the previous insn from the count of insns to be output.  */
  if (csky_condexec_count)
      csky_condexec_count--;

  /* Nothing to do if we are already inside a conditional block.  */
  if (csky_condexec_count)
    return;

  if (GET_CODE (body) != COND_EXEC)
    return;

  /* Conditional jumps are implemented directly.  */
  if (JUMP_P (insn))
    return;

  predicate = COND_EXEC_TEST (body);
  csky_current_cc = get_csky_condition_code (predicate);

  n = get_attr_ce_count (insn);
  csky_condexec_count = 1;
  csky_condexec_mask = (1 << n) - 1;
  csky_condexec_masklen = n;
   /* See if subsequent instructions can be combined into the same block.  */
  for (;;)
    {
      insn = next_nonnote_insn (insn);

      /* Jumping into the middle of an SCE block is illegal, so a label or
         barrier terminates the block.  */
      if (!NONJUMP_INSN_P (insn) && !JUMP_P (insn))
        break;

      body = PATTERN (insn);
      /* USE and CLOBBER aren't really insns, so just skip them.  */
      if (GET_CODE (body) == USE
          || GET_CODE (body) == CLOBBER)
        continue;

      /* ??? Recognize conditional jumps, and combine them with SCE blocks.  */
      if (GET_CODE (body) != COND_EXEC)
        break;
      /* Fixed number of conditionally executed instructions in a block.  */
      n = get_attr_ce_count (insn);
      if (csky_condexec_masklen + n > fixed_num)
        break;

      predicate = COND_EXEC_TEST (body);
      code = get_csky_condition_code (predicate);
      mask = (1 << n) - 1;
      if (csky_current_cc == code)
        csky_condexec_mask |= (mask << csky_condexec_masklen);
      else if (csky_current_cc != CSKY_INVERSE_CONDITION_CODE(code))
        break;

      csky_condexec_count++;
      csky_condexec_masklen += n;

      /* A jump must be the last instruction in a conditional block.  */
      if (JUMP_P (insn))
        break;
    }
  /* Restore recog_data (getting the attributes of other insns can
     destroy this array, but final.c assumes that it remains intact
     across this call).  */
  extract_constrain_insn_cached (first_insn);
}

/* Output SCE instructions.  */
void
csky_asm_output_opcode (FILE * stream)
{
  char buff[]="0000";
  int cond = 0;
  int n,i = 0;

  if (csky_condexec_mask)
    {
      for (n = 0; n < csky_condexec_masklen; n++)
        buff[3 - n] = (csky_condexec_mask & (1 << n)) ? '1' : '0';
      while(buff[i++])
        /* convert binary mask to demical number */
        cond = cond * 2 + buff[i - 1] - '0';
      asm_fprintf(stream, "sce\t%d\n\t", cond);
      csky_condexec_mask = 0;
    }
}


static bool
csky_have_conditional_execution (void)
{
  return (CSKY_ISA_FEATURE(2E3)
          && !CSKY_TARGET_ARCH(CK860)
          && !flag_schedule_insns_after_reload);
}

int
csky_max_conditional_execute (void)
{
  return 4;
}

int
csky_fixed_conditional_execute (void)
{
  return 4;
}

/* Implements target hook vector_mode_supported_p.  */
bool
csky_vector_mode_supported_p (machine_mode mode)
{
  if (CSKY_ISA_FEATURE(dspv2)  && (mode == V4QImode || mode == V2HImode
     || mode == V2SImode || mode == V4HImode || mode == V4QQmode
     || mode == V2HQmode || mode == V2SQmode || mode == V4UQQmode
     || mode == V2UHQmode || mode == V2USQmode))
    return true;

  if (CSKY_ISA_FEATURE(vdsp128)  && (mode == V16QImode || mode == V8HImode || mode == V4SImode
      || mode == V16QQmode || mode == V8HQmode || mode == V4SQmode
      || mode == V16UQQmode || mode == V8UHQmode || mode == V4USQmode))
    return true;

  if (CSKY_ISA_FEATURE(vdsp64)  && (mode == V8QImode || mode == V4HImode || mode == V2SImode
      || mode == V8QQmode || mode == V4HQmode || mode == V2SQmode
      || mode == V8UQQmode || mode == V4UHQmode || mode == V2USQmode))
    return true;

  return false;
}

bool
decompose_csky_address_v (rtx addr, struct csky_address * out)
{
  rtx base = NULL_RTX, index = NULL_RTX;

  out->base = out->index = NULL_RTX;

  if (GET_CODE (addr) == PLUS)
    {
      rtx addends[4];

      addends[0] = XEXP (addr, 1);
      addends[1] = XEXP (addr, 0);

      if (GET_CODE (addends[0]) == REG)
        base = addends[0];

      enum rtx_code code = GET_CODE (addends[1]);

      switch (code)
      {
        case MULT:
        case ASHIFT :
          addends[2] = XEXP (addends[1], 0);
          addends[3] = XEXP (addends[1], 1);
          if (GET_CODE (addends[2]) == REG && GET_CODE (addends[3]) == CONST_INT)
            index = addends[1];
          else
            return false;
          break;
      /* The instruction vldrd/vldrq rz, (rx, ry << 0) */
        case  REG:
          index = addends[1];
        default:
          break;
      }
    }
  if (!base)
    return false;

  out->base = base;
  out->index = index;

  return true;
}

const char *
output_csky_move_v (rtx operands[])
{
  rtx dst = operands[0];
  rtx src = operands[1];
  struct csky_address op0, op1;

  if (REG_P (dst))
    {
      if (GET_CODE (src) == MEM)
        {

          decompose_csky_address_v (XEXP (src, 0), &op1);

          if (op1.index)
            {
              switch (GET_MODE (src))
                {
                  case V8QImode:
                  case V8QQmode:
                  case V8UQQmode:
                    return "vldrd.8\t%0, %1";
                  case V4HImode:
                  case V4HQmode:
                  case V4UHQmode:
                    return "vldrd.16\t%0, %1";
                  case V2SImode:
                  case V2SQmode:
                  case V2USQmode:
                    return "vldrd.32\t%0, %1";
                  case V16QImode:
                  case V16QQmode:
                  case V16UQQmode:
                    return "vldrq.8\t%0, %1";
                  case V8HImode:
                  case V8HQmode:
                  case V8UHQmode:
                    return "vldrq.16\t%0, %1";
                  case V4SImode:
                  case V4SQmode:
                  case V4USQmode:
                    return "vldrq.32\t%0, %1";
                  default:
                    gcc_unreachable ();
                }
            }
          else
            {
              switch (GET_MODE (src))
                {
                  case V8QImode:
                  case V8QQmode:
                  case V8UQQmode:
                    return "vldd.8\t%0, %1";
                  case V4HImode:
                  case V4HQmode:
                  case V4UHQmode:
                    return "vldd.16\t%0, %1";
                  case V2SImode:
                  case V2SQmode:
                  case V2USQmode:
                    return "vldd.32\t%0, %1";
                  case V16QImode:
                  case V16QQmode:
                  case V16UQQmode:
                    return "vldq.8\t%0, %1";
                  case V8HImode:
                  case V8HQmode:
                  case V8UHQmode:
                    return "vldq.16\t%0, %1";
                  case V4SImode:
                  case V4SQmode:
                  case V4USQmode:
                    return "vldq.32\t%0, %1";
                  default:
                    gcc_unreachable ();
                }
            }
        }
      else if (REG_P (src))
        {
          int srcreg = REGNO (src);
          int dstreg = REGNO (dst);

          if (CSKY_VREG_P (srcreg) && CSKY_VREG_P (dstreg))
            {
              return "vmov\t%0, %1";
            }
          else if (CSKY_GENERAL_REGNO_P (srcreg)
                   && CSKY_GENERAL_REGNO_P (dstreg))
            {
              switch (GET_MODE_SIZE (GET_MODE (src)))
                {
                  case 4:
                    return "mov\t%0, %1";
                  case 8:
                    return "mov\t%R0, %R1\n\tmov\t%0, %1";
                  case 16:
                    return "mov\t%T0, %T1\n\tmov\t%S0, %S1\n\tmov\t%R0, %R1\n\tmov\t%0, %1";
                  default:
                    gcc_unreachable ();
                }
            }
          else if (CSKY_VREG_P (srcreg))
            {
              switch (GET_MODE (src))
                {
                  case V8QImode:
                  case V8QQmode:
                  case V8UQQmode:
                  case V4HImode:
                  case V4HQmode:
                  case V4UHQmode:
                  case V2SImode:
                  case V2SQmode:
                  case V2USQmode:
                    return "vmfvr.u32\t%R0, %1[1]\n\tvmfvr.u32\t%0, %1[0]";
                  case V16QImode:
                  case V16QQmode:
                  case V16UQQmode:
                  case V8HImode:
                  case V8HQmode:
                  case V8UHQmode:
                  case V4SImode:
                  case V4SQmode:
                  case V4USQmode:
                    return "vmfvr.u32\t%T0, %1[3]\n\tvmfvr.u32\t%S0, %1[2]\n\tvmfvr.u32\t%R0, %1[1]\n\tvmfvr.u32\t%0, %1[0]";
                  default:
                    gcc_unreachable ();
                }
            }
          else if (CSKY_VREG_P (dstreg))
            {
              switch (GET_MODE (src))
                {
                  case V8QImode:
                  case V8QQmode:
                  case V8UQQmode:
                  case V4HImode:
                  case V4HQmode:
                  case V4UHQmode:
                  case V2SImode:
                  case V2SQmode:
                  case V2USQmode:
                    return "vmtvr.u32\t%0[1], %R1\n\tvmtvr.u32\t%0[0], %1";
                  case V16QImode:
                  case V16QQmode:
                  case V16UQQmode:
                  case V8HImode:
                  case V8HQmode:
                  case V8UHQmode:
                  case V4SImode:
                  case V4SQmode:
                  case V4USQmode:
                    return "vmtvr.u32\t%0[3], %T1\n\tvmtvr.u32\t%0[2], %S1\n\tvmtvr.u32\t%0[1], %R1\n\tvmtvr.u32\t%0[0], %1";
                  default:
                    gcc_unreachable ();
                }
            }
        }
    }
  else if (GET_CODE (dst) == MEM)
    {
      decompose_csky_address_v (XEXP (dst, 0), &op0);

      if (op0.index)
        {
          switch (GET_MODE (dst))
            {
              case V8QImode:
              case V8QQmode:
              case V8UQQmode:
                return "vstrd.8\t%1, %0";
              case V4HImode:
              case V4HQmode:
              case V4UHQmode:
                return "vstrd.16\t%1, %0";
              case V2SImode:
              case V2SQmode:
              case V2USQmode:
                return "vstrd.32\t%1, %0";
              case V16QImode:
              case V16QQmode:
              case V16UQQmode:
                return "vstrq.8\t%1, %0";
              case V8HImode:
              case V8HQmode:
              case V8UHQmode:
                return "vstrq.16\t%1, %0";
              case V4SImode:
              case V4SQmode:
              case V4USQmode:
                return "vstrq.32\t%1, %0";
              default:
                gcc_unreachable ();
             }
        }
      else
        {
          switch (GET_MODE (src))
            {
              case V8QImode:
              case V8QQmode:
              case V8UQQmode:
                return "vstd.8\t%1, %0";
              case V4HImode:
              case V4HQmode:
              case V4UHQmode:
                return "vstd.16\t%1, %0";
              case V2SImode:
              case V2SQmode:
              case V2USQmode:
                return "vstd.32\t%1, %0";
              case V16QImode:
              case V16QQmode:
              case V16UQQmode:
                return "vstq.8\t%1, %0";
              case V8HImode:
              case V8HQmode:
              case V8UHQmode:
                return "vstq.16\t%1, %0";
              case V4SImode:
              case V4SQmode:
              case V4USQmode:
                return "vstq.32\t%1, %0";
              default:
                gcc_unreachable ();
            }
        }
    }
  gcc_unreachable ();
}

static machine_mode
csky_preferred_simd_mode (machine_mode mode)
{
  if (CSKY_ISA_FEATURE(vdsp))
    {
      switch (mode)
        {
          case QImode:
            return (CSKY_ISA_FEATURE(vdsp128) ? V16QImode : V8QImode);
          case HImode:
            return (CSKY_ISA_FEATURE(vdsp128) ? V8HImode : V4HImode);
          case SImode:
            return (CSKY_ISA_FEATURE(vdsp128) ? V4SImode : V2SImode);
          default:
            break;
        }
    }
  if (CSKY_ISA_FEATURE(dspv2))
    {
      switch (mode)
        {
          case QImode:
            return V4QImode;
          case HImode:
            return V2HImode;
          default:
            break;
        }
    }
  return word_mode;
}

void
csky_const_bounds (rtx operand, HOST_WIDE_INT low, HOST_WIDE_INT high)
{
  HOST_WIDE_INT value;

  gcc_assert (CONST_INT_P (operand));

  value = INTVAL (operand);

  if (value < low || value >= high)
    {
      error ("constant %wd out of range %wd - %wd", value,
             low, high - 1);
    }
}

/* Implement TARGET_SCALAR_MODE_SUPPORTED_P.
   Add fixed point mode rather than default.  */

static bool
csky_scalar_mode_supported_p (machine_mode mode)
{
  if (ALL_FIXED_POINT_MODE_P (mode))
    return true;
  else
    return default_scalar_mode_supported_p (mode);
}

/* Check if specified Register operand is eliminable later or not.
   Return true if eliminable. Otherwise return false.  */
int
csky_eliminable_register(rtx op)
{
  return REG_P (op) && (REGNO (op) == FRAME_POINTER_REGNUM
                         || REGNO (op) == ARG_POINTER_REGNUM);
}

/* Define this macro if it is advisable to hold scalars in registers
   in a wider mode than that declared by the program.  In such cases,
   the value is constrained to be within the bounds of the declared
   type, but kept valid in the wider mode.  The signedness of the
   extension may differ from that of the type.  */

static machine_mode
csky_promote_function_mode (const_tree type ATTRIBUTE_UNUSED,
                           machine_mode mode,
                           int *punsignedp ATTRIBUTE_UNUSED,
                           const_tree fntype ATTRIBUTE_UNUSED,
                           int for_return ATTRIBUTE_UNUSED)
{
  if (GET_MODE_CLASS (mode) == MODE_INT
      && GET_MODE_SIZE (mode) < UNITS_PER_WORD)
    return SImode;

  return mode;
}

struct gcc_target targetm = TARGET_INITIALIZER;

#include "gt-abiv2-csky.h"

