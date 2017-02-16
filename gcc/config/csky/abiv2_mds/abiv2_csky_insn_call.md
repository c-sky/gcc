
(define_expand "call"
  [(parallel [(call (match_operand:SI 0 "" "") (match_operand 1 "" ""))
              (clobber (reg:SI 15))])]
  ""
  "{
    rtx pic_ref;
    rtx addr_ref = XEXP (operands[0], 0);

    /* TODO PIC related code.  */

     if (GET_CODE (operands[0]) == MEM
         && ! register_operand (XEXP (operands[0], 0), SImode)
         && ! symbolic_csky_address_p (XEXP (operands[0], 0))
         /* TODO add condition about PIC.  */)
    {
      operands[0] = gen_rtx_MEM (GET_MODE (operands[0]),
                                 force_reg (Pmode, XEXP (operands[0], 0)));
    }
  }"
)


(define_insn "*call_internal"
  [(call (mem:SI (match_operand:SI 0 "csky_call_address_operand" "b,r,S"))
         (match_operand 1 "" ""))
   (clobber (reg:SI 15))]
  ""
  "@
    jsr\t%0
    jsr\t%0
    jbsr\t%0"
  [(set_attr "length" "2,4,4")]
)

; TODO PIC related define_isnsn call_internal_pic


(define_expand "call_value"
  [(parallel [(set (match_operand 0 "register_operand" "")
                   (call (match_operand:SI 1 "" "") (match_operand 2 "" "")))
              (clobber (reg:SI 15))])]
  ""
  "{
    /* TODO PIC related code.  */

     if (GET_CODE (operands[0]) == MEM
         && ! register_operand (XEXP (operands[0], 0), SImode)
         && ! symbolic_csky_address_p (XEXP (operands[0], 0))
         /* TODO add condition about PIC.  */)
    {
      operands[0] = gen_rtx_MEM (GET_MODE (operands[0]),
                                 force_reg (Pmode, XEXP (operands[0], 0)));
    }
  }")


(define_insn "*call_value_internal"
  [(set (match_operand                  0 "register_operand"          "=r,r,r")
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "b, r,S"))
              (match_operand 2 "" "")))
   (clobber (reg:SI 15))]
  ""
  "@
    jsr\t%1
    jsr\t%1
    jbsr\t%0"
  [(set_attr "length" "2,4,4")]
)

; TODO PIC related define_isnsn call_value_internal_pic


(define_insn "*call_value_struct"
  [(set (match_parallel 0 "" [(expr_list (match_operand 3 "register_operand" "")
                                         (match_operand 4 "immediate_operand" ""))
                              (expr_list (match_operand 5 "register_operand" "")
                                         (match_operand 6 "immediate_operand" ""))])
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "b,r,S"))
              (match_operand 2 "" "")))
        (clobber (reg:SI 15))]
  ""
  "@
    jsr\t%1
    jsr\t%1
    jbsr\t%0"
  [(set_attr "length" "2,4,4")]
)

; TODO PIC related define_isnsn call_value_struct_pic
