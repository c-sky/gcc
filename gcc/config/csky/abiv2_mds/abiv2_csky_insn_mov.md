
(define_expand "movsi"
  [(set (match_operand:SI 0 "general_operand" "")
        (match_operand:SI 1 "general_operand" ""))]
  ""
  "
  {
    if (can_create_pseudo_p () && MEM_P (operands[0]))
      {
        operands[1] = force_reg (SImode, operands[1]);
        emit_insn(gen_rtx_SET (VOIDmode, operands[0], operands[1]));
        DONE;
      }
    /* Recognize the case where operand[1] is a reference to thread-local
       data and load its address to a register.  */
    /* TODO impelent the TLS related function later. */
    /* TODO PIC related code.  */
  }"
)

(define_insn "*cskyv2_movsi"
  [(set (match_operand:SI 0 "nonimmediate_operand"        "=r,r,r, r, r, r, r,r,m,*y,*r,*v,*r,*v")
        (match_operand:SI 1 "general_operand" "r, I,Un,Uc,Uo,mi,F,c,r,*r,*y,*r,*v,*v"))]
  "!TARGET_CK801"
  "* return output_csky_move (insn, operands, SImode);"
  [(set_attr "length" "4,4,4,4,8,4,4,4,4,4,4,4,4,4")]
)

(define_insn "*ck801_movsi"
 [(set (match_operand:SI 0 "nonimmediate_operand"        "=r,a, a,r ,r,r,m")
       (match_operand:SI 1 "general_operand" "r, Up,T,mi,F,c,r"))]
 "TARGET_CK801"
 "* return output_ck801_move (insn, operands, SImode);"
 [(set_attr "length" "2,2,2,4,4,2,4")]
)

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
  [(set (match_operand:HI 0 "nonimmediate_operand"         "=r,r,r,r,m,*y,*r,*v,*r")
        (match_operand:HI 1 "general_operand"  "r, i,c,m,r,*r,*y,*r,*v"))]
  "!TARGET_CK801"
  "* return output_csky_move (insn, operands, HImode);"
  [(set_attr "length" "4,8,4,4,4,4,4,4,4")]
)

(define_insn "*ck801_movhi"
  [(set (match_operand:HI 0 "nonimmediate_operand"         "=r,a, a,r,r,r,m")
        (match_operand:HI 1 "general_operand"  "r, Up,T,i,m,c,r"))]
  "TARGET_CK801"
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
  "!TARGET_CK801"
  "* return output_csky_move (insn, operands, QImode);"
  [(set_attr "length" "4,8,4,4,4,4,4,4,4,4")]
)

(define_insn "*ck801_movqi"
  [(set (match_operand:QI 0 "nonimmediate_operand"  "=r,a, a,r,r,r,m")
        (match_operand:QI 1 "general_operand"       "r, Up,T,i,m,c,r"))]
  "TARGET_CK801"
  "* return output_csky_move (insn, operands, QImode);"
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

(define_insn "*csky_movdi"
  [(set (match_operand:DI 0 "nonimmediate_operand"  "=r,r,r,r,m,*r,*y,*v,*r,*v")
        (match_operand:DI 1 "general_operand"       "i, F,r,m,r,*y,*r,*r,*v,*v"))]
 "!TARGET_CK801"
 "* return output_csky_movedouble (operands, DImode);"
 [(set_attr "length" "8,8,16,16,16,16,16,16,16,16")]
)

(define_insn "*ck801_movdi"
  [(set (match_operand:DI 0 "nonimmediate_operand"  "=r,a, a,r,r,r,m")
        (match_operand:DI 1 "general_operand"       "r, Up,T,i,m,F,r"))]
 "TARGET_CK801"
 "* return output_csky_movedouble (operands, DImode);"
 [(set_attr "length" "4,4,4,8,8,8,8")]
)
