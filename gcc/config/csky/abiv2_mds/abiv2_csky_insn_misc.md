
(define_insn "nop"
  [(const_int 0)]
  ""
  "or\tr0, r0, r0"
  [(set_attr "length" "2")]
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
