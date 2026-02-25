(define_mode_iterator F3ANY [HF SF DF])
(define_mode_attr f3t [(HF "16") (SF "32") (DF "64")])

(define_mode_iterator SFDF [SF DF])
(define_mode_attr f2t [(SF "32") (DF "64")])

(define_code_iterator FCMPZ [ne ge lt gt le])
(define_code_attr zero_inst [(ne "nez") (ge "hsz") (lt "ltz") (gt "hz") (le "lsz")])

(define_code_iterator FCMP [ne ge lt])
(define_code_attr reg_inst [(ne "ne") (ge "hs") (lt "lt")])

(define_code_iterator FIX_SU [fix unsigned_fix])
(define_code_attr fixsuop [(fix "")  (unsigned_fix "uns")])
(define_code_attr fixsu   [(fix "s") (unsigned_fix "u")])

(define_code_iterator FLOAT_SU [float unsigned_float])
(define_code_attr floatsuop [(float "")  (unsigned_float "uns")])
(define_code_attr floatsu   [(float "s") (unsigned_float "u")])

(define_int_iterator FRM  [UNSPEC_FLOOR
                           UNSPEC_CEIL UNSPEC_RINT])

(define_int_iterator FRMF [UNSPEC_FLOOR
                           UNSPEC_CEIL UNSPEC_BTRUNC])

(define_int_attr frm_pattern [(UNSPEC_FLOOR "floor")
                              (UNSPEC_CEIL "ceil")   (UNSPEC_BTRUNC "btrunc")
                              (UNSPEC_RINT "rint")])

(define_int_attr rm [(UNSPEC_FLOOR ".rni")
                     (UNSPEC_CEIL ".rpi")  (UNSPEC_BTRUNC ".rz")
                     (UNSPEC_RINT "")])
;; -------------------------------------------------------------------------
;; Float mov instructions
;; -------------------------------------------------------------------------

