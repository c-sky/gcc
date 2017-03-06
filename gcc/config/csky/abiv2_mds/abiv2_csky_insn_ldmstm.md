
(define_expand "load_multiple"
  [(match_par_dup 3 [(set (match_operand:SI 0 "" "")
                          (match_operand:SI 1 "" ""))
                     (use (match_operand:SI 2 "" ""))])]
  "TARGET_MULTIPLE_STLD"
  "{
    int regno, count, i;
    rtx base,src;

    if (GET_CODE (operands[2])    != CONST_INT
        || INTVAL (operands[2])   < 2
        || INTVAL (operands[2])   > CSKY_MAX_MULTIPLE_STLD
        || GET_CODE (operands[1]) != MEM
        || !REG_P (XEXP (operands[1], 0))
        || XEXP (operands[1], 0)  != stack_pointer_rtx
        || GET_CODE (operands[0]) != REG
        || (REGNO (XEXP (operands[1], 0)) > REGNO (operands[0])
            && REGNO (XEXP (operands[1], 0)) < REGNO (operands[0]) + INTVAL (operands[2])))
      FAIL;

    count = INTVAL (operands[2]);
    regno = REGNO (operands[0]);

    operands[3] = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (count));

    base = force_reg (SImode, XEXP(operands[1], 0));
    src = replace_equiv_address (operands[1], base);

    for (i = 0; i < count; i++)
      {
        XVECEXP (operands[3], 0, i) = gen_rtx_SET (gen_rtx_REG (SImode, regno + i),
                                                   adjust_address_nv (src, SImode, i * 4));
      }
  }"
)

(define_expand "store_multiple"
  [(match_par_dup 3 [(set (match_operand:SI 0 "")
                          (match_operand:SI 1 ""))
                     (use (match_operand:SI 2 ""))])]
  "TARGET_MULTIPLE_STLD"
  "{
    int regno, count, i;
    rtx base, dest;

    /* Support only storing a constant number of registers to memory and
       only if at least two registers. */
    if (GET_CODE (operands[2])    != CONST_INT
        || INTVAL (operands[2])   < 2
        || INTVAL (operands[2])   > CSKY_MAX_MULTIPLE_STLD
        || GET_CODE (operands[0]) != MEM
        || !REG_P (XEXP (operands[0], 0))
        || XEXP (operands[0], 0)  != stack_pointer_rtx
        || GET_CODE (operands[1]) != REG
        || (REGNO (XEXP (operands[0], 0)) >= REGNO (operands[1])
            && REGNO (XEXP (operands[0], 0)) < REGNO (operands[1]) + INTVAL (operands[2])))
      FAIL;

    count = INTVAL (operands[2]);
    regno = REGNO (operands[1]);

    operands[3] = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (count));

    base = force_reg (SImode, XEXP(operands[0], 0));
    dest = replace_equiv_address (operands[0], base);

    for(i = 0; i < count; i++)
      {
        XVECEXP (operands[3], 0, i) = gen_rtx_SET (adjust_address_nv (dest, SImode, i * 4),
                                                   gen_rtx_REG (SImode, regno + i));
      }
  }"
)


(define_insn "*csky_ldmsi12"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
     (set (match_operand:SI 10 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 32))))
     (set (match_operand:SI 11 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 36))))
     (set (match_operand:SI 12 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 40))))
     (set (match_operand:SI 13 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 44))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 12"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi11"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
     (set (match_operand:SI 10 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 32))))
     (set (match_operand:SI 11 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 36))))
     (set (match_operand:SI 12 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 40))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 11"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi10"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
     (set (match_operand:SI 10 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 32))))
     (set (match_operand:SI 11 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 36))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 10"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi9"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
     (set (match_operand:SI 10 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 32))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 9"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi8"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 8"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi7"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 7"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi6"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 6"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_ldmsi5"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 5"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_ldmsi4"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 4"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_ldmsi3"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 3"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_ldmsi2"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 2"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

;; -----------------------------------------------------------------
;;   stmsi
;; -----------------------------------------------------------------

(define_insn "*csky_stmsi12"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 32)))
          (match_operand:SI 10 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 36)))
          (match_operand:SI 11 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 40)))
          (match_operand:SI 12 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 44)))
          (match_operand:SI 13 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 12"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi11"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 32)))
          (match_operand:SI 10 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 36)))
          (match_operand:SI 11 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 40)))
          (match_operand:SI 12 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 11"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi10"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 32)))
          (match_operand:SI 10 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 36)))
          (match_operand:SI 11 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 10"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi9"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 32)))
          (match_operand:SI 10 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 9"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi8"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 8"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi7"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 7"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi6"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 6"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_stmsi5"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 5"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi4"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 4"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi3"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 3"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi2"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 2"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)
