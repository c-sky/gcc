
;; Shift instructions.

(define_expand "ashlsi3"
  [(set (match_operand:SI            0 "register_operand"     "")
        (ashift:SI (match_operand:SI 1 "register_operand"     "")
                   (match_operand:SI 2 "csky_arith_K_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_ashlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=r,r")
        (ashift:SI (match_operand:SI 1 "register_operand"     "r,r")
                   (match_operand:SI 2 "csky_arith_K_operand" "r,Ui")))]
  "!TARGET_CK801"
  "@
  lsl  %0, %1, %2
  lsli %0, %1, %2"
)

(define_insn "ck801_ashlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=a,r")
        (ashift:SI (match_operand:SI 1 "register_operand"     "a,0")
                   (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "TARGET_CK801"
  "@
  lsli %0, %1, %2
  lsl  %0, %1, %2"
)
