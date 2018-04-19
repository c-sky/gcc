/* Output routines for CSKY processor
   Copyright (C) 1993-2016 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

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
#include "optabs.h"
#include "emit-rtl.h"
#include "diagnostic-core.h"
#include "stor-layout.h"
#include "varasm.h"
#include "calls.h"
#include "abiv1_csky.h"
#include "output.h"
#include "explow.h"
#include "expr.h"
#include "cfgrtl.h"
#include "builtins.h"
#include "regs.h"
#include "flags.h"
#include "rtl-iter.h"
#include "ggc.h"
#include "reload.h"
#include "dumpfile.h"
#include "recog.h"

/* This file should be included last.  */
#include "target-def.h"

/* For dumping information about frame sizes.  */
char *csky_current_function_name = 0;

/* Global variables for machine-dependent things.  */

/* Provides the class number of the smallest class containing
   reg number.  */
const enum reg_class regno_reg_class[FIRST_PSEUDO_REGISTER] =
{
  GENERAL_REGS, RWCPCR_REGS, LRW_REGS, LRW_REGS,
  LRW_REGS, LRW_REGS, LRW_REGS, LRW_REGS,
  LRW_REGS, LRW_REGS, LRW_REGS, LRW_REGS,
  LRW_REGS, LRW_REGS, LRW_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  /* 32 */
  GENERAL_REGS, C_REGS, GENERAL_REGS, OTHER_REGS,
  HI_REGS, LO_REGS,
  /* 38 */
  FPU_REGS, FPU_REGS, FPU_REGS, FPU_REGS,
  FPU_REGS, FPU_REGS, FPU_REGS, FPU_REGS,
  FPU_REGS, FPU_REGS, FPU_REGS, FPU_REGS,
  FPU_REGS, FPU_REGS, FPU_REGS, FPU_REGS,
  FPU_REGS, FPU_REGS, FPU_REGS, FPU_REGS,
  FPU_REGS, FPU_REGS, FPU_REGS, FPU_REGS,
  FPU_REGS, FPU_REGS, FPU_REGS, FPU_REGS,
  FPU_REGS, FPU_REGS, FPU_REGS, FPU_REGS,
};

const int csky_dbg_register_map[FIRST_PSEUDO_REGISTER] = {
  0, 1, 2, 3, 4, 5, 6, 7,
  8, 9, 10, 11, 12, 13, 14, 15,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, 56,
  20, 21,
  24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 38, 39,
  40, 41, 42, 43, 44, 45, 46, 47,
  48, 49, 50, 51, 52, 53, 54, 55,
};

unsigned long arch_flags = 0;
unsigned long csky_flags = 0;

static const struct csky_processors csky_all_processors[] = {
  /* 510 Serial */
  {"ck510", MASK_ARCH_CK510 | MASK_INST_CSKYV1, 0UL, 0UL},
  {"ck510e", MASK_ARCH_CK510 | MASK_INST_CSKYV1, 0UL, MASK_DSP},
  {"ck520", MASK_ARCH_CK510 | MASK_INST_CSKYV1, 0UL, MASK_SECURITY},
  /* ck610 Serial */
  {"ck610", MASK_ARCH_CK610 | MASK_INST_CSKYV1, 0UL, 0UL},
  {"ck610e", MASK_ARCH_CK610 | MASK_INST_CSKYV1, 0UL, MASK_DSP},
  {"ck610f", MASK_ARCH_CK610 | MASK_INST_CSKYV1, 0UL, MASK_FPUV1},
  {"ck610ef", MASK_ARCH_CK610 | MASK_INST_CSKYV1, 0UL, MASK_DSP | MASK_FPUV1},
  {"ck620", MASK_ARCH_CK610 | MASK_INST_CSKYV1, 0UL, MASK_SECURITY},
  {"ck620f", MASK_ARCH_CK610 | MASK_INST_CSKYV1, 0UL,
   MASK_SECURITY | MASK_FPUV1},
};

static const int csky_num_cpu =
  sizeof (csky_all_processors) / sizeof (csky_all_processors[0]);


static const struct csky_architectures csky_all_architectures[] = {
  {"ck510", MASK_ARCH_CK510 | MASK_INST_CSKYV1, 0UL},
  {"ck610", MASK_ARCH_CK610 | MASK_INST_CSKYV1, 0UL},
};

static const int csky_num_arch =
  sizeof (csky_all_architectures) / sizeof (csky_all_architectures[0]);

int flag_stack_protect_cskyv1 = 0;

#define TARGET_PRELOAD_PROTECT ((optimize == 0) ||  flag_preload_protect)


static void output_stack_adjust (int, int);
static int calc_live_r0_r31_regs (int *);
static int try_constant_tricks (HOST_WIDE_INT, HOST_WIDE_INT *,
                                HOST_WIDE_INT *);
static const char *output_inline_const (machine_mode, rtx *);
static void layout_csky_frame (struct csky_frame *);
static void csky_setup_incoming_varargs (cumulative_args_t, machine_mode,
                                         tree, int *, int);
//static void csky_reorg (void);
static tree csky_handle_naked_attribute (tree *, tree, tree, int, bool *);
static void csky_print_operand (FILE *, rtx, int);
static void csky_print_operand_address (FILE *, machine_mode, rtx);
static bool csky_print_operand_punct_valid_p (unsigned char code);
static int csky_const_costs (rtx, RTX_CODE);
static bool csky_rtx_costs (rtx, machine_mode, int, int, int *, bool);
static int csky_address_cost (rtx, machine_mode, addr_space_t, bool);
static int csky_register_move_cost (machine_mode, reg_class_t, reg_class_t);
static bool csky_return_in_memory (const_tree, const_tree);
static rtx csky_function_value (const_tree, const_tree, bool);
static bool csky_function_value_regno_p (const unsigned int regno);
static int csky_arg_partial_bytes (cumulative_args_t,
                                   machine_mode, tree, bool);
static rtx csky_function_arg (cumulative_args_t,
                              machine_mode, const_tree, bool);
static void csky_function_arg_advance (cumulative_args_t,
                                       machine_mode, const_tree, bool);
static unsigned int csky_function_arg_boundary (machine_mode, const_tree);
static void csky_asm_trampoline_template (FILE *);
static void csky_trampoline_init (rtx, tree, rtx);
static bool csky_warn_func_return (tree);
static void csky_option_override (void);
static bool csky_legitimate_constant_p (machine_mode, rtx);
static bool csky_legitimate_address_p (machine_mode, rtx, bool, addr_space_t);
static reg_class_t csky_preferred_reload_class (rtx, reg_class_t);
static reg_class_t csky_secondary_reload (bool, rtx, reg_class_t,
                                          machine_mode,
                                          secondary_reload_info *);
static void csky_conditional_register_usage (void);
static void csky_output_mi_thunk (FILE *, tree, HOST_WIDE_INT, HOST_WIDE_INT,
                                  tree);
static bool csky_can_eliminate (const int, const int);
static bool csky_cannot_copy_insn_p (rtx_insn *);
static bool csky_cannot_modify_jumps_p (void);
static bool csky_cannot_force_const_mem (machine_mode, rtx);
static bool csky_lra_p (void);
static void csky_init_libfuncs(void);


/* CSKY specific attributes.  */

static const struct attribute_spec csky_attribute_table[] = {
  /* { name, min_len, max_len, decl_req, type_req, fn_type_req, handler,
     affects_type_identity } */
  {"naked", 0, 0, true, false, false, csky_handle_naked_attribute,
   false},
  {NULL, 0, 0, false, false, false, NULL, false}
};

/* Initialize the GCC target structure.  */

#ifdef OBJECT_FORMAT_ELF
#undef  TARGET_ASM_UNALIGNED_HI_OP
#define TARGET_ASM_UNALIGNED_HI_OP "\t.short\t"
#undef  TARGET_ASM_UNALIGNED_SI_OP
#define TARGET_ASM_UNALIGNED_SI_OP "\t.long\t"
#endif

#undef  TARGET_PRINT_OPERAND
#define TARGET_PRINT_OPERAND                csky_print_operand
#undef  TARGET_PRINT_OPERAND_ADDRESS
#define TARGET_PRINT_OPERAND_ADDRESS        csky_print_operand_address
#undef  TARGET_PRINT_OPERAND_PUNCT_VALID_P
#define TARGET_PRINT_OPERAND_PUNCT_VALID_P csky_print_operand_punct_valid_p

#undef  TARGET_LRA_P
#define TARGET_LRA_P csky_lra_p

#undef  TARGET_ATTRIBUTE_TABLE
#define TARGET_ATTRIBUTE_TABLE                 csky_attribute_table
#undef  TARGET_REGISTER_MOVE_COST
#define TARGET_REGISTER_MOVE_COST csky_register_move_cost
#undef  TARGET_RTX_COSTS
#define TARGET_RTX_COSTS    csky_rtx_costs
#undef  TARGET_ADDRESS_COST
#define TARGET_ADDRESS_COST csky_address_cost

#undef  TARGET_PROMOTE_FUNCTION_MODE
#define TARGET_PROMOTE_FUNCTION_MODE        default_promote_function_mode_always_promote
#undef  TARGET_PROMOTE_PROTOTYPES
#define TARGET_PROMOTE_PROTOTYPES        hook_bool_const_tree_true

#undef  TARGET_RETURN_IN_MEMORY
#define TARGET_RETURN_IN_MEMORY                csky_return_in_memory
#undef  TARGET_MUST_PASS_IN_STACK
#define TARGET_MUST_PASS_IN_STACK        must_pass_in_stack_var_size
#undef  TARGET_PASS_BY_REFERENCE
#define TARGET_PASS_BY_REFERENCE  hook_pass_by_reference_must_pass_in_stack
#undef  TARGET_ARG_PARTIAL_BYTES
#define TARGET_ARG_PARTIAL_BYTES        csky_arg_partial_bytes
#undef  TARGET_FUNCTION_ARG
#define TARGET_FUNCTION_ARG                csky_function_arg
#undef  TARGET_FUNCTION_ARG_ADVANCE
#define TARGET_FUNCTION_ARG_ADVANCE        csky_function_arg_advance
#undef  TARGET_FUNCTION_ARG_BOUNDARY
#define TARGET_FUNCTION_ARG_BOUNDARY        csky_function_arg_boundary
#undef  TARGET_FUNCTION_VALUE
#define TARGET_FUNCTION_VALUE csky_function_value
#undef  TARGET_FUNCTION_VALUE_REGNO_P
#define TARGET_FUNCTION_VALUE_REGNO_P csky_function_value_regno_p

#undef  TARGET_SETUP_INCOMING_VARARGS
#define TARGET_SETUP_INCOMING_VARARGS        csky_setup_incoming_varargs

#undef  TARGET_ASM_TRAMPOLINE_TEMPLATE
#define TARGET_ASM_TRAMPOLINE_TEMPLATE        csky_asm_trampoline_template
#undef  TARGET_TRAMPOLINE_INIT
#define TARGET_TRAMPOLINE_INIT                csky_trampoline_init

#undef  TARGET_OPTION_OVERRIDE
#define TARGET_OPTION_OVERRIDE csky_option_override

#undef  TARGET_LEGITIMATE_CONSTANT_P
#define TARGET_LEGITIMATE_CONSTANT_P csky_legitimate_constant_p
#undef  TARGET_ADDR_SPACE_LEGITIMATE_ADDRESS_P
#define TARGET_ADDR_SPACE_LEGITIMATE_ADDRESS_P csky_legitimate_address_p

#undef  TARGET_WARN_FUNC_RETURN
#define TARGET_WARN_FUNC_RETURN csky_warn_func_return

#undef  TARGET_PREFERRED_RELOAD_CLASS
#define TARGET_PREFERRED_RELOAD_CLASS csky_preferred_reload_class
#undef  TARGET_SECONDARY_RELOAD
#define TARGET_SECONDARY_RELOAD csky_secondary_reload

#undef  TARGET_CONDITIONAL_REGISTER_USAGE
#define TARGET_CONDITIONAL_REGISTER_USAGE csky_conditional_register_usage

#undef  TARGET_ASM_OUTPUT_MI_THUNK
#define TARGET_ASM_OUTPUT_MI_THUNK csky_output_mi_thunk

#undef TARGET_ASM_CAN_OUTPUT_MI_THUNK
#define TARGET_ASM_CAN_OUTPUT_MI_THUNK hook_bool_const_tree_hwi_hwi_const_tree_true

#undef  TARGET_HAVE_TLS
#define TARGET_HAVE_TLS true

#undef  TARGET_CAN_ELIMINATE
#define TARGET_CAN_ELIMINATE csky_can_eliminate

#undef  TARGET_CANNOT_COPY_INSN_P
#define TARGET_CANNOT_COPY_INSN_P csky_cannot_copy_insn_p

/* try to fix Complex support */
#undef  TARGET_SPLIT_COMPLEX_ARG
#define TARGET_SPLIT_COMPLEX_ARG  hook_bool_const_tree_true

#undef  TARGET_CANNOT_MODIFY_JUMPS_P
#define TARGET_CANNOT_MODIFY_JUMPS_P csky_cannot_modify_jumps_p

