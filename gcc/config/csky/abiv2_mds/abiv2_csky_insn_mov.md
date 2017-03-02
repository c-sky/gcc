
(define_mode_iterator QHI [QI HI])

;; ------------------------------------------------------------------------
;; Mov insns
;; ------------------------------------------------------------------------
(define_expand "movsi"
  [(set (match_operand:SI 0 "general_operand" "")
        (match_operand:SI 1 "general_operand" ""))]
  ""
  "
  {
    if (can_create_pseudo_p () && MEM_P (operands[0]))
      {
        operands[1] = force_reg (SImode, operands[1]);
        emit_insn(gen_rtx_SET (operands[0], operands[1]));
        DONE;
      }

    /* Recognize the case where operand[1] is a reference to thread-local
       data and load its address to a register.  */
    if (csky_tls_referenced_p (operands[1]))
      {
        rtx tmp = operands[1];
        rtx addend = NULL;

        if (GET_CODE (tmp) == CONST && GET_CODE (XEXP (tmp, 0)) == PLUS)
          {
            addend = XEXP (XEXP (tmp, 0), 1);
            tmp = XEXP (XEXP (tmp, 0), 0);
          }

        gcc_assert (GET_CODE (tmp) == SYMBOL_REF);
        gcc_assert (SYMBOL_REF_TLS_MODEL (tmp) != 0);

        tmp = legitimize_tls_address (tmp, !can_create_pseudo_p () ? operands[0] : 0);
        if (addend)
          {
            tmp = gen_rtx_PLUS (SImode, tmp, addend);
            tmp = force_operand (tmp, operands[0]);
          }
        operands[1] = tmp;
      }
    else if (flag_pic
             && (CONSTANT_P (operands[1])
                 || symbol_mentioned_p (operands[1])
                 || label_mentioned_p (operands[1])))
      {
        operands[1] = legitimize_pic_address (operands[1],
                                              SImode,
                                              (!can_create_pseudo_p () ? operands[0] : 0),
                                              1);
      }
  }"
)

(define_insn "*cskyv2_movsi"
  [(set (match_operand:SI 0 "nonimmediate_operand"  "=r,r,r, r, r, r, r,r,m,*y,*r,*v,*r,*v")
        (match_operand:SI 1 "general_operand"       "r, I,Un,Uc,Uo,mi,F,c,r,*r,*y,*r,*v,*v"))]
  "CSKY_ISA_FEATURE(E2)"
  "* return output_csky_move (insn, operands, SImode);"
  [(set_attr "length" "4,4,4,4,8,4,4,4,4,4,4,4,4,4")]
)

(define_insn "*ck801_movsi"
 [(set (match_operand:SI 0 "nonimmediate_operand"   "=r,a, a,r ,r,r,m")
       (match_operand:SI 1 "general_operand"        "r, Up,T,mi,F,c,r"))]
 "CSKY_ISA_FEATURE(E1)"
 "* return output_ck801_move (insn, operands, SImode);"
 [(set_attr "length" "2,2,2,4,4,2,4")]
)

;;Convert negative assignments to zero minus positive numbers.
(define_split
  [(set (match_operand:SI 0 "register_operand" "")
        (match_operand:SI 1 "const_int_operand" ""))]
    "satisfies_constraint_T (operands[1])"
    [(set (match_dup 0) (match_dup 2))
     (set (match_dup 0) (plus:SI (match_dup 0) (match_dup 1)))]
    "
      operands[2] = const0_rtx;
    "
)

;;Convert const assignments to small number of assignments and left shift.
(define_split
  [(set (match_operand:SI 0 "register_operand" "")
        (match_operand:SI 1 "const_int_operand" ""))]
  "satisfies_constraint_Ux (operands[1])"
  [(set (match_dup 0) (match_dup 1))
   (set (match_dup 0) (ashift:SI (match_dup 0) (match_dup 2)))]
  "
  {
    unsigned HOST_WIDE_INT val = INTVAL (operands[1]) &0xffffffffu;
    unsigned HOST_WIDE_INT mask = 0xff;
    int i;

    for (i = 0; i< 25; i++)
        if((val & (mask << i)) == val)
            break;
    if (i == 0)
        FAIL;
    operands[1] = GEN_INT (val >>i );
    operands[2] = GEN_INT (i);
  }"
)


