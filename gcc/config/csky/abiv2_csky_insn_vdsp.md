
;; ------------------------------------------------------------
;; CK803 Vector DSP insns
;; ------------------------------------------------------------


;; Load/Store 32 bit but mode is v4qi/v2hi,
;; and insn is still "ld.w/st.w and ldbi.w/stbi.w".

(define_expand "mov<mode>"
  [(set (match_operand:V32QHI 0 "nonimmediate_operand"  "")
        (match_operand:V32QHI 1 "nonimmediate_operand"  ""))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    if (can_create_pseudo_p ())
      {
        if (!REG_P (operands[0]))
          operands[1] = force_reg (<MODE>mode, operands[1]);
      }
  }
)

(define_insn "*dspv2_mov<mode>"
  [(set (match_operand:V32QHI 0 "nonimmediate_operand"  "=r,m,r")
        (match_operand:V32QHI 1 "nonimmediate_operand"  "m,r, r"))]
  "CSKY_ISA_FEATURE(dspv2)
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
  "* return output_csky_move (insn, operands, <MODE>mode);"
  [(set_attr "length" "4,4,4")
   (set_attr "type" "alu,alu,alu")]
)

(define_insn "add<mode>3"
  [(set (match_operand:V32QHI               0 "register_operand" "=r")
        (plus:V32QHI  (match_operand:V32QHI 1 "register_operand" "%r")
                      (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "padd.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "csky_addh<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (div:V32QHI (plus:V32QHI (match_operand:V32QHI 1 "register_operand" "%r")
                                 (match_operand:V32QHI 2 "register_operand" "r"))
                                 (const_int 2)))]
  "CSKY_ISA_FEATURE(dspv2)"
  "paddh.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ssadd<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (ss_plus:V32QHI (match_operand:V32QHI 1 "register_operand" "%r")
                        (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "padd.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "usadd<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (us_plus:V32QHI (match_operand:V32QHI 1 "register_operand" "%r")
                         (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "padd.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sub<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (minus:V32QHI (match_operand:V32QHI 1 "register_operand" "r")
                      (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psub.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sssub<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (ss_minus:V32QHI (match_operand:V32QHI 1 "register_operand" "%r")
                         (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psub.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ussub<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (us_minus:V32QHI (match_operand:V32QHI 1 "register_operand" "%r")
                         (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psub.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_code_iterator pcond [ne ge geu lt ltu])
(define_code_attr pcond_suf [(ne "ne.") (ge "hs.s") (geu "hs.u") (lt "lt.s") (ltu "lt.u")])

(define_insn "*mov<code>_16"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (if_then_else:V2HI(pcond:V2HI(match_operand:V2HI 1 "register_operand" "r")
                                     (match_operand:V2HI 2 "register_operand" "r"))
                          (const_int 65535)(const_int 0)))]
 "CSKY_ISA_FEATURE(dspv2)"
 "pcmp<pcond_suf>16\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*mov<code>_8"
  [(set (match_operand:V4QI 0 "register_operand" "=r")
        (if_then_else:V4QI(pcond:V4QI(match_operand:V4QI 1 "register_operand" "r")
                                     (match_operand:V4QI 2 "register_operand" "r"))
                           (const_int 255)(const_int 0)))]
 "CSKY_ISA_FEATURE(dspv2)"
 "pcmp<pcond_suf>8\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "smax<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (smax:V32QHI (match_operand:V32QHI 1 "register_operand" "r")
                     (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pmax.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umax<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (umax:V32QHI (match_operand:V32QHI 1 "register_operand" "r")
                     (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pmax.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "smin<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (smin:V32QHI (match_operand:V32QHI 1 "register_operand" "r")
                     (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pmin.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umin<mode>3"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (umin:V32QHI (match_operand:V32QHI 1 "register_operand" "r")
                     (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pmin.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "extendv4qiv4hi2"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (sign_extend:V4HI (match_operand:V4QI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pext.s8.e\t%0, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "zero_extendv4qiv4hi2"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (zero_extend:V4HI (match_operand:V4QI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pext.u8.e\t%0, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "ashrv2hi3"
  [(set (match_operand:V2HI 0 "register_operand" "")
        (ashiftrt:V2HI (match_operand:V2HI 1 "register_operand" "")
                       (match_operand:SI   2 "nonmemory_operand" "")))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    if (CONST_INT_P (operands[2])
        && !IN_RANGE (INTVAL (operands[2]), 1, 16))
      operands[2] = force_reg (SImode, operands[2]);
  }
)

(define_insn "*ashrim"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (ashiftrt:V2HI (match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI   2 "const_1_to_16_operand" "i")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pasri.s16\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*ashrre"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (ashiftrt:V2HI (match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI   2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pasr.s16\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "lshrv2hi3"
  [(set (match_operand:V2HI 0 "register_operand" "")
        (lshiftrt:V2HI (match_operand:V2HI 1 "register_operand" "")
                       (match_operand:SI   2 "nonmemory_operand" "")))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    if (CONST_INT_P (operands[2])
        && !IN_RANGE (INTVAL (operands[2]), 1, 16))
      operands[2] = force_reg (SImode, operands[2]);
  }
)

(define_insn "*lshrim"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (lshiftrt:V2HI (match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI   2 "const_1_to_16_operand" "i")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsri.u16\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*lshrre"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (lshiftrt:V2HI (match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI   2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsr.u16\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "ashlv2hi3"
  [(set (match_operand:V2HI 0 "register_operand" "")
        (ashift:V2HI (match_operand:V2HI 1 "register_operand" "")
                       (match_operand:SI 2 "nonmemory_operand" "")))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    if (CONST_INT_P (operands[2])
        && !IN_RANGE (INTVAL (operands[2]), 1, 16))
      operands[2] = force_reg (SImode, operands[2]);
  }
)

(define_insn "*lshlim"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (ashift:V2HI (match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI   2 "const_1_to_16_operand" "i")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsli.16\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*lshlre"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (ashift:V2HI (match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsl.16\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "ashlv2hq3"
  [(set (match_operand:V2HI 0 "register_operand" "")
        (ashift:V2HI (match_operand:V2HI 1 "register_operand" "")
                       (match_operand:SI 2 "nonmemory_operand" "")))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    if (CONST_INT_P (operands[2])
        && !IN_RANGE (INTVAL (operands[2]), 1, 16))
      operands[2] = force_reg (SImode, operands[2]);
  }
)

(define_insn "*lshlim_sat"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (ashift:V2HI (match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI   2 "const_1_to_16_operand" "i")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsli.16.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*lshlre_sat"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (ashift:V2HI (match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsl.16.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "vec_cmp<mode><mode>"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (match_operator:V32QHI 3 "ordered_comparison_operator"
          [(match_operand:V32QHI 1 "register_operand" "r")
           (match_operand:V32QHI 2 "register_operand" "r")]))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    int inverse = 0;
    int swap_operands = 0;
    rtx (*base_comparison) (rtx, rtx, rtx);
    switch (GET_CODE (operands[3]))
      {
        case EQ:
          inverse = 1;
        case NE:
          base_comparison = gen_csky_pcmpne<mode>;
          break;
        case LT:
          base_comparison = gen_csky_pcmplts<mode>;
          break;
        case GT:
          base_comparison = gen_csky_pcmplts<mode>;
          swap_operands = 1;
          break;
        case LE:
          base_comparison = gen_csky_pcmplts<mode>;
          break;
        case GE:
          base_comparison = gen_csky_pcmplts<mode>;
          swap_operands = 1;
          break;
        case LTU:
          base_comparison = gen_csky_pcmpltu<mode>;
          break;
        case GTU:
          base_comparison = gen_csky_pcmpltu<mode>;
          swap_operands = 1;
          break;
        case LEU:
          base_comparison = gen_csky_pcmpltu<mode>;
          break;
        case GEU:
          base_comparison = gen_csky_pcmpltu<mode>;
          swap_operands = 1;
          break;
        default:
          gcc_unreachable ();
      }

    if (swap_operands)
      emit_insn (base_comparison (operands[0], operands[1],
                                  operands[2]));
    else
      emit_insn (base_comparison (operands[0], operands[2],
                                  operands[1]));
    if (inverse)
      emit_insn (gen_one_cmpl<mode>2 (operands[0],
                                      operands[1]));
    DONE;
  }
)

(define_insn "csky_pcmpne<mode>"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (ne:V32QHI (match_operand:V32QHI 1 "register_operand" "%r")
                   (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pcmpne.<sup3>\t%0, %1, %2"
)

(define_code_iterator ltcond [lt ltu])

(define_insn "csky_pcmplt<codesup2><mode>"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (ltcond:V32QHI (match_operand:V32QHI 1 "register_operand" "%r")
                       (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pcmplt.<codesup2><sup3>\t%0, %1, %2"
)

(define_code_iterator gecond [ge geu])

(define_insn "csky_pcmphs<codesup2><mode>"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (gecond:V32QHI (match_operand:V32QHI 1 "register_operand" "%r")
                       (match_operand:V32QHI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pcmphs.<codesup2><sup3>\t%0, %1, %2"
)

(define_insn "one_cmpl<mode>2"
  [(set (match_operand:V32QHI         0 "register_operand" "=r")
        (not:V32QHI (match_operand:V32QHI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "not %0, %1"
)

(define_insn "mulv2hiv2si3"
  [(set (match_operand:V2SI                              0 "register_operand" "=r")
        (mult:V2SI (sign_extend:V2SI (match_operand:V2HI 1 "register_operand" "%r"))
                   (sign_extend:V2SI (match_operand:V2HI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pmul.s16\t%0, %1, %2"
)

(define_insn "umulv2hiv2si3"
  [(set (match_operand:V2SI                              0 "register_operand" "=r")
        (mult:V2SI (zero_extend:V2SI (match_operand:V2HI 1 "register_operand" "%r"))
                   (zero_extend:V2SI (match_operand:V2HI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pmul.u16\t%0, %1, %2"
)

;; ------------------------------------------------------------
;; CK803 Vector DSP builtin function insns
;; ------------------------------------------------------------

(define_expand "csky_padd<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_add<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_paddss<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_ssadd<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_paddus<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_usadd<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_psub<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_sub<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_psubss<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_sssub<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_psubus<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_ussub<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_smax<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_smax<mode>3 (operands[0], operands[1],
                                operands[2]));
    DONE;
  }
)

(define_expand "csky_umax<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_umax<mode>3 (operands[0], operands[1],
                                operands[2]));
    DONE;
  }
)

(define_expand "csky_smin<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_smin<mode>3 (operands[0], operands[1],
                                operands[2]));
    DONE;
  }
)

(define_expand "csky_umin<mode>"
  [(match_operand:V32QHI 0 "register_operand" "")
   (match_operand:V32QHI 1 "register_operand" "")
   (match_operand:V32QHI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_umin<mode>3 (operands[0], operands[1],
                                operands[2]));
    DONE;
  }
)

(define_expand "csky_plslv2hi"
  [(match_operand:V2HI 0 "register_operand" "")
   (match_operand:V2HI 1 "register_operand" "")
   (match_operand:SI   2 "nonmemory_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_lshrv2hi3 (operands[0], operands[1],
                              operands[2]));
    DONE;
  }
)

(define_expand "csky_plsrv2hi"
  [(match_operand:V2HI 0 "register_operand" "")
   (match_operand:V2HI 1 "register_operand" "")
   (match_operand:SI   2 "nonmemory_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_ashrv2hi3 (operands[0], operands[1],
                              operands[2]));
    DONE;
  }
)

(define_int_iterator PSHIFTIR [
  UNSPEC_PASRIR
  UNSPEC_PLSRIR
])

(define_int_attr pshiftir [
  (UNSPEC_PASRIR "pasri")
  (UNSPEC_PLSRIR "plsri")
])

(define_insn "csky_<pshiftir>rv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:SI   2 "const_1_to_16_operand" "i")]
                      PSHIFTIR))]
  "CSKY_ISA_FEATURE(dspv2)"
  "<pshiftir>.<sup2>16.r\t%0, %1, %2"
)

(define_int_iterator PSHIFTRR [
  UNSPEC_PASRR
  UNSPEC_PLSRR
])

(define_int_attr pshiftrr [
  (UNSPEC_PASRR "pasr")
  (UNSPEC_PLSRR "plsr")
])

(define_insn "csky_<pshiftrr>rv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:SI   2 "register_operand" "r")]
                      PSHIFTRR))]
  "CSKY_ISA_FEATURE(dspv2)"
  "<pshiftrr>.<sup2>16.r\t%0, %1, %2"
)

(define_insn "csky_plslissv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:SI   2 "const_1_to_16_operand" "i")]
                      UNSPEC_PLSLISS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsli.s16.s\t%0, %1, %2"
)

(define_insn "csky_plsliusv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI   2 "const_1_to_16_operand" "i")]
                       UNSPEC_PLSLIUS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsli.u16.s\t%0, %1, %2"
)

(define_insn "csky_plslssv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:SI   2 "register_operand" "r")]
                      UNSPEC_PLSLSS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsl.s16.s\t%0, %1, %2"
)

(define_insn "csky_plslusv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                       (match_operand:SI   2 "register_operand" "r")]
                       UNSPEC_PLSLUS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsl.u16.s\t%0, %1, %2"
)

(define_int_iterator PADDH [UNSPEC_PADDH_S UNSPEC_PADDH_U])
(define_int_iterator PSUBH [UNSPEC_PSUBH_S UNSPEC_PSUBH_U])
(define_int_iterator PASXH [UNSPEC_PASXH_S UNSPEC_PASXH_U])
(define_int_iterator PSAXH [UNSPEC_PSAXH_S UNSPEC_PSAXH_U])

(define_insn "csky_paddh<sup2><mode>"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (unspec:V32QHI [(match_operand:V32QHI 1 "register_operand" "r")
                        (match_operand:V32QHI 2 "register_operand" "r")]
                        PADDH))]
  "CSKY_ISA_FEATURE(dspv2)"
  "paddh.<sup2><sup3>\t%0, %1, %2"
)

(define_insn "csky_psubh<sup2><mode>"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (unspec:V32QHI [(match_operand:V32QHI 1 "register_operand" "r")
                        (match_operand:V32QHI 2 "register_operand" "r")]
                        PSUBH))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psubh.<sup2><sup3>\t%0, %1, %2"
)

(define_insn "csky_pasxv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                         (match_operand:V2HI 2 "register_operand" "r")]
                         UNSPEC_PASX))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pasx.16\t%0, %1, %2"
)

(define_insn "csky_pasxssv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                         (match_operand:V2HI 2 "register_operand" "r")]
                         UNSPEC_PASXSS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pasx.s16.s\t%0, %1, %2"
)

(define_insn "csky_pasxusv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                         (match_operand:V2HI 2 "register_operand" "r")]
                         UNSPEC_PASXUS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pasx.u16.s\t%0, %1, %2"
)

(define_insn "csky_psaxv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                         (match_operand:V2HI 2 "register_operand" "r")]
                         UNSPEC_PSAX))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psax.16\t%0, %1, %2"
)

(define_insn "csky_psaxssv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                         (match_operand:V2HI 2 "register_operand" "r")]
                         UNSPEC_PSAXSS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psax.s16.s\t%0, %1, %2"
)

(define_insn "csky_psaxusv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                         (match_operand:V2HI 2 "register_operand" "r")]
                         UNSPEC_PSAXUS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psax.u16.s\t%0, %1, %2"
)

(define_insn "csky_pasxh<sup2>v2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
                      PASXH))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pasxh.<sup2>16\t%0, %1, %2"
)

(define_insn "csky_psaxh<sup2>v2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r")
                      (match_operand:V2HI 2 "register_operand" "r")]
                      PSAXH))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psaxh.<sup2>16\t%0, %1, %2"
)

;; Control streaming data stream instructions

(define_insn "csky_selsi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")
                    (match_operand:SI 3 "register_operand" "r")]
                    UNSPEC_SEL))]
  "CSKY_ISA_FEATURE(dspv2)"
  "sel\t%0, %1, %2, %3"
)

(define_int_iterator PKG3R [ UNSPEC_PKGLL
                             UNSPEC_PKGHH
                             UNSPEC_NARL
                             UNSPEC_NARH
                             UNSPEC_NARLX
                             UNSPEC_NARHX])
(define_int_attr pkg3r [
  ( UNSPEC_PKGLL  "pkgll" )
  ( UNSPEC_PKGHH  "pkghh" )
  ( UNSPEC_NARL   "narl"  )
  ( UNSPEC_NARH   "narh"  )
  ( UNSPEC_NARLX  "narlx" )
  ( UNSPEC_NARHX  "narhx" )
])

(define_insn "csky_<pkg3r>si"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "register_operand" "r")]
                    PKG3R))]
  "CSKY_ISA_FEATURE(dspv2)"
  "<pkg3r>\t%0, %1, %2"
)

