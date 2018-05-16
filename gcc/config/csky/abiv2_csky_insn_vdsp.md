;; ------------------------------------------------------------
;; Common insn iterator
;; ------------------------------------------------------------

(define_mode_iterator VANY   [V4SI  V8HI  V16QI
                              V4SQ  V8HQ  V16QQ
                              V4USQ V8UHQ V16UQQ

                              V2SI  V4HI  V8QI
                              V2SQ  V4HQ  V8QQ
                              V2USQ V4UHQ V8UQQ])

(define_mode_iterator V128ALL [V4SI  V8HI  V16QI
                               V4SQ  V8HQ  V16QQ
                               V4USQ V8UHQ V16UQQ])

(define_mode_iterator V128QHI [V16QI V8HI])
(define_mode_iterator V128HSI [V8HI  V4SI])
(define_mode_iterator V128QHSI [V16QI V8HI  V4SI])
(define_mode_iterator V128QHSQ [V16QQ V8HQ V4SQ])
(define_mode_iterator V128UQHSQ [V16UQQ V8UHQ V4USQ])

(define_mode_iterator V64ALL [V2SI  V4HI  V8QI
                              V2SQ  V4HQ  V8QQ
                              V2USQ V4UHQ V8UQQ])

(define_mode_iterator V64QHI [V8QI V4HI])
(define_mode_iterator V64HSI [V4HI  V2SI])
(define_mode_iterator V64QHSI [V8QI V4HI  V2SI])
(define_mode_iterator V64QHSQ [V8QQ V4HQ V2SQ])
(define_mode_iterator V64UQHSQ [V8UQQ V4UHQ V2USQ])

(define_mode_iterator V32QHIV64SI [V2HI V4QI V2SI])
(define_mode_iterator V32QHQ      [V2HQ V4QQ])
(define_mode_iterator V32UQHQ     [V2UHQ V4UQQ])
(define_mode_iterator V32HIHQ  [V2HI V2HQ V2UHQ])
(define_mode_iterator V32QHI   [V2HI V4QI])

(define_mode_attr sup3 [
  (V16QI "8") (V8HI "16")   (V4SI "32")
  (V16QQ "8") (V8HQ "16")   (V4SQ "32")
  (V16UQQ "8") (V8UHQ "16") (V4USQ "32")
  (V8QI "8") (V4HI "16")   (V2SI "32")
  (V8QQ "8") (V4HQ "16")   (V2SQ "32")
  (V8UQQ "8") (V4UHQ "16") (V2USQ "32")
  (V4QI "8") (V2HI "16")
  (V4QQ "8") (V2HQ "16")
  (V4UQQ "8") (V2UHQ "16")
])

(define_mode_attr vtoimode [(V4SI "SI") (V8HI "HI") (V16QI "QI")
                            (V2SI "SI") (V4HI "HI") (V8QI "QI")])

(define_mode_attr vexmode [(V8HI "V4SI") (V16QI "V8HI")
                           (V4HI "V2SI") (V8QI "V4HI")])

(define_mode_attr vhalfmode [(V8HI "V16QI") (V4SI "V8HI")
                             (V4HI "V8QI") (V2SI "V4HI")])

(define_int_attr sup2 [
  (UNSPEC_VADDEU     "u")
  (UNSPEC_VADDES     "s")
  (UNSPEC_VMULEU     "u")
  (UNSPEC_VMULES     "s")
  (UNSPEC_VMULAEU    "u")
  (UNSPEC_VMULAES    "s")
  (UNSPEC_VMULSEU    "u")
  (UNSPEC_VMULSES    "s")
  (UNSPEC_VSABSEU    "u")
  (UNSPEC_VSABSES    "s")
  (UNSPEC_VSABSAEU   "u")
  (UNSPEC_VSABSAES   "s")
  (UNSPEC_VSUBEU     "u")
  (UNSPEC_VSUBES     "s")
  (UNSPEC_VADDXU	   "u")
  (UNSPEC_VADDXS	   "s")
  (UNSPEC_VADDXSLU   "u")
  (UNSPEC_VADDXSLS   "s")
  (UNSPEC_VSUBXU     "u")
  (UNSPEC_VSUBXS     "s")
  (UNSPEC_VADDHU     "u")
  (UNSPEC_VADDHS     "s")
  (UNSPEC_VADDHRU    "u")
  (UNSPEC_VADDHRS    "s")
  (UNSPEC_VANDN      "")
  (UNSPEC_VCADDU     "u")
  (UNSPEC_VCADDS     "s")
  (UNSPEC_VCMAXU     "u")
  (UNSPEC_VCMAXS     "s")
  (UNSPEC_VCMINU     "u")
  (UNSPEC_VCMINS     "s")
  (UNSPEC_VCMPHSU    "u")
  (UNSPEC_VCMPHSS    "s")
  (UNSPEC_VCMPHSZU   "u")
  (UNSPEC_VCMPHSZS   "s")
  (UNSPEC_VCMPLTU    "u")
  (UNSPEC_VCMPLTS    "s")
  (UNSPEC_VCMPLTZU   "u")
  (UNSPEC_VCMPLTZS   "s")
  (UNSPEC_VCMPNEU    "u")
  (UNSPEC_VCMPNES    "s")
  (UNSPEC_VCMPNEZU   "u")
  (UNSPEC_VCMPNEZS   "s")
  (UNSPEC_VDCH       "")
  (UNSPEC_VDCL       "")
  (UNSPEC_VICH       "")
  (UNSPEC_VICL       "")
  (UNSPEC_VNOR       "")
  (UNSPEC_VSABSU     "u")
  (UNSPEC_VSABSS     "s")
  (UNSPEC_VSABSAU    "u")
  (UNSPEC_VSABSAS    "s")
  (UNSPEC_VSHLU      "u")
  (UNSPEC_VSHLS      "s")
  (UNSPEC_VSHRU      "u")
  (UNSPEC_VSHRS      "s")
  (UNSPEC_VSHRRU     "u")
  (UNSPEC_VSHRRS     "s")
  (UNSPEC_VSUBHU     "u")
  (UNSPEC_VSUBHS     "s")
  (UNSPEC_VSUBHRU    "u")
  (UNSPEC_VSUBHRS    "s")
  (UNSPEC_VTRCH      "")
  (UNSPEC_VTRCL      "")
  (UNSPEC_VTST       "")
  (UNSPEC_VCADDEU    "u")
  (UNSPEC_VCADDES    "s")
  (UNSPEC_VMOVEU     "u")
  (UNSPEC_VMOVES     "s")
  (UNSPEC_VMOVHU     "u")
  (UNSPEC_VMOVHS     "s")
  (UNSPEC_VMOVLU     "u")
  (UNSPEC_VMOVLS     "s")
  (UNSPEC_VMOVRHU    "u")
  (UNSPEC_VMOVRHS    "s")
  (UNSPEC_VMOVSLU    "u")
  (UNSPEC_VMOVSLS    "s")
  (UNSPEC_VCLSS      "s")
  (UNSPEC_VCLZ       "")
  (UNSPEC_VREV       "")
  (UNSPEC_VSTOUSLS   "s")
  (UNSPEC_VMFVRU     "u")
  (UNSPEC_VMFVRS     "s")
  (UNSPEC_VMTVRU     "u")
  (UNSPEC_VSHLIU     "u")
  (UNSPEC_VSHLIS     "s")
  (UNSPEC_VSHRIU     "u")
  (UNSPEC_VSHRIS     "s")
  (UNSPEC_VSHRIRU    "u")
  (UNSPEC_VSHRIRS    "s")
  (UNSPEC_PADDH_S "s") (UNSPEC_PADDH_U "u")
  (UNSPEC_PSUBH_S "s") (UNSPEC_PSUBH_U "u")
  (UNSPEC_PASXH_S "s") (UNSPEC_PASXH_U "u")
  (UNSPEC_PSAXH_S "s") (UNSPEC_PSAXH_U "u")
  (UNSPEC_CLIPS   "s") (UNSPEC_CLIPU   "u")
  (UNSPEC_PCLIPS  "s") (UNSPEC_PCLIPU  "u")
  (UNSPEC_PEXTXS8 "s") (UNSPEC_PEXTXU8 "u")
  (UNSPEC_PMULXS  "s") (UNSPEC_PMULXU  "u")
  (UNSPEC_PLSLISS "s") (UNSPEC_PLSLIUS "u")
  (UNSPEC_PLSLSS  "s") (UNSPEC_PLSLUS  "u")
  (UNSPEC_PASRIR  "s") (UNSPEC_PLSRIR  "u")
  (UNSPEC_PASRR   "s") (UNSPEC_PLSRR   "u")
])

(define_code_attr codesup2 [
  (lt "s") (ltu "u")
  (ge "s") (geu "u")
  ])

(define_mode_attr modesup2 [
  (V2HI "") (V2HQ "s") (V2UHQ "u")
])

