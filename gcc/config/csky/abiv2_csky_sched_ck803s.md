(define_automaton "ck803s")

(define_cpu_unit "ck803s_ex1" "ck803s")

;;(define_cpu_unit "ck803s_ex2" "ck803s")

(define_cpu_unit "ck803s_exit" "ck803s")

(define_insn_reservation "ck803s_3cycle" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803S)")
       (eq_attr "type" "alu,cmp,branch"))
  "ck803s_ex1+ck803s_exit")

(define_insn_reservation "ck803s_alu1" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803S)")
       (eq_attr "type" "addsub,alu_ix"))
  "ck803s_ex1+ck803s_exit")

(define_insn_reservation "ck803s_cbranch" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803S)")
       (eq_attr "type" "cbranch"))
  "ck803s_ex1+ck803s_exit")

(define_insn_reservation "ck803s_load" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803S)")
       (eq_attr "type" "load"))
  "ck803s_ex1+ck803s_exit")

(define_insn_reservation "ck803s_store" 1
  (and (match_test "CSKY_TARGET_ARCH(CK803S)")
       (eq_attr "type" "store"))
  "ck803s_ex1+ck803s_exit")

(define_bypass 0 "ck803s_alu1" "ck803s_cbranch")

(define_bypass 0 "ck803s_store" "ck803s_store,ck803s_load,ck803s_cbranch,ck803s_alu1,ck803s_3cycle")