
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
/* FIXME Include this file for function dwarf2out_do_frame, can we
   repalce this function just like arm?  */
#include "debug.h"

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

/* The register number to be used for the PIC offset register.  */
unsigned csky_pic_register = INVALID_REGNUM;

/******************************************************************
 *                         Storage Layout                         *
 ******************************************************************/


#undef  TARGET_PROMOTE_FUNCTION_MODE
#define TARGET_PROMOTE_FUNCTION_MODE \
  default_promote_function_mode_always_promote


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

#undef  TARGET_PROMOTE_PROTOTYPES
#define TARGET_PROMOTE_PROTOTYPES hook_bool_const_tree_true

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


/******************************************************************
 *                Implementing the Varargs Macros                 *
 ******************************************************************/


#undef  TARGET_SETUP_INCOMING_VARARGS
#define TARGET_SETUP_INCOMING_VARARGS csky_setup_incoming_varargs


/******************************************************************
 *         Defining target-specific uses of __attribute__         *
 ******************************************************************/


#undef  TARGET_OPTION_OVERRIDE
#define TARGET_OPTION_OVERRIDE csky_option_override


static const struct csky_processors all_cores[] =
{
#undef CSKY_CORE
#define CSKY_CORE(NAME, CORE, X, ARCH, ISA)  \
  {NAME, TARGET_CPU_##CORE, #ARCH, CSKY_BASE_ARCH_##ARCH, \
  {ISA CSKY_ISA_FEATURE_GET(none)}},
#include "abiv2_csky_cores.def"
#undef CSKY_CORE
  {NULL, TARGET_CPU_csky_none, NULL, CSKY_BASE_ARCH_NONE, \
  {CSKY_ISA_FEATURE_GET(none)}}
};

static const struct csky_processors all_architectures[] =
{
#undef CSKY_ARCH
#define CSKY_ARCH(NAME, CORE, ARCH, ISA)     \
  {NAME, TARGET_CPU_##CORE, #ARCH, CSKY_BASE_ARCH_##ARCH,  \
  {ISA CSKY_ISA_FEATURE_GET(none)}},
#include "abiv2_csky_arches.def"
#undef CSKY_ARCH
  {NULL, TARGET_CPU_csky_none, NULL, CSKY_BASE_ARCH_NONE, \
  {CSKY_ISA_FEATURE_GET(none)}}
};

static const struct csky_fpu_desc all_fpus[] =
{
#undef CSKY_FPU
#define CSKY_FPU(NAME, CNAME, ISA) \
  {NAME, {ISA CSKY_ISA_FEATURE_GET(none)}},
#include "abiv2_csky_fpus.def"
#undef CSKY_FPU
};

static sbitmap csky_isa_all_fpubits;

/* Active target architecture.  */
struct csky_build_target csky_active_target;

/* The following are used in the .md file as equivalents to bits.  */
int csky_arch_isa_features[CSKY_ISA_FEATURE_GET(max)] = {0};

/* The highest CSKY architecture version supported by the target.  */
enum csky_base_architecture csky_base_arch = CSKY_TARGET_ARCH_GET(NONE);

const char *csky_arch_name = NULL;


/* Forward definitions of types.  */
typedef struct minipool_node    Mnode;
typedef struct minipool_fixup   Mfix;


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


/******************************************************************
 *                    Miscellaneous Parameters                    *
 ******************************************************************/


#undef  TARGET_MACHINE_DEPENDENT_REORG
#define TARGET_MACHINE_DEPENDENT_REORG csky_reorg

#undef  TARGET_ALLOCATE_STACK_SLOTS_FOR_ARGS
#define TARGET_ALLOCATE_STACK_SLOTS_FOR_ARGS csky_allocate_stack_slots_for_args

/* The declaration of functions.  */
static void get_csky_frame_layout (csky_stack_frame *);
static unsigned long get_csky_isr_type(tree);
static void push_csky_minipool_fix (rtx_insn *, HOST_WIDE_INT, rtx *,
                                    machine_mode, rtx);
static bool csky_decompose_address (rtx addr, struct csky_address * out);
void csky_print_operand_address (FILE * stream, machine_mode mode, rtx x);
void csky_print_operand (FILE * stream, rtx x, int code);
static enum csky_inline_const_type
try_csky_constant_tricks (HOST_WIDE_INT value, HOST_WIDE_INT * x,
                          HOST_WIDE_INT * y);


static int
csky_naked_function_p (void)
{
  return (lookup_attribute ("naked",
                            DECL_ATTRIBUTES (current_function_decl))
          != NULL_TREE);
}


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


/* Only output argument spill and registers save instructions if needed.  */

