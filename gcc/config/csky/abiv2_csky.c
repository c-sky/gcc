
#include "abiv2_csky_internal.h"


/* Array of the smallest class containing reg number REGNO, indexed by
   REGNO.  Used by REGNO_REG_CLASS.  */
enum reg_class regno_reg_class[FIRST_PSEUDO_REGISTER] =
{
  /* Registers r0-r7.  */
  MINI_REGS,     MINI_REGS,     MINI_REGS,     MINI_REGS,
  MINI_REGS,     MINI_REGS,     MINI_REGS,     MINI_REGS,
  /* Registers r8-r13.  */
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS,
  /* SP register.  */
  SP_REGS,
  /* Registers r15-r31.  */
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS,
  GENERAL_REGS,
  /* Reserved.  */
  RESERVE_REGS,
  /* CC,HI,LO registers.  */
  C_REGS,      HI_REGS,      LO_REGS,
  /* Reserved.  */
  RESERVE_GRES, RESERVE_GEGS, RESERVE_REGS, RESERVE_REGS,
  RESERVE_GRES, RESERVE_GEGS, RESERVE_REGS, RESERVE_REGS,
  RESERVE_GRES, RESERVE_GEGS, RESERVE_REGS, RESERVE_REGS,
  RESERVE_GRES, RESERVE_GEGS, RESERVE_REGS, RESERVE_REGS,
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

/* The following are used in the .md file as equivalents to bits
   in the above two flag variables.  */

/* Nonzero if this chip supports the CSKY Architecture base instructions.  */
int csky_arch_base = 0;


#define CSKY_ADDISP_MAX_STEP  508
#define CSKY_SUBISP_MAX_STEP  508

#define CSKY_ADDI_MAX_STEP    ((TARGET_CK801) ? (CSKY_ADDISP_MAX_STEP) : 4096)
#define CSKY_SUBI_MAX_STEP    ((TARGET_CK801) ? (CSKY_SUBISP_MAX_STEP) : 4096)


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
  return gen_rtx_REG (mode, CSKY_FIRST_RET_REG)
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

  return get_hard_reg_initial_val (Pmode, LR_REGNUM);
}


/* return the number of bytes at the beginning of an argument
   that must be put in registers. The value must be zero for arguments
   that are passed entirely in registers or
   that are entirely pushed on the stack.  */
