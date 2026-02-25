;;--------------------------------
;; Define iterators for csky
;;--------------------------------

;; ------------------------------------------------------------
;; Common insn iterator
;; ------------------------------------------------------------

(define_mode_iterator VANY   [V2DI   V4SI   V8HI
                              V16QI  OI
                              V4SQ   V8HQ   V16QQ
                              V4USQ  V8UHQ  V16UQQ

                              V2SI   V4HI   V8QI
                              V2SQ   V4HQ   V8QQ
                              V2USQ  V4UHQ  V8UQQ])

(define_mode_iterator V128ALL [V4SI  V8HI  V16QI
                               V4SQ  V8HQ  V16QQ
                               V4USQ V8UHQ V16UQQ])
(define_mode_iterator V128ALLP [V4SI  V8HI  V16QI V2DI
                               V4SQ  V8HQ  V16QQ
                               V4USQ V8UHQ V16UQQ])
                               

(define_mode_iterator V128QHSDI [V16QI V8HI V4SI V2DI])
(define_mode_iterator V128HSDI [V8HI V4SI V2DI])
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
(define_mode_iterator V64QHSI [V8QI V4HI V2SI])
(define_mode_iterator V64QHSQ [V8QQ V4HQ V2SQ])
(define_mode_iterator V64UQHSQ [V8UQQ V4UHQ V2USQ])

(define_mode_iterator V32QHIV64SI [V2HI V4QI V2SI])
(define_mode_iterator V32QHQ      [V2HQ V4QQ])
(define_mode_iterator V32UQHQ     [V2UHQ V4UQQ])
(define_mode_iterator V32HIHQ  [V2HI V2HQ V2UHQ])
(define_mode_iterator V32QHI   [V2HI V4QI])

(define_mode_attr sup3 [
  (V16QI "8") (V8HI "16")   (V4SI "32") (V2DI "64")
  (V16QQ "8") (V8HQ "16")   (V4SQ "32")
  (V16UQQ "8") (V8UHQ "16") (V4USQ "32")
  (V8QI "8") (V4HI "16")   (V2SI "32")
  (V8QQ "8") (V4HQ "16")   (V2SQ "32")
  (V8UQQ "8") (V4UHQ "16") (V2USQ "32")
  (V4QI "8") (V2HI "16")
  (V4QQ "8") (V2HQ "16")
  (V4UQQ "8") (V2UHQ "16")
  (V8HF "16") (V4SF "32")
])

(define_mode_attr vldst1mode [
  (V16QI "V1QI") (V8HI "V1HI") (V4SI "V1SI")
  (V8HF "V1HF") (V4SF "V1SF")
])

(define_mode_attr vldst2mode [
  (V16QI "V2QI") (V8HI "V2HI") (V4SI "V2SI")
  (V8HF "V2HF") (V4SF "V2SF")
])

(define_mode_attr vldst3mode [
  (V16QI "V3QI") (V8HI "V3HI") (V4SI "V3SI")
  (V8HF "V3HF") (V4SF "V3SF")
])

(define_mode_attr vldst4mode [
  (V16QI "V4QI") (V8HI "V4HI") (V4SI "V4SI")
  (V8HF "V4HF") (V4SF "V4SF")
])

(define_mode_attr vtoimode [(V4SI "SI") (V8HI "HI") (V16QI "QI") (V2DI "DI")
                            (V2SI "SI") (V4HI "HI") (V8QI "QI")])

(define_mode_attr vexmode [(V8HI "V4SI") (V16QI "V8HI")
                           (V4HI "V2SI") (V8QI "V4HI")
                           (V4SI "V2DI")])
(define_mode_attr vexxmode [(V16QI "V4SI") (V8HI "V2DI")])

(define_mode_attr vhalfmode [(V8HI "V16QI") (V4SI "V8HI")
                             (V4HI "V8QI") (V2SI "V4HI")
                             (V2DI "V4SI")])

(define_mode_attr vhimode [(V8HI "V4HI") (V4SI "V2SI")
                             (V16QI "V8QI")])

(define_mode_attr vextendmode [(V8HI "OI")   (V4SI "OI")
                               (V16QI "OI") (V4HI "V4SI")
                               (V2SI "V2DI")   (V8QI "V8HI")])

(define_mode_attr vtruncatecbmode [
  (V8HI "V16QI") (V4SI "V8HI") (V2DI "V4SI")
  (V4SF "V8HF") (V2DF "V4SF")
])

(define_code_iterator VCMPS1 [ge lt ne])
(define_code_iterator VCMPU1 [geu ltu ne])
(define_code_iterator VCMPS2 [gt le])
(define_code_iterator VCMPU2 [gtu leu])
(define_code_iterator VCMPU3 [geu ltu])

(define_code_attr vcmps1_attr
  [(lt "lt") (ge "hs" ) (ne "ne")]
)

(define_code_attr vcmpu1_attr
  [(ltu "lt") (geu "hs" ) (ne "ne")]
)

(define_code_attr vcmps2_attr
  [(le "ls") (gt "h" )]
)

(define_code_attr vcmpu2_attr
  [(leu "ls") (gtu "h" )]
)

(define_code_attr vcmpu3_attr
  [(geu "hs") (ltu "lt")]
)

(define_code_iterator VEXT [plus minus mult])

