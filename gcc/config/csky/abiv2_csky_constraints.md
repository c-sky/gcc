
(define_register_constraint "a" "MINI_REGS" "r0 - r7")


(define_register_constraint "b" "LOW_REGS"  "r0 - r15")


(define_register_constraint "c" "C_REGS" "C")


(define_register_constraint "y" "HILO_REGS" "HI & LO")


(define_register_constraint "l" "LO_REGS" "lo register only")


(define_register_constraint "h" "HI_REGS" "hi register only")


(define_register_constraint "v" "V_REGS" "Vector REGS")


(define_register_constraint "z" "SP_REGS" "sp register only")


(define_memory_constraint "Q"
  "memory operands with base register, index regster and short displacement for FPUV2"
  (match_test "get_cskyv2_mem_constraint (\"Q\", op)"))

(define_memory_constraint "W"
  "memory operands with base register, index regster"
  (match_test "get_cskyv2_mem_constraint (\"W\", op)"))

(define_constraint "S"
  "Symbol reference"
  (match_test "symbolic_csky_address_p(op)"))


(define_constraint "R"
  "memory operands whose address only accept label_ref"
  (and (match_code "mem")
       (match_test "GET_CODE (XEXP (op, 0)) == LABEL_REF")))

(define_constraint "Un"
  "Constant whose low 16 bits are all zeros"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_MOVIH(ival)")))

(define_constraint "I"
  "Constant in range 0-65535"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_I(ival)")))

(define_constraint "Ub"
  "exact_log2 (VALUE & 0xFFFFFFFF) >= 0"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Ub (ival)")))

(define_constraint "Uc"
  "exact_log2 ((VALUE) + 1) >=0 && exact_log2 ((VALUE) + 1) <= 31"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Uc (ival)")))

(define_constraint "Ui"
  "Constant in range 0-31"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_K(ival)")))

(define_constraint "Uo"
  "Constant which is inlinable"
  (and (match_code "const_int")
       (match_test "constant_csky_inlinable(ival)")))

(define_constraint "Up"
  "Constant in range 0 - 255"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_N(ival + 1)")))

(define_constraint "Uf"
  "A constant with two '1' bit maximum"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Uf (ival)")))

(define_constraint "T"
  "Constant in range -256 - (-1)"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_T(ival)")))

(define_constraint "N"
  "Constant in range 1-256"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_N(ival)")))

(define_constraint "L"
  "Constant in range 1-8"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_L(ival)")))

(define_constraint "M"
  "Constant in range 1-4096"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_M(ival)")))

(define_constraint "Us"
  "Constant in range -8 - -1"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_US(ival)")))

(define_constraint "Um"
  "Constant in range -1 - (-4096)"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Um(ival)")))

(define_constraint "Ua"
  "Constant 0"
  (and (match_code "const_int")
       (match_test "ival == 0")))

(define_constraint "Ug"
  "Constant in range -508 - (-4) and is divisible by 4"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Ug (ival)")))

(define_constraint "Uj"
  "Constant in range 4 - 1024 and is divisible by 4"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Uj (ival)")))

(define_constraint "Ul"
  "Constant in range -1024 - (-4) and is divisible by 4"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Ul (ival)")))

(define_constraint "P"
  "Constant in range 4 - 508 and is divisible by 4"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_P (ival)")))

(define_constraint "Uq"
  "Constant in range 0 - 1020 and is divisible by 4"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Uj(ival + 4)")))

(define_constraint "Ur"
  "Constant in range 0 - -1020 and is divisible by 4"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Uj(-ival + 4)")))

(define_constraint "Ux"
 "satifies the @code{I} multiplied by any power of 2"
 (and (match_code "const_int")
      (match_test "shiftable_csky_imm8_const(ival)")))

(define_constraint "Uk"
  "Constant in range 1 - 65536"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Uk(ival)")))

(define_constraint "Uh"
  "Constant in range -31 - 0"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Uh (ival)")))

(define_constraint "Ue"
  "A constant with two '0' bit maximum"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Ue (ival)")))

(define_constraint "J"
  "Constant in range 1- 32"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_J(ival)")))

(define_constraint "K"
  "Constant in range 0-31"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_K(ival)")))

(define_constraint "Ut"
  "Constant in range 0-15"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Ut(ival)")))

(define_constraint "Uu"
  "Constant in range 1-16"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_Uu(ival)")))

(define_constraint "O"
  "Constant in range 0-4095"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_O(ival)")))

(define_constraint "Dp"
  "memory operands whose address only accept post_inc if condition is dspv2"
  (and (match_code "mem")
       (match_test "CSKY_ISA_FEATURE(dspv2) && GET_CODE (XEXP (op, 0)) == POST_INC")))

(define_constraint "Dm"
  "memory operands whose address do not accept post_inc if condition is dspv2"
  (and (match_code "mem")
       (match_test "!CSKY_ISA_FEATURE(dspv2) || GET_CODE (XEXP (op, 0)) != POST_INC")))

(define_memory_constraint "Ds"
  "memory operands just valid for single float instructions."
  (and (match_code "mem")
       (match_test "csky_legitimate_address_p (SFmode, XEXP (op, 0), 0)")))

(define_memory_constraint "Dd"
  "memory operands just valid for double float instructions."
  (and (match_code "mem")
       (match_test "csky_legitimate_address_p (DFmode, XEXP (op, 0), 0)")))