static int
csky_arg_partial_bytes (CUMULATIVE_ARGS *pcum, enum machine_mode mode,
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

   On csky, ck801 has registers r0-r8,r13,r14,r15.
   ck802 & ck803s has registers r0-r15.
   Other cpu has registers r0-r31 when -mhigh-registers, otherwise it has
   only r0-r15, ck803 default close this option, others default open.  */

static void
csky_conditional_register_usage (void)
{
  /* Only use mini registers in smart mode or 801.  */
  if (TARGET_SMART || TARGET_CK801)
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
  else if (TARGET_CK802 || TARGET_CK803S || !TARGET_HIGH_REGISTER)
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
  if (!TARGET_FPUV2 || !TARGET_HARD_FLOAT )
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
  if (TARGET_PIC)
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
          if (TARGET_SMART || TARGET_CK801)
            return (regno < CSKY_LAST_MINI_REGNUM);
          else if (TARGET_CK802 || TARGET_CK803S || !TARGET_HIGH_REGISTERS)
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
  if (((TARGET_SMART || TARGET_CK801)
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
enum reg_class
csky_secondary_reload (bool in_p ATTRIBUTE_UNUSED, rtx x,
                       enum reg_class rclass,
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
      && !GENERAL_REGNO_P (regno))
    return GENERAL_REGS;

  if (rclass == V_REGS && !GENERAL_REGNO_P (regno))
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
  const struct processors *csky_selected_arch = NULL;
  const struct processors *csky_selected_cpu = NULL;
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
      auto_sbitmap fpu_bits (CSKY_ISA_FEATURE_GET(max));

      csky_initialize_isa (fpu_bits, csky_selected_fpu->isa_bits);
      bitmap_and_compl (target->isa, target->isa, csky_isa_all_fpubits);
      bitmap_ior (target->isa, target->isa, fpu_bits);
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
      csky_fpu_index = (enum fpu_type) fpu_index;
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

  /* TODO: target_flags  */

  /* Initialize boolean versions of the architectural flags, for use
     in the .md file.  */
  csky_arch_base = bitmap_bit_p (csky_active_target.isa,
                                 CSKY_ISA_FEATURE_GET(base));

  /* TODO  */

/* Resynchronize the saved target options.  */
  cl_target_option_save (TREE_TARGET_OPTION (target_option_default_node),
                         &global_options);
}


/* Determine if it's legal to put X into the constant pool.  This
   is not possible for the address of thread-local symbols, which
   is checked above.  */

static bool
csky_cannot_force_const_mem (rtx x)
{
  /* TODO impelent the TLS related function later.  */
  return csky_tls_referenced_p (x);
}


/* Nonzero if the constant value X is a legitimate general operand.
   It is given that X satisfies CONSTANT_P or is a CONST_DOUBLE.  */

static bool
csky_legitimate_constant_p (machine_mode mode, rtx x)
{
  return (!csky_cannot_force_const_mem (x)
          && CONSTANT_P (x))
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
  if (TARGET_CK801)
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
  if (csky_tls_symbol_p (x))
    return legitimize_tls_address (x, NULL_RTX);

  if (GET_CODE (x) == PLUS)
    {
      rtx xop0 = XEXP (x, 0);
      rtx xop1 = XEXP (x, 1);

      if (is_csky_address_register_rtx_p (xop0, 0)
          && CONST_INT_P (xop1))
        {
          HOST_WIDE_INT offset = INTVAL (op1);

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

              op0 = force_operand (plus_constant (op0, offset - new_ld_offset),
                                   NULL_RTX);
              x = plus_constant (op0, new_ld_offset);
            }
          else if (offset < 0 && offset >= (-CSKY_SUBI_MAX_IMM))
            x = force_operand (x, NULL_RTX);
          else if (offset > CSKY_LD16_MAX_OFFSET (mode)
                   || offset < 0)
            {
              /* For the remaining cases, force the constant into a register.  */
              op1 = force_reg (SImode, op1);
              x = gen_rtx_PLUS (SImode, op0, op1);
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
      x = plus_constant (base_reg, index);
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
              && (XINT (addr.disp, 1) == PIC_SYMBOL_PLT
                  || XINT (addr.disp, 1) == PIC_SYMBOL_GOT))
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
          rtx xiop0 = XEXP (x, 0);
          rtx xiop1 = XEXP (x, 1);

          /* FIXME can the xiop1 be the reg and xiop0 be the int when mult?  */
          return (is_csky_address_register_rtx_p (xiop0, strict_p)
                  && CONST_INT_P (xiop1)
                  && is_ldr_shift_p (INTVAL (xiop1), code));
        }
    }

  return 0;
}


static int
csky_legitimate_index_p (machine_mode mode, rtx index, RTX_CODE outer,
                        int strict_p)
{
  if (TARGET_CK801)
    return ck801_legitimate_index_p (mode, index, outer, strict_p);
  else if (TARGET_CK802)
    return ck802_legitimate_index_p (mode, index, outer, strict_p);
  else
    return ck810_legitimate_index_p (mode, index, outer, strict_p);
}


/* Recognizes RTL expressions that are valid memory addresses for an
   instruction.  The MODE argument is the machine mode for the MEM
   expression that wants to use this address.

   It only recognizes address in canonical form.  LEGITIMIZE_ADDRESS should
   convert common non-canonical forms to canonical form so that they will
   be recognized.  */

static bool
csky_legitimate_address_p (machine_mode, rtx addr, bool strict)
{
  enum rtx_code code = GET_CODE (x);

  if (is_csky_address_register_rtx_p (x, strict_p))
    return 1;

  if (code == PLUS)
    {
      rtx xop0 = XEXP (x, 0);
      rtx xop1 = XEXP (x, 1);

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

static int
csky_note_pic_base (rtx * x, void *date ATTRIBUTE_UNUSED)
{
  if (GET_CODE (*x) == UNSPEC
      && ((XINT (*x, 1) == UNSPEC_TLS_LABEL) ||
          (XINT (*x, 1) == PIC_SYMBOL_GOTPC_GRS)))
    return 1;
  return 0;
}


static bool
csky_cannot_copy_insn_p (rtx insn)
{
  return for_each_rtx (&PATTERN (insn), csky_note_pic_base, NULL);
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
csky_print_operand_address (FILE * stream, rtx x)
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
            (stream, XEXP (adjust_address (x, SImode, 4), 0));
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
          output_address (XEXP (x, 0));
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

