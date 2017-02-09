
(define_predicate "csky_arith_K_operand"
  (match_code "reg,subreg,const_int")
  {
    if (register_operand (op, mode))
      return 1;

    if (CONST_INT_P (op) && CONST_OK_FOR_K (INTVAL(op)))
      return 1;

    return 0;
  })
