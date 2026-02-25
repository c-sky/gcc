;;-------------------------------------------------------------------
;; insn for VDSPV2
;;--------------------------------------------------------------------

(define_expand "vec_set<mode>_internal"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (vec_merge:V128QHSI
          (vec_duplicate:V128QHSI (match_operand:<vtoimode> 1 "register_operand" "r"))
          (match_operand:V128QHSI 2 "register_operand" "0")
          (match_operand:SI 3 "const_int_operand" "i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

;;---------------------------
;; vector shift
;;---------------------------

(define_insn "vashl<mode>3_internal"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w,w")
        (ashift:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w,w")
                         (match_operand:V128QHSI 2 "imm_lshift_or_reg_vdspv2" "w,i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    switch(which_alternative)
    {
      case 0: return "vshl.u<sup3>\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshli",'u',"",&operands[2],
                                                 <MODE>mode, 1, 0);
      default:gcc_unreachable();
    }
  }
)

(define_insn "vashr<mode>3_internal"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w, w")
        (ashiftrt:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w, w")
                            (match_operand:V128QHSI 2 "imm_rshift_or_reg_vdspv2" "w, i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    switch(which_alternative)
    {
      case 0: return "vshr.s<sup3>\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshri",'s',"",&operands[2],
                                                   <MODE>mode, 0, 0);
      default:gcc_unreachable();
    }
  }
)

(define_insn "vshlus<mode>_internal"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w, w")
        (us_ashift:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w, w")
                             (match_operand:V128QHSI 2 "imm_lshift_or_reg_vdspv2" "w, i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    switch(which_alternative)
    {
      case 0: return "vshl.u<sup3>.s\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshli",'u',".s",&operands[2],
                                                   <MODE>mode, 1, 0);
      default:gcc_unreachable();
    }
  }
)

(define_insn "vlshr<mode>3_internal"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w, w")
        (lshiftrt:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w, w")
                           (match_operand:V128QHSI 2 "imm_rshift_or_reg_vdspv2" "w, i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    switch(which_alternative)
    {
      case 0: return "vshr.u<sup3>\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshri",'u',"",&operands[2],
                                                   <MODE>mode, 0, 0);
      default:gcc_unreachable();
    }
  }
)

(define_insn "vshlss<mode>_internal"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w, w")
        (ss_ashift:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w,w")
                             (match_operand:V128QHSI 2 "imm_lshift_or_reg_vdspv2" "w, i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    switch(which_alternative)
    {
      case 0: return "vshl.s<sup3>.s\t%0, %1, %2";
      case 1: return vdspv2_output_shift_immediate("vshli",'s',".s",&operands[2],
                                                   <MODE>mode, 1, 0);
      default:gcc_unreachable();
    }
  }
)

;;-----------------------------------------
;; vector COMPARE
;;-----------------------------------------

(define_insn "csky_vcmps<vcmps1_attr><mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
	(VCMPS1:V128QHSI
	  (match_operand:V128QHSI 1 "register_operand" "w")
	  (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "*
  switch(<CODE>){
    case LT:
    case GE:
      return \"vcmp<vcmps1_attr>.s<sup3>\\t%0, %1, %2\";
    case NE:
      return \"vcmp<vcmps1_attr>.u<sup3>\\t%0, %1, %2\";
    default:
      gcc_unreachable();
  }
  ")

(define_insn "csky_vcmpu<vcmpu1_attr><mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
	(VCMPU1:V128QHSI
	  (match_operand:V128QHSI 1 "register_operand" "w")
	  (match_operand:V128QHSI 2 "register_operand"  "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
 "*
 switch(<CODE>){
  case LTU:
  case GEU:
  case NE:
    return \"vcmp<vcmpu1_attr>.u<sup3>\\t%0, %1, %2\";
  default:
    gcc_unreachable();
    }
 ")

(define_insn "vcmp<vcmps1_attr>z<mode>_internal"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
	(VCMPS1:V128QHSI
	  (match_operand:V128QHSI 1 "register_operand" "w")
	  (match_operand:V128QHSI 2 "zero_operand" "i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "* switch(<CODE>){
  case GE:
  case LT:
    return \"vcmp<vcmps1_attr>z.s<sup3>\\t%0, %1\";
  case NE:
    return \"vcmp<vcmps1_attr>z.u<sup3>\\t%0, %1\";
  default:
    gcc_unreachable();
  }")

(define_insn "vcmp<vcmpu3_attr>zu<mode>_internal"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (VCMPU3:V128QHSI
          (match_operand:V128QHSI 1 "register_operand" "w")
          (match_operand:V128QHSI 2 "zero_operand" "i")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "* switch(<CODE>){
  case GEU:
  case LTU:
    return \"vcmp<vcmpu3_attr>z.u<sup3>\\t%0, %1\";
  default:
    gcc_unreachable();
  }")
