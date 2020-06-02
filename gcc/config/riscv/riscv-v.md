;; vsetvli/vsetvl

(define_insn "riscv_vsetvli"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI
          [(match_operand:SI 1 "register_operand" "r")
           (match_operand 2 "immediate_operand" "i")
           (match_operand 3 "immediate_operand" "i")]
          UNSPEC_VSETVLI))]
  "TARGET_VECTOR"
  {
    const char *pattern = "vsetvli\t%%0,%%1,%s,%s";
    static char buf[128] = {0};
    snprintf(buf, sizeof(buf), pattern,
             riscv_output_vector_sew(INTVAL(operands[2])),
             riscv_output_vector_lmul(INTVAL(operands[3])));
    return buf;
  }
)

(define_insn "riscv_vsetvli_max"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI
          [(match_operand 1 "immediate_operand" "i")
           (match_operand 2 "immediate_operand" "i")]
          UNSPEC_VSETVLI_MAX))]
  "TARGET_VECTOR"
  {
    const char *pattern = "vsetvli\t%%0,x0,%s,%s";
    static char buf[128] = {0};
    snprintf(buf, sizeof(buf), pattern,
             riscv_output_vector_sew(INTVAL(operands[1])),
             riscv_output_vector_lmul(INTVAL(operands[2])));
    return buf;
  }
)

(define_insn "riscv_vsetvl"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI
          [(match_operand:SI 1 "register_operand" "r")
           (match_operand:SI 2 "register_operand" "r")]
          UNSPEC_VSETVLR))]
  "TARGET_VECTOR"
  "vsetvl\t%0,%1,%2"
)

(define_expand "mov<mode>"
  [(set (match_operand:VANY128 0 "nonimmediate_operand"  "")
        (match_operand:VANY128 1 "nonimmediate_operand"  ""))]
  "TARGET_VECTOR"
  {
    if (can_create_pseudo_p ())
      {
        if (!REG_P (operands[0]))
          operands[1] = force_reg (<MODE>mode, operands[1]);
      }
  }
)

(define_insn_and_split "riscv_mov_<mode>"
  [(set (match_operand:VANY128 0 "nonimmediate_operand"  "=v,v,m")
        (match_operand:VANY128 1 "nonimmediate_operand"  "v,m,v"))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    operands[2] = gen_rtx_REG(SImode, 0);
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);

    if (REG_P(operands[0]) && REG_P(operands[1]))
      emit_insn(gen_riscv_vmvvv_<mode>_internal(operands[0], operands[1], operands[2]));
    else if (REG_P(operands[0]) && MEM_P(operands[1]))
      emit_insn(gen_riscv_vlev_<mode>_internal(operands[0], operands[1], operands[2]));
    else if (REG_P(operands[1]) && MEM_P(operands[0]))
      emit_insn(gen_riscv_vsev_<mode>_internal(operands[0], operands[1], operands[2]));
    else
      gcc_unreachable ();

    DONE;
  }
)

(define_expand "mov<mode>"
  [(set (match_operand:VANY_STRUCT 0 "nonimmediate_operand"  "")
        (match_operand:VANY_STRUCT 1 "nonimmediate_operand"  ""))]
  "TARGET_VECTOR"
  {
    if (can_create_pseudo_p ())
      {
        if (!REG_P (operands[0]))
          operands[1] = force_reg (<MODE>mode, operands[1]);
      }
    rtx scratch = gen_rtx_SCRATCH (Pmode);
    rtx clobber = gen_rtx_CLOBBER (VOIDmode, scratch);
    rtx set = gen_rtx_SET (operands[0], operands[1]);
    emit_insn (gen_rtx_PARALLEL (VOIDmode, gen_rtvec (2, set, clobber)));
    DONE;
  }
)

(define_insn_and_split "riscv_mov_<mode>"
  [(set (match_operand:VANY_STRUCT 0 "nonimmediate_operand"  "=v,v,m")
        (match_operand:VANY_STRUCT 1 "nonimmediate_operand"  "v,m,v"))
   (clobber (match_scratch  2 "=X,&r,&r"))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    int mul = (GET_MODE_SIZE (<MODE>mode) + UNITS_PER_VR_REG - 1) / UNITS_PER_VR_REG;

    machine_mode mode = V16QImode;

    operands[3] = gen_rtx_REG(SImode, 0);
    riscv_emit_vsetvli(mode, operands[3], operands[3]);

    for (int i = 0; i < mul; i++)
      {
        int step = i ? 1 : 0;

        if (REG_P(operands[0]) && REG_P(operands[1]))
          {
            operands[0] = gen_rtx_REG(mode, REGNO(operands[0]) + step);
            operands[1] = gen_rtx_REG(mode, REGNO(operands[1]) + step);
            emit_insn(gen_riscv_vmvvv_v16qi_internal(operands[0], operands[1], operands[3]));
          }
        else if (REG_P(operands[0]) && MEM_P(operands[1]))
          {
            operands[0] = gen_rtx_REG(mode, REGNO(operands[0]) + step);

            rtx orig = force_reg (Pmode, XEXP (operands[1], 0));
            emit_insn (gen_add3_insn (operands[2], orig, gen_rtx_CONST_INT(VOIDmode, step * UNITS_PER_VR_REG)));
            operands[1] = gen_rtx_MEM(mode, operands[2]);
            emit_insn(gen_riscv_vlev_v16qi_internal(operands[0], operands[1], operands[3]));
          }
        else if (REG_P(operands[1]) && MEM_P(operands[0]))
          {
            operands[1] = gen_rtx_REG(mode, REGNO(operands[1]) + step);

            rtx orig = force_reg (Pmode, XEXP (operands[0], 0));
            emit_insn (gen_add3_insn (operands[2], orig, gen_rtx_CONST_INT(VOIDmode, step * UNITS_PER_VR_REG)));
            operands[0] = gen_rtx_MEM(mode, operands[2]);
            emit_insn(gen_riscv_vsev_v16qi_internal(operands[0], operands[1], operands[3]));
          }
        else
          gcc_unreachable ();
      }
    DONE;
  }
)

(include "riscv-v-mem.md")

;; vmcmp instruction

(define_insn_and_split "riscv_<vop>vv_<VANY:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
         (unspec:VMASK [(match_operand:VANY 1 "register_operand" "v")
                  (match_operand:VANY 2 "register_operand" "v")
                  (match_operand:SI 3 "register_operand" "r")]
                 VECTOR_INT_CMP_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VANY:MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vop>vv_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                 operands[3]));
    DONE;
   }
)

