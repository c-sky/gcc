
(define_insn "tls_do_add_pc"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (const_int 8)
                    (match_operand    2 "" "")]
                   UNSPEC_TLS_BASE))
   (clobber (match_scratch:SI         3 "=&r"))]
  "CSKY_ISA_FEATURE(tls)"
  "*
    output_asm_insn(\"grs\t%3, .LTLS%2\", operands);
    output_asm_insn(\"addu\t%0, %1, %3\", operands);
    return \"\";
  "
  [(set_attr "length" "8")]
)

(define_insn "*tls_get_symbol_1"
  [(set (match_operand:SI                      0 "register_operand" "=r")
        (unspec:SI [(match_operand             1 "" "")
                    (match_operand             2 "" "")
                    (unspec:SI [(match_operand 3 "" "")] UNSPEC_TLS_LABEL)]
                   UNSPEC_TLS))]
  "CSKY_ISA_FEATURE(tls)"
  "*
    default_internal_label (asm_out_file, \"LTLS\", INTVAL (operands[3]));
    switch (INTVAL (operands[2]))
      {
      case TLS_GD32:
        return \"lrw\t%0, %1@TLSGD32\";
      case TLS_LDM32:
        return \"lrw\t%0, %1@TLSLDM32\";
      case TLS_IE32:
        return \"lrw\t%0, %1@GOTTPOFF\";
      default:
        return \"\";
      }
  "
)

(define_insn "*tls_get_symbol_2"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (unspec:SI [(match_operand 1 "" "")
                    (match_operand 2 "" "")]
                   UNSPEC_TLS))]
  "CSKY_ISA_FEATURE(tls)"
  "*
    switch (INTVAL (operands[2]))
      {
      case TLS_LE32:
        return \"lrw\t%0, %1@TPOFF\";
      case TLS_LDO32:
        return \"lrw\t%0, %1@TLSLDO32\";
      default:
        return \"\";
      }
  "
)

(define_insn "load_tp_hard"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(const_int 0)] UNSPEC_TLS))]
  "CSKY_ISA_FEATURE(tls) && TARGET_HARD_TP"
  "mov\t%0, r31"
)

;; Do not clobber r1-r3, must use r0 for the first operand.
(define_insn "load_tp_soft"
  [(set     (reg:SI 0) (unspec:SI [(const_int 0)] UNSPEC_TLS))
   (clobber (reg:SI 15))
   (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(tls) && TARGET_SOFT_TP"
  "jbsr\t__read_tp"
)