(define_code_attr insnvvv
  [(plus "vadd") (minus "vsub") (mult "vmul")]
)

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
  (UNSPEC_VCADDU     "u")
  (UNSPEC_VCADDS     "s")
  (UNSPEC_VCMAXU     "u")
  (UNSPEC_VCMAXS     "s")
  (UNSPEC_VCMINU     "u")
  (UNSPEC_VCMINS     "s")
  (UNSPEC_VDCH       "")
  (UNSPEC_VDCL       "")
  (UNSPEC_VICH       "")
  (UNSPEC_VICL       "")
  (UNSPEC_VSABSU    "u")
  (UNSPEC_VSABSS    "s")
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
  (UNSPEC_VTRCH       "")
  (UNSPEC_VTRCL       "")
  (UNSPEC_VTSTS       "")
  (UNSPEC_VTSTU       "")
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
  (UNSPEC_VCADDU     "")
  (UNSPEC_VCADDS     "")
  (UNSPEC_VCMAXU     "")
  (UNSPEC_VCMAXS     "")
  (UNSPEC_VCMINU     "")
  (UNSPEC_VCMINS     "")
  (UNSPEC_VDCH       "")
  (UNSPEC_VDCL       "")
  (UNSPEC_VICH       "")
  (UNSPEC_VICL       "")
  (UNSPEC_VSABSU    "")
  (UNSPEC_VSABSS    "")
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
  (UNSPEC_VTSTS      "")
  (UNSPEC_VTSTU      "")
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
  (UNSPEC_VCADDU     "")
  (UNSPEC_VCADDS     "")
  (UNSPEC_VCMAXU     "")
  (UNSPEC_VCMAXS     "")
  (UNSPEC_VCMINU     "")
  (UNSPEC_VCMINS     "")
  (UNSPEC_VDCH       "")
  (UNSPEC_VDCL       "")
  (UNSPEC_VICH       "")
  (UNSPEC_VICL       "")
  (UNSPEC_VSABSU    "")
  (UNSPEC_VSABSS    "")
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
  (UNSPEC_VTSTS      "")
  (UNSPEC_VTSTU      "")
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

(define_mode_attr sup1 [(V2HI "p") (V4QI "p") (V2SI "")
                        (V2HQ "p") (V4QQ "p") (V2SQ "") (SQ "")
                        (V2UHQ "p") (V4UQQ "p") (V2USQ "") (USQ "") (SI "")])


;;------------------------------
;;------------------------------
;;------------------------------
;; CSKY860vdsp
;;------------------------------
;;------------------------------
;;------------------------------

;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators

;; LDRU.T.N

;; 
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------

;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators

;; UNI OPERATION

;; like insn rz, rx
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------



;;---------------------------------------------------------------------
;; without extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_UNIOP_QHSQ [
  UNSPEC_VRECPES
  UNSPEC_VRSQRTES
  UNSPEC_VEXPES
])

(define_int_iterator INSN_UNIOP_UQHSQ [
  UNSPEC_VRECPEU
  UNSPEC_VRSQRTEU
  UNSPEC_VEXPEU
])

;;---------------------------------------------------------------------
;; with extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_UNIOPE_QHS [
  UNSPEC_VPADDEU
  UNSPEC_VPADDES
])

(define_int_iterator INSN_UNIOPAE_QHS[
  UNSPEC_VPADDAEU
  UNSPEC_VPADDAES
])



;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators
;;
;; BINARAY OPERATION
;;
;; like insn rz, rx, ry
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------

;;---------------------------------------------------------------------
;; without extending
;;---------------------------------------------------------------------


(define_int_iterator INSN_BINOP_QHS[
  UNSPEC_VASXSS
  UNSPEC_VASXUS
  UNSPEC_VSAXUS
  UNSPEC_VSAXSS
  UNSPEC_VASXHS
  UNSPEC_VASXHU
  UNSPEC_VSAXHU
  UNSPEC_VSAXHS
  UNSPEC_VPMAXU
  UNSPEC_VPMAXS
  UNSPEC_VPMINU
  UNSPEC_VPMINS
  UNSPEC_VMULUH
  UNSPEC_VMULSH
  UNSPEC_VRMULHSS
  UNSPEC_VRMULHSRS
  UNSPEC_VRCMULSRS
  UNSPEC_VRCMULCSRS
  UNSPEC_VRCMULNSRS
  UNSPEC_VRCMULCNSRS
])

(define_int_iterator INSN_BINOP_QHSQ[
  UNSPEC_VRECPSS
  UNSPEC_VRSQRTSS
])

(define_int_iterator INSN_BINOP_Q[
  UNSPEC_VTBL
])

(define_int_iterator INSN_TERNOP_Q[
  UNSPEC_VTBX
])

(define_int_iterator INSN_BINOP_UQHSQ[
  UNSPEC_VRECPSU
  UNSPEC_VRSQRTSU
])

(define_int_iterator INSN_BINOP_QHSD[
  UNSPEC_VSHRUR
  UNSPEC_VSHRSR
  UNSPEC_VPADDU
  UNSPEC_VPADDS
  UNSPEC_VPADDUS
  UNSPEC_VPADDSS
  UNSPEC_VSHTU
  UNSPEC_VSHTS
  UNSPEC_VSHTSS
  UNSPEC_VSHTUS
  UNSPEC_VSHTUR
  UNSPEC_VSHTSR
  UNSPEC_VSHTURS
  UNSPEC_VSHTSRS
])


(define_int_iterator INSN_BINOP_HSD[
  UNSPEC_VADDUH
  UNSPEC_VSUBUH
  UNSPEC_VADDSH
  UNSPEC_VSUBSH
  UNSPEC_VADDURH
  UNSPEC_VSUBURH
  UNSPEC_VADDSRH
  UNSPEC_VSUBSRH
])


(define_int_iterator INSN_BINOPA_QHS[
  UNSPEC_VRMULHASRS
  UNSPEC_VRMULHSSRS
  UNSPEC_VRMULXAASRS
  UNSPEC_VRMULXASSRS
  UNSPEC_VRMULXSSSRS
  UNSPEC_VRMULXSASRS
])