(define_insn "riscv_<vop>vv_<VANY:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
         (unspec:VMASK [(match_operand:VANY 1 "register_operand" "v")
                  (match_operand:VANY 2 "register_operand" "v")
                  (match_operand:SI 3 "register_operand" "r")]
                 VECTOR_INT_CMP_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "<vop>.vv\t%0,%1,%2");
  }
)

(define_insn_and_split "riscv_<vop>vx_<VANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VANY 1 "register_operand" "v")
                 (match_operand:<VANY:VANY_SCALAR_attr> 2 "register_operand" "r")
                 (match_operand:SI 3 "register_operand" "r")]
         VECTOR_INT_CMP_VX))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VANY:MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vop>vx_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                 operands[3]));
    DONE;
   }
)

(define_insn "riscv_<vop>vx_<VANY:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
         (unspec:VMASK [(match_operand:VANY 1 "register_operand" "v")
                  (match_operand:<VANY:VANY_SCALAR_attr> 2 "register_operand" "r")
                  (match_operand:SI 3 "register_operand" "r")]
                 VECTOR_INT_CMP_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vi_<VANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VANY 1 "register_operand" "v")
                 (match_operand:<VANY:VANY_SCALAR_attr> 2 "const_int_operand" "i")
                 (match_operand:SI 3 "register_operand" "r")]
         VECTOR_INT_CMP_VI))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VANY:MODE>mode, operands[3], operands[3]);
    emit_insn(gen_riscv_<vop>vi_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                 operands[3]));
    DONE;
   }
)

(define_insn "riscv_<vop>vi_<VANY:mode>_internal_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VANY 1 "register_operand" "v")
                 (match_operand:<VANY:VANY_SCALAR_attr> 2 "const_int_operand" "i")
                 (match_operand:SI 3 "register_operand" "r")]
         VECTOR_INT_CMP_VI))
  (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "<vop>.vi\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<VANY:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
         (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                  (match_operand:VANY 2 "register_operand" "u")
                  (match_operand:VANY 3 "register_operand" "u")
                  (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                  (match_operand:SI 5 "register_operand" "r")]
                 VECTOR_INT_CMP_VV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
    emit_insn(gen_riscv_<vop_mask>vv_mask_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                      operands[3], operands[4], operands[5]));
    DONE;
  }
)

