
(define_automaton "ck810")

(define_cpu_unit "ck810_p0_ex1, ck810_p0_ex2" "ck810")
(define_cpu_unit "ck810_p1_ex1, ck810_p1_ex2" "ck810")
(define_cpu_unit "ck810_p0_wb, ck810_p1_wb" "ck810")

(define_cpu_unit "ck810_lsu_ex1, ck810_lsu_ex2, ck810_lsu_ex3, ck810_lsu_ex4" "ck810")
(define_cpu_unit "ck810_lsu_wb" "ck810")

(define_cpu_unit "ck810_mad_ex1, ck810_mad_ex2, ck810_mad_ex3, ck810_mad_ex4" "ck810")
(define_cpu_unit "ck810_bju_ex1, ck810_bju_ex2" "ck810")

(define_reservation "ck810_p0_default" "ck810_p0_ex1, ck810_p0_wb")
(define_reservation "ck810_p1_default" "ck810_p1_ex1, ck810_p1_wb")
(define_reservation "ck810_p0_2" "ck810_p0_ex1, ck810_p0_ex2, ck810_p0_wb")
(define_reservation "ck810_p1_2" "ck810_p1_ex1, ck810_p1_ex2, ck810_p1_wb")
(define_reservation "ck810_lsu_default" "ck810_lsu_ex1, ck810_lsu_ex2, ck810_lsu_ex3, ck810_lsu_wb")
(define_reservation "ck810_mad_default" "ck810_mad_ex1, ck810_mad_ex2, ck810_mad_ex3, ck810_mad_ex4")
(define_reservation "ck810_mad_div" "ck810_mad_ex1 + ck810_mad_ex2 + ck810_mad_ex3 + ck810_mad_ex4")

(define_insn_reservation "ck810_alu" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "alu,addsub,sexth,lslr"))
  "ck810_p0_default|ck810_p1_default")

(define_insn_reservation "ck810_alu_2" 3
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "caddsub, zext, sext, ins"))
  "ck810_p0_2|ck810_p1_2")

(define_insn_reservation "ck810_load" 4
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "load"))
  "ck810_lsu_default")

(define_insn_reservation "ck810_store" 3
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "store"))
  "ck810_lsu_ex1, ck810_lsu_ex2, ck810_lsu_wb")

(define_insn_reservation "ck810_load_4" 5
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "loadr, loadi"))
  "ck810_lsu_ex1, ck810_lsu_ex2, ck810_lsu_ex3, ck810_lsu_ex4, ck810_lsu_wb")

(define_insn_reservation "ck810_mul" 5
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "mul"))
  "ck810_mad_default, (ck810_p0_wb | ck810_p1_wb)")

(define_insn_reservation "ck810_div" 20
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "div"))
  "ck810_mad_div * 19, (ck810_p0_wb | ck810_p1_wb)")

(define_insn_reservation "ck810_jmp_2" 3
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "branch, branch_jmp, cbranch"))
  "ck810_bju_ex1, ck810_bju_ex2, (ck810_p0_wb | ck810_p1_wb)")

(define_insn_reservation "ck810_jmp_r15" 3
  (and  (match_test "CSKY_TARGET_ARCH(CK810)")
        (eq_attr "type" "call, call_jsr"))
  "ck810_bju_ex1, ck810_bju_ex2, (ck810_p0_wb | ck810_p1_wb)")

(define_bypass 1 "ck810_alu" "ck810_*")
(define_bypass 2 "ck810_alu_2" "ck810_*")
(define_bypass 2 "ck810_jmp_r15" "ck810_*")

(define_bypass 5 "ck810_load" "ck810_*")
(define_bypass 6 "ck810_load_4" "ck810_*")


;;-------------------------------------------------------------
;; Pipeline descriptions for ckdefault
;;-------------------------------------------------------------

(define_attr "cycle" "1,2,not_used_yet"
    (const_string "1"))
(define_automaton "ckdefault")
(define_cpu_unit "pipeline_alu0" "ckdefault")
(define_insn_reservation "alu_one_cycle" 1
    (and (eq_attr "cycle" "1")
         (not (match_test "CSKY_TARGET_ARCH(CK802)
                           || CSKY_TARGET_ARCH(CK803)
                           || CSKY_TARGET_ARCH(CK805)
                           || CSKY_TARGET_ARCH(CK807)
                           || CSKY_TARGET_ARCH(CK810)
                           || CSKY_TARGET_ARCH(CK860)")))
    "pipeline_alu0")