;; INSN_BINOPA_QHSD used as "asm vz, vx, ry"
(define_int_iterator INSN_BINOPA_QHSD[
  UNSPEC_VEXHS
  UNSPEC_VEXLS
  UNSPEC_VEXHU
  UNSPEC_VEXLU
  ])

;;---------------------------------------------------------------------
;; combination with half-truncating
;;---------------------------------------------------------------------

(define_int_iterator INSN_BINOPTC_HSD[
  UNSPEC_VMOVTL
  UNSPEC_VMOVTH
  UNSPEC_VMOVSSL
  UNSPEC_VMOVUSL
  UNSPEC_VMOVURH
  UNSPEC_VMOVSRH
])

(define_int_iterator INSN_IMM_BINOPTC_HSD[
  UNSPEC_VSHRISL
  UNSPEC_VSHRIUL
  UNSPEC_VSHRISLR
  UNSPEC_VSHRIULR
  UNSPEC_VSHRIULS
  UNSPEC_VSHRISLS
  UNSPEC_VSHRIULRS
  UNSPEC_VSHRISLRS
])

;;---------------------------------------------------------------------
;; with extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_BINOPE_QHS[
  UNSPEC_VRMULSSE
])

(define_int_iterator INSN_BINOPW_QHS[
  UNSPEC_VTRN
])
;;---------------------------------------------------------------------
;; with fourth extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_BINOPEE_QH[
  UNSPEC_VMULACAU
  UNSPEC_VMULACAS
])

(define_int_iterator INSN_BINOPAEE_QH[
  UNSPEC_VMULACAAU
  UNSPEC_VMULACAAS
])
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators
;;
;; TRIPLE_OPERATIONS
;;
;; like insn rz, rx, ry, rk
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------

;;---------------------------------------------------------------------
;; without extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_THOP_QHSD[
  UNSPEC_VSELS
  UNSPEC_VSELU
])



;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators
;;
;; UNI_OPERATIONS with imm
;;
;; like insn rz,imm
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------

;;---------------------------------------------------------------------
;; without extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_IMM_UNIOP_Q[
  UNSPEC_VMASKIL
  UNSPEC_VMASKIH
])

(define_int_iterator INSN_IMM_UNIOP_HS[
  UNSPEC_VMOVIU
  UNSPEC_VMOVIS
])

(define_int_iterator INSN_IMM_UNIOP_H[
  UNSPEC_VMASKI
])

;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators
;;
;; BINARY_OPERATIONS with imm
;;
;; like insn rz, rx, imm
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------

;;---------------------------------------------------------------------
;; without extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_IMM_BINOP_QHSD[
  UNSPEC_VCLIPS
  UNSPEC_VCLIPU
  UNSPEC_VSHRIUR
  UNSPEC_VSHRISR
])

(define_int_iterator INSN_IMM_BINOPA_QHSD[
  UNSPEC_VSHRIAUR
  UNSPEC_VSHRIASR
  ])

;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators
;;
;; TRIPLE_OPERATIONS with imm
;;
;; like insn rz, rx, ry, imm
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------


;;---------------------------------------------------------------------
;; without extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_IMM_THROP_QHS[
  UNSPEC_VMULIUH
  UNSPEC_VMULISH
  UNSPEC_VRMULHISS
  UNSPEC_VRMULHISRS
])

(define_int_iterator INSN_IMM_THROPA_QHS[
  UNSPEC_VRMULHAISRS
  UNSPEC_VRMULHSISRS
  UNSPEC_VRMULXAAISRS
  UNSPEC_VRMULXASISRS
  UNSPEC_VRMULXSSISRS
  UNSPEC_VRMULXSAISRS
])

(define_int_iterator INSN_IMM_THROP_Q[
  UNSPEC_VEXTI
])


;;---------------------------------------------------------------------
;; with extending
;;---------------------------------------------------------------------
(define_int_iterator INSN_IMM_THROPE_QHS[
  UNSPEC_VRMULISSE
  UNSPEC_VRMULSHRSE
])


(define_int_iterator INSN_IMM_THROPAE_QHS[
  UNSPEC_VRMULSASE
  UNSPEC_VRMULSSSE
  UNSPEC_VRCMULASE
  UNSPEC_VRCMULCASE
  UNSPEC_VRCMULNASE
  UNSPEC_VRCMULCNASE
])

;;---------------------------------------------------------------------
;; with fourth extending
;;---------------------------------------------------------------------

(define_int_iterator INSN_IMM_THROPEE_QH[
  UNSPEC_VMULACAIU
  UNSPEC_VMULACAIS
])

(define_int_iterator INSN_IMM_THROPAEE_QH[
  UNSPEC_VMULACAAIU
  UNSPEC_VMULACAAIS
])

;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators
;;
;; TRIPLE_OPERATIONS with imms
;;
;; like insn rz, rx, imm, imm2
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------


(define_int_iterator INSN_IMM2_THROPE_QHS[
  UNSPEC_VRMULSHRISE
])

(define_int_iterator INSN_IMM2_THROPAE_QHS[
  UNSPEC_VRMULSAISE
  UNSPEC_VRMULSSISE
])

;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int iterators
;;
;; FOUR_OPERATIONS with two imm
;;
;; like insn rz, rx, ry, imm, imm
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------

;;---------------------------------------------------------------------
;; with extending
;;---------------------------------------------------------------------


;;---------------------------------------------------------------------
;;---------------------------------------------------------------------
;; define Int attrs
;;
;; <ASMATTR>.<SIGNATTR><SIZEATTR><SUF>
;;
;;
;;---------------------------------------------------------------------
;;---------------------------------------------------------------------