(define_insn "riscv_<vop_mask>vv_mask_<VANY:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
         (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                  (match_operand:VANY 2 "register_operand" "u")
                  (match_operand:VANY 3 "register_operand" "u")
                  (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                  (match_operand:SI 5 "register_operand" "r")]
                 VECTOR_INT_CMP_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%4.t");
  }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<VANY:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
         (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                  (match_operand:VANY 2 "register_operand" "u")
                  (match_operand:<VANY:VANY_SCALAR_attr> 3 "register_operand" "r")
                  (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                  (match_operand:SI 5 "register_operand" "r")]
                 VECTOR_INT_CMP_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VANY:MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                      operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<VANY:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
         (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                  (match_operand:VANY 2 "register_operand" "u")
                  (match_operand:<VANY:VANY_SCALAR_attr> 3 "register_operand" "r")
                  (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                  (match_operand:SI 5 "register_operand" "r")]
                 VECTOR_INT_CMP_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vi_mask_<VANY:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
         (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                  (match_operand:VANY 2 "register_operand" "u")
                  (match_operand:<VANY:VANY_SCALAR_attr> 3 "const_int_operand" "i")
                  (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                  (match_operand:SI 5 "register_operand" "r")]
                 VECTOR_INT_CMP_VI_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VANY:MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vi_mask_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vi_mask_<VANY:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&u")
         (unspec:VMASK [(match_operand:VMASK 1 "vmask_mode_register_operand" "0")
                  (match_operand:VANY 2 "register_operand" "u")
                  (match_operand:<VANY:VANY_SCALAR_attr> 3 "const_int_operand" "i")
                  (match_operand:VMASK 4 "vmask_mode_register_operand" "w")
                  (match_operand:SI 5 "register_operand" "r")]
                 VECTOR_INT_CMP_VI_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "<vop_mask>.vi\t%0,%2,%3,%4.t");
   }
)

;; vmask instruction

(define_insn_and_split "riscv_<vop>mm_<VALL:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK                   0 "vmask_mode_register_operand" "=v")
         (unspec:VMASK [(match_operand:VMASK          1 "vmask_mode_register_operand" "v")
                        (match_operand:VMASK    2 "vmask_mode_register_operand" "v")
                        (match_operand:SI 3 "register_operand" "r")
                        (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                       VECTOR_MASK_LOGICAL))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VALL:MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>mm_<VALL:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>mm_<VALL:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK                   0 "vmask_mode_register_operand" "=v")
         (unspec:VMASK [(match_operand:VMASK          1 "vmask_mode_register_operand" "v")
                        (match_operand:VMASK    2 "vmask_mode_register_operand" "v")
                        (match_operand:SI 3 "register_operand" "r")
                        (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                       VECTOR_MASK_LOGICAL))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VALL:MODE>mode, "<vop>.mm\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>m_<VALL:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK                   0 "vmask_mode_register_operand" "=v")
         (unspec:VMASK [(match_operand:VMASK          1 "vmask_mode_register_operand" "v")
                        (match_operand:SI 2 "register_operand" "r")
                        (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                       VECTOR_MASK_PSEUDO_CAST))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VALL:MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_<vop>m_<VALL:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn "riscv_<vop>m_<VALL:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK                   0 "vmask_mode_register_operand" "=v")
         (unspec:VMASK [(match_operand:VMASK          1 "vmask_mode_register_operand" "v")
                        (match_operand:SI 2 "register_operand" "r")
                        (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                       VECTOR_MASK_PSEUDO_CAST))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VALL:MODE>mode, "<vop>.m\t%0,%1");
  }
)

(define_insn_and_split "riscv_<vop>m_<VALL:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK                   0 "vmask_mode_register_operand" "=v")
         (unspec:VMASK [(match_operand:SI 1 "register_operand" "r")
                        (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                       VECTOR_MASK_PSEUDO_SET))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VALL:MODE>mode, operands[1], operands[1]);
    emit_insn(gen_riscv_<vop>m_<VALL:mode>_internal_<VMASK:mode>(operands[0], operands[1]));
    DONE;
  }
)

(define_insn "riscv_<vop>m_<VALL:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK                   0 "vmask_mode_register_operand" "=v")
         (unspec:VMASK [(match_operand:SI 1 "register_operand" "r")
                        (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                       VECTOR_MASK_PSEUDO_SET))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VALL:MODE>mode, "<vop>.m\t%0");
  }
)

(define_insn_and_split "riscv_<vop>m_<mode>"
   [(set (match_operand:DI              0 "register_operand" "=r")
         (unspec:DI [(match_operand     1 "vmask_mode_register_operand" "v")
                     (match_operand:SI  2 "register_operand" "r")
                     (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                    VECTOR_MASK_BIT))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
     emit_insn(gen_riscv_<vop>m_<mode>_internal(operands[0], operands[1], operands[2]));
     DONE;
   }
)

(define_insn "riscv_<vop>m_<mode>_internal"
   [(set (match_operand:DI              0 "register_operand" "=r")
         (unspec:DI [(match_operand     1 "vmask_mode_register_operand" "v")
                     (match_operand:SI  2 "register_operand" "r")
                     (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                    VECTOR_MASK_BIT))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.m\t%0,%1");
   }
)

(define_insn_and_split "riscv_<vop_mask>m_mask_<mode>"
   [(set (match_operand:DI              0 "register_operand" "=r")
         (unspec:DI [(match_operand     1 "vmask_mode_register_operand" "u")
                     (match_operand     2 "vmask_mode_register_operand" "w")
                     (match_operand:SI  3 "register_operand" "r")
                     (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                    VECTOR_MASK_BIT_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop_mask>m_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                          operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>m_mask_<mode>_internal"
   [(set (match_operand:DI              0 "register_operand" "=r")
         (unspec:DI [(match_operand     1 "vmask_mode_register_operand" "u")
                     (match_operand     2 "vmask_mode_register_operand" "w")
                     (match_operand:SI  3 "register_operand" "r")
                     (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                    VECTOR_MASK_BIT_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.m\t%0,%1,%2.t");
   }
)

(define_insn_and_split "riscv_<vop>m_<VALL:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK             0 "vmask_mode_register_operand" "=v")
         (unspec:VMASK [(match_operand:VMASK    1 "vmask_mode_register_operand" "v")
                  (match_operand:SI 2 "register_operand" "r")
                  (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                  VECTOR_MASK_SET_FIRST))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VALL:MODE>mode, operands[2], operands[2]);
     emit_insn(gen_riscv_<vop>m_<VALL:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2]));
     DONE;
   }
)

(define_insn "riscv_<vop>m_<VALL:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK             0 "vmask_mode_register_operand" "=v")
         (unspec:VMASK [(match_operand:VMASK    1 "vmask_mode_register_operand" "v")
                  (match_operand:SI 2 "register_operand" "r")
                  (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                  VECTOR_MASK_SET_FIRST))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VALL:MODE>mode, "<vop>.m\t%0,%1");
   }
)

(define_insn_and_split "riscv_<vop_mask>m_mask_<VALL:mode>_<VMASK:mode>"
   [(set (match_operand:VMASK             0 "vmask_mode_register_operand" "=u")
         (unspec:VMASK [(match_operand:VMASK    1 "vmask_mode_register_operand" "u")
                  (match_operand:VMASK    2 "vmask_mode_register_operand" "w")
                  (match_operand:SI 3 "register_operand" "r")
                  (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                  VECTOR_MASK_SET_FIRST_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VALL:MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop_mask>m_mask_<VALL:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                          operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>m_mask_<VALL:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK             0 "vmask_mode_register_operand" "=u")
         (unspec:VMASK [(match_operand:VMASK    1 "vmask_mode_register_operand" "u")
                  (match_operand:VMASK    2 "vmask_mode_register_operand" "w")
                  (match_operand:SI 3 "register_operand" "r")
                  (unspec:VALL [(const_int 0)] UNSPEC_TYPE)]
                  VECTOR_MASK_SET_FIRST_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VALL:MODE>mode, "<vop_mask>.m\t%0,%1,%2.t");
   }
)

;; vector bitwise instruction

(define_insn_and_split "riscv_<vop>vv_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITWISE_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vv_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITWISE_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vx_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITWISE_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vx_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITWISE_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_vnotv_<mode>"
  [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VNOTV))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vnotv_<mode>_internal(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn "riscv_vnotv_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VNOTV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vnot.v\t%0,%1");
  }
)

(define_insn_and_split "riscv_vnotv_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VNOTV_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vnotv_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3], operands[4]));
    DONE;
  }
)

(define_insn "riscv_vnotv_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VNOTV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vnot.v\t%0,%2,%3.t");
  }
)

(define_insn_and_split "riscv_<vop>vi_<mode>"
  [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_int_operand" "i")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITWISE_VI))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vi_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vi_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_int_operand" "i")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITWISE_VI))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vi\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                       VECTOR_INT_BITWISE_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vv_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                       VECTOR_INT_BITWISE_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                       VECTOR_INT_BITWISE_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                       VECTOR_INT_BITWISE_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vi_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 3 "const_int_operand" "i")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                       VECTOR_INT_BITWISE_VI_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vi_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vi_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 3 "const_int_operand" "i")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                       VECTOR_INT_BITWISE_VI_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vi\t%0,%2,%3,%4.t");
   }
)

;;vector bit shift instruction

(define_insn_and_split "riscv_<vop>vv_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vv_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vx_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vx_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vi_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_K_operand" "K")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VI))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vi_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vi_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_K_operand" "K")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VI))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vi\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vv_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_BITSHIFT_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vi_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                         (match_operand:<VANY_SCALAR_attr> 3 "const_K_operand" "K")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
                        VECTOR_INT_BITSHIFT_VI_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vi_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vi_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                         (match_operand:<VANY_SCALAR_attr> 3 "const_K_operand" "K")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
                        VECTOR_INT_BITSHIFT_VI_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vi\t%0,%2,%3,%4.t");
   }
)

;;vector narrow shift instruction

