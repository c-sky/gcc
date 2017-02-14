
(define_predicate "csky_arith_K_operand"
  (match_code "reg,subreg,const_int")
  {
    if (register_operand (op, mode))
      return 1;

    if (CONST_INT_P (op) && CSKY_CONST_OK_FOR_K (INTVAL(op)))
      return 1;

    return 0;
  })


;; Nonzero if OP is a register or constant value of 1

(define_predicate "csky_arith_int1_operand"
  (match_code "reg,subreg,const_int")
  {
    if (register_operand (op, mode))
        return 1;

    if (op == const1_rtx)
        return 1;

    return 0;
  })
