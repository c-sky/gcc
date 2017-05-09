
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

(define_insn "consttable_4"
  [(unspec_volatile [(match_operand 0 "" "")] VUNSPEC_POOL_4)]
  ""
  "*
  assemble_integer(operands[0], 4, BITS_PER_WORD, 1);
  mark_symbol_refs_as_used(operands[0]);
  return \"\";
  "
  [(set_attr "length" "4")]
)

;;FIXME record the deferred symbol_ref information with use insn
(define_insn "*cskyv2_use_symbol_ref"
 [(unspec_volatile [(match_operand 0 "" "")] VUNSPEC_SYMBOL_REF)]
 ""
 ""
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
;; Push multiple registers to the stack.  Registers are in parallel (use ...)
;; expressions.  For simplicity, the first register is also in the unspec
;; part.
;; To avoid the usage of GNU extension, the length attribute is computed
;; in a C function arm_attr_length_push_multi.
(define_insn "*push_multi"
  [(match_parallel 2 "registers_pushpop"
    [(set (match_operand:BLK 0 "push_memory_operand" "")
          (unspec:BLK [(match_operand:SI 1 "register_operand" "")]
            UNSPEC_PUSHPOP_MULT))])]
  ""
  "*
  {
    int num_saves = XVECLEN (operands[2], 0);

    int i;
    char pattern[100];

    strcpy (pattern, \"push\\t%1\");

    for (i = 1; i < num_saves; i++)
      {
        strcat (pattern, \", \");
        strcat (pattern,
            reg_names[REGNO (XEXP (XVECEXP (operands[2], 0, i), 0))]);
      }

    output_asm_insn (pattern, operands);

    return \"\";
  }"
  [(set (attr "length")
        (symbol_ref "get_csky_pushpop_length (operands)"))]
)

;; Pop (as used in epilogue RTL)
;;
(define_insn "*pop_multi"
  [(match_parallel 2 "registers_pushpop"
    [(set (match_operand:SI 1 "register_operand" "")
          (unspec:SI [(match_operand:SI 0 "pop_memory_operand" "")]
            UNSPEC_PUSHPOP_MULT))])]
  ""
  "*
  {
    int num_saves = XVECLEN (operands[2], 0);

    int i;
    char pattern[100];

    strcpy (pattern, \"pop\\t%1\");

    for (i = 1; i < num_saves; i++)
      {
        strcat (pattern, \", \");
        strcat (pattern,
            reg_names[REGNO (XEXP (XVECEXP (operands[2], 0, i), 0))]);
      }

    output_asm_insn (pattern, operands);

    return \"\";
  }"
  [(set (attr "length")
        (symbol_ref "get_csky_pushpop_length (operands)"))]
)

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

(define_insn "trap"
  [(trap_if (const_int 1) (const_int 0))]
  ""
  "bkpt"
  [(set (attr "length") (const_int 2))]
)

;;------------------------------------------------------------
;; switch case optimize
;;------------------------------------------------------------

(define_expand "casesi"
  [(match_operand:SI 0 "register_operand" "")   ; index to jump on
   (match_operand:SI 1 "const_int_operand" "")  ; lower bound
   (match_operand:SI 2 "const_int_operand" "")  ; total range        (max - min)
   (match_operand:SI 3 "" "")                   ; table label
   (match_operand:SI 4 "" "")]                  ; Out of range label (default:)
  "CSKY_ISA_FEATURE(casesi)"
  "{
    enum insn_code code;
    if (operands[1] != const0_rtx)
      {
        rtx reg = gen_reg_rtx (SImode);
        emit_insn (gen_subsi3 (reg,
                               operands[0],
                               GEN_INT (INTVAL (operands[1]))));
        operands[0] = reg;
      }

    code = CODE_FOR_csky_casesi_internal;

    if (!insn_data[(int) code].operand[1].predicate(operands[2], SImode))
      operands[2] = force_reg (SImode,operands[2]);

    emit_jump_insn (GEN_FCN ((int) code) (operands[0],operands[2],
                    operands[3],operands[4]));
    DONE;
  }"
)

(define_expand "csky_casesi_internal"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "csky_literal_Uk_operand" "")
   (match_operand    2 "" "")
   (match_operand    3 "" "")]
  ""
  {
    rtx reg0;
    rtx test = gen_rtx_GTU(VOIDmode, operands[0], operands[1]);
    emit_jump_insn (gen_cbranchsi4 (test,operands[0],operands[1], operands[3]));
    reg0 = gen_rtx_REG (SImode, 0);
    emit_move_insn (reg0, operands[0]);
    emit_jump_insn (gen_csky_casesi_dispatch (operands[2]/*, operands[3]*/));
    DONE;
  }
)

(define_insn "csky_casesi_dispatch"
  [(parallel [(set (pc) (unspec [(reg:SI 0) (label_ref (match_operand 0 "" ""))
;;                                          (label_ref (match_operand 1 "" ""))
                                ]
                                UNSPEC_CSKY_CASESI))
              (clobber (reg:SI 15))])]
  ""
  "*return csky_output_casesi(operands);"
  [(set_attr "length" "4")]
)
