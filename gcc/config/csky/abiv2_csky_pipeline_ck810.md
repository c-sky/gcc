;;-------------------------------------------------------------
;; Pipeline descriptions for ck810
;;-------------------------------------------------------------

(define_attr "cycle" "1,2,not_used_yet"
    (const_string "1"))
(define_automaton "cskyv2_ck810")
(define_cpu_unit "pipeline_alu0" "cskyv2_ck810")
(define_insn_reservation "alu_one_cycle" 1
    (and (eq_attr "cycle" "1")
         (not (ior (match_test "CSKY_TARGET_ARCH(CK803)")
                   (match_test "CSKY_TARGET_ARCH(CK802)"))))
    "pipeline_alu0")
