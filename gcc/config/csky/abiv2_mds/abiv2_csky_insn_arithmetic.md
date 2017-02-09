
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
  "!TARGET_CK801"
  "@
  asr  %0, %1, %2
  asri %0, %1, %2"
)

(define_insn "*ck801_ashrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=a,r")
        (ashiftrt:SI (match_operand:SI 1 "register_operand"     "a,0")
                     (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "TARGET_CK801"
  "@
  asri %0, %1, %2
  asr  %0, %1, %2"
)


;; Add instructions.

(define_expand "addsi3"
  [(set (match_operand:SI          0 "register_operand" "")
        (plus:SI (match_operand:SI 1 "register_operand" "")
                 (match_operand:SI 2 "nonmemory_operand" "")))]
  ""
  ""
)

(define_insn "*smart_addsi3"
 [(set (match_operand:SI          0 "register_operand"  "=a,r,a,a,a,a, r, r,r")
       (plus:SI (match_operand:SI 1 "register_operand"  "%a,0,0,a,0,a, r, r,r")
                (match_operand:SI 2 "nonmemory_operand" "a, r,N,L,T,Us,Ua,M,Um")))]
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
)


(define_insn "*smart_addsi3_sp"
  [(set (match_operand:SI          0 "register_operand"  "=z,z, z,a, z,a,r")
        (plus:SI (match_operand:SI 1 "register_operand"  "0, 0, 0,z, a,z,r")
                 (match_operand:SI 2 "nonmemory_operand" "P, Ug,r,Ug,a,a,M")))]
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
  "TARGET_CK801"
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
  "TARGET_FAST && !TARGET_CK801"
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
    if (TARGET_CK801 && (GET_CODE (operands[2]) != REG))
        operands[2] = force_reg (DImode, operands[2]);
  }
  "
)

(define_insn "*cskyv2_adddi3"
  [(set (match_operand:DI          0 "register_operand" "=&r,&r")
        (plus:DI (match_operand:DI 1 "register_operand" "%0, r")
                 (match_operand:DI 2 "register_operand" "r,  r")))
   (clobber (reg:CC 33))]
  "!TARGET_CK801"
  "*
  {
    if (TARGET_LITTLE_ENDIAN)
      return \"cmplt\t%0, %0\;addc\t%0, %1, %2\;addc\t%R0, %R1, %R2\";
    return \"cmplt\t%R0, %R0\;addc\t%R0, %R1, %R2\;addc\t%0, %1, %2\";
  }"
  [(set_attr "length" "12")]
)

(define_insn "*ck801_adddi3"
  [(set (match_operand:DI          0 "register_operand" "=&r")
        (plus:DI (match_operand:DI 1 "register_operand" "%0")
                 (match_operand:DI 2 "register_operand" "r")))
   (clobber (reg:CC 33))]
  "TARGET_CK801"
  "*
  {
    if (TARGET_LITTLE_ENDIAN)
      return \"cmplt\t%0, %0\;addc\t%0, %1, %2\;addc\t%R0, %R1, %R2\";
    return \"cmplt\t%R0, %R0\;addc\t%R0, %R1, %R2\;addc\t%0, %1, %2\";
  }"
  [(set_attr "length" "6")]
)

;; special case for "longlong += 1"
(define_insn "*cskyv2_adddi1_1"
  [(set (match_operand:DI          0 "register_operand" "=&r")
        (plus:DI (match_operand:DI 1 "register_operand" "0")
                 (const_int 1)))
  (clobber (reg:CC 33))]
  "!TARGET_CK801"
  "*
  {
    if(TARGET_LITTLE_ENDIAN)
      return \"addi\t%0, %0, 1\;cmpnei\t%0, 0\;incf\t%R0, %R0, 1\";
    return \"addi\t%R0, %R0, 1\;cmpnei\t%R0, 0\;incf\t%0, %0, 1\";
  }"
  [(set_attr "length" "12")]
)