#undef  TARGET_CANNOT_FORCE_CONST_MEM
#define TARGET_CANNOT_FORCE_CONST_MEM csky_cannot_force_const_mem

#undef  TARGET_MAX_ANCHOR_OFFSET
#define TARGET_MAX_ANCHOR_OFFSET 15

#undef TARGET_INIT_LIBFUNCS
#define TARGET_INIT_LIBFUNCS csky_init_libfuncs

struct gcc_target targetm = TARGET_INITIALIZER;


int
csky_default_branch_cost (bool speed_p, bool predictable_p)
{
  return 1;
}

bool
csky_default_logical_op_non_short_circuit(void)
{
  return BRANCH_COST (optimize_function_for_speed_p (cfun), false) >= 2;
}

/* Adjust the stack and return the number of bytes taken to do it.  */
static int
output_stack_adjust_for_nested (int direction, int size)
{
  int s = size;
  if (cfun->static_chain_decl != NULL)
    {
      for (; s && s > 32; s -= 32)
        {
          output_stack_adjust(direction, 32);
        }
    }
  return s;
}

static void
output_stack_adjust (int direction, int size)
{
  size = output_stack_adjust_for_nested(direction, size);

  if (size)
    {
      rtx insn;
      rtx val = GEN_INT (size);

      if (size > 32)
        {
          rtx nval = gen_rtx_REG (SImode, 1);
          insn = emit_insn (gen_movsi (nval, val));
          RTX_FRAME_RELATED_P (insn) = 1;
          val = nval;
        }

      if (direction > 0)
        insn = gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx, val);
      else
        insn = gen_subsi3 (stack_pointer_rtx, stack_pointer_rtx, val);

      insn = emit_insn (insn);
      RTX_FRAME_RELATED_P (insn) = 1;
    }
}

/* Work out the registers which need to be saved,
   both as a mask and a count.  */

static int
calc_live_r0_r31_regs (int *count)
{
  int reg;
  int live_regs_mask = 0;

  *count = 0;

  if (flag_pic && df_regs_ever_live_p (PIC_OFFSET_TABLE_REGNUM))
    df_set_regs_ever_live (LK_REGNUM, true);

  if (frame_pointer_needed)
    df_set_regs_ever_live (HARD_FRAME_POINTER_REGNUM, true);

  for (reg = 0; reg < 32; reg++)
    {
      if (df_regs_ever_live_p (reg) && !call_really_used_regs[reg])
        {
          (*count)++;
          live_regs_mask |= (1 << reg);
        }
    }

  /* If eh_return, save EH_RETURN_DATA_REGNO.  */
  if (crtl->calls_eh_return)
    {
      unsigned int i;
      for (i = 0; EH_RETURN_DATA_REGNO (i) != INVALID_REGNUM; i++)
        {
          live_regs_mask |= (1 << EH_RETURN_DATA_REGNO (i));
          (*count)++;
        }
    }

  return live_regs_mask;
}

/* Print the operand address in x to the stream.  */

static void
csky_print_operand_address (FILE * stream, machine_mode /*mode */ , rtx x)
{
  switch (GET_CODE (x))
    {
    case REG:
      fprintf (stream, "(%s)", reg_names[REGNO (x)]);
      break;

    case PLUS:
      {
        rtx base = XEXP (x, 0);
        rtx index = XEXP (x, 1);

        if (GET_CODE (base) != REG)
          {
            /* Ensure that BASE is a register (one of them must be).  */
            rtx temp = base;
            base = index;
            index = temp;
          }

        switch (GET_CODE (index))
          {
          case CONST_INT:
            fprintf (stream, "(%s," HOST_WIDE_INT_PRINT_DEC ")",
                     reg_names[REGNO (base)], INTVAL (index));
            break;

          default:
            gcc_unreachable ();
          }
      }

      break;

    default:
      output_addr_const (stream, x);
      break;
    }
}

/* Implement TARGET_PRINT_OPERAND_PUNCT_VALID_P */

static bool
csky_print_operand_punct_valid_p (unsigned char code)
{
  return (code == '.' || code == '#' || code == '*' || code == '^'
          || code == '!');
}

/* Print operand x (an rtx) in assembler syntax to file stream
   according to modifier code.

   'R'  print the next register or memory location along, i.e. the lsw in
        a double word value
   'O'  print a constant without the #
   'M'  print a constant as its negative
   'P'  print log2 of a power of two
   'Q'  print log2 of an inverse of a power of two
   'U'  print register for ldm/stm instruction
   'X'  print byte number for xtrbN instruction.  */

static void
csky_print_operand (FILE * stream, rtx x, int code)
{
  switch (code)
    {
    case 'N':
      if (INTVAL (x) == -1)
        fprintf (asm_out_file, "32");
      else
        fprintf (asm_out_file, "%d", exact_log2 (INTVAL (x) + 1));
      break;
    case 'P':
      fprintf (asm_out_file, "%d", exact_log2 (INTVAL (x) & 0xffffffff));
      break;
    case 'Q':
      fprintf (asm_out_file, "%d", exact_log2 (~INTVAL (x)));
      break;
    case 'O':
      fprintf (asm_out_file, HOST_WIDE_INT_PRINT_DEC, INTVAL (x));
      break;
    case 'M':
      fprintf (asm_out_file, HOST_WIDE_INT_PRINT_DEC, -INTVAL (x));
      break;
    case 'R':
      /* Next location along in memory or register.  */
      switch (GET_CODE (x))
        {
        case REG:
          fputs (reg_names[REGNO (x) + 1], (stream));
          break;
        case MEM:
          csky_print_operand_address
            (stream, GET_MODE (x), XEXP (adjust_address (x, SImode, 4), 0));
          break;
        default:
          gcc_unreachable ();
        }
      break;
    case 'U':
      fprintf (asm_out_file, "%s-%s", reg_names[REGNO (x)],
               reg_names[REGNO (x) + 3]);
      break;
    case 'x':
      fprintf (asm_out_file, HOST_WIDE_INT_PRINT_HEX, INTVAL (x));
      break;
    case 'X':
      fprintf (asm_out_file, HOST_WIDE_INT_PRINT_DEC, 3 - INTVAL (x) / 8);
      break;
    case 'S':
      /* 'S'  print convert fr* regnum in bigendian mode */
      gcc_assert (REG_P (x));
      if (TARGET_LITTLE_ENDIAN || !FPU_REG_P (REGNO (x)))
        fputs (reg_names[REGNO (x)], (stream));
      else
        fputs (reg_names
               [(REGNO (x) & 0x1) ? (REGNO (x) - 1) : (REGNO (x) + 1)],
               (stream));
      break;
    default:
      switch (GET_CODE (x))
        {
        case REG:
          fputs (reg_names[REGNO (x)], (stream));
          break;
        case MEM:
          output_address (GET_MODE (x), XEXP (x, 0));
          break;
        default:
          output_addr_const (stream, x);
          break;
        }
      break;
    }
}

/* What does a constant cost ?  */

static int
csky_const_costs (rtx exp, enum rtx_code code ATTRIBUTE_UNUSED)
{
  HOST_WIDE_INT val = INTVAL (exp);

  /* Easy constants.  */
  if (const_ok_for_csky (val))
    return 0;
  else if (csky_const_ok_for_inline (val))
    return COSTS_N_INSNS (1);
  else
    return COSTS_N_INSNS (3);
}

/* RTX costs */

static bool
csky_rtx_costs (rtx x, machine_mode mode ATTRIBUTE_UNUSED, int outer_code,
                int opno ATTRIBUTE_UNUSED,
                int *total, bool speed ATTRIBUTE_UNUSED)
{
  enum rtx_code code = GET_CODE (x);

  switch (code)
    {
    case CONST_INT:
      *total = csky_const_costs (x, (enum rtx_code) outer_code);
      return true;
    case CONST:
    case LABEL_REF:
    case SYMBOL_REF:
      *total = COSTS_N_INSNS (3);
      return true;
    case AND:
    case IOR:
    case XOR:
      *total = COSTS_N_INSNS (1);
      return true;
    case ROTATE:
    case ASHIFT:
    case ASHIFTRT:
    case LSHIFTRT:
      *total = COSTS_N_INSNS (1);
      return true;
    case PLUS:
    case MINUS:
      *total = COSTS_N_INSNS (1);
      return true;
    case MULT:
    case UDIV:
      *total = COSTS_N_INSNS (4);
      return true;
    case NEG:
    case ABS:
    case NOT:
      *total = COSTS_N_INSNS (1);
      return true;
    case SIGN_EXTEND:
      *total = COSTS_N_INSNS (1);
      return true;
    case ZERO_EXTEND:
      if (!REG_P (XEXP (x, 0)))
        *total = COSTS_N_INSNS (3);
      else
        *total = COSTS_N_INSNS (1);
      return true;
    case IF_THEN_ELSE:
      {
        if (XEXP (x, 1) == pc_rtx || XEXP (x, 2) == pc_rtx)
          {
            *total = COSTS_N_INSNS (3);
            return true;
          }
        int op1cost = rtx_cost (XEXP (x, 1), mode, SET, 1, speed);
        int op2cost = rtx_cost (XEXP (x, 2), mode, SET, 1, speed);
        *total = rtx_cost (XEXP (x, 0), mode, IF_THEN_ELSE, 0, speed);
        *total += op1cost + op2cost;
        return true;
      }
    case EQ:
    case NE:
    case LT:
    case LE:
    case GT:
    case GE:
    case LTU:
    case LEU:
    case GEU:
    case GTU:
    case ORDERED:
    case UNORDERED:
    case UNEQ:
    case UNLE:
    case UNLT:
    case UNGE:
    case UNGT:
    case LTGT:
      *total = COSTS_N_INSNS (1);
      return true;
    case SIGN_EXTRACT:
      *total = COSTS_N_INSNS (2);
      return true;
    case ZERO_EXTRACT:
      *total = COSTS_N_INSNS (1);
      return true;
    case UNSPEC:
    case UNSPEC_VOLATILE:
      *total = COSTS_N_INSNS (2);
      return true;
    case SET:
    case PARALLEL:
      return false;
    case CLOBBER:
      *total = 0;
      return true;
    default:
      return false;
    }
}

/* Implement TARGET_ADDRESS_COST. */

