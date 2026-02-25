
(define_automaton "ck807")

(define_cpu_unit "ck807_p0_ex1" "ck807")
(define_cpu_unit "ck807_p1_ex1" "ck807")
(define_cpu_unit "ck807_p0_wb, ck807_p1_wb" "ck807")

(define_cpu_unit "ck807_lsu_ex1, ck807_lsu_ex2, ck807_lsu_ex3" "ck807")
(define_cpu_unit "ck807_lsu_wb" "ck807")

(define_cpu_unit "ck807_mad_ex1, ck807_mad_ex2, ck807_mad_ex3" "ck807")
(define_cpu_unit "ck807_bju_ex1" "ck807")

(define_reservation "ck807_p0_default" "ck807_p0_ex1, ck807_p0_wb")
(define_reservation "ck807_p1_default" "ck807_p1_ex1, ck807_p1_wb")
(define_reservation "ck807_lsu_default" "ck807_lsu_ex1, ck807_lsu_ex2, ck807_lsu_ex3, ck807_lsu_wb")
(define_reservation "ck807_mad_default" "ck807_mad_ex1, ck807_mad_ex2, ck807_mad_ex3")
(define_reservation "ck807_mad_div" "ck807_mad_ex1 + ck807_mad_ex2 + ck807_mad_ex3")

(define_insn_reservation "ck807_alu" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK807)")
        (eq_attr "type" "alu,zext,sext,ins,sexth,lslr,addsub,caddsub,cmp"))
  "ck807_p0_default|ck807_p1_default")

(define_insn_reservation "ck807_load" 4
  (and  (match_test "CSKY_TARGET_ARCH(CK807)")
        (eq_attr "type" "load, loadr, loadi"))
  "ck807_lsu_default")

(define_insn_reservation "ck807_store" 3
  (and  (match_test "CSKY_TARGET_ARCH(CK807)")
        (eq_attr "type" "store"))
  "ck807_lsu_ex1, ck807_lsu_ex2, ck807_lsu_wb")

(define_insn_reservation "ck807_mul" 4
  (and  (match_test "CSKY_TARGET_ARCH(CK807)")
        (eq_attr "type" "mul"))
  "ck807_mad_default, (ck807_p0_wb | ck807_p1_wb)")

(define_insn_reservation "ck807_div" 20
  (and  (match_test "CSKY_TARGET_ARCH(CK807)")
        (eq_attr "type" "div"))
  "ck807_mad_div * 19, (ck807_p0_wb | ck807_p1_wb)")

(define_insn_reservation "ck807_jmp_2" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK807)")
        (eq_attr "type" "branch, branch_jmp, cbranch"))
  "ck807_bju_ex1, (ck807_p0_wb | ck807_p1_wb)")

(define_insn_reservation "ck807_jmp_r15" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK807)")
        (eq_attr "type" "call, call_jsr"))
  "ck807_bju_ex1, (ck807_p0_wb | ck807_p1_wb)")

;; Deleting this can contribute to improve CRC8-slow's performance .
;(define_bypass 1 "ck807_alu" "ck807_*")
;(define_bypass 1 "ck807_jmp_r15" "ck807_*")

;(define_bypass 3 "ck807_load" "ck807_*")
