;;-------------------------------------------------------------
;; Pipeline descriptions for ck802
;;-------------------------------------------------------------
(define_automaton "cskyv2_ck802")

(define_cpu_unit "cskyv2_ck802_alu0" "cskyv2_ck802")

(define_insn_reservation "ck802_alu" 1
 (and (match_test "CSKY_TARGET_ARCH(CK802)")
      (eq_attr "type" "alu"))
 "cskyv2_ck802_alu0")

(define_insn_reservation "ck802_cmp" 1
 (and (match_test "CSKY_TARGET_ARCH(CK802)")
      (eq_attr "type" "cmp"))
 "cskyv2_ck802_alu0")

(define_insn_reservation "ck802_btbf" 1
 (and (match_test "CSKY_TARGET_ARCH(CK802)")
      (eq_attr "type" "branch"))
 "cskyv2_ck802_alu0")

(define_insn_reservation "ck802_load" 1
 (and (match_test "CSKY_TARGET_ARCH(CK802)")
      (eq_attr "type" "load"))
 "cskyv2_ck802_alu0")

(define_insn_reservation "ck802_store" 1
 (and (match_test "CSKY_TARGET_ARCH(CK802)")
      (eq_attr "type" "store"))
 "cskyv2_ck802_alu0")

(define_bypass 1 "ck802_cmp" "ck802_btbf")

(define_bypass 1 "ck802_load" "ck802_load,ck802_store")