static int
csky_address_cost (rtx x ATTRIBUTE_UNUSED, machine_mode mode,
                   addr_space_t as ATTRIBUTE_UNUSED,
                   bool speed ATTRIBUTE_UNUSED)
{
#define CSKY_NUM_REGS(MODE) \
  (((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD))
  return (2 * CSKY_NUM_REGS (mode));
}

/* Prepare the operands for a comparison of integer mode.
   Return whether the branch/setcc should reverse the operands.  */

bool
csky_gen_compare (enum rtx_code code, rtx op0, rtx op1)
{
  if (TARGET_HARD_FLOAT && TARGET_FPUV1)
    {
      if ((GET_MODE (op0) == SFmode || GET_MODE (op0) == DFmode)
          || (GET_MODE (op1) == SFmode || GET_MODE (op1) == DFmode))
        return csky_gen_compare_float(code, op0, op1);
    }

  rtx cc_reg = gen_rtx_REG (CCmode, CC_REG);
  bool invert;

  if (GET_CODE (op1) == CONST_INT)
    {
      HOST_WIDE_INT val = INTVAL (op1);

      switch (code)
        {
        case GTU:
          /* Unsigned > 0 is the same as != 0; everything else is converted
             below to LEU (reversed cmphs).  */
          if (val == 0)
            code = NE;
          break;

          /* Check whether (LE A imm) can become (LT A imm + 1),
             or (GT A imm) can become (GE A imm + 1).  */
        case GT:
        case LE:
          if (CONST_OK_FOR_J (val + 1))
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
    op1 = force_reg (GET_MODE(op1), op1);

  /* cmpnei: 0-31 (K immediate)
     cmplti: 1-32 (J immediate, 0 using btsti x,31).  */
  invert = false;
  switch (code)
    {
    case EQ:                        /* Use inverted condition, cmpne.  */
      code = NE;
      invert = true;
      /* Drop through.  */

    case NE:                        /* Use normal condition, cmpne.  */
      if (GET_CODE (op1) == CONST_INT && !CONST_OK_FOR_K (INTVAL (op1)))
        op1 = force_reg (SImode, op1);
      break;

    case LE:                        /* Use inverted condition, reversed cmplt.  */
      code = GT;
      invert = true;
      /* Drop through.  */

    case GT:                        /* Use normal condition, reversed cmplt.  */
      if (GET_CODE (op1) == CONST_INT)
        op1 = force_reg (SImode, op1);
      break;

    case GE:                        /* Use inverted condition, cmplt.  */
      code = LT;
      invert = true;
      /* Drop through.  */

    case LT:                        /* Use normal condition, cmplt.  */
      if (GET_CODE (op1) == CONST_INT &&
          /* covered by btsti x,31.  */
          INTVAL (op1) != 0 && !CONST_OK_FOR_J (INTVAL (op1)))
        op1 = force_reg (SImode, op1);
      break;

    case GTU:                        /* Use inverted condition, cmple.  */
      /* We coped with unsigned > 0 above.  */
      gcc_assert (GET_CODE (op1) != CONST_INT || INTVAL (op1) != 0);
      code = LEU;
      invert = true;
      /* Drop through.  */

    case LEU:                        /* Use normal condition, reversed cmphs.  */
      if (GET_CODE (op1) == CONST_INT && INTVAL (op1) != 0)
        op1 = force_reg (SImode, op1);
      break;

    case LTU:                        /* Use inverted condition, cmphs.  */
      code = GEU;
      invert = true;
      /* Drop through.  */

    case GEU:                        /* Use normal condition, cmphs.  */
      if (GET_CODE (op1) == CONST_INT && INTVAL (op1) != 0)
        op1 = force_reg (SImode, op1);
      break;

    default:
      break;
    }

  emit_insn (gen_rtx_SET (cc_reg, gen_rtx_fmt_ee (code, CCmode, op0, op1)));
  return invert;
}

/* Prepare the operands for a comparison of float point mode.
   Return whether the branch/setcc should reverse the operands.  */

bool
csky_gen_compare_float (enum rtx_code code, rtx op0, rtx op1)
{
  rtx cc_reg = gen_rtx_REG (CCmode, CC_REGNUM);
  bool invert;

  if (!csky_const_float_0 (op1, GET_MODE (op1)))
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
    case GT:
      if (csky_const_float_0 (op1, GET_MODE (op1)))
        {
          op1 = force_reg (GET_MODE (op1), op1);
        }
      break;
    case GE:
      break;
    case LT:
      if ((csky_const_float_0 (op1, GET_MODE (op1))))
        {
          code = GE;
          invert = true;
        }
      break;

    default:
      break;
    }
  emit_insn (gen_rtx_PARALLEL (VOIDmode,
                               gen_rtvec (2,
                                          gen_rtx_SET (cc_reg,
                                                       gen_rtx_fmt_ee (code,
                                                                       CCmode,
                                                                       op0,
                                                                       op1)),
                                          gen_rtx_CLOBBER (VOIDmode,
                                                           gen_rtx_SCRATCH
                                                           (SImode)))));

  return invert;

}


/* Implement TARGET_REGISTER_MOVE_COST.

   Compute extra cost of moving data between one register class
   and another.  All register moves are cheap. */

static int
csky_register_move_cost (machine_mode mode ATTRIBUTE_UNUSED,
                         reg_class_t from, reg_class_t to)
{
#define GR_REG_CLASS_P(CLASS) \
  ((CLASS) == GENERAL_REGS || (CLASS) == RWCPCR_REGS || (CLASS) == LRW_REGS)

#define HILO_REG_CLASS_P(CLASS) \
  ((CLASS) == HI_REGS || (CLASS) == LO_REGS || (CLASS) == HILO_REGS)

#define FPU_REG_CLASS_P(CLASS) \
  ((CLASS) == FPU_REGS)
  return ((HILO_REG_CLASS_P (from) && GR_REG_CLASS_P (to)) ? 16
          : ((GR_REG_CLASS_P (from) && HILO_REG_CLASS_P (to)) ? 16
             : ((HILO_REG_CLASS_P (from) && HILO_REG_CLASS_P (to)) ? 16
                : ((FPU_REG_CLASS_P (from) && FPU_REG_CLASS_P (to)) ? 16
                   : ((HILO_REG_CLASS_P (from) && FPU_REG_CLASS_P (to)) ? 32
                      : ((FPU_REG_CLASS_P (from)
                          && HILO_REG_CLASS_P (to)) ? 32
                         : ((FPU_REG_CLASS_P (from)
                             && GR_REG_CLASS_P (to)) ? 16
                            : ((GR_REG_CLASS_P (from)
                                && FPU_REG_CLASS_P (to)) ? 16 : 2))))))));
}

int
csky_symbolic_address_p (rtx x)
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

/* Functions to output assembly code for a function call.  */

char *
csky_output_call (rtx operands[], int index)
{
  static char buffer[20];
  rtx addr = operands[index];

  if (REG_P (addr))
    {
      sprintf (buffer, "jsr\t%%%d", index);
    }
  else
    {
      sprintf (buffer, "jbsr\t%%%d", index);
    }

  return buffer;
}

/* Can we load a constant with a single instruction ?  */

int
const_ok_for_csky (HOST_WIDE_INT value)
{
  if (value >= 0 && value <= 127)
    return 1;

  /* Try exact power of two.  */
  if (CONST_OK_FOR_M (value))
    return 1;

  /* Try exact power of two - 1.  */
  if (CONST_OK_FOR_N (value) && value != -1)
    return 1;

  return 0;
}

/* Can we load a constant inline with up to 2 instructions ?  */

int
csky_const_ok_for_inline (HOST_WIDE_INT value)
{
  HOST_WIDE_INT x, y;

  return try_constant_tricks (value, &x, &y) > 0;
}

/* Try tricks to load a constant inline and return the trick number if
   success (0 is non-inlinable).

   0: not inlinable
   1: single instruction (do the usual thing)
   2: single insn followed by a 'not'
   3: single insn followed by a subi
   4: single insn followed by an addi
   5: single insn followed by rsubi
   6: single insn followed by bseti
   7: single insn followed by bclri
   8: single insn followed by rotli
   9: single insn followed by lsli
   10: single insn followed by ixh
   11: single insn followed by ixw.  */

static int
try_constant_tricks (HOST_WIDE_INT value, HOST_WIDE_INT * x,
                     HOST_WIDE_INT * y)
{
  HOST_WIDE_INT i;
  unsigned HOST_WIDE_INT bit, shf, rot;

  if (const_ok_for_csky (value))
    return 1;                        /* Do the usual thing.  */

  if (!TARGET_HARDLIT)
    return 0;

  if (const_ok_for_csky (~value))
    {
      *x = ~value;
      return 2;
    }

  for (i = 1; i <= 32; i++)
    {
      if (const_ok_for_csky (value - i))
        {
          *x = value - i;
          *y = i;

          return 3;
        }

      if (const_ok_for_csky (value + i))
        {
          *x = value + i;
          *y = i;

          return 4;
        }
    }

  bit = 0x80000000ULL;

  for (i = 0; i <= 31; i++)
    {
      if (const_ok_for_csky (i - value))
        {
          *x = i - value;
          *y = i;

          return 5;
        }

      if (const_ok_for_csky (value & ~bit))
        {
          *y = bit;
          *x = value & ~bit;
          return 6;
        }

      if (const_ok_for_csky (value | bit))
        {
          *y = ~bit;
          *x = value | bit;

          return 7;
        }

      bit >>= 1;
    }

  shf = value;
  rot = value;

  for (i = 1; i < 31; i++)
    {
      int c;

      /* CSKY has rotate left.  */
      c = rot << 31;
      rot >>= 1;
      rot &= 0x7FFFFFFF;
      rot |= c;                        /* Simulate rotate.  */

      if (const_ok_for_csky (rot))
        {
          *y = i;
          *x = rot;

          return 8;
        }

      if (shf & 1)
        shf = 0;                /* Can't use logical shift, low order bit is one.  */

      shf >>= 1;

      if (shf != 0 && const_ok_for_csky (shf))
        {
          *y = i;
          *x = shf;

          return 9;
        }
    }

  if ((value % 3) == 0 && const_ok_for_csky (value / 3))
    {
      *x = value / 3;

      return 10;
    }

  if ((value % 5) == 0 && const_ok_for_csky (value / 5))
    {
      *x = value / 5;

      return 11;
    }

  return 0;
}

/* Check whether reg is dead at first.  This is done by searching ahead
   for either the next use (i.e., reg is live), a death note, or a set of
   reg.  Don't just use dead_or_set_p() since reload does not always mark
   deaths (especially if PRESERVE_DEATH_NOTES_REGNO_P is not defined). We
   can ignore subregs by extracting the actual register.  BRC  */

int
csky_op_is_dead (rtx_insn * first, rtx reg)
{
  rtx_insn *insn;

  /* For csky, subregs can't live independently of their parent regs.  */
  if (GET_CODE (reg) == SUBREG)
    reg = SUBREG_REG (reg);

  /* Dies immediately.  */
  if (dead_or_set_p (first, reg))
    return 1;

  /* Look for conclusive evidence of live/death, otherwise we have
     to assume that it is live.  */
  for (insn = NEXT_INSN (first); insn; insn = NEXT_INSN (insn))
    {
      if (JUMP_P (insn))
        return 0;                /* We lose track, assume it is alive.  */

      else if (CALL_P (insn))
        {
          /* Call's might use it for target or register parms.  */
          if (reg_referenced_p (reg, PATTERN (insn))
              || find_reg_fusage (insn, USE, reg))
            return 0;
          else if (dead_or_set_p (insn, reg))
            return 1;
        }
      else if (NONJUMP_INSN_P (insn))
        {
          if (reg_referenced_p (reg, PATTERN (insn)))
            return 0;
          else if (dead_or_set_p (insn, reg))
            return 1;
        }
    }

  /* No conclusive evidence either way, we cannot take the chance
     that control flow hid the use from us -- "I'm not dead yet".  */
  return 0;
}

/* Count the number of ones in mask.  */

int
csky_num_ones (HOST_WIDE_INT mask)
{
  /* A trick to count set bits recently posted on comp.compilers.  */
  mask = (mask >> 1 & 0x55555555) + (mask & 0x55555555);
  mask = ((mask >> 2) & 0x33333333) + (mask & 0x33333333);
  mask = ((mask >> 4) + mask) & 0x0f0f0f0f;
  mask = ((mask >> 8) + mask);

  return (mask + (mask >> 16)) & 0xff;
}

/* Count the number of zeros in mask.  */

int
csky_num_zeros (HOST_WIDE_INT mask)
{
  return 32 - csky_num_ones (mask);
}

/* Output a series of bseti's corresponding to mask.  */

const char *
csky_output_bseti (rtx dst, int mask)
{
  rtx out_operands[2];
  int bit;

  out_operands[0] = dst;

  for (bit = 0; bit < 32; bit++)
    {
      if ((mask & 0x1) == 0x1)
        {
          out_operands[1] = GEN_INT (bit);

          output_asm_insn ("bseti\t%0, %1", out_operands);
        }
      mask >>= 1;
    }

  return "";
}

/* Output a series of bclri's corresponding to mask.  */

const char *
csky_output_bclri (rtx dst, int mask)
{
  rtx out_operands[2];
  int bit;

  out_operands[0] = dst;

  for (bit = 0; bit < 32; bit++)
    {
      if ((mask & 0x1) == 0x0)
        {
          out_operands[1] = GEN_INT (bit);

          output_asm_insn ("bclri\t%0, %1", out_operands);
        }

      mask >>= 1;
    }

  return "";
}

/* Output an inline constant.  */

static const char *
output_inline_const (machine_mode mode, rtx operands[])
{
  HOST_WIDE_INT x = 0, y = 0;
  int trick_no;
  rtx out_operands[3];
  char buf[256];
  char load_op[256];
  const char *dst_fmt;
  HOST_WIDE_INT value;

  value = INTVAL (operands[1]);

  trick_no = try_constant_tricks (value, &x, &y);
  /* lrw's are handled separately: Large inlinable constants never get
     turned into lrw's.  Our caller uses try_constant_tricks to back
     off to an lrw rather than calling this routine.  */
  gcc_assert (trick_no != 0);

  if (trick_no == 1)
    x = value;

  /* operands: 0 = dst, 1 = load immed., 2 = immed. adjustment.  */
  out_operands[0] = operands[0];
  out_operands[1] = GEN_INT (x);

  if (trick_no > 2)
    out_operands[2] = GEN_INT (y);

  /* Select dst format based on mode.  */
  if (mode == DImode && (!TARGET_LITTLE_ENDIAN))
    dst_fmt = "%R0";
  else
    dst_fmt = "%0";

  if (x >= 0 && x <= 127)
    sprintf (load_op, "movi\t%s,%%1", dst_fmt);

  /* Try exact power of two.  */
  else if (CONST_OK_FOR_M (x))
    sprintf (load_op, "bgeni\t%s,%%P1", dst_fmt);

  /* Try exact power of two - 1.  */
  else if (CONST_OK_FOR_N (x))
    sprintf (load_op, "bmaski\t%s,%%N1", dst_fmt);

  else
    {
      sprintf (load_op, "BADMOVI-inline_const %s, %%1", dst_fmt);
      gcc_unreachable ();
    }

  switch (trick_no)
    {
    case 1:
      strcpy (buf, load_op);
      break;
    case 2:                        /* not */
      sprintf (buf, "%s\n\tnot\t%s\t// %ld 0x%lx", load_op, dst_fmt, value,
               value);
      break;
    case 3:                        /* add */
      sprintf (buf, "%s\n\taddi\t%s,%%2\t// %ld 0x%lx", load_op, dst_fmt,
               value, value);
      break;
    case 4:                        /* sub */
      sprintf (buf, "%s\n\tsubi\t%s,%%2\t// %ld 0x%lx", load_op, dst_fmt,
               value, value);
      break;
    case 5:                        /* rsub */
      /* Never happens unless -mrsubi, see try_constant_tricks().  */
      sprintf (buf, "%s\n\trsubi\t%s,%%2\t// %ld 0x%lx", load_op, dst_fmt,
               value, value);
      break;
    case 6:                        /* bseti */
      sprintf (buf, "%s\n\tbseti\t%s,%%P2\t// %ld 0x%lx", load_op, dst_fmt,
               value, value);
      break;
    case 7:                        /* bclr */
      sprintf (buf, "%s\n\tbclri\t%s,%%Q2\t// %ld 0x%lx", load_op, dst_fmt,
               value, value);
      break;
    case 8:                        /* rotl */
      sprintf (buf, "%s\n\trotli\t%s,%%2\t// %ld 0x%lx", load_op, dst_fmt,
               value, value);
      break;
    case 9:                        /* lsl */
      sprintf (buf, "%s\n\tlsli\t%s,%%2\t// %ld 0x%lx", load_op, dst_fmt,
               value, value);
      break;
    case 10:                        /* ixh */
      sprintf (buf, "%s\n\tixh\t%s,%s\t// %ld 0x%lx", load_op, dst_fmt,
               dst_fmt, value, value);
      break;
    case 11:                        /* ixw */
      sprintf (buf, "%s\n\tixw\t%s,%s\t// %ld 0x%lx", load_op, dst_fmt,
               dst_fmt, value, value);
      break;
    default:
      return "";
    }

  output_asm_insn (buf, out_operands);

  return "";
}

/* Output a move of a word or less value.  */

const char *
csky_output_move (rtx insn ATTRIBUTE_UNUSED, rtx operands[],
                  machine_mode mode ATTRIBUTE_UNUSED)
{
  rtx dst = operands[0];
  rtx src = operands[1];

  if (REG_P (dst))
    {
      if (REG_P (src))
        {
          int dstreg = REGNO (dst);
          int srcreg = REGNO (src);

          /* hilo registers exchange their places,
             and their order of Dimode as same as other
             general registers in LITTLE_ENDIAN mode. */
          if (TARGET_LITTLE_ENDIAN)
            {
              if (dstreg == HI_REG)
                return "mtlo\t%1";
              else if (dstreg == LO_REG)
                return "mthi\t%1";
              else if (srcreg == HI_REG)
                return "mflo\t%0";
              else if (srcreg == LO_REG)
                return "mfhi\t%0";
            }
          else
            {
              if (dstreg == HI_REG)
                return "mthi\t%1";
              else if (dstreg == LO_REG)
                return "mtlo\t%1";
              else if (srcreg == HI_REG)
                return "mfhi\t%0";
              else if (srcreg == LO_REG)
                return "mflo\t%0";
            }

          if (FPU_REG_P (dstreg))
            return "fmts\t%1, %S0";
          if (FPU_REG_P (srcreg))
            return "fmfs\t%0, %S1";

          if (srcreg == CC_REG)        /* r-c */
            return "mvc\t%0";
          else
            return "mov\t%0, %1";        /* r-r */
        }
      else if (GET_CODE (src) == MEM)
        {
          if (GET_CODE (XEXP (src, 0)) == LABEL_REF)
            return "lrw\t%0, [%1]";        /* a-R */
          else
            switch (GET_MODE (src))        /* r-m */
              {
              case SImode:
                return "ldw\t%0, %1";
              case HImode:
                return "ld.h\t%0, %1";
              case QImode:
                return "ld.b\t%0, %1";
              case SFmode:
                return "ldw\t%0, %1";
              default:
                gcc_unreachable ();
              }
        }
      else if (GET_CODE (src) == CONST_INT)
        {
          HOST_WIDE_INT x, y;

          if (CONST_OK_FOR_I (INTVAL (src)))        /* r-I */
            return "movi\t%0, %1";
          else if (CONST_OK_FOR_M (INTVAL (src)))        /* r-M */
            return "bgeni\t%0, %P1\t// %1 %x1";
          else if (CONST_OK_FOR_N (INTVAL (src)))        /* r-N */
            return "bmaski\t%0, %N1\t// %1 %x1";
          else if (try_constant_tricks (INTVAL (src), &x, &y))        /* R-P */
            return output_inline_const (SImode, operands);        /* 1-2 insns */
          else
            return "lrw\t%0, %O1";        /* Get it from literal pool.  */
        }
      else if (GET_CODE (src) == CONST_DOUBLE && GET_MODE (src) == SFmode)
        {
          const REAL_VALUE_TYPE *d;
          long l;
          HOST_WIDE_INT x, y;

          d = CONST_DOUBLE_REAL_VALUE (src);
          REAL_VALUE_TO_TARGET_SINGLE (*d, l);
          operands[1] = GEN_INT (l);
          src = operands[1];

          if (CONST_OK_FOR_I (INTVAL (src)))        /* r-I */
            return "movi\t%0, %1";
          else if (CONST_OK_FOR_M (INTVAL (src)))        /* r-M */
            return "bgeni\t%0, %P1\t// %1 %x1";
          else if (CONST_OK_FOR_N (INTVAL (src)))        /* r-N */
            return "bmaski\t%0, %N1\t// %1 %x1";
          else if (try_constant_tricks (INTVAL (src), &x, &y))        /* R-P */
            return output_inline_const (SImode, operands);        /* 1-2 insns */
          else
            return "lrw\t%0, %O1";        /* Get it from literal pool.  */
        }
      else
        return "lrw\t%0, %1";        /* Into the literal pool.  */
    }
  else if (GET_CODE (dst) == MEM)        /* m-r */
    switch (GET_MODE (dst))
      {
      case SImode:
        return "stw\t%1, %0";
      case HImode:
        return "st.h\t%1, %0";
      case QImode:
        return "st.b\t%1, %0";
      case SFmode:
        return "stw\t%1, %0";
      default:
        gcc_unreachable ();
      }

  gcc_unreachable ();
}

/* Return a sequence of instructions to perform DI or DF move.
   Since the CSKY cannot move a DI or DF in one instruction, we have
   to take care when we see overlapping source and dest registers.  */

const char *
csky_output_movedouble (rtx operands[], machine_mode mode ATTRIBUTE_UNUSED)
{
  rtx dst = operands[0];
  rtx src = operands[1];

  if (GET_CODE (dst) == REG)
    {
      if (GET_CODE (src) == REG)
        {
          int dstreg = REGNO (dst);
          int srcreg = REGNO (src);

          if (HILO_REG_P (srcreg))
            {
              if (TARGET_LITTLE_ENDIAN)
                return "mfhi\t%R0\n\tmflo\t%0";
              else
                return "mfhi\t%0\n\tmflo\t%R0";
            }
          else if (HILO_REG_P (dstreg))
            {
              if (TARGET_LITTLE_ENDIAN)
                return "mthi\t%R1\n\tmtlo\t%1";
              else
                return "mthi\t%1\n\tmtlo\t%R1";
            }
          else if (FPU_REG_P (srcreg))
            {
              return "fmfd\t%0, %1";
            }
          else if (FPU_REG_P (dstreg))
            {
              return "fmtd\t%1, %0";
            }

          /* Ensure the second source not overwritten.  */
          if (srcreg + 1 == dstreg)
            return "mov %R0, %R1\n\tmov %0, %1";
          else
            return "mov %0, %1\n\tmov %R0, %R1";
        }
      else if (GET_CODE (src) == MEM)
        {
          rtx memexp = XEXP (src, 0);
          int dstreg = REGNO (dst);
          int basereg = -1;

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

          /* ??? length attribute is wrong here.  */
          if (dstreg == basereg)
            {
              /* Just load them in reverse order.  */
              return "ldw\t%R0, %R1\n\tldw\t%0, %1";

              /* XXX: alternative: move basereg to basereg+1
                 and then fall through.  */
            }
          else
            return "ldw\t%0, %1\n\tldw\t%R0, %R1";
        }
      else if (GET_CODE (src) == CONST_INT || GET_CODE (src) == CONST_DOUBLE)
        {
          split_double (src, &operands[2], &operands[3]);

          if (CONST_OK_FOR_I (INTVAL (operands[2])))
            output_asm_insn ("movi\t%0, %2", operands);

          else if (CONST_OK_FOR_N (INTVAL (operands[2])))
            output_asm_insn ("bmaski\t%0, %N2", operands);

          else if (TARGET_CSKYV1 && CONST_OK_FOR_M (INTVAL (operands[2])))
            output_asm_insn ("bgeni\t%0, %P2", operands);

          else
            output_asm_insn ("lrw\t%0, %2", operands);


          if (CONST_OK_FOR_I (INTVAL (operands[3])))
            output_asm_insn ("movi\t%R0, %3", operands);

          else if (CONST_OK_FOR_N (INTVAL (operands[3])))
            output_asm_insn ("bmaski\t%R0, %N3", operands);

          else if (TARGET_CSKYV1 && CONST_OK_FOR_M (INTVAL (operands[3])))
            output_asm_insn ("bgeni\t%R0, %P3", operands);

          else
            output_asm_insn ("lrw\t%R0, %3", operands);

          return "";

        }
      else
        gcc_unreachable ();
    }
  else if (GET_CODE (dst) == MEM && GET_CODE (src) == REG)
    return "stw\t%1, %0\n\tstw\t%R1, %R0";
  else
    gcc_unreachable ();
}

/* Expand insert bit field.  BRC  */

int
csky_expand_insv (rtx operands[])
{
  int width = INTVAL (operands[1]);
  int posn = INTVAL (operands[2]);
  int mask;

  /* To get width 1 insv, the test in store_bit_field() (expmed.c, line 191)
     for width==1 must be removed.  Look around line 368.  This is something
     we really want the md part to do.  */
  if (width == 1 && GET_CODE (operands[3]) == CONST_INT)
    {
      /* Do directly with bseti or bclri.  */
      /* RBE: 2/97 consider only low bit of constant.  */
      if ((INTVAL (operands[3]) & 1) == 0)
        {
          mask = ~(1 << posn);
          emit_insn (gen_rtx_SET (operands[0],
                                  gen_rtx_AND (SImode, operands[0],
                                               GEN_INT (mask))));
        }
      else
        {
          mask = 1 << posn;
          emit_insn (gen_rtx_SET (operands[0],
                                  gen_rtx_IOR (SImode, operands[0],
                                               GEN_INT (mask))));
        }

      return 1;
    }

  return 0;
}


/* Code to generate prologue and epilogue sequences.  */
static int number_of_regs_before_varargs;

/* Set by TARGET_SETUP_INCOMING_VARARGS to indicate to prolog that this is
   for a varargs function.  */
static int current_function_anonymous_args;

#define        STACK_BYTES (STACK_BOUNDARY/BITS_PER_UNIT)
#define        STORE_REACH (64)        /* Maximum displace of word store + 4.  */
#define        ADDI_REACH (32)        /* Maximum addi operand.  */

/* Compute the frame layout */

static void
layout_csky_frame (struct csky_frame *infp)
{
  int n;
  unsigned int i;
  int nbytes;
  int regarg;
  int localregarg;
  int outbounds;
  unsigned int growths;
  int step;

  /* Might have to spill bytes to re-assemble a big argument that
     was passed partially in registers and partially on the stack.  */
  nbytes = crtl->args.pretend_args_size;

  /* Determine how much space for spilled anonymous args (e.g., stdarg).  */
  if (current_function_anonymous_args)
    nbytes += (NPARM_REGS - number_of_regs_before_varargs) * UNITS_PER_WORD;

  infp->arg_size = nbytes;

  /* How much space to save non-volatile registers we stomp.  */
  infp->reg_mask = calc_live_r0_r31_regs (&n);
  infp->reg_size = n * 4;

  /* And the rest of it... locals and space for overflowed outbounds.  */
  infp->local_size = get_frame_size ();
  infp->outbound_size = crtl->outgoing_args_size;

  /* Make sure we have a whole number of words for the locals.  */
  if (infp->local_size % STACK_BYTES)
    infp->local_size =
      (infp->local_size + STACK_BYTES - 1) & ~(STACK_BYTES - 1);

  /* Only thing we know we have to pad is the outbound space, since
     we've aligned our locals assuming that base of locals is aligned.  */
  infp->pad_local = 0;
  infp->pad_reg = 0;
  infp->pad_outbound = 0;
  if (infp->outbound_size % STACK_BYTES)
    infp->pad_outbound = STACK_BYTES - (infp->outbound_size % STACK_BYTES);

  /* Now we see how we want to stage the prologue so that it does
     the most appropriate stack growth and register saves to either:
     (1) run fast,
     (2) reduce instruction space, or
     (3) reduce stack space.  */
  for (i = 0; i < ARRAY_SIZE (infp->growth); i++)
    infp->growth[i] = 0;

  regarg = infp->reg_size + infp->arg_size;
  localregarg = infp->local_size + regarg;
  outbounds = infp->outbound_size + infp->pad_outbound;
  growths = 0;

  /* XXX: Consider one where we consider localregarg + outbound too! */

  /* Frame of <= 32 bytes and using stm would get <= 2 registers.
     use stw's with offsets and buy the frame in one shot.  */
  if (localregarg <= ADDI_REACH
      && (infp->reg_size <= 8 || (infp->reg_mask & 0xc000) != 0xc000)
      && (!TARGET_PRELOAD_PROTECT
          || (TARGET_PRELOAD_PROTECT && (infp->reg_size > 16))))
    {
      /* Make sure we'll be aligned.  */
      if (localregarg % STACK_BYTES)
        infp->pad_reg = STACK_BYTES - (localregarg % STACK_BYTES);

      step = localregarg + infp->pad_reg;
      infp->reg_offset = infp->local_size;

      if (outbounds + step <= ADDI_REACH && !frame_pointer_needed)
        {
          step += outbounds;
          infp->reg_offset += outbounds;
          outbounds = 0;
        }

      infp->arg_offset = step - 4;
      infp->growth[growths++] = step;
      infp->reg_growth = growths;
      infp->local_growth = growths;

      /* If we haven't already folded it in.  */
      if (outbounds)
        infp->growth[growths++] = outbounds;

      goto finish;
    }

  /* Frame can't be done with a single subi, but can be done with 2
     insns.  If the 'stm' is getting <= 2 registers, we use stw's and
     shift some of the stack purchase into the first subi, so both are
     single instructions.  */
  if (localregarg <= STORE_REACH
      && (infp->local_size > ADDI_REACH)
      && (infp->reg_size <= 8 || (infp->reg_mask & 0xc000) != 0xc000)
      && (!TARGET_PRELOAD_PROTECT
          || (TARGET_PRELOAD_PROTECT && (infp->reg_size > 16))))
    {
      int all;

      /* Make sure we'll be aligned; use either pad_reg or pad_local.  */
      if (localregarg % STACK_BYTES)
        infp->pad_reg = STACK_BYTES - (localregarg % STACK_BYTES);

      all = localregarg + infp->pad_reg + infp->pad_local;
      step = ADDI_REACH;        /* As much up front as we can.  */
      if (step > all)
        step = all;

      /* XXX: Consider whether step will still be aligned; we believe so.  */
      infp->arg_offset = step - 4;
      infp->growth[growths++] = step;
      infp->reg_growth = growths;
      infp->reg_offset =
        step - infp->pad_reg - infp->reg_size - infp->arg_size;
      all -= step;

      /* Can we fold in any space required for outbounds?  */
      if (outbounds + all <= ADDI_REACH && !frame_pointer_needed)
        {
          all += outbounds;
          outbounds = 0;
        }

      /* Get the rest of the locals in place.  */
      step = all;
      infp->growth[growths++] = step;
      infp->local_growth = growths;
      all -= step;

      /* Finish off if we need to do so.  */
      if (outbounds)
        infp->growth[growths++] = outbounds;

      goto finish;
    }

  /* Registers + args is nicely aligned, so we'll buy that in one shot.
     Then we buy the rest of the frame in 1 or 2 steps depending on
     whether we need a frame pointer.  */
  if ((regarg % STACK_BYTES) == 0)
    {
      infp->growth[growths++] = regarg;
      infp->reg_growth = growths;
      infp->arg_offset = regarg - 4;
      infp->reg_offset = 0;

      if (infp->local_size % STACK_BYTES)
        infp->pad_local = STACK_BYTES - (infp->local_size % STACK_BYTES);

      step = infp->local_size + infp->pad_local;

      if (!frame_pointer_needed)
        {
          step += outbounds;
          outbounds = 0;
        }

      infp->growth[growths++] = step;
      infp->local_growth = growths;

      /* If there's any left to be done.  */
      if (outbounds)
        infp->growth[growths++] = outbounds;

      goto finish;
    }

  /* XXX: optimizations that we'll want to play with....
     -- regarg is not aligned, but it's a small number of registers;
     use some of localsize so that regarg is aligned and then
     save the registers.  */

  /* Simple encoding; plods down the stack buying the pieces as it goes.
     -- does not optimize space consumption.
     -- does not attempt to optimize instruction counts.
     -- but it is safe for all alignments.  */
  if (regarg % STACK_BYTES != 0)
    infp->pad_reg = STACK_BYTES - (regarg % STACK_BYTES);

  infp->growth[growths++] = infp->arg_size + infp->reg_size + infp->pad_reg;
  infp->reg_growth = growths;
  infp->arg_offset = infp->growth[0] - 4;
  infp->reg_offset = 0;

  if (frame_pointer_needed)
    {
      if (infp->local_size % STACK_BYTES != 0)
        infp->pad_local = STACK_BYTES - (infp->local_size % STACK_BYTES);

      infp->growth[growths++] = infp->local_size + infp->pad_local;
      infp->local_growth = growths;

      infp->growth[growths++] = outbounds;
    }
  else
    {
      if ((infp->local_size + outbounds) % STACK_BYTES != 0)
        infp->pad_local =
          STACK_BYTES - ((infp->local_size + outbounds) % STACK_BYTES);

      infp->growth[growths++] =
        infp->local_size + infp->pad_local + outbounds;
      infp->local_growth = growths;
    }

  /* Anything else that we've forgotten?, plus a few consistency checks.  */
finish:
  gcc_assert (infp->reg_offset >= 0);
  gcc_assert (growths <= MAX_STACK_GROWS);

  for (i = 0; i < growths; i++)
    gcc_assert (!(infp->growth[i] % STACK_BYTES));
}

/* Define the offset between two registers, one to be eliminated, and
   the other its replacement, at the start of a routine.  */

int
csky_initial_elimination_offset (int from, int to)
{
  int above_frame;
  int below_frame;
  struct csky_frame fi;

  layout_csky_frame (&fi);

  /* fp to ap */
  above_frame = fi.local_size + fi.pad_local + fi.reg_size + fi.pad_reg;
  /* sp to fp */
  below_frame = fi.outbound_size + fi.pad_outbound;

  if (from == ARG_POINTER_REGNUM && to == FRAME_POINTER_REGNUM)
    return above_frame;

  if (from == ARG_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    return above_frame + below_frame;

  if (from == ARG_POINTER_REGNUM && to == HARD_FRAME_POINTER_REGNUM)
    return above_frame;

  if (from == FRAME_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    return below_frame;

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
   ARG_POINTER_REGNUM.  */

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

/* Keep track of some information about varargs for the prolog.  */

static void
csky_setup_incoming_varargs (cumulative_args_t args_so_far_v,
                             machine_mode mode, tree type,
                             int *ptr_pretend_size ATTRIBUTE_UNUSED,
                             int second_time ATTRIBUTE_UNUSED)
{
  CUMULATIVE_ARGS *args_so_far = get_cumulative_args (args_so_far_v);

  current_function_anonymous_args = 1;

  /* We need to know how many argument registers are used before
     the varargs start, so that we can push the remaining argument
     registers during the prologue.  */
  number_of_regs_before_varargs =
    *args_so_far + csky_num_arg_regs (mode, type);

  /* There is a bug somewhere in the arg handling code.
     Until I can find it this workaround always pushes the
     last named argument onto the stack.  */
  number_of_regs_before_varargs = *args_so_far;

  /* resolve the varargs problem because double-word mode need 8 byte align. */
  if (*args_so_far % 2 && csky_num_arg_regs (mode, type) == 2)
    number_of_regs_before_varargs++;

  /* The last named argument may be split between argument registers
     and the stack.  Allow for this here.  */
  if (number_of_regs_before_varargs > NPARM_REGS)
    number_of_regs_before_varargs = NPARM_REGS;
}

/* Emit RTL sequence for function prologue. */

void
csky_expand_prolog (void)
{
  struct csky_frame fi;
  int space_allocated = 0;
  int growth = 0;
  int offset_lr = 0;
  rtx insn;

  /* Find out what we're doing.  */
  layout_csky_frame (&fi);

  space_allocated = fi.arg_size + fi.reg_size + fi.local_size +
    fi.outbound_size + fi.pad_outbound + fi.pad_local + fi.pad_reg;

  if (dump_file)
    {
      fprintf (dump_file, "Stack Layout:\n");
      fprintf (dump_file, "  arg_size = %d\n", fi.arg_size);
      fprintf (dump_file, "  reg_size= %d\n", fi.reg_size);
      fprintf (dump_file, "  pad_reg = %d\n", fi.pad_reg);
      fprintf (dump_file, "  local_size = %d\n", fi.local_size);
      fprintf (dump_file, "  pad_local = %d\n", fi.pad_local);
      fprintf (dump_file, "  outbound_size = %d\n", fi.outbound_size);
      fprintf (dump_file, "  pad_outbound = %d\n", fi.pad_outbound);
      fprintf (dump_file, "  arg_offset = %d\n", fi.arg_offset);
      fprintf (dump_file, "  reg_offset = %d\n", fi.reg_offset);
      for (unsigned i = 0; i < ARRAY_SIZE (fi.growth); i++)
        fprintf (dump_file, "  growth[%d] = %d\n", i, fi.growth[i]);
    }

  if (csky_naked_function_p ())
    {
      if (flag_stack_usage_info)
        current_function_static_stack_size = 0;
      return;
    }

  /* Handle stdarg+regsaves in one shot: can't be more than 64 bytes.  */
  output_stack_adjust (-1, fi.growth[growth++]);        /* Grows it.  */

  /* If we have a parameter passed partially in regs and partially in memory,
     the registers will have been stored to memory already in function.c.  So
     we only need to do something here for varargs functions.  */
  if (fi.arg_size != 0 && crtl->args.pretend_args_size == 0)
    {
      int offset;
      int rn = FIRST_PARM_REG + NPARM_REGS - 1;
      int remaining = fi.arg_size;

      for (offset = fi.arg_offset; remaining >= 4;
           offset -= 4, rn--, remaining -= 4)
        {
          insn = emit_insn (gen_movsi
                            (gen_rtx_MEM (SImode,
                                          plus_constant (Pmode,
                                                         stack_pointer_rtx,
                                                         offset)),
                             gen_rtx_REG (SImode, rn)));
          RTX_FRAME_RELATED_P (insn) = 1;
        }
    }

  /* Do we need another stack adjustment before we do the register saves?  */
  if (growth < fi.reg_growth)
    output_stack_adjust (-1, fi.growth[growth++]);        /* Grows it.  */

  if (fi.reg_size != 0)
    {
      int i;
      int offs = fi.reg_offset;

      for (i = 15; i >= 0; i--)
        {
          if (offs == 0 && i == 15 && ((fi.reg_mask & 0xc000) == 0xc000))
            {
              int first_reg = 15;

              while (fi.reg_mask & (1 << first_reg))
                first_reg--;
              first_reg++;

              if (TARGET_MULTIPLE_STLD)
                {
                  rtx dwarf, reg, tmp;
                  int dwarf_par_index = 0;
                  int num_regs = 16 - first_reg;

                  insn = emit_insn (gen_store_multiple
                                    (gen_rtx_MEM
                                     (SImode, stack_pointer_rtx),
                                     gen_rtx_REG (SImode, first_reg),
                                     GEN_INT (num_regs)));

                  dwarf = gen_rtx_SEQUENCE (VOIDmode, rtvec_alloc (num_regs));
                  for (;dwarf_par_index < num_regs;dwarf_par_index++)
                    {
                      reg = gen_rtx_REG (SImode, first_reg + dwarf_par_index);
                      tmp = gen_rtx_SET
                              (gen_frame_mem
                                (SImode,
                                 plus_constant (Pmode, stack_pointer_rtx,
                                                4 * dwarf_par_index)),
                                 reg);
                      RTX_FRAME_RELATED_P (tmp) = 1;
                      XVECEXP (dwarf, 0, dwarf_par_index) = tmp;
                    }
                  add_reg_note (insn, REG_FRAME_RELATED_EXPR, dwarf);
                  RTX_FRAME_RELATED_P (insn) = 1;

                  i -= (15 - first_reg);
                  offs += (16 - first_reg) * 4;
                  offset_lr = (15 - first_reg) * 4;
                }
              else
                {
                  int j;
                  for (j = first_reg; j <= 15; j++)
                    {
                      insn = emit_insn (gen_movsi
                                        (gen_rtx_MEM (SImode,
                                                      plus_constant (Pmode,
                                                                     stack_pointer_rtx,
                                                                     offs)),
                                         gen_rtx_REG (SImode, j)));
                      RTX_FRAME_RELATED_P (insn) = 1;
                      offs += 4;
                      if (j == 15)
                        offset_lr = offs - 4;
                    }

                  i -= (15 - first_reg);
                }
            }
          else if (fi.reg_mask & (1 << i))
            {
              insn = emit_insn (gen_movsi
                                (gen_rtx_MEM (SImode,
                                              plus_constant (Pmode,
                                                             stack_pointer_rtx,
                                                             offs)),
                                 gen_rtx_REG (SImode, i)));
              RTX_FRAME_RELATED_P (insn) = 1;
              offs += 4;
              if (i == 15)
                offset_lr = offs - 4;
            }
        }
    }
  if (flag_pic && fi.reg_mask & (1 << PIC_OFFSET_TABLE_REGNUM))
    {
      rtx l1 = gen_label_rtx ();
      rtx bsr_label = gen_rtx_LABEL_REF (SImode, l1);
      rtx reg_gb = gen_rtx_REG (SImode, PIC_OFFSET_TABLE_REGNUM);
      rtx reg_pc = gen_rtx_REG (SImode, LK_REGNUM);

      emit_insn (gen_prologue_get_pc (bsr_label));
      emit_insn (gen_pic_get_symbol
                 (reg_gb, bsr_label, GEN_INT (PIC_SYMBOL_GOTPC)));

      emit_insn (gen_addsi3 (reg_gb, reg_gb, reg_pc));
      emit_insn (gen_movsi (reg_pc, gen_rtx_MEM (SImode,
                                                 plus_constant (Pmode,
                                                                stack_pointer_rtx,
                                                                offset_lr))));
    }

  /* Figure the locals + outbounds.  */
  if (frame_pointer_needed)
    {
      /* If we haven't already purchased to 'fp'.  */
      if (growth < fi.local_growth)
        output_stack_adjust (-1, fi.growth[growth++]);        /* Grows it.  */

      insn =
        emit_insn (gen_movsi (hard_frame_pointer_rtx, stack_pointer_rtx));
      RTX_FRAME_RELATED_P (insn) = 1;

      /* ... and then go any remaining distance for outbounds, etc.  */
      if (fi.growth[growth])
        output_stack_adjust (-1, fi.growth[growth++]);
    }
  else
    {
      if (growth < fi.local_growth)
        output_stack_adjust (-1, fi.growth[growth++]);        /* Grows it.  */
      if (fi.growth[growth])
        output_stack_adjust (-1, fi.growth[growth++]);
    }

  /* generate .stack_size function-name, size for callgraph,
   * the default stack size is 0. */
  if (TARGET_STACK_SIZE && (space_allocated > 0))
    {
      gcc_assert (current_function_decl != NULL);
      emit_insn (gen_stack_size
                 ((XEXP (DECL_RTL (current_function_decl), 0)),
                  GEN_INT (space_allocated)));
    }

  if (flag_stack_usage_info)
    current_function_static_stack_size = space_allocated;
}

/* Emit RTL sequence for function epilogue. */

void
csky_expand_epilog (void)
{
  struct csky_frame fi;
  int i;
  int offs;
  int growth = MAX_STACK_GROWS - 1;
  rtx insn;


  /* Find out what we're doing.  */
  layout_csky_frame (&fi);

  if (csky_naked_function_p ())
    return;

  /* If we had a frame pointer, restore the sp from that.  */
  if (frame_pointer_needed)
    {
      insn =
        emit_insn (gen_movsi (stack_pointer_rtx, hard_frame_pointer_rtx));
      RTX_FRAME_RELATED_P (insn) = 1;
      growth = fi.local_growth - 1;
    }
  else
    {
      /* XXX: while loop should accumulate and do a single sell.  */
      while (growth >= fi.local_growth)
        {
          if (fi.growth[growth] != 0)
            output_stack_adjust (1, fi.growth[growth]);
          growth--;
        }
    }

  /* Make sure we've shrunk stack back to the point where the registers
     were laid down. This is typically 0/1 iterations.  Then pull the
     register save information back off the stack.  */
  while (growth >= fi.reg_growth)
    output_stack_adjust (1, fi.growth[growth--]);

  offs = fi.reg_offset;

  if (TARGET_PRELOAD_PROTECT && (fi.reg_size <= 16))
    {
      /* Add ld r6, sp+offset+16 to prevent hardware from enabling
         preload function.  */
      emit_insn (gen_movsi
                 (gen_rtx_REG (SImode, 6),
                  gen_rtx_MEM (SImode,
                               plus_constant (Pmode,
                                              stack_pointer_rtx,
                                              offs + 16))));
      emit_insn (gen_prologue_use(gen_rtx_REG (SImode, 6)));
    }

  for (i = 15; i >= 0; i--)
    {
      if (offs == 0 && i == 15 && ((fi.reg_mask & 0xc000) == 0xc000))
        {
          int first_reg;

          /* Find the starting register.  */
          first_reg = 15;

          while (fi.reg_mask & (1 << first_reg))
            first_reg--;

          first_reg++;

          if (TARGET_MULTIPLE_STLD)
            {
              emit_insn (gen_load_multiple (gen_rtx_REG (SImode, first_reg),
                                            gen_rtx_MEM (SImode,
                                                         stack_pointer_rtx),
                                            GEN_INT (16 - first_reg)));
              if (TARGET_PRELOAD_PROTECT)
                offs += (16 - first_reg) * 4;
            }
          else
            {
              if (TARGET_PRELOAD_PROTECT)
                {
                  int j = first_reg;
                  for (; j <= 15; j++)
                    {
                      insn = emit_insn (gen_movsi (
                                          gen_rtx_REG (SImode, j),
                                          gen_rtx_MEM (SImode,
                                            plus_constant (Pmode,
                                                           stack_pointer_rtx,
                                                           offs))));
                      offs += 4;
                    }
                }
              else
                {
                  int invert = offs + (16 - first_reg) * 4 - 4;
                  int j;

                  for (j = 15; j >= first_reg; j--)
                  {
                    insn = emit_insn (gen_movsi (
                                gen_rtx_REG (SImode, j),
                                gen_rtx_MEM (SImode,
                                  plus_constant (Pmode,
                                                 stack_pointer_rtx,
                                                 invert))));
                    //RTX_FRAME_RELATED_P (insn) = 1;
                    invert -= 4;
                   }
                }
            }
          i -= (15 - first_reg);
          if (!TARGET_PRELOAD_PROTECT)
            offs += (16 - first_reg) * 4;
        }
      else if (fi.reg_mask & (1 << i))
        {
          emit_insn (gen_movsi
                     (gen_rtx_REG (SImode, i),
                      gen_rtx_MEM (SImode,
                                   plus_constant (Pmode, stack_pointer_rtx,
                                                  offs))));
          offs += 4;
        }
    }

  /* Give back anything else.  */
  /* XXX: Should accumulate total and then give it back.  */
  while (growth >= 0)
    output_stack_adjust (1, fi.growth[growth--]);

  /* adjust sp by offset */
  if (crtl->calls_eh_return)
    emit_insn (gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx,
                           EH_RETURN_STACKADJ_RTX));

  current_function_anonymous_args = 0;
}


/* Return true if X is something that can be moved directly into r15.  */

bool
csky_r15_operand_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case CONST_INT:
      return csky_const_ok_for_inline (INTVAL (x));

    case REG:
    case SUBREG:
    case MEM:
      return 1;

    default:
      return 0;
    }
}

/* Implement TARGET_SECONDARY_RELOAD.  If RCLASS contains r15, and we can't
   directly move X into it, use r1-r14 as a temporary.  */

static reg_class_t
csky_secondary_reload (bool in_p ATTRIBUTE_UNUSED, rtx x, reg_class_t rclass,
                       machine_mode mode ATTRIBUTE_UNUSED,
                       secondary_reload_info * sri ATTRIBUTE_UNUSED)
{
  if (TEST_HARD_REG_BIT (reg_class_contents[rclass], 15)
      && !csky_r15_operand_p (x))
    return LRW_REGS;

  int regno = -1;
  if (GET_CODE (x) == REG || GET_CODE (x) == SUBREG)
    regno = true_regnum (x);

  /* We always require a general register when copying anything to
     HI/LO_REGNUM, except when copying an SImode value from HI/LO_REGNUM
     to a general register, or when copying from register 0.  */
  if ((rclass == HILO_REGS || rclass == LO_REGS || rclass == HI_REGS)
      && !GENERAL_REG_P (regno))
    return GENERAL_REGS;

  if (rclass == FPU_REGS && !GENERAL_REG_P (regno))
    return GENERAL_REGS;

  return NO_REGS;
}

/* Return the reg_class to use when reloading the rtx X into the class
   RCLASS.  If X is too complex to move directly into r15, prefer to
   use LRW_REGS instead.  */

static reg_class_t
csky_preferred_reload_class (rtx x, reg_class_t rclass)
{
  if (reg_class_subset_p (LRW_REGS, rclass) && !csky_r15_operand_p (x))
    return LRW_REGS;

  return rclass;
}

static void
csky_option_override (void)
{
  const struct csky_processors *csky_proc, *csky_proc_end;
  const struct csky_architectures *csky_arch, *csky_arch_end;
  int flag;
  unsigned long temp_arch_flags, temp_csky_flags, temp_target_flags;

  /* Only support dwarf debuging info */
  /* Don't emit DWARF2/4 unless specifically selected. */
  if (!global_options_set.x_dwarf_strict)
    dwarf_strict = 1;
  if (!global_options_set.x_dwarf_version)
    dwarf_version = 3;

  /* if -mcpu= is specified */
  if (csky_cpu_string)
    {
      csky_proc_end = csky_all_processors + csky_num_cpu;
      csky_proc = csky_all_processors;
      flag = 0;
      for (; csky_proc < csky_proc_end; csky_proc++)
        {
          if (!strcmp (csky_cpu_string, csky_proc->name))
            {
              flag = 1;
              temp_arch_flags = csky_proc->arch_flags;
              temp_csky_flags = csky_proc->csky_flags;
              temp_target_flags = csky_proc->sub_target_flags;
              break;
            }
        }

      if (!flag)
        {
          error ("bad value (%s) for -mcpu= switch", csky_cpu_string);
          abort ();
        }

      target_flags |= temp_target_flags;
      arch_flags |= temp_arch_flags;
      csky_flags |= temp_csky_flags;
    }

  /* if -march= is specified */
  else
    {
      /* neither -mcpu nor -march is specified, assume -march=ck510 */
      if (!csky_arch_string)
        csky_arch_string = "ck510";

      csky_arch_end = csky_all_architectures + csky_num_arch;
      csky_arch = csky_all_architectures;
      flag = 0;
      for (; csky_arch < csky_arch_end; csky_arch++)
        {
          if (!strcmp (csky_arch_string, csky_arch->name))
            {
              flag = 1;
              temp_arch_flags = csky_arch->arch_flags;
              temp_csky_flags = csky_arch->csky_flags;
              break;
            }
        }

      if (!flag)
        {
          error ("bad value (%s) for -march= switch", csky_arch_string);
          abort ();
        }

      arch_flags |= temp_arch_flags;
      csky_flags |= temp_csky_flags;
    }

  /* handle -msoft-fp, -mhard-fp and etc */
  if (TARGET_HARD_FLOAT && (TARGET_CK510 || TARGET_CK610))
    {
      target_flags |= MASK_FPUV1;
    }
  else if (TARGET_HARD_FLOAT && (TARGET_CK803 || TARGET_CK810))
    {
      target_flags |= MASK_FPUV2;
    }

  /* FIXME added by yanwb 2011/3/2 shut off ldm stm */
  if (flag_strict_volatile_bitfields < 0)
    flag_strict_volatile_bitfields = 1;

  if (flag_stack_protect != 0)
    {
      flag_stack_protect_cskyv1 = flag_stack_protect;
      flag_stack_protect = 0;
    }
}


/* Compute the number of word sized registers needed to
   hold a function argument of mode MODE and type TYPE.  */

int
csky_num_arg_regs (machine_mode mode, const_tree type)
{
  int size;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return 0;

  if (type && mode == BLKmode)
    size = int_size_in_bytes (type);
  else
    size = GET_MODE_SIZE (mode);

  return ROUND_ADVANCE (size);
}


/* Define how to find the scalar value returned by a function.  */

static rtx
csky_function_value (const_tree valtype, const_tree func,
                     bool outgoing ATTRIBUTE_UNUSED)
{
  enum machine_mode mode;
  int unsigned_p;
  int size;

  mode = TYPE_MODE (valtype);
  size = int_size_in_bytes (valtype);

  /* Since we promote return types, we must promote the mode here too.  */
  if (INTEGRAL_TYPE_P (valtype))
    {
      mode = promote_function_mode (valtype, mode, &unsigned_p, func, 1);
      return gen_rtx_REG (mode, FIRST_RET_REG);
    }

  if (mode == BLKmode && size > UNITS_PER_WORD && size <= UNITS_PER_WORD * 2)
    {
      rtx ret_regs[2];
      rtx result;
      rtvec tmp_rtvec;

      ret_regs[0] = gen_rtx_EXPR_LIST (SImode, gen_rtx_REG (SImode, 2),
                                       GEN_INT (0 * UNITS_PER_WORD));
      ret_regs[1] = gen_rtx_EXPR_LIST (SImode, gen_rtx_REG (SImode, 3),
                                       GEN_INT (1 * UNITS_PER_WORD));
      tmp_rtvec = gen_rtvec (2, ret_regs[0], ret_regs[1]);

      result = gen_rtx_PARALLEL (mode, tmp_rtvec);
      return result;
    }

  return gen_rtx_REG (mode, FIRST_RET_REG);
}

/* 1 if N is a possible register number for a function value.
   On the CSKY, only r2 can return results.  */

static bool
csky_function_value_regno_p (const unsigned int regno)
{
  return (regno == FIRST_RET_REG);
}

/* Define where to put the arguments to a function.
   Value is zero to push the argument on the stack,
   or a hard register in which to store the argument.

   MODE is the argument's machine mode.
   TYPE is the data type of the argument (as a tree).
    This is null for libcalls where that information may
    not be available.
   CUM is a variable of type CUMULATIVE_ARGS which gives info about
    the preceding args and about the function being called.
   NAMED is nonzero if this argument is a named parameter
    (otherwise it is an extra parameter matching an ellipsis).

   On CSKY the first args are normally in registers
   and the rest are pushed.  Any arg that starts within the first
   NPARM_REGS words is at least partially passed in a register unless
   its data type forbids.  */

static rtx
csky_function_arg (cumulative_args_t cum, machine_mode mode,
                   const_tree type, bool named)
{
  int arg_reg;

  if (!named || mode == VOIDmode)
    return 0;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return 0;

  arg_reg = ROUND_REG (*get_cumulative_args (cum), mode);

  if (arg_reg < NPARM_REGS)
    return gen_rtx_REG (mode, FIRST_PARM_REG + arg_reg);

  return 0;
}


/* Update the data in PCUM to advance over an argument
   of mode MODE and data type TYPE.
   (TYPE is null for libcalls where that information may not be available.)  */

static void
csky_function_arg_advance (cumulative_args_t cum_v, machine_mode mode,
                           const_tree type, bool named ATTRIBUTE_UNUSED)
{
  CUMULATIVE_ARGS *cum = get_cumulative_args (cum_v);

  *cum = (ROUND_REG (*cum, mode)
          + (int) named * csky_num_arg_regs (mode, type));
}

static unsigned int
csky_function_arg_boundary (machine_mode mode,
                            const_tree type ATTRIBUTE_UNUSED)
{
  /* Doubles must be aligned to an 8 byte boundary.  */
  return ((mode != BLKmode && mode != CSImode
           && GET_MODE_SIZE (mode) > 4)
          ? BIGGEST_ALIGNMENT : PARM_BOUNDARY);
}

/* Returns the number of bytes of argument registers required to hold *part*
   of a parameter of machine mode MODE and type TYPE (which may be NULL if
   the type is not known).  If the argument fits entirely in the argument
   registers, or entirely on the stack, then 0 is returned.  CUM is the
   number of argument registers already used by earlier parameters to
   the function.  */

static int
csky_arg_partial_bytes (cumulative_args_t cum, machine_mode mode,
                        tree type, bool named)
{
  int reg = ROUND_REG (*get_cumulative_args (cum), mode);

  if (named == 0)
    return 0;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return 0;

  /* REG is not the *hardware* register number of the register that holds
     the argument, it is the *argument* register number.  So for example,
     the first argument to a function goes in argument register 0, which
     translates (for the CSKY) into hardware register 2.  The second
     argument goes into argument register 1, which translates into hardware
     register 3, and so on.  NPARM_REGS is the number of argument registers
     supported by the target, not the maximum hardware register number of
     the target.  */
  if (reg >= NPARM_REGS)
    return 0;

  /* If the argument fits entirely in registers, return 0.  */
  if (reg + csky_num_arg_regs (mode, type) <= NPARM_REGS)
    return 0;

  /* The argument overflows the number of available argument registers.
     Compute how many argument registers have not yet been assigned to
     hold an argument.  */
  reg = NPARM_REGS - reg;

  /* Return partially in registers and partially on the stack.  */
  return reg * UNITS_PER_WORD;
}

/* CSKY specific attribute support.
   naked     - do not create a function prologue/epilogue.  */

/* Handle a "naked" attribute; arguments as in
   struct attribute_spec.handler.  */

static tree
csky_handle_naked_attribute (tree * node, tree name,
                             tree args ATTRIBUTE_UNUSED,
                             int flags ATTRIBUTE_UNUSED, bool * no_add_attrs)
{
  if (TREE_CODE (*node) != FUNCTION_DECL)
    {
      warning (OPT_Wattributes, "%qE attribute only applies to functions",
               name);
      *no_add_attrs = true;
    }

  return NULL_TREE;
}

int
csky_naked_function_p (void)
{
  return lookup_attribute ("naked",
                           DECL_ATTRIBUTES (current_function_decl)) !=
    NULL_TREE;
}

static bool
csky_warn_func_return (tree decl)
{
  /* Naked functions are implemented entirely in assembly, including the
     return sequence, so suppress warnings about this.  */
  return lookup_attribute ("naked", DECL_ATTRIBUTES (decl)) == NULL_TREE;
}

/* Worker function for TARGET_RETURN_IN_MEMORY.  */

static bool
csky_return_in_memory (const_tree type, const_tree fntype ATTRIBUTE_UNUSED)
{
  const HOST_WIDE_INT size = int_size_in_bytes (type);
  return (size == -1 || size > 2 * UNITS_PER_WORD);
}

/* Worker function for TARGET_ASM_TRAMPOLINE_TEMPLATE.
   Output assembler code for a block containing the constant parts
   of a trampoline, leaving space for the variable parts. */

static void
csky_asm_trampoline_template (FILE * f)
{
  fprintf (f, "\tlrw %s, [.Ltrampoline_data]\n",
           reg_names[STATIC_CHAIN_REGNUM]);
  fprintf (f, "\tjmpi [.Ltrampoline_data + 4]\n");
  fprintf (f, ".Ltrampoline_data:\n");
  fprintf (f, "\t.long        0\n");
  fprintf (f, "\t.long        0\n");
}

/* Worker function for TARGET_TRAMPOLINE_INIT.  */

static void
csky_trampoline_init (rtx m_tramp, tree fndecl, rtx chain_value)
{
  rtx fnaddr = XEXP (DECL_RTL (fndecl), 0);
  rtx mem, a_tramp;

  emit_block_move (m_tramp, assemble_trampoline_template (),
                   GEN_INT (TRAMPOLINE_SIZE - 8), BLOCK_OP_NORMAL);

  mem = adjust_address (m_tramp, SImode, 4);
  emit_move_insn (mem, chain_value);
  mem = adjust_address (m_tramp, SImode, 8);
  emit_move_insn (mem, fnaddr);

  a_tramp = XEXP (m_tramp, 0);
  emit_library_call (gen_rtx_SYMBOL_REF (Pmode, "__clear_cache"),
                     LCT_NORMAL, VOIDmode, 2, a_tramp, Pmode,
                     plus_constant (Pmode, a_tramp, TRAMPOLINE_SIZE), Pmode);
}

/* Implement TARGET_LEGITIMATE_CONSTANT_P

   On the CSKY, allow anything but a double.  */

static bool
csky_legitimate_constant_p (machine_mode mode ATTRIBUTE_UNUSED, rtx x)
{
  return !csky_tls_referenced_p (x) && CONSTANT_P (x);
}

/* Helper function for `csky_legitimate_address_p'.  */

static bool
csky_decompose_address (rtx addr, struct csky_address *out)
{
  rtx base = NULL_RTX, index = NULL_RTX, disp = NULL_RTX;
  HOST_WIDE_INT scale = 1;
  rtx scale_rtx = NULL_RTX;
  int i;

  out->base = out->index = out->disp = NULL_RTX;
  out->scale = 0;

  if (REG_P (addr))
    {
      out->base = addr;
      return true;
    }

  if (GET_CODE (addr) != PLUS)
    return false;


  rtx addends[2], op, tmp;

  addends[0] = XEXP (addr, 0);
  addends[1] = XEXP (addr, 1);

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
          break;

        case ASHIFT:
          if (index)
            return false;
          index = XEXP (op, 0);
          scale_rtx = XEXP (op, 1);
          if (!CONST_INT_P (scale_rtx))
            return false;
          scale = scale << INTVAL (scale_rtx);


        default:
          return false;
        }
    }

  if (!base)
    return false;

  if (scale_rtx && !CONST_INT_P (scale_rtx))
    {
      tmp = scale_rtx;
      scale_rtx = index;
      index = tmp;
    }

  if (scale_rtx && !CONST_INT_P (scale_rtx))
    return false;
  else if (scale_rtx && CONST_INT_P (scale_rtx))
    scale = INTVAL (scale_rtx);

  out->base = base;
  out->index = index;
  out->disp = disp;
  out->scale = scale;

  return true;
}

