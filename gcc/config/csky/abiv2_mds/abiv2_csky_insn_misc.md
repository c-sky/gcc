
(define_insn "nop"
  [(const_int 0)]
  ""
  "or\tr0, r0, r0"
  [(set_attr "length" "2")]
)

(define_insn "force_register_use"
  [(unspec:SI [(match_operand:SI 0 "register_operand" "")] UNSPEC_REGISTER_USE)]
  ""
  "# %0 needed"
  [(set_attr "length" "0")]
)

;;-------------------------------------------------------------
;; Special patterns for dealing with the constant pool
;;-------------------------------------------------------------

(define_insn "align_4"
  [(unspec_volatile [(const_int 0)] VUNSPEC_ALIGN)]
  ""
  "*
  assemble_align(32);
  return \"\";
  "
  [(set_attr "length" "0")]
)

(define_insn "csky_constpool_label"
  [(unspec_volatile [(match_operand 0 "" "")] VUNSPEC_POOL_LABEL)]
  ""
  "*
  {
    char tmp_label[15];
    ASM_GENERATE_INTERNAL_LABEL(tmp_label, \"LCP\", INTVAL(operands[0]));
    assemble_label(asm_out_file, tmp_label);
    return \"\";
  }"
  [(set_attr "length" "0")]
)

;;-------------------------------------------------------------
;; prologue & epilogue
;;-------------------------------------------------------------

(define_expand "prologue"
  [(clobber (const_int 0))]
  ""
  "{
    csky_expand_prologue ();
    DONE;
  }"
)

(define_expand "epilogue"
  [(simple_return)]
  ""
  "{
    /* Prevent optimaze */
    if (crtl->calls_eh_return)
      emit_insn (gen_force_register_use (gen_rtx_REG (Pmode, 2)));

    csky_expand_epilogue();
    emit_jump_insn (gen_rtx_UNSPEC_VOLATILE (VOIDmode,
                                             gen_rtvec (1, ret_rtx),
                                             FLAG_EPILOGUE));
  }"
)

(define_insn "*epilogue_insns"
  [(unspec_volatile [(return)] FLAG_EPILOGUE)]
  ""
  "*
    return csky_unexpanded_epilogue();
  "
)

/* TODO: pushpop */

;;
;; Stack allocation -- in particular, for alloca().
;; this is *not* what we use for entry into functions.
;;
;; This is how we allocate stack space.  If we are allocating a
;; constant amount of space and we know it is less than 4096
;; bytes, we need do nothing.
;;
;; If it is more than 4096 bytes, we need to probe the stack
;; periodically.
;;
;; operands[1], the distance is a POSITIVE number indicating that we
;; are allocating stack space
;;

(define_expand "allocate_stack"
  [(set (reg:SI 0)
        (plus:SI (reg:SI 0)
                 (match_operand:SI 1 "general_operand" "")))
   (set (match_operand:SI 0 "register_operand" "=r")
        (match_dup 2))]
  ""
  "{
    /* If he wants no probing, just do it for him.  */
    if (csky_stack_increment == 0)
      {
        emit_insn (gen_addsi3 (stack_pointer_rtx,
                               stack_pointer_rtx, operands[1]));
        emit_move_insn (operands[0], virtual_stack_dynamic_rtx);
        DONE;
      }

    /* For small constant growth, we unroll the code.  */
    if (GET_CODE (operands[1]) == CONST_INT
        && INTVAL (operands[1]) < 8 * CSKY_STACK_UNITS_MAXSTEP)
      {
        HOST_WIDE_INT left = INTVAL(operands[1]);

        /* If it's a long way, get close enough for a last shot.  */
        if (left >= CSKY_STACK_UNITS_MAXSTEP)
          {
            rtx tmp = gen_reg_rtx (Pmode);
            emit_insn (gen_movsi (tmp, GEN_INT (CSKY_STACK_UNITS_MAXSTEP)));

            do
            {
              rtx memref = gen_rtx_MEM (SImode, stack_pointer_rtx);
              MEM_VOLATILE_P (memref) = 1;
              emit_insn (gen_subsi3 (stack_pointer_rtx,
                                     stack_pointer_rtx,
                                     tmp));
              emit_insn (gen_movsi (memref, stack_pointer_rtx));
              left -= CSKY_STACK_UNITS_MAXSTEP;
            } while (left > CSKY_STACK_UNITS_MAXSTEP);
          }

        /* Perform the final adjustment.  */
        emit_insn (gen_addsi3 (stack_pointer_rtx,
                               stack_pointer_rtx,
                               GEN_INT (-left)));
        emit_move_insn (operands[0], virtual_stack_dynamic_rtx);
        DONE;
      }
    else
      {
        rtx out_label = 0;
        rtx loop_label = gen_label_rtx ();
        rtx step = gen_reg_rtx (Pmode);
        rtx tmp = gen_reg_rtx (Pmode);
        rtx test, memref;

        emit_insn (gen_movsi (tmp, operands[1]));
        emit_insn (gen_movsi (step, GEN_INT (CSKY_STACK_UNITS_MAXSTEP)));

        if (GET_CODE (operands[1]) != CONST_INT)
          {
            out_label = gen_label_rtx ();
            test = gen_rtx_GEU (VOIDmode, step, tmp);   /* quick out */
            emit_jump_insn (gen_cbranchsi4 (test, step, tmp, out_label));
          }

        /* Run a loop that steps it incrementally.  */
        emit_label (loop_label);

        /* Extend a step, probe, and adjust remaining count.  */
        emit_insn(gen_subsi3(stack_pointer_rtx, stack_pointer_rtx, step));
        memref = gen_rtx_MEM (SImode, stack_pointer_rtx);
        MEM_VOLATILE_P (memref) = 1;
        emit_insn(gen_movsi(memref, stack_pointer_rtx));
        emit_insn(gen_subsi3(tmp, tmp, step));

        /* Loop condition -- going back up.  */
        test = gen_rtx_LTU (VOIDmode, step, tmp);
        emit_jump_insn (gen_cbranchsi4 (test, step, tmp, loop_label));

        if (out_label)
          emit_label (out_label);

        /* Bump the residual.  */
        emit_insn (gen_subsi3 (stack_pointer_rtx, stack_pointer_rtx, tmp));
        emit_move_insn (operands[0], virtual_stack_dynamic_rtx);
        DONE;
      }
  }"
)