(define_expand "movhi"
  [(set (match_operand:HI 0 "general_operand" "")
        (match_operand:HI 1 "general_operand"  ""))]
  ""
  "
  {
    if (GET_CODE (operands[0]) == MEM)
        operands[1] = force_reg (HImode, operands[1]);
    else if (CONSTANT_P (operands[1])
             && (GET_CODE (operands[1]) != CONST_INT
                 || (! CSKY_CONST_OK_FOR_I (INTVAL (operands[1]))
                     && ! CSKY_CONST_OK_FOR_Ub (INTVAL (operands[1]))
                     && ! CSKY_CONST_OK_FOR_Uc (INTVAL (operands[1]))))
             && ! reload_completed && ! reload_in_progress)
    {
        rtx reg = gen_reg_rtx (SImode);
        emit_insn (gen_movsi (reg, operands[1]));
        operands[1] = gen_lowpart (HImode, reg);
    }
  }"
)

(define_insn "*cskyv2_movhi"
  [(set (match_operand:HI 0 "nonimmediate_operand"  "=r,r,r,r,m,*y,*r,*v,*r")
        (match_operand:HI 1 "general_operand"       "r, i,c,m,r,*r,*y,*r,*v"))]
  "CSKY_ISA_FEATURE(E2)"
  "* return output_csky_move (insn, operands, HImode);"
  [(set_attr "length" "4,8,4,4,4,4,4,4,4")]
)

(define_insn "*ck801_movhi"
  [(set (match_operand:HI 0 "nonimmediate_operand"  "=r,a, a,r,r,r,m")
        (match_operand:HI 1 "general_operand"       "r, Up,T,i,m,c,r"))]
  "CSKY_ISA_FEATURE(E1)"
  "* return output_ck801_move (insn, operands, HImode);"
  [(set_attr "length" "2,2,2,4,4,2,4")]
)


(define_expand "movqi"
  [(set (match_operand:QI 0 "general_operand" "")
        (match_operand:QI 1 "general_operand"  ""))]
  ""
  "
  {
    if (can_create_pseudo_p () && GET_CODE (operands[0]) == MEM)
        operands[1] = force_reg (QImode, operands[1]);
    else if (CONSTANT_P (operands[1])
             && (GET_CODE (operands[1]) != CONST_INT
                 || (! CSKY_CONST_OK_FOR_I (INTVAL (operands[1]))
                     && ! CSKY_CONST_OK_FOR_Ub(INTVAL (operands[1]))
                     && ! CSKY_CONST_OK_FOR_Uc (INTVAL (operands[1]))))
             && ! reload_completed && ! reload_in_progress)
    {
        rtx reg = gen_reg_rtx (SImode);
        emit_insn (gen_movsi (reg, operands[1]));
        operands[1] = gen_lowpart (QImode, reg);
    }
  }"
)

(define_insn "*cskyv2_movqi"
  [(set (match_operand:QI 0 "nonimmediate_operand" "=r,r,r,r,m,*y,*r,*v,*r,*v")
        (match_operand:QI 1 "general_operand"      "r, i,c,m,r,*r,*y,*r,*v,*v"))]
  "CSKY_ISA_FEATURE(E2)"
  "* return output_csky_move (insn, operands, QImode);"
  [(set_attr "length" "4,8,4,4,4,4,4,4,4,4")]
)

(define_insn "*ck801_movqi"
  [(set (match_operand:QI 0 "nonimmediate_operand"  "=r,a, a,r,r,r,m")
        (match_operand:QI 1 "general_operand"       "r, Up,T,i,m,c,r"))]
  "CSKY_ISA_FEATURE(E1)"
  "* return output_ck801_move (insn, operands, QImode);"
  [(set_attr "length" "2,2,2,4,4,2,4")]
)