/* Determine whether a rtx may be used as a base address of memory addr */

static bool
csky_reg_ok_for_base_p (const_rtx reg, bool strict_p)
{
  if (strict_p)
    return REGNO_OK_FOR_BASE_P (REGNO (reg));
  else
    return (GENERAL_REG_P (REGNO (reg)) || !HARD_REGISTER_P (reg));
}

static bool
csky_base_register_rtx_p (const_rtx x, bool strict_p)
{
  return REG_P (x) && csky_reg_ok_for_base_p (x, strict_p);
}

/*  A legitimate index for a QI is 0..15, for HI is 0..30, for SI is 0..60,
    and for DI is 0..56 because we use two SI loads, etc.  */

static bool
csky_legitimate_disp_p (machine_mode mode, const_rtx op)
{
  if (CONST_INT_P (op))
    {
      if (GET_MODE_SIZE (mode) >= 4
          && (((unsigned HOST_WIDE_INT) INTVAL (op)) % 4) == 0
          && ((unsigned HOST_WIDE_INT) INTVAL (op))
          <= (unsigned HOST_WIDE_INT) 64 - GET_MODE_SIZE (mode))
        return true;
      if (GET_MODE_SIZE (mode) == 2
          && (((unsigned HOST_WIDE_INT) INTVAL (op)) % 2) == 0
          && ((unsigned HOST_WIDE_INT) INTVAL (op)) <= 30)
        return true;
      if (GET_MODE_SIZE (mode) == 1
          && ((unsigned HOST_WIDE_INT) INTVAL (op)) <= 15)
        return true;
    }
  return false;
}