(define_insn_and_split "riscv_<vop>vv_<mode>"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&v")
         (unspec:<VNARROW_attr> [(match_operand:VNARROW 1 "register_operand" "v")
                                 (match_operand:<VNARROW_attr> 2 "register_operand" "v")
                                 (match_operand:SI 3 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VNARROW_attr>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vv_<mode>_internal"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&v")
         (unspec:<VNARROW_attr> [(match_operand:VNARROW 1 "register_operand" "v")
                                 (match_operand:<VNARROW_attr> 2 "register_operand" "v")
                                 (match_operand:SI 3 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vx_<mode>"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&v")
         (unspec:<VNARROW_attr> [(match_operand:VNARROW 1 "register_operand" "v")
                                 (match_operand:<VANY_SCALAR_NARROW_attr> 2 "register_operand" "r")
                                 (match_operand:SI 3 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VNARROW_attr>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vx_<mode>_internal"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&v")
         (unspec:<VNARROW_attr> [(match_operand:VNARROW 1 "register_operand" "v")
                                 (match_operand:<VANY_SCALAR_NARROW_attr> 2 "register_operand" "r")
                                 (match_operand:SI 3 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vi_<mode>"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&v")
         (unspec:<VNARROW_attr> [(match_operand:VNARROW 1 "register_operand" "v")
                                 (match_operand:<VANY_SCALAR_NARROW_attr> 2 "const_K_operand" "K")
                                 (match_operand:SI 3 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VI))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VNARROW_attr>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vi_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vi_<mode>_internal"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&v")
         (unspec:<VNARROW_attr> [(match_operand:VNARROW 1 "register_operand" "v")
                                 (match_operand:<VANY_SCALAR_NARROW_attr> 2 "const_K_operand" "K")
                                 (match_operand:SI 3 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VI))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vi\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<mode>"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&u")
         (unspec:<VNARROW_attr> [(match_operand:<VNARROW_attr> 1 "register_operand" "0")
                                 (match_operand:VNARROW 2 "register_operand" "u")
                                 (match_operand:<VNARROW_attr> 3 "register_operand" "u")
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VNARROW_attr>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vv_mask_<mode>_internal"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&u")
         (unspec:<VNARROW_attr> [(match_operand:<VNARROW_attr> 1 "register_operand" "0")
                                 (match_operand:VNARROW 2 "register_operand" "u")
                                 (match_operand:<VNARROW_attr> 3 "register_operand" "u")
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<mode>"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&u")
         (unspec:<VNARROW_attr> [(match_operand:<VNARROW_attr> 1 "register_operand" "0")
                                 (match_operand:VNARROW 2 "register_operand" "u")
                                 (match_operand:<VANY_SCALAR_NARROW_attr> 3 "register_operand" "r")
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VNARROW_attr>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                                operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<mode>_internal"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&u")
         (unspec:<VNARROW_attr> [(match_operand:<VNARROW_attr> 1 "register_operand" "0")
                                 (match_operand:VNARROW 2 "register_operand" "u")
                                 (match_operand:<VANY_SCALAR_NARROW_attr> 3 "register_operand" "r")
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vi_mask_<mode>"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&u")
         (unspec:<VNARROW_attr> [(match_operand:<VNARROW_attr> 1 "register_operand" "0")
                                 (match_operand:VNARROW 2 "register_operand" "u")
                                 (match_operand:<VANY_SCALAR_NARROW_attr> 3 "const_K_operand" "K")
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VI_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VNARROW_attr>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vi_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vi_mask_<mode>_internal"
   [(set (match_operand:<VNARROW_attr>                 0 "register_operand" "=&u")
         (unspec:<VNARROW_attr> [(match_operand:<VNARROW_attr> 1 "register_operand" "0")
                                 (match_operand:VNARROW 2 "register_operand" "u")
                                 (match_operand:<VANY_SCALAR_NARROW_attr> 3 "const_K_operand" "K")
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_NARROWSHIFT_VI_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vi\t%0,%2,%3,%4.t");
   }
)

;; vector arithmetic instruction

; Binary operation

(define_insn_and_split "riscv_<vop>vv_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_ARITH_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vv_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_ARITH_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vx_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_ARITH_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vx_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_ARITH_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vi_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_M_operand" "i")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_ARITH_VI))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vi_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vi_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_M_operand" "i")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_ARITH_VI))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vi\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                        VECTOR_INT_ARITH_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vv_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                         (match_operand:VANY 3 "register_operand" "u")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
                        VECTOR_INT_ARITH_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                         (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
                        VECTOR_INT_ARITH_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                         (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
                        VECTOR_INT_ARITH_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vi_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                         (match_operand:<VANY_SCALAR_attr> 3 "const_M_operand" "i")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
                        VECTOR_INT_ARITH_VI_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vi_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vi_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                         (match_operand:<VANY_SCALAR_attr> 3 "const_M_operand" "i")
                         (match_operand 4 "vmask_mode_register_operand" "w")
                         (match_operand:SI 5 "register_operand" "r")]
                        VECTOR_INT_ARITH_VI_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vi\t%0,%2,%3,%4.t");
   }
)

; Ternary accumulation operation

(define_insn_and_split "riscv_<vop>vv_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:VANY 3 "register_operand" "0")
                       (match_operand:SI 4 "register_operand" "r")]
                      VECTOR_INT_ARITH_ACCUM_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
     emit_insn(gen_riscv_<vop>vv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
     DONE;
   }
)

(define_insn "riscv_<vop>vv_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:VANY 3 "register_operand" "0")
                       (match_operand:SI 4 "register_operand" "r")]
                      VECTOR_INT_ARITH_ACCUM_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vx_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:<VANY_SCALAR_attr> 1 "register_operand" "r")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:VANY 3 "register_operand" "0")
                       (match_operand:SI 4 "register_operand" "r")]
                      VECTOR_INT_ARITH_ACCUM_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
     emit_insn(gen_riscv_<vop>vx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
     DONE;
   }
)

(define_insn "riscv_<vop>vx_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:<VANY_SCALAR_attr> 1 "register_operand" "r")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:VANY 3 "register_operand" "0")
                       (match_operand:SI 4 "register_operand" "r")]
                      VECTOR_INT_ARITH_ACCUM_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand:VANY 4 "register_operand" "0")
                       (match_operand 5 "vmask_mode_register_operand" "w")
                       (match_operand:SI 6 "register_operand" "r")]
                      VECTOR_INT_ARITH_ACCUM_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[6], operands[6]);
     emit_insn(gen_riscv_<vop_mask>vv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5], operands[6]));
    if (REGNO(operands[0]) != REGNO(operands[1]))
      emit_insn(gen_riscv_vmergevvm_mask_<mode>(operands[0], operands[1], operands[0], operands[5], operands[6]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vv_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand:VANY 4 "register_operand" "0")
                       (match_operand 5 "vmask_mode_register_operand" "w")
                       (match_operand:SI 6 "register_operand" "r")]
                      VECTOR_INT_ARITH_ACCUM_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%5.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand:VANY 4 "register_operand" "0")
                       (match_operand 5 "vmask_mode_register_operand" "w")
                       (match_operand:SI 6 "register_operand" "r")]
                      VECTOR_INT_ARITH_ACCUM_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[6], operands[6]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5], operands[6]));
    if (REGNO(operands[0]) != REGNO(operands[1]))
      emit_insn(gen_riscv_vmergevvm_mask_<mode>(operands[0], operands[1], operands[0], operands[5], operands[6]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand:VANY 4 "register_operand" "0")
                       (match_operand 5 "vmask_mode_register_operand" "w")
                       (match_operand:SI 6 "register_operand" "r")]
                      VECTOR_INT_ARITH_ACCUM_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%5.t");
   }
)