static void
process_csky_function_prologue (FILE *f,
                                HOST_WIDE_INT frame_size,
                                int asm_out,
                                HOST_WIDE_INT *length)
{
  /* FIXME it should be designed again.  */
#if 0
  struct csky_frame fi;
  int cfa_offset = 0;
  unsigned long func_type;
  int cfa_reg = CSKY_SP_REGNUM;
  int space_allocated = 0;

  if (length)
    *length = 0;

  if (csky_naked_function_p() && asm_out)
    {
      asm_fprintf(f, "\t#Naked Function: prologue and epilogue \
                      provided by programmer.\n");
      return;
    }

  func_type = get_csky_current_func_type();
  if((func_type & CSKY_FT_INTERRUPT) != 0 && asm_out)
    {
      asm_fprintf(f, "\t#Interrupt Service Routine.\n");
      asm_fprintf(f, "\tnie\n\tipush\n");
      if (length)
        *length += 4;
    }

  get_csky_frame_layout(&fi);

  space_allocated = fi.arg_size + fi.reg_size + fi.local_size
                    + fi.outbound_size + fi.pad_outbound
                    + fi.pad_local + fi.pad_reg;

  if (fi.arg_size != 0 && crtl->args.pretend_args_size == 0)
    {
      int offset = fi.arg_size + fi.pad_arg - 4;
      int rn = CSKY_FIRST_PARM_REG + CSKY_NPARM_REGS - 1;
      int remaining = fi.arg_size;

      if (asm_out)
        {
          asm_fprintf (f, "\tsubi\t%s, %d\n", reg_names[CSKY_SP_REGNUM],
                       fi.arg_size + fi.pad_arg);
        }
      if (length)
        {
          *length += 4;
        }
      if(dwarf2out_do_frame() && asm_out)
        {
          char *l = dwarf2out_cfi_label(false);
          cfa_offset += fi.arg_size + fi.pad_arg;
          dwarf2out_def_cfa(l, cfa_reg, cfa_offset);
        }
      for (; remaining >= 4; offset -=4, rn--, remaining -= 4)
        {
          if (asm_out)
            {
              asm_fprintf (f, "\tst.w\t%s, (%s, %d)\n", reg_names[rn],
                           reg_names[CSKY_SP_REGNUM], offset);
            }
          if (length)
            {
              *length += 4;
            }
          if(dwarf2out_do_frame() && asm_out)
            {
              char *l = dwarf2out_cfi_label(false);
              dwarf2out_reg_save (l, rn, offset - cfa_offset);
            }
        }
    }
  else if (fi.arg_size != 0)
    {
      if (asm_out)
        {
          asm_fprintf (f, "\tsubi\t%s, %d\n", reg_names[CSKY_SP_REGNUM],
                       fi.arg_size + fi.pad_arg);
        }
      if (length)
        {
          *length += 4;
        }
      if(dwarf2out_do_frame() && asm_out)
        {
          char *l = dwarf2out_cfi_label(false);
          cfa_offset += fi.arg_size + fi.pad_arg;
          dwarf2out_def_cfa(l, cfa_reg, cfa_offset);
        }
    }

  if (target_flags & MASK_BACKTRACE)
    {
      csky_backtrace_push_reg (fi,
                               &cfa_offset,
                               &cfa_reg,
                               length,
                               asm_out,
                               f);
    }
  else if (TARGET_PUSHPOP && can_save_regs_use_pushpop(fi.reg_mask))
    {
      int rn = 4;
      int reg_end = 31;
      int reg_count = 0;

      if (asm_out)
        {
          asm_fprintf (f, "\tpush\t");
        }
      if (length)
        {
          *length += 4;
        }
      /* Find the first regnum */
      for (; !(fi.reg_mask & (1 << rn)); rn++);
      /* Output first regname */
      if (asm_out)
        {
          asm_fprintf (f, "%s", reg_names[rn++]);
        }

      reg_count++;
      /* Output remain regs */
      for (; rn <= reg_end; rn++)
        {
          if (fi.reg_mask & (1 << rn))
            {
              if (asm_out)
                {
                  asm_fprintf (f, ", %s", reg_names[rn]);
                }
              reg_count ++;
            }
        }
      if (asm_out)
        {
          asm_fprintf (f, "\n");
        }
      if(dwarf2out_do_frame() && asm_out)
        {
          char *l = dwarf2out_cfi_label(false);
          cfa_offset += reg_count * 4;
          dwarf2out_def_cfa (l, cfa_reg, cfa_offset);
          rn = 4;
          reg_count = 0;
          for (; rn <= reg_end; rn++)
            {
              if (fi.reg_mask & (1 << rn))
                {
                  dwarf2out_reg_save (l, rn, (reg_count * 4) - cfa_offset);
                  reg_count++;
                }
            }
        }
    }
  else if (fi.reg_size > 0)
    {
      int remain = fi.reg_size;
      int rn = -1;
      int offset = 0;

      if (asm_out)
        {
          asm_fprintf (f, "\tsubi\t%s, %d\n", reg_names[CSKY_SP_REGNUM],
                       fi.reg_size + fi.pad_reg);
        }
      if (length)
        {
          *length += 4;
        }
      if(dwarf2out_do_frame() && asm_out)
        {
          char *l = dwarf2out_cfi_label(false);
          cfa_offset += fi.reg_size + fi.pad_reg;
          dwarf2out_def_cfa (l, cfa_reg, cfa_offset);
        }

      while (remain > 0)
        {
          while (!(fi.reg_mask & (1 << ++rn)));

          if (asm_out)
            {
              asm_fprintf (f, "\tst.w\t%s, (%s, %d)\n",
                           reg_names[rn], reg_names[CSKY_SP_REGNUM], offset);
            }
          if (length)
            {
              *length += 4;
            }
          if(dwarf2out_do_frame() && asm_out)
            {
              char *l = dwarf2out_cfi_label(false);
              dwarf2out_reg_save (l, rn, offset - cfa_offset);
            }

          offset += 4;
          remain -= 4;
        }
    }

  if (frame_pointer_needed)
    {
      if (asm_out)
        {
          asm_fprintf (f, "\tmov\t%s, %s\n", reg_names[8],
                       reg_names[CSKY_SP_REGNUM]);
        }
      if (length)
        {
          *length += 4;
        }
      /* FIXME: if define cfa as r8 here, the last adjust for sp cannot
         be defined, so sp cannot be restored when unwind.  */
      if(dwarf2out_do_frame() && asm_out)
        {
          cfa_reg = 8;
          char *l = dwarf2out_cfi_label (false);
          dwarf2out_def_cfa (l, cfa_reg, cfa_offset);
        }
    }
  if(fi.local_size + fi.outbound_size)
    {
      int size = fi.local_size + fi.outbound_size;
      if (size > CSKY_SUBI_MAX_STEP * 2)
        {
          if (CSKY_TARGET_ARCH(CK801))
            {
              if (asm_out)
                {
                  asm_fprintf (f, "\tlrw\t%s, 0x%x\n", reg_names[4], size);
                }
              if (length)
                {
                  *length += 4;
                }
            }
          else if(size & 0xffff0000)
            {
              if (asm_out)
                {
                  asm_fprintf (f, "\tmovih\t%s, 0x%x\n",
                               reg_names[4], size >> 16);
                }
              if (length)
                {
                  *length += 4;
                }
              if(size & 0xffff)
                {
                  if (asm_out)
                    {
                      asm_fprintf (f, "\tori\t%s, %s, 0x%x\n",
                                   reg_names[4], reg_names[4], size & 0xffff);
                    }
                  if (length)
                    {
                      *length += 4;
                    }
                }
            }
          else
            {
              if (asm_out)
                {
                  asm_fprintf (f, "\tmovi\t%s, 0x%x\n", reg_names[4], size);
                }
              if (length)
                {
                  *length += 4;
                }
            }

          if (asm_out)
            {
              asm_fprintf (f, "\tsub\t%s, %s\n",
                           reg_names[CSKY_SP_REGNUM], reg_names[4]);
            }
          if (length)
            {
              *length += 4;
            }
        }
      else if(size > CSKY_SUBI_MAX_STEP)
        {
          if (asm_out)
            {
              asm_fprintf (f, "\tsubi\t%s, %d\n",
                           reg_names[CSKY_SP_REGNUM], CSKY_SUBI_MAX_STEP);
              asm_fprintf (f, "\tsubi\t%s, %d\n",
                           reg_names[CSKY_SP_REGNUM],
                           size - CSKY_SUBI_MAX_STEP);
            }
          if (length)
            {
              *length += 8;
            }
        }
      else
        {
          if (asm_out)
            {
              asm_fprintf (f, "\tsubi\t%s, %d\n",
                           reg_names[CSKY_SP_REGNUM], size);
            }
          if (length)
            {
              *length += 4;
            }
        }
      cfa_offset += size;
      if(dwarf2out_do_frame() && !frame_pointer_needed && asm_out)
        {
          char *l = dwarf2out_cfi_label(false);
          dwarf2out_def_cfa (l, cfa_reg, cfa_offset);
        }
    }

  /* generate .stack_size function-name, size for callgraph,
   * the default stack size is 0.  */
  if ((target_flags & MASK_STACK_SIZE)
      && (space_allocated > 0)
      && asm_out )
    {
      gcc_assert (current_function_decl != NULL);
      const char * func_name =
          IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (current_function_decl));
      if (func_name[0] == '*')
        asm_fprintf (f, "\t.stack_size %s, %d\n",
                     &func_name[1], space_allocated);
      else
        asm_fprintf (f, "\t.stack_size %s, %d\n", func_name, space_allocated);
    }
