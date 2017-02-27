
(define_insn "mulsidi3"
  [(set (match_operand:DI                          0 "register_operand" "=y")
        (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(dsp)"
  "muls\t%1, %2"
)

(define_insn "umulsidi3"
  [(set (match_operand:DI                          0 "register_operand" "=y")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulu\t%1, %2"
)

(define_insn "maddsidi4"
  [(set (match_operand:DI                                   0 "register_operand" "=y")
        (plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))
                 (match_operand:DI                          3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulsa\t%1, %2"
)

(define_insn "umaddsidi4"
  [(set (match_operand:DI                                   0 "register_operand" "=y")
        (plus:DI (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))
                 (match_operand:DI                          3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulua\t%1, %2"
)

(define_insn "msubsidi4"
  [(set (match_operand:DI                                    0 "register_operand" "=y")
        (minus:DI (match_operand:DI                          3 "register_operand" "0")
                  (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                           (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulss\t%1, %2"
)

(define_insn "umsubsidi4"
  [(set (match_operand:DI                                    0 "register_operand" "=y")
        (minus:DI (match_operand:DI                          3 "register_operand" "0")
                  (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                           (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulus\t%1, %2"
)
