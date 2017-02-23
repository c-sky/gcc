
(define_predicate "csky_arith_K_operand"
  (match_code "reg,subreg,const_int")
  {
    if (register_operand (op, mode))
      return 1;

    if (CONST_INT_P (op) && CSKY_CONST_OK_FOR_K (INTVAL(op)))
      return 1;

    return 0;
  })

(define_predicate "csky_literal_K_operand"
  (match_code "const_int")
  {
    if (CONST_INT_P (op) && CSKY_CONST_OK_FOR_K (INTVAL(op)))
      return 1;

    return 0;
  })

(define_predicate "csky_literal_I_operand"
  (match_code "const_int")
  {
    if (CONST_INT_P (op) && CSKY_CONST_OK_FOR_I (INTVAL(op)))
      return 1;

    return 0;
  })

(define_predicate "csky_literal_J_operand"
  (match_code "const_int")
  {
    if (CONST_INT_P (op) && CSKY_CONST_OK_FOR_J (INTVAL(op)))
      return 1;

    return 0;
  })

(define_predicate "csky_literal_Uk_operand"
  (match_code "const_int")
  {
    if (CONST_INT_P (op) && CSKY_CONST_OK_FOR_Uk (INTVAL(op)))
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


;; Nonzero if OP is legal address for function call

(define_predicate "csky_call_address_operand"
  (match_code "reg,subreg,symbol_ref")
  {
    if (!flag_pic && (GET_CODE (op) == SYMBOL_REF))
      return 1;

    if (register_operand (op, mode))
      return 1;

    return 0;
  })

;; Nonzero if OP is a valid source operand for a compare operation.

(define_predicate "csky_compare_operand"
  (match_code "const_int,reg,subreg")
  {
    if (register_operand (op, mode))
      return 1;

    if (GET_CODE (op) == CONST_INT && INTVAL (op) == 0)
      return 1;

    return 0;
  })

(define_predicate "csky_literal_K_Uh_operand"
  (match_code "const_int")
  {
    if (CONST_INT_P (op)
        && (CSKY_CONST_OK_FOR_K (INTVAL(op))
            || CSKY_CONST_OK_FOR_Uh (INTVAL(op))))
          return 1;

    return 0;
  })

(define_predicate "csky_addr_reg_disp"
  (match_code "mem")
  {
    if (! general_operand(op, mode))
      return 0;
    else
      {
        struct csky_address addr;

        decompose_csky_address (XEXP(op, 0), &addr);

        /* FIXME The PIC related code.
           Check if load the symbol address from got table.  */
        if (addr.disp && GET_CODE(addr.disp) == UNSPEC)
            return 0;

        if (! addr.index && !addr.symbol)
          return 1;

        return 0;
      }
  })

(define_predicate "csky_arith_any_imm_operand"
  (match_code "const_int,reg,subreg")
  {
    if (register_operand (op, mode))
      return 1;

    if (CONST_INT_P (op))
      return 1;

    return 0;
  })

(define_predicate "csky_arith_O_operand"
  (match_code "reg,subreg,const_int")
  {
    if (register_operand (op, mode))
      return 1;

    if (CONST_INT_P (op) && CSKY_CONST_OK_FOR_O (INTVAL(op)))
      return 1;

    return 0;
  })

(define_predicate "csky_arith_Uf_operand"
  (match_code "reg,subreg,const_int")
  {
    if (register_operand (op, mode))
      return 1;

    if (CONST_INT_P (op) && CSKY_CONST_OK_FOR_Uf (INTVAL(op)))
      return 1;

    return 0;
  })
