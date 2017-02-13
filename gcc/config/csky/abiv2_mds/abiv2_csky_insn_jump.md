
;; ------------------------------------------------------------------------
;; Jump and linkage insns
;; ------------------------------------------------------------------------
(define_expand "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  ""
)

(define_insn "*csky_jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  "!TARGET_CK801"
  "jbr  %l0"
)

;;FIXME the length of bsr is not really 5, it's used to distinguish
;;      from br32, use a better way here.
(define_insn "*ck801_jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  "TARGET_CK801"
  "*{
    if (get_attr_length(insn) != 5)
      return \"jbr\\t%l0\";
    else
      return \"bsr\\t%l0\\t//too far jump\";
  }"
  [(set (attr "far_jump")
        (if_then_else (eq_attr "length" "5")
                      (const_string "yes")
                      (const_string "no")))
   (set (attr "length")
        (if_then_else (and (ge (minus (match_dup 0) (pc)) (const_int -1024))
                           (le (minus (match_dup 0) (pc)) (const_int 1022)))
                      (const_int 2)
                      (if_then_else (and (ge (minus (match_dup 0) (pc)) (const_int -65536))
                                    (le (minus (match_dup 0) (pc)) (const_int 65534)))
                                    (const_int 4)
                                    (const_int 5))))]
)
