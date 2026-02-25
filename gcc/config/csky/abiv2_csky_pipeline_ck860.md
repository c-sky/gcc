(define_automaton "csky_ck860")

(define_cpu_unit "csky_ck860_ex1_p0" "csky_ck860")
(define_cpu_unit "csky_ck860_ex2_p0" "csky_ck860")
(define_cpu_unit "csky_ck860_ex3_p0" "csky_ck860")
(define_cpu_unit "csky_ck860_ex4_p0" "csky_ck860")
(define_cpu_unit "csky_ck860_wb_p0" "csky_ck860")
(define_cpu_unit "csky_ck860_ex1_p1" "csky_ck860")
(define_cpu_unit "csky_ck860_ex2_p1" "csky_ck860")
(define_cpu_unit "csky_ck860_ex3_p1" "csky_ck860")
(define_cpu_unit "csky_ck860_ex4_p1" "csky_ck860")
(define_cpu_unit "csky_ck860_wb_p1" "csky_ck860")
(define_cpu_unit "csky_ck860_ex1_p2" "csky_ck860")
(define_cpu_unit "csky_ck860_wb_p2" "csky_ck860")
(define_cpu_unit "csky_ck860_ex1_p3" "csky_ck860")
(define_cpu_unit "csky_ck860_ex2_p3" "csky_ck860")
(define_cpu_unit "csky_ck860_ex3_p3" "csky_ck860")
(define_cpu_unit "csky_ck860_wb_p3" "csky_ck860")
(define_cpu_unit "csky_ck860_ex1_p4" "csky_ck860")
(define_cpu_unit "csky_ck860_ex2_p4" "csky_ck860")
(define_cpu_unit "csky_ck860_ex3_p4" "csky_ck860")
(define_cpu_unit "csky_ck860_wb_p4" "csky_ck860")

(define_reservation "div" "csky_ck860_ex1_p0+csky_ck860_ex2_p0+csky_ck860_ex3_p0+csky_ck860_ex4_p0")

(define_reservation "ext_default_0" "csky_ck860_ex1_p0*2, csky_ck860_wb_p0")
(define_reservation "ext_default_1" "csky_ck860_ex1_p1*2, csky_ck860_wb_p1")
(define_reservation "ins_default_0" "csky_ck860_ex1_p0*3, csky_ck860_wb_p0")
(define_reservation "ins_default_1" "csky_ck860_ex1_p1*3, csky_ck860_wb_p1")
(define_reservation "alu_default_0" "csky_ck860_ex1_p0, csky_ck860_wb_p0")
(define_reservation "alu_default_1" "csky_ck860_ex1_p1, csky_ck860_wb_p1")

(define_insn_reservation "ck860_ext" 3
  (and  (match_test "CSKY_TARGET_ARCH(CK860)")
        (eq_attr "type" "sext,zext"))
  "ext_default_0|ext_default_1")

(define_insn_reservation "ck860_ins" 4
  (and  (match_test "CSKY_TARGET_ARCH(CK860)")
        (eq_attr "type" "ins"))
  "ins_default_0|ins_default_1")

(define_insn_reservation "ck860_alu" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK860)")
        (eq_attr "type" "alu,addsub,cmp,sexth,lslr"))
  "alu_default_0|alu_default_1")

(define_insn_reservation "ck860_branch" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK860)")
        (eq_attr "type" "branch,cbranch,branch_jmp,call,call_jsr"))
  "csky_ck860_ex1_p2, csky_ck860_wb_p2")

(define_insn_reservation "ck860_mul" 5
  (and  (match_test "CSKY_TARGET_ARCH(CK860)")
        (eq_attr "type" "mul"))
  "csky_ck860_ex1_p1, csky_ck860_ex2_p1, csky_ck860_ex3_p1,
   csky_ck860_ex4_p1, csky_ck860_wb_p1")

; div 6~35
(define_insn_reservation "ck860_div"21
  (and  (match_test "CSKY_TARGET_ARCH(CK860)")
        (eq_attr "type" "div"))
  "div*20, csky_ck860_wb_p0")

(define_insn_reservation "ck860_ld" 4
  (and  (match_test "CSKY_TARGET_ARCH(CK860)")
        (eq_attr "type" "load"))
  "csky_ck860_ex1_p3, csky_ck860_ex2_p3, csky_ck860_ex3_p3,
   csky_ck860_wb_p3")

(define_insn_reservation "ck860_st" 4
  (and  (match_test "CSKY_TARGET_ARCH(CK860)")
        (eq_attr "type" "store"))
  "csky_ck860_ex1_p4, csky_ck860_ex2_p4, csky_ck860_ex3_p4,
   csky_ck860_wb_p4")

(define_bypass 5 "ck860_ext" "ck860_div")
(define_bypass 6 "ck860_ins" "ck860_div")
(define_bypass 4 "ck860_alu" "ck860_div")
(define_bypass 22 "ck860_div" "ck860_div")

(define_bypass 5 "ck860_ext" "ck860_mul")
(define_bypass 6 "ck860_ins" "ck860_mul")
(define_bypass 4 "ck860_alu" "ck860_mul")
(define_bypass 7 "ck860_mul" "ck860_mul")
