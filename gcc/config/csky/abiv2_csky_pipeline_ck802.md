
(define_automaton "csky_ck802")

(define_cpu_unit "csky_ck802_ex" "csky_ck802")
(define_cpu_unit "csky_ck802_wb" "csky_ck802")

(define_insn_reservation "ck802_alu" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK802)")
        (eq_attr "type" "alu"))
  "csky_ck802_ex, csky_ck802_wb")

(define_insn_reservation "ck802_branch" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK802)")
        (eq_attr "type" "branch, branch_jmp"))
  "csky_ck802_ex, csky_ck802_wb")

(define_insn_reservation "ck802_cmp" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK802)")
        (eq_attr "type" "cmp"))
  "csky_ck802_ex, csky_ck802_wb")

(define_insn_reservation "ck802_cbranch" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK802)")
        (eq_attr "type" "cbranch"))
  "csky_ck802_ex, csky_ck802_wb")

(define_insn_reservation "ck802_call" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK802)")
        (eq_attr "type" "call, call_jsr"))
  "csky_ck802_ex, csky_ck802_wb")

(define_insn_reservation "ck802_load" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK802)")
        (eq_attr "type" "load"))
  "csky_ck802_ex, csky_ck802_wb")

(define_insn_reservation "ck802_store" 2
  (and  (match_test "CSKY_TARGET_ARCH(CK802)")
        (eq_attr "type" "store"))
  "csky_ck802_ex, csky_ck802_wb")

(define_bypass 1 "*" "ck802_alu")

(define_bypass 1 "*" "ck802_branch")

(define_bypass 2 "ck802_cmp" "ck802_cbranch")