;;vector widen arithmetic instruction

(define_insn_and_split "riscv_<vop>vv_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:VWIDEN_DSHQ 1 "register_operand" "v")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "v")
                                (match_operand:SI 3 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vv_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:VWIDEN_DSHQ 1 "register_operand" "v")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "v")
                                (match_operand:SI 3 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vx_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:VWIDEN_DSHQ 1 "register_operand" "v")
                                (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                                (match_operand:SI 3 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vx_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:VWIDEN_DSHQ 1 "register_operand" "v")
                                (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                                (match_operand:SI 3 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "u")
                                (match_operand:VWIDEN_DSHQ 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                                (match_operand:SI 5 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vv_mask_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "u")
                                (match_operand:VWIDEN_DSHQ 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                                (match_operand:SI 5 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "u")
                                 (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_WIDENARITH_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "u")
                                 (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_WIDENARITH_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop>wv_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "v")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "v")
                                (match_operand:SI 3 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENARITH_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>wv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>wv_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "v")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "v")
                                (match_operand:SI 3 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENARITH_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.wv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>wx_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "v")
                                (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                                (match_operand:SI 3 "register_operand" "r")
                                (unspec:VWIDEN_DSHQ [(const_int 0)] UNSPEC_TYPE)]
                               VECTOR_INT_WIDENWIDENARITH_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>wx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>wx_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "v")
                                (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                                (match_operand:SI 3 "register_operand" "r")
                                (unspec:VWIDEN_DSHQ [(const_int 0)] UNSPEC_TYPE)]
                               VECTOR_INT_WIDENWIDENARITH_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.wx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>wv_mask_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:<VWIDEN_attr> 2 "register_operand" "u")
                                (match_operand:VWIDEN_DSHQ 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                                (match_operand:SI 5 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENARITH_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>wv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>wv_mask_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:<VWIDEN_attr> 2 "register_operand" "u")
                                (match_operand:VWIDEN_DSHQ 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                                (match_operand:SI 5 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENARITH_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.wv\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>wx_mask_<mode>"
    [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
          (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                 (match_operand:<VWIDEN_attr> 2 "register_operand" "u")
                                 (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                                 (unspec:VWIDEN_DSHQ [(const_int 0)] UNSPEC_TYPE)
                                 (match_operand 4 "vmask_mode_register_operand" "w")
                                 (match_operand:SI 5 "register_operand" "r")]
                                VECTOR_INT_WIDENWIDENARITH_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>wx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>wx_mask_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:<VWIDEN_attr> 2 "register_operand" "u")
                                (match_operand:<VANY_SCALAR_attr> 3 "register_operand" "r")
                                (unspec:VWIDEN_DSHQ [(const_int 0)] UNSPEC_TYPE)
                                (match_operand 4 "vmask_mode_register_operand" "w")
                                (match_operand:SI 5 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENARITH_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.wx\t%0,%2,%3,%4.t");
   }
)

;;vector widen arithmetic accumulation instruction

(define_insn_and_split "riscv_<vop>vv_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:VWIDEN_DSHQ 1 "register_operand" "v")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "v")
                                (match_operand:<VWIDEN_attr> 3 "register_operand" "0")
                                (match_operand:SI 4 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_ACCUM_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
     emit_insn(gen_riscv_<vop>vv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
     DONE;
   }
)

(define_insn "riscv_<vop>vv_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:VWIDEN_DSHQ 1 "register_operand" "v")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "v")
                                (match_operand:<VWIDEN_attr> 3 "register_operand" "0")
                                (match_operand:SI 4 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_ACCUM_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop>vx_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:<VANY_SCALAR_attr> 1 "register_operand" "r")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "v")
                                (match_operand:<VWIDEN_attr> 3 "register_operand" "0")
                                (match_operand:SI 4 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_ACCUM_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
     emit_insn(gen_riscv_<vop>vx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
     DONE;
   }
)

(define_insn "riscv_<vop>vx_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:<VANY_SCALAR_attr> 1 "register_operand" "r")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "v")
                                (match_operand:<VWIDEN_attr> 3 "register_operand" "0")
                                (match_operand:SI 4 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_ACCUM_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "u")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "u")
                                (match_operand:VWIDEN_DSHQ 3 "register_operand" "u")
                                (match_operand:<VWIDEN_attr> 4 "register_operand" "0")
                                (match_operand 5 "vmask_mode_register_operand" "w")
                                (match_operand:SI 6 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_ACCUM_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[6], operands[6]);
     emit_insn(gen_riscv_<vop_mask>vv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5], operands[6]));
    if (REGNO(operands[0]) != REGNO(operands[1]))
      emit_insn(gen_riscv_vmergevvm_mask_<vwiden_attr>(operands[0], operands[1], operands[0], operands[5], operands[6]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vv_mask_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "u")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "u")
                                (match_operand:VWIDEN_DSHQ 3 "register_operand" "u")
                                (match_operand:<VWIDEN_attr> 4 "register_operand" "0")
                                (match_operand 5 "vmask_mode_register_operand" "w")
                                (match_operand:SI 6 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_ACCUM_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%5.t");
   }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "u")
                                (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                                (match_operand:VWIDEN_DSHQ 3 "register_operand" "u")
                                (match_operand:<VWIDEN_attr> 4 "register_operand" "0")
                                (match_operand 5 "vmask_mode_register_operand" "w")
                                (match_operand:SI 6 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_ACCUM_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[6], operands[6]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5], operands[6]));
    if (REGNO(operands[0]) != REGNO(operands[1]))
      emit_insn(gen_riscv_vmergevvm_mask_<vwiden_attr>(operands[0], operands[1], operands[0], operands[5], operands[6]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "u")
                                (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                                (match_operand:VWIDEN_DSHQ 3 "register_operand" "u")
                                (match_operand:<VWIDEN_attr> 4 "register_operand" "0")
                                (match_operand 5 "vmask_mode_register_operand" "w")
                                (match_operand:SI 6 "register_operand" "r")]
                               VECTOR_INT_WIDENARITH_ACCUM_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%5.t");
   }
)

