
(define_int_iterator UNSPEC_VLMEM_OP [
  UNSPEC_VLB UNSPEC_VLBU
  UNSPEC_VLH UNSPEC_VLHU
  UNSPEC_VLW UNSPEC_VLWU
  UNSPEC_VLE
])

(define_int_iterator UNSPEC_VLSMEM_OP [
  UNSPEC_VLSB UNSPEC_VLSBU
  UNSPEC_VLSH UNSPEC_VLSHU
  UNSPEC_VLSW UNSPEC_VLSWU
  UNSPEC_VLSE
])

(define_int_iterator UNSPEC_VLXMEM_OP [
  UNSPEC_VLXB UNSPEC_VLXBU
  UNSPEC_VLXH UNSPEC_VLXHU
  UNSPEC_VLXW UNSPEC_VLXWU
  UNSPEC_VLXE
])

(define_int_attr vlmem_op_attr [
  (UNSPEC_VLB "b") (UNSPEC_VLBU "bu")
  (UNSPEC_VLH "h") (UNSPEC_VLHU "hu")
  (UNSPEC_VLW "w") (UNSPEC_VLWU "wu")
  (UNSPEC_VLE "e")

  (UNSPEC_VLSB "b") (UNSPEC_VLSBU "bu")
  (UNSPEC_VLSH "h") (UNSPEC_VLSHU "hu")
  (UNSPEC_VLSW "w") (UNSPEC_VLSWU "wu")
  (UNSPEC_VLSE "e")

  (UNSPEC_VLXB "b") (UNSPEC_VLXBU "bu")
  (UNSPEC_VLXH "h") (UNSPEC_VLXHU "hu")
  (UNSPEC_VLXW "w") (UNSPEC_VLXWU "wu")
  (UNSPEC_VLXE "e")

  (UNSPEC_VSUXB "b")
  (UNSPEC_VSUXH "h")
  (UNSPEC_VSUXW "w")
  (UNSPEC_VSUXE "e")
])

(define_int_iterator UNSPEC_VSMEM_OP [
  UNSPEC_VLB
  UNSPEC_VLH
  UNSPEC_VLW
  UNSPEC_VLE
])

(define_int_iterator UNSPEC_VSSMEM_OP [
  UNSPEC_VLSB
  UNSPEC_VLSH
  UNSPEC_VLSW
  UNSPEC_VLSE
])

(define_int_iterator UNSPEC_VSXMEM_OP [
  UNSPEC_VLXB
  UNSPEC_VLXH
  UNSPEC_VLXW
  UNSPEC_VLXE
])

(define_int_iterator UNSPEC_VSUXMEM_OP [
  UNSPEC_VSUXB
  UNSPEC_VSUXH
  UNSPEC_VSUXW
  UNSPEC_VSUXE
])

;; Vector Unit-Stride Loads and Stores
;; ===================================

; load

(define_expand "riscv_vl<vlmem_op_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand:SI 2 "register_operand" "r")]
                        UNSPEC_VLMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[1] = gen_rtx_MEM(<MODE>mode, operands[1]);
    emit_insn(gen_riscv_vl<vlmem_op_attr>v_<mode>_split(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vl<vlmem_op_attr>v_<mode>_split"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand:VALL 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand:SI 2 "register_operand" "r")]
                        UNSPEC_VLMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vl<vlmem_op_attr>v_<mode>_internal(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn "riscv_vl<vlmem_op_attr>v_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand:VALL 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand:SI 2 "register_operand" "r")]
                        UNSPEC_VLMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vl<vlmem_op_attr>.v\t%0,%1");
  }
)

; load mask

(define_expand "riscv_vl<vlmem_op_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand 2 "register_operand" "r")
                                (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")]
                        UNSPEC_VLMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[2] = gen_rtx_MEM(<MODE>mode, operands[2]);
    emit_insn(gen_riscv_vl<vlmem_op_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vl<vlmem_op_attr>v_mask_<mode>_split"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand:VALL 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")]
                        UNSPEC_VLMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vl<vlmem_op_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vl<vlmem_op_attr>v_mask_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand:VALL 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")]
                        UNSPEC_VLMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vl<vlmem_op_attr>.v\t%0,%2,%3.t");
  }
)

; store

(define_expand "riscv_vs<vlmem_op_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand:SI 2 "register_operand" "r")]
                        UNSPEC_VSMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vs<vlmem_op_attr>v_<mode>_split(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vs<vlmem_op_attr>v_<mode>_split"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand:SI 2 "register_operand" "r")]
                        UNSPEC_VSMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vs<vlmem_op_attr>v_<mode>_internal(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn "riscv_vs<vlmem_op_attr>v_<mode>_internal"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand:SI 2 "register_operand" "r")]
                        UNSPEC_VSMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vs<vlmem_op_attr>.v\t%1,%0");
  }
)

