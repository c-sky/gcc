(define_automaton "ck803")

(define_cpu_unit "ck803_ex1" "ck803")

;;(define_cpu_unit "ck803_ex2" "ck803")

(define_cpu_unit "ck803_exit" "ck803")

(define_insn_reservation "ck803_3cycle" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803)")
       (eq_attr "type" "alu,cmp,branch,branch_jmp,call_jsr,call"))
  "ck803_ex1+ck803_exit")

(define_insn_reservation "ck803_alu1" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803)")
       (eq_attr "type" "addsub,alu_ix"))
  "ck803_ex1+ck803_exit")

(define_insn_reservation "ck803_cbranch" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803)")
       (eq_attr "type" "cbranch"))
  "ck803_ex1+ck803_exit")

(define_insn_reservation "ck803_load" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803)")
       (eq_attr "type" "load"))
  "ck803_ex1+ck803_exit")

(define_insn_reservation "ck803_store" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803)")
       (eq_attr "type" "store"))
  "ck803_ex1+ck803_exit")

(define_bypass 2 "ck803_3cycle,ck803_cbranch,ck803_load,ck803_store" "ck803_cbranch")