(define_int_attr dot [
  (UNSPEC_VADDEU     "")
  (UNSPEC_VADDES     "")
  (UNSPEC_VMULEU     "")
  (UNSPEC_VMULES     "")
  (UNSPEC_VMULAEU    "")
  (UNSPEC_VMULAES    "")
  (UNSPEC_VMULSEU    "")
  (UNSPEC_VMULSES    "")
  (UNSPEC_VSABSEU    "")
  (UNSPEC_VSABSES    "")
  (UNSPEC_VSABSAEU   "")
  (UNSPEC_VSABSAES   "")
  (UNSPEC_VSUBEU     "")
  (UNSPEC_VSUBES     "")
  (UNSPEC_VADDXU	   "")
  (UNSPEC_VADDXS	   "")
  (UNSPEC_VADDXSLU   ".")
  (UNSPEC_VADDXSLS   ".")
  (UNSPEC_VSUBXU     "")
  (UNSPEC_VSUBXS     "")
  (UNSPEC_VADDHU     "")
  (UNSPEC_VADDHS     "")
  (UNSPEC_VADDHRU    ".")
  (UNSPEC_VADDHRS    ".")
  (UNSPEC_VANDN      "")
  (UNSPEC_VCADDU     "")
  (UNSPEC_VCADDS     "")
  (UNSPEC_VCMAXU     "")
  (UNSPEC_VCMAXS     "")
  (UNSPEC_VCMINU     "")
  (UNSPEC_VCMINS     "")
  (UNSPEC_VCMPHSU    "")
  (UNSPEC_VCMPHSS    "")
  (UNSPEC_VCMPHSZU   "")
  (UNSPEC_VCMPHSZS   "")
  (UNSPEC_VCMPLTU    "")
  (UNSPEC_VCMPLTS    "")
  (UNSPEC_VCMPLTZU   "")
  (UNSPEC_VCMPLTZS   "")
  (UNSPEC_VCMPNEU    "")
  (UNSPEC_VCMPNES    "")
  (UNSPEC_VCMPNEZU   "")
  (UNSPEC_VCMPNEZS   "")
  (UNSPEC_VDCH       "")
  (UNSPEC_VDCL       "")
  (UNSPEC_VICH       "")
  (UNSPEC_VICL       "")
  (UNSPEC_VNOR       "")
  (UNSPEC_VSABSU     "")
  (UNSPEC_VSABSS     "")
  (UNSPEC_VSABSAU    "")
  (UNSPEC_VSABSAS    "")
  (UNSPEC_VSHLU      "")
  (UNSPEC_VSHLS      "")
  (UNSPEC_VSHRU      "")
  (UNSPEC_VSHRS      "")
  (UNSPEC_VSHRRU     ".")
  (UNSPEC_VSHRRS     ".")
  (UNSPEC_VSUBHU     "")
  (UNSPEC_VSUBHS     "")
  (UNSPEC_VSUBHRU    ".")
  (UNSPEC_VSUBHRS    ".")
  (UNSPEC_VTRCH      "")
  (UNSPEC_VTRCL      "")
  (UNSPEC_VTST       "")
  (UNSPEC_VCADDEU    "")
  (UNSPEC_VCADDES    "")
  (UNSPEC_VMOVEU     "")
  (UNSPEC_VMOVES     "")
  (UNSPEC_VMOVHU     ".")
  (UNSPEC_VMOVHS     ".")
  (UNSPEC_VMOVLU     ".")
  (UNSPEC_VMOVLS     ".")
  (UNSPEC_VMOVRHU    ".")
  (UNSPEC_VMOVRHS    ".")
  (UNSPEC_VMOVSLU    ".")
  (UNSPEC_VMOVSLS    ".")
  (UNSPEC_VCLSS      "")
  (UNSPEC_VCLZ       "")
  (UNSPEC_VREV       "")
  (UNSPEC_VSTOUSLS   ".")
  (UNSPEC_VSHLIU     "")
  (UNSPEC_VSHLIS     "")
  (UNSPEC_VSHRIU     "")
  (UNSPEC_VSHRIS     "")
  (UNSPEC_VSHRIRU    ".")
  (UNSPEC_VSHRIRS    ".")
  (UNSPEC_MULCA      ".")
  (UNSPEC_MULCAX     ".")
  (UNSPEC_MULCS      "")
  (UNSPEC_MULCSR     "")
  (UNSPEC_MULCSX     "")
  (UNSPEC_MULACA     ".")
  (UNSPEC_MULACAX    ".")
  (UNSPEC_MULACS     ".")
  (UNSPEC_MULACSR    ".")
  (UNSPEC_MULACSX    ".")
  (UNSPEC_MULSCA     ".")
  (UNSPEC_MULSCAX    ".")
])

(define_mode_attr modedot [
  (V2HI "") (V2HQ ".") (V2UHQ ".")
])

(define_int_attr sup4 [
  (UNSPEC_VADDEU     "")
  (UNSPEC_VADDES     "")
  (UNSPEC_VMULEU     "")
  (UNSPEC_VMULES     "")
  (UNSPEC_VMULAEU    "")
  (UNSPEC_VMULAES    "")
  (UNSPEC_VMULSEU    "")
  (UNSPEC_VMULSES    "")
  (UNSPEC_VSABSEU    "")
  (UNSPEC_VSABSES    "")
  (UNSPEC_VSABSAEU   "")
  (UNSPEC_VSABSAES   "")
  (UNSPEC_VSUBEU     "")
  (UNSPEC_VSUBES     "")
  (UNSPEC_VADDXU	   "")
  (UNSPEC_VADDXS	   "")
  (UNSPEC_VADDXSLU   "sl")
  (UNSPEC_VADDXSLS   "sl")
  (UNSPEC_VSUBXU     "")
  (UNSPEC_VSUBXS     "")
  (UNSPEC_VADDHU     "")
  (UNSPEC_VADDHS     "")
  (UNSPEC_VADDHRU    "r")
  (UNSPEC_VADDHRS    "r")
  (UNSPEC_VANDN      "")
  (UNSPEC_VCADDU     "")
  (UNSPEC_VCADDS     "")
  (UNSPEC_VCMAXU     "")
  (UNSPEC_VCMAXS     "")
  (UNSPEC_VCMINU     "")
  (UNSPEC_VCMINS     "")
  (UNSPEC_VCMPHSU    "")
  (UNSPEC_VCMPHSS    "")
  (UNSPEC_VCMPHSZU   "")
  (UNSPEC_VCMPHSZS   "")
  (UNSPEC_VCMPLTU    "")
  (UNSPEC_VCMPLTS    "")
  (UNSPEC_VCMPLTZU   "")
  (UNSPEC_VCMPLTZS   "")
  (UNSPEC_VCMPNEU    "")
  (UNSPEC_VCMPNES    "")
  (UNSPEC_VCMPNEZU   "")
  (UNSPEC_VCMPNEZS   "")
  (UNSPEC_VDCH       "")
  (UNSPEC_VDCL       "")
  (UNSPEC_VICH       "")
  (UNSPEC_VICL       "")
  (UNSPEC_VNOR       "")
  (UNSPEC_VSABSU     "")
  (UNSPEC_VSABSS     "")
  (UNSPEC_VSABSAU    "")
  (UNSPEC_VSABSAS    "")
  (UNSPEC_VSHLU      "")
  (UNSPEC_VSHLS      "")
  (UNSPEC_VSHRU      "")
  (UNSPEC_VSHRS      "")
  (UNSPEC_VSHRRU     "r")
  (UNSPEC_VSHRRS     "r")
  (UNSPEC_VSUBHU     "")
  (UNSPEC_VSUBHS     "")
  (UNSPEC_VSUBHRU    "r")
  (UNSPEC_VSUBHRS    "r")
  (UNSPEC_VTRCH      "")
  (UNSPEC_VTRCL      "")
  (UNSPEC_VTST       "")
  (UNSPEC_VCADDEU    "")
  (UNSPEC_VCADDES    "")
  (UNSPEC_VMOVEU     "")
  (UNSPEC_VMOVES     "")
  (UNSPEC_VMOVHU     "h")
  (UNSPEC_VMOVHS     "h")
  (UNSPEC_VMOVLU     "l")
  (UNSPEC_VMOVLS     "l")
  (UNSPEC_VMOVRHU    "rh")
  (UNSPEC_VMOVRHS    "rh")
  (UNSPEC_VMOVSLU    "sl")
  (UNSPEC_VMOVSLS    "sl")
  (UNSPEC_VCLSS      "")
  (UNSPEC_VCLZ       "")
  (UNSPEC_VREV       "")
  (UNSPEC_VSTOUSLS   "sl")
  (UNSPEC_VSHLIU     "")
  (UNSPEC_VSHLIS     "")
  (UNSPEC_VSHRIU     "")
  (UNSPEC_VSHRIS     "")
  (UNSPEC_VSHRIRU    "r")
  (UNSPEC_VSHRIRS    "r")
  (UNSPEC_MULCA      "s")
  (UNSPEC_MULCAX     "s")
  (UNSPEC_MULCS      "")
  (UNSPEC_MULCSR     "")
  (UNSPEC_MULCSX     "")
  (UNSPEC_MULACA     "s")
  (UNSPEC_MULACAX    "s")
  (UNSPEC_MULACS     "s")
  (UNSPEC_MULACSR    "s")
  (UNSPEC_MULACSX    "s")
  (UNSPEC_MULSCA     "s")
  (UNSPEC_MULSCAX    "s")
])

