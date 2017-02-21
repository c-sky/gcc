
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
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
  "jbr  %l0"
)

;;FIXME the length of bsr is not really 5, it's used to distinguish
;;      from br32, use a better way here.
(define_insn "*ck801_jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
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

(define_insn "indirect_jump"
  [(set (pc) (match_operand:SI 0 "register_operand" "b,r"))]
  ""
  "@
    jmp\t%0
    jmp\t%0"
  [(set_attr "length" "2,4")]
)


;; ------------------------------------------------------------------------
;; Conditional jump insns
;; ------------------------------------------------------------------------
(define_expand "cbranchsi4"
  [(set (pc)  (if_then_else (match_operator 0 "ordered_comparison_operator"
                              [(match_operand:SI 1 "csky_compare_operand")
                               (match_operand:SI 2 "nonmemory_operand")])
                            (label_ref (match_operand 3 ""))
                            (pc)))]
  ""
  "{
    enum rtx_code code = GET_CODE (operands[0]);

     if (CSKY_ISA_FEATURE_GET2MD(ck803)
         && (code == LE || code == LT || code == GT
             || code == GE || code == EQ || code == NE)
         && operands[2] == const0_rtx )
     {
       /* To emit jbeb, jbnez, jbhz, jblsz, jblz.
          do nothing, emit the rtl tmplate.  */
     }
     else
     {
       bool invert;
       invert = gen_csky_compare (code, operands[1], operands[2]);

       if (invert)
         emit_jump_insn (gen_csky_jbf (operands[3]));
       else
         emit_jump_insn (gen_csky_jbt (operands[3]));
       DONE;
     }
  }"
)

(define_insn "csky_jbt"
  [(set (pc) (if_then_else (ne (reg:CC 33) (const_int 0))
                           (label_ref (match_operand 0 "" ""))
                           (pc)))]
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
  "jbt\t%l0"
)

(define_insn "csky_jbf"
  [(set (pc) (if_then_else (eq (reg:CC 33) (const_int 0))
                           (label_ref (match_operand 0 "" ""))
                           (pc)))]
  "!CSKY_ISA_FEATURE_GET2MD(ck801)"
  "jbf\t%l0"
)

;;FIXME the length of bsr is not really 7, it's used to distinguish
;;      from br32, use a better way here.
(define_insn "ck801_jbt"
  [(set (pc) (if_then_else (ne (reg:CC 33) (const_int 0))
                           (label_ref (match_operand 0 "" ""))
                           (pc)))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
  "*
  {
    if (get_attr_length(insn) == 6)
      return \"jbf\\t.LCB%=\;jbr\\t%l0\\t//far jump\\n.LCB%=:\";
    else if (get_attr_length(insn) == 7)
      return \"jbf\\t.LCB%=\;bsr\\t%l0\\t//too far jump\\n.LCB%=:\";
    else
      return \"jbt\\t%l0\";
   }
  "
  [(set (attr "far_jump")
        (if_then_else
        (eq_attr "length" "7")
        (const_string "yes")
        (const_string "no")))
   (set (attr "length")
        (if_then_else
        (and (ge (minus (match_dup 0) (pc)) (const_int -1024))
             (le (minus (match_dup 0) (pc)) (const_int 1022)))
        (const_int 2)
        (if_then_else
        (and (ge (minus (match_dup 0) (pc)) (const_int -65536))
             (le (minus (match_dup 0) (pc)) (const_int 65534)))
        (const_int 6)
        (const_int 7))))]
)

(define_insn "ck801_jbf"
  [(set (pc) (if_then_else (eq (reg:CC 33) (const_int 0))
                           (label_ref (match_operand 0 "" ""))
                           (pc)))]
  "CSKY_ISA_FEATURE_GET2MD(ck801)"
  "*
  {
    if (get_attr_length(insn) == 6)
      return \"jbt\\t.LCB%=\;jbr\\t%l0\\t//far jump\\n.LCB%=:\";
    else if (get_attr_length(insn) == 7)
      return \"jbt\\t.LCB%=\;bsr\\t%l0\\t//too far jump\\n.LCB%=:\";
    else
      return \"jbf\\t%l0\";
  }
  "
  [(set (attr "far_jump")
        (if_then_else
        (eq_attr "length" "7")
        (const_string "yes")
        (const_string "no")))
   (set (attr "length")
        (if_then_else
        (and (ge (minus (match_dup 0) (pc)) (const_int -1024))
             (le (minus (match_dup 0) (pc)) (const_int 1022)))
        (const_int 2)
        (if_then_else
        (and (ge (minus (match_dup 0) (pc)) (const_int -65536))
             (le (minus (match_dup 0) (pc)) (const_int 65534)))
        (const_int 6)
        (const_int 7))))]
)

(define_code_iterator zero_cond [lt le gt ge eq ne])

(define_code_attr inst [(lt "jblz") (le "jblsz") (gt "jbhz") (ge "jbhsz") (eq "jbez") (ne "jbnez")])

(define_insn "*<inst>"
  [(set (pc) (if_then_else (zero_cond (match_operand:SI 0 "register_operand" "r")
                                      (const_int 0))
             (label_ref (match_operand 1 "" ""))
             (pc)))]
  "CSKY_ISA_FEATURE_GET2MD(ck803)"
  "<inst>\t%0, %l1"
)


(define_insn "*csky_simple_return"
  [(simple_return)]
  "reload_completed"
  "*
    return output_csky_return_instruction();
  "
)