(define_int_attr asmattr[
  (UNSPEC_VRECPEU  "vrecpe")
  (UNSPEC_VRECPES  "vrecpe")
  (UNSPEC_VRSQRTEU "vrsqrte")
  (UNSPEC_VRSQRTES "vrsqrte")
  (UNSPEC_VEXPEU   "vexpe")
  (UNSPEC_VEXPES   "vexpe")
  (UNSPEC_VCLSS     "vcls")
  (UNSPEC_VPADDEU  "vpadd")
  (UNSPEC_VPADDES  "vpadd")
  (UNSPEC_VPADDAEU "vpadda")
  (UNSPEC_VPADDAES "vpadda")
  (UNSPEC_VASXSS   "vasx")
  (UNSPEC_VASXUS   "vasx")
  (UNSPEC_VSAXUS   "vsax")
  (UNSPEC_VSAXSS   "vsax")
  (UNSPEC_VASXHS   "vasxh")
  (UNSPEC_VASXHU   "vasxh")
  (UNSPEC_VSAXHU   "vsaxh")
  (UNSPEC_VSAXHS   "vsaxh")
  (UNSPEC_VPMAXU   "vpmax")
  (UNSPEC_VPMAXS   "vpmax")
  (UNSPEC_VPMINU   "vpmin")
  (UNSPEC_VPMINS   "vpmin")
  (UNSPEC_VMULUH   "vmul")
  (UNSPEC_VMULSH   "vmul")
  (UNSPEC_VRMULHSS "vrmulh")
  (UNSPEC_VRMULHSRS    "vrmulh")
  (UNSPEC_VRMULHASRS   "vrmulha")
  (UNSPEC_VRMULHSSRS   "vrmulhs")
  (UNSPEC_VRMULXAASRS  "vrmulxaa")
  (UNSPEC_VRMULXASSRS  "vrmulxas")
  (UNSPEC_VRMULXSSSRS  "vrmulxss")
  (UNSPEC_VRMULXSASRS  "vrmulxsa")
  (UNSPEC_VRCMULSRS    "vrcmul")
  (UNSPEC_VRCMULCSRS   "vrcmulc")
  (UNSPEC_VRCMULNSRS   "vrcmuln")
  (UNSPEC_VRCMULCNSRS  "vrcmulcn")
  (UNSPEC_VRECPSS  "vrecps")
  (UNSPEC_VRECPSU  "vrecps")
  (UNSPEC_VRSQRTSS "vrsqrts")
  (UNSPEC_VRSQRTSU "vrsqrts")
  (UNSPEC_VTRN "vtrn")
  (UNSPEC_VPADDU   "vpadd")
  (UNSPEC_VPADDS   "vpadd")
  (UNSPEC_VPADDUS   "vpadd")
  (UNSPEC_VPADDSS   "vpadd")
  (UNSPEC_VSHTU    "vsht")
  (UNSPEC_VSHTS    "vsht")
  (UNSPEC_VSHTSS   "vsht")
  (UNSPEC_VSHTUS   "vsht")
  (UNSPEC_VSHTUR   "vsht")
  (UNSPEC_VSHTSR   "vsht")
  (UNSPEC_VSHTURS  "vsht")
  (UNSPEC_VSHTSRS  "vsht")
  (UNSPEC_VEXHS "vexh")
  (UNSPEC_VEXLS "vexl")
  (UNSPEC_VEXHU "vexh")
  (UNSPEC_VEXLU "vexl")
  (UNSPEC_VADDUH   "vadd")
  (UNSPEC_VSUBUH   "vsub")
  (UNSPEC_VADDSH   "vadd")
  (UNSPEC_VSUBSH   "vsub")
  (UNSPEC_VADDURH  "vadd")
  (UNSPEC_VSUBURH  "vsub")
  (UNSPEC_VADDSRH  "vadd")
  (UNSPEC_VSUBSRH  "vsub")
  (UNSPEC_VMOVTL    "vmov")
  (UNSPEC_VMOVTH    "vmov")
  (UNSPEC_VMOVSSL  "vmov")
  (UNSPEC_VMOVUSL  "vmov")
  (UNSPEC_VMOVURH  "vmov")
  (UNSPEC_VMOVSRH  "vmov")
  (UNSPEC_VRMULSSSE "vrmulss")
  (UNSPEC_VRMULSSE "vrmul")
  (UNSPEC_VRMULSHRSE "vrmulshr")
  (UNSPEC_VMULACAU "vmulaca")
  (UNSPEC_VMULACAS "vmulaca")
  (UNSPEC_VMULACAAU "vmulacaa")
  (UNSPEC_VMULACAAS "vmulacaa")
  (UNSPEC_VSELS    "vsel")
  (UNSPEC_VSELU    "vsel")
  (UNSPEC_VMASKIL  "vmaski")
  (UNSPEC_VMASKIH  "vmaski")
  (UNSPEC_VMOVIU   "vmovi")
  (UNSPEC_VMOVIS   "vmovi")
  (UNSPEC_VMASKI   "vmaski")
  (UNSPEC_VCLIPS    "vclip")
  (UNSPEC_VCLIPU    "vclip")
  (UNSPEC_VSHRIUR  "vshri")
  (UNSPEC_VSHRISR  "vshri")
  (UNSPEC_VSHRIAUR "vshria")
  (UNSPEC_VSHRIASR "vshria")
  (UNSPEC_VSHRISL  "vshri")
  (UNSPEC_VSHRIUL  "vshri")
  (UNSPEC_VSHRISLR "vshri")
  (UNSPEC_VSHRIULR "vshri")
  (UNSPEC_VSHRIULS "vshri")
  (UNSPEC_VSHRISLS "vshri")
  (UNSPEC_VSHRIULRS    "vshri")
  (UNSPEC_VSHRISLRS    "vshri")
  (UNSPEC_VMULIUH "vmuli")
  (UNSPEC_VMULISH "vmuli")
  (UNSPEC_VRMULHISS    "vrmulhi")
  (UNSPEC_VRMULHISRS   "vrmulhi")
  (UNSPEC_VRMULHAISRS  "vrmulhai")
  (UNSPEC_VRMULHSISRS  "vrmulhsi")
  (UNSPEC_VRMULXAAISRS "vrmulxaai")
  (UNSPEC_VRMULXASISRS "vrmulxasi")
  (UNSPEC_VRMULXSSISRS "vrmulxssi")
  (UNSPEC_VRMULXSAISRS "vrmulxsai")
  (UNSPEC_VEXTI "vexti")
  (UNSPEC_VTBL "vtbl")
  (UNSPEC_VTBX "vtbx")
  (UNSPEC_VRMULISSE    "vrmuli")
  (UNSPEC_VRMULSASE    "vrmulsa")
  (UNSPEC_VRMULSHRISE  "vrmulshri")
  (UNSPEC_VRCMULASE    "vrcmula")
  (UNSPEC_VRCMULCASE   "vrcmulca")
  (UNSPEC_VRCMULNASE   "vrcmulna")
  (UNSPEC_VRCMULCNASE  "vrcmulcna")
  (UNSPEC_VMULACAIU    "vmulacai")
  (UNSPEC_VMULACAIS    "vmulacai")
  (UNSPEC_VMULACAAIU    "vmulacaai")
  (UNSPEC_VMULACAAIS    "vmulacaai")
  (UNSPEC_VRMULSAISE   "vrmulsai")
  (UNSPEC_VRMULSSISE   "vrmulssi")
  (UNSPEC_VSHRUR  "vshr")
  (UNSPEC_VSHRSR  "vshr")
]
)