(define_mode_attr modesup4 [
  (V2HI "") (V2HQ "s") (V2UHQ "s")
])

(define_mode_attr sup1 [(V2HI "p") (V4QI "p") (V2SI "")
                        (V2HQ "p") (V4QQ "p") (V2SQ "") (SQ "")
                        (V2UHQ "p") (V4UQQ "p") (V2USQ "") (USQ "") (SI "")])

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
  [(set (match_operand:V32QHQ 0 "register_operand" "=r")
        (ss_plus:V32QHQ (match_operand:V32QHQ 1 "register_operand" "%r")
                        (match_operand:V32QHQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "padd.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "usadd<mode>3"
  [(set (match_operand:V32UQHQ 0 "register_operand" "=r")
        (us_plus:V32UQHQ (match_operand:V32UQHQ 1 "register_operand" "%r")
                         (match_operand:V32UQHQ 2 "register_operand" "r")))]
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
  [(set (match_operand:V32QHQ 0 "register_operand" "=r")
        (ss_minus:V32QHQ (match_operand:V32QHQ 1 "register_operand" "%r")
                         (match_operand:V32QHQ 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psub.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ussub<mode>3"
  [(set (match_operand:V32UQHQ 0 "register_operand" "=r")
        (us_minus:V32UQHQ (match_operand:V32UQHQ 1 "register_operand" "%r")
                          (match_operand:V32UQHQ 2 "register_operand" "r")))]
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
  [(set (match_operand:V2HQ 0 "register_operand" "")
        (ashift:V2HQ (match_operand:V2HQ 1 "register_operand" "")
                       (match_operand:SI 2 "nonmemory_operand" "")))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    if (CONST_INT_P (operands[2])
        && !IN_RANGE (INTVAL (operands[2]), 1, 16))
      operands[2] = force_reg (SImode, operands[2]);
  }
)

(define_insn "*lshlim_sat"
  [(set (match_operand:V2HQ 0 "register_operand" "=r")
        (ashift:V2HQ (match_operand:V2HQ 1 "register_operand" "r")
                       (match_operand:SI   2 "const_1_to_16_operand" "i")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsli.16.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*lshlre_sat"
  [(set (match_operand:V2HQ 0 "register_operand" "=r")
        (ashift:V2HQ (match_operand:V2HQ 1 "register_operand" "r")
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

(define_expand "csky_padd<mode>"
  [(match_operand:V32QHQ 0 "register_operand" "")
   (match_operand:V32QHQ 1 "register_operand" "")
   (match_operand:V32QHQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_ssadd<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_padd<mode>"
  [(match_operand:V32UQHQ 0 "register_operand" "")
   (match_operand:V32UQHQ 1 "register_operand" "")
   (match_operand:V32UQHQ 2 "register_operand" "")]
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

(define_expand "csky_psub<mode>"
  [(match_operand:V32QHQ 0 "register_operand" "")
   (match_operand:V32QHQ 1 "register_operand" "")
   (match_operand:V32QHQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_sssub<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_psub<mode>"
  [(match_operand:V32UQHQ 0 "register_operand" "")
   (match_operand:V32UQHQ 1 "register_operand" "")
   (match_operand:V32UQHQ 2 "register_operand" "")]
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

(define_insn "csky_plslissv2hq"
  [(set (match_operand:V2HQ 0 "register_operand" "=r")
        (unspec:V2HQ [(match_operand:V2HQ 1 "register_operand" "r")
                      (match_operand:SI   2 "const_1_to_16_operand" "i")]
                      UNSPEC_PLSLISS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsli.s16.s\t%0, %1, %2"
)

(define_insn "csky_plsliusv2uhq"
  [(set (match_operand:V2UHQ 0 "register_operand" "=r")
        (unspec:V2UHQ [(match_operand:V2UHQ 1 "register_operand" "r")
                       (match_operand:SI   2 "const_1_to_16_operand" "i")]
                       UNSPEC_PLSLIUS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsli.u16.s\t%0, %1, %2"
)

(define_insn "csky_plslssv2hq"
  [(set (match_operand:V2HQ 0 "register_operand" "=r")
        (unspec:V2HQ [(match_operand:V2HQ 1 "register_operand" "r")
                      (match_operand:SI   2 "register_operand" "r")]
                      UNSPEC_PLSLSS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "plsl.s16.s\t%0, %1, %2"
)

(define_insn "csky_plslusv2uhq"
  [(set (match_operand:V2UHQ 0 "register_operand" "=r")
        (unspec:V2UHQ [(match_operand:V2UHQ 1 "register_operand" "r")
                       (match_operand:SI   2 "register_operand" "r")]
                       UNSPEC_PLSLSS))]
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

(define_insn "csky_pasx<mode>"
  [(set (match_operand:V32HIHQ 0 "register_operand" "=r")
        (unspec:V32HIHQ [(match_operand:V32HIHQ 1 "register_operand" "r")
                         (match_operand:V32HIHQ 2 "register_operand" "r")]
                         UNSPEC_PASX))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pasx.<modesup2>16<modedot><modesup4>\t%0, %1, %2"
)

(define_insn "csky_psax<mode>"
  [(set (match_operand:V32HIHQ 0 "register_operand" "=r")
        (unspec:V32HIHQ [(match_operand:V32HIHQ 1 "register_operand" "r")
                         (match_operand:V32HIHQ 2 "register_operand" "r")]
                         UNSPEC_PSAX))]
  "CSKY_ISA_FEATURE(dspv2)"
  "psax.<modesup2>16<modedot><modesup4>\t%0, %1, %2"
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
  [(set (match_operand:V32QHQ 0 "register_operand" "=r")
        (ss_abs:V32QHQ (match_operand:V32QHQ 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "pabs.s<sup3>.s\t%0, %1"
)

(define_expand "ssneg<mode>2"
  [(set (match_operand:V32QHQ                0 "register_operand" "=r")
        (ss_neg:V32QHQ (match_operand:V32QHQ 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  {
    emit_insn (gen_csky_ssneg<mode> (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "csky_ssneg<mode>"
  [(set (match_operand:V32QHQ 0 "register_operand" "=r")
        (ss_neg:V32QHQ (match_operand:V32QHQ 1 "register_operand" "r")))]
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

(define_int_iterator PSABS [
  UNSPEC_PSABSA
  UNSPEC_PSABSASA
])

(define_int_attr psabs [
  (UNSPEC_PSABSA    "psabsa")
  (UNSPEC_PSABSASA  "psabsaa")
])

(define_insn "csky_<psabs>v4qi"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:V4QI 1 "register_operand"  "r")
                    (match_operand:V4QI 2 "register_operand"  "r")]
                    PSABS))]
  "CSKY_ISA_FEATURE(dspv2)"
  "<psabs>.u8\t%0, %1, %2"
)

;; ------------------------------------------------------------
;; CK810 Vector DSP insns
;; ------------------------------------------------------------

(define_expand "mov<mode>"
  [(set (match_operand:V128ALL 0 "nonimmediate_operand"  "")
        (match_operand:V128ALL 1 "nonimmediate_operand"  ""))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    if (can_create_pseudo_p ())
      {
        if (!REG_P (operands[0]))
          operands[1] = force_reg (<MODE>mode, operands[1]);
      }
  }
)

(define_insn "*vdsp128_mov<mode>"
  [(set (match_operand:V128ALL 0 "nonimmediate_operand"  "=v,v,m,v,r")
        (match_operand:V128ALL 1 "nonimmediate_operand"  "m,v,v, r,v"))]
  "CSKY_ISA_FEATURE(vdsp128)
   && (register_operand (operands[0], <MODE>mode)
       || register_operand (operands[1], <MODE>mode))"
  "* return output_csky_move_v (operands);"
  [(set_attr "length" "4,4,4,4,4")
   (set_attr "type" "alu,alu,alu,alu,alu")]
)

(define_expand "vec_extract<mode>"
  [(match_operand:<vtoimode> 0 "register_operand")
   (match_operand:V128QHSI   1 "register_operand")
   (match_operand:SI         2 "const_int_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
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

(define_mode_attr vmvrtrmask [(V8HI "7") (V16QI "15")
                              (V4HI "7") (V8QI "15")])

(define_insn "*csky_vec_extracts<mode>"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (sign_extend:SI (vec_select:<vtoimode>
                          (match_operand:V128QHI 1 "register_operand" "v")
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
                          (match_operand:V128QHI 1 "register_operand" "v")
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
          (match_operand:V128QHSI 1 "register_operand" "v")
          (parallel
            [(match_operand:SI 2 "const_0_to_<vmvrtrallmask>_operand")])))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmfvr.u<sup3>\t%0,%1[%2]"
  [(set_attr "length" "4")
   (set_attr "type" "alu")]
)

(define_expand "vec_set<mode>"
  [(match_operand:V128QHSI   0 "register_operand")
   (match_operand:<vtoimode> 1 "register_operand")
   (match_operand            2 "const_int_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
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

(define_code_iterator vscond [ne ge lt])
(define_code_iterator vucond [ne geu ltu])
(define_code_attr vscond_suf [(ne "ne") (ge "hs") (lt "lt")])
(define_code_attr vucond_suf [(ne "ne") (geu "hs") (ltu "lt")])

(define_expand "vec_cmp<mode><mode>"
  [(set (match_operand:V128QHSI    0 "register_operand")
        (match_operator:V128QHSI   1 "csky_scond_operator"
          [(match_operand:V128QHSI 2 "register_operand")
           (match_operand:V128QHSI 3 "reg_or_zero_operand")]))]
  "CSKY_ISA_FEATURE(vdsp128)"
  ""
)

(define_insn "*vec_cmp<vscond_suf><mode>"
  [(set (match_operand:V128QHSI                  0 "register_operand"    "=v,v")
        (vscond:V128QHSI (match_operand:V128QHSI 1 "register_operand"    "v,v")
                         (match_operand:V128QHSI 2 "reg_or_zero_operand" "v,i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "@
   vcmp<vscond_suf>.s<sup3>\t%0,%1,%2
   vcmp<vscond_suf>.s<sup3>z\t%0,%1"
 [(set_attr "type"   "alu")
  (set_attr "length"   "4")])

(define_expand "vec_cmpu<mode><mode>"
  [(set (match_operand:V128QHSI    0 "register_operand")
        (match_operator:V128QHSI   1 "csky_ucond_operator"
          [(match_operand:V128QHSI 2 "register_operand")
           (match_operand:V128QHSI 3 "reg_or_zero_operand")]))]
  "CSKY_ISA_FEATURE(vdsp128)"
  ""
)

(define_insn "*vec_cmp<vucond_suf><mode>"
  [(set (match_operand:V128QHSI                  0 "register_operand" "=v,v")
        (vucond:V128QHSI (match_operand:V128QHSI 1 "register_operand" "v,v")
                     (match_operand:V128QHSI     2 "reg_or_zero_operand" "v,i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "@
   vcmp<vucond_suf>.u<sup3>\t%0,%1,%2
   vcmp<vucond_suf>.u<sup3>z\t%0,%1"
 [(set_attr "type"   "alu")
  (set_attr "length"   "4")])

(define_insn "add<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=v")
        (plus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                      (match_operand:V128QHSI  2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vadd.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ssadd<mode>3"
  [(set (match_operand:V128QHSQ                   0 "register_operand" "=v")
        (ss_plus:V128QHSQ (match_operand:V128QHSQ 1 "register_operand" "%v")
                          (match_operand:V128QHSQ 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vadd.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "usadd<mode>3"
  [(set (match_operand:V128UQHSQ                    0 "register_operand" "=v")
        (us_plus:V128UQHSQ (match_operand:V128UQHSQ 1 "register_operand" "%v")
                           (match_operand:V128UQHSQ 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vadd.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sub<mode>3"
  [(set (match_operand:V128QHSI                 0 "register_operand" "=v")
        (minus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "v")
                       (match_operand:V128QHSI  2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vsub.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sssub<mode>3"
  [(set (match_operand:V128QHSQ                 0 "register_operand" "=v")
        (minus:V128QHSQ (match_operand:V128QHSQ 1 "register_operand" "v")
                       (match_operand:V128QHSQ  2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vsub.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ussub<mode>3"
  [(set (match_operand:V128UQHSQ                  0 "register_operand" "=v")
        (minus:V128UQHSQ (match_operand:V128UQHSQ 1 "register_operand" "v")
                         (match_operand:V128UQHSQ 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vsub.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "and<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=v")
        (and:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                      (match_operand:V128QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vand.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ior<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=v")
        (ior:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                      (match_operand:V128QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "xor<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=v")
        (xor:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                      (match_operand:V128QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vxor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "smax<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=v")
        (smax:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                       (match_operand:V128QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmax.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umax<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=v")
        (umax:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                      (match_operand:V128QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmax.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "smin<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=v")
        (smin:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                      (match_operand:V128QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmin.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umin<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=v")
        (umin:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                      (match_operand:V128QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmin.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "fma<mode>4"
  [(set (match_operand:V128QHSI               0 "register_operand" "=v")
        (fma:V128QHSI (match_operand:V128QHSI 1 "register_operand" "v")
                      (match_operand:V128QHSI 2 "register_operand" "v")
                      (match_operand:V128QHSI 3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmula.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "fms<mode>4"
  [(set (match_operand:V128QHSI               0 "register_operand" "=v")
        (fma:V128QHSI (match_operand:V128QHSI 1 "register_operand" "v")
                      (match_operand:V128QHSI 2 "register_operand" "v")
                      (neg:V128QHSI (match_operand:V128QHSI 3 "register_operand" "0"))))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmuls.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "mul<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=v")
        (mult:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%v")
                       (match_operand:V128QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmul.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "neg<mode>2"
  [(set (match_operand:V128QHSI               0 "register_operand" "=v")
        (neg:V128QHSI (match_operand:V128QHSI 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vneg.s<sup3>\t%0, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ssneg<mode>2"
  [(set (match_operand:V128QHSQ                  0 "register_operand" "=v")
        (ss_neg:V128QHSQ (match_operand:V128QHSQ 1 "register_operand" "v")))]
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
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=v")
;;        (lshiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "v")
;;          (match_operand:SI       2 "register_operand" "r")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshr.u<sup3>\t%0, %1, %2"
;;)

;;(define_insn "csky_lshr3_vdspi<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=v")
;;        (lshiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "v")
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
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=v")
;;        (ashiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "v")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshri.s<sup3>\t%0, %1, %2"
;;)

;;(define_insn "csky_ashr_vdspr<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=v")
;;        (ashiftrt:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "v")
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
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=v")
;;        (ashift:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "v")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshli.u<sup3>\t%0, %1, %2"
;;)
;;(define_insn "csky_ashl_vdspr<mode>"
;;  [(set (match_operand:V128QHSI   0 "register_operand" "=v")
;;        (ashift:V128QHSI
;;          (match_operand:V128QHSI 1 "register_operand" "v")
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
;;  [(set (match_operand:V128QHSQ   0 "register_operand" "=v")
;;        (ashift:V128QHSQ
;;         (match_operand:V128QHSQ 1 "register_operand" "v")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshli.s<sup3>.s\t%0, %1, %2"
;;)

;;(define_insn "csky_ssashl_vdspr<mode>"
;;  [(set (match_operand:V128QHSQ   0 "register_operand" "=v")
;;        (ashift:V128QHSQ
;;          (match_operand:V128QHSQ 1 "register_operand" "v")
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
;;  [(set (match_operand:V128UQHSQ   0 "register_operand" "=v")
;;        (ashift:V128UQHSQ
;;          (match_operand:V128UQHSQ 1 "register_operand" "v")
;;          (match_operand:SI        2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshli.u<sup3>.s\t%0, %1, %2"
;;)

;;(define_insn "csky_usashl_vdspr<mode>"
;;  [(set (match_operand:V128UQHSQ   0 "register_operand" "=v")
;;        (ashift:V128UQHSQ
;;          (match_operand:V128UQHSQ 1 "register_operand" "v")
;;          (match_operand:SI        2 "register_operand" "r")))]
;;  "CSKY_ISA_FEATURE(vdsp128)"
;;  "vshl.u<sup3>.s\t%0, %1, %2"
;;)

(define_insn "abs<mode>2"
  [(set (match_operand:V128QHSI               0 "register_operand" "=v")
        (abs:V128QHSI (match_operand:V128QHSI 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vabs.s<sup3>\t%0, %1"
)

(define_insn "ssabs<mode>2"
  [(set (match_operand:V128QHSQ                  0 "register_operand" "=v")
        (ss_abs:V128QHSQ (match_operand:V128QHSQ 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vabs.s<sup3>.s\t%0, %1"
)

(define_insn "usabs<mode>2"
  [(set (match_operand:V128UQHSQ                   0 "register_operand" "=v")
        (ss_abs:V128UQHSQ (match_operand:V128UQHSQ 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vabs.u<sup3>.s\t%0, %1"
)

(define_insn "bswap<mode>2"
  [(set (match_operand:V128QHSI                 0 "register_operand" "=v")
        (bswap:V128QHSI (match_operand:V128QHSI 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vrev.<sup3>\t%0, %1"
)


;; ------------------------------------------------------------
;; CK810 Vector DSP builtin function insns
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

(define_expand "csky_vadd<mode>"
  [(match_operand:V128QHSQ 0 "register_operand" "")
   (match_operand:V128QHSQ 1 "register_operand" "")
   (match_operand:V128QHSQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_ssadd<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_vadd<mode>"
  [(match_operand:V128UQHSQ 0 "register_operand" "")
   (match_operand:V128UQHSQ 1 "register_operand" "")
   (match_operand:V128UQHSQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_usadd<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

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

(define_expand "csky_vsub<mode>"
  [(match_operand:V128QHSQ 0 "register_operand" "")
   (match_operand:V128QHSQ 1 "register_operand" "")
   (match_operand:V128QHSQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_sssub<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_vsub<mode>"
  [(match_operand:V128UQHSQ 0 "register_operand" "")
   (match_operand:V128UQHSQ 1 "register_operand" "")
   (match_operand:V128UQHSQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_ussub<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

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

(define_expand "csky_vmul<mode>"
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

(define_expand "csky_vmul_u<mode>"
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

(define_expand "csky_vmula<mode>"
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

(define_expand "csky_vmuls<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "")
   (match_operand:V128QHSI 1 "register_operand" "")
   (match_operand:V128QHSI 2 "register_operand" "")
   (match_operand:V128QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_fms<mode>4 (operands[0], operands[1],
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
    emit_insn (gen_fms<mode>4 (operands[0], operands[1],
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
    emit_insn (gen_fms<mode>4 (operands[0], operands[1],
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

(define_expand "csky_vxor<mode>"
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

;; Instructions use format: insn vrx,vry
;; And has mode: v16qi v8hi v4si
;; vry = f(vrx)

(define_int_iterator INSNVV [
  UNSPEC_VCMPHSZU
  UNSPEC_VCMPHSZS
  UNSPEC_VCMPLTZU
  UNSPEC_VCMPLTZS
  UNSPEC_VCMPNEZU
  UNSPEC_VCMPNEZS
])

(define_int_attr insnvv [
  (UNSPEC_VCMPHSZU  "vcmphsz")
  (UNSPEC_VCMPHSZS  "vcmphsz")
  (UNSPEC_VCMPLTZU  "vcmpltz")
  (UNSPEC_VCMPLTZS  "vcmpltz")
  (UNSPEC_VCMPNEZU  "vcmpnez")
  (UNSPEC_VCMPNEZS  "vcmpnez")
])

(define_insn "csky_<insnvv><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=v")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "v")]
                          INSNVV))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvv>.<sup2><sup3><dot><sup4>\t%0, %1"
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
  [(set (match_operand:V16QI 0 "register_operand" "=v")
        (unspec:V16QI [(match_operand:V16QI 1 "register_operand"  "v")
                       (match_operand:V16QI 2 "register_operand"  "v")]
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
  (UNSPEC_VADDEU     "vadd")
  (UNSPEC_VADDES     "vadd")
  (UNSPEC_VMULEU     "vmul")
  (UNSPEC_VMULES     "vmul")
  (UNSPEC_VSABSEU    "vsabs")
  (UNSPEC_VSABSES    "vsabs")
  (UNSPEC_VSUBEU     "vsub")
  (UNSPEC_VSUBES     "vsub")
])

(define_insn "csky_<insnvvv2>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=v")
        (unspec:<vexmode> [(match_operand:V128QHI 1 "register_operand"  "v")
                           (match_operand:V128QHI 2 "register_operand"  "v")]
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
  (UNSPEC_VMULAEU    "vmula")
  (UNSPEC_VMULAES    "vmula")
  (UNSPEC_VMULSEU    "vmuls")
  (UNSPEC_VMULSES    "vmuls")
  (UNSPEC_VSABSAEU   "vsabsa")
  (UNSPEC_VSABSAES   "vsabsa")
])

(define_insn "csky_<insnvvv3>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=v")
        (unspec:<vexmode> [(match_operand:V128QHI   1 "register_operand"  "v")
                           (match_operand:V128QHI   2 "register_operand"  "v")
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
  (UNSPEC_VADDXU	    "vadd")
  (UNSPEC_VADDXS	    "vadd")
  (UNSPEC_VSUBXU      "vsub")
  (UNSPEC_VSUBXS      "vsub")
])

(define_insn "csky_<insnvvv4>x<sup4><sup2><mode>"
  [(set (match_operand:V128HSI 0 "register_operand" "=v")
        (unspec:V128HSI [(match_operand:<vhalfmode> 1 "register_operand"  "v")
                         (match_operand:V128HSI 2 "register_operand"  "v")]
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
  [(set (match_operand:<vhalfmode> 0 "register_operand" "=v")
        (unspec:<vhalfmode> [(match_operand:<vhalfmode> 1 "register_operand"  "v")
                             (match_operand:V128HSI 2 "register_operand"  "v")]
                             INSNVVV4_1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv4_1>.x<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v16qi v8hi v4si
;; vrx = f(vry, vrz)

(define_int_iterator INSNVVV5 [
  UNSPEC_VADDHU
  UNSPEC_VADDHS
  UNSPEC_VADDHRU
  UNSPEC_VADDHRS
  UNSPEC_VANDN
  UNSPEC_VCADDU
  UNSPEC_VCADDS
  UNSPEC_VCMAXU
  UNSPEC_VCMAXS
  UNSPEC_VCMINU
  UNSPEC_VCMINS
  UNSPEC_VCMPHSU
  UNSPEC_VCMPHSS
  UNSPEC_VCMPLTU
  UNSPEC_VCMPLTS
  UNSPEC_VCMPNEU
  UNSPEC_VCMPNES
  UNSPEC_VDCH
  UNSPEC_VDCL
  UNSPEC_VICH
  UNSPEC_VICL
  UNSPEC_VNOR
  UNSPEC_VSABSU
  UNSPEC_VSABSS
  UNSPEC_VSHLU
  UNSPEC_VSHLS
  UNSPEC_VSHRU
  UNSPEC_VSHRS
  UNSPEC_VSHRRU
  UNSPEC_VSHRRS
  UNSPEC_VSUBHU
  UNSPEC_VSUBHS
  UNSPEC_VSUBHRU
  UNSPEC_VSUBHRS
  UNSPEC_VTRCH
  UNSPEC_VTRCL
  UNSPEC_VTST
])

(define_int_attr insnvvv5 [
  (UNSPEC_VADDHU    "vaddh")
  (UNSPEC_VADDHS    "vaddh")
  (UNSPEC_VADDHRU   "vaddh")
  (UNSPEC_VADDHRS   "vaddh")
  (UNSPEC_VANDN     "vandn")
  (UNSPEC_VCADDU    "vcadd")
  (UNSPEC_VCADDS    "vcadd")
  (UNSPEC_VCMAXU    "vcmax")
  (UNSPEC_VCMAXS    "vcmax")
  (UNSPEC_VCMINU    "vcmin")
  (UNSPEC_VCMINS    "vcmin")
  (UNSPEC_VCMPHSU   "vcmphs")
  (UNSPEC_VCMPHSS   "vcmphs")
  (UNSPEC_VCMPLTU   "vcmplt")
  (UNSPEC_VCMPLTS   "vcmplt")
  (UNSPEC_VCMPNEU   "vcmpne")
  (UNSPEC_VCMPNES   "vcmpne")
  (UNSPEC_VDCH      "vdch")
  (UNSPEC_VDCL      "vdcl")
  (UNSPEC_VICH      "vich")
  (UNSPEC_VICL      "vicl")
  (UNSPEC_VNOR      "vnor")
  (UNSPEC_VSABSU    "vsabs")
  (UNSPEC_VSABSS    "vsabs")
  (UNSPEC_VSHLU     "vshl")
  (UNSPEC_VSHLS     "vshl")
  (UNSPEC_VSHRU     "vshr")
  (UNSPEC_VSHRS     "vshr")
  (UNSPEC_VSHRRU    "vshr")
  (UNSPEC_VSHRRS    "vshr")
  (UNSPEC_VSUBHU    "vsubh")
  (UNSPEC_VSUBHS    "vsubh")
  (UNSPEC_VSUBHRU   "vsubh")
  (UNSPEC_VSUBHRS   "vsubh")
  (UNSPEC_VTRCH     "vtrch")
  (UNSPEC_VTRCL     "vtrcl")
  (UNSPEC_VTST      "vtst")
])

(define_insn "csky_<insnvvv5><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=v")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "v")
                          (match_operand:V128QHSI 2 "register_operand"  "v")]
                          INSNVVV5))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv5>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_vshl<mode>"
  [(set (match_operand:V128QHSQ                   0 "register_operand" "=v")
        (unspec:V128QHSQ [(match_operand:V128QHSQ 1 "register_operand"  "v")
                          (match_operand:V128QHSQ 2 "register_operand"  "v")]
                          UNSPEC_VSHLS))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vshl.s<sup3>.s\t%0, %1, %2"
)

(define_insn "csky_vshl<mode>"
  [(set (match_operand:V128UQHSQ                    0 "register_operand" "=v")
        (unspec:V128UQHSQ [(match_operand:V128UQHSQ 1 "register_operand"  "v")
                           (match_operand:V128UQHSQ 2 "register_operand"  "v")]
                           UNSPEC_VSHLS))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vshl.u<sup3>.s\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v16qi v8hi v4si
;; vrx = f(vrx, vry, vrz)

(define_int_iterator INSNVVV6 [
  UNSPEC_VSABSAU
  UNSPEC_VSABSAS
])

(define_int_attr insnvvv6 [
  (UNSPEC_VSABSAU   "vsabsa")
  (UNSPEC_VSABSAS   "vsabsa")
])

(define_insn "csky_<insnvvv6><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand" "=v")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "0")
                          (match_operand:V128QHSI 2 "register_operand"  "v")
                          (match_operand:V128QHSI 3 "register_operand"  "v")]
                          INSNVVV6))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvv6>.<sup2><sup3><dot><sup4>\t%0, %2, %3"
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

(define_expand "csky_vabs<mode>"
  [(match_operand:V128QHSQ 0 "register_operand" "")
   (match_operand:V128QHSQ 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_ssabs<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_vabs<mode>"
  [(match_operand:V128UQHSQ 0 "register_operand" "")
   (match_operand:V128UQHSQ 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_usabs<mode>2 (operands[0], operands[1]));
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

(define_expand "csky_vneg<mode>"
  [(match_operand:V128QHSQ 0 "register_operand" "")
   (match_operand:V128QHSQ 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    emit_insn (gen_ssneg<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "csky_vcnt1v16qi"
  [(set (match_operand:V16QI 0 "register_operand" "=v")
        (unspec:V16QI [(match_operand:V16QI 1 "register_operand"  "v")]
                       UNSPEC_VCNT1))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vcnt1.8\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v16qi v8hi
;; vrx = f(vry)

(define_int_iterator INSNVV1 [
  UNSPEC_VMOVEU
  UNSPEC_VMOVES
])

(define_int_attr insnvv1 [
  (UNSPEC_VMOVEU      "vmov")
  (UNSPEC_VMOVES      "vmov")
])

(define_insn "csky_<insnvv1>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=v")
        (unspec:<vexmode> [(match_operand:V128QHI 1 "register_operand"  "v")]
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
  [(set (match_operand:<vexmode> 0 "register_operand" "=v")
        (unspec:<vexmode> [(match_operand:V128QHI 1 "register_operand"  "v")
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
  [(set (match_operand:<vhalfmode> 0 "register_operand" "=v")
        (unspec:<vhalfmode> [(match_operand:V128HSI 1 "register_operand"  "v")]
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
  UNSPEC_VREV
])

(define_int_attr insnvv4 [
  (UNSPEC_VCLSS       "vcls")
  (UNSPEC_VCLZ        "vclz")
  (UNSPEC_VREV        "vrev")
])

(define_insn "csky_<insnvv4><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=v")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "v")]
                          INSNVV4))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvv4>.<sup2><sup3><dot><sup4>\t%0, %1"
)

;; Instructions use format: insn vrx,vry[index]
;; And has mode: v16qi v8hi v4si
;; vrx = f(vry[index])

(define_insn "csky_vdup<mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand"  "=v")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "v")
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
  [(set (match_operand:V128QHSI                   0 "register_operand" "=v")
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
  [(set (match_operand:V128QHSI                   0 "register_operand" "=v")
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
  [(set (match_operand:V128QHSI                   0 "register_operand"  "=v")
        (unspec:V128QHSI [(match_operand:SI       1 "immediate_operand" "i")
                          (match_operand:V128QHSI 2 "register_operand"  "v")
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
        (unspec:<vtoimode> [(match_operand:V128QHSI 1 "register_operand"  "v")
                            (match_operand:SI       2 "immediate_operand" "i")]
                            UNSPEC_VMFVRU))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmfvr.u<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx[index], ry
;; And has mode: v16qi v8hi v4si
;; vrx = f(index, ry)

(define_insn "csky_vmtvru<mode>"
  [(set (match_operand:V128QHSI                     0 "register_operand"  "=v")
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
        (unspec:<vtoimode> [(match_operand:V128QHI  1 "register_operand"  "v")
                            (match_operand:SI       2 "immediate_operand" "i")]
                            UNSPEC_VMFVRS))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vmfvr.s<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx, vry, imm5
;; And has mode: v16qi v8hi v4si
;; vrx = f(vry, imm5)

(define_int_iterator INSNVVI [
  UNSPEC_VSHLIU
  UNSPEC_VSHLIS
  UNSPEC_VSHRIU
  UNSPEC_VSHRIS
  UNSPEC_VSHRIRU
  UNSPEC_VSHRIRS
])

(define_int_attr insnvvi [
  (UNSPEC_VSHLIU      "vshli")
  (UNSPEC_VSHLIS      "vshli")
  (UNSPEC_VSHRIU      "vshri")
  (UNSPEC_VSHRIS      "vshri")
  (UNSPEC_VSHRIRU     "vshri")
  (UNSPEC_VSHRIRS     "vshri")
])

(define_insn "csky_<insnvvi><sup4><sup2><mode>"
  [(set (match_operand:V128QHSI                   0 "register_operand"  "=v")
        (unspec:V128QHSI [(match_operand:V128QHSI 1 "register_operand"  "v")
                          (match_operand:SI       2 "immediate_operand" "i")]
                          INSNVVI))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "<insnvvi>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_vshli<mode>"
  [(set (match_operand:V128UQHSQ                   0 "register_operand"  "=v")
        (unspec:V128UQHSQ [(match_operand:V128UQHSQ 1 "register_operand"  "v")
                           (match_operand:SI       2 "immediate_operand" "i")]
                           UNSPEC_VSHLIS))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vshli.u<sup3>.s\t%0, %1, %2"
)

(define_insn "csky_vshli<mode>"
  [(set (match_operand:V128QHSQ                   0 "register_operand"  "=v")
        (unspec:V128QHSQ [(match_operand:V128QHSQ 1 "register_operand"  "v")
                          (match_operand:SI       2 "immediate_operand" "i")]
                          UNSPEC_VSHLIS))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "vshli.s<sup3>.s\t%0, %1, %2"
)

;; ------------------------------------------------------------
;; CK810 Vector DSP for 64bit
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
  [(set (match_operand:V64ALL 0 "nonimmediate_operand"  "=v,v,m,v,r,?r")
        (match_operand:V64ALL 1 "nonimmediate_operand"  "m, v,v,r,v,r"))]
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
                          (match_operand:V64QHI 1 "register_operand" "v")
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
                          (match_operand:V64QHI 1 "register_operand" "v")
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
          (match_operand:V64QHSI 1 "register_operand" "v")
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
        (match_operator:V64QHSI   1 "csky_scond_operator"
          [(match_operand:V64QHSI 2 "register_operand")
           (match_operand:V64QHSI 3 "reg_or_zero_operand")]))]
  "CSKY_ISA_FEATURE(vdsp64)"
  ""
)

(define_insn "*vec_cmp<vscond_suf><mode>"
  [(set (match_operand:V64QHSI                  0 "register_operand"    "=v,v")
        (vscond:V64QHSI (match_operand:V64QHSI 1 "register_operand"    "v,v")
                         (match_operand:V64QHSI 2 "reg_or_zero_operand" "v,i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "@
   vcmp<vscond_suf>.s<sup3>\t%0,%1,%2
   vcmp<vscond_suf>.s<sup3>z\t%0,%1"
 [(set_attr "type"   "alu")
  (set_attr "length"   "4")])

(define_expand "vec_cmpu<mode><mode>"
  [(set (match_operand:V64QHSI    0 "register_operand")
        (match_operator:V64QHSI   1 "csky_ucond_operator"
          [(match_operand:V64QHSI 2 "register_operand")
           (match_operand:V64QHSI 3 "reg_or_zero_operand")]))]
  "CSKY_ISA_FEATURE(vdsp64)"
  ""
)

(define_insn "*vec_cmp<vucond_suf><mode>"
  [(set (match_operand:V64QHSI                  0 "register_operand" "=v,v")
        (vucond:V64QHSI (match_operand:V64QHSI 1 "register_operand" "v,v")
                     (match_operand:V64QHSI     2 "reg_or_zero_operand" "v,i")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "@
   vcmp<vucond_suf>.u<sup3>\t%0,%1,%2
   vcmp<vucond_suf>.u<sup3>z\t%0,%1"
 [(set_attr "type"   "alu")
  (set_attr "length"   "4")])

(define_insn "add<mode>3"
  [(set (match_operand:V64QHSI               0 "register_operand" "=v")
        (plus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                      (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vadd.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ssadd<mode>3"
  [(set (match_operand:V64QHSQ                  0 "register_operand" "=v")
        (ss_plus:V64QHSQ (match_operand:V64QHSQ 1 "register_operand" "%v")
                         (match_operand:V64QHSQ 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vadd.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "usadd<mode>3"
  [(set (match_operand:V64UQHSQ                   0 "register_operand" "=v")
        (us_plus:V64UQHSQ (match_operand:V64UQHSQ 1 "register_operand" "%v")
                          (match_operand:V64UQHSQ 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vadd.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sub<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=v")
        (minus:V64QHSI (match_operand:V64QHSI 1 "register_operand" "v")
                       (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsub.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sssub<mode>3"
  [(set (match_operand:V64QHSQ                 0 "register_operand" "=v")
        (minus:V64QHSQ (match_operand:V64QHSQ 1 "register_operand" "v")
                       (match_operand:V64QHSQ  2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsub.s<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ussub<mode>3"
  [(set (match_operand:V64UQHSQ                 0 "register_operand" "=v")
        (minus:V64UQHSQ (match_operand:V64UQHSQ 1 "register_operand" "v")
                        (match_operand:V64UQHSQ 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vsub.u<sup3>.s\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "and<mode>3"
  [(set (match_operand:V64QHSI              0 "register_operand" "=v")
        (and:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                     (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vand.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ior<mode>3"
  [(set (match_operand:V64QHSI              0 "register_operand" "=v")
        (ior:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                     (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "xor<mode>3"
  [(set (match_operand:V64QHSI              0 "register_operand" "=v")
        (xor:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                     (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vxor.<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "smax<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=v")
        (smax:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                       (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmax.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umax<mode>3"
  [(set (match_operand:V64QHSI 0 "register_operand" "=v")
        (umax:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                      (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmax.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "smin<mode>3"
  [(set (match_operand:V64QHSI 0 "register_operand" "=v")
        (smin:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                      (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmin.s<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umin<mode>3"
  [(set (match_operand:V64QHSI 0 "register_operand" "=v")
        (umin:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                      (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmin.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "fma<mode>4"
  [(set (match_operand:V64QHSI               0 "register_operand" "=v")
        (fma:V64QHSI (match_operand:V64QHSI 1 "register_operand" "v")
                      (match_operand:V64QHSI 2 "register_operand" "v")
                      (match_operand:V64QHSI 3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmula.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "fms<mode>4"
  [(set (match_operand:V64QHSI               0 "register_operand" "=v")
        (fma:V64QHSI (match_operand:V64QHSI 1 "register_operand" "v")
                      (match_operand:V64QHSI 2 "register_operand" "v")
                      (neg:V64QHSI (match_operand:V64QHSI 3 "register_operand" "0"))))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmuls.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "mul<mode>3"
  [(set (match_operand:V64QHSI                0 "register_operand" "=v")
        (mult:V64QHSI (match_operand:V64QHSI 1 "register_operand" "%v")
                       (match_operand:V64QHSI 2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmul.u<sup3>\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "neg<mode>2"
  [(set (match_operand:V64QHSI               0 "register_operand" "=v")
        (neg:V64QHSI (match_operand:V64QHSI 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vneg.s<sup3>\t%0, %1"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "ssneg<mode>2"
  [(set (match_operand:V64QHSQ                  0 "register_operand" "=v")
        (ss_neg:V64QHSQ (match_operand:V64QHSQ 1 "register_operand" "v")))]
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
;;  [(set (match_operand:V64QHSI   0 "register_operand" "=v")
;;        (lshiftrt:V64QHSI
;;          (match_operand:V64QHSI 1 "register_operand" "v")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshri.u<sup3>\t%0,%1,%2"
;;)

;;(define_insn "ashr<mode>3"
;;  [(set (match_operand:V64QHSI   0 "register_operand" "=v")
;;        (ashiftrt:V64QHSI
;;          (match_operand:V64QHSI 1 "register_operand" "v")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshri.s<sup3>\t%0, %1, %2"
;;)

;;(define_insn "ashl<mode>3"
;;  [(set (match_operand:V64QHSI   0 "register_operand" "=v")
;;        (ashift:V64QHSI
;;          (match_operand:V64QHSI 1 "register_operand" "v")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshli.u<sup3>\t%0, %1, %2"
;;)

;;(define_insn "ssashl<mode>3"
;;  [(set (match_operand:V64QHSQ   0 "register_operand" "=v")
;;        (ashift:V64QHSQ
;;          (match_operand:V64QHSQ 1 "register_operand" "v")
;;          (match_operand:SI       2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshli.s<sup3>.s\t%0, %1, %2"
;;)

;;(define_insn "usashl<mode>3"
;;  [(set (match_operand:V64UQHSQ   0 "register_operand" "=v")
;;        (ashift:V64UQHSQ
;;          (match_operand:V64UQHSQ 1 "register_operand" "v")
;;          (match_operand:SI        2 "const_0_to_31_operand" "i")))]
;;  "CSKY_ISA_FEATURE(vdsp64)"
;;  "vshli.u<sup3>.s\t%0, %1, %2"
;;)

(define_insn "abs<mode>2"
  [(set (match_operand:V64QHSI               0 "register_operand" "=v")
        (abs:V64QHSI (match_operand:V64QHSI 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vabs.s<sup3>\t%0, %1"
)

(define_insn "ssabs<mode>2"
  [(set (match_operand:V64QHSQ                  0 "register_operand" "=v")
        (ss_abs:V64QHSQ (match_operand:V64QHSQ 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vabs.s<sup3>.s\t%0, %1"
)

(define_insn "usabs<mode>2"
  [(set (match_operand:V64UQHSQ                   0 "register_operand" "=v")
        (ss_abs:V64UQHSQ (match_operand:V64UQHSQ 1 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vabs.u<sup3>.s\t%0, %1"
)

(define_insn "bswap<mode>2"
  [(set (match_operand:V64QHSI                 0 "register_operand" "=v")
        (bswap:V64QHSI (match_operand:V64QHSI 1 "register_operand" "v")))]
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

(define_expand "csky_vadd<mode>"
  [(match_operand:V64QHSQ 0 "register_operand" "")
   (match_operand:V64QHSQ 1 "register_operand" "")
   (match_operand:V64QHSQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_ssadd<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_vadd<mode>"
  [(match_operand:V64UQHSQ 0 "register_operand" "")
   (match_operand:V64UQHSQ 1 "register_operand" "")
   (match_operand:V64UQHSQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_usadd<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

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

(define_expand "csky_vsub<mode>"
  [(match_operand:V64QHSQ 0 "register_operand" "")
   (match_operand:V64QHSQ 1 "register_operand" "")
   (match_operand:V64QHSQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_sssub<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

(define_expand "csky_vsub<mode>"
  [(match_operand:V64UQHSQ 0 "register_operand" "")
   (match_operand:V64UQHSQ 1 "register_operand" "")
   (match_operand:V64UQHSQ 2 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_ussub<mode>3 (operands[0], operands[1],
                                 operands[2]));
    DONE;
  }
)

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

(define_expand "csky_vmul<mode>"
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

(define_expand "csky_vmul_u<mode>"
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

(define_expand "csky_vmula<mode>"
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

(define_expand "csky_vmuls<mode>"
  [(match_operand:V64QHSI 0 "register_operand" "")
   (match_operand:V64QHSI 1 "register_operand" "")
   (match_operand:V64QHSI 2 "register_operand" "")
   (match_operand:V64QHSI 3 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_fms<mode>4 (operands[0], operands[1],
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
    emit_insn (gen_fms<mode>4 (operands[0], operands[1],
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
    emit_insn (gen_fms<mode>4 (operands[0], operands[1],
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

(define_expand "csky_vxor<mode>"
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

;; Instructions use format: insn vrx,vry
;; And has mode: v8qi v4hi v2si
;; vry = f(vrx)

(define_insn "csky_<insnvv><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=v")
        (unspec:V64QHSI [(match_operand:V64QHSI 1 "register_operand"  "v")]
                          INSNVV))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv>.<sup2><sup3><dot><sup4>\t%0, %1"
)

;; Instructions use format: insn vrx,vry,vrz
;; And only has mode v8qi
;; vrx = f(vry, vrz)

(define_insn "csky_<insnvvv1>v8qi"
  [(set (match_operand:V8QI 0 "register_operand" "=v")
        (unspec:V8QI  [(match_operand:V8QI 1 "register_operand"  "v")
                       (match_operand:V8QI 2 "register_operand"  "v")]
                       INSNVVV1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv1>.8\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8qi v4hi
;; vrx = f(vry, vrz)

(define_insn "csky_<insnvvv2>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=v")
        (unspec:<vexmode> [(match_operand:V64QHI 1 "register_operand"  "v")
                           (match_operand:V64QHI 2 "register_operand"  "v")]
                           INSNVVV2))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv2>.e<sup2><sup3>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8qi v4hi
;; vrx = f(vrx, vry, vrz)

(define_insn "csky_<insnvvv3>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=v")
        (unspec:<vexmode> [(match_operand:V64QHI 1 "register_operand"  "v")
                           (match_operand:V64QHI 2 "register_operand"  "v")
                           (match_operand:<vexmode> 3 "register_operand"  "0")]
                           INSNVVV3))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv3>.e<sup2><sup3>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v4hi v2si
;; vrx = f(vry, vrz)

(define_insn "csky_<insnvvv4>x<sup4><sup2><mode>"
  [(set (match_operand:V64HSI 0 "register_operand" "=v")
        (unspec:V64HSI [(match_operand:<vhalfmode> 1 "register_operand"  "v")
                        (match_operand:V64HSI 2 "register_operand"  "v")]
                         INSNVVV4))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv4>.x<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_<insnvvv4_1>x<sup4><sup2><mode>"
  [(set (match_operand:<vhalfmode> 0 "register_operand" "=v")
        (unspec:<vhalfmode> [(match_operand:<vhalfmode> 1 "register_operand"  "v")
                             (match_operand:V64HSI 2 "register_operand"  "v")]
                             INSNVVV4_1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv4_1>.x<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8qi v4hi v2si
;; vrx = f(vry, vrz)

(define_insn "csky_<insnvvv5><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=v")
        (unspec:V64QHSI  [(match_operand:V64QHSI 1 "register_operand"  "v")
                          (match_operand:V64QHSI 2 "register_operand"  "v")]
                          INSNVVV5))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv5>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_vshl<mode>"
  [(set (match_operand:V64QHSQ                  0 "register_operand" "=v")
        (unspec:V64QHSQ [(match_operand:V64QHSQ 1 "register_operand"  "v")
                         (match_operand:V64QHSQ 2 "register_operand"  "v")]
                         UNSPEC_VSHLS))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vshl.s<sup3>.s\t%0, %1, %2"
)

(define_insn "csky_vshl<mode>"
  [(set (match_operand:V64UQHSQ                   0 "register_operand" "=v")
        (unspec:V64UQHSQ [(match_operand:V64UQHSQ 1 "register_operand"  "v")
                          (match_operand:V64UQHSQ 2 "register_operand"  "v")]
                          UNSPEC_VSHLS))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vshl.u<sup3>.s\t%0, %1, %2"
)

;; Instructions use format: insn vrx,vry,vrz
;; And has mode: v8qi v4hi v2si
;; vrx = f(vrx, vry, vrz)

(define_insn "csky_<insnvvv6><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=v")
        (unspec:V64QHSI  [(match_operand:V64QHSI 1 "register_operand"  "0")
                          (match_operand:V64QHSI 2 "register_operand"  "v")
                          (match_operand:V64QHSI 3 "register_operand"  "v")]
                          INSNVVV6))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvv6>.<sup2><sup3><dot><sup4>\t%0, %2, %3"
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

(define_expand "csky_vabs<mode>"
  [(match_operand:V64QHSQ 0 "register_operand" "")
   (match_operand:V64QHSQ 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_ssabs<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_expand "csky_vabs<mode>"
  [(match_operand:V64UQHSQ 0 "register_operand" "")
   (match_operand:V64UQHSQ 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_usabs<mode>2 (operands[0], operands[1]));
    DONE;
  }
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

(define_expand "csky_vneg<mode>"
  [(match_operand:V64QHSQ 0 "register_operand" "")
   (match_operand:V64QHSQ 1 "register_operand" "")]
  "CSKY_ISA_FEATURE(vdsp64)"
  {
    emit_insn (gen_ssneg<mode>2 (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "csky_vcnt1v8qi"
  [(set (match_operand:V8QI 0 "register_operand" "=v")
        (unspec:V8QI [(match_operand:V8QI 1 "register_operand"  "v")]
                       UNSPEC_VCNT1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vcnt1.8\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v8qi v4hi
;; vrx = f(vry)

(define_insn "csky_<insnvv1>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=v")
        (unspec:<vexmode> [(match_operand:V64QHI 1 "register_operand"  "v")]
                           INSNVV1))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv1>.e<sup2><sup3>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v8qi v4hi
;; vrx = f(vrx, vry)

(define_insn "csky_<insnvv2>e<sup2><mode>"
  [(set (match_operand:<vexmode> 0 "register_operand" "=v")
        (unspec:<vexmode>  [(match_operand:V64QHI 1 "register_operand"  "v")
                            (match_operand:V64QHI 2 "register_operand"  "0")]
                            INSNVV2))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv2>.e<sup2><sup3>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v4hi v2si
;; vrx = f(vry)

(define_insn "csky_<insnvv3><sup4><sup2><mode>"
  [(set (match_operand:<vhalfmode> 0 "register_operand" "=v")
        (unspec:<vhalfmode> [(match_operand:V64HSI 1 "register_operand"  "v")]
                             INSNVV3))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv3>.<sup2><sup3><dot><sup4>\t%0, %1"
)

;; Instructions use format: insn vrx,vry
;; And has mode: v8qi v4hi v2si
;; vrx = f(vry)

(define_insn "csky_<insnvv4><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI 0 "register_operand" "=v")
        (unspec:V64QHSI [(match_operand:V64QHSI 1 "register_operand"  "v")]
                          INSNVV4))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvv4>.<sup2><sup3><dot><sup4>\t%0, %1"
)

;; Instructions use format: insn vrx,vry[index]
;; And has mode: v8qi v4hi v2si
;; vrx = f(vry[index])

(define_insn "csky_vdup<mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand"  "=v")
        (unspec:V64QHSI [(match_operand:V64QHSI  1 "register_operand"  "v")
                          (match_operand:SI      2 "immediate_operand" "i")]
                          UNSPEC_VDUP))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vdup.<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx,(ry, offset)
;; And has mode: v16qi v8hi v4si
;; vrx = f(ry, offset)

(define_insn "csky_<insnvgo1><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand" "=v")
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
  [(set (match_operand:V64QHSI                    0 "register_operand" "=v")
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
  [(set (match_operand:V64QHSI                    0 "register_operand"  "=v")
        (unspec:V64QHSI  [(match_operand:SI       1 "immediate_operand" "i")
                          (match_operand:V64QHSI  2 "register_operand"  "v")
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
        (unspec:<vtoimode> [(match_operand:V64QHSI 1 "register_operand"  "v")
                            (match_operand:SI       2 "immediate_operand" "i")]
                            UNSPEC_VMFVRU))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmfvr.u<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx[index], ry
;; And has mode: v8qi v4hi v2si
;; vrx = f(index, ry)

(define_insn "csky_vmtvru<mode>"
  [(set (match_operand:V64QHSI                     0 "register_operand"  "=v")
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
        (unspec:<vtoimode> [(match_operand:V64QHI  1 "register_operand"  "v")
                            (match_operand:SI       2 "immediate_operand" "i")]
                            UNSPEC_VMFVRS))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vmfvr.s<sup3>\t%0, %1[%2]"
)

;; Instructions use format: insn vrx, vry, imm5
;; And has mode: v8qi v4hi v2si
;; vrx = f(vry, imm5)

(define_insn "csky_<insnvvi><sup4><sup2><mode>"
  [(set (match_operand:V64QHSI                   0 "register_operand"  "=v")
        (unspec:V64QHSI [(match_operand:V64QHSI  1 "register_operand"  "v")
                         (match_operand:SI       2 "immediate_operand" "i")]
                         INSNVVI))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "<insnvvi>.<sup2><sup3><dot><sup4>\t%0, %1, %2"
)

(define_insn "csky_vshli<mode>"
  [(set (match_operand:V64UQHSQ                   0 "register_operand"  "=v")
        (unspec:V64UQHSQ [(match_operand:V64UQHSQ 1 "register_operand"  "v")
                          (match_operand:SI       2 "immediate_operand" "i")]
                          UNSPEC_VSHLIS))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vshli.u<sup3>.s\t%0, %1, %2"
)

(define_insn "csky_vshli<mode>"
  [(set (match_operand:V64QHSQ                   0 "register_operand"  "=v")
        (unspec:V64QHSQ [(match_operand:V64QHSQ  1 "register_operand"  "v")
                         (match_operand:SI       2 "immediate_operand" "i")]
                         UNSPEC_VSHLIS))]
  "CSKY_ISA_FEATURE(vdsp64)"
  "vshli.s<sup3>.s\t%0, %1, %2"
)
