/* Prototypes for exported functions defined in csky.c
   Copyright (C) 2000-2016 Free Software Foundation, Inc.
   Contributed by CSKY.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#ifndef GCC_ABIV1_CSKY_PROTOS_H
#define GCC_ABIV1_CSKY_PROTOS_H

struct csky_address
{
  rtx base, index, disp;
  HOST_WIDE_INT scale;
};

struct csky_processors
{
  const char *const name;
  const unsigned long arch_flags;
  const unsigned long csky_flags;
  const unsigned long sub_target_flags;
};

struct csky_architectures
{
  const char *const name;
  const unsigned long arch_flags;
  const unsigned long csky_flags;
};

struct csky_frame
{
  int arg_size;			/* Stdarg spills (bytes).  */
  int reg_size;			/* Non-volatile reg saves (bytes).  */
  int reg_mask;			/* Non-volatile reg saves.  */
  int local_size;		/* Locals.  */
  int outbound_size;		/* Arg overflow on calls out.  */
  int pad_outbound;
  int pad_local;
  int pad_reg;
  /* Describe the steps we'll use to grow it.  */
#define MAX_STACK_GROWS 4	/* Gives us some spare space.  */
  int growth[MAX_STACK_GROWS];
  int arg_offset;
  int reg_offset;
  int reg_growth;
  int local_growth;
};

/* Supported TLS relocations.  */

enum tls_reloc
{
  TLS_GD32,
  TLS_LDM32,
  TLS_LDO32,
  TLS_IE32,
  TLS_LE32
};

extern const char *csky_output_jump_label_table (void);
extern void csky_expand_prolog (void);
extern void csky_expand_epilog (void);
extern int csky_const_ok_for_inline (HOST_WIDE_INT);
extern int csky_num_ones (HOST_WIDE_INT);
extern int csky_num_zeros (HOST_WIDE_INT);
extern int csky_initial_elimination_offset (int, int);
extern int csky_byte_offset (unsigned int);
extern int csky_halfword_offset (unsigned int);
extern int csky_const_trick_uses_not (HOST_WIDE_INT);
extern int csky_naked_function_p (void);

#ifdef TREE_CODE
#ifdef HAVE_MACHINE_MODES
extern int csky_num_arg_regs (machine_mode, const_tree);
#endif /* HAVE_MACHINE_MODES */

#ifdef RTX_CODE
extern rtx csky_function_value (const_tree, const_tree);
#endif /* RTX_CODE */
#endif /* TREE_CODE */

#ifdef RTX_CODE

extern const char *csky_output_bclri (rtx, int);
extern const char *csky_output_bseti (rtx, int);
extern const char *csky_output_cmov (rtx *, int, const char *);
extern char *csky_output_call (rtx *, int);
extern int csky_op_is_dead (rtx_insn *, rtx);
extern int csky_expand_insv (rtx *);
extern const char *csky_output_andn (rtx, rtx *);
extern bool csky_gen_compare (RTX_CODE, rtx, rtx);
extern bool csky_gen_compare_float (RTX_CODE, rtx, rtx);
extern int csky_symbolic_address_p (rtx);
extern bool csky_r15_operand_p (rtx);
extern enum reg_class csky_secondary_reload_class (enum reg_class,
                                                   machine_mode, rtx);
extern enum reg_class csky_reload_class (rtx, enum reg_class);
extern int csky_is_same_reg (rtx, rtx);

#ifdef HAVE_MACHINE_MODES
extern const char *csky_output_move (rtx, rtx *, machine_mode);
extern const char *csky_output_movedouble (rtx *, machine_mode);
extern int const_ok_for_csky (HOST_WIDE_INT);
#endif /* HAVE_MACHINE_MODES */
#endif /* RTX_CODE */

extern int tls_mentioned_p (rtx);
extern int symbol_mentioned_p (rtx);
extern int label_mentioned_p (rtx);
extern bool csky_tls_referenced_p (rtx);
extern rtx legitimize_tls_address (rtx, rtx);
extern rtx legitimize_pic_address (rtx, enum machine_mode, rtx, int);

extern void csky_set_eh_return_address (rtx, rtx);

extern rtx csky_return_addr (int, rtx);

extern int csky_default_branch_cost (bool speed_p, bool predictable_p);
extern bool csky_default_logical_op_non_short_circuit(void);
extern bool csky_pad_arg_upward (machine_mode, const_tree);
extern bool csky_pad_reg_upward (machine_mode, tree, int);

#endif /* ! GCC_ABIV1_CSKY_PROTOS_H */
