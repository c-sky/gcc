
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
    jbsr\t%0
  "
  [(set_attr "length" "2,4,4")]
)

; TODO PIC related define_isnsn call_internal_pic
