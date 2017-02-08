(define_register_constraint "c" "C_REGS" "C")


(define_register_constraint "l" "LO_REGS" "lo register only")


(define_register_constraint "h" "HI_REGS" "hi register only")


(define_register_constraint "v" "V_REGS" "Vector REGS")


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

(define_constraint "Uo"
  "Constant which is inlinable"
  (and (match_code "const_int")
       (match_test "constant_inlinable(ival)")))

(define_constraint "Up"
  "Constant in range 0 - 255"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_N(ival + 1)")))

(define_constraint "T"
  "Constant in range -256 - (-1)"
  (and (match_code "const_int")
       (match_test "CSKY_CONST_OK_FOR_T(ival)")))
