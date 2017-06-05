;;------------------- FPU V1.0 instructions  --------------

;;----------- double operands instructions ----------

;; FIXME we can add general register constrains to optimize
;;     the code in some fp instructions
;;---
;; abs
;;---
(define_insn "abssf2"
 [(set (match_operand:SF 0 "register_operand" "=f,r")
       (abs:SF (match_operand:SF 1 "register_operand" "f,0")))
  (clobber (match_scratch:SI 2 "=a,b"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "@
  fabss\t%S0, %S1, %2
  bclri\t%0, 31")

(define_insn "absdf2"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (abs:DF (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fabsd\t%0, %1, %2")

;;---
;; neg
;;---
(define_insn "negsf2"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (neg:SF (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fnegs\t%S0, %S1, %2")

(define_insn "negdf2"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (neg:DF (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fnegd\t%0, %1, %2")

;;---
;; sqrt
;;---
(define_insn "sqrtsf2"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (sqrt:SF (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fsqrts\t%S0, %S1, %2")

(define_insn "sqrtdf2"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (sqrt:DF (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fsqrtd\t%0, %1, %2")


;;----------- fpu add/sub/mul/div instructions --------

;;---
;; add
;;---
(define_insn "addsf3"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (plus:SF (match_operand:SF 1 "register_operand" "f")
                (match_operand:SF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fadds\t%S0, %S1, %S2, %3")

(define_insn "adddf3"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (plus:DF (match_operand:DF 1 "register_operand" "f")
                (match_operand:DF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "faddd\t%0, %1, %2, %3")

;;---
;; sub
;;---
(define_insn "subsf3"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (minus:SF (match_operand:SF 1 "register_operand" "f")
                 (match_operand:SF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fsubs\t%S0, %S1, %S2, %3")

(define_insn "subdf3"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (minus:DF (match_operand:DF 1 "register_operand" "f")
                 (match_operand:DF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fsubd\t%0, %1, %2, %3")


;;---
;; multiplication
;;---
(define_insn "mulsf3"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (mult:SF (match_operand:SF 1 "register_operand" "f")
                (match_operand:SF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fmuls\t%S0, %S1, %S2, %3")

(define_insn "muldf3"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (mult:DF (match_operand:DF 1 "register_operand" "f")
                (match_operand:DF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fmuld\t%0, %1, %2, %3")


(define_insn "nmuldf3"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (neg:DF (mult:DF (match_operand:DF 1 "register_operand" "f")
                        (match_operand:DF 2 "register_operand" "f"))))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fnmuld\t%0, %1, %2, %3")

;;---
;; division
;;---
(define_expand "divsf3"
 [(parallel [
    (set (match_operand:SF 0 "register_operand" "")
       (div:SF (match_operand:SF 1 "csky_arith_float1_operand" "")
               (match_operand:SF 2 "register_operand" "")))
    (clobber (match_scratch:SI 3 ""))])]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "")

(define_insn "*fpuv1_divsf3"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (div:SF (match_operand:SF 1 "register_operand" "f")
               (match_operand:SF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fdivs\t%S0, %S1, %S2, %3")

(define_insn "*fpuv1_1_divsf3"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (div:SF (match_operand:SF 1 "csky_const_float_1" "i")
               (match_operand:SF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "frecips\t%S0, %S2, %3")


(define_expand "divdf3"
 [(parallel [(set (match_operand:DF 0 "register_operand" "")
                  (div:DF (match_operand:DF 1 "csky_arith_float1_operand" "")
                          (match_operand:DF 2 "register_operand" "")))
             (clobber (match_scratch:SI 3))])]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "")

(define_insn "*fpuv1_divdf3"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (div:DF (match_operand:DF 1 "register_operand" "f")
               (match_operand:DF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fdivd\t%0, %1, %2, %3")


(define_insn "*fpuv1_1_divdf3"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (div:DF (match_operand:DF 1 "csky_const_float_1" "i")
               (match_operand:DF 2 "register_operand" "f")))
  (clobber (match_scratch:SI 3 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "frecipd\t%0, %2, %3")



;; FIXME can we use the standard pattern name for fmacs and fnmacs ?

;;---
;; frd <= frd + frs0 * frs1
;;--
(define_insn "*csky_fpuv1_fmacs"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (plus:SF (mult:SF (match_operand:SF 1 "register_operand" "f")
                         (match_operand:SF 2 "register_operand" "f"))
                (match_operand:SF 3 "register_operand" "0")))
  (clobber (match_scratch:SI 4 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fmacs\t%S0, %S1, %S2, %4")

(define_insn "*csky_fpuv1_fmacd"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (plus:DF (mult:DF (match_operand:DF 1 "register_operand" "f")
                         (match_operand:DF 2 "register_operand" "f"))
                (match_operand:DF 3 "register_operand" "0")))
  (clobber (match_scratch:SI 4 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fmacd\t%0, %1, %2, %4")

;;---
;; frd <= frd - frs0 * frs1
;;---
(define_insn "*csky_fpuv1_fnmacs"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (minus:SF (match_operand:SF 1 "register_operand" "0")
                 (mult:SF (match_operand:SF 2 "register_operand" "f")
                          (match_operand:SF 3 "register_operand" "f"))))
  (clobber (match_scratch:SI 4 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fnmacs\t%S0, %S2, %S3, %4")

(define_insn "*csky_fpuv1_fnmacd"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (minus:DF (match_operand:DF 1 "register_operand" "0")
                 (mult:DF (match_operand:DF 2 "register_operand" "f")
                          (match_operand:DF 3 "register_operand" "f"))))
  (clobber (match_scratch:SI 4 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fnmacd\t%0, %2, %3, %4")


;;---
;; frd <= frs0 * frs1 - frd
;;---
(define_insn "*csky_fpuv1_fmscs"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (minus:SF (mult:SF (match_operand:SF 1 "register_operand" "f")
                          (match_operand:SF 2 "register_operand" "f"))
                 (match_operand:SF 3 "register_operand" "0")))
  (clobber (match_scratch:SI 4 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fmscs\t%S0, %S1, %S2, %4")

(define_insn "*csky_fpuv1_fmscd"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (minus:DF (mult:DF (match_operand:DF 1 "register_operand" "f")
                          (match_operand:DF 2 "register_operand" "f"))
                 (match_operand:DF 3 "register_operand" "0")))
  (clobber (match_scratch:SI 4 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fmscd\t%0, %1, %2, %4")


;;---
;; frd = - (frd + frs0 * frs1)
;;---
(define_insn "*csky_fpuv1_fnmscs"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (neg:SF (plus:SF (mult:SF (match_operand:SF 1 "register_operand" "f")
                                 (match_operand:SF 2 "register_operand" "f"))
                        (match_operand:SF 3 "register_operand" "0"))))
  (clobber (match_scratch:SI 4 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fnmscs\t%S0, %S1, %S2, %4")

(define_insn "*csky_fpuv1_fnmscd"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (neg:DF (plus:DF (mult:DF (match_operand:DF 1 "register_operand" "f")
                                 (match_operand:DF 2 "register_operand" "f"))
                        (match_operand:DF 3 "register_operand" "0"))))
  (clobber (match_scratch:SI 4 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fnmscd\t%0, %1, %2, %4")


;;---------- fp compare instructions ------------

;;---
;; cbranch SF mode
;;---
(define_expand "cbranchsf4"
 [(set (pc)
       (if_then_else (match_operator 0 "ordered_comparison_operator"
                       [(match_operand:SF 1 "register_operand")
                        (match_operand:SF 2 "csky_compare_operand_float")])
       (label_ref (match_operand 3 ""))
       (pc)))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "{
  enum rtx_code code = GET_CODE (operands[0]);
  bool invert;

  invert = csky_gen_compare_float (code, operands[1], operands[2]);

  if (invert)
    emit_jump_insn (gen_csky_jbf (operands[3]));
  else
    emit_jump_insn (gen_csky_jbt (operands[3]));
  DONE;

  }")

;;---
;; SF mode comparisions
;;---
(define_insn "*fpuv1_ne"
 [(set (reg:CC CC_REGNUM)
       (ne:CC (match_operand:SF 0 "register_operand" "f")
              (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmpnes\t%S0, %S1, %2")

(define_insn "*fpuv1_gt"
 [(set (reg:CC CC_REGNUM)
       (gt:CC (match_operand:SF 0 "register_operand" "f")
              (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmplts\t%S1, %S0, %2")

(define_insn "*fpuv1_ge"
 [(set (reg:CC CC_REGNUM)
       (ge:CC (match_operand:SF 0 "register_operand" "f")
              (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmphss\t%S0, %S1, %2")

(define_insn "*fpuv1_lt"
 [(set (reg:CC CC_REGNUM)
       (lt:CC (match_operand:SF 0 "register_operand" "f")
              (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmplts\t%S0, %S1, %2")

(define_insn "*fpuv1_le"
 [(set (reg:CC CC_REGNUM)
       (le:CC (match_operand:SF 0 "register_operand" "f")
              (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmphss\t%S1, %S0, %2")


(define_insn "*fpuv1_gez"
 [(set (reg:CC CC_REGNUM)
       (ge:CC (match_operand:SF 0 "register_operand" "f")
              (match_operand:SF 1 "csky_const_float_0" "i")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmpzhss\t%S0, %2")

(define_insn "*fpuv1_nez"
 [(set (reg:CC CC_REGNUM)
       (ne:CC (match_operand:SF 0 "register_operand" "f")
              (match_operand:SF 1 "csky_const_float_0" "i")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmpznes\t%S0, %2")




;;---
;; cbranch DF mode
;;---
(define_expand "cbranchdf4"
 [(set (pc)
       (if_then_else (match_operator 0 "ordered_comparison_operator"
                       [(match_operand:DF 1 "register_operand")
                        (match_operand:DF 2 "csky_compare_operand_float")])
                     (label_ref (match_operand 3 ""))
                     (pc)))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "{
  enum rtx_code code = GET_CODE (operands[0]);
  bool invert;

  invert = csky_gen_compare_float (code, operands[1], operands[2]);
  if (invert)
    emit_jump_insn (gen_csky_jbf (operands[3]));
  else
    emit_jump_insn (gen_csky_jbt (operands[3]));
  DONE;
  }")

;;---
;; DF mode comparisions
;;---
(define_insn "*fpuv1_dne"
 [(set (reg:CC CC_REGNUM)
       (ne:CC (match_operand:DF 0 "register_operand" "f")
              (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmpned\t%0, %1, %2")

(define_insn "*fpuv1_dgt"
 [(set (reg:CC CC_REGNUM)
       (gt:CC (match_operand:DF 0 "register_operand" "f")
              (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmpltd\t%1, %0, %2")

(define_insn "*fpuv1_dge"
 [(set (reg:CC CC_REGNUM)
       (ge:CC (match_operand:DF 0 "register_operand" "f")
              (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmphsd\t%0, %1, %2")

(define_insn "*fpuv1_dlt"
 [(set (reg:CC CC_REGNUM)
       (lt:CC (match_operand:DF 0 "register_operand" "f")
              (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmpltd\t%0, %1, %2")

(define_insn "*fpuv1_dle"
 [(set (reg:CC CC_REGNUM)
       (le:CC (match_operand:DF 0 "register_operand" "f")
              (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmphsd\t%1, %0, %2")


(define_insn "*fpuv1_dgez"
 [(set (reg:CC CC_REGNUM)
       (ge:CC (match_operand:DF 0 "register_operand" "f")
              (match_operand:DF 1 "csky_const_float_0" "i")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmpzhsd\t%0, %2")

(define_insn "*fpuv1_dnez"
 [(set (reg:CC CC_REGNUM)
       (ne:CC (match_operand:DF 0 "register_operand" "f")
              (match_operand:DF 1 "csky_const_float_0" "i")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fcmpzned\t%0, %2")


;;---------- fp convert instructions ------------

;;---
;; DF <- SF
;;---
(define_insn "extendsfdf2"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (float_extend:DF (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fstod\t%0, %S1, %2")

;;---
;; SF <- DF
;;---
(define_insn "truncdfsf2"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (float_truncate:SF (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fdtos\t%S0, %1, %2")

;;---
;; SF <- SI
;;---
(define_insn "floatsisf2"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (float:SF (match_operand:SI 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fsitos\t%S0, %S1, %2")

;;---
;; DF <- SI
;;---
(define_insn "floatsidf2"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (float:DF (match_operand:SI 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fsitod\t%0, %S1, %2")

;;---
;; SF <- unsigned SI
;;---
(define_insn "floatunssisf2"
 [(set (match_operand:SF 0 "register_operand" "=f")
       (unsigned_float:SF (match_operand:SI 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fuitos\t%S0, %S1, %2")

;;---
;; DF <- unsigned SI
;;---
(define_insn "floatunssidf2"
 [(set (match_operand:DF 0 "register_operand" "=f")
       (unsigned_float:DF (match_operand:SI 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fuitod\t%0, %S1, %2")

;;---
;; SI <- SF
;;---
(define_insn "fix_truncsfsi2"
 [(set (match_operand:SI 0 "register_operand" "=f")
       (fix:SI (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fstosi\t%S0, %S1, RM_ZERO, %2")

;;---
;; SI <- DF
;;---
(define_insn "fix_truncdfsi2"
 [(set (match_operand:SI 0 "register_operand" "=f")
       (fix:SI (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fdtosi\t%S0, %1, RM_ZERO, %2")

;;---
;; unsigned SI <- SF
;;---
(define_insn "fixuns_truncsfsi2"
 [(set (match_operand:SI 0 "register_operand" "=f")
       (unsigned_fix:SI (match_operand:SF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fstoui\t%S0, %S1, RM_ZERO, %2")

;;---
;; unsigned SI <- DF
;;---
(define_insn "fixuns_truncdfsi2"
 [(set (match_operand:SI 0 "register_operand" "=f")
       (unsigned_fix:SI (match_operand:DF 1 "register_operand" "f")))
  (clobber (match_scratch:SI 2 "=a"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "fdtoui\t%S0, %1, RM_ZERO, %2")


;;---------- fp move instructions ---------------

;;---
;; move
;;---
(define_expand "movsf"
 [(set (match_operand:SF 0 "general_operand" "")
       (match_operand:SF 1 "general_operand" ""))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "
{
  if (GET_CODE(operands[0]) == MEM && can_create_pseudo_p ())
  {
    operands[1] = force_reg (SFmode, operands[1]);
  }
}
")

(define_insn "*csky_fpuv1_movsf"
 [(set (match_operand:SF 0 "nonimmediate_operand" "=r,a,m,r,r,f")
       (match_operand:SF 1 "general_operand" "r,F,r,m,f,r"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "* return csky_output_move(insn, operands, SFmode);"
)

(define_expand "movdf"
 [(set (match_operand:DF 0 "general_operand" "")
       (match_operand:DF 1 "general_operand" ""))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "
{
  if (GET_CODE(operands[0]) == MEM && can_create_pseudo_p ())
  {
    operands[1] = force_reg (DFmode, operands[1]);
  }
}
")

(define_insn "*csky_fpuv1_movdf"
 [(set (match_operand:DF 0 "nonimmediate_operand" "=r,a,m,r,r,f")
       (match_operand:DF 1 "general_operand" "r,F,r,m,f,r"))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "* return csky_output_movedouble(operands, DFmode);"
)

;;---
;; cstore SF
;;---
(define_expand "cstoresf4"
 [(set (match_operand:SI 0 "register_operand" "")
       (match_operator 1 "ordered_comparison_operator"
         [(match_operand:SF 2 "register_operand" "")
          (match_operand:SF 3 "csky_compare_operand_float" "")]))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "{
    bool invert;

    invert = csky_gen_compare_float (GET_CODE (operands[1]),
                    operands[2], operands[3]);
    if(invert)
      emit_insn (gen_mvcv (operands[0]));
    else
      emit_insn (gen_mvc (operands[0]));
    DONE;
 }")

;;---
;; cstore DF
;;---
(define_expand "cstoredf4"
 [(set (match_operand:SI 0 "register_operand" "")
       (match_operator:SI 1 "ordered_comparison_operator"
         [(match_operand:DF 2 "register_operand" "")
          (match_operand:DF 3 "csky_compare_operand_float" "")]))]
 "TARGET_HARD_FLOAT && TARGET_FPUV1"
 "{
    bool invert;

    invert = csky_gen_compare_float (GET_CODE (operands[1]),
                    operands[2], operands[3]);
    if(invert)
      emit_insn (gen_mvcv (operands[0]));
    else
      emit_insn (gen_mvc (operands[0]));
    DONE;
 }")