(define_insn "csky_dextsi"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r,r")
                    (match_operand:SI 2 "register_operand" "r,r")
                    (match_operand:SI 3 "csky_arith_K_operand" "Ui,r")]
                    UNSPEC_DEXT))]
  "CSKY_ISA_FEATURE(dspv2)"
  "@
   dexti\t%0, %1, %2, %3
   dext\t%0, %1, %2, %3"
)

(define_int_iterator CLIP [UNSPEC_CLIPU UNSPEC_CLIPS])

(define_insn "csky_clipusi"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r,r")
                    (match_operand:SI 2 "csky_arith_K_operand" "K,r")]
                    UNSPEC_CLIPU))]
  "CSKY_ISA_FEATURE(dspv2)"
  "@
   clipi.u32\t%0, %1, %2
   clip.u32\t%0, %1, %2"
)

(define_insn "csky_clipssi"
  [(set (match_operand:SI 0 "register_operand" "=r,r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r,r")
                    (match_operand:SI 2 "csky_arith_J_operand" "J,r")]
                    UNSPEC_CLIPS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "@
   clipi.s32\t%0, %1, %2
   clip.s32\t%0, %1, %2"
)

(define_int_iterator PCLIP [UNSPEC_PCLIPU UNSPEC_PCLIPS])

(define_insn "csky_pclipuv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r,r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r,r")
                      (match_operand:SI 2 "csky_arith_Ut_operand" "Ut,r")]
                      UNSPEC_PCLIPU))]
  "CSKY_ISA_FEATURE(dspv2)"
  "@
   pclipi.u16\t%0, %1, %2
   pclip.u16\t%0, %1, %2"
)

(define_insn "csky_pclipsv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r,r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand" "r,r")
                      (match_operand:SI 2 "csky_arith_Uu_operand" "Uu,r")]
                      UNSPEC_PCLIPS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "@
   pclipi.s16\t%0, %1, %2
   pclip.s16\t%0, %1, %2"
)

(define_insn "csky_ssabs<mode>"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (ss_abs:V32QHI (match_operand:V32QHI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pabs.s<sup3>.s\t%0, %1"
)

(define_expand "ssneg<mode>2"
  [(set (match_operand:V32QHI                0 "register_operand" "=r")
        (ss_neg:V32QHI (match_operand:V32QHI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_csky_ssneg<mode> (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "csky_ssneg<mode>"
  [(set (match_operand:V32QHI 0 "register_operand" "=r")
        (ss_neg:V32QHI (match_operand:V32QHI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pneg.s<sup3>.s\t%0, %1"
)

(define_insn "csky_pkgsi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand"        "r")
                    (match_operand:SI 2 "immediate_operand" "i")
                    (match_operand:SI 3 "register_operand"        "r")
                    (match_operand:SI 4 "immediate_operand" "i")]
                    UNSPEC_PKG))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pkg\t%0, %1, %2, %3, %4"
)

(define_expand "csky_pextsv4qi"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4QI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_extendv4qiv4hi2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_pextuv4qi"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4QI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_zero_extendv4qiv4hi2 (operands[0], operands[1]));
    DONE;
  }
)

(define_int_iterator PEXTX [ UNSPEC_PEXTXU8
                             UNSPEC_PEXTXS8 ])

(define_insn "csky_pextx<sup2>v4qi"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
        (unspec:V4HI [(match_operand:V4QI 1 "register_operand" "r")]
                      PEXTX))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pextx.<sup2>8.e\t%0, %1"
)

(define_insn "csky_dupv4qi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand"  "r")
                    (match_operand:SI 2 "immediate_operand"   "i")]
                    UNSPEC_DUP8))]
  "CSKY_ISA_FEATURE(dspv2)"
  "dup.8\t%0, %1, %2"
)

(define_insn "csky_dupv2hi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand"  "r")
                    (match_operand:SI 2 "immediate_operand"   "i")]
                    UNSPEC_DUP16))]
  "CSKY_ISA_FEATURE(dspv2)"
  "dup.16\t%0, %1, %2"
)

(define_expand "csky_pmulsv2hi"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2HI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_mulv2hiv2si3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_pmuluv2hi"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2HI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_umulv2hiv2si3 (operands[0], operands[1],
                                  operands[2]));
    DONE;
  }
)

(define_int_iterator PMULX [UNSPEC_PMULXS UNSPEC_PMULXU])

(define_insn "csky_pmulx<sup2>v2hi"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand"  "r")
                      (match_operand:V2HI 2 "register_operand"  "r")]
                      PMULX))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pmulx.<sup2>16\t%0, %1, %2"
)

