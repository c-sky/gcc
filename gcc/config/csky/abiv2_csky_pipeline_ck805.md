(define_automaton "ck805")

(define_cpu_unit "ck805_ex1" "ck805")

;;(define_cpu_unit "ck805_ex2" "ck805")

(define_cpu_unit "ck805_exit" "ck805")

(define_insn_reservation "ck805_3cycle" 1
  (and (match_test "CSKY_TARGET_ARCH(CK805)")
       (eq_attr "type" "alu,mul,div,zext,sext,sexth,ins,lslr,cmp,branch,branch_jmp,call_jsr,call"))
  "ck805_ex1+ck805_exit")

(define_insn_reservation "ck805_alu1" 1
  (and (match_test "CSKY_TARGET_ARCH(CK805)")
       (eq_attr "type" "addsub,caddsub,alu_ix"))
  "ck805_ex1+ck805_exit")

(define_insn_reservation "ck805_cbranch" 1
  (and (match_test "CSKY_TARGET_ARCH(CK805)")
       (eq_attr "type" "cbranch"))
  "ck805_ex1+ck805_exit")

(define_insn_reservation "ck805_load" 1
  (and (match_test "CSKY_TARGET_ARCH(CK805)")
       (eq_attr "type" "load, loadr, loadi"))
  "ck805_ex1+ck805_exit")

(define_insn_reservation "ck805_store" 1
  (and (match_test "CSKY_TARGET_ARCH(CK805)")
       (eq_attr "type" "store"))
  "ck805_ex1+ck805_exit")

(define_bypass 2 "ck805_3cycle,ck805_cbranch,ck805_load,ck805_store" "ck805_cbranch")

