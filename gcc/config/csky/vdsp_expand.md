;; ------------------------------------------------------------
;; vdspv2 insns
;; ------------------------------------------------------------


;; ------------------------------------------------------------
;; vector MOV
;; -----------------------------------------------------------

(define_expand "mov<mode>"
  [(set (match_operand:V128ALL 0 "nonimmediate_operand"  "")
        (match_operand:V128ALL 1 "nonimmediate_operand"  ""))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    if (can_create_pseudo_p ())
      {
        if (!REG_P (operands[0]))
          operands[1] = force_reg (<MODE>mode, operands[1]);
      }
    else if(CONSTANT_P(operands[1])){
      operands[1] = csky_make_constant(operands[1]);
      gcc_assert(operands[1] != NULL_RTX);
    }
  }
)


;; ------------------------------------------------------------
;; vector ADD/SUB
;; -----------------------------------------------------------

(define_expand "add<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (plus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                       (match_operand:V128QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "")

(define_expand "ssadd<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (ss_plus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                          (match_operand:V128QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "")

(define_expand "usadd<mode>3"
   [(set (match_operand:V128QHSI                0 "register_operand" "=w")
      (us_plus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                        (match_operand:V128QHSI  2 "register_operand" "w")))]
 "CSKY_ISA_FEATURE(vdsp128)"
 "")

(define_expand "sub<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (minus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")
                        (match_operand:V128QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "")

(define_expand "sssub<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (ss_minus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")
                           (match_operand:V128QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "")

(define_expand "ussub<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (us_minus:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")
                           (match_operand:V128QHSI  2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  "")

;;-------------------------------
;; vector ABS
;;-------------------------------

(define_expand "abs<mode>2"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (abs:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

(define_expand "ssabs<mode>2"
  [(set (match_operand:V128QHSI                  0 "register_operand" "=w")
        (ss_abs:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

;;---------------------------
;; vector shift
;;---------------------------

(define_expand "csky_vshlu<mode>"
 [(match_operand:V128QHSI      0 "register_operand")
  (match_operand:V128QHSI      1 "register_operand")
  (match_operand:V128QHSI      2 "register_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
  emit_insn(gen_vashl<mode>3_internal(operands[0], operands[1], operands[2]));
  DONE;
 }
 )

(define_expand "csky_vshls<mode>"
 [(match_operand:V128QHSI      0 "register_operand")
  (match_operand:V128QHSI      1 "register_operand")
  (match_operand:V128QHSI      2 "register_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
  emit_insn(gen_vashl<mode>3_internal(operands[0], operands[1], operands[2]));
  DONE;
 }
 )

(define_expand "csky_vshliu<mode>"
  [(match_operand:V128QHSI                0 "register_operand")
   (match_operand:V128QHSI 1 "register_operand")
   (match_operand:SI 2 "immediate_operand" )]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vashl<mode>3_internal(operands[0], operands[1], operands[2]));
   DONE;
 }
 )
 
(define_expand "csky_vshlis<mode>"
  [(match_operand:V128QHSI  0 "register_operand" )
   (match_operand:V128QHSI 1 "register_operand" )
   (match_operand:SI 2 "immediate_operand" )]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vashl<mode>3_internal(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshlus<mode>"
  [(match_operand:V128QHSI 0 "register_operand")
   (match_operand:V128QHSI 1 "register_operand")
   (match_operand:V128QHSI 2 "register_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
   emit_insn(gen_vshlus<mode>_internal(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshlss<mode>"
  [(match_operand:V128QHSI 0 "register_operand" )
   (match_operand:V128QHSI 1 "register_operand" )
   (match_operand:V128QHSI 2 "register_operand" )]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
   emit_insn(gen_vshlss<mode>_internal(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshlius<mode>"
  [(match_operand:V128QHSI                0 "register_operand")
   (match_operand:V128QHSI 1 "register_operand")
   (match_operand:SI 2 "immediate_operand" )]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vshlus<mode>_internal(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshliss<mode>"
  [(match_operand:V128QHSI  0 "register_operand" )
   (match_operand:V128QHSI 1 "register_operand" )
   (match_operand:SI 2 "immediate_operand" )]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vshlss<mode>_internal(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

(define_expand "csky_vshru<mode>"
 [(match_operand:V128QHSI      0 "register_operand")
  (match_operand:V128QHSI      1 "register_operand")
  (match_operand:V128QHSI      2 "register_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
  emit_insn(gen_vlshr<mode>3_internal(operands[0], operands[1], operands[2]));
  DONE;
 }
 )

(define_expand "csky_vshrs<mode>"
 [(match_operand:V128QHSI      0 "register_operand")
  (match_operand:V128QHSI      1 "register_operand")
  (match_operand:V128QHSI      2 "register_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
  emit_insn(gen_vashr<mode>3_internal(operands[0], operands[1], operands[2]));
  DONE;
 }
 )

(define_expand "csky_vshriu<mode>"
  [(match_operand:V128QHSI                0 "register_operand")
   (match_operand:V128QHSI 1 "register_operand")
   (match_operand:SI 2 "immediate_operand" )]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vlshr<mode>3_internal(operands[0], operands[1], operands[2]));
   DONE;
 }
 )
 
(define_expand "csky_vshris<mode>"
  [(match_operand:V128QHSI  0 "register_operand" )
   (match_operand:V128QHSI 1 "register_operand" )
   (match_operand:SI 2 "immediate_operand" )]
  "CSKY_ISA_FEATURE(vdsp128)"
 {
   operands[2] = vdspv2_immediate_from_scalar(operands[2], <MODE>mode);
   emit_insn(gen_vashr<mode>3_internal(operands[0], operands[1], operands[2]));
   DONE;
 }
 )

;;-------------------------------
;; vector NEG
;;-------------------------------

(define_expand "neg<mode>2"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (neg:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  )

(define_expand "ssneg<mode>2"
  [(set (match_operand:V128QHSI                  0 "register_operand" "=w")
        (ss_neg:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
 )

;;---------------------------------
;; vector UMAX/UMIN/SMAX/SMIN
;;---------------------------------

(define_expand "smax<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (smax:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                       (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

(define_expand "umax<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (umax:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

(define_expand "smin<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (smin:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

(define_expand "umin<mode>3"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (umin:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

;;--------------------------------------------
;; vector VMUL/VMULA/VMULS
;;--------------------------------------------

(define_expand "fma<mode>4"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (fma:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")
                      (match_operand:V128QHSI 3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  )

(define_expand "mul<mode>3"
  [(set (match_operand:V128QHSI                0 "register_operand" "=w")
        (mult:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                       (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  )

(define_expand "fnma<mode>4"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (fma:V128QHSI (neg:V128QHSI (match_operand:V128QHSI 1 "register_operand" "w"))
                      (match_operand:V128QHSI 2 "register_operand" "w")
                      (match_operand:V128QHSI 3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(vdsp128)"
  )

;;-------------------------------------------------
;; vector DUP
;;-------------------------------------------------

(define_expand "vec_duplicate<mode>"
  [(match_operand:V128QHSI   0 "register_operand" )
   (match_operand:<vtoimode> 1 "register_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    rtx tmp = gen_rtx_VEC_DUPLICATE(<MODE>mode, operands[1]);
    emit_insn(gen_rtx_SET(operands[0], tmp));
    DONE;
  }
)

;;------------------------------------------------------
;; vector field operation EXTRACT/SET
;;------------------------------------------------------
(define_expand "vec_extract<mode>"
  [(match_operand:<vtoimode>  0 "register_operand" "=w")
   (match_operand:V128QHSI 1 "register_operand" "w")
   (match_operand:SI 2 "immediate_operand" "i")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
     machine_mode inner_mode = GET_MODE_INNER (GET_MODE (operands[1]));
     rtx target = operands[0];
     rtx tmp;
  
     tmp = gen_rtx_PARALLEL (VOIDmode, gen_rtvec (1, GEN_INT (INTVAL (operands[2]))));
     tmp = gen_rtx_VEC_SELECT (inner_mode, operands[1], tmp);
     emit_insn (gen_rtx_SET (target, tmp));
     DONE;
  }
  )

(define_expand "vec_set<mode>"
  [(match_operand:V128QHSI   0 "register_operand")
   (match_operand:<vtoimode> 1 "register_operand")
   (match_operand:SI         2 "const_int_operand")]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    HOST_WIDE_INT elem = (HOST_WIDE_INT) 1 << (INTVAL(operands[2]));
    emit_insn(gen_vec_set<mode>_internal(operands[0], operands[1], operands[0], GEN_INT(elem)));
    DONE;
  }
)

(define_expand "vdspv2_vset_lane<mode>"
  [(match_operand:V128QHSI 0 "register_operand" "=w")
   (match_operand:<vtoimode> 1 "register_operand" "r")
   (match_operand:V128QHSI 2 "register_operand" "0")
   (match_operand:SI 3 "immediate_operand" "i")]
  "CSKY_ISA_FEATURE(vdsp128)"
{
  unsigned int elt = INTVAL (operands[3]);

  if (BYTES_BIG_ENDIAN)
    {
      unsigned int reg_nelts
       = 64 / GET_MODE_UNIT_BITSIZE (<MODE>mode);
      elt ^= reg_nelts - 1;
    }

  emit_insn (gen_vec_set<mode>_internal (operands[0], operands[1],
                                         operands[2],GEN_INT (1 << elt)));
  DONE;
})

;;--------------------------------------------------
;; vector SWP
;;--------------------------------------------------

(define_expand "bswap<mode>2"
  [(set (match_operand:V128QHSDI                 0 "register_operand" "=w")
        (bswap:V128QHSDI (match_operand:V128QHSDI 1 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

;;---------------------------------------------------
;; vector BITOP
;;---------------------------------------------------
(define_expand "and<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (and:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

(define_expand "ior<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (ior:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

(define_expand "xor<mode>3"
  [(set (match_operand:V128QHSI               0 "register_operand" "=w")
        (xor:V128QHSI (match_operand:V128QHSI 1 "register_operand" "%w")
                      (match_operand:V128QHSI 2 "register_operand" "w")))]
  "CSKY_ISA_FEATURE(vdsp128)"
)

;;-----------------------------------------------
;; vector COMPARE
;;-----------------------------------------------

(define_expand "vec_cmp<mode><mode>"
  [(set (match_operand:V128QHSI 0 "register_operand")
        (match_operator:V128QHSI 1 "csky_scond_operator"
          [(match_operand:V128QHSI 2 "register_operand")
           (match_operand:V128QHSI 3 "vectcmp_operand")]))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    if (GET_CODE(operands[1]) == GT || GET_CODE(operands[1]) == LE)
      if (CSKY_ISA_FEATURE(vdsp128))
        gcc_unreachable ();
  })

(define_expand "vec_cmpu<mode><mode>"
  [(set (match_operand:V128QHSI 0 "register_operand")
        (match_operator:V128QHSI 1 "csky_ucond_operator"
          [(match_operand:V128QHSI 2 "register_operand")
           (match_operand:V128QHSI 3 "vectcmp_operand")]))]
  "CSKY_ISA_FEATURE(vdsp128)"
  {
    if (GET_CODE(operands[1]) == GTU || GET_CODE(operands[1]) == LEU)
      if (CSKY_ISA_FEATURE(vdsp128))
        gcc_unreachable ();
  })

(define_expand "csky_vcmpnezu<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
	    (match_operand:V128QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp128)"
{
  emit_insn(gen_vcmpnez<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmpnez<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
	    (match_operand:V128QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp128)"
{
  emit_insn(gen_vcmpnez<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmphsz<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
	    (match_operand:V128QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp128)"
{
  emit_insn(gen_vcmphsz<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmpltz<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
	    (match_operand:V128QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp128)"
{
  emit_insn(gen_vcmpltz<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmphszu<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (match_operand:V128QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp128)"
{
  emit_insn(gen_vcmphszu<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(define_expand "csky_vcmpltzu<mode>"
  [(set (match_operand:V128QHSI 0 "register_operand" "=w")
        (match_operand:V128QHSI 1 "register_operand" "w"))]
  "CSKY_ISA_FEATURE(vdsp128)"
{
  emit_insn(gen_vcmpltzu<mode>_internal(operands[0],
                                          operands[1],
                                          CONST0_RTX(<MODE>mode)));
  DONE;
})

(include "vdspv2_insn.md")
