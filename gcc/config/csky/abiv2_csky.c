
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


#define CSKY_ADDISP_MAX_STEP  508
#define CSKY_SUBISP_MAX_STEP  508

#define CSKY_ADDI_MAX_STEP    ((TARGET_CK801) ? (CSKY_ADDISP_MAX_STEP) : 4096)
#define CSKY_SUBI_MAX_STEP    ((TARGET_CK801) ? (CSKY_SUBISP_MAX_STEP) : 4096)


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

  memset(infp, 0, sizeof(*infp));

  spill_size = 0;
  if (cfun->machine->uses_anonymous_args && crtl->args.pretend_args_size == 0)
    spill_size = (CSKY_NPARM_REGS
                  - cfun->machine->number_of_regs_before_varargs)
                 * UNITS_PER_WORD;

  arg_size = spill_size ? spill_size : crtl->args.pretend_args_size;
  pad_arg = (arg_size % CSKY_STACK_BOUNDARY_BYTES)
            ? (CSKY_STACK_BOUNDARY_BYTES
               - (arg_size % CSKY_STACK_BOUNDARY_BYTES))
            : 0;

  local_size = get_frame_size();
  pad_local = (local_size % CSKY_STACK_BOUNDARY_BYTES)
              ? (CSKY_STACK_BOUNDARY_BYTES
                 - (local_size % CSKY_STACK_BOUNDARY_BYTES))
              : 0;

  outbound_size = crtl->outgoing_args_size;
  pad_outbound = (outbound_size % CSKY_STACK_BOUNDARY_BYTES)
                 ? (CSKY_STACK_BOUNDARY_BYTES
                    - (outbound_size % CSKY_STACK_BOUNDARY_BYTES))
                 : 0;

  if ((local_size + pad_local + outbound_size + pad_outbound)
      > (CSKY_ADDI_MAX_STEP * 2))
    df_set_regs_ever_live(4, true); /* need r4 as tmp reg for adjust sp */

  reg_mask = get_csky_live_regs (&reg_count);
  reg_size = reg_count * 4;

  pad_reg = (reg_size % CSKY_STACK_BOUNDARY_BYTES)
            ? (CSKY_STACK_BOUNDARY_BYTES
               - (reg_size % CSKY_STACK_BOUNDARY_BYTES))
            : 0;

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
    return NULL_rtx;

  if (targetm.calls.must_pass_in_stack (mode, type))
    return NULL_rtx;

  if (arg_reg < CSKY_NPARM_REGS)
    return gen_rtx_REG (mode, CSKY_FIRST_PARM_REG + arg_reg);

  return NULL_rtx;
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
