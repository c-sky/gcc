(define_insn "ssaddsq3"
  [(set (match_operand:SQ              0 "register_operand" "=r")
        (ss_plus:SQ  (match_operand:SQ 1 "register_operand" "%r")
                     (match_operand:SQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "add.s32.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "usaddusq3"
  [(set (match_operand:USQ               0 "register_operand" "=r")
        (us_plus:USQ  (match_operand:USQ 1 "register_operand" "%r")
                      (match_operand:USQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "add.u32.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ssadddq3"
  [(set (match_operand:DQ              0 "register_operand" "=r")
        (ss_plus:DQ  (match_operand:DQ 1 "register_operand" "%r")
                     (match_operand:DQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "add.s64.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "usaddudq3"
  [(set (match_operand:UDQ               0 "register_operand" "=r")
        (us_plus:UDQ  (match_operand:UDQ 1 "register_operand" "%r")
                      (match_operand:UDQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "add.u64.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sssubsq3"
  [(set (match_operand:SQ              0 "register_operand" "=r")
        (ss_minus:SQ  (match_operand:SQ 1 "register_operand" "%r")
                     (match_operand:SQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "sub.s32.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ussubusq3"
  [(set (match_operand:USQ               0 "register_operand" "=r")
        (us_minus:USQ  (match_operand:USQ 1 "register_operand" "%r")
                      (match_operand:USQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "sub.u32.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sssubdq3"
  [(set (match_operand:DQ              0 "register_operand" "=r")
        (ss_minus:DQ  (match_operand:DQ 1 "register_operand" "%r")
                     (match_operand:DQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "sub.s64.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ussubudq3"
  [(set (match_operand:UDQ               0 "register_operand" "=r")
        (us_minus:UDQ  (match_operand:UDQ 1 "register_operand" "%r")
                      (match_operand:UDQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "sub.u64.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ssabssq2"
  [(set (match_operand:SQ 0 "register_operand" "=r")
        (ss_abs:SQ (match_operand:SQ 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "abs.s32.s\t%0, %1"
)

(define_insn "ssnegsq2"
  [(set (match_operand:SQ 0 "register_operand" "=r")
        (ss_neg:SQ (match_operand:SQ 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "neg.s32.s\t%0, %1"
)

(define_expand "csky_ssabssq"
  [(match_operand:SQ 0 "register_operand" "")
   (match_operand:SQ 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_ssabssq2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_ssnegsq"
  [(match_operand:SQ 0 "register_operand" "")
   (match_operand:SQ 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_ssnegsq2 (operands[0], operands[1]));
    DONE;
  }
)