(define_int_attr signattr[
  (UNSPEC_VRECPEU  "u")
  (UNSPEC_VRECPES  "s")
  (UNSPEC_VRSQRTEU "u")
  (UNSPEC_VRSQRTES "s")
  (UNSPEC_VEXPEU   "u")
  (UNSPEC_VEXPES   "s")
  (UNSPEC_VCLSS     "s")
  (UNSPEC_VPADDEU  "u")
  (UNSPEC_VPADDES  "s")
  (UNSPEC_VPADDAEU "u")
  (UNSPEC_VPADDAES "s")
  (UNSPEC_VASXSS   "s")
  (UNSPEC_VASXUS   "u")
  (UNSPEC_VSAXUS   "u")
  (UNSPEC_VSAXSS   "s")
  (UNSPEC_VASXHS   "s")
  (UNSPEC_VASXHU   "u")
  (UNSPEC_VSAXHU   "u")
  (UNSPEC_VSAXHS   "s")
  (UNSPEC_VPMAXU   "u")
  (UNSPEC_VPMAXS   "s")
  (UNSPEC_VPMINU   "u")
  (UNSPEC_VPMINS   "s")
  (UNSPEC_VMULUH   "u")
  (UNSPEC_VMULSH   "s")
  (UNSPEC_VRMULHSS "s")
  (UNSPEC_VRMULHSRS    "s")
  (UNSPEC_VRMULHASRS   "s")
  (UNSPEC_VRMULHSSRS   "s")
  (UNSPEC_VRMULXAASRS  "s")
  (UNSPEC_VRMULXASSRS  "s")
  (UNSPEC_VRMULXSSSRS  "s")
  (UNSPEC_VRMULXSASRS  "s")
  (UNSPEC_VRCMULSRS    "s")
  (UNSPEC_VRCMULCSRS   "s")
  (UNSPEC_VRCMULNSRS   "s")
  (UNSPEC_VRCMULCNSRS  "s")
  (UNSPEC_VRECPSS  "s")
  (UNSPEC_VRECPSU  "u")
  (UNSPEC_VRSQRTSS "s")
  (UNSPEC_VRSQRTSU "u")
  (UNSPEC_VTRN "")
  (UNSPEC_VPADDU   "u")
  (UNSPEC_VPADDS   "s")
  (UNSPEC_VPADDUS   "u")
  (UNSPEC_VPADDSS   "s")
  (UNSPEC_VSHTU    "u")
  (UNSPEC_VSHTS    "s")
  (UNSPEC_VSHTSS   "s")
  (UNSPEC_VSHTUS   "u")
  (UNSPEC_VSHTUR   "u")
  (UNSPEC_VSHTSR   "s")
  (UNSPEC_VSHTURS  "u")
  (UNSPEC_VSHTSRS  "s")
  (UNSPEC_VEXHU "")
  (UNSPEC_VEXLU "")
  (UNSPEC_VEXHS "")
  (UNSPEC_VEXLS "")
  (UNSPEC_VADDUH   "u")
  (UNSPEC_VSUBUH   "u")
  (UNSPEC_VADDSH   "s")
  (UNSPEC_VSUBSH   "s")
  (UNSPEC_VADDURH  "u")
  (UNSPEC_VSUBURH  "u")
  (UNSPEC_VADDSRH  "s")
  (UNSPEC_VSUBSRH  "s")
  (UNSPEC_VMOVTL    "")
  (UNSPEC_VMOVTH    "")
  (UNSPEC_VMOVSSL  "s")
  (UNSPEC_VMOVUSL  "u")
  (UNSPEC_VMOVURH  "u")
  (UNSPEC_VMOVSRH  "s")
  (UNSPEC_VRMULSSSE "s")
  (UNSPEC_VRMULSSE "s")
  (UNSPEC_VRMULSHRSE "s")
  (UNSPEC_VMULACAU "u")
  (UNSPEC_VMULACAS "s")
  (UNSPEC_VMULACAAU "u")
  (UNSPEC_VMULACAAS "s")
  (UNSPEC_VSELS    "")
  (UNSPEC_VSELU    "")
  (UNSPEC_VMASKIL  "")
  (UNSPEC_VMASKIH  "")
  (UNSPEC_VMOVIU   "u")
  (UNSPEC_VMOVIS   "s")
  (UNSPEC_VMASKI   "")
  (UNSPEC_VCLIPS    "s")
  (UNSPEC_VCLIPU    "u")
  (UNSPEC_VSHRIUR  "u")
  (UNSPEC_VSHRISR  "s")
  (UNSPEC_VSHRIAUR "u")
  (UNSPEC_VSHRIASR "s")
  (UNSPEC_VSHRISL  "s")
  (UNSPEC_VSHRIUL  "u")
  (UNSPEC_VSHRISLR "s")
  (UNSPEC_VSHRIULR "u")
  (UNSPEC_VSHRIULS "u")
  (UNSPEC_VSHRISLS "s")
  (UNSPEC_VSHRIULRS    "u")
  (UNSPEC_VSHRISLRS    "s")
  (UNSPEC_VMULIUH "u")
  (UNSPEC_VMULISH "s")
  (UNSPEC_VRMULHISS    "s")
  (UNSPEC_VRMULHISRS   "s")
  (UNSPEC_VRMULHAISRS  "s")
  (UNSPEC_VRMULHSISRS  "s")
  (UNSPEC_VRMULXAAISRS "s")
  (UNSPEC_VRMULXASISRS "s")
  (UNSPEC_VRMULXSSISRS "s")
  (UNSPEC_VRMULXSAISRS "s")
  (UNSPEC_VEXTI "")
  (UNSPEC_VTBL "")
  (UNSPEC_VTBX "")
  (UNSPEC_VRMULISSE    "s")
  (UNSPEC_VRMULSASE    "s")
  (UNSPEC_VRMULSHRISE  "s")
  (UNSPEC_VRCMULASE    "s")
  (UNSPEC_VRCMULCASE   "s")
  (UNSPEC_VRCMULNASE   "s")
  (UNSPEC_VRCMULCNASE  "s")
  (UNSPEC_VMULACAIU    "u")
  (UNSPEC_VMULACAIS    "s")
  (UNSPEC_VMULACAAIU    "u")
  (UNSPEC_VMULACAAIS    "s")
  (UNSPEC_VRMULSAISE   "s")
  (UNSPEC_VRMULSSISE   "s")
  (UNSPEC_VSHRUR  "u")
  (UNSPEC_VSHRSR  "s")
]
)