; store mask

(define_expand "riscv_vs<vlmem_op_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "vmask_mode_register_operand" "w")
                         (match_operand:SI 3 "register_operand" "r")]
                        UNSPEC_VSMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vs<vlmem_op_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_vs<vlmem_op_attr>v_mask_<mode>_split"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "vmask_mode_register_operand" "w")
                         (match_operand:SI 3 "register_operand" "r")]
                        UNSPEC_VSMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_vs<vlmem_op_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn "riscv_vs<vlmem_op_attr>v_mask_<mode>_internal"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "vmask_mode_register_operand" "w")
                         (match_operand:SI 3 "register_operand" "r")]
                        UNSPEC_VSMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vs<vlmem_op_attr>.v\t%1,%0,%2.t");
  }
)

;; Vector Strided Loads and Stores
;; ===============================

; load

(define_expand "riscv_vls<vlmem_op_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "r")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VLSMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[1] = gen_rtx_MEM(<MODE>mode, operands[1]);
    emit_insn(gen_riscv_vls<vlmem_op_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_vls<vlmem_op_attr>v_<mode>_split"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand:VALL 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand 2 "register_operand" "r")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VLSMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_vls<vlmem_op_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn "riscv_vls<vlmem_op_attr>v_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand:VALL 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand 2 "register_operand" "r")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VLSMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vls<vlmem_op_attr>.v\t%0,%1,%2");
  }
)

; load mask

(define_expand "riscv_vls<vlmem_op_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand 2 "register_operand" "r")
                                (match_operand 3 "register_operand" "r")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")]
                        UNSPEC_VLSMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[2] = gen_rtx_MEM(<MODE>mode, operands[2]);
    emit_insn(gen_riscv_vls<vlmem_op_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_vls<vlmem_op_attr>v_mask_<mode>_split"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand:VALL 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "register_operand" "r")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")]
                        UNSPEC_VLSMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_vls<vlmem_op_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn "riscv_vls<vlmem_op_attr>v_mask_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand:VALL 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "register_operand" "r")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")]
                        UNSPEC_VLSMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vls<vlmem_op_attr>.v\t%0,%2,%3,%4.t");
  }
)

; store

(define_expand "riscv_vss<vlmem_op_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSSMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vss<vlmem_op_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_vss<vlmem_op_attr>v_<mode>_split"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSSMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_vss<vlmem_op_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn "riscv_vss<vlmem_op_attr>v_<mode>_internal"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSSMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vss<vlmem_op_attr>.v\t%2,%0,%1");
  }
)

; store mask

(define_expand "riscv_vss<vlmem_op_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSSMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vss<vlmem_op_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vss<vlmem_op_attr>v_mask_<mode>_split"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSSMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vss<vlmem_op_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vss<vlmem_op_attr>v_mask_<mode>_internal"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSSMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vss<vlmem_op_attr>.v\t%2,%0,%1,%3.t");
  }
)

;; Vector Indexed Loads and Stores
;; ===============================

; load

