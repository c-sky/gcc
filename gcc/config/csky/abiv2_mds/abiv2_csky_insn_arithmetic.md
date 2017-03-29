
(define_insn "abssi2"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (abs:SI (match_operand:SI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(2E3)"
  "abs\t%0, %1"
)

(define_insn "extv"
  [(set (match_operand:SI                  0 "register_operand" "=r")
        (sign_extract:SI (match_operand:SI 1 "register_operand" "r")
                         (match_operand:SI 2 "const_int_operand" "")
                         (match_operand:SI 3 "const_int_operand" "")))]
  "CSKY_ISA_FEATURE(2E3)"
  "*{
    operands[2] = GEN_INT(INTVAL(operands[3]) + INTVAL(operands[2]) - 1);
    return \"sext\t%0, %1, %2, %3\";
  }"
)

(define_insn "insv"
  [(set (zero_extract:SI (match_operand:SI 0 "register_operand"  "+r")
                         (match_operand:SI 1 "const_int_operand" "i")
                         (match_operand:SI 2 "const_int_operand" "i"))
        (match_operand:SI                  3 "register_operand"  "r"))]
  "CSKY_ISA_FEATURE(2E3)"
  "*{
    operands[1] = GEN_INT (INTVAL (operands[2]) + INTVAL (operands[1]) - 1);
    return \"ins\t%0, %3, %1, %2\";
  }"
)

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
  "CSKY_ISA_FEATURE(E2)"
  "@
  lsl  %0, %1, %2
  lsli %0, %1, %2"
)