(define_expand "movdi"
  [(set (match_operand:DI 0 "general_operand" "")
        (match_operand:DI 1 "general_operand" ""))]
  ""
  "
  {
    if (can_create_pseudo_p () && GET_CODE (operands[0]) == MEM)
      operands[1] = force_reg (DImode, operands[1]);
    else if (GET_CODE (operands[1]) == CONST_INT)
      {
        int i;
        for (i = 0; i < UNITS_PER_WORD * 2; i += UNITS_PER_WORD)
            emit_move_insn (simplify_gen_subreg (SImode, operands[0], DImode, i),
                            simplify_gen_subreg (SImode, operands[1], DImode, i));
        DONE;
      }
  }"
)

;;Convert negative assignments to zero minus positive numbers.
(define_split
  [(set (match_operand:QHI 0 "register_operand" "")
        (match_operand:QHI 1 "const_int_operand" ""))]
  "satisfies_constraint_T (operands[1])"
  [(set (match_dup 4) (match_dup 2))
   (set (match_dup 4) (match_dup 3))
   (set (match_dup 0) (match_dup 5))]
  "
    int low;

    if (TARGET_BIG_ENDIAN)
      low = 4 - mode_size[GET_MODE(operands[0])];
    else
      low = 0;

    operands[2] = const0_rtx;
    if (can_create_pseudo_p ())
      operands[4] = gen_reg_rtx (SImode);
    else
    {
      operands[4] = gen_rtx_REG (SImode,
                                 REGNO (operands[0]));
    }
    operands[3] = gen_rtx_PLUS (SImode,
                                operands[4],
                                operands[1]);
    operands[5] = gen_rtx_SUBREG (GET_MODE(operands[0]),
                                  operands[4],
                                  low);
  "
)

;;Convert const assignments to small number of assignments and left shift.
(define_split
  [(set (match_operand:QHI 0 "register_operand" "")
        (match_operand:QHI 1 "const_int_operand" ""))]
  "satisfies_constraint_Ux (operands[1])"
  [(set (match_dup 3) (match_dup 1))
   (set (match_dup 3) (ashift:SI (match_dup 3) (match_dup 2)))
   (set (match_dup 0) (match_dup 4))]
  "
  {
    unsigned HOST_WIDE_INT val = INTVAL (operands[1]) &0xffffffffu;
    unsigned HOST_WIDE_INT mask = 0xff;
    int i;
    int low;

    if (TARGET_BIG_ENDIAN)
      low = 4 - mode_size[GET_MODE(operands[0])];
    else
      low = 0;

    if (can_create_pseudo_p ())
      operands[3] = gen_reg_rtx (SImode);
    else
    {
      operands[3] = gen_rtx_REG (SImode,
                                 REGNO (operands[0]));
    }

    operands[4] = gen_rtx_SUBREG (GET_MODE(operands[0]),
                                  operands[3],
                                  low);

    for (i = 0; i< 25; i++)
      {
        if((val & (mask << i)) == val)
          break;
      }
    if (i == 0)
        FAIL;
    operands[1] = GEN_INT (val >>i );
    operands[2] = GEN_INT (i);
  }"
)


(define_insn "*csky_movdi"
  [(set (match_operand:DI 0 "nonimmediate_operand"  "=r,r,r,r,m,*r,*y,*v,*r,*v")
        (match_operand:DI 1 "general_operand"       "i, F,r,m,r,*y,*r,*r,*v,*v"))]
 "CSKY_ISA_FEATURE(E2)"
 "* return output_csky_movedouble (operands, DImode);"
 [(set_attr "length" "8,8,16,16,16,16,16,16,16,16")]
)