(define_int_attr sufattr[
  (UNSPEC_VRECPEU  "")
  (UNSPEC_VRECPES  "")
  (UNSPEC_VRSQRTEU "")
  (UNSPEC_VRSQRTES "")
  (UNSPEC_VEXPEU   "")
  (UNSPEC_VEXPES   "")
  (UNSPEC_VCLSS     "")
  (UNSPEC_VPADDEU  ".e")
  (UNSPEC_VPADDES  ".e")
  (UNSPEC_VPADDAEU ".e")
  (UNSPEC_VPADDAES ".e")
  (UNSPEC_VASXSS   ".s")
  (UNSPEC_VASXUS   ".s")
  (UNSPEC_VSAXUS   ".s")
  (UNSPEC_VSAXSS   ".s")
  (UNSPEC_VASXHS   "")
  (UNSPEC_VASXHU   "")
  (UNSPEC_VSAXHU   "")
  (UNSPEC_VSAXHS   "")
  (UNSPEC_VPMAXU   "")
  (UNSPEC_VPMAXS   "")
  (UNSPEC_VPMINU   "")
  (UNSPEC_VPMINS   "")
  (UNSPEC_VMULUH   ".h")
  (UNSPEC_VMULSH   ".h")
  (UNSPEC_VRMULHSS ".s")
  (UNSPEC_VRMULHSRS    ".rs")
  (UNSPEC_VRMULHASRS   ".rs")
  (UNSPEC_VRMULHSSRS   ".rs")
  (UNSPEC_VRMULXAASRS  ".rs")
  (UNSPEC_VRMULXASSRS  ".rs")
  (UNSPEC_VRMULXSSSRS  ".rs")
  (UNSPEC_VRMULXSASRS  ".rs")
  (UNSPEC_VRCMULSRS    ".rs")
  (UNSPEC_VRCMULCSRS   ".rs")
  (UNSPEC_VRCMULNSRS   ".rs")
  (UNSPEC_VRCMULCNSRS  ".rs")
  (UNSPEC_VRECPSS  "")
  (UNSPEC_VRECPSU  "")
  (UNSPEC_VRSQRTSS "")
  (UNSPEC_VRSQRTSU "")
  (UNSPEC_VTRN "")
  (UNSPEC_VPADDU   "")
  (UNSPEC_VPADDS   "")
  (UNSPEC_VPADDUS   ".s")
  (UNSPEC_VPADDSS   ".s")
  (UNSPEC_VSHTU    "")
  (UNSPEC_VSHTS    "")
  (UNSPEC_VSHTSS   ".s")
  (UNSPEC_VSHTUS   ".s")
  (UNSPEC_VSHTUR   ".r")
  (UNSPEC_VSHTSR   ".r")
  (UNSPEC_VSHTURS  ".rs")
  (UNSPEC_VSHTSRS  ".rs")
  (UNSPEC_VEXHS "")
  (UNSPEC_VEXLS "")
  (UNSPEC_VEXHU "")
  (UNSPEC_VEXLU "")
  (UNSPEC_VADDUH   ".h")
  (UNSPEC_VSUBUH   ".h")
  (UNSPEC_VADDSH   ".h")
  (UNSPEC_VSUBSH   ".h")
  (UNSPEC_VADDURH  ".rh")
  (UNSPEC_VSUBURH  ".rh")
  (UNSPEC_VADDSRH  ".rh")
  (UNSPEC_VSUBSRH  ".rh")
  (UNSPEC_VMOVTL    ".l")
  (UNSPEC_VMOVTH    ".h")
  (UNSPEC_VMOVSSL  ".sl")
  (UNSPEC_VMOVUSL  ".sl")
  (UNSPEC_VMOVURH  ".rh")
  (UNSPEC_VMOVSRH  ".rh")
  (UNSPEC_VRMULSSSE ".e")
  (UNSPEC_VRMULSSE ".se")
  (UNSPEC_VRMULSHRSE ".e")
  (UNSPEC_VMULACAU "")
  (UNSPEC_VMULACAS "")
  (UNSPEC_VMULACAAU "")
  (UNSPEC_VMULACAAS "")
  (UNSPEC_VSELS    "")
  (UNSPEC_VSELU    "")
  (UNSPEC_VMASKIL  ".l")
  (UNSPEC_VMASKIH  ".h")
  (UNSPEC_VMOVIU   "")
  (UNSPEC_VMOVIS   "")
  (UNSPEC_VMASKI   "")
  (UNSPEC_VCLIPS    "")
  (UNSPEC_VCLIPU    "")
  (UNSPEC_VSHRIUR  ".r")
  (UNSPEC_VSHRISR  ".r")
  (UNSPEC_VSHRIAUR ".r")
  (UNSPEC_VSHRIASR ".r")
  (UNSPEC_VSHRISL  ".l")
  (UNSPEC_VSHRIUL  ".l")
  (UNSPEC_VSHRISLR ".lr")
  (UNSPEC_VSHRIULR ".lr")
  (UNSPEC_VSHRIULS ".ls")
  (UNSPEC_VSHRISLS ".ls")
  (UNSPEC_VSHRIULRS    ".lrs")
  (UNSPEC_VSHRISLRS    ".lrs")
  (UNSPEC_VMULIUH ".h")
  (UNSPEC_VMULISH ".h")
  (UNSPEC_VRMULHISS    ".s")
  (UNSPEC_VRMULHISRS   ".rs")
  (UNSPEC_VRMULHAISRS  ".rs")
  (UNSPEC_VRMULHSISRS  ".rs")
  (UNSPEC_VRMULXAAISRS ".rs")
  (UNSPEC_VRMULXASISRS ".rs")
  (UNSPEC_VRMULXSSISRS ".rs")
  (UNSPEC_VRMULXSAISRS ".rs")
  (UNSPEC_VEXTI "")
  (UNSPEC_VTBL "")
  (UNSPEC_VTBX "")
  (UNSPEC_VRMULISSE    ".se")
  (UNSPEC_VRMULSASE    ".e")
  (UNSPEC_VRMULSHRISE  ".e")
  (UNSPEC_VRCMULASE    ".e")
  (UNSPEC_VRCMULCASE   ".e")
  (UNSPEC_VRCMULNASE   ".e")
  (UNSPEC_VRCMULCNASE  ".e")
  (UNSPEC_VMULACAIU    "")
  (UNSPEC_VMULACAIS    "")
  (UNSPEC_VMULACAAIU    "")
  (UNSPEC_VMULACAAIS    "")
  (UNSPEC_VRMULSAISE   ".e")
  (UNSPEC_VRMULSSISE   ".e")
  (UNSPEC_VSHRUR  ".r")
  (UNSPEC_VSHRSR  ".r")
]
)

