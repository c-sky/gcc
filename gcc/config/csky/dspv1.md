;;--------------------------------------------------
;;          DSP instruction
;;--------------------------------------------------

;;--------- sign si -> di  mode ---------
;;---
;; (s)HILO[63:0] <- (s)Rx[31:0] * (s)RY[31:0] ck800 & ck610 is same
;;---

(define_insn "mulsidi3"
 [(set (match_operand:DI 0 "register_operand" "=y")
       (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
 "TARGET_DSP"
 "muls\t%1, %2"

)

;;--------- unsign si -> di  mode ---------
;;---
;; (u)HILO[63:0] <- (u)Rx[31:0] * (u)RY[31:0]
;;---
(define_expand "umulsidi3"
 [(set (match_operand:DI 0 "register_operand" "=y")
       (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
 "TARGET_DSP || TARGET_SECURITY"
 "
 {
  if(TARGET_SECURITY)
  {
    emit_insn (gen_csky_security_umulsidi3(operands[0],
              operands[1], operands[2]));
    DONE;
  }
 }
 "
 )

(define_insn "*umulsidi3"
 [(set (match_operand:DI 0 "register_operand" "=y")
       (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
 "TARGET_DSP"
 "mulu\t%1, %2"

)

(define_insn "csky_security_umulsidi3"
 [(set (match_operand:DI 0 "register_operand" "=y")
       (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))
  (clobber (match_scratch:SI 3 "=r"))]
 "TARGET_SECURITY"
 "movi\t%3, 0\;mthi\t%3\;mtlo\t%3\;mac\t%1, %2"
)

;;---
;; (s)HILO[63:0] <- (s)HILO[63:0] + ((s)Rx[31:0] * (s)RY[31:0])
;;---
(define_insn "maddsidi4"
 [(set (match_operand:DI 0 "register_operand" "=y")
       (plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                         (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))
                (match_operand:DI 3 "register_operand" "0")))]
 "TARGET_DSP"
 "mulsa\t%1, %2"

)

;;---
;; (u)HILO[63:0] <- (u)HILO[63:0] + ((u)Rx[31:0] * (u)RY[31:0])
;;---
(define_insn "*umaddsidi4"
 [(set (match_operand:DI 0 "register_operand" "=y")
       (plus:DI (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                         (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))
                (match_operand:DI 3 "register_operand" "0")))]
 "TARGET_DSP || TARGET_SECURITY"
 "*
 {
  if (TARGET_SECURITY)
    return \"mac\t%1, %2\";
  else
    return \"mulua\t%1, %2\";
 }")

;;---
;; (s)HILO[63:0] <- (s)HILO[63:0] - ((s)Rx[31:0] * (s)RY[31:0])
;;---
(define_insn "msubsidi4"
 [(set (match_operand:DI 0 "register_operand" "=y")
       (minus:DI (match_operand:DI 3 "register_operand" "0")
                 (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))))]
 "TARGET_DSP"
 "mulss\t%1, %2")


;;---
;; (u)HILO[63:0] <- (u)HILO[63:0] - ((u)Rx[31:0] * (u)RY[31:0])
;;---
(define_insn "umsubsidi4"
 [(set (match_operand:DI 0 "register_operand" "=y")
       (minus:DI (match_operand:DI 3 "register_operand" "0")
                 (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))))]
 "TARGET_DSP"
 "mulus\t%1, %2")

;;---
;; (s)LO[31:0] <- (s)LO[31:0] + (s)RX[15:0] * (s)RY[15:0]
;;---
(define_expand "maddhisi4"
 [(set (match_operand:SI 0 "register_operand" "")
       (plus:SI (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" ""))
                         (sign_extend:SI (match_operand:HI 2 "register_operand" "")))
                (match_operand:SI 3 "register_operand" "")))]
 "TARGET_DSP"
 ""
)

(define_insn "*maddhisi4_big"
 [(set (match_operand:SI 0 "register_operand" "=l")
       (plus:SI (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
                         (sign_extend:SI (match_operand:HI 2 "register_operand" "r")))
                (match_operand:SI 3 "register_operand" "0")))]
 "TARGET_DSP && !TARGET_LITTLE_ENDIAN"
 "mulsha\t%1, %2"
)

  ;;---
  ;; HI LO have exchanged their places to keep their order of DImode as same
  ;; as general registers in little endian. so we must change this insn to
  ;; tell gcc we use the HI register in "mulsha" in little endian.
  ;;---
(define_insn "*maddhisi4_little"
 [(set (match_operand:SI 0 "register_operand" "=h")
       (plus:SI (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
                         (sign_extend:SI (match_operand:HI 2 "register_operand" "r")))
                (match_operand:SI 3 "register_operand" "0")))]
 "TARGET_DSP && TARGET_LITTLE_ENDIAN"
 "mulsha\t%1, %2"
)

;;---
;; (s)LO[31:0] <- (s)LO[31:0] - (s)Rx[15:0] * (s)RY[15:0]
;;---
(define_expand "msubhisi4"
 [(set (match_operand:SI 0 "register_operand" "")
       (minus:SI (match_operand:SI 3 "register_operand" "")
                 (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" ""))
                 (sign_extend:SI (match_operand:HI 2 "register_operand" "")))))]
 "TARGET_DSP"
 "")


(define_insn "*msubhisi4_big"
 [(set (match_operand:SI 0 "register_operand" "=l")
       (minus:SI (match_operand:SI 3 "register_operand" "0")
                 (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
                 (sign_extend:SI (match_operand:HI 2 "register_operand" "r")))))]
 "TARGET_DSP && !TARGET_LITTLE_ENDIAN"
 "mulshs\t%1, %2")

  ;;---
  ;; HI LO have exchanged their places to keep their order of DImode as same
  ;; as general registers in little endian. so we must change this insn to
  ;; tell gcc we use the HI register in "mulsha" in little endian.
  ;;---
(define_insn "*msubhisi4_little"
 [(set (match_operand:SI 0 "register_operand" "=h")
       (minus:SI (match_operand:SI 3 "register_operand" "0")
                 (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "r"))
                          (sign_extend:SI (match_operand:HI 2 "register_operand" "r")))))]
 "TARGET_DSP && TARGET_LITTLE_ENDIAN"
 "mulshs\t%1, %2")

