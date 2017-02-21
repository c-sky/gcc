
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

/* TODO: pic */