;; vector reduction instruction

;; Binary operation

(define_insn_and_split "riscv_<vop>vs_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_RED_VS))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vs_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vs_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:VANY 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_RED_VS))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vs\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vs_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_RED_VS_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vs_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vs_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand:VANY 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_RED_VS_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vs\t%0,%2,%3,%4.t");
   }
)

; vector widen reduction instruction

(define_insn_and_split "riscv_<vop>vs_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:VWIDEN_DSHQ 1 "register_operand" "v")
                                (match_operand:<VWIDEN_attr> 2 "register_operand" "v")
                                (match_operand:SI 3 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENRED_VS))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vs_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vs_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&v")
         (unspec:<VWIDEN_attr> [(match_operand:VWIDEN_DSHQ 1 "register_operand" "v")
                                (match_operand:<VWIDEN_attr> 2 "register_operand" "v")
                                (match_operand:SI 3 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENRED_VS))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vs\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vs_mask_<mode>"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "u")
                                (match_operand:<VWIDEN_attr> 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                                (match_operand:SI 5 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENRED_VS_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vs_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vs_mask_<mode>_internal"
   [(set (match_operand:<VWIDEN_attr>                 0 "register_operand" "=&u")
         (unspec:<VWIDEN_attr> [(match_operand:<VWIDEN_attr> 1 "register_operand" "0")
                                (match_operand:VWIDEN_DSHQ 2 "register_operand" "u")
                                (match_operand:<VWIDEN_attr> 3 "register_operand" "u")
                                (match_operand 4 "vmask_mode_register_operand" "w")
                                (match_operand:SI 5 "register_operand" "r")]
                               VECTOR_INT_WIDENWIDENRED_VS_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vs\t%0,%2,%3,%4.t");
   }
)

;; vector slide instruction and gather instruction

(define_insn_and_split "riscv_<vop>vv_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=&v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_GATHER_VV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vv_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vv_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=&v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand 2 "register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_GATHER_VV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vv\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vv_mask_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=&u")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "0")
                       (match_operand:VALL 2 "register_operand" "u")
                       (match_operand 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_GATHER_VV_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vv_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vv_mask_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=&u")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "0")
                       (match_operand:VALL 2 "register_operand" "u")
                       (match_operand 3 "register_operand" "u")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_GATHER_VV_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vv\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop>vx_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=&v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand 2 "register_operand" "r")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_SLIDEGATHER_VX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vx_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vx_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=&v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand 2 "register_operand" "r")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_SLIDEGATHER_VX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vx\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vx_mask_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=&u")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "0")
                       (match_operand:VALL 2 "register_operand" "u")
                       (match_operand 3 "register_operand" "r")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_SLIDEGATHER_VX_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vx_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vx_mask_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=&u")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "0")
                       (match_operand:VALL 2 "register_operand" "u")
                       (match_operand 3 "register_operand" "r")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_SLIDEGATHER_VX_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vx\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop>vi_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=&v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand 2 "const_K_operand" "K")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_SLIDE_VI))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vi_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vi_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=&v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand 2 "const_K_operand" "K")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_SLIDE_VI))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vi\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vi_mask_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=&u")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "0")
                       (match_operand:VALL 2 "register_operand" "u")
                       (match_operand 3 "const_K_operand" "K")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_SLIDE_VI_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vi_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vi_mask_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=&u")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "0")
                       (match_operand:VALL 2 "register_operand" "u")
                       (match_operand 3 "const_K_operand" "K")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_SLIDE_VI_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vi\t%0,%2,%3,%4.t");
   }
)

(define_insn_and_split "riscv_<vop>vi_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=&v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand 2 "const_K_operand" "i")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_GATHER_VI))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_<vop>vi_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3]));
     DONE;
   }
)

(define_insn "riscv_<vop>vi_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=&v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand 2 "const_K_operand" "i")
                       (match_operand:SI 3 "register_operand" "r")]
                      VECTOR_INT_GATHER_VI))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop>.vi\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_<vop_mask>vi_mask_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=&u")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "0")
                       (match_operand:VALL 2 "register_operand" "u")
                       (match_operand 3 "const_K_operand" "i")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_GATHER_VI_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[5], operands[5]);
     emit_insn(gen_riscv_<vop_mask>vi_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                           operands[3], operands[4], operands[5]));
     DONE;
   }
)

(define_insn "riscv_<vop_mask>vi_mask_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=&u")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "0")
                       (match_operand:VALL 2 "register_operand" "u")
                       (match_operand 3 "const_K_operand" "i")
                       (match_operand 4 "vmask_mode_register_operand" "w")
                       (match_operand:SI 5 "register_operand" "r")]
                      VECTOR_INT_GATHER_VI_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vi\t%0,%2,%3,%4.t");
   }
)

;; vector compress instruction

(define_insn_and_split "riscv_vcompressvm_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=&v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand 2 "vmask_mode_register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      UNSPEC_VCOMPRESS))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_vcompressvm_<mode>_internal(operands[0], operands[1], operands[2],
                                                     operands[3]));
     DONE;
   }
)

(define_insn "riscv_vcompressvm_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=&v")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand 2 "vmask_mode_register_operand" "v")
                       (match_operand:SI 3 "register_operand" "r")]
                      UNSPEC_VCOMPRESS))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vcompress.vm\t%0,%1,%2");
   }
)

;; vector iota and id instruction

(define_insn_and_split "riscv_viotam_<mode>"
    [(set (match_operand:VANY                 0 "register_operand" "=&v")
          (unspec:VANY [(match_operand 1 "vmask_mode_register_operand" "v")
                        (match_operand:SI 2 "register_operand" "r")]
                       UNSPEC_VIOTA))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
     emit_insn(gen_riscv_viotam_<mode>_internal(operands[0], operands[1], operands[2]));
     DONE;
   }
)

(define_insn "riscv_viotam_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=&v")
         (unspec:VANY [(match_operand 1 "vmask_mode_register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VIOTA))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "viota.m\t%0,%1");
   }
)

(define_insn_and_split "riscv_viotam_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=&u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand 2 "vmask_mode_register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VIOTA_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
     emit_insn(gen_riscv_viotam_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                     operands[3], operands[4]));
     DONE;
   }
)

