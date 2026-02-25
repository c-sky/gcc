
(define_c_enum "unspec" [
  UNSPEC_ASM_REQUIRED_PRINTF
  UNSPEC_ASM_REQUIRED_SCANF
  UNSPEC_GET_ISRP2FP_OFFSET
])

(define_insn "csky_required_printf"
  [(unspec_volatile [(match_operand:SI 0 "" "")] UNSPEC_ASM_REQUIRED_PRINTF)]
  ""
  ".required %0"
  [(set_attr "length" "0")]
)

(define_insn "csky_required_scanf"
  [(unspec_volatile [(match_operand:SI 0 "" "")] UNSPEC_ASM_REQUIRED_SCANF)]
  ""
  ".required %0"
  [(set_attr "length" "0")]
)

(define_insn "csky_isrp2fp_offsetsi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec_volatile:SI [(const_int 0)] UNSPEC_GET_ISRP2FP_OFFSET))]
  ""
  {
    operands[1] = GEN_INT (csky_isrp2fp_offset);
    return output_csky_move(insn, operands, SImode);
  }
)