(define_expand "riscv_vlx<vlmem_op_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand 1 "register_operand" "r")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VLXMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[1] = gen_rtx_MEM(<MODE>mode, operands[1]);
    emit_insn(gen_riscv_vlx<vlmem_op_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_vlx<vlmem_op_attr>v_<mode>_split"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand:VALL 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VLXMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_vlx<vlmem_op_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn "riscv_vlx<vlmem_op_attr>v_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=v")
        (unspec:VALL [(match_operand:VALL 1 "riscv_vector_mem_operand" "Qmv")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VLXMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vlx<vlmem_op_attr>.v\t%0,%1,%2");
  }
)

; load mask

(define_expand "riscv_vlx<vlmem_op_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand 2 "register_operand" "r")
                                (match_operand 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")]
                        UNSPEC_VLXMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[2] = gen_rtx_MEM(<MODE>mode, operands[2]);
    emit_insn(gen_riscv_vlx<vlmem_op_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_vlx<vlmem_op_attr>v_mask_<mode>_split"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand:VALL 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")]
                        UNSPEC_VLXMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_vlx<vlmem_op_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn "riscv_vlx<vlmem_op_attr>v_mask_<mode>_internal"
  [(set (match_operand 0 "register_operand" "=u")
        (unspec:VALL [(match_operand 1 "register_operand" "0")
                 (match_operand:VALL 2 "riscv_vector_mem_operand" "Qmv")
                                (match_operand 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand 5 "register_operand" "r")]
                        UNSPEC_VLXMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vlx<vlmem_op_attr>.v\t%0,%2,%3,%4.t");
  }
)

; store

(define_expand "riscv_vsx<vlmem_op_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSXMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vsx<vlmem_op_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_vsx<vlmem_op_attr>v_<mode>_split"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSXMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_vsx<vlmem_op_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn "riscv_vsx<vlmem_op_attr>v_<mode>_internal"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSXMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vsx<vlmem_op_attr>.v\t%2,%0,%1");
  }
)

; store mask

(define_expand "riscv_vsx<vlmem_op_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSXMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vsx<vlmem_op_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vsx<vlmem_op_attr>v_mask_<mode>_split"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSXMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vsx<vlmem_op_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vsx<vlmem_op_attr>v_mask_<mode>_internal"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSXMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vsx<vlmem_op_attr>.v\t%2,%0,%1,%3.t");
  }
)

; unordered store

(define_expand "riscv_vsux<vlmem_op_attr>v_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSUXMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vsux<vlmem_op_attr>v_<mode>_split(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_vsux<vlmem_op_attr>v_<mode>_split"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSUXMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_vsux<vlmem_op_attr>v_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn "riscv_vsux<vlmem_op_attr>v_<mode>_internal"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "register_operand" "r")]
                        UNSPEC_VSUXMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vsux<vlmem_op_attr>.v\t%2,%0,%1");
  }
)

; unordered store mask

(define_expand "riscv_vsux<vlmem_op_attr>v_mask_<mode>"
  [(set (match_operand 0 "register_operand" "=r")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSUXMEM_OP))]
  "TARGET_VECTOR"
  {
    operands[0] = gen_rtx_MEM(<MODE>mode, operands[0]);
    emit_insn(gen_riscv_vsux<vlmem_op_attr>v_mask_<mode>_split(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vsux<vlmem_op_attr>v_mask_<mode>_split"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSUXMEM_OP))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vsux<vlmem_op_attr>v_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vsux<vlmem_op_attr>v_mask_<mode>_internal"
  [(set (match_operand:VALL 0 "riscv_vector_mem_operand" "=Qmv")
        (unspec:VALL [(match_operand 1 "register_operand" "v")
                         (match_operand 2 "register_operand" "v")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand 4 "register_operand" "r")]
                        UNSPEC_VSUXMEM_OP))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vsux<vlmem_op_attr>.v\t%2,%0,%1,%3.t");
  }
)

(include "riscv-v-segmem.md")