(define_insn "*ck801_movdi"
  [(set (match_operand:DI 0 "nonimmediate_operand"  "=r,a, a,r,r,r,m")
        (match_operand:DI 1 "general_operand"       "r, Up,T,i,m,F,r"))]
 "CSKY_ISA_FEATURE(E1)"
 "* return output_ck801_movedouble (operands, DImode);"
 [(set_attr "length" "4,4,4,8,8,8,8")]
)


;; ------------------------------------------------------------------------
;; Conditional mov insns
;; ------------------------------------------------------------------------

(define_expand "movsicc"
  [(set (match_operand 0 "register_operand" "")
        (if_then_else:SI (match_operand    1 "ordered_comparison_operator" "")
                         (match_operand:SI 2 "nonmemory_operand" "")
                         (match_operand:SI 3 "nonmemory_operand" "")))]
  "CSKY_ISA_FEATURE(E2)"
  "
  {
    bool invert;

    /* FIXME the float comparsion is not needed being considered here
       since it will call the libgcc function. If we want to handle it,
       describe the movsfcc and movdfcc.  */
    invert = gen_csky_compare (GET_CODE (operands[1]),
                               XEXP (operands[1], 0),
                               XEXP (operands[1], 1));

    if (invert)
      emit_insn (gen_movf(operands[0],operands[2],operands[3]));
    else
      emit_insn (gen_movt(operands[0],operands[2],operands[3]));
    DONE;
  }")

(define_insn "movt"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (if_then_else:SI (ne (reg:CC 33) (const_int 0))
                         (match_operand:SI 1 "nonmemory_operand" "r")
                         (match_operand:SI 2 "nonmemory_operand" "r")))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
    if ( rtx_equal_p (operands[0], operands[1]) )
      return \"movf\t%0, %2\";
    else if ( rtx_equal_p (operands[0], operands[2]) )
      return \"movt\t%0, %1\";
    else
      return \"movt\t%0, %1\;movf\t%0, %2\";
  }"
  [(set (attr "length")
        (if_then_else
          (and (ne (match_dup 0) (match_dup 1))
               (ne (match_dup 0) (match_dup 2))
          )
        (const_int 8)
        (const_int 4))
   )]
)

(define_insn "movf"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (if_then_else:SI (eq (reg:CC 33) (const_int 0))
                         (match_operand:SI 1 "nonmemory_operand" "r")
                         (match_operand:SI 2 "nonmemory_operand" "r")))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
    if ( rtx_equal_p (operands[0], operands[1]) )
      return \"movt\t%0, %2\";
    else if ( rtx_equal_p (operands[0], operands[2]) )
      return \"movf\t%0, %1\";
    else
      return \"movt\t%0, %2\;movf\t%0, %1\";
  }"
  [(set (attr "length")
        (if_then_else
          (and (ne (match_dup 0) (match_dup 1))
               (ne (match_dup 0) (match_dup 2))
          )
        (const_int 8)
        (const_int 4))
  )]
)

(define_expand "cstoresi4"
  [(set (match_operand:SI 0 "register_operand" "")
        (match_operator   1 "ordered_comparison_operator"
          [(match_operand:SI 2 "csky_compare_operand" "")
           (match_operand:SI 3 "nonmemory_operand" "")]))]
  ""
  "
  {
    bool invert;

    invert = gen_csky_compare (GET_CODE (operands[1]),
                               operands[2], operands[3]);

    if (invert)
      emit_insn (gen_mvcv (operands[0]));
    else {
      if (CSKY_ISA_FEATURE(E1)) {
        emit_insn (gen_movsi(operands[0], const0_rtx));
        emit_insn (gen_ck801_addc(operands[0], operands[0], operands[0]));
      } else {
        emit_insn (gen_mvc (operands[0]));
      }
    }
    DONE;
  }"
)

(define_insn "mvc"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (ne:SI (reg:CC 33) (const_int 0)))]
  "CSKY_ISA_FEATURE(E2)"
  "mvc\t%0"
)

(define_insn "mvcv"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (eq:SI (reg:CC 33) (const_int 0)))]
  ""
  "mvcv\t%0"
)