/* Worker function for TARGET_ADDR_SPACE_LEGITIMATE_ADDRESS_P.

   Allow  REG
          REG + disp  */

static bool
csky_legitimate_address_p (machine_mode mode, rtx x, bool strict_p,
                           addr_space_t as)
{
  gcc_assert (ADDR_SPACE_GENERIC_P (as));

  struct csky_address addr;

  if (!csky_decompose_address (x, &addr))
    return false;

  /* verify base register */
  if (!csky_base_register_rtx_p (addr.base, strict_p))
    return false;

  if (addr.index)
    return false;

  if (addr.disp && !csky_legitimate_disp_p (mode, addr.disp))        /* verify disp operand */
    return false;

  return true;
}

/* Implement TARGET_CONDITIONAL_REGISTER_USAGE. */

static void
csky_conditional_register_usage (void)
{
  if (TARGET_CSKYV1 || !(TARGET_HIGH_REGISTERS))
    {
      int i;

      for (i = 16; i < 32; i++)
        {
          fixed_regs[i] = 1;
          call_used_regs[i] = 1;
        }
    }
  if (!(TARGET_DSP || TARGET_SECURITY))
    {
      fixed_regs[HI_REG] = 1;
      call_used_regs[HI_REG] = 1;

      fixed_regs[LO_REG] = 1;
      call_used_regs[LO_REG] = 1;
    }

  if (!TARGET_FPUV1 || !TARGET_HARD_FLOAT)
    {
      int regno;

      for (regno = FPU_REG_FIRST; regno <= FPU_REG_LAST; regno++)
        {
          fixed_regs[regno] = 1;
          call_used_regs[regno] = 1;
        }
    }

  if (flag_pic)
    {
      fixed_regs[PIC_OFFSET_TABLE_REGNUM] = 1;
      call_used_regs[PIC_OFFSET_TABLE_REGNUM] = 1;
      call_really_used_regs[PIC_OFFSET_TABLE_REGNUM] = 0;
      reg_names[PIC_OFFSET_TABLE_REGNUM] = "gb";
    }
}