#endif
}


const char *
process_csky_function_epilogue (int asm_out, HOST_WIDE_INT *length)
{
  /* FIXME it should be designed again.  */
#if 0
  struct csky_frame fi;
  int begin_reg, end_reg;
  unsigned long func_type;
  int use_pop = false;

  func_type = get_csky_current_func_type();

  if (csky_naked_function_p())
    return "";

  get_csky_frame_layout (&fi);
  if (length)
    *length = 0;

  if (target_flags & MASK_BACKTRACE)
    {
      use_pop = csky_backtrace_pop_reg (fi,
                                        length,
                                        asm_out,
                                        asm_out_file,
                                        func_type);
      if (use_pop == true)
        return "";
    }
  else if (TARGET_PUSHPOP
           && can_save_regs_use_pushpop(fi.reg_mask)
           && fi.arg_size == 0
           && (!(func_type & CSKY_FT_INTERRUPT)))
    {
      int rn = 4;
      int reg_end = 31;

      if (asm_out)
        asm_fprintf (asm_out_file, "\tpop \t");
      if (length)
        *length += 4;
      /* Find the first regnum */
      for (; !(fi.reg_mask & (1 << rn)); rn++);
      /* Output first regname */
      if (asm_out)
        asm_fprintf (asm_out_file, "%s", reg_names[rn++]);
      /* Output remain regs */
      for (; rn <= reg_end; rn++)
        {
          if (fi.reg_mask & (1 << rn) )
            {
              if (asm_out)
                asm_fprintf (asm_out_file, ", %s", reg_names[rn]);
            }
        }
      if (asm_out)
        asm_fprintf (asm_out_file, "\n");

      /* if lrpop instruction set pc = lr.  */
      return "";
    }
  else if (can_save_regs_use_stm (fi.reg_mask, &begin_reg, &end_reg))
    {
      if (frame_pointer_needed && begin_reg != CSKY_FRAME_POINTER_REGNUM)
        {
          int off = (end_reg - begin_reg + 1 ) * 4;
          if (asm_out)
            {
              asm_fprintf (asm_out_file, "ld.w\t%s, (%s, %d)\n",
                           reg_names[CSKY_FRAME_POINTER_REGNUM],
                           reg_names[CSKY_SP_REGNUM], off);
            }
          if (length)
            *length += 4;
        }
      if (asm_out)
        {
          asm_fprintf (asm_out_file, "\tldm\t%s-%s,(%s)\n",
                       reg_names[begin_reg],
                       reg_names[end_reg],
                       reg_names[CSKY_SP_REGNUM]);
          asm_fprintf (asm_out_file, "\taddi\t%s, 0x%x\n",
                       reg_names[CSKY_SP_REGNUM],
                       fi.reg_size + fi.pad_reg + fi.arg_size + fi.pad_arg);
        }
      if (length)
        *length += 8;
    }
  else
    {
      int offset = fi.reg_size + fi.pad_reg;
      int adjust = fi.arg_size + fi.pad_arg + fi.reg_size + fi.pad_reg;
      int remain = fi.reg_size;
      int rn = 31;

      if (offset > 0)
        {

          offset -= fi.pad_reg;
          offset -= 4;

          while (remain > 0)
            {
              while (!(fi.reg_mask & (1 << --rn)));

              if (asm_out)
                {
                  asm_fprintf (asm_out_file, "\tld.w\t%s, (%s, %d)\n",
                               reg_names[rn],
                               reg_names[CSKY_SP_REGNUM],
                               offset);
                }
              if (length)
                *length += 4;

              offset -= 4;
              remain -= 4;
            }
          if (asm_out)
            asm_fprintf (asm_out_file, "\taddi\t%s, 0x%x\n",
                         reg_names[CSKY_SP_REGNUM], adjust);
          if (length)
            *length += 4;
        }
      else if (adjust)
        {
          if (asm_out)
            asm_fprintf (asm_out_file, "\taddi\t%s, 0x%x\n",
                         reg_names[CSKY_SP_REGNUM], adjust);
          if (length)
            *length += 4;
        }
    }
  if(crtl->calls_eh_return)
    {
      if (asm_out)
        asm_fprintf (asm_out_file, "\taddu\t%s, %s\n",
                     reg_names[CSKY_SP_REGNUM],
                     reg_names[CSKY_EH_STACKADJ_REGNUM]);
      if (length)
        *length += 4;
    }

  if((func_type & CSKY_FT_INTERRUPT) != 0 && asm_out)
    {
      asm_fprintf(asm_out_file, "\tipop\n\tnir\n");
      if (length)
        *length += 4;
    }

  /* Out put rts */
  if (asm_out && !(func_type & CSKY_FT_INTERRUPT))
    asm_fprintf (asm_out_file, "\trts\n");
  if (length)
    *length += 4;

  return "";
#endif
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


static bool
is_csky_epilogue_insn(rtx x)
{
    if ((GET_CODE(x) == JUMP_INSN)
        && (GET_CODE(PATTERN(x)) == UNSPEC_VOLATILE)
        && (XINT(PATTERN(x), 1) == FLAG_EPILOGUE))
      return true;
    else
      return false;
}


/* Determines if INSN is the start of a jump table.  Returns the end
   of the TABLE or NULL_RTX.  */

static rtx_insn*
is_csky_jump_table (rtx_insn *insn)
{
  rtx_insn *table;

  if (GET_CODE (insn) == JUMP_INSN
      && JUMP_LABEL (insn) != NULL
      && ((table = next_real_insn (JUMP_LABEL (insn)))
      == next_real_insn (insn))
      && table != NULL
      && GET_CODE (table) == JUMP_INSN
      && (GET_CODE (PATTERN (table)) == ADDR_VEC
      || GET_CODE (PATTERN (table)) == ADDR_DIFF_VEC))
    return table;

  return NULL;
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
   needed.  The function returns TRUE if any fixups were needed/pushed.
*/

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
                         HOST_WIDE_INT min_address, HOST_WIDE_INT max_address)
{
  rtx_barrier *barrier;
  rtx_insn *from;
  if (fix)
    from = fix->insn;
  else
    from = get_insns();
  /* The instruction after which we will insert the jump.  */
  rtx selected = NULL;
  int selected_cost;
  /* The address at which the jump instruction will be placed.  */
  HOST_WIDE_INT selected_address;
  Mfix * new_fix;
  HOST_WIDE_INT count;
  if (fix)
    count = fix->address;
  else
    count = min_address;
  HOST_WIDE_INT max_count = max_address;
  rtx label = gen_label_rtx ();

  selected_cost = get_csky_barrier_cost (from);

  while (from && count < max_count)
    {
      rtx_insn *tmp;
      int new_cost;

      /* Count the length of this insn.  */
      count += get_attr_length (from);

      /* If there is a jump table, add its length.  */
      tmp = is_csky_jump_table (from);
      if (tmp != NULL)
        {
          count += get_csky_jump_table_size (tmp);

          /* Jump tables aren't in a basic block, so base the cost on
             the dispatch insn.  If we select this location, we will
             still put the pool after the table.  */
          new_cost = get_csky_barrier_cost (from);

          if (count < max_count
              && (!selected || new_cost <= selected_cost))
            {
              selected = tmp;
              selected_cost = new_cost;
              selected_address = count;
            }

          /* Continue after the dispatch table.  */
          from = NEXT_INSN (tmp);
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
    HOST_WIDE_INT address;
    HOST_WIDE_INT tmp_len, prolog_len;
    Mfix * fix;

    minipool_fix_head = minipool_fix_tail = NULL;
    process_csky_function_prologue(NULL, get_frame_size(), 0, &tmp_len);
    address = prolog_len = tmp_len;

    /* The first insn must always be a note, or the code below won't
       scan it properly.  */
    insn = get_insns ();
    gcc_assert (GET_CODE (insn) == NOTE);

    /* Scan the insns and record the operands that will need fixing.  */
    for (insn = next_nonnote_insn (insn); insn; insn = next_nonnote_insn (insn))
      {
        if (GET_CODE (insn) == BARRIER)
          push_csky_minipool_barrier (insn, address);
        else if (is_csky_epilogue_insn(insn))
          {
            process_csky_function_epilogue(0, &tmp_len);
            address += tmp_len;
          }
        else if (INSN_P (insn))
          {
            rtx_insn *table;

            note_csky_invalid_constants (insn, address, true);
            address += get_attr_length (insn);

            /* If the insn is a vector jump, add the size of the table
             and skip the table.  */
            if ((table = is_csky_jump_table (insn)) != NULL)
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
        Mfix * fdel;
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
            while (fix && (GET_CODE (fix->insn) == BARRIER))
              fix = fix->next;
            if (fix == NULL)
              break;
          }

        last_added_fix = NULL;

        for (ftmp = fix; ftmp; ftmp = ftmp->next)
          {
            if (GET_CODE (ftmp->insn) == BARRIER)
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
        if (last_added_fix && GET_CODE (last_added_fix->insn) == BARRIER)
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
                                                    prolog_len, max_address);
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

        /* if the current insn list is the last part of internal function, only
         * need to modify the address constraint; Otherwise, dump the minipool. */
        #define MAX_PROLOG_LENGTH ((4 + 8 + 1 + 4 + 1 + 4) * 4)
        if (!minipool_vector_head)
          {
          }
        else if (reach_end == true
                && minipool_vector_head->max_address <= (last_barrier->address
                                                         + MAX_PROLOG_LENGTH))
          {
            dump_csky_minipool (last_barrier->insn);
          }
        /* TODO will_change_section and is_last_func should be added to
           cgraphunit.c file. Try to find a solution don't edit gcc file.*/
#if 0
        else if (reach_end == true && will_change_section == true)
          {
            dump_csky_minipool (last_barrier->insn);
          }
        else if (reach_end == true && is_last_func == true)
          {
            dump_csky_minipool (last_barrier->insn);
          }
#endif
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

        fix = ftmp;
        if (fix->next == NULL)
          break;
      }

    /* Free the minipool memory.  */
    obstack_free (&minipool_obstack, minipool_startobj);
}


static int
get_csky_live_regs (int *count)
{
  int reg;
  int live_regs_mask = 0;
  *count = 0;

  /* FIXME: we should set live regs in one please
     and use interface of gcc to detect all readlly used regs ?  */
  if (frame_pointer_needed)
    {
      (*count)++;
      live_regs_mask |= (1 << FRAME_POINTER_REGNUM);
    }

  /* TODO for ck801 */

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
  return live_regs_mask;
}


static void
get_csky_frame_layout (csky_stack_frame *infp)
{
  int arg_size, reg_size, local_size, outbound_size;
  int pad_arg, pad_reg, pad_local, pad_outbound;
  int spill_size; /* the size of args we need to spill ourselves */
  int reg_mask, reg_count;
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

  reg_mask = get_csky_live_regs (&reg_count);
  reg_size = reg_count * 4;

  mod = reg_size % CSKY_STACK_BOUNDARY_BYTES;
  pad_reg = mod ? (CSKY_STACK_BOUNDARY_BYTES - mod) : 0;

  infp->arg_size = arg_size;
  infp->reg_size = reg_size;
  infp->reg_mask = reg_mask;
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

  if (from == ARG_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    return ap2fp_offset + fp2sp_offset;

  if (from == FRAME_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
    return fp2sp_offset;

  gcc_unreachable ();
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
  int arg_reg = *pcum;

  if (!named || mode == VOIDmode)
    return NULL_RTX;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return NULL_RTX;

  if (arg_reg < CSKY_NPARM_REGS)
    return gen_rtx_REG (mode, CSKY_FIRST_PARM_REG + arg_reg);

  return NULL_RTX;
}


static int
get_csky_arg_regs_num (enum machine_mode mode, const_tree type)
{
  int size;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return 0;

  if (type && mode == BLKmode)
    size = int_size_in_bytes (type);
  else
    size = GET_MODE_SIZE (mode);

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

  *pcum = *pcum + named * get_csky_arg_regs_num(mode, type);
}


static unsigned int
csky_function_arg_boundary (machine_mode mode, const_tree type)
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
csky_libcall_value (machine_mode mode, const_rtx libcall)
{
  return gen_rtx_REG (mode, CSKY_FIRST_RET_REG);
}


/* 1 if N is a possible register number for a function value.
   On the CSKY, only r0 can return results.  */
static bool
csky_function_value_regno_p (const unsigned int regno)
{
  return (regno == CSKY_FIRST_RET_REG);
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

  int reg = *pcum;

  if (named == 0)
    return 0;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return 0;

  /* REG is not the *hardware* register number of the register that holds
     the argument, it is the *argument* register number.  So for example,
     the first argument to a function goes in argument register 0, which
     translates (for the cskyv1) into hardware register 2.  The second
     argument goes into argument register 1, which translates into hardware
     register 3, and so on.  */
  if (reg >= CSKY_NPARM_REGS)
    return 0;

  /* If the argument fits entirely in registers, return 0.  */
  int size = get_csky_arg_regs_num (mode, type);
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
          machine_mode mode,
          tree type,
          int *pretend_size,
          int second_time ATTRIBUTE_UNUSED)
{
  CUMULATIVE_ARGS *pcum = get_cumulative_args (pcum_v);
  int reg = *pcum;

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
                      HOST_WIDE_INT vcall_offset ATTRIBUTE_UNUSED,
                      tree function)
{
  char *thiz = "a0";
  char *reg0 = "t0";
  char *reg1 = "t1";

  rtx fnaddr = XEXP (DECL_RTL (function), 0);

  /* TODO for ck801  */

  if (aggregate_value_p (TREE_TYPE (TREE_TYPE (function)), function))
    thiz = "a1";

  /* Add delta to this_rtx.  */
  if (delta != 0)
    {
      if (delta > CSKY_ADDI_MAX_STEP || delta < -CSKY_ADDI_MAX_STEP)
        {
          fprintf(file, "\tlrw\t%s, 0x%x\n", reg0, delta);
          fprintf(file, "\taddu\t%s, %s, %s\n", thiz, thiz, reg0);
        }
        else
          {
            fprintf(file, "\t%s\t%s, %s, 0x%x\n",
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
          fprintf(file, "\tlrw\t%s, 0x%x\n", reg1, vcall_offset);
          fprintf(file, "\taddu\t%s, %s, %s\n", reg0, reg0, reg1);
        }
      else
        {
          fprintf(file, "\t%s\t%s, %s, 0x%x\n",
                  (vcall_offset > 0 ? "addi" : "subi"), reg0,
                  reg0,
                  (vcall_offset > 0 ? vcall_offset : -vcall_offset));
        }

      /* Load the offset and add it to this_rtx  */
      fprintf(file, "\tld.w\t%s, (%s, 0)\n", reg0, reg0);
      fprintf(file, "\taddu\t%s, %s, %s\n", thiz, thiz, reg0);
    }

  fprintf(file, "\tjbr \t");
  output_addr_const(file, fnaddr);
  fprintf(file, "\n");
}


/* Conditionally modify five variables fixed_regs, call_used_regs, global_regs,
   reg_names, and reg_class_contents, to take into account any dependence of
   these register sets on target flags.

   On csky, ck801 has registers r0-r7,r13,r14,r15.
   ck802 & ck803s has registers r0-r15.
   Other cpu has registers r0-r31 when -mhigh-registers, otherwise it has
   only r0-r15, ck803 default close this option, others default open.  */

static void
csky_conditional_register_usage (void)
{
  /* Only use mini registers in smart mode or 801.  */
  if (TARGET_SMART || CSKY_TARGET_ARCH(CK801))
    {
      int i;

      for (i = (CSKY_LAST_MINI_REGNUM + 1); i < 32; i++)
        {
          fixed_regs[i] = 1;
          call_used_regs[i] = 1;
          call_really_used_regs[i] = 1;
        }
    }
  /* For some targets, the high regitser is not supported.
     Expect ck801 & ck802 & ck803s, other cpu use high registers
     depend on -mhigh-registers option(ck803 is default off,
     others are default on).  */
  else if (CSKY_TARGET_ARCH(CK802)
           || CSKY_TARGET_ARCH(CK803S)
           || !TARGET_HIGH_REGISTERS)
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
  if (!TARGET_DSP)
    {
      fixed_regs[CSKY_HI_REGNUM] = 1;
      call_used_regs[CSKY_HI_REGNUM] = 1;
      call_really_used_regs[CSKY_HI_REGNUM] = 1;

      fixed_regs[CSKY_LO_REGNUM] = 1;
      call_used_regs[CSKY_LO_REGNUM] = 1;
      call_really_used_regs[CSKY_LO_REGNUM] = 1;
    }

  /* The V_REGS is only suported on hard float mode.  */
  if (!TARGET_HARD_FLOAT)
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
      gcc_assert (csky_pic_register != INVALID_REGNUM);

      fixed_regs[csky_pic_register] = 1;
      call_used_regs[csky_pic_register] = 1;
      call_really_used_regs[csky_pic_register] = 0;
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
          if (TARGET_SMART || CSKY_TARGET_ARCH(CK801))
            return (regno < CSKY_LAST_MINI_REGNUM);
          else if (CSKY_TARGET_ARCH(CK802)
                   || CSKY_TARGET_ARCH(CK803S)
                   || !TARGET_HIGH_REGISTERS)
            {
              /* Without high register, r15 cannot hold two word size data.  */
              return (regno < (CSKY_SP_REGNUM - 1));
            }
          else
            return ((regno >= CSKY_LR_REGNUM)
                    && (regno < CSKY_LAST_HIGH_UNFIXED_REGNUM));
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
      if (!TARGET_DSP || mode == SFmode || mode == DFmode)
        return 0;
      else if (CSKY_NUM_REGS(mode) == 2)
        return (regno == CSKY_HI_REGNUM);
      else
        return 1;
    }
  else if ((regno >= CSKY_FIRST_VFP_REGNUM) && (regno <= CSKY_LAST_VFP_REGNUM))
      return TARGET_HARD_FLOAT;

  return 0;
}


/* We need to define this for MINI_REGS when we only use r0 - r7.
   Otherwise we can end up using r0-r4 for function arguments,and don't
   have enough left over to do doubleword arithmetic.  */

static bool
csky_class_likely_spilled_p (reg_class_t rclass)
{
  if (((TARGET_SMART || CSKY_TARGET_ARCH(CK801))
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

  if (rclass == V_REGS && !CSKY_GENERAL_REGNO_P (regno))
    return GENERAL_REGS;

  return NO_REGS;
}


/* Convert a static initializer array of feature bits to sbitmap
   representation.  */
static void
csky_initialize_isa (sbitmap isa, const enum csky_isa_feature *isa_bits)
{
  bitmap_clear (isa);
  while (*isa_bits != CSKY_ISA_FEATURE_DEFINE(none))
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
  const struct csky_processors *csky_selected_arch = NULL;
  const struct csky_processors *csky_selected_cpu = NULL;
  const struct csky_fpu_desc *csky_selected_fpu = NULL;

  bitmap_clear (target->isa);
  target->core_name = NULL;
  target->arch_name = NULL;

  if (opts_set->x_csky_arch_option)
    csky_selected_arch = &all_architectures[opts->x_csky_arch_option];

  if (opts_set->x_csky_cpu_option)
      csky_selected_cpu = &all_cores[opts->x_csky_cpu_option];

  if (csky_selected_arch)
    {
      csky_initialize_isa (target->isa, csky_selected_arch->isa_bits);

      if (csky_selected_cpu)
        {
          /* TODO  */
        }
      else
        {
          /* Pick a CPU based on the architecture.  */
          csky_selected_cpu = csky_selected_arch;
          target->arch_name = csky_selected_arch->name;
          /* Note: target->core_name is left unset in this path.  */
        }
    }
  else if (csky_selected_cpu)
    {
      target->core_name = csky_selected_cpu->name;
      csky_initialize_isa (target->isa, csky_selected_cpu->isa_bits);
    }
  else /* If the user did not specify a processor, choose one for them.  */
    {
      csky_selected_cpu = &all_cores[TARGET_CPU_DEFAULT];
      gcc_assert (csky_selected_cpu->name);

      /* TODO: TARGET_CPU_DEFAULT + options to create cpu  */

      /* Now we know the CPU, we can finally initialize the target
         structure.  */
      target->core_name = csky_selected_cpu->name;
      csky_initialize_isa (target->isa, csky_selected_cpu->isa_bits);
    }

  gcc_assert (csky_selected_cpu);

  if (opts->x_csky_fpu_index != TARGET_FPU_auto)
    {
      csky_selected_fpu = &all_fpus[opts->x_csky_fpu_index];
      sbitmap fpu_bits = sbitmap_alloc (CSKY_ISA_FEATURE_GET(max));
      csky_initialize_isa (fpu_bits, csky_selected_fpu->isa_bits);

      bitmap_and_compl (target->isa, target->isa, csky_isa_all_fpubits);
      bitmap_ior (target->isa, target->isa, fpu_bits);

      sbitmap_free(fpu_bits);
    }
  else if (target->core_name == NULL)
    /* To support this we need to be able to parse FPU feature options
       from the architecture string.  */
    sorry ("-mfpu=auto not currently supported without an explicit CPU.");

  /* Finish initializing the target structure.  */
  target->arch_pp_name = csky_selected_cpu->arch;
  target->base_arch = csky_selected_cpu->base_arch;
  target->arch_core = csky_selected_cpu->core;
}


static void
csky_option_override (void)
{
  static const enum csky_isa_feature fpu_bitlist[]
  = {CSKY_ISA_ALL_FPU, CSKY_ISA_FEATURE_GET(none)};

  csky_isa_all_fpubits = sbitmap_alloc (CSKY_ISA_FEATURE_GET(max));
  csky_initialize_isa (csky_isa_all_fpubits, fpu_bitlist);

  csky_active_target.isa = sbitmap_alloc (CSKY_ISA_FEATURE_GET(max));

  if (!global_options_set.x_csky_fpu_index)
    {
      const char *target_fpu_name;
      bool ok;
      int fpu_index;

#ifdef CSKY_FPUTYPE_DEFAULT
      target_fpu_name = CSKY_FPUTYPE_DEFAULT;
#else
      target_fpu_name = "vfpv2";
#endif

      ok = opt_enum_arg_to_value (OPT_mfpu_, target_fpu_name, &fpu_index,
                                  CL_TARGET);
      gcc_assert (ok);
      csky_fpu_index = (enum csky_fpu_type) fpu_index;
    }

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

  /* TODO: target_flags  */

  /* Initialize boolean versions of the architectural flags, for use
     in the .md file.  */

#undef  CSKY_ISA
#define CSKY_ISA(NAME, IDENT)                                             \
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
}


/* Determine if it's legal to put X into the constant pool.  This
   is not possible for the address of thread-local symbols, which
   is checked above.  */

static bool
csky_cannot_force_const_mem (machine_mode mode, rtx x)
{
  /* TODO impelent the TLS related function later.  */
#if 0
  return csky_tls_referenced_p (x);
#endif
}


/* Nonzero if the constant value X is a legitimate general operand.
   It is given that X satisfies CONSTANT_P or is a CONST_DOUBLE.  */

static bool
csky_legitimate_constant_p (machine_mode mode, rtx x)
{
  return (!csky_cannot_force_const_mem (mode, x)
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


/* Get the bits count of offset used in ld.(bhwd) instruction
   accordding to MODE.  */

static unsigned int
get_offset_bits_count (machine_mode mode)
{
  if (CSKY_TARGET_ARCH(CK801))
    {
      switch (GET_MODE_SIZE (mode))
        {
        case 1:
          return 5;
        case 2:
          return 6;
        default:
          return 7;
        }
    }
  else
    {
      switch (GET_MODE_SIZE (mode))
        {
        case 1:
          return 12;
        case 2:
          return 13;
        default:
          return 14;
        }
    }
}


/* Try machine-dependent ways of modifying an illegitimate address
   to be legitimate.  If we find one, return the new, valid address.  */

static rtx
csky_legitimize_address (rtx x, rtx orig_x, enum machine_mode mode)
{

  /* TODO impelent the TLS related function later.  */
#if 0
  if (csky_tls_symbol_p (x))
    return legitimize_tls_address (x, NULL_RTX);
#endif

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
              && offset <= (CSKY_ADDI_MAX_IMM
                           + CSKY_LD16_MAX_OFFSET (mode)))
            {
              HOST_WIDE_INT new_ld_offset = offset
                & CSKY_LD16_OFFSET_MASK (mode);

              xop0 = force_operand (plus_constant (Pmode, xop0,
                                                   offset - new_ld_offset),
                                    NULL_RTX);
              x = plus_constant (Pmode, xop0, new_ld_offset);
            }
          else if (offset < 0 && offset >= (-CSKY_SUBI_MAX_IMM))
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
ck801_legitimate_index_p (enum machine_mode mode, rtx index, int strict_p)
{
  enum rtx_code code = GET_CODE (index);

  /* When the mode size is larger than 4, we may use two ld instruction
     to get data, the index and (index+1) should be valid.  */
  if (GET_MODE_SIZE (mode) >= 8)
    return (code == CONST_INT
            && INTVAL (index) <  CSKY_LD16_MAX_OFFSET (SImode)
            && INTVAL (index) >= 0 && (INTVAL (index) & 3) == 0);

  if (code == CONST_INT
      && INTVAL (index) <= CSKY_LD16_MAX_OFFSET (mode)
      && INTVAL (index) >= 0)
    return (INTVAL (index) % GET_MODE_SIZE (mode));

  return 0;
}


static int
ck802_legitimate_index_p (enum machine_mode mode, rtx index, int strict_p)
{
  enum rtx_code code = GET_CODE (index);

  /* When the mode size is larger than 4, we may use two ld instruction
     to get data, the index and (index+1) should be valid.  */
  if (GET_MODE_SIZE (mode) >= 8)
    return (code == CONST_INT
            && INTVAL (index) < CSKY_LD32_MAX_OFFSET (SImode)
            && INTVAL (index) >= 0 && (INTVAL (index) & 3) == 0);

  if (code == CONST_INT
      && INTVAL (index) <= CSKY_LD32_MAX_OFFSET(mode)
      && INTVAL (index) >= 0)
    return (INTVAL (index) % GET_MODE_SIZE (mode));

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

  if (code == CONST_INT)
    {
      /* When the mode size is larger than 4, we may use two ld instruction
         to get data, the index and (index+1) should be valid.  */
      if (GET_MODE_SIZE (mode) >= 8)
        return (INTVAL (index) < CSKY_LD32_MAX_OFFSET (SImode)
                && INTVAL (index) >= 0 && (INTVAL (index) & 3) == 0);

      if (INTVAL (index) <= CSKY_LD32_MAX_OFFSET (SImode)
          && INTVAL (index) >= 0)
        return (INTVAL (index) % GET_MODE_SIZE (mode));
    }
  /* Allow ld.w rx, (gb, sym@got) when -fpic specially.  */
  else if (code == UNSPEC)
    {
      return (flag_pic == 1
              && (XINT (index, 1) == PIC_SYMBOL_PLT
                  || XINT (index, 1) == PIC_SYMBOL_GOT));
    }
  /* The follow index is for ldr instruction, the ldr cannot
     load dword data, so the mode size should not be larger than
     4.  */
  else if (GET_MODE_SIZE (mode) <= 4)
    {
      if (code == REG)
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

static bool
csky_legitimate_address_p (machine_mode mode, rtx addr, bool strict_p)
{
  enum rtx_code code = GET_CODE (addr);

  if (is_csky_address_register_rtx_p (addr, strict_p))
    return 1;
  /* It is a pc-relative load, may be generated for constpool.  */
  else if (GET_CODE (addr) == LABEL_REF)
    return 1;

  if (code == PLUS)
    {
      rtx xop0 = XEXP (addr, 0);
      rtx xop1 = XEXP (addr, 1);

      return ((is_csky_address_register_rtx_p (xop0, strict_p)
               && csky_legitimate_index_p (mode, xop1, strict_p))
              || (is_csky_address_register_rtx_p (xop1, strict_p)
                  && csky_legitimate_index_p (mode, xop0, strict_p)));
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

static bool
csky_decompose_address (rtx addr, struct csky_address * out)
{
  rtx base = NULL_RTX, index = NULL_RTX, disp = NULL_RTX;
  HOST_WIDE_INT scale = 1;
  rtx scale_rtx = NULL_RTX;
  int i;

  out->base = out->index = out->symbol = out->label = out->disp = NULL_RTX;
  out->scale = 0;

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

  if (GET_CODE (addr) == PLUS)
    {
      rtx addends[2], op, tmp;

      addends[0] = XEXP (addr, 0);
      addends[1] = XEXP (addr, 1);

      if (GET_CODE (addends[0]) == LABEL_REF && CONST_INT_P (addends[1]))
        {
          out->label = addends[0];
          out->disp = addends[1];
          return true;
        }

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
    }

  if (!base)
    return false;

  if (scale_rtx && !CONST_INT_P (scale_rtx))
    {
      rtx tmp = scale_rtx;
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
csky_print_operand_address (FILE * stream, machine_mode mode, rtx x)
{

  struct csky_address addr;

  csky_decompose_address (x, &addr);

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
    case 'H':
      fprintf (stream, "%d", ((INTVAL (x)) & 0xFFFF0000) >> 16);
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
               dst_fmt, value, value);
      break;
    /* Add instruction 'addi'.  */
    case IC_APPEND_ADDI:
      sprintf (buf, "%s\n\taddi\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'subi'.  */
    case IC_APPEND_SUBI:
      sprintf (buf, "%s\n\tsubi\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'addi', the last instruction is bgeni.  */
    case IC_BGENI_ADDI:
      sprintf (buf, "%s\n\taddi\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'subi', the last instruction is bgeni.  */
    case IC_BGENI_SUBI:
      sprintf (buf, "%s\n\tsubi\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'bseti'.  */
    case IC_APPEND_BSETI:
      sprintf (buf, "%s\n\tbseti\t%s, %s, %%P2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'movi'.  */
    case IC_APPEND_MOVI:
      sprintf (buf, "%s\n\tmovi\t%s, %%2\t// %ld 0x%x", load_op, dst_fmt,
               value, value);
      break;
    /* Add instruction 'bclri'.  */
    case IC_APPEND_BCLRI:
      sprintf (buf, "%s\n\tbclri\t%s, %s, %%Q2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'rotli'.  */
    case IC_APPEND_ROTLI:
      sprintf (buf, "%s\n\trotli\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'lsli'.  */
    case IC_APPEND_LSLI:
      sprintf (buf, "%s\n\tlsli\t%s, %s, %%2\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'ixh'.  */
    case IC_APPEND_IXH:
      sprintf (buf, "%s\n\tixh\t%s, %s, %s\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, dst_fmt, value, value);
      break;
    /* Add instruction 'ixw'.  */
    case IC_APPEND_IXW:
      sprintf (buf, "%s\n\tixw\t%s, %s, %s\t// %ld 0x%x", load_op,
               dst_fmt, dst_fmt, dst_fmt, value, value);
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
              return "mvc\t\t%0";
            else
              return "mov\t\t%0, %1";
        }
      /* The situation mov memory to reg.  */
      else if (GET_CODE (src) == MEM)
        {
          csky_decompose_address (XEXP (src, 0), &op1);

          if (op1.index)
            {
              switch (GET_MODE (src))
                {
                case HImode:
                  return "ldr.h\t%0, %1";
                case QImode:
                  return "ldr.b\t%0, %1";
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
            return "lrw\t\t%0, %x1\t";
        }
      else if (TARGET_ANCHOR && GET_CODE (src) == SYMBOL_REF)
        {
          if (SYMBOL_REF_FUNCTION_P (src))
            return "lrw\t\t%0, %1@BTEXT";
          else
            return "lrw\t\t%0, %1@BDATA";
        }
      else if (GET_CODE (src) == UNSPEC && XINT (src, 1) == PIC_SYMBOL_GRS)
        return "grs\t\t%0, %1";
      else
        return "lrw\t\t%0, %1";
    }
  else if (GET_CODE (dst) == MEM)
    {
      csky_decompose_address (XEXP (dst, 0), &op0);

      if (op0.index)
        {
          switch (GET_MODE (src))
            {
            case HImode:
              return "str.h\t%1, %0";
            case QImode:
              return "str.b\t%1, %0";
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

  struct csky_address op0, op1;

  if (REG_P (dst))
    {
      if (REG_P (src))
        {
          int dstreg = REGNO (dst);
          int srcreg = REGNO (src);

          return "mov\t\t%0, %1";
        }
      else if (GET_CODE (src) == MEM)
        {
          csky_decompose_address (XEXP (src, 0), &op1);

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
          HOST_WIDE_INT x, y;

          if (0 <= REGNO (dst) && REGNO (dst) <= 7)
            {
              if (CSKY_CONST_OK_FOR_N (INTVAL (src) + 1))
                return "movi\t%0, %1";
              /* Return '#' to split it.  */
              else if (CSKY_CONST_OK_FOR_T (INTVAL (src)))
                return "#";
              else if (shiftable_csky_imm8_const (INTVAL (src)))
                return "#";
              else
                return "lrw\t\t%0, %x1\t";
            }
          else
            return "lrw\t\t%0, %x1\t";
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
            return "lrw\t\t%0, %x1\t";
        }
      else if (TARGET_ANCHOR && GET_CODE (src) == SYMBOL_REF)
        {
          if (SYMBOL_REF_FUNCTION_P (src))
            return "lrw\t\t%0, %1@BTEXT";
          else
            return "lrw\t\t%0, %1@BDATA";
        }
      else
        return "lrw\t\t%0, %1";
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
              if (TARGET_BIG_ENDIAN)
                return "fmfvrh\t%0, %1\n\tfmfvrl\t%R0, %1";
              else
                return "fmfvrh\t%R0, %1\n\tfmfvrl\t%0, %1";
            }
          else if (CSKY_VREG_P (dstreg))
            {
              if (TARGET_BIG_ENDIAN)
                return "fmtvrh\t%0, %1\n\tfmtvrl\t%0, %R1";
              else
                return "fmtvrh\t%0, %R1\n\tfmtvrl\t%0, %1";
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

          csky_decompose_address (XEXP (src, 0), &op0);

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

      csky_decompose_address (XEXP (dst, 0), &op0);

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

          csky_decompose_address (XEXP (src, 0), &op0);

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

          if (0 <= REGNO (dst) && REGNO (dst) <= 7
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

      csky_decompose_address (XEXP (dst, 0), &op0);

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


struct gcc_target targetm = TARGET_INITIALIZER;
