
;; -------------------------------------------------------------------------
;; SImode signed integer comparisons
;; -------------------------------------------------------------------------

(define_insn "*cmpnesi_r"
  [(set (reg:CC 33) (ne:CC (match_operand:SI 0 "register_operand" "b,r")
                           (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "@
    cmpne\t%0, %1
    cmpne\t%0, %1"
  [(set_attr "length" "2,4")]
)

;;cmpnei is 0-31 for Smart MODE
(define_insn "*smart_cmpnesi_i"
  [(set (reg:CC 33)  (ne:CC (match_operand:SI 0 "register_operand"       "a")
                            (match_operand:SI 1 "csky_literal_K_operand" "K")))]
  "TARGET_SMART || CSKY_ISA_FEATURE_GET2MD(ck801)"
  "cmpnei\t%0, %1"
)

;;cmpnei is 0 - 65536 for Fast MODE
(define_insn "*fast_cmpnesi_i"
  [(set (reg:CC 33) (ne:CC (match_operand:SI 0 "register_operand"       "r")
                           (match_operand:SI 1 "csky_literal_I_operand" "I")))]
  "!TARGET_SMART && !CSKY_ISA_FEATURE_GET2MD(ck801)"
  "cmpnei\t%0, %1"
)

(define_insn "*cmpgtsi"
  [(set (reg:CC 33) (gt:CC (match_operand:SI 0 "register_operand" "b,r")
                           (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmplt\t%1, %0"
  [(set_attr "length" "2,4")]
)

(define_insn "*cmpltsi_r"
  [(set (reg:CC 33) (lt:CC (match_operand:SI 0 "register_operand" "b,r")
                           (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmplt\t%0, %1"
  [(set_attr "length" "2,4")]
)

;;cmplti is 1-32 for Smart MODE
(define_insn "*smart_cmpltsi_i"
  [(set (reg:CC 33) (lt:CC (match_operand:SI 0 "register_operand"       "a")
                           (match_operand:SI 1 "csky_literal_J_operand" "J")))]
  "TARGET_SMART || CSKY_ISA_FEATURE_GET2MD(ck801)"
  "cmplti\t%0, %1"
  [(set_attr "length" "2")]
)


;;cmplti is 1-65536 for Fast MODE
(define_insn "*fast_cmpltsi_i"
  [(set (reg:CC 33) (lt:CC (match_operand:SI 0 "register_operand"        "a,r")
                           (match_operand:SI 1 "csky_literal_Uk_operand" "J,Uk")))]
  "!TARGET_SMART && !CSKY_ISA_FEATURE_GET2MD(ck801)"
  "cmplti\t%0, %1"
  [(set_attr "length" "2,4")]
)

; covers cmplti x,0
(define_insn "*cskyv2_cmpltsi_0"
  [(set (reg:CC 33) (lt:CC (match_operand:SI 0 "register_operand" "r")
                           (const_int 0)))]
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
  "btsti\t%0, 31"
)

(define_insn "*ck801_cmpltsi_0"
  [(set (reg:CC 33) (lt:CC (match_operand:SI 0 "register_operand" "a")
                           (const_int 0)))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
  "btsti\t%0, 31"
)


;; -------------------------------------------------------------------------
;; SImode unsigned integer comparisons
;; -------------------------------------------------------------------------

(define_insn "*cmpgeusi_r"
  [(set (reg:CC 33) (geu:CC (match_operand:SI 0 "register_operand" "b,r")
                            (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmphs\t%0, %1"
  [(set_attr "length" "2,4")]
) 

(define_insn "*smart_cmpgeusi_i"
  [(set (reg:CC 33) (geu:CC (match_operand:SI 0 "register_operand"       "a")
                            (match_operand:SI 1 "csky_literal_J_operand" "J")))]
  "TARGET_SMART || CSKY_ISA_FEATURE_GET2MD(ck801)"
  "cmphsi\t%0, %1"
  [(set_attr "length" "2")]
)

(define_insn "*fast_cmpgeusi_i"
  [(set (reg:CC 33) (geu:CC (match_operand:SI 0 "register_operand"        "a,r")
                            (match_operand:SI 1 "csky_literal_Uk_operand" "J,Uk")))]
  "!TARGET_SMART && !CSKY_ISA_FEATURE_GET2MD(ck801)"
  "cmphsi\t%0, %1"
  [(set_attr "length" "2,4")]
)

(define_insn "*cmpleusi"
  [(set (reg:CC 33) (leu:CC (match_operand:SI 0 "register_operand" "b,r")
                            (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmphs\t%1, %0"
  [(set_attr "length" "2,4")]
) 