/* Return TRUE if X references a SYMBOL_REF.  */

int
symbol_mentioned_p (rtx x)
{
  const char *fmt;
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
  const char *fmt;
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

    default:
      return 0;
    }
}

/* Implement TARGET_ASM_OUTPUT_MI_THUNK.  Generate rtl rather than asm text
   in order to avoid duplicating too much logic from elsewhere.  */

static void
csky_output_mi_thunk (FILE * file, tree thunk_fndecl ATTRIBUTE_UNUSED,
                      HOST_WIDE_INT delta, HOST_WIDE_INT vcall_offset,
                      tree function)
{

  const char *this_reg, *temp0_reg, *temp1_reg;
  rtx fnaddr;
  int flag_restore = 0;

  final_start_function (emit_barrier (), file, 1);

  fnaddr = XEXP (DECL_RTL (function), 0);

  /* We need two temporary registers in some cases.  */
  temp0_reg = "r1";
  temp1_reg = "r15";

  /* Find out which register contains the "this" pointer.  */
  if (aggregate_value_p (TREE_TYPE (TREE_TYPE (function)), function))
    this_reg = "a1";
  else
    this_reg = "a0";

  if (flag_pic || (vcall_offset > 32 || vcall_offset < -32))
    {
      fprintf(file, "\tsubi\tsp, sp, 8\n");
      fprintf(file, "\tst.w\tr15, (sp, 0)\n");

      flag_restore = 1;
    }

  /* Add delta to this_rtx.  */
  if (delta != 0)
    {
      if (delta > 32 || delta < -32)
        {
          fprintf (file, "\tlrw\t%s, 0x%lx\n", temp0_reg, delta);
          fprintf (file, "\taddu\t%s, %s, %s\n", this_reg, this_reg,
                   temp0_reg);
        }
      else
        {
          fprintf (file, "\t%s\t%s, %s, 0x%lx\n",
                   ((delta > 0) ? "addi" : "subi"), this_reg, this_reg,
                   ((delta > 0) ? delta : -delta));
        }
    }

  /* If needed, add *(*this_rtx + vcall_offset) to this_rtx.  */
  if (vcall_offset != 0)
    {

      if (vcall_offset > 32 || vcall_offset < -32)
        {
          fprintf (file, "\tld.w\t%s, (%s, 0)\n", temp1_reg, this_reg);
          fprintf (file, "\tlrw\t%s, 0x%lx\n", temp0_reg, vcall_offset);
          fprintf (file, "\taddu\t%s, %s, %s\n", temp0_reg, temp0_reg,
                   temp1_reg);
        }
      else
        {
          fprintf (file, "\tld.w\t%s, (%s, 0)\n", temp0_reg, this_reg);
          fprintf (file, "\t%s\t%s, %s, 0x%lx\n",
                   ((vcall_offset > 0) ? "addi" : "subi"),
                   temp0_reg, temp0_reg,
                   ((vcall_offset > 0) ? vcall_offset : -vcall_offset));
        }

      /* Load the offset and add it to this_rtx  */
      fprintf (file, "\tld.w\t%s, (%s, 0)\n", temp0_reg, temp0_reg);
      fprintf (file, "\taddu\t%s, %s, %s\n", this_reg, this_reg, temp0_reg);
    }

  if (flag_pic)
    {
      fprintf(file, "\tbsr \t");
      output_addr_const(file, fnaddr);
      fprintf(file, "_GET_PC\n");
      output_addr_const(file, fnaddr);
      fprintf(file, "_GET_PC:\n");

      fprintf(file, "\tlrw \t%s, ", temp0_reg);
      output_addr_const(file, fnaddr);
      fprintf(file, "_GET_PC@GOTPC\n");

      fprintf(file, "\taddu\t%s, %s, %s\n", temp1_reg, temp1_reg, temp0_reg);

      fprintf(file, "\tlrw \t%s, ", temp0_reg);
      output_addr_const(file, fnaddr);
      fprintf(file, "@GOTOFF\n");

      fprintf(file, "\taddu\t%s, %s, %s\n", temp0_reg, temp0_reg, temp1_reg);

      fprintf(file, "\tld.w\tr15, (sp, 0)\n");
      fprintf(file, "\taddi\tsp, sp, 8\n");

      fprintf(file, "\tjmp \t%s\n", temp0_reg);

      final_end_function ();

      return;
    }

  /* Restore r15 if it is needed */
  if (flag_restore)
    {
      fprintf(file, "\tld.w\tr15, (sp, 0)\n");
      fprintf(file, "\taddi\tsp, sp, 8\n");
    }

  /* Jump to the function */
  fprintf (file, "\tjbr\t");
  output_addr_const (file, fnaddr);
  fprintf (file, "\n");

  final_end_function ();
}