(define_insn "riscv_viotam_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=&u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand 2 "vmask_mode_register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VIOTA_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "viota.m\t%0,%2,%3.t");
   }
)

(define_insn_and_split "riscv_vidv_<mode>"
    [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:SI 1 "register_operand" "r")]
                      UNSPEC_VID))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[1], operands[1]);
     emit_insn(gen_riscv_vidv_<mode>_internal(operands[0], operands[1]));
     DONE;
   }
)

(define_insn "riscv_vidv_<mode>_internal"
    [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:SI 1 "register_operand" "r")]
                      UNSPEC_VID))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vid.v\t%0");
   }
)

(define_insn_and_split "riscv_vidv_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand 2 "vmask_mode_register_operand" "w")
                       (match_operand:SI 3 "register_operand" "r")]
                      UNSPEC_VID_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_vidv_mask_<mode>_internal(operands[0], operands[1], operands[2], operands[3]));
     DONE;
   }
)

(define_insn "riscv_vidv_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "0")
                       (match_operand 2 "vmask_mode_register_operand" "w")
                       (match_operand:SI 3 "register_operand" "r")]
                      UNSPEC_VID_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vid.v\t%0,%2.t");
   }
)

;; vector vmerge(vmv) instruction

(define_insn_and_split "riscv_vmvvv_<mode>"
   [(set (match_operand:VALL                 0 "register_operand" "=v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VMVVV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
     emit_insn(gen_riscv_vmvvv_<mode>_internal(operands[0], operands[1], operands[2]));
     DONE;
   }
)

(define_insn "riscv_vmvvv_<mode>_internal"
   [(set (match_operand:VALL                 0 "register_operand" "=v")
         (unspec:VALL [(match_operand:VALL 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VMVVV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vmv.v.v\t%0,%1");
   }
)

(define_insn_and_split "riscv_vmergevvm_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VMERGEVVM_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
     emit_insn(gen_riscv_vmergevvm_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                     operands[3], operands[4]));
     DONE;
   }
)

(define_insn "riscv_vmergevvm_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VMERGEVVM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vmerge.vvm\t%0,%1,%2,%3");
   }
)

(define_insn_and_split "riscv_vmvvx_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:<VANY_SCALAR_attr> 1 "register_operand" "r")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VMVVX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
     emit_insn(gen_riscv_vmvvx_<mode>_internal(operands[0], operands[1], operands[2]));
     DONE;
   }
)

(define_insn "riscv_vmvvx_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:<VANY_SCALAR_attr> 1 "register_operand" "r")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VMVVX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vmv.v.x\t%0,%1");
   }
)

(define_insn_and_split "riscv_vmergevxm_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VMERGEVXM_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
     emit_insn(gen_riscv_vmergevxm_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                        operands[3], operands[4]));
     DONE;
   }
)

(define_insn "riscv_vmergevxm_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VMERGEVXM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vmerge.vxm\t%0,%1,%2,%3");
   }
)

(define_insn_and_split "riscv_vmvvi_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:<VANY_SCALAR_attr> 1 "const_M_operand" "i")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VMVVI))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
     emit_insn(gen_riscv_vmvvi_<mode>_internal(operands[0], operands[1], operands[2]));
     DONE;
   }
)

(define_insn "riscv_vmvvi_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:<VANY_SCALAR_attr> 1 "const_M_operand" "i")
                       (match_operand:SI 2 "register_operand" "r")]
                      UNSPEC_VMVVI))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vmv.v.i\t%0,%1");
   }
)

(define_insn_and_split "riscv_vmergevim_mask_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_M_operand" "i")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VMERGEVIM_MASK))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
     emit_insn(gen_riscv_vmergevim_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                        operands[3], operands[4]));
     DONE;
   }
)

(define_insn "riscv_vmergevim_mask_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_M_operand" "i")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
                      UNSPEC_VMERGEVIM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vmerge.vim\t%0,%1,%2,%3");
   }
)

;; vector permutation instruction

(define_insn_and_split "riscv_vextxv_<mode>"
   [(set (match_operand:<VANY_SCALAR_attr>                 0 "register_operand" "=r")
         (unspec:<VANY_SCALAR_attr> [(match_operand:VANY 1 "register_operand" "v")
                                     (match_operand:SI 2 "register_operand" "r")
                                     (match_operand:SI 3 "register_operand" "r")]
                                    UNSPEC_VEXTXV))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[3], operands[3]);
     emit_insn(gen_riscv_vextxv_<mode>_internal(operands[0], operands[1],operands[2],
                                                operands[3]));
     DONE;
   }
)

(define_insn "riscv_vextxv_<mode>_internal"
   [(set (match_operand:<VANY_SCALAR_attr>                 0 "register_operand" "=r")
         (unspec:<VANY_SCALAR_attr> [(match_operand:VANY 1 "register_operand" "v")
                                     (match_operand:SI 2 "register_operand" "r")
                                     (match_operand:SI 3 "register_operand" "r")]
                                    UNSPEC_VEXTXV))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vext.x.v\t%0,%1,%2");
   }
)

(define_insn_and_split "riscv_vmvsx_<mode>"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:<VANY_SCALAR_attr> 1 "register_operand" "r")
                       (match_operand:SI 2 "register_operand" "r")]
                       UNSPEC_VMVSX))]
   "TARGET_VECTOR"
   "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
     emit_insn(gen_riscv_vmvsx_<mode>_internal(operands[0], operands[1], operands[2]));
     DONE;
   }
)

(define_insn "riscv_vmvsx_<mode>_internal"
   [(set (match_operand:VANY                 0 "register_operand" "=v")
         (unspec:VANY [(match_operand:<VANY_SCALAR_attr> 1 "register_operand" "r")
                       (match_operand:SI 2 "register_operand" "r")]
                       UNSPEC_VMVSX))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vmv.s.x\t%0,%1");
   }
)

(define_insn_and_split "riscv_vmvxs_<mode>"
   [(set (match_operand:<VANY_SCALAR_attr> 0 "register_operand" "=r")
         (unspec:<VANY_SCALAR_attr> [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
                       UNSPEC_VMVXS))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[2], operands[2]);
    emit_insn(gen_riscv_vmvxs_<mode>_internal(operands[0], operands[1], operands[2]));
    DONE;
  }
)

