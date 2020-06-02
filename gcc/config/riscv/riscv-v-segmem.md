
(define_int_iterator UNSPEC_VLSEG_NFOP [
  UNSPEC_VLSEGB UNSPEC_VLSEGBU
  UNSPEC_VLSEGH UNSPEC_VLSEGHU
  UNSPEC_VLSEGW UNSPEC_VLSEGWU
  UNSPEC_VLSEGE
])

(define_int_iterator UNSPEC_VLSSEG_NFOP [
  UNSPEC_VLSSEGB UNSPEC_VLSSEGBU
  UNSPEC_VLSSEGH UNSPEC_VLSSEGHU
  UNSPEC_VLSSEGW UNSPEC_VLSSEGWU
  UNSPEC_VLSSEGE
])

(define_int_iterator UNSPEC_VLXSEG_NFOP [
  UNSPEC_VLXSEGB UNSPEC_VLXSEGBU
  UNSPEC_VLXSEGH UNSPEC_VLXSEGHU
  UNSPEC_VLXSEGW UNSPEC_VLXSEGWU
  UNSPEC_VLXSEGE
])

(define_int_attr vlseg_nfop_attr [
  (UNSPEC_VLSEGB "b") (UNSPEC_VLSEGBU "bu")
  (UNSPEC_VLSEGH "h") (UNSPEC_VLSEGHU "hu")
  (UNSPEC_VLSEGW "w") (UNSPEC_VLSEGWU "wu")
  (UNSPEC_VLSEGE "e")

  (UNSPEC_VLSSEGB "b") (UNSPEC_VLSSEGBU "bu")
  (UNSPEC_VLSSEGH "h") (UNSPEC_VLSSEGHU "hu")
  (UNSPEC_VLSSEGW "w") (UNSPEC_VLSSEGWU "wu")
  (UNSPEC_VLSSEGE "e")

  (UNSPEC_VLXSEGB "b") (UNSPEC_VLXSEGBU "bu")
  (UNSPEC_VLXSEGH "h") (UNSPEC_VLXSEGHU "hu")
  (UNSPEC_VLXSEGW "w") (UNSPEC_VLXSEGWU "wu")
  (UNSPEC_VLXSEGE "e")
])

(define_mode_iterator VANYSEG [
  V16QI V32QI V64QI V128QI
  V8HI V16HI V32HI V64HI
  V4SI V8SI V16SI V32SI
  V2DI V4DI  V8DI V16DI

  V8HF V16HF V32HF V64HF
  V4SF V8SF V16SF V32SF
  V2DF V4DF  V8DF V16DF

  V24QI V40QI V48QI V56QI V80QI V96QI V112QI
  V12HI V20HI V24HI V28HI V40HI V48HI V56HI
  V6SI V10SI V12SI V14SI V20SI V24SI V28SI
  V3DI V5DI V6DI V7DI V10DI V12DI V14DI

  V12HF V20HF V24HF V28HF V40HF V48HF V56HF
  V6SF V10SF V12SF V14SF V20SF V24SF V28SF
  V3DF V5DF V6DF V7DF V10DF V12DF V14DF
])


(define_int_iterator UNSPEC_VSSEG_NFOP [
  UNSPEC_VLSEGB
  UNSPEC_VLSEGH
  UNSPEC_VLSEGW
  UNSPEC_VLSEGE
])

(define_int_iterator UNSPEC_VSSSEG_NFOP [
  UNSPEC_VLSSEGB
  UNSPEC_VLSSEGH
  UNSPEC_VLSSEGW
  UNSPEC_VLSSEGE
])

(define_int_iterator UNSPEC_VSXSEG_NFOP [
  UNSPEC_VLXSEGB
  UNSPEC_VLXSEGH
  UNSPEC_VLXSEGW
  UNSPEC_VLXSEGE
])

;; Vector Unit-Stride Segment Loads and Stores
;; ===========================================

; vlseg<nf>{b,h,w}.v vd, (rs1)
; vlseg<nf>e.v vd, (rs1)
; vlseg<nf>{b,h,w}u.v vd, (rs1)

(define_expand "riscv_vlseg<vlseg_nfop_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand:SI 2 "register_operand" "r")
                         (match_operand:SI 3 "const_int_operand" "")]
                        UNSPEC_VLSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[1] = gen_rtx_MEM(<MODE>mode, operands[1]);
    emit_insn(gen_riscv_vlseg<vlseg_nfop_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_vlseg<vlseg_nfop_attr>v_<mode>_split"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand:VANYSEG 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand:SI 2 "register_operand" "r")
                         (match_operand:SI 3 "const_int_operand" "")]
                        UNSPEC_VLSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[2], operands[2], operands[3]);
    emit_insn(gen_riscv_vlseg<vlseg_nfop_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn "riscv_vlseg<vlseg_nfop_attr>v_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand:VANYSEG 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand:SI 2 "register_operand" "r")
                         (match_operand:SI 3 "const_int_operand" "")]
                        UNSPEC_VLSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vlseg%3<vlseg_nfop_attr>.v\t%0,%1");
  }
)