static GTY (()) int tls_labelno;

/* Build the SYMBOL_REF for __tls_get_addr.  */

static GTY (()) rtx tls_get_addr_libfunc;

/* Return TRUE if X contains any TLS symbol references.  */

bool
csky_tls_referenced_p (rtx x)
{
  if (!TARGET_HAVE_TLS)
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
  rtx tmp;

  if (!target)
    target = gen_reg_rtx (SImode);

  /* Always returned in r2.  Immediately copy the result into a pseudo,
     otherwise other uses of r2 (e.g. setting up function arguments) may
     clobber the value.  */

  if (flag_pic)
    emit_insn (gen_load_tp_soft_pic ());
  else
    emit_insn (gen_load_tp_soft ());

  tmp = gen_rtx_REG (SImode, 2);
  emit_move_insn (target, tmp);
  return target;
}

static rtx
csky_call_tls_get_addr (rtx x, rtx reg, rtx * valuep, int reloc)
{
  rtx insns, labelno;

  if (reg == NULL_RTX)
    reg = gen_reg_rtx (SImode);

  start_sequence ();

  labelno = GEN_INT (tls_labelno++);
  emit_insn (gen_tls_get_symbol_1 (reg, x, GEN_INT (reloc), labelno));
  *valuep = emit_library_call_value (get_tls_get_addr (), NULL_RTX, LCT_PURE,        /* LCT_CONST?  */
                                     Pmode, 1, reg, Pmode);

  insns = get_insns ();
  end_sequence ();

  return insns;
}