(define_insn "csky_prmulsv2hi"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand"  "r")
                      (match_operand:V2HI 2 "register_operand"  "r")]
                      UNSPEC_PRMULS16))]
  "CSKY_ISA_FEATURE(dspv2)"
  "prmul.s16\t%0, %1, %2"
)

(define_insn "csky_prmulxsv2hi"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
        (unspec:V2SI [(match_operand:V2HI 1 "register_operand"  "r")
                      (match_operand:V2HI 2 "register_operand"  "r")]
                      UNSPEC_PRMULXS16))]
  "CSKY_ISA_FEATURE(dspv2)"
  "prmulx.s16\t%0, %1, %2"
)

(define_insn "csky_prmulshv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand"  "r")
                      (match_operand:V2HI 2 "register_operand"  "r")]
                      UNSPEC_PRMULS16H))]
  "CSKY_ISA_FEATURE(dspv2)"
  "prmul.s16.h\t%0, %1, %2"
)

(define_insn "csky_prmulsrhv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand"  "r")
                      (match_operand:V2HI 2 "register_operand"  "r")]
                      UNSPEC_PRMULS16RH))]
  "CSKY_ISA_FEATURE(dspv2)"
  "prmul.s16.rh\t%0, %1, %2"
)

(define_insn "csky_prmulxshv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand"  "r")
                      (match_operand:V2HI 2 "register_operand"  "r")]
                      UNSPEC_PRMULXS16H))]
  "CSKY_ISA_FEATURE(dspv2)"
  "prmulx.s16.h\t%0, %1, %2"
)

(define_insn "csky_prmulxsrhv2hi"
  [(set (match_operand:V2HI 0 "register_operand" "=r")
        (unspec:V2HI [(match_operand:V2HI 1 "register_operand"  "r")
                      (match_operand:V2HI 2 "register_operand"  "r")]
                      UNSPEC_PRMULXS16RH))]
  "CSKY_ISA_FEATURE(dspv2)"
  "prmulx.s16.rh\t%0, %1, %2"
)

(define_int_iterator MULCA [
  UNSPEC_MULCA
  UNSPEC_MULCAX
  UNSPEC_MULCS
  UNSPEC_MULCSR
  UNSPEC_MULCSX
  UNSPEC_MULACA
  UNSPEC_MULACAX
  UNSPEC_MULACS
  UNSPEC_MULACSR
  UNSPEC_MULACSX
  UNSPEC_MULSCA
  UNSPEC_MULSCAX
])

(define_int_attr mulca [
  (UNSPEC_MULCA  "mulca")
  (UNSPEC_MULCAX "mulcax")
  (UNSPEC_MULCS  "mulcs")
  (UNSPEC_MULCSR "mulcsr")
  (UNSPEC_MULCSX "mulcsx")
  (UNSPEC_MULACA   "mulaca")
  (UNSPEC_MULACAX  "mulacax")
  (UNSPEC_MULACS   "mulacs")
  (UNSPEC_MULACSR  "mulacsr")
  (UNSPEC_MULACSX  "mulacsx")
  (UNSPEC_MULSCA   "mulsca")
  (UNSPEC_MULSCAX  "mulscax")
])

(define_insn "csky_<mulca>v2hi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V2HI 1 "register_operand"  "r")
                    (match_operand:V2HI 2 "register_operand"  "r")]
                    MULCA))]
  "CSKY_ISA_FEATURE(dspv2)"
  "<mulca>.s16<dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_mulacav4qi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand"  "r")
                    (match_operand:V4QI 2 "register_operand"  "r")]
                    UNSPEC_MULACA))]
  "CSKY_ISA_FEATURE(dspv2)"
  "mulaca.s8\t%0, %1, %2"
)

(define_int_iterator MULAE [
  UNSPEC_MULACAE
  UNSPEC_MULACAXE
  UNSPEC_MULACSE
  UNSPEC_MULACSRE
  UNSPEC_MULACSXE
  UNSPEC_MULSCAE
  UNSPEC_MULSCAXE
])

(define_int_attr mulae [
  (UNSPEC_MULACAE   "mulaca")
  (UNSPEC_MULACAXE  "mulacax")
  (UNSPEC_MULACSE   "mulacs")
  (UNSPEC_MULACSRE  "mulacsr")
  (UNSPEC_MULACSXE  "mulacsx")
  (UNSPEC_MULSCAE   "mulsca")
  (UNSPEC_MULSCAXE  "mulscax")
])

(define_insn "csky_<mulae>ev2hi"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:V2HI 1 "register_operand"  "r")
                    (match_operand:V2HI 2 "register_operand"  "r")]
                    MULAE))]
  "CSKY_ISA_FEATURE(dspv2)"
  "<mulae>.s16.e\t%0, %1, %2"
)

(define_insn "csky_psabsav4qi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand"  "r")
                    (match_operand:V4QI 2 "register_operand"  "r")]
                    UNSPEC_PSABSA))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psabsa.u8\t%0, %1, %2"
)

(define_insn "csky_psabsaav4qi"
  [(set (match_operand:SI 0 "register_operand" "=&r")
        (unspec:SI [(match_operand:SI 1 "register_operand"  "0")
                    (match_operand:V4QI 2 "register_operand"  "r")
                    (match_operand:V4QI 3 "register_operand"  "r")]
                    UNSPEC_PSABSASA))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psabsaa.u8\t%0, %2, %3"
)

;; ------------------------------------------------------------
;; Vector DSP insns
;; ------------------------------------------------------------


(define_insn "*vdsp128_mov<mode>"
  [(set (match_operand:V128ALL 0 "nonimmediate_operand"  "=w,w,m,w,r")
        (match_operand:V128ALL 1 "nonimmediate_operand"  "m,w,w,r,w"))]
  "CSKY_ISA_FEATURE(vdsp128)
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
  "* return output_csky_move_v (operands);"
  [(set_attr "length" "4,4,4,4,4")
   (set_attr "type" "alu,alu,alu,alu,alu")]
)

(define_mode_attr vmvrtrmask [(V8HI "7") (V16QI "15")
                              (V4HI "7") (V8QI "15")])

(define_insn "*csky_vec_extracts<mode>"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (sign_extend:SI (vec_select:<vtoimode>
                          (match_operand:V128QHI 1 "register_operand" "w")
                          (parallel
                            [(match_operand:SI 2 "const_0_to_<vmvrtrmask>_operand")]))))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmfvr.s<sup3>\t%0,%1[%2]"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_insn "*csky_vec_extractu<mode>"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (zero_extend:SI (vec_select:<vtoimode>
                          (match_operand:V128QHI 1 "register_operand" "w")
                          (parallel
                            [(match_operand:SI 2 "const_0_to_<vmvrtrmask>_operand")]))))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmfvr.u<sup3>\t%0,%1[%2]"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_mode_attr vmvrtrallmask [(V4SI "3") (V8HI "7") (V16QI "15")
                                 (V2SI "3") (V4HI "7") (V8QI "15")])