(define_insn "riscv_vmvxs_<mode>_internal"
   [(set (match_operand:<VANY_SCALAR_attr> 0 "register_operand" "=r")
         (unspec:<VANY_SCALAR_attr> [(match_operand:VANY 1 "register_operand" "v")
                       (match_operand:SI 2 "register_operand" "r")]
                       UNSPEC_VMVXS))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
    return riscv_output_vector_insn(<MODE>mode, "vmv.x.s\t%0,%1");
  }
)

;; carry and borrow

(define_insn_and_split "riscv_<vop_mask>vvm_mask_<mode>"
  [(set (match_operand:VANY 0 "register_operand" "=u")
        (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                      (match_operand:VANY 2 "register_operand" "u")
                      (match_operand 3 "vmask_mode_register_operand" "w")
                      (match_operand:SI 4 "register_operand" "r")]
         VECTOR_CARRYUSE_VVM_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vop_mask>vvm_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
    DONE;
   }
)

(define_insn "riscv_<vop_mask>vvm_mask_<mode>_internal"
   [(set (match_operand:VANY 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:VANY 2 "register_operand" "u")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
          VECTOR_CARRYUSE_VVM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vvm\t%0,%1,%2,%3");
   }
)

(define_insn_and_split "riscv_<vop_mask>vxm_mask_<mode>"
  [(set (match_operand:VANY 0 "register_operand" "=u")
        (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                      (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                      (match_operand 3 "vmask_mode_register_operand" "w")
                      (match_operand:SI 4 "register_operand" "r")]
         VECTOR_CARRYUSE_VXM_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vop_mask>vxm_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
    DONE;
   }
)

(define_insn "riscv_<vop_mask>vxm_mask_<mode>_internal"
   [(set (match_operand:VANY 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 2 "register_operand" "r")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
          VECTOR_CARRYUSE_VXM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "<vop_mask>.vxm\t%0,%1,%2,%3");
   }
)

(define_insn_and_split "riscv_vadcvim_mask_<mode>"
  [(set (match_operand:VANY 0 "register_operand" "=u")
        (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                      (match_operand:<VANY_SCALAR_attr> 2 "const_M_operand" "i")
                      (match_operand 3 "vmask_mode_register_operand" "w")
                      (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VADCVIM_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vadcvim_mask_<mode>_internal(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
    DONE;
   }
)

(define_insn "riscv_vadcvim_mask_<mode>_internal"
   [(set (match_operand:VANY 0 "register_operand" "=u")
         (unspec:VANY [(match_operand:VANY 1 "register_operand" "u")
                       (match_operand:<VANY_SCALAR_attr> 2 "const_M_operand" "i")
                       (match_operand 3 "vmask_mode_register_operand" "w")
                       (match_operand:SI 4 "register_operand" "r")]
          UNSPEC_VADCVIM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<MODE>mode, "vadc.vim\t%0,%1,%2,%3");
   }
)

(define_insn_and_split "riscv_<vop_mask>vvm_mask_<VANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VANY 1 "register_operand" "u")
                 (match_operand:VANY 2 "register_operand" "u")
                 (match_operand:VMASK 3 "vmask_mode_register_operand" "w")
                 (match_operand:SI 4 "register_operand" "r")]
         VECTOR_CARRYOUT_VVM_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VANY:MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vop_mask>vvm_mask_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
    DONE;
   }
)

(define_insn "riscv_<vop_mask>vvm_mask_<VANY:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
         (unspec:VMASK [(match_operand:VANY 1 "register_operand" "u")
                  (match_operand:VANY 2 "register_operand" "u")
                  (match_operand:VMASK 3 "vmask_mode_register_operand" "w")
                  (match_operand:SI 4 "register_operand" "r")]
          VECTOR_CARRYOUT_VVM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "<vop_mask>.vvm\t%0,%1,%2,%3");
   }
)

(define_insn_and_split "riscv_<vop_mask>vxm_mask_<VANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VANY 1 "register_operand" "u")
                 (match_operand:<VANY:VANY_SCALAR_attr> 2 "register_operand" "r")
                 (match_operand:VMASK 3 "vmask_mode_register_operand" "w")
                 (match_operand:SI 4 "register_operand" "r")]
         VECTOR_CARRYOUT_VXM_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VANY:MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_<vop_mask>vxm_mask_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
    DONE;
   }
)

(define_insn "riscv_<vop_mask>vxm_mask_<VANY:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
         (unspec:VMASK [(match_operand:VANY 1 "register_operand" "u")
                  (match_operand:<VANY:VANY_SCALAR_attr> 2 "register_operand" "r")
                  (match_operand:VMASK 3 "vmask_mode_register_operand" "w")
                  (match_operand:SI 4 "register_operand" "r")]
          VECTOR_CARRYOUT_VXM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "<vop_mask>.vxm\t%0,%1,%2,%3");
   }
)

(define_insn_and_split "riscv_vmadcvim_mask_<VANY:mode>_<VMASK:mode>"
  [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
        (unspec:VMASK [(match_operand:VANY 1 "register_operand" "u")
                 (match_operand:<VANY:VANY_SCALAR_attr> 2 "const_M_operand" "i")
                 (match_operand:VMASK 3 "vmask_mode_register_operand" "w")
                 (match_operand:SI 4 "register_operand" "r")]
         UNSPEC_VMADCVIM_MASK))]
  "TARGET_VECTOR"
  "#"
  "&& TARGET_VECTOR_VSPLIT"
  [(clobber (const_int 0))]
  {
    riscv_emit_vsetvli(<VANY:MODE>mode, operands[4], operands[4]);
    emit_insn(gen_riscv_vmadcvim_mask_<VANY:mode>_internal_<VMASK:mode>(operands[0], operands[1], operands[2],
                                                 operands[3], operands[4]));
    DONE;
   }
)

(define_insn "riscv_vmadcvim_mask_<VANY:mode>_internal_<VMASK:mode>"
   [(set (match_operand:VMASK 0 "vmask_mode_register_operand" "=&v")
         (unspec:VMASK [(match_operand:VANY 1 "register_operand" "u")
                  (match_operand:<VANY:VANY_SCALAR_attr> 2 "const_M_operand" "i")
                  (match_operand:VMASK 3 "vmask_mode_register_operand" "w")
                  (match_operand:SI 4 "register_operand" "r")]
          UNSPEC_VMADCVIM_MASK))
   (clobber (const_int 0))]
  "TARGET_VECTOR"
  {
     return riscv_output_vector_insn(<VANY:MODE>mode, "vmadc.vim\t%0,%1,%2,%3");
   }
)
