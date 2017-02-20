
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
  "@
  lsl  %0, %1, %2
  lsli %0, %1, %2"
)

(define_insn "ck801_ashlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=a,r")
        (ashift:SI (match_operand:SI 1 "register_operand"     "a,0")
                   (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
  "@
  asr  %0, %1, %2
  asri %0, %1, %2"
)

(define_insn "*ck801_ashrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=a,r")
        (ashiftrt:SI (match_operand:SI 1 "register_operand"     "a,0")
                     (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
  "@
  lsr  %0, %1, %2
  lsri %0, %1, %2"
)

(define_insn "ck801_lshrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=a,r")
        (lshiftrt:SI (match_operand:SI 1 "register_operand"     "a,0")
                     (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
  "@
  rotl  %0, %1, %2
  rotli %0, %1, %2"
)

(define_insn "*ck801_rotlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=r")
        (rotate:SI (match_operand:SI 1 "register_operand"     "0")
                   (match_operand:SI 2 "csky_arith_K_operand" "r")))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
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
 [(set (match_operand:SI          0 "register_operand"  "=a,a,a,a,a,a, a, r,r")
       (plus:SI (match_operand:SI 1 "register_operand"  "%a,0,0,a,0,a, a, r,r")
                (match_operand:SI 2 "nonmemory_operand" "a, a,N,L,T,Us,Ua,M,Um")))]
 "TARGET_SMART && operands[0] != stack_pointer_rtx
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
  "TARGET_SMART && (operands[0] == stack_pointer_rtx
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
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  [(set (match_operand:SI          0 "register_operand"  "=r,r,r")
        (plus:SI (match_operand:SI 1 "register_operand"  "%r,r,r")
                 (match_operand:SI 2 "nonmemory_operand" "r, M,Um")))]
  "CSKY_ISA_FEATURE_FAST && !CSKY_ISA_FEATURE_GET2MD(ck801)"
  "@
    addu    %0, %1, %2
    addi    %0, %1, %2
    subi    %0, %1, %M2"
)

(define_expand "adddi3"
  [(parallel [(set (match_operand:DI 0 "register_operand" "")
                   (plus:DI (match_operand:DI 1 "register_operand" "")
                            (match_operand:DI 2 "csky_arith_int1_operand" "")))
              (clobber (reg:CC 33))])]
  ""
  "
  {
    if (CSKY_ISA_FEATURE_GET2MD(ck801) && (GET_CODE (operands[2]) != REG))
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  "TARGET_SMART && operands[0] != stack_pointer_rtx
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
  "TARGET_SMART && (operands[0] == stack_pointer_rtx
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
  "CSKY_ISA_FEATURE_GET2MD(ck801)
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
  "CSKY_ISA_FEATURE_GET2MD(ck801)
   && (operands[0] == stack_pointer_rtx
       || operands[1] == stack_pointer_rtx)"
  "@
    addi    %0, %1, %M2
    subi    %0, %1, %2
    addi    %0, %1, %M2
    subu    %0, %1, %2"
)

(define_insn "*fast_subsi3"
  [(set (match_operand:SI           0 "register_operand"  "=r,r,r")
        (minus:SI (match_operand:SI 1 "register_operand"  "r, r,r")
                  (match_operand:SI 2 "nonmemory_operand" "r, M,Um")))]
 "!(CSKY_ISA_FEATURE_GET2MD(ck801) || TARGET_SMART)"
 "@
    subu    %0, %1, %2
    subi    %0, %1, %2
    addi    %0, %1, %M2"
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
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

(define_insn "mulsi3"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (mult:SI (match_operand:SI 1 "register_operand" "%r")
                 (match_operand:SI 2 "register_operand" "r")))]
  ""
  "mult\t%0, %1, %2"
)

(define_insn "*ck801_mulsi3"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (mult:SI (match_operand:SI 1 "register_operand" "%0")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
  "mult\t%0, %1, %2"
)


;; ------------------------------------------------------------------------
;; Conditional add insns
;; ------------------------------------------------------------------------

(define_expand "addsicc"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand    1 "ordered_comparison_operator" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:SI 3 "csky_literal_K_Uh_operand" "")]
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
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
                         (match_operand:SI          1 "register_operand"          "r,r")
                         (plus:SI (match_dup 1)
                                  (match_operand:SI 2 "csky_literal_K_Uh_operand" "K,Uh"))))]
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
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

(define_insn "cskyv2_addcc_invert"
  [(set (match_operand:SI                           0 "register_operand"          "=r,r")
        (if_then_else:SI (eq (reg:CC 33) (const_int 0))
                         (match_operand:SI          1 "register_operand"          "r,r")
                         (plus:SI (match_dup 1)
                                  (match_operand:SI 2 "csky_literal_K_Uh_operand" "K,Uh"))))]
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
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

/* FIXME this insn is now only used in 801 store, can it use
   for 801 conditional add const 1?  */
(define_insn "ck801_addc"
  [(set (match_operand:SI                   0 "register_operand" "=r")
        (plus:SI (ne:SI (reg:CC 33) (const_int 0))
                 (plus:SI (match_operand:SI 1 "register_operand" "%0")
                          (match_operand:SI 2 "register_operand" "r"))))
  (clobber (reg:CC 33))]
 "CSKY_ISA_FEATURE_GET2MD(ck801)"
 "addc\t%0, %1, %2"
)