; vlseg<nf>{b,h,w}.v vd, (rs1), vm
; vlseg<nf>e.v vd, (rs1), vm
; vlseg<nf>{b,h,w}u.v vd, (rs1), vm

(define_expand "riscv_vlseg<vlseg_nfop_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand 2 "register_operand" "r")
                                (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VLSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[2] = gen_rtx_MEM(<MODE>mode, operands[2]);
    emit_insn(gen_riscv_vlseg<vlseg_nfop_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_vlseg<vlseg_nfop_attr>v_mask_<mode>_split"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand:VANYSEG 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VLSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[4], operands[4], operands[5]);
    emit_insn(gen_riscv_vlseg<vlseg_nfop_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn "riscv_vlseg<vlseg_nfop_attr>v_mask_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand:VANYSEG 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VLSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vlseg%5<vlseg_nfop_attr>.v\t%0,%2,%3.t");
  }
)

; vsseg<nf>{b,h,w,e}.v vs3, (rs1)

(define_expand "riscv_vsseg<vlseg_nfop_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand:SI 2 "register_operand" "r")
                         (match_operand:SI 3 "const_int_operand" "")]
                        UNSPEC_VSSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vsseg<vlseg_nfop_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_vsseg<vlseg_nfop_attr>v_<mode>_split"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand:SI 2 "register_operand" "r")
                         (match_operand:SI 3 "const_int_operand" "")]
                        UNSPEC_VSSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[2], operands[2], operands[3]);
    emit_insn(gen_riscv_vsseg<vlseg_nfop_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn "riscv_vsseg<vlseg_nfop_attr>v_<mode>_internal"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand:SI 2 "register_operand" "r")
                         (match_operand:SI 3 "const_int_operand" "")]
                        UNSPEC_VSSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vsseg%3<vlseg_nfop_attr>.v\t%1,%0");
  }
)

; vsseg<nf>{b,h,w,e}.v vs3, (rs1), vm

(define_expand "riscv_vsseg<vlseg_nfop_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "vmask_mode_register_operand" "w")
                         (match_operand:SI 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vsseg<vlseg_nfop_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vsseg<vlseg_nfop_attr>v_mask_<mode>_split"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "vmask_mode_register_operand" "w")
                         (match_operand:SI 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[3], operands[3], operands[4]);
    emit_insn(gen_riscv_vsseg<vlseg_nfop_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vsseg<vlseg_nfop_attr>v_mask_<mode>_internal"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "vmask_mode_register_operand" "w")
                         (match_operand:SI 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vsseg%4<vlseg_nfop_attr>.v\t%1,%0,%2.t");
  }
)

;; Vector Strided Segment Loads and Stores
;; =======================================

; vlsseg<nf>{b,h,w}.v vd, (rs1), rs2
; vlsseg<nf>e.v vd, (rs1), rs2
; vlsseg<nf>{b,h,w}u.v vd, (rs1), rs2

(define_expand "riscv_vlsseg<vlseg_nfop_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "r")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VLSSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[1] = gen_rtx_MEM(<MODE>mode, operands[1]);
    emit_insn(gen_riscv_vlsseg<vlseg_nfop_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vlsseg<vlseg_nfop_attr>v_<mode>_split"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand:VANYSEG 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand 2 "register_operand" "r")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VLSSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[3], operands[3], operands[4]);
    emit_insn(gen_riscv_vlsseg<vlseg_nfop_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vlsseg<vlseg_nfop_attr>v_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand:VANYSEG 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand 2 "register_operand" "r")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VLSSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vlsseg%4<vlseg_nfop_attr>.v\t%0,%1,%2");
  }
)

; vlsseg<nf>{b,h,w}.v vd, (rs1), rs2, vm
; vlsseg<nf>e.v vd, (rs1), rs2, vm
; vlsseg<nf>{b,h,w}u.v vd, (rs1), rs2, vm

(define_expand "riscv_vlsseg<vlseg_nfop_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand 2 "register_operand" "r")
                                (match_operand 3 "register_operand" "r")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")
                         (match_operand:SI 6 "const_int_operand" "")]
                        UNSPEC_VLSSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[2] = gen_rtx_MEM(<MODE>mode, operands[2]);
    emit_insn(gen_riscv_vlsseg<vlseg_nfop_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6]));
    DONE;
  }
)

(define_insn_and_split "riscv_vlsseg<vlseg_nfop_attr>v_mask_<mode>_split"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand:VANYSEG 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "register_operand" "r")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")
                         (match_operand:SI 6 "const_int_operand" "")]
                        UNSPEC_VLSSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[5], operands[5], operands[6]);
    emit_insn(gen_riscv_vlsseg<vlseg_nfop_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6]));
    DONE;
  }
)

(define_insn "riscv_vlsseg<vlseg_nfop_attr>v_mask_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand:VANYSEG 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "register_operand" "r")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")
                         (match_operand:SI 6 "const_int_operand" "")]
                        UNSPEC_VLSSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vlsseg%6<vlseg_nfop_attr>.v\t%0,%2,%3,%4.t");
  }
)

