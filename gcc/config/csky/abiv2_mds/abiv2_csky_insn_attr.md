
; LENGTH of an instruction (in bytes)
(define_attr "length" "" (if_then_else
                         (match_test "CSKY_TARGET_ARCH(CK801)")
                         (const_int 2)
                         (const_int 4)))

; Used for ck801 to represent whether do we need to use bsr for long
; distance jump. If we do so, set the attribute to yes and the function
; will save lr at the prologue according to this.
(define_attr "far_jump" "yes,no" (const_string "no"))

; Used for insn schedule
(define_attr "type" "alu,load,store,cmp,branch"
    (const_string "alu"))
