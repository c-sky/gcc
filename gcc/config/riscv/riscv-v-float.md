;; float-point/interger type-convert instruction
(define_insn_and_split "riscv_vfcvtxfv_<mode>"
  [(set (match_operand:VTDSH 0 "register_operand" "=v")
        (unspec:VTDSH [(match_operand:<V_CVTF_ATTR> 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCVTXFV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfcvt_x_f_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfcvtxfv_mask_<mode>"
  [(set (match_operand:VTDSH 0 "register_operand" "=u")
        (unspec:VTDSH [(match_operand:VTDSH 1 "register_operand" "0")
                       (match_operand:<V_CVTF_ATTR> 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCVTXFV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfcvt_x_f_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfcvtxufv_<mode>"
  [(set (match_operand:VTDSH 0 "register_operand" "=v")
        (unspec:VTDSH [(match_operand:<V_CVTF_ATTR> 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCVTXUFV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfcvt_xu_f_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfcvtxufv_mask_<mode>"
  [(set (match_operand:VTDSH 0 "register_operand" "=u")
        (unspec:VTDSH [(match_operand:VTDSH 1 "register_operand" "0")
                       (match_operand:<V_CVTF_ATTR> 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCVTXUFV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfcvt_xu_f_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfcvtfxv_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:<VF_CVTX_ATTR> 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCVTFXV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfcvt_f_x_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfcvtfxv_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:<VF_CVTX_ATTR> 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCVTFXV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfcvt_f_x_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfcvtfxuv_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:<VF_CVTX_ATTR> 1 "register_operand" "v")
                (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCVTFXUV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfcvt_f_xu_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfcvtfxuv_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:<VF_CVTX_ATTR> 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCVTFXUV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfcvt_f_xu_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtxfv_<mode>"
  [(set (match_operand:VNARROWER 0 "register_operand" "=&v")
        (unspec:VNARROWER [(match_operand:<VNARROW_F_ATTR> 1 "register_operand" "v")
                           (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTXFV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfncvt_x_f_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtxfv_mask_<mode>"
  [(set (match_operand:VNARROWER 0 "register_operand" "=&u")
        (unspec:VNARROWER [(match_operand:VNARROWER 1 "register_operand" "0")
                           (match_operand:<VNARROW_F_ATTR> 2 "register_operand" "u")
                           (match_operand 3 "vmask_mode_register_operand" "w")
                           (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTXFV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfncvt_x_f_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtxufv_<mode>"
  [(set (match_operand:VNARROWER 0 "register_operand" "=&v")
        (unspec:VNARROWER [(match_operand:<VNARROW_F_ATTR> 1 "register_operand" "v")
                           (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTXUFV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfncvt_xu_f_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtxufv_mask_<mode>"
  [(set (match_operand:VNARROWER 0 "register_operand" "=&u")
        (unspec:VNARROWER [(match_operand:VNARROWER 1 "register_operand" "0")
                           (match_operand:<VNARROW_F_ATTR> 2 "register_operand" "u")
                           (match_operand 3 "vmask_mode_register_operand" "w")
                           (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTXUFV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfncvt_xu_f_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtfxv_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&v")
        (unspec:VFNARROW [(match_operand:<VFNARROW_X_ATTR> 1 "register_operand" "v")
                          (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTFXV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfncvt_f_x_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtfxv_mask_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&u")
        (unspec:VFNARROW [(match_operand:VFNARROW 1 "register_operand" "0")
                          (match_operand:<VFNARROW_X_ATTR> 2 "register_operand" "u")
                          (match_operand 3 "vmask_mode_register_operand" "w")
                          (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTFXV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfncvt_f_x_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtfxuv_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&v")
        (unspec:VFNARROW [(match_operand:<VFNARROW_X_ATTR> 1 "register_operand" "v")
                          (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTFXUV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfncvt_f_xu_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtfxuv_mask_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&u")
        (unspec:VFNARROW [(match_operand:VFNARROW 1 "register_operand" "0")
                          (match_operand:<VFNARROW_X_ATTR> 2 "register_operand" "u")
                          (match_operand 3 "vmask_mode_register_operand" "w")
                          (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTFXUV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfncvt_f_xu_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtxfv_<mode>"
  [(set (match_operand:VWIDEN_FROM_FLOAT 0 "register_operand" "=&v")
        (unspec:VWIDEN_FROM_FLOAT [(match_operand:<VWIDEN_F_ATTR> 1 "register_operand" "v")
                                   (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTXFV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VWIDEN_F_ATTR>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfwcvt_x_f_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtxfv_mask_<mode>"
  [(set (match_operand:VWIDEN_FROM_FLOAT 0 "register_operand" "=&u")
        (unspec:VWIDEN_FROM_FLOAT [(match_operand:VWIDEN_FROM_FLOAT 1 "register_operand" "0")
                                   (match_operand:<VWIDEN_F_ATTR> 2 "register_operand" "u")
                                   (match_operand 3 "vmask_mode_register_operand" "w")
                                   (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTXFV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VWIDEN_F_ATTR>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfwcvt_x_f_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtxufv_<mode>"
  [(set (match_operand:VWIDEN_FROM_FLOAT 0 "register_operand" "=&v")
        (unspec:VWIDEN_FROM_FLOAT [(match_operand:<VWIDEN_F_ATTR> 1 "register_operand" "v")
                                   (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTXUFV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VWIDEN_F_ATTR>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfwcvt_xu_f_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtxufv_mask_<mode>"
  [(set (match_operand:VWIDEN_FROM_FLOAT 0 "register_operand" "=&u")
        (unspec:VWIDEN_FROM_FLOAT [(match_operand:VWIDEN_FROM_FLOAT 1 "register_operand" "0")
                                   (match_operand:<VWIDEN_F_ATTR> 2 "register_operand" "u")
                                   (match_operand 3 "vmask_mode_register_operand" "w")
                                   (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTXUFV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VWIDEN_F_ATTR>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfwcvt_xu_f_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtfxv_<mode>"
  [(set (match_operand:VFWIDEN_FROM_INT 0 "register_operand" "=&v")
        (unspec:VFWIDEN_FROM_INT [(match_operand:<VFWIDEN_X_ATTR> 1 "register_operand" "v")
                                  (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTFXV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_X_ATTR>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfwcvt_f_x_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtfxv_mask_<mode>"
  [(set (match_operand:VFWIDEN_FROM_INT 0 "register_operand" "=&u")
        (unspec:VFWIDEN_FROM_INT [(match_operand:VFWIDEN_FROM_INT 1 "register_operand" "0")
                                  (match_operand:<VFWIDEN_X_ATTR> 2 "register_operand" "u")
                                  (match_operand 3 "vmask_mode_register_operand" "w")
                                  (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTFXV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_X_ATTR>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfwcvt_f_x_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtfxuv_<mode>"
  [(set (match_operand:VFWIDEN_FROM_INT 0 "register_operand" "=&v")
        (unspec:VFWIDEN_FROM_INT [(match_operand:<VFWIDEN_X_ATTR> 1 "register_operand" "v")
                                  (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTFXUV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_X_ATTR>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfwcvt_f_xu_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtfxuv_mask_<mode>"
  [(set (match_operand:VFWIDEN_FROM_INT 0 "register_operand" "=&u")
        (unspec:VFWIDEN_FROM_INT [(match_operand:VFWIDEN_FROM_INT 1 "register_operand" "0")
                                  (match_operand:<VFWIDEN_X_ATTR> 2 "register_operand" "u")
                                  (match_operand 3 "vmask_mode_register_operand" "w")
                                  (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTFXUV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_X_ATTR>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfwcvt_f_xu_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtffv_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&v")
        (unspec:VFNARROW [(match_operand:<VFNARROW_ATTR> 1 "register_operand" "v")
                          (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTFFV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfncvt_f_f_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfncvtffv_mask_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&u")
        (unspec:VFNARROW [(match_operand:VFNARROW 1 "register_operand" "0")
                          (match_operand:<VFNARROW_ATTR> 2 "register_operand" "u")
                          (match_operand 3 "vmask_mode_register_operand" "w")
                          (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTFFV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfncvt_f_f_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtffv_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")
                         (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTFFV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfwcvt_f_f_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfwcvtffv_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "u")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTFFV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfwcvt_f_f_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opm_attr>vv_<VFANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:VFANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OPM_VV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFANY:MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_opm_attr>_vv_<VFANY:mode>_<VMASK:mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opm_attr>vf_<VFANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VFANY 1 "register_operand" "v")
                 (match_operand:<VFANY:VF_SEM_ATTR> 2 "register_operand" "f")
                 (match_operand:SI 3 "register_operand" "r")]
         VF_OPM_VF))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_opm_attr>_vf_<VFANY:mode>_<VMASK:mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opm_attr>vv_mask_<VFANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
        (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                 (match_operand:VFANY 2 "register_operand" "u")
                 (match_operand:VFANY 3 "register_operand" "u")
                 (match_operand 4 "vmask_mode_register_operand" "w")
                 (match_operand:SI 5 "register_operand" "r")]
         VF_OPM_VV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFANY:MODE>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vf_opm_attr>_vv_mask_<VFANY:mode>_<VMASK:mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opm_attr>vf_mask_<VFANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
        (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand:<VFANY:VF_SEM_ATTR> 3 "register_operand" "f")
                       (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
         VF_OPM_VF_MASK))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFANY:MODE>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vf_opm_attr>_vf_mask_<VFANY:mode>_<VMASK:mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfsqrtv_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFSQRTV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfsqrt_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfsqrtv_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFSQRTV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfsqrt_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfclassv_<mode>"
  [(set (match_operand:<VF_CVTX_ATTR> 0 "register_operand" "=v")
        (unspec:<VF_CVTX_ATTR> [(match_operand:VFANY 1 "register_operand" "v")
                                (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCLASSV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfclass_v_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfclassv_mask_<mode>"
  [(set (match_operand:<VF_CVTX_ATTR> 0 "register_operand" "=u")
        (unspec:<VF_CVTX_ATTR> [(match_operand:<VF_CVTX_ATTR> 1 "register_operand" "0")
                                (match_operand:VFANY 2 "register_operand" "u")
                                (match_operand 3 "vmask_mode_register_operand" "w")
                                (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCLASSV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfclass_v_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_attr>vv_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:VFANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OP_VV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_op_attr>_vv_<mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_attr>vf_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:<VF_SEM_ATTR> 2 "register_operand" "f")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OP_VF))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_op_attr>_vf_<mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_attr>vv_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand:VFANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
         VF_OP_VV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vf_op_attr>_vv_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_attr>vf_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand:<VF_SEM_ATTR> 3 "register_operand" "f")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
         VF_OP_VF_MASK))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vf_op_attr>_vf_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_attr>vv_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "v")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_VV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_opw_attr>_vv_<mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_attr>vf_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")
                         (match_operand:<VFWIDEN_SEM_ATTR> 2 "register_operand" "f")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_VF))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_opw_attr>_vf_<mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_attr>vv_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "u")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "u")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
         VF_OPW_VV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vf_opw_attr>_vv_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_attr>vf_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "u")
                         (match_operand:<VFWIDEN_SEM_ATTR> 3 "register_operand" "f")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
         VF_OPW_VF_MASK))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vf_opw_attr>_vf_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_attr>wv_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "v")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "v")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_WV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_opw_attr>_wv_<mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_attr>wf_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "v")
                         (match_operand:<VFWIDEN_SEM_ATTR> 2 "register_operand" "f")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_WF))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_opw_attr>_wf_<mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_attr>wv_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:VFWIDEN 2 "register_operand" "u")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "u")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
         VF_OPW_WV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vf_opw_attr>_wv_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_attr>wf_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:VFWIDEN 2 "register_operand" "u")
                         (match_operand:<VFWIDEN_SEM_ATTR> 3 "register_operand" "f")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
         VF_OPW_VF_MASK))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vf_opw_attr>_wf_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_fused_attr>vv_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "v")
                       (match_operand:VFANY 3 "register_operand" "v")
                       (match_operand:SI 4 "register_operand" "r")]
         VF_OP_FUSED_VV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vf_op_fused_attr>_vv_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_fused_attr>vf_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:<VF_SEM_ATTR> 2 "register_operand" "f")
                       (match_operand:VFANY 3 "register_operand" "v")
                       (match_operand:SI 4 "register_operand" "r")]
         VF_OP_FUSED_VF))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vf_op_fused_attr>_vf_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_fused_attr>vv_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "u")
                       (match_operand:VFANY 2 "register_operand" "0")
                       (match_operand:VFANY 3 "register_operand" "u")
                       (match_operand:VFANY 4 "register_operand" "u")
                       (match_operand 5 "vmask_mode_register_operand" "w")
                       (match_operand:SI 6 "register_operand" "r")]
         VF_OP_FUSED_VV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    if (REGNO(operands[0]) != REGNO(operands[1]))
      emit_move_insn(operands[0], operands[1]);
    riscv_emit_vsetvli(<MODE>mode, operands[6], operands[6]);
    emit_insn(gen_riscv_<vf_op_fused_attr>_vv_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_fused_attr>vf_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "u")
                       (match_operand:VFANY 2 "register_operand" "0")
                       (match_operand:<VF_SEM_ATTR> 3 "register_operand" "f")
                       (match_operand:VFANY 4 "register_operand" "u")
                       (match_operand 5 "vmask_mode_register_operand" "w")
                       (match_operand:SI 6 "register_operand" "r")]
         VF_OP_FUSED_VF_MASK))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    if (REGNO(operands[0]) != REGNO(operands[1]))
      emit_move_insn(operands[0], operands[1]);
    riscv_emit_vsetvli(<MODE>mode, operands[6], operands[6]);
    emit_insn(gen_riscv_<vf_op_fused_attr>_vf_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_fusedw_attr>vv_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "v")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "v")
                         (match_operand:SI 4 "register_operand" "r")]
         VF_OP_FUSEDW_VV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vf_op_fusedw_attr>_vv_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_fusedw_attr>vf_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_SEM_ATTR> 2 "register_operand" "f")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "v")
                         (match_operand:SI 4 "register_operand" "r")]
         VF_OP_FUSEDW_VF))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vf_op_fusedw_attr>_vf_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_fusedw_attr>vv_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "u")
                         (match_operand:VFWIDEN 2 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "u")
                         (match_operand:<VFWIDEN_ATTR> 4 "register_operand" "u")
                         (match_operand 5 "vmask_mode_register_operand" "w")
                         (match_operand:SI 6 "register_operand" "r")]
         VF_OP_FUSEDW_VV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    if (REGNO(operands[0]) != REGNO(operands[1]))
      emit_move_insn(operands[0], operands[1]);
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[6], operands[6]);
    emit_insn(gen_riscv_<vf_op_fusedw_attr>_vv_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_fusedw_attr>vf_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "u")
                         (match_operand:VFWIDEN 2 "register_operand" "0")
                 (match_operand:<VFWIDEN_SEM_ATTR> 3 "register_operand" "f")
                 (match_operand:<VFWIDEN_ATTR> 4 "register_operand" "u")
                 (match_operand 5 "vmask_mode_register_operand" "w")
                 (match_operand:SI 6 "register_operand" "r")]
         VF_OP_FUSEDW_VF_MASK))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    if (REGNO(operands[0]) != REGNO(operands[1]))
      emit_move_insn(operands[0], operands[1]);
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[6], operands[6]);
    emit_insn(gen_riscv_<vf_op_fusedw_attr>_vf_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4], operands[5], operands[6]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfmergevfm_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "u")
                       (match_operand:<VF_SEM_ATTR> 2 "register_operand" "f")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFMARGEVFM))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vfmerge_vfm_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfmvvf_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:<VF_SEM_ATTR> 1 "register_operand" "f")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFMVVF))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfmv_v_f_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfmvsf_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:<VF_SEM_ATTR> 1 "register_operand" "f")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFMVSF))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfmv_s_f_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_vfmvfs_<mode>"
  [(set (match_operand:<VF_SEM_ATTR> 0 "register_operand" "=f")
        (unspec:<VF_SEM_ATTR> [(match_operand:VFANY 1 "register_operand" "v")
                               (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFMVFS))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vfmv_f_s_<mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_vs_attr>vs_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:VFANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OP_VS))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_op_vs_attr>_vs_<mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_op_vs_attr>vs_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "u")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         VF_OP_VS))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vf_op_vs_attr>_vs_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_vs_attr>vs_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")
                         (match_operand:VFWIDEN 2 "register_operand" "v")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_VS))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vf_opw_vs_attr>_vs_<mode>(operands[0], operands[1], operands[2], operands[3]));
    DONE;
  }
)

(define_insn_and_split "riscv_<vf_opw_vs_attr>vs_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "u")
                         (match_operand:VFWIDEN 2 "register_operand" "u")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")]
         VF_OPW_VS))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VFWIDEN_ATTR>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vf_opw_vs_attr>_vs_mask_<mode>(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

;; Auto-vectorize
;; SPN
(define_expand "vec_duplicate<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (vec_duplicate:VFANY (match_operand:<VF_SEM_ATTR> 1 "register_operand" "f")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN && TARGET_HARD_FLOAT"
  {
    emit_insn(gen_riscv_vfmvvf_<mode>(operands[0], operands[1], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "add<mode>3"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (plus:VFANY (match_operand:VFANY 1 "register_operand" "v")
                    (match_operand:VFANY 2 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfaddvv_<mode>(operands[0], operands[1], operands[2], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "sub<mode>3"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (minus:VFANY (match_operand:VFANY 1 "register_operand" "v")
                     (match_operand:VFANY 2 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfsubvv_<mode>(operands[0], operands[1], operands[2], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "mul<mode>3"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (mult:VFANY (match_operand:VFANY 1 "register_operand" "v")
                    (match_operand:VFANY 2 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfmulvv_<mode>(operands[0], operands[1], operands[2], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "div<mode>3"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (div:VFANY (match_operand:VFANY 1 "register_operand" "v")
                   (match_operand:VFANY 2 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfdivvv_<mode>(operands[0], operands[1], operands[2], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "sqrt<mode>2"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (sqrt:VFANY (match_operand:VFANY 1 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfsqrtv_<mode>(operands[0], operands[1], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "fix<v_cvtf_attr><mode>2"
  [(set (match_operand:VTDSH 0 "register_operand" "=v")
        (fix:VTDSH (match_operand:<V_CVTF_ATTR> 1 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfcvtxfv_<mode>(operands[0], operands[1], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "fixuns<v_cvtf_attr><mode>2"
  [(set (match_operand:VTDSH 0 "register_operand" "=v")
        (unsigned_fix:VTDSH (match_operand:<V_CVTF_ATTR> 1 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfcvtxufv_<mode>(operands[0], operands[1], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "float<vf_cvtx_attr><mode>2"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (float:VFANY (match_operand:<VF_CVTX_ATTR> 1 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfcvtfxv_<mode>(operands[0], operands[1], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "floatuns<vf_cvtx_attr><mode>2"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unsigned_float:VFANY (match_operand:<VF_CVTX_ATTR> 1 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfcvtfxuv_<mode>(operands[0], operands[1], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "trunc<vfnarrow_attr><mode>2"
  [(set (match_operand:VFNARROW 0 "register_operand" "=v")
        (float_truncate:VFNARROW (match_operand:<VFNARROW_ATTR> 1 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfncvtffv_<mode>(operands[0], operands[1], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

(define_expand "extend<vfwiden_attr><mode>2"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=v")
        (float_extend:VFWIDEN (match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")))]
  "TARGET_VECTOR && TARGET_VECTOR_VSPN"
  {
    emit_insn(gen_riscv_vfwcvtffv_<mode>(operands[0], operands[1], gen_rtx_REG(SImode, 0)));
    DONE;
  }
)

;; float-point/interger type-convert instruction
(define_insn "riscv_vfcvt_x_f_v_<mode>"
  [(set (match_operand:VTDSH 0 "register_operand" "=v")
        (unspec:VTDSH [(match_operand:<V_CVTF_ATTR> 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCVTXFV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfcvt.x.f.v\t%0,%1");
  }
)

(define_insn "riscv_vfcvt_x_f_v_mask_<mode>"
  [(set (match_operand:VTDSH 0 "register_operand" "=u")
        (unspec:VTDSH [(match_operand:VTDSH 1 "register_operand" "0")
                       (match_operand:<V_CVTF_ATTR> 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCVTXFV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfcvt.x.f.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfcvt_xu_f_v_<mode>"
  [(set (match_operand:VTDSH 0 "register_operand" "=v")
        (unspec:VTDSH [(match_operand:<V_CVTF_ATTR> 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCVTXUFV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfcvt.xu.f.v\t%0,%1");
  }
)

(define_insn "riscv_vfcvt_xu_f_v_mask_<mode>"
  [(set (match_operand:VTDSH 0 "register_operand" "=u")
        (unspec:VTDSH [(match_operand:VTDSH 1 "register_operand" "0")
                       (match_operand:<V_CVTF_ATTR> 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCVTXUFV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfcvt.xu.f.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfcvt_f_x_v_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:<VF_CVTX_ATTR> 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCVTFXV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfcvt.f.x.v\t%0,%1");
  }
)

(define_insn "riscv_vfcvt_f_x_v_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:<VF_CVTX_ATTR> 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCVTFXV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfcvt.f.x.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfcvt_f_xu_v_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:<VF_CVTX_ATTR> 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCVTFXUV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfcvt.f.xu.v\t%0,%1");
  }
)

(define_insn "riscv_vfcvt_f_xu_v_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:<VF_CVTX_ATTR> 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCVTFXUV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfcvt.f.xu.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfncvt_x_f_v_<mode>"
  [(set (match_operand:VNARROWER 0 "register_operand" "=&v")
        (unspec:VNARROWER [(match_operand:<VNARROW_F_ATTR> 1 "register_operand" "v")
                           (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTXFV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.x.f.v\t%0,%1");
  }
)

(define_insn "riscv_vfncvt_x_f_v_mask_<mode>"
  [(set (match_operand:VNARROWER 0 "register_operand" "=&u")
        (unspec:VNARROWER [(match_operand:VNARROWER 1 "register_operand" "0")
                           (match_operand:<VNARROW_F_ATTR> 2 "register_operand" "u")
                           (match_operand 3 "vmask_mode_register_operand" "w")
                           (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTXFV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.x.f.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfncvt_xu_f_v_<mode>"
  [(set (match_operand:VNARROWER 0 "register_operand" "=&v")
        (unspec:VNARROWER [(match_operand:<VNARROW_F_ATTR> 1 "register_operand" "v")
                           (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTXUFV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.xu.f.v\t%0,%1");
  }
)

(define_insn "riscv_vfncvt_xu_f_v_mask_<mode>"
  [(set (match_operand:VNARROWER 0 "register_operand" "=&u")
        (unspec:VNARROWER [(match_operand:VNARROWER 1 "register_operand" "0")
                           (match_operand:<VNARROW_F_ATTR> 2 "register_operand" "u")
                           (match_operand 3 "vmask_mode_register_operand" "w")
                           (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTXUFV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.xu.f.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfncvt_f_x_v_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&v")
        (unspec:VFNARROW [(match_operand:<VFNARROW_X_ATTR> 1 "register_operand" "v")
                          (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTFXV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.f.x.v\t%0,%1");
  }
)

(define_insn "riscv_vfncvt_f_x_v_mask_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&u")
        (unspec:VFNARROW [(match_operand:VFNARROW 1 "register_operand" "0")
                          (match_operand:<VFNARROW_X_ATTR> 2 "register_operand" "u")
                          (match_operand 3 "vmask_mode_register_operand" "w")
                          (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTFXV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.f.x.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfncvt_f_xu_v_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&v")
        (unspec:VFNARROW [(match_operand:<VFNARROW_X_ATTR> 1 "register_operand" "v")
                          (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTFXUV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.f.xu.v\t%0,%1");
  }
)

(define_insn "riscv_vfncvt_f_xu_v_mask_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&u")
        (unspec:VFNARROW [(match_operand:VFNARROW 1 "register_operand" "0")
                          (match_operand:<VFNARROW_X_ATTR> 2 "register_operand" "u")
                          (match_operand 3 "vmask_mode_register_operand" "w")
                          (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTFXUV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.f.xu.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfwcvt_x_f_v_<mode>"
  [(set (match_operand:VWIDEN_FROM_FLOAT 0 "register_operand" "=&v")
        (unspec:VWIDEN_FROM_FLOAT [(match_operand:<VWIDEN_F_ATTR> 1 "register_operand" "v")
                                   (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTXFV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.x.f.v\t%0,%1");
  }
)

(define_insn "riscv_vfwcvt_x_f_v_mask_<mode>"
  [(set (match_operand:VWIDEN_FROM_FLOAT 0 "register_operand" "=&u")
        (unspec:VWIDEN_FROM_FLOAT [(match_operand:VWIDEN_FROM_FLOAT 1 "register_operand" "0")
                                   (match_operand:<VWIDEN_F_ATTR> 2 "register_operand" "u")
                                   (match_operand 3 "vmask_mode_register_operand" "w")
                                   (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTXFV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.x.f.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfwcvt_xu_f_v_<mode>"
  [(set (match_operand:VWIDEN_FROM_FLOAT 0 "register_operand" "=&v")
        (unspec:VWIDEN_FROM_FLOAT [(match_operand:<VWIDEN_F_ATTR> 1 "register_operand" "v")
                                   (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTXUFV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.xu.f.v\t%0,%1");
  }
)

(define_insn "riscv_vfwcvt_xu_f_v_mask_<mode>"
  [(set (match_operand:VWIDEN_FROM_FLOAT 0 "register_operand" "=&u")
        (unspec:VWIDEN_FROM_FLOAT [(match_operand:VWIDEN_FROM_FLOAT 1 "register_operand" "0")
                                   (match_operand:<VWIDEN_F_ATTR> 2 "register_operand" "u")
                                   (match_operand 3 "vmask_mode_register_operand" "w")
                                   (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTXUFV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.xu.f.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfwcvt_f_x_v_<mode>"
  [(set (match_operand:VFWIDEN_FROM_INT 0 "register_operand" "=&v")
        (unspec:VFWIDEN_FROM_INT [(match_operand:<VFWIDEN_X_ATTR> 1 "register_operand" "v")
                                  (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTFXV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.f.x.v\t%0,%1");
  }
)

(define_insn "riscv_vfwcvt_f_x_v_mask_<mode>"
  [(set (match_operand:VFWIDEN_FROM_INT 0 "register_operand" "=&u")
        (unspec:VFWIDEN_FROM_INT [(match_operand:VFWIDEN_FROM_INT 1 "register_operand" "0")
                                  (match_operand:<VFWIDEN_X_ATTR> 2 "register_operand" "u")
                                  (match_operand 3 "vmask_mode_register_operand" "w")
                                  (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTFXV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.f.x.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfwcvt_f_xu_v_<mode>"
  [(set (match_operand:VFWIDEN_FROM_INT 0 "register_operand" "=&v")
        (unspec:VFWIDEN_FROM_INT [(match_operand:<VFWIDEN_X_ATTR> 1 "register_operand" "v")
                                  (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTFXUV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.f.xu.v\t%0,%1");
  }
)

(define_insn "riscv_vfwcvt_f_xu_v_mask_<mode>"
  [(set (match_operand:VFWIDEN_FROM_INT 0 "register_operand" "=&u")
        (unspec:VFWIDEN_FROM_INT [(match_operand:VFWIDEN_FROM_INT 1 "register_operand" "0")
                                  (match_operand:<VFWIDEN_X_ATTR> 2 "register_operand" "u")
                                  (match_operand 3 "vmask_mode_register_operand" "w")
                                  (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTFXUV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.f.xu.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfncvt_f_f_v_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&v")
        (unspec:VFNARROW [(match_operand:<VFNARROW_ATTR> 1 "register_operand" "v")
                          (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFNCVTFFV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.f.f.v\t%0,%1");
  }
)

(define_insn "riscv_vfncvt_f_f_v_mask_<mode>"
  [(set (match_operand:VFNARROW 0 "register_operand" "=&u")
        (unspec:VFNARROW [(match_operand:VFNARROW 1 "register_operand" "0")
                          (match_operand:<VFNARROW_ATTR> 2 "register_operand" "u")
                          (match_operand 3 "vmask_mode_register_operand" "w")
                          (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFNCVTFFV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfncvt.f.f.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfwcvt_f_f_v_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")
                         (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFWCVTFFV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.f.f.v\t%0,%1");
  }
)

(define_insn "riscv_vfwcvt_f_f_v_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "u")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFWCVTFFV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfwcvt.f.f.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_<vf_opm_attr>_vv_<VFANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:VFANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OPM_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<VFANY:MODE>mode, "<vf_opm_attr>.vv\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_opm_attr>_vf_<VFANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:<VFANY:VF_SEM_ATTR> 2 "register_operand" "f")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OPM_VF))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<VFANY:MODE>mode, "<vf_opm_attr>.vf\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_opm_attr>_vv_mask_<VFANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
        (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand:VFANY 3 "register_operand" "u")
                       (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
         VF_OPM_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<VFANY:MODE>mode, "<vf_opm_attr>.vv\t%0,%2,%3,%4.t");
  }
)

(define_insn "riscv_<vf_opm_attr>_vf_mask_<VFANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
        (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand:<VFANY:VF_SEM_ATTR> 3 "register_operand" "f")
                       (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
         VF_OPM_VF_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<VFANY:MODE>mode, "<vf_opm_attr>.vf\t%0,%2,%3,%4.t");
  }
)

(define_insn "riscv_vfsqrt_v_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFSQRTV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfsqrt.v\t%0,%1");
  }
)

(define_insn "riscv_vfsqrt_v_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFSQRTV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfsqrt.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_vfclass_v_<mode>"
  [(set (match_operand:<VF_CVTX_ATTR> 0 "register_operand" "=v")
        (unspec:<VF_CVTX_ATTR> [(match_operand:VFANY 1 "register_operand" "v")
                                (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFCLASSV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfclass.v\t%0,%1");
  }
)

(define_insn "riscv_vfclass_v_mask_<mode>"
  [(set (match_operand:<VF_CVTX_ATTR> 0 "register_operand" "=u")
        (unspec:<VF_CVTX_ATTR> [(match_operand:<VF_CVTX_ATTR> 1 "register_operand" "0")
                                (match_operand:VFANY 2 "register_operand" "u")
                                (match_operand 3 "vmask_mode_register_operand" "w")
                                (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFCLASSV_MASK))
   (clobber (const_int 0))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfclass.v\t%0,%2,%3.t");
  }
)

(define_insn "riscv_<vf_op_attr>_vv_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:VFANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OP_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_attr>.vv\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_op_attr>_vf_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:<VF_SEM_ATTR> 2 "register_operand" "f")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OP_VF))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_attr>.vf\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_op_attr>_vv_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand:VFANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
         VF_OP_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_attr>.vv\t%0,%2,%3,%4.t");
  }
)

(define_insn "riscv_<vf_op_attr>_vf_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand:<VF_SEM_ATTR> 3 "register_operand" "f")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
         VF_OP_VF_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_attr>.vf\t%0,%2,%3,%4.t");
  }
)

(define_insn "riscv_<vf_opw_attr>_vv_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "v")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_attr>.vv\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_opw_attr>_vf_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")
                         (match_operand:<VFWIDEN_SEM_ATTR> 2 "register_operand" "f")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_VF))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_attr>.vf\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_opw_attr>_vv_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "u")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "u")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
         VF_OPW_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_attr>.vv\t%0,%2,%3,%4.t");
  }
)

(define_insn "riscv_<vf_opw_attr>_vf_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "u")
                         (match_operand:<VFWIDEN_SEM_ATTR> 3 "register_operand" "f")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
         VF_OPW_VF_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_attr>.vf\t%0,%2,%3,%4.t");
  }
)

(define_insn "riscv_<vf_opw_attr>_wv_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "v")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "v")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_WV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_attr>.wv\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_opw_attr>_wf_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "v")
                         (match_operand:<VFWIDEN_SEM_ATTR> 2 "register_operand" "f")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_WF))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_attr>.wf\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_opw_attr>_wv_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:VFWIDEN 2 "register_operand" "u")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "u")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
         VF_OPW_WV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_attr>.wv\t%0,%2,%3,%4.t");
  }
)

(define_insn "riscv_<vf_opw_attr>_wf_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:VFWIDEN 2 "register_operand" "u")
                         (match_operand:<VFWIDEN_SEM_ATTR> 3 "register_operand" "f")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
         VF_OPW_VF_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_attr>.wf\t%0,%2,%3,%4.t");
  }
)

(define_insn "riscv_<vf_op_fused_attr>_vv_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:VFANY 2 "register_operand" "v")
                       (match_operand:VFANY 3 "register_operand" "v")
                       (match_operand:SI 4 "register_operand" "r")]
         VF_OP_FUSED_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_fused_attr>.vv\t%0,%2,%3");
  }
)

(define_insn "riscv_<vf_op_fused_attr>_vf_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "0")
                       (match_operand:<VF_SEM_ATTR> 2 "register_operand" "f")
                       (match_operand:VFANY 3 "register_operand" "v")
                       (match_operand:SI 4 "register_operand" "r")]
         VF_OP_FUSED_VF))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_fused_attr>.vf\t%0,%2,%3");
  }
)

(define_insn "riscv_<vf_op_fused_attr>_vv_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "u")
                       (match_operand:VFANY 2 "register_operand" "0")
                       (match_operand:VFANY 3 "register_operand" "u")
                       (match_operand:VFANY 4 "register_operand" "u")
                       (match_operand 5 "vmask_mode_register_operand" "w")
                       (match_operand:SI 6 "register_operand" "r")]
         VF_OP_FUSED_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_fused_attr>.vv\t%0,%3,%4,%5.t");
  }
)

(define_insn "riscv_<vf_op_fused_attr>_vf_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "u")
                       (match_operand:VFANY 2 "register_operand" "0")
                       (match_operand:<VF_SEM_ATTR> 3 "register_operand" "f")
                       (match_operand:VFANY 4 "register_operand" "u")
                       (match_operand 5 "vmask_mode_register_operand" "w")
                       (match_operand:SI 6 "register_operand" "r")]
         VF_OP_FUSED_VF_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_fused_attr>.vf\t%0,%3,%4,%5.t");
  }
)

(define_insn "riscv_<vf_op_fusedw_attr>_vv_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 2 "register_operand" "v")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "v")
                         (match_operand:SI 4 "register_operand" "r")]
         VF_OP_FUSEDW_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_fusedw_attr>.vv\t%0,%2,%3");
  }
)

(define_insn "riscv_<vf_op_fusedw_attr>_vf_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "0")
                         (match_operand:<VFWIDEN_SEM_ATTR> 2 "register_operand" "f")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "v")
                         (match_operand:SI 4 "register_operand" "r")]
         VF_OP_FUSEDW_VF))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_fusedw_attr>.vf\t%0,%2,%3");
  }
)

(define_insn "riscv_<vf_op_fusedw_attr>_vv_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "u")
                         (match_operand:VFWIDEN 2 "register_operand" "0")
                         (match_operand:<VFWIDEN_ATTR> 3 "register_operand" "u")
                         (match_operand:<VFWIDEN_ATTR> 4 "register_operand" "u")
                         (match_operand 5 "vmask_mode_register_operand" "w")
                         (match_operand:SI 6 "register_operand" "r")]
         VF_OP_FUSEDW_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_fusedw_attr>.vv\t%0,%3,%4,%5.t");
  }
)

(define_insn "riscv_<vf_op_fusedw_attr>_vf_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:VFWIDEN 1 "register_operand" "u")
                         (match_operand:VFWIDEN 2 "register_operand" "0")
                 (match_operand:<VFWIDEN_SEM_ATTR> 3 "register_operand" "f")
                 (match_operand:<VFWIDEN_ATTR> 4 "register_operand" "u")
                 (match_operand 5 "vmask_mode_register_operand" "w")
                 (match_operand:SI 6 "register_operand" "r")]
         VF_OP_FUSEDW_VF_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_fusedw_attr>.vf\t%0,%3,%4,%5.t");
  }
)

(define_insn "riscv_vfmerge_vfm_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "u")
                       (match_operand:<VF_SEM_ATTR> 2 "register_operand" "f")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VFMARGEVFM))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfmerge.vfm\t%0,%1,%2,%3");
  }
)

(define_insn "riscv_vfmv_v_f_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:<VF_SEM_ATTR> 1 "register_operand" "f")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFMVVF))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfmv.v.f\t%0,%1");
  }
)

(define_insn "riscv_vfmv_s_f_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:<VF_SEM_ATTR> 1 "register_operand" "f")
                       (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFMVSF))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfmv.s.f\t%0,%1");
  }
)

(define_insn "riscv_vfmv_f_s_<mode>"
  [(set (match_operand:<VF_SEM_ATTR> 0 "register_operand" "=f")
        (unspec:<VF_SEM_ATTR> [(match_operand:VFANY 1 "register_operand" "v")
                               (match_operand:SI 2 "register_operand" "r")]
         UNSPEC_VFMVFS))
   (clobber (const_int 0))]
  "TARGET_VECTOR && TARGET_HARD_FLOAT"
  {
    return riscv_output_vector_insn(<MODE>mode, "vfmv.f.s\t%0,%1");
  }
)

(define_insn "riscv_<vf_op_vs_attr>_vs_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=v")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "v")
                       (match_operand:VFANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
         VF_OP_VS))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_vs_attr>.vs\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_op_vs_attr>_vs_mask_<mode>"
  [(set (match_operand:VFANY 0 "register_operand" "=u")
        (unspec:VFANY [(match_operand:VFANY 1 "register_operand" "u")
                       (match_operand:VFANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
         VF_OP_VS))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_op_vs_attr>.vs\t%0,%1,%2,%3.t");
  }
)

(define_insn "riscv_<vf_opw_vs_attr>_vs_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&v")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "v")
                         (match_operand:VFWIDEN 2 "register_operand" "v")
                         (match_operand:SI 3 "register_operand" "r")]
         VF_OPW_VS))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_vs_attr>.vs\t%0,%1,%2");
  }
)

(define_insn "riscv_<vf_opw_vs_attr>_vs_mask_<mode>"
  [(set (match_operand:VFWIDEN 0 "register_operand" "=&u")
        (unspec:VFWIDEN [(match_operand:<VFWIDEN_ATTR> 1 "register_operand" "u")
                         (match_operand:VFWIDEN 2 "register_operand" "u")
                         (match_operand 3 "vmask_mode_register_operand" "w")
                         (match_operand:SI 4 "register_operand" "r")]
         VF_OPW_VS))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "<vf_opw_vs_attr>.vs\t%0,%1,%2,%3.t");
  }
)