(define_expand "movhf"
  [(set (match_operand:HF 0 "general_operand" "")
        (match_operand:HF 1 "general_operand" ""))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  "
  {
    if (GET_CODE(operands[0]) == MEM && can_create_pseudo_p ())
      {
        operands[1] = force_reg (HFmode, operands[1]);
      }
  }
")

(define_expand "mov<mode>"
  [(set (match_operand:SFDF 0 "general_operand" "")
        (match_operand:SFDF 1 "general_operand" ""))]
  "CSKY_ISA_FEATURE(fpv2_<mode>)
   || CSKY_ISA_FEATURE(fpv3_<mode>)"
  "
  {
    if (GET_CODE(operands[0]) == MEM && can_create_pseudo_p ())
      {
        operands[1] = force_reg (<MODE>mode, operands[1]);
      }
  }
")

;; -------------------------------------------------------------------------
;; Float Mul instructions
;; -------------------------------------------------------------------------

(define_expand "mulhf3"
  [(set (match_operand:HF            0 "register_operand" "=v")
        (mult:HF (match_operand:HF   1 "register_operand" "v")
                 (match_operand:HF   2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  "")

(define_expand "mul<mode>3"
  [(set (match_operand:SFDF            0 "register_operand" "=v")
        (mult:SFDF (match_operand:SFDF   1 "register_operand" "v")
                 (match_operand:SFDF   2 "register_operand" "v")))]
  "CSKY_ISA_FEATURE(fpv2_<mode>)
  || CSKY_ISA_FEATURE(fpv3_<mode>)"
  "")

(define_expand "fma<mode>4"
  [(set (match_operand:F3ANY            0 "register_operand" "=v")
        (fma:F3ANY (match_operand:F3ANY  1 "register_operand" "v")
                   (match_operand:F3ANY  2 "register_operand" "v")
                   (match_operand:F3ANY  3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(fpv3_<mode>)"
  "")

;; -------------------------------------------------------------------------
;; Float ADD SUB NEG ABS instructions
;; -------------------------------------------------------------------------

(define_expand "addhf3"
  [(set (match_operand:HF           0 "register_operand" "")
        (plus:HF (match_operand:HF  1 "register_operand" "")
                 (match_operand:HF  2 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  ""
)

(define_expand "add<mode>3"
  [(set (match_operand:SFDF             0 "register_operand" "")
        (plus:SFDF (match_operand:SFDF  1 "register_operand" "")
                   (match_operand:SFDF  2 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
  ""
)

(define_expand "subhf3"
  [(set (match_operand:HF            0 "register_operand" "")
        (minus:HF (match_operand:HF  1 "register_operand" "")
                  (match_operand:HF  2 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  ""
)

(define_expand "sub<mode>3"
  [(set (match_operand:SFDF              0 "register_operand" "")
        (minus:SFDF (match_operand:SFDF  1 "register_operand" "")
                    (match_operand:SFDF  2 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
  ""
)

(define_expand "abshf2"
  [(set (match_operand:HF           0 "register_operand" "")
        (abs:HF (match_operand:HF   1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  ""
)

(define_expand "abs<mode>2"
  [(set (match_operand:SFDF             0 "register_operand" "")
        (abs:SFDF (match_operand:SFDF   1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
  ""
)

(define_expand "neghf2"
  [(set (match_operand:HF           0 "register_operand" "")
        (neg:HF (match_operand:HF   1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  ""
)

(define_expand "neg<mode>2"
  [(set (match_operand:SFDF           0 "register_operand" "")
        (neg:SFDF (match_operand:SFDF 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
  ""
)

(define_expand "sqrthf2"
  [(set (match_operand:HF           0 "register_operand" "")
        (sqrt:HF (match_operand:HF  1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  ""
)

(define_expand "sqrt<mode>2"
  [(set (match_operand:SFDF            0 "register_operand" "")
        (sqrt:SFDF (match_operand:SFDF 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
  ""
)

;; -------------------------------------------------------------------------
;; Float div instructions
;; -------------------------------------------------------------------------

(define_expand "div<mode>3"
  [(set (match_operand:SFDF           0 "register_operand" "")
        (div:SFDF (match_operand:SFDF 1 "csky_arith_float1_operand" "")
                  (match_operand:SFDF 2 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
  "")

(define_expand "divhf3"
 [(set (match_operand:HF 0 "register_operand" "")
       (div:HF (match_operand:HF 1 "csky_arith_float1_operand" "")
               (match_operand:HF 2 "register_operand" "")))]
 "CSKY_ISA_FEATURE(fpv3_hf)"
 "")

;; -------------------------------------------------------------------------
;; Float compare instructions
;; -------------------------------------------------------------------------

(define_expand "cbranch<mode>4"
  [(set (pc) (if_then_else (match_operator 0 "csky_float_comparison_operator"
                            [(match_operand:SFDF 1 "register_operand")
                             (match_operand:SFDF 2 "csky_compare_operand_float")])
                           (label_ref (match_operand 3 ""))
                           (pc)))]
"CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
"{
  enum rtx_code code = GET_CODE (operands[0]);
  bool invert;

  invert = gen_csky_compare_float (code, operands[1], operands[2]);

  if (invert)
    emit_jump_insn (gen_csky_jbf (operands[3]));
  else
    emit_jump_insn (gen_csky_jbt (operands[3]));

  DONE;

}")

(define_expand "cbranchhf4"
  [(set (pc) (if_then_else (match_operator 0 "csky_float_comparison_operator"
                            [(match_operand:HF 1 "register_operand")
                             (match_operand:HF 2 "csky_compare_operand_float")])
                           (label_ref (match_operand 3 ""))
                           (pc)))]
"CSKY_ISA_FEATURE(fpv3_hf)"
"{
  enum rtx_code code = GET_CODE (operands[0]);
  bool invert;

  invert = gen_csky_compare_float (code, operands[1], operands[2]);

  if (invert)
    emit_jump_insn (gen_csky_jbf (operands[3]));
  else
    emit_jump_insn (gen_csky_jbt (operands[3]));

  DONE;

}")

;; -------------------------------------------------------------------------
;; Float convert instructions
;; -------------------------------------------------------------------------

;; SF <- HF
(define_expand "extendhfsf2"
  [(set (match_operand:SF                  0 "register_operand" "")
        (float_extend:SF (match_operand:HF 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  "")

;; HF <- SF
(define_expand "truncsfhf2"
  [(set (match_operand:HF                     0 "register_operand" "")
        (float_truncate:HF (match_operand:SF 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  "")

;; DF <- SF
(define_expand "extendsfdf2"
  [(set (match_operand:DF                  0 "register_operand" "")
        (float_extend:DF (match_operand:SF 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_df) || CSKY_ISA_FEATURE(fpv3_df)"
  "")

;; SF <- DF
(define_expand "truncdfsf2"
  [(set (match_operand:SF                    0 "register_operand" "")
        (float_truncate:SF (match_operand:DF 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_df) || CSKY_ISA_FEATURE(fpv3_df)"
  "")

;; HF <- unsigned SI,SI
(define_expand "float<floatsuop>sihf2"
  [(set (match_operand:HF           0 "register_operand" "")
        (FLOAT_SU:HF (match_operand:SI 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  "")

;; DF,SF <- unsigned SI,SI
(define_expand "float<floatsuop>si<mode>2"
  [(set (match_operand:SFDF                    0 "register_operand" "")
        (FLOAT_SU:SFDF (match_operand:SI 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
  "")

;; DF,SF,HF <- unsigned HI,HI
(define_expand "float<floatsuop>hi<mode>2"
  [(set (match_operand:F3ANY           0 "register_operand" "")
        (FLOAT_SU:F3ANY (match_operand:HI 1 "register_operand" "")))]
  "CSKY_ISA_FEATURE(fpv3_<mode>) && CSKY_ISA_FEATURE(fpv3_hi)"
  "")

;; unsigned SI,SI <- HF
(define_expand "fix<fixsuop>_trunchfsi2"
  [(set (match_operand:SI            0 "register_operand" "")
        (FIX_SU:SI (fix:HF (match_operand:HF 1 "register_operand" ""))))]
  "CSKY_ISA_FEATURE(fpv3_hf)"
  "")

;; unsigned SI,SI <- DF,SF
(define_expand "fix<fixsuop>_trunc<mode>si2"
  [(set (match_operand:SI            0 "register_operand" "")
        (FIX_SU:SI (fix:SFDF (match_operand:SFDF 1 "register_operand" ""))))]
  "CSKY_ISA_FEATURE(fpv2_<mode>) || CSKY_ISA_FEATURE(fpv3_<mode>)"
  "")

(include "fpuv3.md")
(include "fpuv2.md")