(define_insn "*csky_vec_extractu<mode>"
  [(set (match_operand:<vtoimode> 0 "register_operand" "=r")
        (vec_select:<vtoimode>
          (match_operand:V128QHSI 1 "register_operand" "w")
          (parallel
            [(match_operand:SI 2 "const_0_to_<vmvrtrallmask>_operand")])))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmfvr.u<sup3>\t%0,%1[%2]"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_insn "csky_vec_set<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "+v")
        (vec_merge:V128QHSI
          (vec_duplicate:V128QHSI (match_operand:<vtoimode> 1 "register_operand" "r"))
          (match_dup 0)
          (match_operand 2 "const_int_operand")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmtvr.u<sup3>\t%0[%P2],%1"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_insn "*cskyv_add<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (plus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vadd.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_sub<mode>3"
  [(set (match_operand:V128QHSI                 0 "register_operand" "=w")
        (minus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")
                       (match_operand:V128QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vsub.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_and<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (and:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vand.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_ior<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (ior:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "nor<mode>3"
  [(set (match_operand:V128QHSI              0 "register_operand" "=w")
        (not:V128QHSI
          (ior:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                        (match_operand:V128QHSI 2 "register_operand" "w"))))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vnor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_xor<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (xor:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vxor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_smax<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (smax:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                       (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmax.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_umax<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (umax:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmax.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_smin<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (smin:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmin.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_umin<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (umin:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmin.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_fma<mode>4"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (fma:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")
                      (match_operand:V128QHSI 2 "register_operand" "w")
                      (match_operand:V128QHSI 3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmula.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_fnma<mode>4"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (fma:V128QHSI (neg:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w"))
                      (match_operand:V128QHSI 2 "register_operand" "w")
                      (match_operand:V128QHSI 3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmuls.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_mulu<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (mult:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                       (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmul.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_neg<mode>2"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (neg:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vneg.s<sup3>\t%0, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*cskyv_ssneg<mode>2"
  [(set (match_operand:V128QHSI                  0 "register_operand" "=w")
        (ss_neg:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vneg.s<sup3>.s\t%0, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

;; Comment those templates used for supporting shift operation of type vector.
;; Because the implementation mechanism in CSKY CPU differs mechanism defined by
;; GCC foreend.
;; The vector shift operation in CSKY means that performing shift operation on both
;; vector operand, however, GCC foreend requires 2nd operand is scalar type instead
;; of vector.
;; Commented by JianpingZeng on 3/20, 2018.
;;(define_expand "lshr<mode>3"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "")
;;        (lshiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "")
;;          (match_operand:SI       2 "nonmemory_operand" "")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  {
;;      if (const_0_to_31_operand(operands[2], SImode))
;;        emit_insn(gen_csky_lshr3_vdspr<mode>(operands[0], operands[1], operands[2]));
;;      else
;;      {
;;        rtx reg = gen_reg_rtx (SImode);
;;        emit_insn (gen_movsi (reg, operands[2]));
;;        emit_insn(gen_csky_lshr3_vdspi<mode>(operands[0], operands[1], reg));
;;      }
;;     DONE;
;;  }
;;)

;;(define_insn "csky_lshr3_vdspr<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=w")
;;        (lshiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "register_operand" "r")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshr.u<sup3>\t%0, %1, %2"
;;)

;;(define_insn "csky_lshr3_vdspi<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=w")
;;        (lshiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshri.u<sup3>\t%0, %1, %2"
;;)
;;(define_expand "ashr<mode>3"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "")
;;        (ashiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "")
;;          (match_operand:SI       2 "nonmemory_operand" "")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  {
;;    if (const_0_to_31_operand(operands[2], SImode))
;;      emit_insn(gen_csky_ashr_vdspi<mode>(operands[0], operands[1], operands[2]));
;;    else
;;    {
;;      rtx reg = gen_reg_rtx (SImode);
;;      emit_insn (gen_movsi (reg, operands[2]));
;;      emit_insn(gen_csky_ashr_vdspr<mode>(operands[0], operands[1], reg));
;;   }
;;    DONE;
;;  }
;;)

;;(define_insn "csky_ashr_vdspi<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=w")
;;        (ashiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshri.s<sup3>\t%0, %1, %2"
;;)

;;(define_insn "csky_ashr_vdspr<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=w")
;;        (ashiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "register_operand" "r")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshr.s<sup3>\t%0, %1, %2"
;;)


;;(define_expand "ashl<mode>3"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "")
;;        (ashift:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "")
;;          (match_operand:SI       2 "nonmemory_operand" "")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  {
;;      if (const_0_to_31_operand(operands[2], SImode))
;;        emit_insn(gen_csky_ashl_vdspi<mode>(operands[0], operands[1], operands[2]));
;;      else
;;      {
;;        rtx reg = gen_reg_rtx (SImode);
;;        emit_insn (gen_movsi (reg, operands[2]));
;;        emit_insn(gen_csky_ashl_vdspr<mode>(operands[0], operands[1], reg));
;;      }
;;      DONE;
;;  }
;;)

;;(define_insn "csky_ashl_vdspi<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=w")
;;        (ashift:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshli.u<sup3>\t%0, %1, %2"
;;)
;;(define_insn "csky_ashl_vdspr<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=w")
;;        (ashift:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "register_operand" "r")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshl.u<sup3>\t%0, %1, %2"
;;)

;;(define_expand "ssashl<mode>3"
;;  [(set (match_operand:V128QHSQ   0 "register_operand" "")
;;        (ashift:V128QHSQ
;;          (match_operand:V128QHSQ 1 "register_operand" "")
;;         (match_operand:SI       2 "nonmemory_operand" "")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  {
;;      if (const_0_to_31_operand(operands[2], SImode))
;;        emit_insn(gen_csky_ssashl_vdspi<mode>(operands[0], operands[1], operands[2]));
;;      else
;;     {
;;        rtx reg = gen_reg_rtx (SImode);
;;        emit_insn (gen_movsi (reg, operands[2]));
;;        emit_insn(gen_csky_ssashl_vdspr<mode>(operands[0], operands[1], reg));
;;     }
;;      DONE;
;;  }
;;)

;;(define_insn "csky_ssashl_vdspi<mode>"
;;  [(set (match_operand:V128QHSQ   0 "register_operand" "=w")
;;        (ashift:V128QHSQ
;;         (match_operand:V128QHSQ 1 "register_operand" "w")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshli.s<sup3>.s\t%0, %1, %2"
;;)

;;(define_insn "csky_ssashl_vdspr<mode>"
;;  [(set (match_operand:V128QHSQ   0 "register_operand" "=w")
;;        (ashift:V128QHSQ
;;          (match_operand:V128QHSQ 1 "register_operand" "w")
;;          (match_operand:SI       2 "register_operand" "r")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshl.s<sup3>.s\t%0, %1, %2"
;;)

;;(define_expand "usashl<mode>3"
;;  [(set (match_operand:V128UQHSQ   0 "register_operand" "")
;;        (ashift:V128UQHSQ
;;          (match_operand:V128UQHSQ 1 "register_operand" "")
;;          (match_operand:SI        2 "nonmemory_operand" "")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  {
;;      if (const_0_to_31_operand(operands[2], SImode))
;;        emit_insn(gen_csky_usashl_vdspi<mode>(operands[0], operands[1], operands[2]));
;;      else
;;      {
;;        rtx reg = gen_reg_rtx (SImode);
;;        emit_insn (gen_movsi (reg, operands[2]));
;;        emit_insn(gen_csky_usashl_vdspr<mode>(operands[0], operands[1], reg));
;;      }
;;      DONE;
;;  }
;;)

;;(define_insn "csky_usashl_vdspi<mode>"
;;  [(set (match_operand:V128UQHSQ   0 "register_operand" "=w")
;;        (ashift:V128UQHSQ
;;          (match_operand:V128UQHSQ 1 "register_operand" "w")
;;          (match_operand:SI        2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshli.u<sup3>.s\t%0, %1, %2"
;;)

;;(define_insn "csky_usashl_vdspr<mode>"
;;  [(set (match_operand:V128UQHSQ   0 "register_operand" "=w")
;;        (ashift:V128UQHSQ
;;          (match_operand:V128UQHSQ 1 "register_operand" "w")
;;          (match_operand:SI        2 "register_operand" "r")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshl.u<sup3>.s\t%0, %1, %2"
;;)

(define_insn "*cskyv_abs<mode>2"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (abs:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vabs.s<sup3>\t%0, %1"
)

(define_insn "csky_vabsss<mode>"
  [(set (match_operand:V128QHSI                  0 "register_operand" "=w")
        (ss_abs:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vabs.s<sup3>.s\t%0, %1"
)

(define_insn "*cskyv_bswap<mode>2"
  [(set (match_operand:V128QHSI                 0 "register_operand" "=w")
        (bswap:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vrev.<sup3>\t%0, %1"
)


;; ------------------------------------------------------------
;; Vector DSP builtin function insns
;; ------------------------------------------------------------

(define_expand "csky_vadd<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_add<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_insn "csky_vaddss<mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=w")
        (ss_plus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                          (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vadd.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "csky_vaddus<mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=w")
        (us_plus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                          (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vadd.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "csky_vsub<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_sub<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_insn "csky_vsubss<mode>"
  [(set (match_operand:V128QHSI                    0 "register_operand" "=w")
        (ss_minus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                           (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vsub.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "csky_vsubus<mode>"
  [(set (match_operand:V128QHSI                    0 "register_operand" "=w")
        (us_minus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                           (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vsub.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "csky_vand<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_and<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vsmax<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_smax<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vumax<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_umax<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vsmin<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_smin<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vumin<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_umin<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vmulu<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_mul<mode>3 (operands[0], operands[1],
                                operands[2]));
    DONE;
  }
)

(define_expand "csky_vmul_s<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_mul<mode>3 (operands[0], operands[1],
                                operands[2]));
    DONE;
  }
)

(define_expand "csky_vmulau<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")
   (match_operand:V128QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_fma<mode>4 (operands[0], operands[1],
                               operands[2], operands[3]));
    DONE;
  }
)

(define_expand "csky_vmulas<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")
   (match_operand:V128QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_fma<mode>4 (operands[0], operands[1],
                               operands[2], operands[3]));
    DONE;
  }
)

(define_expand "csky_vmulsu<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")
   (match_operand:V128QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_fnma<mode>4 (operands[0], operands[1],
                               operands[2], operands[3]));
    DONE;
  }
)

(define_expand "csky_vmulss<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")
   (match_operand:V128QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_fnma<mode>4 (operands[0], operands[1],
                               operands[2], operands[3]));
    DONE;
  }
)

(define_expand "csky_vor<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_ior<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vnoru<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_nor<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vnors<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_nor<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vxors<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_xor<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vxoru<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_xor<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

;; Instructions use format: insn vrx,vry,vrz
;; And only has mode v16qi
;; vrx = f(vry, vrz)

(define_int_iterator INSNVVV1 [
  UNSPEC_VBPERM
  UNSPEC_VBPERMZ
])

(define_int_attr insnvvv1 [
  (UNSPEC_VBPERM  "vbperm")
  (UNSPEC_VBPERMZ "vbpermz")
])

(define_insn "csky_<insnvvv1>v16qi"
  [(set (match_operand:V16QI 0 "register_operand" "=w")
        (unspec:V16QI [(match_operand:V16QI 1 "register_operand"  "w")
                       (match_operand:V16QI 2 "register_operand"  "w")]
                       INSNVVV1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv1>.8\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v16qi v8hi
;; vrx = f(vry, vrz)

(define_int_iterator INSNVVV2 [
  UNSPEC_VADDEU
  UNSPEC_VADDES
  UNSPEC_VMULEU
  UNSPEC_VMULES
  UNSPEC_VSABSEU
  UNSPEC_VSABSES
  UNSPEC_VSUBEU
  UNSPEC_VSUBES
])

(define_int_attr insnvvv2 [
  (UNSPEC_VADDEU   "vadd")
  (UNSPEC_VADDES   "vadd")
  (UNSPEC_VMULEU   "vmul")
  (UNSPEC_VMULES   "vmul")
  (UNSPEC_VSABSEU  "vsabs")
  (UNSPEC_VSABSES  "vsabs")
  (UNSPEC_VSUBEU   "vsub")
  (UNSPEC_VSUBES   "vsub")
])

(define_insn "csky_<insnvvv2>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=w")
        (unspec:<vexmode> [(match_operand:V128QHI 1 "register_operand"  "w")
                           (match_operand:V128QHI 2 "register_operand"  "w")]
                           INSNVVV2))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv2>.e<sup2><sup3>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v16qi v8hi
;; vrx = f(vrx, vry, vrz)

(define_int_iterator INSNVVV3 [
  UNSPEC_VMULAEU
  UNSPEC_VMULAES
  UNSPEC_VMULSEU
  UNSPEC_VMULSES
  UNSPEC_VSABSAEU
  UNSPEC_VSABSAES
])

(define_int_attr insnvvv3 [
  (UNSPEC_VMULAEU   "vmula")
  (UNSPEC_VMULAES   "vmula")
  (UNSPEC_VMULSEU   "vmuls")
  (UNSPEC_VMULSES   "vmuls")
  (UNSPEC_VSABSAEU  "vsabsa")
  (UNSPEC_VSABSAES  "vsabsa")
])

(define_insn "csky_<insnvvv3>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=w")
        (unspec:<vexmode> [(match_operand:V128QHI 1 "register_operand"  "w")
                           (match_operand:V128QHI 2 "register_operand"  "w")
                           (match_operand:<vexmode> 3 "register_operand"  "0")]
                           INSNVVV3))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv3>.e<sup2><sup3>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8hi v4si
;; vrx = f(vry, vrz)

(define_int_iterator INSNVVV4 [
  UNSPEC_VADDXU
  UNSPEC_VADDXS
  UNSPEC_VSUBXU
  UNSPEC_VSUBXS
])

(define_int_attr insnvvv4 [
  (UNSPEC_VADDXU  "vadd")
  (UNSPEC_VADDXS  "vadd")
  (UNSPEC_VSUBXU  "vsub")
  (UNSPEC_VSUBXS  "vsub")
])

(define_insn "csky_<insnvvv4>x<sup4><sup2><mode>"
  [(set (match_operand:V128HSI 0 "register_operand" "=w")
        (unspec:V128HSI [(match_operand:<vhalfmode> 1 "register_operand"  "w")
                        (match_operand:V128HSI 2 "register_operand"  "w")]
                         INSNVVV4))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv4>.x<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_int_iterator INSNVVV4_1 [
  UNSPEC_VADDXSLU
  UNSPEC_VADDXSLS
])

(define_int_attr insnvvv4_1 [
  (UNSPEC_VADDXSLU    "vadd")
  (UNSPEC_VADDXSLS    "vadd")
])

(define_insn "csky_<insnvvv4_1>x<sup4><sup2><mode>"
  [(set (match_operand:<vhalfmode> 0 "register_operand" "=w")
        (unspec:<vhalfmode> [(match_operand:<vhalfmode> 1 "register_operand"  "w")
                             (match_operand:V128HSI 2 "register_operand"  "w")]
                             INSNVVV4_1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv4_1>.x<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v16qi v8hi v4si
;; vrx = f(vry, vrz)

(define_int_iterator INSNVVV5 [
  UNSPEC_VCADDU
  UNSPEC_VCADDS
  UNSPEC_VCMAXU
  UNSPEC_VCMAXS
  UNSPEC_VCMINU
  UNSPEC_VCMINS
  UNSPEC_VDCH
  UNSPEC_VDCL
  UNSPEC_VICH
  UNSPEC_VICL
  UNSPEC_VSABSU
  UNSPEC_VSABSS
  UNSPEC_VTRCH
  UNSPEC_VTRCL
])

(define_int_iterator INSNVVV7 [
  UNSPEC_VADDHU
  UNSPEC_VADDHS
  UNSPEC_VADDHRU
  UNSPEC_VADDHRS
  UNSPEC_VSUBHU
  UNSPEC_VSUBHS
  UNSPEC_VSUBHRU
  UNSPEC_VSUBHRS
  UNSPEC_VSHRRU
  UNSPEC_VSHRRS
])

(define_int_iterator INSNVVV7_1 [
  UNSPEC_VTSTU
  UNSPEC_VTSTS
])

(define_int_attr insnvvv5 [
  (UNSPEC_VCADDU    "vcadd")
  (UNSPEC_VCADDS    "vcadd")
  (UNSPEC_VCMAXU    "vcmax")
  (UNSPEC_VCMAXS    "vcmax")
  (UNSPEC_VCMINU    "vcmin")
  (UNSPEC_VCMINS    "vcmin")
  (UNSPEC_VDCH      "vdch")
  (UNSPEC_VDCL      "vdcl")
  (UNSPEC_VICH      "vich")
  (UNSPEC_VICL      "vicl")
  (UNSPEC_VSABSU    "vsabs")
  (UNSPEC_VSABSS    "vsabs")
  (UNSPEC_VTRCH     "vtrch")
  (UNSPEC_VTRCL     "vtrcl")
])

(define_int_attr insnvvv7 [
  (UNSPEC_VADDHU    "vaddh")
  (UNSPEC_VADDHS    "vaddh")
  (UNSPEC_VADDHRU   "vaddh")
  (UNSPEC_VADDHRS   "vaddh")
  (UNSPEC_VSUBHU    "vsubh")
  (UNSPEC_VSUBHS    "vsubh")
  (UNSPEC_VSUBHRU   "vsubh")
  (UNSPEC_VSUBHRS   "vsubh")
  (UNSPEC_VSHRRU    "vshr")
  (UNSPEC_VSHRRS    "vshr")
  (UNSPEC_VTSTS     "vtst")
  (UNSPEC_VTSTU     "vtst")
])

(define_int_attr insnvvv7_1 [
  (UNSPEC_VTSTS     "vtst")
  (UNSPEC_VTSTU     "vtst")
])

(define_int_attr insnvvv7_1a [
  (UNSPEC_VTSTS     "vtsts")
  (UNSPEC_VTSTU     "vtstu")
])

(define_insn "csky_<insnvvv5><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")
                          (match_operand:V128QHSI 2 "register_operand"  "w")]
                          INSNVVV5))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv5>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_<insnvvv7><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")
                          (match_operand:V128QHSI 2 "register_operand"  "w")]
                          INSNVVV7))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv7>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_<insnvvv7_1a><sup4><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")
                          (match_operand:V128QHSI 2 "register_operand"  "w")]
                          INSNVVV7_1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv7_1>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)



(define_insn "csky_vandn<mode>"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (and:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")
                      (not:V128QHSI(match_operand:V128QHSI 2 "register_operand" "w"))))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vandn.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v16qi v8hi v4si
;; vrx = f(vrx, vry, vrz)

(define_insn "csky_vsabsas<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")
                          (match_operand:V128QHSI 2 "register_operand"  "w")
                          (match_operand:V128QHSI 3 "register_operand"  "w")]
                          UNSPEC_VSABSAS))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vsabsa.s<sup3>\t%0, %2, %3"
)

(define_insn "csky_vsabsau<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")
                          (match_operand:V128QHSI 2 "register_operand"  "w")
                          (match_operand:V128QHSI 3 "register_operand"  "w")]
                          UNSPEC_VSABSAU))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vsabsa.u<sup3>\t%0, %2, %3"
)

(define_expand "csky_vabs<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_abs<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_vmov<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_mov<mode> (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_vneg<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_neg<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_vnegs<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_ssneg<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "csky_vcnt1sv16qi"
  [(set (match_operand:V16QI 0 "register_operand" "=w")
        (unspec:V16QI [(match_operand:V16QI 1 "register_operand"  "w")]
                       UNSPEC_VCNT1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vcnt1.8\t%0, %1"
)

(define_expand "csky_vcnt1uv16qi"
  [(match_operand:V16QI 0 "register_operand" "")
   (match_operand:V16QI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_csky_vcnt1sv16qi (operands[0], operands[1]));
    DONE;
  }
)

;; Instructions use format: insn vrx,vry
;; And has mode: v16qi v8hi
;; vrx = f(vry)

(define_int_iterator INSNVV1 [
  UNSPEC_VMOVEU
  UNSPEC_VMOVES
])

(define_int_attr insnvv1 [
  (UNSPEC_VMOVEU  "vmov")
  (UNSPEC_VMOVES  "vmov")
])

(define_insn "csky_<insnvv1>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=w")
        (unspec:<vexmode> [(match_operand:V128QHI 1 "register_operand"  "w")]
                           INSNVV1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvv1>.e<sup2><sup3>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v16qi v8hi
;; vrx = f(vrx, vry)

(define_int_iterator INSNVV2 [
  UNSPEC_VCADDEU
  UNSPEC_VCADDES
])

(define_int_attr insnvv2 [
  (UNSPEC_VCADDEU     "vcadd")
  (UNSPEC_VCADDES     "vcadd")
])

(define_insn "csky_<insnvv2>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=w")
        (unspec:<vexmode> [(match_operand:V128QHI 1 "register_operand"  "w")
                           (match_operand:V128QHI 2 "register_operand"  "0")]
                           INSNVV2))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvv2>.e<sup2><sup3>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v8hi v4si
;; vrx = f(vry)

(define_int_iterator INSNVV3 [
  UNSPEC_VMOVHU
  UNSPEC_VMOVHS
  UNSPEC_VMOVLU
  UNSPEC_VMOVLS
  UNSPEC_VMOVRHU
  UNSPEC_VMOVRHS
  UNSPEC_VMOVSLU
  UNSPEC_VMOVSLS
  UNSPEC_VSTOUSLS
])

(define_int_attr insnvv3 [
  (UNSPEC_VMOVHU      "vmov")
  (UNSPEC_VMOVHS      "vmov")
  (UNSPEC_VMOVLU      "vmov")
  (UNSPEC_VMOVLS      "vmov")
  (UNSPEC_VMOVRHU     "vmov")
  (UNSPEC_VMOVRHS     "vmov")
  (UNSPEC_VMOVSLU     "vmov")
  (UNSPEC_VMOVSLS     "vmov")
  (UNSPEC_VSTOUSLS    "vstou")
])

(define_insn "csky_<insnvv3><sup4><sup2><mode>"
  [(set (match_operand:<vhalfmode> 0 "register_operand" "=w")
        (unspec:<vhalfmode> [(match_operand:V128HSI 1 "register_operand"  "w")]
                             INSNVV3))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvv3>.<sup2><sup3><dot><sup4>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v16qi v8hi v4si
;; vrx = f(vry)

(define_int_iterator INSNVV4 [
  UNSPEC_VCLSS
  UNSPEC_VCLZ
])

(define_int_attr insnvv4 [
  (UNSPEC_VCLSS       "vcls")
  (UNSPEC_VCLZ        "vclz")
])

(define_insn "csky_<insnvv4><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")]
                          INSNVV4))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvv4>.<sup2><sup3><dot><sup4>\t%0, %1"
)

(define_insn "csky_vrev<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")]
                          UNSPEC_VREV))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vrev.<sup3>\t%0, %1"
)

;; Instructions use format: insn vrx,vry[index]
;; And has mode: v16qi v8hi v4si
;; vrx = f(vry[index])

(define_insn "csky_vdup<mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand"  "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")
                          (match_operand:SI       2 "immediate_operand" "i")]
                          UNSPEC_VDUP))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vdup.<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx,(ry, offset)
;; And has mode: v16qi v8hi v4si
;; vrx = f(ry, offset)

(define_int_iterator INSNVGO1 [
  UNSPEC_VLDD
  UNSPEC_VLDQ
  UNSPEC_VSTD
  UNSPEC_VSTQ
])

(define_int_attr insnvgo1 [
  (UNSPEC_VLDD        "vldd")
  (UNSPEC_VLDQ        "vldq")
  (UNSPEC_VSTD        "vstd")
  (UNSPEC_VSTQ        "vstq")
])

(define_insn "csky_<insnvgo1><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:SI       1 "register_operand"  "r")
                          (match_operand:SI       2 "immediate_operand" "i")]
                          INSNVGO1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvgo1>.<sup3>\t%0, (%1, %2)"
)

;; Instructions use format: insn vrx,(ry, rz, shift)
;; And has mode: v16qi v8hi v4si
;; vrx = f(ry, rz, shift)

(define_int_iterator INSNVGGS1 [
  UNSPEC_VLDRD
  UNSPEC_VLDRQ
  UNSPEC_VSTRD
  UNSPEC_VSTRQ
])

(define_int_attr insnvggs1 [
  (UNSPEC_VLDRD        "vldrd")
  (UNSPEC_VLDRQ        "vldrq")
  (UNSPEC_VSTRD        "vstrd")
  (UNSPEC_VSTRQ        "vstrq")
])

(define_insn "csky_<insnvggs1><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=w")
        (unspec:V128QHSI [(match_operand:SI       1 "register_operand"  "r")
                          (match_operand:SI       2 "register_operand"  "r")
                          (match_operand:SI       3 "immediate_operand" "i")]
                          INSNVGGS1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvggs1>.<sup3>\t%0, (%1, %2<<%3)"
)

;; Instructions use format: insn vrx[index1],vry[index2]
;; And has mode: v16qi v8hi v4si
;; vrx = f(vrx[index1],vry[index2])

(define_insn "csky_vins<mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand"  "=w")
        (unspec:V128QHSI [(match_operand:SI       1 "immediate_operand" "i")
                          (match_operand:V128QHSI 2 "register_operand"  "w")
                          (match_operand:SI       3 "immediate_operand" "i")]
                          UNSPEC_VINS))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vins.<sup3>\t%0[%1], %2[%3]"
)

;; Instructions use format: insn rx,vry[index]
;; And has mode: v16qi v8hi v4si
;; rx = f(vry[index])

(define_insn "csky_vmfvru<mode>"
  [(set (match_operand:<vtoimode>                   0 "register_operand"  "=r")
        (unspec:<vtoimode> [(match_operand:V128QHSI 1 "register_operand"  "w")
                            (match_operand:SI       2 "immediate_operand" "i")]
                            UNSPEC_VMFVRU))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmfvr.u<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx[index], ry
;; And has mode: v16qi v8hi v4si
;; vrx = f(index, ry)

(define_insn "csky_vmtvru<mode>"
  [(set (match_operand:V128QHSI                     0 "register_operand"  "=w")
        (unspec:V128QHSI [(match_operand:SI         1 "immediate_operand"  "i")
                          (match_operand:<vtoimode> 2 "register_operand"  "r")]
                          UNSPEC_VMTVRU))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmtvr.u<sup3>\t%0[%1], %2"
)

;; Instructions use format: insn rx,vry[index]
;; And has mode: v16qi v8hi
;; rx = f(vry[index])

(define_insn "csky_vmfvrs<mode>"
  [(set (match_operand:<vtoimode>                   0 "register_operand"  "=r")
        (unspec:<vtoimode> [(match_operand:V128QHI  1 "register_operand"  "w")
                            (match_operand:SI       2 "immediate_operand" "i")]
                            UNSPEC_VMFVRS))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmfvr.s<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx, vry, imm5
;; And has mode: v16qi v8hi v4si
;; vrx = f(vry, imm5)

(define_int_iterator INSNVVI [
  UNSPEC_VSHRIRU
  UNSPEC_VSHRIRS
])

(define_int_attr insnvvi [
  (UNSPEC_VSHRIRU "vshri")
  (UNSPEC_VSHRIRS "vshri")
])

(define_insn "csky_<insnvvi><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand"  "=w")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "w")
                          (match_operand:SI       2 "immediate_operand" "i")]
                          INSNVVI))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvi>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

;; ------------------------------------------------------------
;; Vector DSP for 64bit
;; ------------------------------------------------------------

(define_expand "mov<mode>"
  [(set (match_operand:V64ALL 0 "nonimmediate_operand"  "")
        (match_operand:V64ALL 1 "nonimmediate_operand"  ""))]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    if (can_create_pseudo_p ())
      {
        if (!REG_P (operands[0]))
          operands[1] = force_reg (<MODE>mode, operands[1]);
      }
  }
)

(define_insn "*vdsp64_mov<mode>"
  [(set (match_operand:V64ALL 0 "nonimmediate_operand"  "=w,w,m,w,r,?r")
        (match_operand:V64ALL 1 "nonimmediate_operand"  "m,w,w,r,w,r"))]
  "CSKY_ISA_FEATURE(vdsp64)
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
  "* return output_csky_move_v (operands);"
  [(set_attr "length" "4,4,4,4,4,4")
   (set_attr "type" "alu,alu,alu,alu,alu,alu")]
)

(define_expand "vec_extract<mode>"
  [(match_operand:<vtoimode> 0 "register_operand")
   (match_operand:V64QHSI    1 "register_operand")
   (match_operand:SI         2 "const_int_operand")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    machine_mode inner_mode = GET_MODE_INNER (GET_MODE (operands[1]));
    rtx target = operands[0];
    rtx tmp;

    tmp = gen_rtx_PARALLEL (VOIDmode, gen_rtvec (1, GEN_INT (INTVAL (operands[2]))));
    tmp = gen_rtx_VEC_SELECT (inner_mode, operands[1], tmp);

    emit_insn (gen_rtx_SET (target, tmp));
    DONE;
  }
)

(define_insn "*csky_vec_extracts<mode>"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (sign_extend:SI (vec_select:<vtoimode>
                          (match_operand:V64QHI 1 "register_operand" "w")
                          (parallel
                            [(match_operand:SI 2 "const_0_to_<vmvrtrmask>_operand")]))))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmfvr.s<sup3>\t%0,%1[%2]"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_insn "*csky_vec_extractu<mode>"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (zero_extend:SI (vec_select:<vtoimode>
                          (match_operand:V64QHI 1 "register_operand" "w")
                          (parallel
                            [(match_operand:SI 2 "const_0_to_<vmvrtrmask>_operand")]))))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmfvr.u<sup3>\t%0,%1[%2]"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_insn "*csky_vec_extractu<mode>"
  [(set (match_operand:<vtoimode> 0 "register_operand" "=r")
        (vec_select:<vtoimode>
          (match_operand:V64QHSI 1 "register_operand" "w")
          (parallel
            [(match_operand:SI 2 "const_0_to_<vmvrtrallmask>_operand")])))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmfvr.u<sup3>\t%0,%1[%2]"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_expand "vec_set<mode>"
  [(match_operand:V64QHSI   0 "register_operand")
   (match_operand:<vtoimode> 1 "register_operand")
   (match_operand            2 "const_int_operand")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    rtx tmp;
    rtx target = operands[0];
    machine_mode mode = GET_MODE (operands[0]);

    tmp = gen_rtx_VEC_DUPLICATE (mode, operands[1]);
    tmp = gen_rtx_VEC_MERGE (mode,tmp,target,GEN_INT (1 << INTVAL (operands[2])));
    emit_insn (gen_rtx_SET (target, tmp));
    DONE;
  }
)

(define_insn "csky_vec_set<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "+v")
        (vec_merge:V64QHSI
          (vec_duplicate:V64QHSI (match_operand:<vtoimode> 1 "register_operand" "r"))
          (match_dup 0)
          (match_operand 2 "const_int_operand")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmtvr.u<sup3>\t%0[%P2],%1"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_expand "vec_cmp<mode><mode>"
  [(set (match_operand:V64QHSI    0 "register_operand")
        (match_operator:V64QHSI   1 "csky_scond_operator_common"
          [(match_operand:V64QHSI 2 "register_operand")
           (match_operand:V64QHSI 3 "reg_or_zero_operand")]))]
  "CSKY_ISA_FEATURE(vdsp64)"
  ""
)

(define_expand "vec_cmpu<mode><mode>"
  [(set (match_operand:V64QHSI    0 "register_operand")
        (match_operator:V64QHSI   1 "csky_ucond_operator_common"
          [(match_operand:V64QHSI 2 "register_operand")
           (match_operand:V64QHSI 3 "reg_or_zero_operand")]))]
  "CSKY_ISA_FEATURE(vdsp64)"
  ""
)

(define_insn "add<mode>3"
  [(set (match_operand:V64QHSI               0 "register_operand" "=w")
        (plus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                      (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vadd.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])


(define_insn "sub<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=w")
        (minus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")
                       (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsub.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sssub<mode>3"
  [(set (match_operand:V64QHSI                 0 "register_operand" "=w")
        (ss_minus:V64QHSI (match_operand:V64QHSI  1 "register_operand" "w")
                          (match_operand:V64QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsub.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ussub<mode>3"
  [(set (match_operand:V64QHSI                 0 "register_operand" "=w")
        (us_minus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")
                          (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsub.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "and<mode>3"
  [(set (match_operand:V64QHSI              0 "register_operand" "=w")
        (and:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                     (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vand.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ior<mode>3"
  [(set (match_operand:V64QHSI              0 "register_operand" "=w")
        (ior:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                     (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "nor<mode>3"
  [(set (match_operand:V64QHSI              0 "register_operand" "=w")
        (not:V64QHSI
          (ior:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                       (match_operand:V64QHSI 2 "register_operand" "w"))))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vnor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])
 
(define_insn "xor<mode>3"
  [(set (match_operand:V64QHSI              0 "register_operand" "=w")
        (xor:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                     (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vxor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "smax<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=w")
        (smax:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                       (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmax.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umax<mode>3"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (umax:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                      (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmax.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "smin<mode>3"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (smin:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                      (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmin.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umin<mode>3"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (umin:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                      (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmin.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "fma<mode>4"
  [(set (match_operand:V64QHSI               0 "register_operand" "=w")
        (fma:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")
                     (match_operand:V64QHSI 2 "register_operand" "w")
                     (match_operand:V64QHSI 3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmula.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "fnma<mode>4"
  [(set (match_operand:V64QHSI               0 "register_operand" "=w")
        (fma:V64QHSI (neg:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w"))
                     (match_operand:V64QHSI 2 "register_operand" "w")
                     (match_operand:V64QHSI 3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmuls.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "mul<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=w")
        (mult:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                       (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmul.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "neg<mode>2"
  [(set (match_operand:V64QHSI               0 "register_operand" "=w")
        (neg:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vneg.s<sup3>\t%0, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ssneg<mode>2"
  [(set (match_operand:V64QHSI                  0 "register_operand" "=w")
        (ss_neg:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vneg.s<sup3>.s\t%0, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

;; Comment those templates used for supporting shift operation of type vector.
;; Because the implementation mechanism in CSKY CPU differs mechanism defined by
;; GCC foreend.
;; The vector shift operation in CSKY means that performing shift operation on both
;; vector operand, however, GCC foreend requires 2nd operand is scalar type instead
;; of vector.
;; Commented by JianpingZeng on 3/20, 2018.
;;(define_insn "lshr<mode>3"
;;  [(set (match_operand:V64QHSI   0 "register_operand" "=w")
;;        (lshiftrt:V64QHSI
;;          (match_operand:V64QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshri.u<sup3>\t%0,%1,%2"
;;)

;;(define_insn "ashr<mode>3"
;;  [(set (match_operand:V64QHSI   0 "register_operand" "=w")
;;        (ashiftrt:V64QHSI
;;          (match_operand:V64QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshri.s<sup3>\t%0, %1, %2"
;;)

;;(define_insn "ashl<mode>3"
;;  [(set (match_operand:V64QHSI   0 "register_operand" "=w")
;;        (ashift:V64QHSI
;;          (match_operand:V64QHSI 1 "register_operand" "w")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshli.u<sup3>\t%0, %1, %2"
;;)

;;(define_insn "ssashl<mode>3"
;;  [(set (match_operand:V64QHSQ   0 "register_operand" "=w")
;;        (ashift:V64QHSQ
;;          (match_operand:V64QHSQ 1 "register_operand" "w")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshli.s<sup3>.s\t%0, %1, %2"
;;)

;;(define_insn "usashl<mode>3"
;;  [(set (match_operand:V64UQHSQ   0 "register_operand" "=w")
;;        (ashift:V64UQHSQ
;;          (match_operand:V64UQHSQ 1 "register_operand" "w")
;;          (match_operand:SI        2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshli.u<sup3>.s\t%0, %1, %2"
;;)

(define_insn "vashl<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=w,w")
        (ashift:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w,w")
                         (match_operand:V64QHSI 2 "imm_lshift_or_reg_vdspv2" "w,i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    switch(which_alternative)
    {
      case 0: return "vshl.u<sup3>\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshli",'u',"",&operands[2],
                                                 <MODE>mode, 1, 0);
      default:gcc_unreachable();
    }
  }
 )

(define_insn "vashr<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=w, w")
        (ashiftrt:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w, w")
                            (match_operand:V64QHSI 2 "imm_rshift_or_reg_vdspv2" "w, i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    switch(which_alternative)
    {
      case 0: return "vshr.s<sup3>\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshri",'s',"",&operands[2],
                                                   <MODE>mode, 0, 0);
      default:gcc_unreachable();
    }
  }
 )

(define_insn "vlshr<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=w, w")
        (lshiftrt:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w, w")
                          (match_operand:V64QHSI 2 "imm_rshift_or_reg_vdspv2" "w, i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    switch(which_alternative)
    {
      case 0: return "vshr.u<sup3>\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshri",'u',"",&operands[2],
                                                   <MODE>mode, 0, 0);
      default:gcc_unreachable();
    }
  }
 )

(define_insn "abs<mode>2"
  [(set (match_operand:V64QHSI               0 "register_operand" "=w")
        (abs:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vabs.s<sup3>\t%0, %1"
)

(define_insn "*cskyv_bswap<mode>2"
  [(set (match_operand:V64QHSI                 0 "register_operand" "=w")
        (bswap:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vrev.<sup3>\t%0, %1"
)

(define_expand "csky_vadd<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_add<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_insn "csky_vaddss<mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=w")
        (ss_plus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                         (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vadd.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "csky_vaddus<mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=w")
        (us_plus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%w")
                         (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vadd.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "csky_vsub<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_sub<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_insn "csky_vsubss<mode>"
  [(set (match_operand:V64QHSI                 0 "register_operand" "=w")
        (ss_minus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")
                            (match_operand:V64QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsub.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "csky_vsubus<mode>"
  [(set (match_operand:V64QHSI                 0 "register_operand" "=w")
        (us_minus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")
                            (match_operand:V64QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsub.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "csky_vand<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_and<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vsmax<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_smax<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vumax<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_umax<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vsmin<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_smin<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vumin<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_umin<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vmulu<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_mul<mode>3 (operands[0], operands[1],
                                operands[2]));
    DONE;
  }
)

(define_expand "csky_vmul_s<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_mul<mode>3 (operands[0], operands[1],
                                operands[2]));
    DONE;
  }
)

(define_expand "csky_vmulau<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")
   (match_operand:V64QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_fma<mode>4 (operands[0], operands[1],
                               operands[2], operands[3]));
    DONE;
  }
)

(define_expand "csky_vmulas<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")
   (match_operand:V64QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_fma<mode>4 (operands[0], operands[1],
                               operands[2], operands[3]));
    DONE;
  }
)

(define_expand "csky_vmulsu<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")
   (match_operand:V64QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_fnma<mode>4 (operands[0], operands[1],
                               operands[2], operands[3]));
    DONE;
  }
)

(define_expand "csky_vmulss<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")
   (match_operand:V64QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_fnma<mode>4 (operands[0], operands[1],
                               operands[2], operands[3]));
    DONE;
  }
)

(define_expand "csky_vor<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_ior<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vnoru<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_nor<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vnors<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_nor<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vxors<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_xor<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vxoru<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_xor<mode>3 (operands[0], operands[1],
                               operands[2]));
    DONE;
  }
)

(define_expand "csky_vshru<mode>"
 [(match_operand:V64QHSI      0 "register_operand")
  (match_operand:V64QHSI      1 "register_operand")
  (match_operand:V64QHSI      2 "register_operand")]
 "CSKY_ISA_FEATURE(vdsp64)"
 {
  emit_insn(gen_vlshr<mode>3(operands[0], operands[1], operands[2]));
  DONE;
 }
 )

(define_expand "csky_vshrs<mode>"
 [(match_operand:V64QHSI      0 "register_operand")
  (match_operand:V64QHSI      1 "register_operand")
  (match_operand:V64QHSI      2 "register_operand")]
 "CSKY_ISA_FEATURE(vdsp64)"
 {
  emit_insn(gen_vashr<mode>3(operands[0], operands[1], operands[2]));
  DONE;
 }
 )

(define_expand "csky_vshlu<mode>"
 [(match_operand:V64QHSI      0 "register_operand")
  (match_operand:V64QHSI      1 "register_operand")
  (match_operand:V64QHSI      2 "register_operand")]
 "CSKY_ISA_FEATURE(vdsp64)"
 {
  emit_insn(gen_vashl<mode>3(operands[0], operands[1], operands[2]));
  DONE;
 }
 )

(define_expand "csky_vshls<mode>"
 [(match_operand:V64QHSI      0 "register_operand")
  (match_operand:V64QHSI      1 "register_operand")
  (match_operand:V64QHSI      2 "register_operand")]
 "CSKY_ISA_FEATURE(vdsp64)"
 {
  emit_insn(gen_vashl<mode>3(operands[0], operands[1], operands[2]));
  DONE;
 }
 )

(define_expand "csky_vshliu<mode>"
  [(match_operand:V64QHSI                0 "register_operand")
   (match_operand:V64QHSI 1 "register_operand")
   (match_operand:SI 2 "immediate_operand" )]
 "CSKY_ISA_FEATURE(vdsp64)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vashl<mode>3(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshlis<mode>"
  [(match_operand:V64QHSI  0 "register_operand" )
   (match_operand:V64QHSI 1 "register_operand" )
   (match_operand:SI 2 "immediate_operand" )]
 "CSKY_ISA_FEATURE(vdsp64)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vashl<mode>3(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshriu<mode>"
  [(match_operand:V64QHSI                0 "register_operand")
   (match_operand:V64QHSI 1 "register_operand")
   (match_operand:SI 2 "immediate_operand" )]
 "CSKY_ISA_FEATURE(vdsp64)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vlshr<mode>3(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshris<mode>"
  [(match_operand:V64QHSI  0 "register_operand" )
   (match_operand:V64QHSI 1 "register_operand" )
   (match_operand:SI 2 "immediate_operand" )]
 "CSKY_ISA_FEATURE(vdsp64)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vashr<mode>3(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshlius<mode>"
  [(match_operand:V64QHSI                0 "register_operand")
   (match_operand:V64QHSI 1 "register_operand")
   (match_operand:SI 2 "immediate_operand" )]
  "CSKY_ISA_FEATURE(vdsp64)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vshlus<mode>(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshliss<mode>"
  [(match_operand:V64QHSI  0 "register_operand" )
   (match_operand:V64QHSI 1 "register_operand" )
   (match_operand:SI 2 "immediate_operand" )]
  "CSKY_ISA_FEATURE(vdsp64)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vshlss<mode>(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

;; Instructions use format: insn vrx,vry,vrz
;; And only has mode v8qi
;; vrx = f(vry, vrz)

(define_insn "csky_<insnvvv1>v8qi"
  [(set (match_operand:V8QI 0 "register_operand" "=w")
        (unspec:V8QI  [(match_operand:V8QI 1 "register_operand"  "w")
                       (match_operand:V8QI 2 "register_operand"  "w")]
                       INSNVVV1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv1>.8\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v8qi v4hi v2si
;; vry = f(vrx)

(define_expand "csky_vcmpnezs<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (match_operand:V64QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp64)"
{
  emit_insn(gen_vcmpnez<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmpnezu<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
            (match_operand:V64QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp64)"
{
  emit_insn(gen_vcmpnez<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmphszs<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (match_operand:V64QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp64)"
{ 
  emit_insn(gen_vcmphsz<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmpltzs<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (match_operand:V64QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp64)"
{
  emit_insn(gen_vcmpltz<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmphszu<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (match_operand:V64QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp64)"
{
  emit_insn(gen_vcmphszu<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmpltzu<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (match_operand:V64QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp64)"
{
  emit_insn(gen_vcmpltzu<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_insn "vcmp<vcmps1_attr>z<mode>_internal"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (VCMPS1:V64QHSI
          (match_operand:V64QHSI 1 "register_operand" "w")
          (match_operand:V64QHSI 2 "zero_operand" "i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "* switch(<CODE>){
  case GE:
  case LT:
    return \"vcmp<vcmps1_attr>z.s<sup3>\\t%0, %1\";
  case NE:
    return \"vcmp<vcmps1_attr>z.u<sup3>\\t%0, %1\";
  default:
    gcc_unreachable();
  }")

(define_insn "vcmp<vcmpu3_attr>zu<mode>_internal"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (VCMPU3:V64QHSI
          (match_operand:V64QHSI 1 "register_operand" "w")
          (match_operand:V64QHSI 2 "zero_operand" "i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "* switch(<CODE>){
  case GEU:
  case LTU:
    return \"vcmp<vcmpu3_attr>z.u<sup3>\\t%0, %1\";
  default:
    gcc_unreachable();
  }")

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8qi v4hi
;; vrx = f(vry, vrz)

(define_insn "csky_<insnvvv2>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=w")
        (unspec:<vexmode> [(match_operand:V64QHI 1 "register_operand"  "w")
                           (match_operand:V64QHI 2 "register_operand"  "w")]
                           INSNVVV2))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv2>.e<sup2><sup3>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8qi v4hi
;; vrx = f(vrx, vry, vrz)

(define_insn "csky_<insnvvv3>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=w")
        (unspec:<vexmode> [(match_operand:V64QHI 1 "register_operand"  "w")
                           (match_operand:V64QHI 2 "register_operand"  "w")
                           (match_operand:<vexmode> 3 "register_operand"  "0")]
                           INSNVVV3))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv3>.e<sup2><sup3>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v4hi v2si
;; vrx = f(vry, vrz)

(define_insn "csky_<insnvvv4>x<sup4><sup2><mode>"
  [(set (match_operand:V64HSI 0 "register_operand" "=w")
        (unspec:V64HSI [(match_operand:<vhalfmode> 1 "register_operand"  "w")
                        (match_operand:V64HSI 2 "register_operand"  "w")]
                         INSNVVV4))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv4>.x<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_<insnvvv4_1>x<sup4><sup2><mode>"
  [(set (match_operand:<vhalfmode> 0 "register_operand" "=w")
        (unspec:<vhalfmode> [(match_operand:<vhalfmode> 1 "register_operand"  "w")
                             (match_operand:V64HSI 2 "register_operand"  "w")]
                             INSNVVV4_1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv4_1>.x<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8qi v4hi v2si
;; vrx = f(vry, vrz)

(define_insn "csky_<insnvvv5><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=w")
        (unspec:V64QHSI  [(match_operand:V64QHSI 1 "register_operand"  "w")
                          (match_operand:V64QHSI 2 "register_operand"  "w")]
                          INSNVVV5))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv5>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_<insnvvv7><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=w")
        (unspec:V64QHSI  [(match_operand:V64QHSI 1 "register_operand"  "w")
                          (match_operand:V64QHSI 2 "register_operand"  "w")]
                          INSNVVV7))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv7>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_<insnvvv7_1a><sup4><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=w")
        (unspec:V64QHSI [(match_operand:V64QHSI 1 "register_operand"  "w")
                          (match_operand:V64QHSI 2 "register_operand"  "w")]
                          INSNVVV7_1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv7_1>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_vandn<mode>"
  [(set (match_operand:V64QHSI               0 "register_operand" "=w")
        (and:V64QHSI (not:V64QHSI(match_operand:V64QHSI 1 "register_operand" "w"))
                     (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vandn.<sup3>\t%0, %2, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "csky_vcmps<vcmps1_attr><mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (VCMPS1:V64QHSI
          (match_operand:V64QHSI 1 "register_operand" "w")
          (match_operand:V64QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "*
  switch(<CODE>){
    case LT:
    case GE:
      return \"vcmp<vcmps1_attr>.s<sup3>\\t%0, %1, %2\";
    case NE:
      return \"vcmp<vcmps1_attr>.u<sup3>\\t%0, %1, %2\";
    default:
      gcc_unreachable();
  }
  ")

(define_insn "csky_vcmpu<vcmpu1_attr><mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (VCMPU1:V64QHSI
          (match_operand:V64QHSI 1 "register_operand" "w")
          (match_operand:V64QHSI 2 "register_operand"  "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
 "*
 switch(<CODE>){
  case LTU:
  case GEU:
  case NE:
    return \"vcmp<vcmpu1_attr>.u<sup3>\\t%0, %1, %2\";
  default:
    gcc_unreachable();
    }
 ")

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8qi v4hi v2si
;; vrx = f(vrx, vry, vrz)

(define_insn "csky_vsabsas<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (unspec:V64QHSI [(match_operand:V64QHSI 1 "register_operand"  "w")
                         (match_operand:V64QHSI 2 "register_operand"  "w")
                         (match_operand:V64QHSI 3 "register_operand"  "w")]
                         UNSPEC_VSABSAS))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsabsa.s<sup3>\t%0, %2, %3"
)

(define_insn "csky_vsabsau<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (unspec:V64QHSI [(match_operand:V64QHSI 1 "register_operand"  "w")
                         (match_operand:V64QHSI 2 "register_operand"  "w")
                         (match_operand:V64QHSI 3 "register_operand"  "w")]
                         UNSPEC_VSABSAU))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsabsa.u<sup3>\t%0, %2, %3"
)

(define_expand "csky_vabs<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_abs<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "csky_vabsss<mode>" 
  [(set (match_operand:V64QHSI                  0 "register_operand" "=w")
        (ss_abs:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vabs.s<sup3>.s\t%0, %1"
)

(define_expand "csky_vmov<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_mov<mode> (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_vneg<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_neg<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_vnegs<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_ssneg<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_vcnt1uv8qi"
  [(match_operand:V8QI 0 "register_operand" "")
   (match_operand:V8QI 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_csky_vcnt1sv8qi (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "csky_vcnt1sv8qi"
  [(set (match_operand:V8QI 0 "register_operand" "=w")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand"  "w")]
                       UNSPEC_VCNT1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vcnt1.8\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v8qi v4hi
;; vrx = f(vry)

(define_insn "csky_<insnvv1>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=w")
        (unspec:<vexmode> [(match_operand:V64QHI 1 "register_operand"  "w")]
                           INSNVV1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv1>.e<sup2><sup3>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v8qi v4hi
;; vrx = f(vrx, vry)

(define_insn "csky_<insnvv2>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=w")
        (unspec:<vexmode>  [(match_operand:V64QHI 1 "register_operand"  "w")
                            (match_operand:V64QHI 2 "register_operand"  "0")]
                            INSNVV2))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv2>.e<sup2><sup3>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v4hi v2si
;; vrx = f(vry)

(define_insn "csky_<insnvv3><sup4><sup2><mode>"
  [(set (match_operand:<vhalfmode> 0 "register_operand" "=w")
        (unspec:<vhalfmode> [(match_operand:V64HSI 1 "register_operand"  "w")]
                             INSNVV3))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv3>.<sup2><sup3><dot><sup4>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v8qi v4hi v2si
;; vrx = f(vry)

(define_insn "csky_<insnvv4><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (unspec:V64QHSI [(match_operand:V64QHSI 1 "register_operand"  "w")]
                          INSNVV4))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv4>.<sup2><sup3><dot><sup4>\t%0, %1"
)

(define_insn "csky_vrev<mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=w")
        (unspec:V64QHSI [(match_operand:V64QHSI 1 "register_operand"  "w")]
                          UNSPEC_VREV))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vrev.<sup3>\t%0, %1"
)

;; Instructions use format: insn vrx,vry[index]
;; And has mode: v8qi v4hi v2si
;; vrx = f(vry[index])

(define_insn "csky_vdup<mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand"  "=w")
        (unspec:V64QHSI [(match_operand:V64QHSI  1 "register_operand"  "w")
                          (match_operand:SI      2 "immediate_operand" "i")]
                          UNSPEC_VDUP))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vdup.<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx,(ry, offset)
;; And has mode: v16qi v8hi v4si
;; vrx = f(ry, offset)

(define_insn "csky_<insnvgo1><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=w")
        (unspec:V64QHSI  [(match_operand:SI      1 "register_operand"  "r")
                          (match_operand:SI      2 "immediate_operand" "i")]
                          INSNVGO1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvgo1>.<sup3>\t%0, (%1, %2)"
)

;; Instructions use format: insn vrx,(ry, rz, shift)
;; And has mode: v8qi v4hi v2si
;; vrx = f(ry, rz, shift)

(define_insn "csky_<insnvggs1><mode>"
  [(set (match_operand:V64QHSI                    0 "register_operand" "=w")
        (unspec:V64QHSI  [(match_operand:SI       1 "register_operand"  "r")
                          (match_operand:SI       2 "register_operand"  "r")
                          (match_operand:SI       3 "immediate_operand" "i")]
                          INSNVGGS1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvggs1>.<sup3>\t%0, (%1, %2<<%3)"
)

;; Instructions use format: insn vrx[index1],vry[index2]
;; And has mode: v8qi v4hi v2si
;; vrx = f(vrx[index1],vry[index2])

(define_insn "csky_vins<mode>"
  [(set (match_operand:V64QHSI                    0 "register_operand"  "=w")
        (unspec:V64QHSI  [(match_operand:SI       1 "immediate_operand" "i")
                          (match_operand:V64QHSI  2 "register_operand"  "w")
                          (match_operand:SI       3 "immediate_operand" "i")]
                          UNSPEC_VINS))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vins.<sup3>\t%0[%1], %2[%3]"
)

;; Instructions use format: insn rx,vry[index]
;; And has mode: v8qi v4hi v2si
;; rx = f(vry[index])

(define_insn "csky_vmfvru<mode>"
  [(set (match_operand:<vtoimode>                   0 "register_operand"  "=r")
        (unspec:<vtoimode> [(match_operand:V64QHSI 1 "register_operand"  "w")
                            (match_operand:SI       2 "immediate_operand" "i")]
                            UNSPEC_VMFVRU))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmfvr.u<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx[index], ry
;; And has mode: v8qi v4hi v2si
;; vrx = f(index, ry)

(define_insn "csky_vmtvru<mode>"
  [(set (match_operand:V64QHSI                     0 "register_operand"  "=w")
        (unspec:V64QHSI [(match_operand:SI         1 "immediate_operand"  "i")
                          (match_operand:<vtoimode> 2 "register_operand"  "r")]
                          UNSPEC_VMTVRU))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmtvr.u<sup3>\t%0[%1], %2"
)

;; Instructions use format: insn rx,vry[index]
;; And has mode: v8qi v4hi
;; rx = f(vry[index])

(define_insn "csky_vmfvrs<mode>"
  [(set (match_operand:<vtoimode>                   0 "register_operand"  "=r")
        (unspec:<vtoimode> [(match_operand:V64QHI  1 "register_operand"  "w")
                            (match_operand:SI       2 "immediate_operand" "i")]
                            UNSPEC_VMFVRS))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmfvr.s<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx, vry, imm5
;; And has mode: v8qi v4hi v2si
;; vrx = f(vry, imm5)

(define_insn "csky_<insnvvi><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand"  "=w")
        (unspec:V64QHSI [(match_operand:V64QHSI  1 "register_operand"  "w")
                         (match_operand:SI       2 "immediate_operand" "i")]
                         INSNVVI))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvi>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_expand "csky_vshlus<mode>"
  [(match_operand:V64QHSI 0 "register_operand")
   (match_operand:V64QHSI 1 "register_operand")
   (match_operand:V64QHSI 2 "register_operand")]
  "CSKY_ISA_FEATURE(vdsp64)"
 {
   emit_insn(gen_vshlus<mode>(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshlss<mode>"
  [(match_operand:V64QHSI 0 "register_operand" )
   (match_operand:V64QHSI 1 "register_operand" )
   (match_operand:V64QHSI 2 "register_operand" )]
  "CSKY_ISA_FEATURE(vdsp64)"
 {
   emit_insn(gen_vshlss<mode>(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_insn "vshlus<mode>"
  [(set (match_operand:V64QHSI                0 "register_operand" "=w, w")
        (us_ashift:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w, w")
                             (match_operand:V64QHSI 2 "imm_lshift_or_reg_vdspv2" "w, i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    switch(which_alternative)
    {
      case 0: return "vshl.u<sup3>.s\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshli",'u',".s",&operands[2],
                                                   <MODE>mode, 1, 0);
      default:gcc_unreachable();
    }
  }
 )

(define_insn "vshlss<mode>"
  [(set (match_operand:V64QHSI                0 "register_operand" "=w, w")
        (ss_ashift:V64QHSI (match_operand:V64QHSI 1 "register_operand" "w,w")
                           (match_operand:V64QHSI 2 "imm_lshift_or_reg_vdspv2" "w, i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    switch(which_alternative)
    {
      case 0: return "vshl.s<sup3>.s\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshli",'s',".s",&operands[2],
                                                   <MODE>mode, 1, 0);
      default:gcc_unreachable();
    }
  }
 )
