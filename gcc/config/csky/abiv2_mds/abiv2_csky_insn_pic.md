
(define_insn "prologue_get_pc"
  [(set (reg:SI 28)
        (match_operand:SI 0 "" "X"))]
  "(GET_CODE(operands[0]) == UNSPEC)
   && (XINT(operands[0], 1) == PIC_SYMBOL_GOTPC_GRS)"
  "*{
    operands[0] = XVECEXP(operands[0], 0, 0);
    output_asm_insn(\"grs\tgb, %0\", operands);
    default_internal_label (asm_out_file, \"L\",
                            CODE_LABEL_NUMBER (XEXP(operands[0], 0)));
    return \"\";
  }"
)

(define_insn "*pic_got_pc"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_GOTPC))]
  "flag_pic"
  "lrw\t%0, %1@GOTPC"
)

(define_insn "*pic_symbol_gotoff"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_GOTOFF))]
  "flag_pic"
  "lrw\t%0, %1@GOTOFF"
)

(define_insn "*pic_symbol_got"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_GOT))]
  "flag_pic"
  "lrw\t%0, %1@GOT"
)

(define_insn "*pic_symbol_plt"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_PLT))]
  "flag_pic"
  "lrw\t%0, %1@PLT"
)

(define_insn "*pic_symbol_grs"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_GRS))]
  "flag_pic"
  "grs\t%0, %1"
)

(define_expand "builtin_setjmp_receiver"
  [(label_ref (match_operand 0 "" ""))]
  "flag_pic"
  "{
    rtx l1 = gen_label_rtx();
    rtx grs_label = gen_rtx_LABEL_REF(SImode, l1);
    rtx reg_gb = gen_rtx_REG(SImode, PIC_OFFSET_TABLE_REGNUM);
    rtx reg_temp = gen_rtx_REG(SImode, 12);

    rtx tmp0_unspec = gen_rtx_UNSPEC (Pmode,
                                      gen_rtvec (1, grs_label),
                                      PIC_SYMBOL_GOTPC_GRS);
    rtx tmp1_unspec = gen_rtx_UNSPEC (Pmode,
                                      gen_rtvec (1, grs_label),
                                      PIC_SYMBOL_GOTPC);

    emit_insn (gen_prologue_get_pc(tmp0_unspec));
    emit_move_insn(reg_temp, tmp1_unspec);
    emit_insn(gen_addsi3(reg_gb, reg_gb, reg_temp));
    emit_use (reg_gb);

    DONE;
  }"
)