(define_int_attr insnattr[
  (UNSPEC_VRECPEU  "vrecpeu")
  (UNSPEC_VRECPES  "vrecpes")
  (UNSPEC_VRSQRTEU "vrsqrteu")
  (UNSPEC_VRSQRTES "vrsqrtes")
  (UNSPEC_VEXPEU   "vexpeu")
  (UNSPEC_VEXPES   "vexpes")
  (UNSPEC_VCLSS     "vclss")
  (UNSPEC_VPADDEU  "vpaddeu")
  (UNSPEC_VPADDES  "vpaddes")
  (UNSPEC_VPADDAEU "vpaddaeu")
  (UNSPEC_VPADDAES "vpaddaes")
  (UNSPEC_VASXSS   "vasxss")
  (UNSPEC_VASXUS   "vasxus")
  (UNSPEC_VSAXUS   "vsaxus")
  (UNSPEC_VSAXSS   "vsaxss")
  (UNSPEC_VASXHS   "vasxhs")
  (UNSPEC_VASXHU   "vasxhu")
  (UNSPEC_VSAXHU   "vsaxhu")
  (UNSPEC_VSAXHS   "vsaxhs")
  (UNSPEC_VPMAXU   "vpmaxu")
  (UNSPEC_VPMAXS   "vpmaxs")
  (UNSPEC_VPMINU   "vpminu")
  (UNSPEC_VPMINS   "vpmins")
  (UNSPEC_VMULUH   "vmuluh")
  (UNSPEC_VMULSH   "vmulsh")
  (UNSPEC_VRMULHSS "vrmulhss")
  (UNSPEC_VRMULHSRS    "vrmulhsrs")
  (UNSPEC_VRMULHASRS   "vrmulhasrs")
  (UNSPEC_VRMULHSSRS   "vrmulhssrs")
  (UNSPEC_VRMULXAASRS  "vrmulxaasrs")
  (UNSPEC_VRMULXASSRS  "vrmulxassrs")
  (UNSPEC_VRMULXSSSRS  "vrmulxsssrs")
  (UNSPEC_VRMULXSASRS  "vrmulxsasrs")
  (UNSPEC_VRCMULSRS    "vrcmulsrs")
  (UNSPEC_VRCMULCSRS   "vrcmulcsrs")
  (UNSPEC_VRCMULNSRS   "vrcmulnsrs")
  (UNSPEC_VRCMULCNSRS  "vrcmulcnsrs")
  (UNSPEC_VRECPSS  "vrecpss")
  (UNSPEC_VRECPSU  "vrecpsu")
  (UNSPEC_VRSQRTSS "vrsqrtss")
  (UNSPEC_VRSQRTSU "vrsqrtsu")
  (UNSPEC_VTRN "vtrn")
  (UNSPEC_VPADDU   "vpaddu")
  (UNSPEC_VPADDS   "vpadds")
  (UNSPEC_VPADDUS   "vpaddus")
  (UNSPEC_VPADDSS   "vpaddss")
  (UNSPEC_VSHTU    "vshtu")
  (UNSPEC_VSHTS    "vshts")
  (UNSPEC_VSHTSS   "vshtss")
  (UNSPEC_VSHTUS   "vshtus")
  (UNSPEC_VSHTUR   "vshtur")
  (UNSPEC_VSHTSR   "vshtsr")
  (UNSPEC_VSHTURS  "vshturs")
  (UNSPEC_VSHTSRS  "vshtsrs")
  (UNSPEC_VEXHS "vexhs")
  (UNSPEC_VEXLS "vexls")
  (UNSPEC_VEXHU "vexhu")
  (UNSPEC_VEXLU "vexlu")
  (UNSPEC_VADDUH   "vadduh")
  (UNSPEC_VSUBUH   "vsubuh")
  (UNSPEC_VADDSH   "vaddsh")
  (UNSPEC_VSUBSH   "vsubsh")
  (UNSPEC_VADDURH  "vaddurh")
  (UNSPEC_VSUBURH  "vsuburh")
  (UNSPEC_VADDSRH  "vaddsrh")
  (UNSPEC_VSUBSRH  "vsubsrh")
  (UNSPEC_VMOVTL    "vmovtl")
  (UNSPEC_VMOVTH    "vmovth")
  (UNSPEC_VMOVSSL  "vmovssl")
  (UNSPEC_VMOVUSL  "vmovusl")
  (UNSPEC_VMOVURH  "vmovurh")
  (UNSPEC_VMOVSRH  "vmovsrh")
  (UNSPEC_VRMULSSSE "vrmulssse")
  (UNSPEC_VRMULSSE "vrmulsse")
  (UNSPEC_VRMULSHRSE "vrmulshrse")
  (UNSPEC_VMULACAU "vmulacau")
  (UNSPEC_VMULACAS "vmulacas")
  (UNSPEC_VMULACAAU "vmulacaau")
  (UNSPEC_VMULACAAS "vmulacaas")
  (UNSPEC_VSELS    "vsels")
  (UNSPEC_VSELU    "vselu")
  (UNSPEC_VMASKIL  "vmaskil")
  (UNSPEC_VMASKIH  "vmaskih")
  (UNSPEC_VMOVIU   "vmoviu")
  (UNSPEC_VMOVIS   "vmovis")
  (UNSPEC_VMASKI   "vmaski")
  (UNSPEC_VCLIPS    "vclips")
  (UNSPEC_VCLIPU    "vclipu")
  (UNSPEC_VSHRIUR  "vshriur")
  (UNSPEC_VSHRISR  "vshrisr")
  (UNSPEC_VSHRIAUR "vshriaur")
  (UNSPEC_VSHRIASR "vshriasr")
  (UNSPEC_VSHRISL  "vshrisl")
  (UNSPEC_VSHRIUL  "vshriul")
  (UNSPEC_VSHRISLR "vshrislr")
  (UNSPEC_VSHRIULR "vshriulr")
  (UNSPEC_VSHRIULS "vshriuls")
  (UNSPEC_VSHRISLS "vshrisls")
  (UNSPEC_VSHRIULRS    "vshriulrs")
  (UNSPEC_VSHRISLRS    "vshrislrs")
  (UNSPEC_VMULIUH "vmuliuh")
  (UNSPEC_VMULISH "vmulish")
  (UNSPEC_VRMULHISS    "vrmulhiss")
  (UNSPEC_VRMULHISRS   "vrmulhisrs")
  (UNSPEC_VRMULHAISRS  "vrmulhaisrs")
  (UNSPEC_VRMULHSISRS  "vrmulhsisrs")
  (UNSPEC_VRMULXAAISRS "vrmulxaaisrs")
  (UNSPEC_VRMULXASISRS "vrmulxasisrs")
  (UNSPEC_VRMULXSSISRS "vrmulxssisrs")
  (UNSPEC_VRMULXSAISRS "vrmulxsaisrs")
  (UNSPEC_VEXTI "vexti")
  (UNSPEC_VTBL "vtbl")
  (UNSPEC_VTBX "vtbx")
  (UNSPEC_VRMULISSE    "vrmulisse")
  (UNSPEC_VRMULSASE    "vrmulsase")
  (UNSPEC_VRMULSHRISE  "vrmulshrise")
  (UNSPEC_VRCMULASE    "vrcmulase")
  (UNSPEC_VRCMULCASE   "vrcmulcase")
  (UNSPEC_VRCMULNASE   "vrcmulnase")
  (UNSPEC_VRCMULCNASE  "vrcmulcnase")
  (UNSPEC_VMULACAIU    "vmulacaiu")
  (UNSPEC_VMULACAIS    "vmulacais")
  (UNSPEC_VMULACAAIU    "vmulacaaiu")
  (UNSPEC_VMULACAAIS    "vmulacaais")
  (UNSPEC_VRMULSAISE   "vrmulsaise")
  (UNSPEC_VRMULSSISE   "vrmulssise")
  (UNSPEC_VSHRUR  "vshrur")
  (UNSPEC_VSHRSR  "vshrsr")
]
)