(define_insn "ck801_ashlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=a,r")
        (ashift:SI (match_operand:SI 1 "register_operand"     "a,0")
                   (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE(E1)"
  "@
  lsli %0, %1, %2
  lsl  %0, %1, %2"
)


(define_expand "ashrsi3"
  [(set (match_operand:SI              0 "register_operand"     "")
        (ashiftrt:SI (match_operand:SI 1 "register_operand"     "")
                     (match_operand:SI 2 "csky_arith_K_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_ashrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=r,r")
        (ashiftrt:SI (match_operand:SI 1 "register_operand"     "r,r")
                     (match_operand:SI 2 "csky_arith_K_operand" "r,Ui")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
  asr  %0, %1, %2
  asri %0, %1, %2"
)

(define_insn "*ck801_ashrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=a,r")
        (ashiftrt:SI (match_operand:SI 1 "register_operand"     "a,0")
                     (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE(E1)"
  "@
  asri %0, %1, %2
  asr  %0, %1, %2"
)


(define_expand "lshrsi3"
  [(set (match_operand:SI              0 "register_operand"     "")
        (lshiftrt:SI (match_operand:SI 1 "register_operand"     "")
                     (match_operand:SI 2 "csky_arith_K_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_lshrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=r,r")
        (lshiftrt:SI (match_operand:SI 1 "register_operand"     "r,r")
                     (match_operand:SI 2 "csky_arith_K_operand" "r,Ui")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
  lsr  %0, %1, %2
  lsri %0, %1, %2"
)

(define_insn "ck801_lshrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=a,r")
        (lshiftrt:SI (match_operand:SI 1 "register_operand"     "a,0")
                     (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE(E1)"
  "@
  lsri %0, %1, %2
  lsr  %0, %1, %2"
)


(define_expand "rotlsi3"
  [(set (match_operand:SI            0 "register_operand"     "")
        (rotate:SI (match_operand:SI 1 "register_operand"     "")
                   (match_operand:SI 2 "csky_arith_K_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_rotlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=r,r")
        (rotate:SI (match_operand:SI 1 "register_operand"     "r,r")
                   (match_operand:SI 2 "csky_arith_K_operand" "r,Ui")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
  rotl  %0, %1, %2
  rotli %0, %1, %2"
)

(define_insn "*ck801_rotlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=r")
        (rotate:SI (match_operand:SI 1 "register_operand"     "0")
                   (match_operand:SI 2 "csky_arith_K_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "rotl %0, %1, %2"
)


;; Add instructions.
;; FIXME there is no need to consider subtraction instructions
;; in addition, neither to consider addition instructions in
;; subtraction.

(define_expand "addsi3"
  [(set (match_operand:SI          0 "register_operand" "")
        (plus:SI (match_operand:SI 1 "register_operand" "")
                 (match_operand:SI 2 "nonmemory_operand" "")))]
  ""
  ""
)

(define_insn "*smart_addsi3"
 [(set (match_operand:SI          0 "register_operand"  "=a,r,a,a,a,a, a, r,r")
       (plus:SI (match_operand:SI 1 "register_operand"  "%a,0,0,a,0,a, a, r,r")
                (match_operand:SI 2 "nonmemory_operand" "a, r,N,L,T,Us,Ua,M,Um")))]
 "CSKY_ISA_FEATURE(smart) && operands[0] != stack_pointer_rtx
  && operands[1] != stack_pointer_rtx"
 "@
     addu\t%0, %1, %2
     addu\t%0, %1, %2
     addi\t%0, %1, %2
     addi\t%0, %1, %2
     subi\t%0, %1, %M2
     subi\t%0, %1, %M2
     mov\t%0, %1
     addi\t%0, %1, %2
     subi\t%0, %1, %M2"
  [(set_attr "length" "2,2,2,2,2,2,2,4,4")]
)

(define_insn "*smart_addsi3_sp"
  [(set (match_operand:SI          0 "register_operand"  "=z,z, z,a, z,a,r")
        (plus:SI (match_operand:SI 1 "register_operand"  "0, 0, 0,z, a,z,r")
                 (match_operand:SI 2 "nonmemory_operand" "P, Ug,r,Uq,a,a,M")))]
  "CSKY_ISA_FEATURE(smart) && (operands[0] == stack_pointer_rtx
                    || operands[1] == stack_pointer_rtx)"
  "@
     addi\t%0, %1, %2
     subi\t%0, %1, %M2
     addu\t%0, %1, %2
     addi\t%0, %1, %2
     addu\t%0, %1, %2
     addu\t%0, %1, %2
     addi\t%0, %1, %2"
)

(define_insn "*ck801_addsi3"
  [(set (match_operand:SI          0 "register_operand"  "=r,a,a,a,a,a, !z,!z,!z,a")
        (plus:SI (match_operand:SI 1 "register_operand"  "%0,a,0,a,0,a, 0, 0, 0, !z")
                 (match_operand:SI 2 "nonmemory_operand" "r, a,N,L,T,Us,P, Ug,r, Uq")))]
  "CSKY_ISA_FEATURE(E1)"
  "@
    addu\t%0, %1, %2
    addu\t%0, %1, %2
    addi\t%0, %1, %2
    addi\t%0, %1, %2
    subi\t%0, %1, %M2
    subi\t%0, %1, %M2
    addi\t%0, %1, %2
    subi\t%0, %1, %M2
    addu\t%0, %1, %2
    addi\t%0, %1, %2"
)

(define_insn "*fast_addsi3"
  [(set (match_operand:SI          0 "register_operand"  "=r,r, r")
        (plus:SI (match_operand:SI 1 "register_operand"  "%r,r, r")
                 (match_operand:SI 2 "nonmemory_operand" "M, Um,r")))]
  "CSKY_ISA_FEATURE_FAST && CSKY_ISA_FEATURE(E2)"
  "@
    addi\t%0, %1, %2
    subi\t%0, %1, %M2
    addu\t%0, %1, %2"
)

(define_expand "adddi3"
  [(parallel [(set (match_operand:DI 0 "register_operand" "")
                   (plus:DI (match_operand:DI 1 "register_operand" "")
                            (match_operand:DI 2 "csky_arith_int1_operand" "")))
              (clobber (reg:CC 33))])]
  ""
  "
  {
    if (CSKY_ISA_FEATURE(E1) && (GET_CODE (operands[2]) != REG))
        operands[2] = force_reg (DImode, operands[2]);
  }
  "
)

;; TODO calculate the length more precisely
(define_insn "*cskyv2_adddi3"
  [(set (match_operand:DI          0 "register_operand" "=&r,&r")
        (plus:DI (match_operand:DI 1 "register_operand" "%0, r")
                 (match_operand:DI 2 "register_operand" "r,  r")))
   (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E2)"
  "*
  {
    if (TARGET_BIG_ENDIAN)
      return \"cmplt\t%R0, %R0\;addc\t%R0, %R1, %R2\;addc\t%0, %1, %2\";
    return \"cmplt\t%0, %0\;addc\t%0, %1, %2\;addc\t%R0, %R1, %R2\";
  }"
  [(set_attr "length" "12,12")]
)

(define_insn "*ck801_adddi3"
  [(set (match_operand:DI          0 "register_operand" "=&r")
        (plus:DI (match_operand:DI 1 "register_operand" "%0")
                 (match_operand:DI 2 "register_operand" "r")))
   (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E1)"
  "*
  {
    if (TARGET_BIG_ENDIAN)
      return \"cmplt\t%R0, %R0\;addc\t%R0, %R1, %R2\;addc\t%0, %1, %2\";
    return \"cmplt\t%0, %0\;addc\t%0, %1, %2\;addc\t%R0, %R1, %R2\";
  }"
  [(set_attr "length" "6")]
)

;; special case for "longlong += 1"
(define_insn "*cskyv2_adddi1_1"
  [(set (match_operand:DI          0 "register_operand" "=&r")
        (plus:DI (match_operand:DI 1 "register_operand" "0")
                 (const_int 1)))
  (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E2)"
  "*
  {
    if(TARGET_BIG_ENDIAN)
      return \"addi\t%R0, %R0, 1\;cmpnei\t%R0, 0\;incf\t%0, %0, 1\";
    return \"addi\t%0, %0, 1\;cmpnei\t%0, 0\;incf\t%R0, %R0, 1\";
  }"
  [(set_attr "length" "12")]
)


;; sub instructions.

(define_expand "subsi3"
  [(set (match_operand:SI 0 "register_operand" "")
        (minus:SI (match_operand:SI 1 "register_operand" "")
                  (match_operand:SI 2 "nonmemory_operand" "")))]
  ""
  ""
)

(define_insn "*smart_subsi3"
  [(set (match_operand:SI           0 "register_operand"    "=a,a,a,a,a,a ,a")
        (minus:SI (match_operand:SI 1 "register_operand"    "a, 0,0,a,0,a ,a")
                  (match_operand:SI 2 "nonmemory_operand"   "a, a,N,L,T,Us,Ua")))]
  "CSKY_ISA_FEATURE(smart) && operands[0] != stack_pointer_rtx
   && operands[1] != stack_pointer_rtx"
  "@
    subu\t%0, %1, %2
    subu\t%0, %1, %2
    subi\t%0, %1, %2
    subi\t%0, %1, %2
    addi\t%0, %1, %M2
    addi\t%0, %1, %M2
    mov\t%0, %1"
  [(set_attr "length" "2,2,2,2,2,2,2")]
)

(define_insn "*smart_subsi3_sp"
  [(set (match_operand:SI           0 "register_operand"  "=z,z, z,a, a,r")
        (minus:SI (match_operand:SI 1 "register_operand"  "0, 0, 0,z, a,r")
                  (match_operand:SI 2 "nonmemory_operand" "P, Ug,a,Ur,a,M")))]
  "CSKY_ISA_FEATURE(smart) && (operands[0] == stack_pointer_rtx
                    || operands[1] == stack_pointer_rtx)"
  "@
    subi\t%0, %1, %2
    addi\t%0, %1, %M2
    subu\t%0, %1, %2
    addi\t%0, %1, %M2
    subu\t%0, %1, %2
    subi\t%0, %1, %2"
  [(set_attr "length" "2,2,2,2,2,4")]
)

(define_insn "*ck801_subsi3"
  [(set (match_operand:SI           0 "register_operand"    "=a,a,a,a,a,a")
        (minus:SI (match_operand:SI 1 "register_operand"    "0, a,0,a,0,a")
                  (match_operand:SI 2 "nonmemory_operand"   "a, a,N,L,T,Us")))]
  "CSKY_ISA_FEATURE(E1)
   && operands[0] != stack_pointer_rtx
   && operands[1] != stack_pointer_rtx"
  "@
    subu\t%0, %1, %2
    subu\t%0, %1, %2
    subi\t%0, %1, %2
    subi\t%0, %1, %2
    addi\t%0, %1, %M2
    addi\t%0, %1, %M2"
)

(define_insn "*ck801_subsi3_sp"
  [(set (match_operand:SI           0 "register_operand"  "=a,z,z, z")
        (minus:SI (match_operand:SI 1 "register_operand"  "z, 0,0, 0")
                  (match_operand:SI 2 "nonmemory_operand" "Ur,P,Ug,r")))]
  "CSKY_ISA_FEATURE(E1)
   && (operands[0] == stack_pointer_rtx
       || operands[1] == stack_pointer_rtx)"
  "@
    addi\t%0, %1, %M2
    subi\t%0, %1, %2
    addi\t%0, %1, %M2
    subu\t%0, %1, %2"
)

(define_insn "*fast_subsi3"
  [(set (match_operand:SI           0 "register_operand"  "=r,r,r")
        (minus:SI (match_operand:SI 1 "register_operand"  "r, r,r")
                  (match_operand:SI 2 "nonmemory_operand" "r, M,Um")))]
  "CSKY_ISA_FEATURE_FAST && CSKY_ISA_FEATURE(E2)"
  "@
     subu\t%0, %1, %2
     subi\t%0, %1, %2
     addi\t%0, %1, %M2"
)

(define_expand "subdi3"
  [(parallel [(set (match_operand:DI 0 "register_operand" "")
                  (minus:DI (match_operand:DI 1 "register_operand" "")
                            (match_operand:DI 2 "register_operand" "")))
              (clobber (reg:CC 33))])]
  ""
  ""
)

;; TODO calculate the length more precisely
(define_insn "*cskyv2_subdi3"
  [(set (match_operand:DI           0 "register_operand" "=&r,&r,&r")
        (minus:DI (match_operand:DI 1 "register_operand" "0,  r,r")
                  (match_operand:DI 2 "register_operand" "r,  0,r")))
  (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
    if (TARGET_BIG_ENDIAN)
      return \"cmphs\t%R0, %R0\;subc\t%R0, %R1,%R2\;subc\t%0, %1, %2\";
    return \"cmphs\t%0, %0\;subc\t%0, %1, %2\;subc\t%R0, %R1, %R2\";
  }"
  [(set_attr "length" "12,12,12")]
)

(define_insn "*ck801_subdi3"
  [(set (match_operand:DI           0 "register_operand" "=&r")
        (minus:DI (match_operand:DI 1 "register_operand" "0")
                  (match_operand:DI 2 "register_operand" "r")))
   (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E1)"
  "*{
    if (TARGET_BIG_ENDIAN)
      return \"cmphs\t%R0, %R0\;subc\t%R0, %R1,%R2\;subc\t%0, %1, %2\";
    return \"cmphs\t%0, %0\;subc\t%0, %1, %2\;subc\t%R0, %R1, %R2\";
  }"
  [(set_attr "length" "6")]
)

;; special case for "longlong -= 1"
(define_insn "*cskyv2_adddi1_1"
  [(set (match_operand:DI          0 "register_operand" "=&r")
        (plus:DI (match_operand:DI 1 "register_operand" "0")
                 (const_int -1)))
  (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
    if(TARGET_BIG_ENDIAN)
      return \"cmpnei\t%R0, 0\;decf\t%0, %0, 1\;subi\t%R0, %R0, 1\";
    return \"cmpnei\t%0, 0\;decf\t%R0, %R0, 1\;subi\t%0, %0, 1\";
  }"
  [(set_attr "length" "12")]
)


;; ------------------------------------------------------------------------
;; Multiplication insns
;; ------------------------------------------------------------------------

(define_expand "mulsi3"
  [(set (match_operand:SI          0 "register_operand" "")
        (mult:SI (match_operand:SI 1 "register_operand" "")
                 (match_operand:SI 2 "register_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_mulsi3"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (mult:SI (match_operand:SI 1 "register_operand" "%r")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E2)"
  "mult\t%0, %1, %2"
)

(define_insn "*ck801_mulsi3"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (mult:SI (match_operand:SI 1 "register_operand" "%0")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "mult\t%0, %1, %2"
)

(define_insn "mulhisi3"
  [(set (match_operand:SI                          0 "register_operand" "=r")
        (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "%r"))
                 (sign_extend:SI (match_operand:HI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(2E3)"
  "mulsh\t%0, %1, %2"
)


;; ------------------------------------------------------------------------
;; Conditional add insns
;; ------------------------------------------------------------------------

(define_expand "addsicc"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand    1 "ordered_comparison_operator" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:SI 3 "csky_literal_K_Uh_operand" "")]
  "CSKY_ISA_FEATURE(E2)"
  "
  {
    bool invert;

    invert = gen_csky_compare (GET_CODE (operands[1]),
                               XEXP (operands[1], 0),
                               XEXP (operands[1], 1));

    if (invert)
      emit_insn (gen_cskyv2_addcc_invert(operands[0],operands[2],operands[3]));
    else
      emit_insn (gen_cskyv2_addcc(operands[0],operands[2],operands[3]));

    DONE;
  }"
)

(define_insn "cskyv2_addcc"
  [(set (match_operand:SI                           0 "register_operand"          "=r,r")
        (if_then_else:SI (ne (reg:CC 33) (const_int 0))
                         (plus:SI (match_operand:SI 1 "register_operand"          "r,r")
                                  (match_operand:SI 2 "csky_literal_K_Uh_operand" "K,Uh"))
                         (match_dup 1)))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
      switch (which_alternative)
      {
         case 0:
           if (rtx_equal_p (operands[0], operands[1]))
             return \"inct\t%0, %1, %2\";
           else
             return \"movf\t%0, %1\;inct\t%0, %1, %2\";
         case 1:
           if (rtx_equal_p (operands[0], operands[1]))
             return \"dect\t%0, %1, %M2\";
           else
             return \"movf\t%0, %1\;dect\t%0, %1, %M2\";
         default:
             gcc_unreachable();
      }
  }"
  [(set (attr "length")
        (if_then_else (eq (match_dup 0) (match_dup 1))
                      (const_int 4)
                      (const_int 8))
  )]
)

(define_insn "cskyv2_addcc_invert"
  [(set (match_operand:SI                           0 "register_operand"          "=r,r")
        (if_then_else:SI (eq (reg:CC 33) (const_int 0))
                         (plus:SI (match_operand:SI 1 "register_operand"          "r,r")
                                  (match_operand:SI 2 "csky_literal_K_Uh_operand" "K,Uh"))
                         (match_dup 1)))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
    switch (which_alternative)
    {
      case 0:
        if (rtx_equal_p (operands[0], operands[1]))
          return \"incf\t%0, %1, %2\";
        else
          return \"movt\t%0, %1\;incf\t%0, %1, %2\";
      case 1:
        if (rtx_equal_p (operands[0], operands[1]))
          return \"decf\t%0, %1, %M2\";
        else
          return \"movt\t%0, %1\;decf\t%0, %1, %M2\";
      default:
          gcc_unreachable();
    }
  }"
  [(set (attr "length")
        (if_then_else (eq (match_dup 0) (match_dup 1))
                      (const_int 4)
                      (const_int 8))
  )]
)

/* FIXME this insn is now only used in 801 store, can it use
   for 801 conditional add const 1?  */
(define_insn "ck801_addc"
  [(set (match_operand:SI                   0 "register_operand" "=r")
        (plus:SI (ne:SI (reg:CC 33) (const_int 0))
                 (plus:SI (match_operand:SI 1 "register_operand" "%0")
                          (match_operand:SI 2 "register_operand" "r"))))
  (clobber (reg:CC 33))]
 "CSKY_ISA_FEATURE(E1)"
 "addc\t%0, %1, %2"
)


;; ------------------------------------------------------------------------
;; Extzv insns
;; ------------------------------------------------------------------------

(define_expand "extzvsi"
  [(set (match_operand:SI 0 "register_operand" "")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "")
                         (match_operand:SI 2 "const_int_operand" "")
                         (match_operand:SI 3 "const_int_operand" "")))]
  ""
  "{
    /* If the cpu has xtrb but donot have zext, we use xtrb if could.
       Now only ck802 will do this job.  */
    if (CSKY_ISA_FEATURE(E2) && !CSKY_ISA_FEATURE(2E3)
        && (INTVAL (operands[2]) == 8)
        && (INTVAL (operands[3]) % 8 == 0))
      {
        rtx xtrb = gen_rtx_SET (operands[0],
                                gen_rtx_ZERO_EXTRACT (SImode,
                                                      operands[1],
                                                      operands[2],
                                                      operands[3]));
        emit (gen_rtx_PARALLEL (VOIDmode,
                                gen_rtvec (2, xtrb,
                                gen_hard_reg_clobber (CCmode, 33))));
        DONE;
      }
    else if (!CSKY_ISA_FEATURE (2E3))
      {
        /* Use lsri and lsli to do extzv when donot have zext.  */
        rtx lshft = GEN_INT (32 - (INTVAL (operands[2])
                             + INTVAL (operands[3])));
        rtx rshft = GEN_INT (32 - INTVAL (operands[2]));
        rtx tmp1 = gen_reg_rtx (SImode);
        rtx tmp2 = gen_reg_rtx (SImode);

        emit_insn (gen_rtx_SET (tmp1, operands[1]));
        emit_insn (gen_rtx_SET (tmp2, gen_rtx_ASHIFT (SImode, tmp1, lshft)));
        emit_insn (gen_rtx_SET (operands[0],
                                gen_rtx_LSHIFTRT (SImode, tmp2, rshft)));
        DONE;
      }
    else
      {
        emit_insn (gen_cskyv2_extzv (operands[0], operands[1],
                                     operands[2], operands[3]));
        DONE;
      }
}")

(define_insn "cskyv2_extzv"
  [(set (match_operand:SI                  0 "register_operand" "=r")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "r")
                         (match_operand:SI 2 "csky_literal_K_operand" "K")
                         (match_operand:SI 3 "csky_literal_K_operand" "K")))]
  "CSKY_ISA_FEATURE(2E3)"
  "*{
    operands[2] = GEN_INT (INTVAL (operands[3]) + INTVAL (operands[2]) - 1);
    return \"zext\t%0, %1, %2, %3\";
  }"
)

(define_insn "*cskyv2_xtrb0"
  [(set (match_operand:SI                  0 "register_operand" "=r,r")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "0,r")
                         (const_int 8)
                         (const_int 24)))
        (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    lsri\t%0, %0, 24
    xtrb0\t%0, %1"
)

(define_insn "*cskyv2_xtrb1"
  [(set (match_operand:SI                  0 "register_operand" "=r")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "r")
                         (const_int 8)
                         (const_int 16)))
        (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E2)"
  "xtrb1\t%0, %1"
)

(define_insn "*cskyv2_xtrb2"
  [(set (match_operand:SI                  0 "register_operand" "=r")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "r")
                         (const_int 8)
                         (const_int 8)))
        (clobber (reg:CC 33))]
  "CSKY_ISA_FEATURE(E2)"
  "xtrb2\t%0, %1"
)


;; -------------------------------------------------------------------------
;; Zero extension instructions
;; -------------------------------------------------------------------------

(define_insn "zero_extendhisi2"
  [(set (match_operand:SI                 0 "register_operand" "=r")
        (zero_extend:SI (match_operand:HI 1 "register_operand" "r")))]
  ""
  "zexth\t%0, %1"
)

(define_insn "*cskyv2_zextend_ldh"
  [(set (match_operand:SI                 0 "register_operand" "=r")
        (zero_extend:SI (match_operand:HI 1 "csky_addr_reg_disp" "m")))]
  ""
  "ld.h\t%0, %1"
  [(set_attr "length" "4")]
)

(define_insn "zero_extendqisi2"
  [(set (match_operand:SI                 0 "register_operand" "=r")
        (zero_extend:SI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "zextb\t%0, %1"
)

(define_insn "*cskyv2_zextend_ldb"
  [(set (match_operand:SI                 0 "register_operand" "=r")
        (zero_extend:SI (match_operand:QI 1 "csky_addr_reg_disp" "m")))]
  ""
  "ld.b\t%0, %1"
  [(set_attr "length" "4")]
)

(define_insn "zero_extendqihi2"
  [(set (match_operand:HI                 0 "register_operand" "=r")
        (zero_extend:HI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "zextb\t%0, %1"
)

(define_insn "*cskyv2_zextend_ldbhi"
  [(set (match_operand:HI                 0 "register_operand"   "=r")
        (zero_extend:HI (match_operand:QI 1 "csky_addr_reg_disp" "m")))]
  ""
  "ld.b\t%0, %1"
  [(set_attr "length" "4")]
)

;; -------------------------------------------------------------------------
;; clzm2 instructions
;; -------------------------------------------------------------------------

(define_insn "clzsi2"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (clz:SI (match_operand:SI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E2)"
  "ff1  %0,%1"
)

;; -------------------------------------------------------------------------
;; one_cmplm2 instructions
;; -------------------------------------------------------------------------

(define_expand "one_cmplsi2"
  [(set (match_operand:SI         0 "register_operand" "")
        (not:SI (match_operand:SI 1 "register_operand" "")))]
  ""
  ""
)

(define_insn "*csky_one_cmplsi2"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (not:SI (match_operand:SI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E2)"
  "not %0, %1"
)

(define_insn "*ck801_one_cmplsi2"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (not:SI (match_operand:SI 1 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(E1)"
  "not %0, %1"
)

;; -------------------------------------------------------------------------
;; Sign extension instructions
;; -------------------------------------------------------------------------

;; One test shows that the following code helps to
;; reduce one 'load' and two 'mov'.
(define_expand "extendsidi2"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (match_operand:SI 1 "register_operand" "r"))]
  ""
  "{
    int low, high;

    if (TARGET_BIG_ENDIAN)
      low = 4, high = 0;
    else
      low = 0, high = 4;

    emit_insn (gen_rtx_SET (gen_rtx_SUBREG(SImode, operands[0], low),
                            operands[1]));

    emit_insn (gen_rtx_SET (gen_rtx_SUBREG (SImode, operands[0], high),
                            gen_rtx_ASHIFTRT (SImode,
                                              gen_rtx_SUBREG (SImode,
                                                              operands[0],
                                                              low),
                                              GEN_INT(31))));
    DONE;
  }"
)

(define_insn "extendhisi2"
  [(set (match_operand:SI                 0 "register_operand" "=r")
        (sign_extend:SI (match_operand:HI 1 "register_operand" "r")))]
  ""
  "sexth  %0, %1"
)

;; qi -> si
(define_insn "extendqisi2"
  [(set (match_operand:SI                 0 "register_operand" "=r")
        (sign_extend:SI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "sextb  %0, %1"
)

;; qi -> hi
(define_insn "extendqihi2"
  [(set (match_operand:HI                 0 "register_operand" "=r")
        (sign_extend:HI (match_operand:QI 1 "register_operand" "r")))]
  ""
  "sextb  %0, %1"
)

;; -------------------------------------------------------------------------
;; And instructions
;; -------------------------------------------------------------------------

(define_expand "andsi3"
  [(set (match_operand:SI 0 "register_operand" "")
        (and:SI (match_operand:SI 1 "register_operand" "")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
  {
    int i;
    rtx not_value;

    if (GET_CODE(operands[2]) == CONST_INT)
    {
      for (i = 13; i <= 31; i++)
      {
        if ((((HOST_WIDE_INT) 1) << i) - 1 == INTVAL (operands[2]))
          {
            emit_insn (gen_extzvsi (operands[0], operands[1], GEN_INT (i),
                                    const0_rtx));
            DONE;
          }
        else if ((((HOST_WIDE_INT) 1) << i) - 1
             == ~INTVAL (operands[2]))
          {
            rtx shift = GEN_INT (i);
            rtx reg = gen_reg_rtx (SImode);

            emit_insn (gen_lshrsi3 (reg, operands[1], shift));
            emit_insn (gen_ashlsi3 (operands[0], reg, shift));
            DONE;
          }
      }

      not_value = GEN_INT (~INTVAL(operands[2]));

      /* Try to transform to andni insrtuction.  */
      if (CSKY_ISA_FEATURE(E2))
        {
          if(csky_arith_O_operand (not_value,SImode))
            {
              emit_insn(gen_cskyv2_andnsi3 (operands[0], not_value, operands[1]));
              DONE;
            }
        }

      /* Let it emit andi or bclri*2 if it could. Otherwise, try
         some other ways.  */
      if (!satisfies_constraint_Ue(operands[2])
          && !(CSKY_ISA_FEATURE(E2) && satisfies_constraint_O (operands[2])))
        {
          /* If it is a negitive number, it seems better to use andn,
             since the NOT_VALUE, is always smaller than the origin value.  */
          if (INTVAL(operands[2]) < 0)
            {
              operands[2] = copy_to_mode_reg(SImode, not_value);
              emit_insn(gen_cskyv2_andnsi3 (operands[0], operands[2], operands[1]));
              DONE;
            }

          /* If the above ways are all not working, mov the const
             to reg.  */
          operands[2] = copy_to_mode_reg(SImode, operands[2]);
        }
    }
 }"
)

;;FIXME describe the length more precisely here.
(define_insn "*cskyv2_andsi3"
  [(set (match_operand:SI         0 "register_operand"           "=r,r,r")
        (and:SI (match_operand:SI 1 "register_operand"           "%r,r,r")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "r, O,Ue")))]
  "CSKY_ISA_FEATURE(E2)
   && (CONST_INT_P(operands[2])
       || !can_trans_by_csky_shlshr (INTVAL (operands[2])))"
  "*{
    switch(which_alternative)
      {
      case 0: return \"and\t%0, %1, %2\";
      case 1: return \"andi\t%0, %1, %2\";
      case 2: return output_csky_bclri(operands[0],
                                       operands[1],
                                       INTVAL(operands[2]));
      default: gcc_unreachable();
      }
  }"
  [(set_attr "length" "4,4,8")]
)

(define_insn "*ck801_andsi3"
  [(set (match_operand:SI         0 "register_operand"      "=r,r")
        (and:SI (match_operand:SI 1 "register_operand"      "%0,0")
                (match_operand:SI 2 "csky_arith_Ue_operand" "r, Ue")))]
  "CSKY_ISA_FEATURE(E1)"
  "*{
    switch(which_alternative)
      {
      case 0: return \"and\t%0, %1, %2\";
      case 1: return output_csky_bclri(operands[0],
                                       operands[1],
                                       INTVAL(operands[2]));
      default: gcc_unreachable();
      }
  }"
  [(set_attr "length" "2,4")]
)

(define_insn "cskyv2_andnsi3"
  [(use (and:SI (not:SI (match_operand:SI 1 "csky_arith_O_operand" "r, O"))
        (match_operand:SI                 2 "register_operand"     "r, r")))
   (set (match_operand:SI                 0 "register_operand"     "=r,r")
        (and:SI (not:SI (match_dup 1))
                (match_dup 2)))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    andn\t%0, %2, %1
    andni\t%0, %2, %1"
)

(define_insn "ck801_andnsi3"
  [(use (and:SI (not:SI (match_operand:SI 1 "register_operand" "r"))
                (match_operand:SI         2 "register_operand" "0")))
   (set (match_operand:SI                 0 "register_operand" "=r")
        (and:SI (not:SI (match_dup 1))
                (match_dup 2)))]
 "CSKY_ISA_FEATURE(E1)"
 "andn\t%0, %2, %1"
)


(define_expand "anddi3"
  [(set (match_operand:DI 0 "register_operand" "")
        (and:DI (match_operand:DI 1 "register_operand" "")
                (match_operand:DI 2 "register_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_anddi3"
  [(set (match_operand:DI         0 "register_operand" "=&b,&r")
        (and:DI (match_operand:DI 1 "register_operand" "%0,r")
                (match_operand:DI 2 "register_operand" "b,r")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    and\t%0, %1, %2\;and\t%R0, %R1, %R2
    and\t%0, %1, %2\;and\t%R0, %R1, %R2"
    [(set_attr "length" "4,8")]
 )

(define_insn "*ck801_anddi3"
 [(set (match_operand:DI         0 "register_operand" "=&r")
       (and:DI (match_operand:DI 1 "register_operand" "%0")
               (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "and\t%0, %1, %2\;and\t%R0, %R1, %R2"
  [(set_attr "length" "4")]
)


;; -------------------------------------------------------------------------
;; Ior instructions
;; -------------------------------------------------------------------------

(define_expand "iorsi3"
  [(set (match_operand:SI 0 "register_operand" "")
        (ior:SI (match_operand:SI 1 "register_operand" "")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
  {
    if (CONST_INT_P (operands[2])
        && ((CSKY_ISA_FEATURE(E1) && !csky_arith_Uf_operand (operands[2],SImode))
            || (CSKY_ISA_FEATURE(E2)
                && !csky_literal_I_operand (operands[2],SImode)
                && !csky_arith_Uf_operand (operands[2],SImode))))
      {
        operands[2] = copy_to_mode_reg (SImode, operands[2]);
      }
  }")

(define_insn "*cskyv2_iorsi3"
  [(set (match_operand:SI         0 "register_operand"           "=r,b, r, b, r, b,r")
        (ior:SI (match_operand:SI 1 "register_operand"           "%r,0, r, 0, r, 0,r")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "I, Ub,Ub,Uf,Uf,b,r")))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
     switch (which_alternative)
       {
       case 0: return \"ori\t%0, %1, %2\";
       case 1: return \"bseti\t%0, %1, %P2\";
       case 2: return \"bseti\t%0, %1, %P2\";
       case 3: return output_csky_bseti (operands[0], operands[1],
                                         INTVAL (operands[2]));
       case 4: return output_csky_bseti (operands[0], operands[1],
                                         INTVAL (operands[2]));
       case 5: return \"or\t%0, %1, %2\";
       case 6: return \"or\t%0, %1, %2\";
       default: gcc_unreachable ();
       }
  }"
  [(set_attr "length" "4,2,4,4,8,2,4")]
)

(define_insn "*ck801_iorsi3"
  [(set (match_operand:SI         0 "register_operand"      "=b,b, r")
        (ior:SI (match_operand:SI 1 "register_operand"      "%0,0, 0")
                (match_operand:SI 2 "csky_arith_Uf_operand" "Ub,Uf,r")))]
  "CSKY_ISA_FEATURE(E1)"
  "*{
     switch (which_alternative)
       {
       case 0: return \"bseti\t%0, %1, %P2\";
       case 1: return output_csky_bseti (operands[0], operands[1],
                                         INTVAL (operands[2]));
       case 2: return \"or\t%0, %1, %2\";
       default: gcc_unreachable ();
       }
  }"
  [(set_attr "length" "4,2,4")]
)


(define_expand "iordi3"
  [(set (match_operand:DI         0 "register_operand" "")
        (ior:DI (match_operand:DI 1 "register_operand" "")
                (match_operand:DI 2 "register_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_iordi3"
  [(set (match_operand:DI         0 "register_operand" "=&r,&r")
        (ior:DI (match_operand:DI 1 "register_operand" "%0, r")
                (match_operand:DI 2 "register_operand" "r,  r")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    or\t%0, %1, %2\;or\t%R0, %R1, %R2
    or\t%0, %1, %2\;or\t%R0, %R1, %R2"
  [(set_attr "length" "8,8")]
)

(define_insn "*ck801_iordi3"
  [(set (match_operand:DI         0 "register_operand" "=&r")
        (ior:DI (match_operand:DI 1 "register_operand" "%0")
                (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "or\t%0, %1, %2\;or\t%R0, %R1, %R2"
  [(set_attr "length" "4")]
)


;; -------------------------------------------------------------------------
;; Xor instructions
;; -------------------------------------------------------------------------

(define_expand "xorsi3"
  [(set (match_operand:SI 0 "register_operand" "")
        (xor:SI (match_operand:SI 1 "register_operand" "")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
  {
    if (CONST_INT_P(operands[2])
        && (CSKY_ISA_FEATURE(E1) || !csky_arith_O_operand(operands[2],SImode)))
      {
        operands[2] = copy_to_mode_reg (SImode, operands[2]);
      }
  }"
)

(define_insn "*cskyv2_xorsi3"
  [(set (match_operand:SI         0 "register_operand"           "=r,r")
        (xor:SI (match_operand:SI 1 "register_operand"           "r, r")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "r, O")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    xor\t%0, %1, %2
    xori\t%0, %1, %2"
)

(define_insn "*ck801_xorsi3"
  [(set (match_operand:SI         0 "register_operand"           "=r")
        (xor:SI (match_operand:SI 1 "register_operand"           "0")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "xor\t%0, %1, %2"
)

(define_expand "xordi3"
  [(set (match_operand:DI         0 "register_operand" "")
        (xor:DI (match_operand:DI 1 "register_operand" "")
                (match_operand:DI 2 "register_operand" "")))]
  ""
  ""
)
(define_insn "*cskyv2_xordi3"
  [(set (match_operand:DI         0 "register_operand" "=&r,&r")
        (xor:DI (match_operand:DI 1 "register_operand" "%0, r")
                (match_operand:DI 2 "register_operand" "r,  r")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    xor\t%0, %1, %2\;xor\t%R0, %R1, %R2
    xor\t%0, %1, %2\;xor\t%R0, %R1, %R2"
  [(set_attr "length" "8,8")]
)

(define_insn "*ck801_xordi3"
  [(set (match_operand:DI         0 "register_operand" "=&r")
        (xor:DI (match_operand:DI 1 "register_operand" "%0")
                (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "xor\t%0, %1, %2\;xor\t%R0, %R1, %R2"
  [(set_attr "length" "4")]
)


;; -------------------------------------------------------------------------
;; Div instructions
;; -------------------------------------------------------------------------

(define_insn "divsi3"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (div:SI (match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(div)"
  "divs\t%0, %1, %2"
)

(define_insn "udivsi3"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (udiv:SI (match_operand:SI 1 "register_operand" "r")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(div)"
  "divu\t%0, %1, %2"
)