rtx
legitimize_tls_address (rtx x, rtx reg)
{
  rtx dest, tp, labelno, insns, ret, eqv, addend;
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
      addend = gen_rtx_UNSPEC (Pmode, gen_rtvec (2, x, GEN_INT (TLS_LDO32)),
                               UNSPEC_TLS);
      addend = force_reg (SImode, addend);
      return gen_rtx_PLUS (Pmode, dest, addend);

    case TLS_MODEL_INITIAL_EXEC:
      if (reg == NULL_RTX)
        reg = gen_reg_rtx (SImode);

      labelno = GEN_INT (tls_labelno++);
      emit_insn (gen_tls_get_symbol_1 (reg, x, GEN_INT (TLS_IE32), labelno));

      emit_move_insn (reg, gen_const_mem (Pmode, reg));

      tp = csky_load_tp (NULL_RTX);

      return gen_rtx_PLUS (Pmode, reg, tp);

    case TLS_MODEL_LOCAL_EXEC:
      tp = csky_load_tp (NULL_RTX);
      if (reg == NULL_RTX)
        reg = gen_reg_rtx (SImode);
      emit_insn (gen_tls_get_symbol_2 (reg, x, GEN_INT (TLS_LE32)));
      return gen_rtx_PLUS (Pmode, reg, tp);

    default:
      abort ();
    }
}

rtx
legitimize_pic_address (rtx orig, enum machine_mode mode ATTRIBUTE_UNUSED,
                        rtx reg, int flag)
{
  /* FIXME replace the 14 by macro */
  rtx pic_reg = gen_rtx_REG (SImode, 14);
  int flag_optimize = 0;

  if (GET_CODE (orig) == SYMBOL_REF || GET_CODE (orig) == LABEL_REF)
    {
      rtx pic_ref;
      rtx insn;
      rtx address = reg;

      if (reg == 0)
        {
          gcc_assert (can_create_pseudo_p ());
          reg = gen_reg_rtx (Pmode);
          address = gen_reg_rtx (Pmode);
        }

      if (GET_CODE (orig) == LABEL_REF
          || ((GET_CODE (orig) == SYMBOL_REF && SYMBOL_REF_LOCAL_P (orig))))
        {
          emit_insn (gen_pic_get_symbol
                     (address, orig, GEN_INT (PIC_SYMBOL_GOTOFF)));
          pic_ref = gen_rtx_PLUS (Pmode, address, pic_reg);

          flag_optimize = 1;
        }
      else
        {
          flag_optimize = flag;

          /* when flag != 0 generate sym@GOT, otherwise generate sym@PLT */
          emit_insn (gen_pic_get_symbol
                     (address, orig,
                      GEN_INT (flag ? PIC_SYMBOL_GOT : PIC_SYMBOL_PLT)));
          emit_move_insn (address, gen_rtx_PLUS (Pmode, address, pic_reg));
          pic_ref = gen_const_mem (Pmode, address);
        }
      insn = emit_move_insn (reg, pic_ref);

      /* Put a REG_EQUAL note on this insn, so that it can be optimized by loop */
      if (flag_optimize)
        set_unique_reg_note (insn, REG_EQUAL, orig);

      return reg;
    }
  else if (GET_CODE (orig) == CONST)
    {
      rtx base, offset;

      if (GET_CODE (XEXP (orig, 0)) == PLUS
          && XEXP (XEXP (orig, 0), 1) == pic_reg)
        return orig;

      if (reg == 0)
        {
          gcc_assert (can_create_pseudo_p ());
          reg = gen_reg_rtx (Pmode);
        }

      gcc_assert (GET_CODE (XEXP (orig, 0)) == PLUS);

      base =
        legitimize_pic_address (XEXP (XEXP (orig, 0), 0), Pmode, reg, flag);
      offset =
        legitimize_pic_address (XEXP (XEXP (orig, 0), 1), Pmode,
                                base == reg ? 0 : reg, flag);

      if (GET_CODE (offset) == CONST_INT)
        return plus_constant (SImode, base, INTVAL (offset));

      return gen_rtx_PLUS (Pmode, base, offset);
    }

  return orig;
}

/* Must not copy the TLS insn that needs an internal label.  */

static bool
csky_cannot_copy_insn_p (rtx_insn * insn)
{
  if (recog_memoized (insn) == CODE_FOR_tls_get_symbol_1)
    return true;

  return false;
}

/* In cskyv1 pic mode, we don't allow general a jump insn after reload */
static bool
csky_cannot_modify_jumps_p (void)
{
  if (!flag_pic || !(TARGET_CSKYV1))
    return false;

  return (reload_completed || reload_in_progress);
}

/* tls symbol cannot be spilled to constant pool */
static bool
csky_cannot_force_const_mem (machine_mode, rtx x)
{
  return csky_tls_referenced_p (x);
}

/* set the caller frame exceptions handler address as lr  */
void
csky_set_eh_return_address (rtx source, rtx scratch)
{
  struct csky_frame fi;
  layout_csky_frame (&fi);
  HOST_WIDE_INT delta = 0;
  rtx addr;
  unsigned long saved_regs;

  saved_regs = fi.reg_mask;

  if (((saved_regs & (1 << LK_REG)) == 0))
    emit_move_insn (gen_rtx_REG (Pmode, LK_REG), source);
  else
    {
      /* LR will be the toppest saved register.  */
      int i = 0;
      delta = 0;
      while (i < MAX_STACK_GROWS)
        delta += fi.growth[i++];
      delta -= fi.arg_size;
      delta -= fi.pad_reg + 4;

      /* frame pointer saved above r15 */
      if (frame_pointer_needed
          && ((saved_regs & (1 << HARD_FRAME_POINTER_REGNUM)) != 0))
        delta -= 4;
      /* If eh_return, EH_RETURN_DATA_REGNO saved above r15.  */
      if (crtl->calls_eh_return)
        {
          unsigned int i;
          for (i = 0; EH_RETURN_DATA_REGNO (i) != INVALID_REGNUM; i++)
            delta -= 4;
        }

      if (delta > 32)
        {
          emit_insn (gen_movsi (scratch, GEN_INT (delta)));
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

/* Determine whether LRA should be enabled. */

static bool
csky_lra_p (void)
{
  return TARGET_LRA;
}

/* Implement RETURN_ADDR_RTX.  We do not support moving back to  a previous frame.  */

rtx
csky_return_addr (int count, rtx frame ATTRIBUTE_UNUSED)
{
  if (count != 0)
    return NULL_RTX;

  return get_hard_reg_initial_val (Pmode, LK_REGNUM);
}

/* Set up library functions unique to CSKY.  */

static void
csky_init_libfuncs(void)
{
  if (TARGET_CSKY_LINUX)
    init_sync_libfuncs (UNITS_PER_WORD);
}

/* For use by FUNCTION_ARG_PADDING (MODE, TYPE).
   Return true if an argument passed on the stack should be padded upwards,
   i.e. if the least-significant byte has useful data. */

bool
csky_pad_arg_upward (machine_mode mode ATTRIBUTE_UNUSED, const_tree type)
{
  if (type && BYTES_BIG_ENDIAN && INTEGRAL_TYPE_P (type))
    return false;

  return true;
}

/* Similarly, for use by BLOCK_REG_PADDING (MODE, TYPE, FIRST).
   Return !BYTES_BIG_ENDIAN if the least significant byte of the
   register has useful data, and return the opposite if the most
   significant byte does.  */

bool
csky_pad_reg_upward (machine_mode mode,
                    tree type, int first ATTRIBUTE_UNUSED)
{
  if (BYTES_BIG_ENDIAN)
    {
      /* Small aggregates, small fixed-point types,
         and small complex types are always padded upwards.  */
      if (type)
        {
          if ((AGGREGATE_TYPE_P (type)
               || TREE_CODE (type) == COMPLEX_TYPE
               || FIXED_POINT_TYPE_P (type))
              && int_size_in_bytes (type) <= 4)
            return true;
        }
      else
        {
          if ((COMPLEX_MODE_P (mode) || ALL_FIXED_POINT_MODE_P (mode))
              && GET_MODE_SIZE (mode) <= 4)
            return true;
        }
    }

  /* Otherwise, use default padding.  */
  return !BYTES_BIG_ENDIAN;
}

#include "gt-abiv1-csky.h"