; vssseg<nf>{b,h,w,e}.v vs3, (rs1), rs2

(define_expand "riscv_vssseg<vlseg_nfop_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSSSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vssseg<vlseg_nfop_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vssseg<vlseg_nfop_attr>v_<mode>_split"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSSSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[3], operands[3], operands[4]);
    emit_insn(gen_riscv_vssseg<vlseg_nfop_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vssseg<vlseg_nfop_attr>v_<mode>_internal"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSSSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vssseg%4<vlseg_nfop_attr>.v\t%2,%0,%1");
  }
)

; vssseg<nf>{b,h,w,e}.v vs3, (rs1), rs2, vm

(define_expand "riscv_vssseg<vlseg_nfop_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VSSSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vssseg<vlseg_nfop_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_vssseg<vlseg_nfop_attr>v_mask_<mode>_split"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VSSSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[4], operands[4], operands[5]);
    emit_insn(gen_riscv_vssseg<vlseg_nfop_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn "riscv_vssseg<vlseg_nfop_attr>v_mask_<mode>_internal"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VSSSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vssseg%5<vlseg_nfop_attr>.v\t%2,%0,%1,%3.t");
  }
)

;; Vector Indexed Segment Loads and Stores
;; =======================================

; vlxseg<nf>{b,h,w}.v vd, (rs1), vs2
; vlxseg<nf>e.v vd, (rs1), vs2
; vlxseg<nf>{b,h,w}u.v vd, (rs1), vs2

(define_expand "riscv_vlxseg<vlseg_nfop_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VLXSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[1] = gen_rtx_MEM(<MODE>mode, operands[1]);
    emit_insn(gen_riscv_vlxseg<vlseg_nfop_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vlxseg<vlseg_nfop_attr>v_<mode>_split"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand:VANYSEG 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VLXSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[3], operands[3], operands[4]);
    emit_insn(gen_riscv_vlxseg<vlseg_nfop_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vlxseg<vlseg_nfop_attr>v_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VANYSEG [(match_operand:VANYSEG 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VLXSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vlxseg%4<vlseg_nfop_attr>.v\t%0,%1,%2");
  }
)

; vlxseg<nf>{b,h,w}.v vd, (rs1), vs2, vm
; vlxseg<nf>e.v vd, (rs1), vs2, vm
; vlxseg<nf>{b,h,w}u.v vd, (rs1), vs2, vm

(define_expand "riscv_vlxseg<vlseg_nfop_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand 2 "register_operand" "r")
                                (match_operand 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")
                         (match_operand:SI 6 "const_int_operand" "")]
                        UNSPEC_VLXSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[2] = gen_rtx_MEM(<MODE>mode, operands[2]);
    emit_insn(gen_riscv_vlxseg<vlseg_nfop_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6]));
    DONE;
  }
)

(define_insn_and_split "riscv_vlxseg<vlseg_nfop_attr>v_mask_<mode>_split"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand:VANYSEG 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")
                         (match_operand:SI 6 "const_int_operand" "")]
                        UNSPEC_VLXSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[5], operands[5], operands[6]);
    emit_insn(gen_riscv_vlxseg<vlseg_nfop_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6]));
    DONE;
  }
)

(define_insn "riscv_vlxseg<vlseg_nfop_attr>v_mask_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "0")
                 (match_operand:VANYSEG 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")
                         (match_operand:SI 6 "const_int_operand" "")]
                        UNSPEC_VLXSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vlxseg%6<vlseg_nfop_attr>.v\t%0,%2,%3,%4.t");
  }
)

; vsxseg<nf>{b,h,w,e}.v vs3, (rs1), vs2

(define_expand "riscv_vsxseg<vlseg_nfop_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSXSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vsxseg<vlseg_nfop_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vsxseg<vlseg_nfop_attr>v_<mode>_split"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSXSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[3], operands[3], operands[4]);
    emit_insn(gen_riscv_vsxseg<vlseg_nfop_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vsxseg<vlseg_nfop_attr>v_<mode>_internal"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")
                         (match_operand:SI 4 "const_int_operand" "")]
                        UNSPEC_VSXSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vsxseg%4<vlseg_nfop_attr>.v\t%2,%0,%1");
  }
)

; vsxseg<nf>{b,h,w,e}.v vs3, (rs1), vs2, vm

(define_expand "riscv_vsxseg<vlseg_nfop_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VSXSEG_NFOP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vsxseg<vlseg_nfop_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_vsxseg<vlseg_nfop_attr>v_mask_<mode>_split"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VSXSEG_NFOP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli_base(<MODE>mode, operands[4], operands[4], operands[5]);
    emit_insn(gen_riscv_vsxseg<vlseg_nfop_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn "riscv_vsxseg<vlseg_nfop_attr>v_mask_<mode>_internal"
  [(set (match_operand:VANYSEG 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VANYSEG [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")
                         (match_operand:SI 5 "const_int_operand" "")]
                        UNSPEC_VSXSEG_NFOP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vsxseg%5<vlseg_nfop_attr>.v\t%2,%0,%1,%3.t");
  }
)
