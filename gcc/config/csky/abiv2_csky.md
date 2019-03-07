
;; ------------------------------------------------------------------------
;; Constant
;; ------------------------------------------------------------------------
(define_constants
  [(PIC_SYMBOL_GOTPC       14)
   (PIC_SYMBOL_GOTPC_GRS   15)
   (PIC_SYMBOL_GOTOFF      1)
   (PIC_SYMBOL_GOT         2)
   (PIC_SYMBOL_PLT         3)
   (PIC_SYMBOL_BSR         4)
   (PIC_SYMBOL_GRS         5)

   (FLAG_PUSH              8)
   (FLAG_POP               9)
   (FLAG_EPILOGUE          10)

   (UNSPEC_TLS_BASE        19)
   (UNSPEC_TLS             20)
   (UNSPEC_TLS_LABEL       21)
   (VUNSPEC_EH_RETURN      22)
   ; this unspec is used to prevent the deletion of
   ; instructions setting registers for EH handling
   ; and stack frame generation.  Operand 0 is the
   ; register to "use"
   ; As USE insns are not meaningful after reload,
   (UNSPEC_REGISTER_USE    23)
   (UNSPEC_CSKY_CASESI     24)
   ; Condition code pseudo register
   (CSKY_CC_REGNUM         33)
   (CSKY_LR_REGNUM         15)
   (CSKY_GB_REGNUM         28)
   (CSKY_FIRST_RET_REG      0)
])

(define_constants
  [(VUNSPEC_ALIGN          0)
   (VUNSPEC_POOL_LABEL     1)
   (VUNSPEC_POOL_4         2)
   (VUNSPEC_POOL_8         3)
   (VUNSPEC_SYMBOL_REF     4)
   (VUNSPEC_BLOCKAGE       5)
])

;; Supported TLS relocations
(define_constants
  [(TLS_GD32               0)
   (TLS_LDM32              1)
   (TLS_LDO32              2)
   (TLS_IE32               3)
   (TLS_LE32               4)]
)

(define_c_enum "unspec" [
  UNSPEC_PUSHPOP_MULT   ;   push or pop multiple' operation:
                        ;   operand 0 is the first register,
                        ;   subsequent registers are in parallel (use ...)
                        ;   expressions.
  UNSPEC_DOLOOP         ;   Used to emit bloop instruction.
  UNSPEC_PADDH_S
  UNSPEC_PADDH_U
  UNSPEC_PSUBH_S
  UNSPEC_PSUBH_U
  UNSPEC_PASX
  UNSPEC_PSAX
  UNSPEC_PASXH_S
  UNSPEC_PASXH_U
  UNSPEC_PSAXH_S
  UNSPEC_PSAXH_U
  UNSPEC_SEL
  UNSPEC_PKGLL
  UNSPEC_PKGHH
  UNSPEC_NARL
  UNSPEC_NARH
  UNSPEC_NARLX
  UNSPEC_NARHX
  UNSPEC_DEXT
  UNSPEC_CLIPU
  UNSPEC_CLIPS
  UNSPEC_PCLIPU
  UNSPEC_PCLIPS
  UNSPEC_PKG
  UNSPEC_PEXTXU8
  UNSPEC_PEXTXS8
  UNSPEC_DUP8
  UNSPEC_DUP16
  UNSPEC_PMULXS
  UNSPEC_PMULXU
  UNSPEC_PRMULS16
  UNSPEC_PRMULXS16
  UNSPEC_PRMULS16H
  UNSPEC_PRMULS16RH
  UNSPEC_PRMULXS16H
  UNSPEC_PRMULXS16RH
  UNSPEC_MULCA
  UNSPEC_MULCAX
  UNSPEC_MULCS
  UNSPEC_MULCSR
  UNSPEC_MULCSX
  UNSPEC_MULACA
  UNSPEC_MULACAX
  UNSPEC_MULACS
  UNSPEC_MULACSR
  UNSPEC_MULACSX
  UNSPEC_MULSCA
  UNSPEC_MULSCAX
  UNSPEC_MULACAE
  UNSPEC_MULACAXE
  UNSPEC_MULACSE
  UNSPEC_MULACSRE
  UNSPEC_MULACSXE
  UNSPEC_MULSCAE
  UNSPEC_MULSCAXE
  UNSPEC_PSABSA
  UNSPEC_PSABSASA
  UNSPEC_VADDEU
  UNSPEC_VADDES
  UNSPEC_VADDXU
  UNSPEC_VADDXS
  UNSPEC_VADDXSLU
  UNSPEC_VADDXSLS
  UNSPEC_VADDHU
  UNSPEC_VADDHS
  UNSPEC_VADDHRU
  UNSPEC_VADDHRS
  UNSPEC_VANDN
  UNSPEC_VBPERM
  UNSPEC_VBPERMZ
  UNSPEC_VCADDU
  UNSPEC_VCADDS
  UNSPEC_VCMAXU
  UNSPEC_VCMAXS
  UNSPEC_VCMINU
  UNSPEC_VCMINS
  UNSPEC_VCMPHSU
  UNSPEC_VCMPHSS
  UNSPEC_VCMPHSZU
  UNSPEC_VCMPHSZS
  UNSPEC_VCMPLTU
  UNSPEC_VCMPLTS
  UNSPEC_VCMPLTZU
  UNSPEC_VCMPLTZS
  UNSPEC_VCMPNEU
  UNSPEC_VCMPNES
  UNSPEC_VCMPNEZU
  UNSPEC_VCMPNEZS
  UNSPEC_VDCH
  UNSPEC_VDCL
  UNSPEC_VICH
  UNSPEC_VICL
  UNSPEC_VMULEU
  UNSPEC_VMULES
  UNSPEC_VMULAEU
  UNSPEC_VMULAES
  UNSPEC_VMULSEU
  UNSPEC_VMULSES
  UNSPEC_VNOR
  UNSPEC_VSABSEU
  UNSPEC_VSABSES
  UNSPEC_VSABSU
  UNSPEC_VSABSS
  UNSPEC_VSABSAEU
  UNSPEC_VSABSAES
  UNSPEC_VSABSAU
  UNSPEC_VSABSAS
  UNSPEC_VSHLU
  UNSPEC_VSHLS
  UNSPEC_VSHRU
  UNSPEC_VSHRS
  UNSPEC_VSHRRU
  UNSPEC_VSHRRS
  UNSPEC_VSUBEU
  UNSPEC_VSUBES
  UNSPEC_VSUBHU
  UNSPEC_VSUBHS
  UNSPEC_VSUBHRU
  UNSPEC_VSUBHRS
  UNSPEC_VSUBXU
  UNSPEC_VSUBXS
  UNSPEC_VTRCH
  UNSPEC_VTRCL
  UNSPEC_VTST
  UNSPEC_VCADDEU
  UNSPEC_VCADDES
  UNSPEC_VCLSS
  UNSPEC_VCLZ
  UNSPEC_VCNT1
  UNSPEC_VMOVEU
  UNSPEC_VMOVES
  UNSPEC_VMOVHU
  UNSPEC_VMOVHS
  UNSPEC_VMOVLU
  UNSPEC_VMOVLS
  UNSPEC_VMOVRHU
  UNSPEC_VMOVRHS
  UNSPEC_VMOVSLU
  UNSPEC_VMOVSLS
  UNSPEC_VREV
  UNSPEC_VSTOUSLS
  UNSPEC_VDUP
  UNSPEC_VLDD
  UNSPEC_VLDQ
  UNSPEC_VSTD
  UNSPEC_VSTQ
  UNSPEC_VLDRD
  UNSPEC_VLDRQ
  UNSPEC_VSTRD
  UNSPEC_VSTRQ
  UNSPEC_VINS
  UNSPEC_VMFVRU
  UNSPEC_VMFVRS
  UNSPEC_VMTVRU
  UNSPEC_VSHLIU
  UNSPEC_VSHLIS
  UNSPEC_VSHLISU
  UNSPEC_VSHLISS
  UNSPEC_VSHRIU
  UNSPEC_VSHRIS
  UNSPEC_VSHRIRU
  UNSPEC_VSHRIRS
  UNSPEC_PASRIR
  UNSPEC_PASRR
  UNSPEC_PLSRIR
  UNSPEC_PLSRR
  UNSPEC_PLSLISS
  UNSPEC_PLSLSS
  UNSPEC_PLSLIUS
  UNSPEC_PLSLUS
  ]
)

;; ------------------------------------------------------------------------
;; Attributes
;; ------------------------------------------------------------------------

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
(define_attr "type" "alu,load,store,cmp,branch,cbranch,addsub,alu_ix,branch_jmp,call_jsr,call"
    (const_string "alu"))

; Used to distinguish between the constraints of the instruction
(define_attr "isa" "def, e1, e2, 2e3, 3e3r1, 3e7, 7e10"
  (const_string "def"))

(define_attr "enabled" "no,yes"
  (cond [
    (eq_attr "isa" "e1") (cond [(match_test "CSKY_ISA_FEATURE(E1)") (const_string "yes")] (const_string "no"))
    (eq_attr "isa" "e2") (cond [(match_test "CSKY_ISA_FEATURE(E2)") (const_string "yes")] (const_string "no"))
    (eq_attr "isa" "2e3") (cond [(match_test "CSKY_ISA_FEATURE(2E3)") (const_string "yes")] (const_string "no"))
    (eq_attr "isa" "3e3r1") (cond [(match_test "CSKY_ISA_FEATURE(3E3r1)") (const_string "yes")] (const_string "no"))
    (eq_attr "isa" "3e7") (cond [(match_test "CSKY_ISA_FEATURE(3E7)") (const_string "yes")] (const_string "no"))
    (eq_attr "isa" "7e10") (cond [(match_test "CSKY_ISA_FEATURE(7E10)") (const_string "yes")] (const_string "no"))
  ]
    (const_string "yes")))

;; The number of machine instructions this pattern expands to.
;; Used for conditional execution.
(define_attr "ce_count" "" (const_int 1))

; Predicable means that the insn can be conditionally executed based on
; an automatically added predicate (additional patterns are generated by
; gen...).  We default to 'no' because not all CSKY patterns do.
(define_attr "predicable" "no,yes" (const_string "no"))

;; ------------------------------------------------------------------------
;; Include files
;; ------------------------------------------------------------------------
(include "abiv2_csky_constraints.md")
(include "abiv2_csky_predicates.md")
(include "abiv2_csky_insn_fpu.md")
(include "abiv2_csky_pipeline_ck802.md")
(include "abiv2_csky_pipeline_ck803.md")
(include "abiv2_csky_pipeline_ck810.md")
(include "abiv2_csky_insn_vdsp.md")
(include "abiv2_csky_fixed.md")

;; ------------------------------------------------------------------------
;; Conditional Execution
;; ------------------------------------------------------------------------

(define_cond_exec
  [(match_operator 0 "ordered_comparison_operator"
    [(match_operand 1 "cc_register" "")
     (match_operand:SI 2 "const_int_operand" "")])]
  "CSKY_ISA_FEATURE(2E3)"
  ""
)

;; ------------------------------------------------------------------------
;; Mov insns
;; ------------------------------------------------------------------------

(define_mode_iterator QHI [QI HI])

(define_expand "movsi"
  [(set (match_operand:SI 0 "general_operand" "")
        (match_operand:SI 1 "general_operand" ""))]
  ""
  "
  {
    if (can_create_pseudo_p () && MEM_P (operands[0]))
      {
        operands[1] = force_reg (SImode, operands[1]);
        emit_insn(gen_rtx_SET (operands[0], operands[1]));
        DONE;
      }

    /* Recognize the case where operand[1] is a reference to thread-local
       data and load its address to a register.  */
    if (csky_tls_referenced_p (operands[1]))
      {
        rtx tmp = operands[1];
        rtx addend = NULL;

        if (GET_CODE (tmp) == CONST && GET_CODE (XEXP (tmp, 0)) == PLUS)
          {
            addend = XEXP (XEXP (tmp, 0), 1);
            tmp = XEXP (XEXP (tmp, 0), 0);
          }

        gcc_assert (GET_CODE (tmp) == SYMBOL_REF);
        gcc_assert (SYMBOL_REF_TLS_MODEL (tmp) != 0);

        tmp = legitimize_tls_address (tmp, !can_create_pseudo_p () ? operands[0] : 0);
        if (addend)
          {
            tmp = gen_rtx_PLUS (SImode, tmp, addend);
            tmp = force_operand (tmp, operands[0]);
          }
        operands[1] = tmp;
      }
    else if (flag_pic
             && (CONSTANT_P (operands[1])
                 || symbol_mentioned_p (operands[1])
                 || label_mentioned_p (operands[1])))
      {
        operands[1] = legitimize_pic_address (operands[1],
                                              (!can_create_pseudo_p () ? operands[0] : 0),
                                              1);
      }
  }"
)

(define_insn "*cskyv2_movsi"
  [(set (match_operand:SI 0 "nonimmediate_operand"  "=r,r,r, r, r, r, r,r,m,*y,*r,*v,*r,*v,*v,*Ds")
        (match_operand:SI 1 "general_operand"       "r, I,Un,Uc,Uo,mi,F,c,r,*r,*y,*r,*v,*v,*Ds,*v"))]
  "CSKY_ISA_FEATURE(E2)"
  "* return output_csky_move (insn, operands, SImode);"
  [(set_attr "length" "4,4,4,4,8,4,4,4,4,4,4,4,4,4,4,4")
   (set_attr "type" "alu,alu,alu,alu,alu,load,alu,alu,store,alu,alu,alu,alu,alu,load,store")]
)

(define_insn "*ck801_movsi"
 [(set (match_operand:SI 0 "nonimmediate_operand"   "=r,a, a,r ,r,r,m")
       (match_operand:SI 1 "general_operand"        "r, Up,T,mi,F,c,r"))]
 "CSKY_ISA_FEATURE(E1)"
 "* return output_ck801_move (insn, operands, SImode);"
 [(set_attr "length" "2,2,2,4,4,2,4")
  (set_attr "type" "alu,alu,alu,store,alu,alu,store")]
)

;;Split constant assignment instruction, if possible.
(define_split
  [(set (match_operand:SI 0 "register_operand" "")
        (match_operand:SI 1 "const_int_operand" ""))]
  "csky_can_split_constant (SET, NULL_RTX, INTVAL (operands[1]))"
  [(clobber (const_int 0))]
  "
    csky_split_constant (SET, SImode, NULL_RTX,
                         INTVAL (operands[1]), operands[0], NULL_RTX, 0);
    DONE;
  "
)

(define_split
  [(set (match_operand:DI 0 "register_operand" "")
  (match_operand:DI 1 "const_double_operand" ""))]
  "TARGET_CONSTANT_POOL && reload_completed"
  [(set (match_dup 0) (match_dup 1))
   (set (match_dup 2) (match_dup 3))]
  "
  operands[2] = gen_highpart (SImode, operands[0]);
  operands[3] = gen_highpart_mode (SImode, GET_MODE (operands[0]),
           operands[1]);
  operands[0] = gen_lowpart (SImode, operands[0]);
  operands[1] = gen_lowpart (SImode, operands[1]);
  "
)

;;Convert negative assignments to zero minus positive numbers.
(define_split
  [(set (match_operand:SI 0 "register_operand" "")
        (match_operand:SI 1 "const_int_operand" ""))]
    "satisfies_constraint_T (operands[1])"
    [(set (match_dup 0) (match_dup 2))
     (set (match_dup 0) (plus:SI (match_dup 0) (match_dup 1)))]
    "
      operands[2] = const0_rtx;
    "
)

;;Convert const assignments to small number of assignments and left shift.
(define_split
  [(set (match_operand:SI 0 "register_operand" "")
        (match_operand:SI 1 "const_int_operand" ""))]
  "satisfies_constraint_Ux (operands[1]) && (optimize_size || !CSKY_ISA_FEATURE(E2))"
  [(set (match_dup 0) (match_dup 1))
   (set (match_dup 0) (ashift:SI (match_dup 0) (match_dup 2)))]
  "
  {
    unsigned HOST_WIDE_INT val = INTVAL (operands[1]) &0xffffffffu;
    unsigned HOST_WIDE_INT mask = 0xff;
    int i;

    for (i = 0; i< 25; i++)
        if((val & (mask << i)) == val)
            break;
    if (i == 0)
        FAIL;
    operands[1] = GEN_INT (val >>i );
    operands[2] = GEN_INT (i);
  }"
)


(define_expand "movhi"
  [(set (match_operand:HI 0 "general_operand" "")
        (match_operand:HI 1 "general_operand"  ""))]
  ""
  "
  {
    if (GET_CODE (operands[0]) == MEM)
        operands[1] = force_reg (HImode, operands[1]);
    else if (CONSTANT_P (operands[1])
             && (GET_CODE (operands[1]) != CONST_INT
                 || (! CSKY_CONST_OK_FOR_I (INTVAL (operands[1]))
                     && ! CSKY_CONST_OK_FOR_Ub (INTVAL (operands[1]))
                     && ! CSKY_CONST_OK_FOR_Uc (INTVAL (operands[1]))))
             && ! reload_completed && ! reload_in_progress)
    {
        rtx reg = gen_reg_rtx (SImode);
        emit_insn (gen_movsi (reg, operands[1]));
        operands[1] = gen_lowpart (HImode, reg);
    }
  }"
)

(define_insn "*cskyv2_movhi"
  [(set (match_operand:HI 0 "nonimmediate_operand"  "=r,r,r,r,m,*y,*r,*v,*r")
        (match_operand:HI 1 "general_operand"       "r, i,c,m,r,*r,*y,*r,*v"))]
  "CSKY_ISA_FEATURE(E2)"
  "* return output_csky_move (insn, operands, HImode);"
  [(set_attr "length" "4,8,4,4,4,4,4,4,4")
   (set_attr "type" "alu,alu,alu,load,store,alu,alu,alu,alu")]
)

(define_insn "*ck801_movhi"
  [(set (match_operand:HI 0 "nonimmediate_operand"  "=r,a, a,r,r,r,m")
        (match_operand:HI 1 "general_operand"       "r, Up,T,i,m,c,r"))]
  "CSKY_ISA_FEATURE(E1)"
  "* return output_ck801_move (insn, operands, HImode);"
  [(set_attr "length" "2,2,2,4,4,2,4")
   (set_attr "type" "alu,alu,alu,alu,store,alu,store")]
)


(define_expand "movqi"
  [(set (match_operand:QI 0 "general_operand" "")
        (match_operand:QI 1 "general_operand"  ""))]
  ""
  "
  {
    if (can_create_pseudo_p ())
      {
        if (GET_CODE (operands[0]) == MEM)
          operands[1] = force_reg (QImode, operands[1]);
        else if (CONSTANT_P (operands[1])
                 && (GET_CODE (operands[1]) != CONST_INT
                     || (! CSKY_CONST_OK_FOR_I (INTVAL (operands[1]))
                     && ! CSKY_CONST_OK_FOR_Ub(INTVAL (operands[1]))
                     && ! CSKY_CONST_OK_FOR_Uc (INTVAL (operands[1]))))
                 && ! reload_completed && ! reload_in_progress)
          {
            rtx reg = gen_reg_rtx (SImode);
            emit_insn (gen_movsi (reg, operands[1]));
            operands[1] = gen_lowpart (QImode, reg);
          }

        if (MEM_P (operands[1]) && optimize > 0)
          {
            rtx reg = gen_reg_rtx (SImode);

            emit_insn (gen_zero_extendqisi2 (reg, operands[1]));
            operands[1] = gen_lowpart (QImode, reg);
          }
      }

  }"
)

(define_insn "*cskyv2_movqi"
  [(set (match_operand:QI 0 "nonimmediate_operand" "=r,r,r,r,m,*y,*r,*v,*r,*v")
        (match_operand:QI 1 "general_operand"      "r, i,c,m,r,*r,*y,*r,*v,*v"))]
  "CSKY_ISA_FEATURE(E2)"
  "* return output_csky_move (insn, operands, QImode);"
  [(set_attr "length" "4,8,4,4,4,4,4,4,4,4")
   (set_attr "type" "alu,alu,alu,load,store,alu,alu,alu,alu,alu")]
)

(define_insn "*ck801_movqi"
  [(set (match_operand:QI 0 "nonimmediate_operand"  "=r,a, a,r,r,r,m")
        (match_operand:QI 1 "general_operand"       "r, Up,T,i,m,c,r"))]
  "CSKY_ISA_FEATURE(E1)"
  "* return output_ck801_move (insn, operands, QImode);"
  [(set_attr "length" "2,2,2,4,4,2,4")
   (set_attr "type" "alu,alu,alu,alu,store,alu,store")]
)


(define_expand "movdi"
  [(set (match_operand:DI 0 "general_operand" "")
        (match_operand:DI 1 "general_operand" ""))]
  ""
  "
  {
    if (can_create_pseudo_p () && GET_CODE (operands[0]) == MEM)
      operands[1] = force_reg (DImode, operands[1]);
  }"
)

;;Convert negative assignments to zero minus positive numbers.
(define_split
  [(set (match_operand:QHI 0 "register_operand" "")
        (match_operand:QHI 1 "const_int_operand" ""))]
  "satisfies_constraint_T (operands[1])"
  [(set (match_dup 4) (match_dup 2))
   (set (match_dup 4) (match_dup 3))
   (set (match_dup 0) (match_dup 5))]
  "
    int low;

    if (TARGET_BIG_ENDIAN)
      low = 4 - mode_size[GET_MODE(operands[0])];
    else
      low = 0;

    operands[2] = const0_rtx;
    if (can_create_pseudo_p ())
      operands[4] = gen_reg_rtx (SImode);
    else
    {
      operands[4] = gen_rtx_REG (SImode,
                                 REGNO (operands[0]));
    }
    operands[3] = gen_rtx_PLUS (SImode,
                                operands[4],
                                operands[1]);
    operands[5] = gen_rtx_SUBREG (GET_MODE(operands[0]),
                                  operands[4],
                                  low);
  "
)

;;Convert const assignments to small number of assignments and left shift.
(define_split
  [(set (match_operand:QHI 0 "register_operand" "")
        (match_operand:QHI 1 "const_int_operand" ""))]
  "satisfies_constraint_Ux (operands[1])"
  [(set (match_dup 3) (match_dup 1))
   (set (match_dup 3) (ashift:SI (match_dup 3) (match_dup 2)))
   (set (match_dup 0) (match_dup 4))]
  "
  {
    unsigned HOST_WIDE_INT val = INTVAL (operands[1]) &0xffffffffu;
    unsigned HOST_WIDE_INT mask = 0xff;
    int i;
    int low;

    if (TARGET_BIG_ENDIAN)
      low = 4 - mode_size[GET_MODE(operands[0])];
    else
      low = 0;

    if (can_create_pseudo_p ())
      operands[3] = gen_reg_rtx (SImode);
    else
    {
      operands[3] = gen_rtx_REG (SImode,
                                 REGNO (operands[0]));
    }

    operands[4] = gen_rtx_SUBREG (GET_MODE(operands[0]),
                                  operands[3],
                                  low);

    for (i = 0; i< 25; i++)
      {
        if((val & (mask << i)) == val)
          break;
      }
    if (i == 0)
        FAIL;
    operands[1] = GEN_INT (val >>i );
    operands[2] = GEN_INT (i);
  }"
)


(define_insn "*csky_movdi"
  [(set (match_operand:DI 0 "nonimmediate_operand"  "=r,r,r,r,m,*r,*y,*v,*r,*v,*v, *Dd")
        (match_operand:DI 1 "general_operand"       "i, F,r,m,r,*y,*r,*r,*v,*v,*Dd,*v"))]
 "CSKY_ISA_FEATURE(E2)"
 "* return output_csky_movedouble (operands, DImode);"
 [(set_attr "length" "8,8,16,16,16,16,16,16,16,4,4,4")
  (set_attr "type" "alu,alu,alu,load,store,alu,alu,alu,alu,alu,alu,alu")]
)

(define_insn "*ck801_movdi"
  [(set (match_operand:DI 0 "nonimmediate_operand"  "=r,a, a,r,r,m")
        (match_operand:DI 1 "general_operand"       "r, Up,T,mi,F,r"))]
 "CSKY_ISA_FEATURE(E1)"
 "* return output_ck801_movedouble (operands, DImode);"
 [(set_attr "length" "4,4,4,8,8,8")
  (set_attr "type" "alu,alu,alu,store,alu,store")]
)


;; ------------------------------------------------------------------------
;; Conditional mov insns
;; ------------------------------------------------------------------------

(define_expand "movsicc"
  [(set (match_operand 0 "register_operand" "")
        (if_then_else:SI (match_operand    1 "ordered_comparison_operator" "")
                         (match_operand:SI 2 "register_operand" "")
                         (match_operand:SI 3 "register_operand" "")))]
  "CSKY_ISA_FEATURE(E2)"
  "
  {
    bool invert;

    /* FIXME the float comparsion is not needed being considered here
       since it will call the libgcc function. If we want to handle it,
       describe the movsfcc and movdfcc.  */
    invert = gen_csky_compare (GET_CODE (operands[1]),
                               XEXP (operands[1], 0),
                               XEXP (operands[1], 1));

    if (invert)
      emit_insn (gen_movf(operands[0],operands[2],operands[3]));
    else
      emit_insn (gen_movt(operands[0],operands[2],operands[3]));
    DONE;
  }")

(define_insn "movt"
  [(set (match_operand:SI 0 "register_operand" "=r, r")
        (if_then_else:SI (ne (reg:CC CSKY_CC_REGNUM) (const_int 0))
                         (match_operand:SI 1 "register_operand" "r, 0")
                         (match_operand:SI 2 "register_operand" "0, r")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    movt\t%0, %1
    movf\t%0, %2"
  [(set_attr "length" "4,4")]
)

(define_insn "movf"
  [(set (match_operand:SI 0 "register_operand" "=r, r")
        (if_then_else:SI (eq (reg:CC CSKY_CC_REGNUM) (const_int 0))
                         (match_operand:SI 1 "register_operand" "r, 0")
                         (match_operand:SI 2 "register_operand" "0, r")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    movf\t%0, %1
    movt\t%0, %2"
  [(set_attr "length" "4,4")]
)

(define_expand "cstoresi4"
  [(set (match_operand:SI 0 "register_operand" "")
        (match_operator   1 "ordered_comparison_operator"
          [(match_operand:SI 2 "csky_compare_operand" "")
           (match_operand:SI 3 "nonmemory_operand" "")]))]
  ""
  "
  {
    bool invert;

    invert = gen_csky_compare (GET_CODE (operands[1]),
                               operands[2], operands[3]);

    if (invert)
      emit_insn (gen_mvcv (operands[0]));
    else {
      if (CSKY_ISA_FEATURE(E1)) {
        emit_insn (gen_movsi(operands[0], const0_rtx));
        emit_insn (gen_ck801_addc(operands[0], operands[0], operands[0]));
      } else {
        emit_insn (gen_mvc (operands[0]));
      }
    }
    DONE;
  }"
)

(define_insn "mvc"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (ne:SI (reg:CC CSKY_CC_REGNUM) (const_int 0)))]
  "CSKY_ISA_FEATURE(E2)"
  "mvc\t%0"
  [(set_attr "length" "4")]
)

(define_insn "mvcv"
  [(set (match_operand:SI 0 "register_operand" "=b,r")
        (eq:SI (reg:CC CSKY_CC_REGNUM) (const_int 0)))]
  ""
  "mvcv\t%0"
  [(set_attr "length" "2,4")
   (set_attr "isa"    "def,2e3")]
)

;; ------------------------------------------------------------------------
;; Arithmetic insns
;; ------------------------------------------------------------------------

(define_insn "abssi2"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (abs:SI (match_operand:SI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(2E3)"
  "abs\t%0, %1"
  [(set_attr "type" "alu")
   (set_attr "length" "4")]
)

(define_insn "extv"
  [(set (match_operand:SI                  0 "register_operand" "=r")
        (sign_extract:SI (match_operand:SI 1 "register_operand" "r")
                         (match_operand:SI 2 "const_int_operand" "")
                         (match_operand:SI 3 "const_int_operand" "")))]
  "CSKY_ISA_FEATURE(2E3)"
  "*{
    operands[2] = GEN_INT(INTVAL(operands[3]) + INTVAL(operands[2]) - 1);
    return \"sext\t%0, %1, %2, %3\";
  }"
  [(set_attr "length" "4")]
)

(define_insn "insv"
  [(set (zero_extract:SI (match_operand:SI 0 "register_operand"  "+r")
                         (match_operand:SI 1 "const_int_operand" "i")
                         (match_operand:SI 2 "const_int_operand" "i"))
        (match_operand:SI                  3 "register_operand"  "r"))]
  "CSKY_ISA_FEATURE(2E3)"
  "*{
    operands[1] = GEN_INT (INTVAL (operands[2]) + INTVAL (operands[1]) - 1);
    return \"ins\t%0, %3, %1, %2\";
  }"
  [(set_attr "length" "4")]
)

;; Shift instructions.

(define_expand "ashlsi3"
  [(set (match_operand:SI            0 "register_operand"     "")
        (ashift:SI (match_operand:SI 1 "register_operand"     "")
                   (match_operand:SI 2 "csky_arith_K_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_ashlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=b,r,a,r")
        (ashift:SI (match_operand:SI 1 "register_operand"     "0,r,a,r")
                   (match_operand:SI 2 "csky_arith_K_operand" "b,r,Ui,Ui")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
  lsl\t%0, %1, %2
  lsl\t%0, %1, %2
  lsli\t%0, %1, %2
  lsli\t%0, %1, %2"
  [(set_attr "predicable" "yes")
   (set_attr "length" "2,4,2,4")]
)

(define_insn "ck801_ashlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=a,r")
        (ashift:SI (match_operand:SI 1 "register_operand"     "a,0")
                   (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE(E1)"
  "@
  lsli\t%0, %1, %2
  lsl\t%0, %1, %2"
)


(define_expand "ashrsi3"
  [(set (match_operand:SI              0 "register_operand"     "")
        (ashiftrt:SI (match_operand:SI 1 "register_operand"     "")
                     (match_operand:SI 2 "csky_arith_K_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_ashrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=b,r,a,r")
        (ashiftrt:SI (match_operand:SI 1 "register_operand"     "0,r,a,r")
                     (match_operand:SI 2 "csky_arith_K_operand" "b,r,Ui,Ui")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
  asr\t%0, %1, %2
  asr\t%0, %1, %2
  asri\t%0, %1, %2
  asri\t%0, %1, %2"
  [(set_attr "type" "alu,alu,alu,alu")
   (set_attr "predicable" "yes")
   (set_attr "length" "2,4,2,4")]
)

(define_insn "*ck801_ashrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=a,r")
        (ashiftrt:SI (match_operand:SI 1 "register_operand"     "a,0")
                     (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE(E1)"
  "@
  asri\t%0, %1, %2
  asr\t%0, %1, %2"
)


(define_expand "lshrsi3"
  [(set (match_operand:SI              0 "register_operand"     "")
        (lshiftrt:SI (match_operand:SI 1 "register_operand"     "")
                     (match_operand:SI 2 "csky_arith_K_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_lshrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=b,r,a,r")
        (lshiftrt:SI (match_operand:SI 1 "register_operand"     "0,r,a,r")
                     (match_operand:SI 2 "csky_arith_K_operand" "b,r,Ui,Ui")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
  lsr\t%0, %1, %2
  lsr\t%0, %1, %2
  lsri\t%0, %1, %2
  lsri\t%0, %1, %2"
  [(set_attr "predicable" "yes")
   (set_attr "length" "2,4,2,4")]
)

(define_insn "ck801_lshrsi3"
  [(set (match_operand:SI              0 "register_operand"     "=a,r")
        (lshiftrt:SI (match_operand:SI 1 "register_operand"     "a,0")
                     (match_operand:SI 2 "csky_arith_K_operand" "Ui,r")))]
  "CSKY_ISA_FEATURE(E1)"
  "@
  lsri\t%0, %1, %2
  lsr\t%0, %1, %2"
)


(define_expand "rotlsi3"
  [(set (match_operand:SI            0 "register_operand"     "")
        (rotate:SI (match_operand:SI 1 "register_operand"     "")
                   (match_operand:SI 2 "csky_arith_K_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_rotlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=b,r,a,r")
        (rotate:SI (match_operand:SI 1 "register_operand"     "0,r,a,r")
                   (match_operand:SI 2 "csky_arith_K_operand" "b,r,Ui,Ui")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
  rotl\t%0, %1, %2
  rotl\t%0, %1, %2
  rotli\t%0, %1, %2
  rotli\t%0, %1, %2"
  [(set_attr "length" "2,4,2,4")]
)

(define_insn "*ck801_rotlsi3"
  [(set (match_operand:SI            0 "register_operand"     "=r")
        (rotate:SI (match_operand:SI 1 "register_operand"     "0")
                   (match_operand:SI 2 "csky_arith_K_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "rotl\t%0, %1, %2"
)


;; Add instructions.
;; FIXME there is no need to consider subtraction instructions
;; in addition, neither to consider addition instructions in
;; subtraction.

(define_expand "addsi3"
  [(set (match_operand:SI          0 "register_operand" "")
        (plus:SI (match_operand:SI 1 "register_operand" "")
                 (match_operand:SI 2 "nonmemory_operand" "")))]
  ""
  ""
)

;;remove mov insn from here.
;; Add extra predicate to exclude those registers would be eliminated to
;; stack pointer.
;; Commented by JianPing Zeng on 1/18/2018.
(define_insn "*smart_addsi3"
 [(set (match_operand:SI          0 "register_operand"  "=a,r,a,a,a,a, a, r,r")
       (plus:SI (match_operand:SI 1 "register_operand"  "%a,0,0,a,0,a, a, r,r")
                (match_operand:SI 2 "nonmemory_operand" "a, r,N,L,T,Us,Ua,M,Um")))]
 "CSKY_ISA_FEATURE(smart) && operands[0] != stack_pointer_rtx
  && operands[1] != stack_pointer_rtx && !csky_eliminable_register(operands[0])
  && !csky_eliminable_register(operands[1])"
 "@
     addu\t%0, %1, %2
     addu\t%0, %1, %2
     addi\t%0, %1, %2
     addi\t%0, %1, %2
     subi\t%0, %1, %M2
     subi\t%0, %1, %M2
     mov\t%0, %1
     addi\t%0, %1, %2
     subi\t%0, %1, %M2"
  [(set_attr "length" "2,2,2,2,2,2,2,4,4")
   (set_attr "type" "addsub")]
)

;; Add the last constraints on operands for sequence of instructions.
;; "%vreg81 = %vreg36 - 4"
;; will be transformated into
;; "%vreg82 = %vreg36"
;; "%vreg82 = %vreg82 - 4"
;; "%vreg81 = %vreg82"
;; Commented by JianPing Zeng on 1/18/2018.
(define_insn "*smart_addsi3_sp"
  [(set (match_operand:SI          0 "register_operand"  "=z,z, z,a, z,a,r,r,r")
        (plus:SI (match_operand:SI 1 "register_operand"  "0, 0, 0,z, a,z,r,0,0")
                 (match_operand:SI 2 "nonmemory_operand" "P, Ug,r,Uq,a,a,M,Um,a")))]
  "CSKY_ISA_FEATURE(smart) && (operands[0] == stack_pointer_rtx
                    || operands[1] == stack_pointer_rtx
                    || csky_eliminable_register(operands[0])
                    || csky_eliminable_register(operands[1]))"
  "@
     addi\t%0, %1, %2
     subi\t%0, %1, %M2
     addu\t%0, %1, %2
     addi\t%0, %1, %2
     addu\t%0, %1, %2
     addu\t%0, %1, %2
     addi\t%0, %1, %2
     subi\t%0, %M2
     addu\t%0, %1, %2"
  [(set_attr "type" "addsub")
   (set_attr "length" "2,2,2,2,4,4,4,4,4")]
)

(define_insn "*ck801_addsi3"
  [(set (match_operand:SI          0 "register_operand"  "=r,a,a,a,a,a, !z,!z,!z,a")
        (plus:SI (match_operand:SI 1 "register_operand"  "%0,a,0,a,0,a, 0, 0, 0, !z")
                 (match_operand:SI 2 "nonmemory_operand" "r, a,N,L,T,Us,P, Ug,r, Uq")))]
  "CSKY_ISA_FEATURE(E1)"
  "@
    addu\t%0, %1, %2
    addu\t%0, %1, %2
    addi\t%0, %1, %2
    addi\t%0, %1, %2
    subi\t%0, %1, %M2
    subi\t%0, %1, %M2
    addi\t%0, %1, %2
    subi\t%0, %1, %M2
    addu\t%0, %1, %2
    addi\t%0, %1, %2"
)

(define_insn "*fast_addsi3"
  [(set (match_operand:SI          0 "register_operand"  "=a,a,r,b,a,r,a,a,r")
        (plus:SI (match_operand:SI 1 "register_operand"  "%0,a,r,0,a,r,0,a,r")
                 (match_operand:SI 2 "nonmemory_operand" "N,L,M,b,a,r,T,Us,Um")))]
  "CSKY_ISA_FEATURE_FAST && CSKY_ISA_FEATURE(E2)"
  "@
    addi\t%0, %1, %2
    addi\t%0, %1, %2
    addi\t%0, %1, %2
    addu\t%0, %1, %2
    addu\t%0, %1, %2
    addu\t%0, %1, %2
    subi\t%0, %1, %M2
    subi\t%0, %1, %M2
    subi\t%0, %1, %M2"
  [(set_attr "type" "addsub")
   (set_attr "predicable" "yes")
   (set_attr "length" "2,2,4,2,2,4,2,2,4")]
)

;; TODO:define insn for addh.s32

(define_insn "*dspv2_addhusi3"
  [(set (match_operand:SI          0 "register_operand"  "=r")
        (udiv:SI (plus:SI (match_operand:SI 1 "register_operand"  "%r")
                         (match_operand:SI 2 "register_operand"  "r"))
                (const_int 2)))]
  "CSKY_ISA_FEATURE(dspv2)"
  "addh.u32\t%0, %1, %2"
  [(set_attr "length" "4")]
)

(define_insn "*dspv2_addhusi3_2"
  [(set (match_operand:SI          0 "register_operand"  "=r")
        (lshiftrt:SI (plus:SI (match_operand:SI 1 "register_operand"  "%r")
                              (match_operand:SI 2 "register_operand"  "r"))
                (const_int 1)))]
  "CSKY_ISA_FEATURE(dspv2)"
  "addh.u32\t%0, %1, %2"
  [(set_attr "length" "4")]
)

(define_expand "adddi3"
  [(parallel [(set (match_operand:DI 0 "register_operand" "")
                   (plus:DI (match_operand:DI 1 "register_operand" "")
                            (match_operand:DI 2 "csky_arith_int1_operand" "")))
              (clobber (reg:CC CSKY_CC_REGNUM))])]
  ""
  "
  {
    if (CSKY_ISA_FEATURE(E1) && (GET_CODE (operands[2]) != REG))
        operands[2] = force_reg (DImode, operands[2]);
    else if (CSKY_ISA_FEATURE (dspv2) && (REG_P (operands[2])
                                          || SUBREG_P (operands[2])))
      {
        emit_insn (gen_dspv2_adddi3 (operands[0], operands[1], operands[2]));
        DONE;
      }
  }
  "
)

;; TODO calculate the length more precisely
;; TODO split the insn in rtx.
(define_insn "*cskyv2_adddi3"
  [(set (match_operand:DI          0 "register_operand" "=&b,&b,&r,&r")
        (plus:DI (match_operand:DI 1 "register_operand" "%0, b, 0, r")
                 (match_operand:DI 2 "register_operand" "b,  b, r, r")))
   (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E2) && !CSKY_ISA_FEATURE(dspv2)"
  "*
  {
    if (TARGET_BIG_ENDIAN)
      return \"cmplt\t%R0, %R0\;addc\t%R0, %R1, %R2\;addc\t%0, %1, %2\";
    return \"cmplt\t%0, %0\;addc\t%0, %1, %2\;addc\t%R0, %R1, %R2\";
  }"
  [(set_attr "length" "6,6,12,12")
   (set_attr "isa"    "def,def,2e3,2e3")]
)

(define_insn "*ck801_adddi3"
  [(set (match_operand:DI          0 "register_operand" "=&r")
        (plus:DI (match_operand:DI 1 "register_operand" "%0")
                 (match_operand:DI 2 "register_operand" "r")))
   (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E1)"
  "*
  {
    if (TARGET_BIG_ENDIAN)
      return \"cmplt\t%R0, %R0\;addc\t%R0, %R1, %R2\;addc\t%0, %1, %2\";
    return \"cmplt\t%0, %0\;addc\t%0, %1, %2\;addc\t%R0, %R1, %R2\";
  }"
  [(set_attr "length" "6")]
)

(define_insn "dspv2_adddi3"
  [(set (match_operand:DI          0 "register_operand" "=r")
        (plus:DI (match_operand:DI 1 "register_operand" "%r")
                 (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "add.64\t%0, %1, %2"
  [(set_attr "length" "4")]
)

;; special case for "longlong += 1"
;;TODO split insn in rtx.
(define_insn "*cskyv2_adddi1_1"
  [(set (match_operand:DI          0 "register_operand" "=&r")
        (plus:DI (match_operand:DI 1 "register_operand" "0")
                 (const_int 1)))
  (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E2)"
  "*
  {
    if(TARGET_BIG_ENDIAN)
      return \"addi\t%R0, %R0, 1\;cmpnei\t%R0, 0\;incf\t%0, %0, 1\";
    return \"addi\t%0, %0, 1\;cmpnei\t%0, 0\;incf\t%R0, %R0, 1\";
  }"
  [(set_attr "length" "12")]
)


;; sub instructions.

(define_expand "subsi3"
  [(set (match_operand:SI 0 "register_operand" "")
        (minus:SI (match_operand:SI 1 "register_operand" "")
                  (match_operand:SI 2 "nonmemory_operand" "")))]
  ""
  ""
)

;;remove mov insn here.
(define_insn "*smart_subsi3"
  [(set (match_operand:SI           0 "register_operand"    "=a,a,a,a,a,a ,a")
        (minus:SI (match_operand:SI 1 "register_operand"    "a, 0,0,a,0,a ,a")
                  (match_operand:SI 2 "nonmemory_operand"   "a, a,N,L,T,Us,Ua")))]
  "CSKY_ISA_FEATURE(smart) && operands[0] != stack_pointer_rtx
   && operands[1] != stack_pointer_rtx"
  "@
    subu\t%0, %1, %2
    subu\t%0, %1, %2
    subi\t%0, %1, %2
    subi\t%0, %1, %2
    addi\t%0, %1, %M2
    addi\t%0, %1, %M2
    mov\t%0, %1"
  [(set_attr "length" "2,2,2,2,2,2,2")
   (set_attr "type" "addsub")]
)

(define_insn "*smart_subsi3_sp"
  [(set (match_operand:SI           0 "register_operand"  "=z,z, z,a, a,r")
        (minus:SI (match_operand:SI 1 "register_operand"  "0, 0, 0,z, a,r")
                  (match_operand:SI 2 "nonmemory_operand" "P, Ug,a,Ur,a,M")))]
  "CSKY_ISA_FEATURE(smart) && (operands[0] == stack_pointer_rtx
                    || operands[1] == stack_pointer_rtx)"
  "@
    subi\t%0, %1, %2
    addi\t%0, %1, %M2
    subu\t%0, %1, %2
    addi\t%0, %1, %M2
    subu\t%0, %1, %2
    subi\t%0, %1, %2"
  [(set_attr "length" "2,2,2,2,2,4")
   (set_attr "type" "addsub")]
)

(define_insn "*ck801_subsi3"
  [(set (match_operand:SI           0 "register_operand"    "=a,a,a,a,a,a")
        (minus:SI (match_operand:SI 1 "register_operand"    "0, a,0,a,0,a")
                  (match_operand:SI 2 "nonmemory_operand"   "a, a,N,L,T,Us")))]
  "CSKY_ISA_FEATURE(E1)
   && operands[0] != stack_pointer_rtx
   && operands[1] != stack_pointer_rtx"
  "@
    subu\t%0, %1, %2
    subu\t%0, %1, %2
    subi\t%0, %1, %2
    subi\t%0, %1, %2
    addi\t%0, %1, %M2
    addi\t%0, %1, %M2"
)

(define_insn "*ck801_subsi3_sp"
  [(set (match_operand:SI           0 "register_operand"  "=a,z,z, z")
        (minus:SI (match_operand:SI 1 "register_operand"  "z, 0,0, 0")
                  (match_operand:SI 2 "nonmemory_operand" "Ur,P,Ug,r")))]
  "CSKY_ISA_FEATURE(E1)
   && (operands[0] == stack_pointer_rtx
       || operands[1] == stack_pointer_rtx)"
  "@
    addi\t%0, %1, %M2
    subi\t%0, %1, %2
    addi\t%0, %1, %M2
    subu\t%0, %1, %2"
)

(define_insn "*fast_subsi3"
  [(set (match_operand:SI           0 "register_operand"  "=b,a,r,a,a,r,a,a,r")
        (minus:SI (match_operand:SI 1 "register_operand"  "0,a,r, 0,a,r,0,a,r")
                  (match_operand:SI 2 "nonmemory_operand" "b,a,r, N,L,M,T,Us,Um")))]
  "CSKY_ISA_FEATURE_FAST && CSKY_ISA_FEATURE(E2)"
  "@
     subu\t%0, %1, %2
     subu\t%0, %1, %2
     subu\t%0, %1, %2
     subi\t%0, %1, %2
     subi\t%0, %1, %2
     subi\t%0, %1, %2
     addi\t%0, %1, %M2
     addi\t%0, %1, %M2
     addi\t%0, %1, %M2"
  [(set_attr "type" "addsub")
   (set_attr "predicable" "yes")
   (set_attr "length" "2,2,4,2,2,4,2,2,4")]
)

;; TODO:define insn for subh.s32

(define_insn "*dspv2_addhusi3"
  [(set (match_operand:SI          0 "register_operand"  "=r")
        (udiv:SI (minus:SI (match_operand:SI 1 "register_operand"  "r")
                           (match_operand:SI 2 "register_operand"  "r"))
                 (const_int 2)))]
  "CSKY_ISA_FEATURE(dspv2)"
  "subh.u32\t%0, %1, %2"
  [(set_attr "length" "4")]
)

(define_insn "*dspv2_addhusi3_2"
  [(set (match_operand:SI          0 "register_operand"  "=r")
        (lshiftrt:SI (minus:SI (match_operand:SI 1 "register_operand"  "%r")
                               (match_operand:SI 2 "register_operand"  "r"))
                     (const_int 1)))]
  "CSKY_ISA_FEATURE(dspv2)"
  "subh.u32\t%0, %1, %2"
  [(set_attr "length" "4")]
)

(define_expand "subdi3"
  [(parallel [(set (match_operand:DI 0 "register_operand" "")
                  (minus:DI (match_operand:DI 1 "register_operand" "")
                            (match_operand:DI 2 "register_operand" "")))
              (clobber (reg:CC CSKY_CC_REGNUM))])]
  ""
  "
    if (CSKY_ISA_FEATURE (dspv2))
    {
      emit_insn (gen_dspv2_subdi3 (operands[0], operands[1], operands[2]));
      DONE;
    }
  "
)

;; TODO calculate the length more precisely
;;TODO split insn in rtx.
(define_insn "*cskyv2_subdi3"
  [(set (match_operand:DI           0 "register_operand" "=&b,&b,&b,&r,&r,&r")
        (minus:DI (match_operand:DI 1 "register_operand" "0,  b, b, 0,  r,r")
                  (match_operand:DI 2 "register_operand" "b,  0, b, r,  0,r")))
  (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E2) && !CSKY_ISA_FEATURE(dspv2)"
  "*{
    if (TARGET_BIG_ENDIAN)
      return \"cmphs\t%R0, %R0\;subc\t%R0, %R1,%R2\;subc\t%0, %1, %2\";
    return \"cmphs\t%0, %0\;subc\t%0, %1, %2\;subc\t%R0, %R1, %R2\";
  }"
  [(set_attr "length" "6,6,6,12,12,12")
   (set_attr "isa"    "def,def,def,2e3,2e3,2e3")]
)

(define_insn "*ck801_subdi3"
  [(set (match_operand:DI           0 "register_operand" "=&r")
        (minus:DI (match_operand:DI 1 "register_operand" "0")
                  (match_operand:DI 2 "register_operand" "r")))
   (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E1)"
  "*{
    if (TARGET_BIG_ENDIAN)
      return \"cmphs\t%R0, %R0\;subc\t%R0, %R1,%R2\;subc\t%0, %1, %2\";
    return \"cmphs\t%0, %0\;subc\t%0, %1, %2\;subc\t%R0, %R1, %R2\";
  }"
  [(set_attr "length" "6")]
)

(define_insn "dspv2_subdi3"
  [(set (match_operand:DI          0 "register_operand" "=r")
        (minus:DI (match_operand:DI 1 "register_operand" "r")
                  (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "sub.64\t%0, %1, %2"
  [(set_attr "length" "4")]
)

;; special case for "longlong -= 1"
;;TODO split insn in rtx.
(define_insn "*cskyv2_adddi1_1"
  [(set (match_operand:DI          0 "register_operand" "=&r")
        (plus:DI (match_operand:DI 1 "register_operand" "0")
                 (const_int -1)))
  (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
    if(TARGET_BIG_ENDIAN)
      return \"cmpnei\t%R0, 0\;decf\t%0, %0, 1\;subi\t%R0, %R0, 1\";
    return \"cmpnei\t%0, 0\;decf\t%R0, %R0, 1\;subi\t%0, %0, 1\";
  }"
  [(set_attr "length" "12")]
)


;; ------------------------------------------------------------------------
;; Multiplication insns
;; ------------------------------------------------------------------------

(define_expand "mulsi3"
  [(set (match_operand:SI          0 "register_operand" "")
        (mult:SI (match_operand:SI 1 "register_operand" "")
                 (match_operand:SI 2 "register_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_mulsi3"
  [(set (match_operand:SI          0 "register_operand" "=b,r")
        (mult:SI (match_operand:SI 1 "register_operand" "%0,r")
                 (match_operand:SI 2 "register_operand" "b,r")))]
  "CSKY_ISA_FEATURE(E2)"
  "mult\t%0, %1, %2"
  [(set_attr "predicable" "yes")
   (set_attr "length" "2,4")]
)

(define_insn "*ck801_mulsi3"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (mult:SI (match_operand:SI 1 "register_operand" "%0")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "mult\t%0, %1, %2"
)

(define_insn "mulhisi3"
  [(set (match_operand:SI                          0 "register_operand" "=b,r")
        (mult:SI (sign_extend:SI (match_operand:HI 1 "register_operand" "%0,r"))
                 (sign_extend:SI (match_operand:HI 2 "register_operand" "b,r"))))]
  "CSKY_ISA_FEATURE(2E3)"
  "mulsh\t%0, %1, %2"
  [(set_attr "length" "2,4")]
)


;; ------------------------------------------------------------------------
;; Conditional add insns
;; ------------------------------------------------------------------------

(define_expand "addsicc"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand    1 "ordered_comparison_operator" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:SI 3 "csky_literal_K_Uh_operand" "")]
  "CSKY_ISA_FEATURE(E2)"
  "
  {
    bool invert;

    invert = gen_csky_compare (GET_CODE (operands[1]),
                               XEXP (operands[1], 0),
                               XEXP (operands[1], 1));

    if (invert)
      emit_insn (gen_cskyv2_addcc_invert(operands[0],operands[2],operands[3]));
    else
      emit_insn (gen_cskyv2_addcc(operands[0],operands[2],operands[3]));

    DONE;
  }"
)

;; TODO split the insn in rtx.
(define_insn "cskyv2_addcc"
  [(set (match_operand:SI                           0 "register_operand"          "=r,r")
        (if_then_else:SI (ne (reg:CC CSKY_CC_REGNUM) (const_int 0))
                         (plus:SI (match_operand:SI 1 "register_operand"          "r,r")
                                  (match_operand:SI 2 "csky_literal_K_Uh_operand" "K,Uh"))
                         (match_dup 1)))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
      switch (which_alternative)
      {
         case 0:
           if (rtx_equal_p (operands[0], operands[1]))
             return \"inct\t%0, %1, %2\";
           else
             return \"movf\t%0, %1\;inct\t%0, %1, %2\";
         case 1:
           if (rtx_equal_p (operands[0], operands[1]))
             return \"dect\t%0, %1, %M2\";
           else
             return \"movf\t%0, %1\;dect\t%0, %1, %M2\";
         default:
             gcc_unreachable();
      }
  }"
  [(set (attr "length")
        (if_then_else (eq (match_dup 0) (match_dup 1))
                      (const_int 4)
                      (const_int 8)))
   (set_attr "type" "addsub")]
)

(define_insn "cskyv2_addcc_invert"
  [(set (match_operand:SI                           0 "register_operand"          "=r,r")
        (if_then_else:SI (eq (reg:CC CSKY_CC_REGNUM) (const_int 0))
                         (plus:SI (match_operand:SI 1 "register_operand"          "r,r")
                                  (match_operand:SI 2 "csky_literal_K_Uh_operand" "K,Uh"))
                         (match_dup 1)))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
    switch (which_alternative)
    {
      case 0:
        if (rtx_equal_p (operands[0], operands[1]))
          return \"incf\t%0, %1, %2\";
        else
          return \"movt\t%0, %1\;incf\t%0, %1, %2\";
      case 1:
        if (rtx_equal_p (operands[0], operands[1]))
          return \"decf\t%0, %1, %M2\";
        else
          return \"movt\t%0, %1\;decf\t%0, %1, %M2\";
      default:
          gcc_unreachable();
    }
  }"
  [(set (attr "length")
        (if_then_else (eq (match_dup 0) (match_dup 1))
                      (const_int 4)
                      (const_int 8)))
   (set_attr "type" "addsub")]
)

/* FIXME this insn is now only used in 801 store, can it use
   for 801 conditional add const 1?  */
(define_insn "ck801_addc"
  [(set (match_operand:SI                   0 "register_operand" "=r")
        (plus:SI (ne:SI (reg:CC CSKY_CC_REGNUM) (const_int 0))
                 (plus:SI (match_operand:SI 1 "register_operand" "%0")
                          (match_operand:SI 2 "register_operand" "r"))))
  (clobber (reg:CC CSKY_CC_REGNUM))]
 "CSKY_ISA_FEATURE(E1)"
 "addc\t%0, %1, %2"
)


;; ------------------------------------------------------------------------
;; Extzv insns
;; ------------------------------------------------------------------------

(define_expand "extzvsi"
  [(set (match_operand:SI 0 "register_operand" "")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "")
                         (match_operand:SI 2 "const_int_operand" "")
                         (match_operand:SI 3 "const_int_operand" "")))]
  ""
  "{
    /* If the cpu has xtrb but donot have zext, we use xtrb if could.
       Now only ck802 will do this job.  */
    if (CSKY_ISA_FEATURE(E2) && !CSKY_ISA_FEATURE(2E3)
        && (INTVAL (operands[2]) == 8)
        && (INTVAL (operands[3]) % 8 == 0))
      {
        rtx xtrb = gen_rtx_SET (operands[0],
                                gen_rtx_ZERO_EXTRACT (SImode,
                                                      operands[1],
                                                      operands[2],
                                                      operands[3]));
        emit (gen_rtx_PARALLEL (VOIDmode,
                                gen_rtvec (2, xtrb,
                                gen_hard_reg_clobber (CCmode, CSKY_CC_REGNUM))));
        DONE;
      }
    else if (!CSKY_ISA_FEATURE (2E3))
      {
        /* Use lsri and lsli to do extzv when donot have zext.  */
        rtx lshft = GEN_INT (32 - (INTVAL (operands[2])
                             + INTVAL (operands[3])));
        rtx rshft = GEN_INT (32 - INTVAL (operands[2]));
        rtx tmp1 = gen_reg_rtx (SImode);
        rtx tmp2 = gen_reg_rtx (SImode);

        emit_insn (gen_rtx_SET (tmp1, operands[1]));
        emit_insn (gen_rtx_SET (tmp2, gen_rtx_ASHIFT (SImode, tmp1, lshft)));
        emit_insn (gen_rtx_SET (operands[0],
                                gen_rtx_LSHIFTRT (SImode, tmp2, rshft)));
        DONE;
      }
    else
      {
        emit_insn (gen_cskyv2_extzv (operands[0], operands[1],
                                     operands[2], operands[3]));
        DONE;
      }
}")

(define_insn "cskyv2_extzv"
  [(set (match_operand:SI                  0 "register_operand" "=r")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "r")
                         (match_operand:SI 2 "csky_literal_K_operand" "K")
                         (match_operand:SI 3 "csky_literal_K_operand" "K")))]
  "CSKY_ISA_FEATURE(2E3)"
  "*{
    operands[2] = GEN_INT (INTVAL (operands[3]) + INTVAL (operands[2]) - 1);
    return \"zext\t%0, %1, %2, %3\";
  }"
)

(define_insn "*cskyv2_xtrb0"
  [(set (match_operand:SI                  0 "register_operand" "=a,r,r")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "0,0,r")
                         (const_int 8)
                         (const_int 24)))
        (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    lsri\t%0, %0, 24
    lsri\t%0, %0, 24
    xtrb0\t%0, %1"
  [(set_attr "length" "2,4,4")]
)

(define_insn "*cskyv2_xtrb1"
  [(set (match_operand:SI                  0 "register_operand" "=r")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "r")
                         (const_int 8)
                         (const_int 16)))
        (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E2)"
  "xtrb1\t%0, %1"
)

(define_insn "*cskyv2_xtrb2"
  [(set (match_operand:SI                  0 "register_operand" "=r")
        (zero_extract:SI (match_operand:SI 1 "register_operand" "r")
                         (const_int 8)
                         (const_int 8)))
        (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(E2)"
  "xtrb2\t%0, %1"
)


;; -------------------------------------------------------------------------
;; Zero extension instructions
;; -------------------------------------------------------------------------
(define_insn "zero_extendhisi2"
  [(set (match_operand:SI                 0 "register_operand" "=b,r")
        (zero_extend:SI (match_operand:HI 1 "register_operand" "b, r")))]
  ""
  "zexth\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "isa"    "def,2e3")]
)

(define_insn "*cskyv2_zextend_ldh"
  [(set (match_operand:SI                 0 "register_operand" "=r,r")
        (zero_extend:SI (match_operand:HI 1 "csky_addr_reg_disp" "Dm,Dp")))]
  ""
  "@
   ld.h\t%0, %1
   ldbi.h\t%0, %1"
  [(set_attr "length" "4")
   (set_attr "type" "load")]
)

(define_insn "zero_extendqisi2"
  [(set (match_operand:SI                 0 "register_operand" "=b,r")
        (zero_extend:SI (match_operand:QI 1 "register_operand" "b, r")))]
  ""
  "zextb\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "isa"    "def,2e3")]
)

(define_insn "*cskyv2_zextend_ldb"
  [(set (match_operand:SI                 0 "register_operand" "=r,r, r")
        (zero_extend:SI (match_operand:QI 1 "csky_addr_reg"    "W, Dm,Dp")))]
  ""
  "@
   ldr.b\t%0, %1
   ld.b\t%0, %1
   ldbi.b\t%0, %1"
  [(set_attr "length" "4,4,4")
   (set_attr "type" "load,load,load")]
)

(define_insn "zero_extendqihi2"
  [(set (match_operand:HI                 0 "register_operand" "=b,r")
        (zero_extend:HI (match_operand:QI 1 "register_operand" "b, r")))]
  ""
  "zextb\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "isa"    "def,2e3")]
)

(define_insn "*cskyv2_zextend_ldbhi"
  [(set (match_operand:HI                 0 "register_operand"   "=r,r")
        (zero_extend:HI (match_operand:QI 1 "csky_addr_reg_disp" "Dm,Dp")))]
  ""
  "@
   ld.b\t%0, %1
   ldbi.b\t%0, %1"
  [(set_attr "length" "4")
   (set_attr "type" "load")]
)

;; -------------------------------------------------------------------------
;; clzm2 instructions
;; -------------------------------------------------------------------------

(define_insn "clzsi2"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (clz:SI (match_operand:SI 1 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E2)"
  "ff1\t%0,%1"
)

;; -------------------------------------------------------------------------
;; one_cmplm2 instructions
;; -------------------------------------------------------------------------

(define_expand "one_cmplsi2"
  [(set (match_operand:SI         0 "register_operand" "")
        (not:SI (match_operand:SI 1 "register_operand" "")))]
  ""
  ""
)

(define_insn "*csky_one_cmplsi2"
  [(set (match_operand:SI         0 "register_operand" "=b,r")
        (not:SI (match_operand:SI 1 "register_operand" "0,r")))]
  "CSKY_ISA_FEATURE(E2)"
  "not\t%0, %1"
  [(set_attr "predicable" "yes")
   (set_attr "length" "2,4")]
)

(define_insn "*ck801_one_cmplsi2"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (not:SI (match_operand:SI 1 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(E1)"
  "not\t%0, %1"
)

;; -------------------------------------------------------------------------
;; Sign extension instructions
;; -------------------------------------------------------------------------

;; One test shows that the following code helps to
;; reduce one 'load' and two 'mov'.
(define_expand "extendsidi2"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (match_operand:SI 1 "register_operand" "r"))]
  ""
  "{
    int low, high;

    if (TARGET_BIG_ENDIAN)
      low = 4, high = 0;
    else
      low = 0, high = 4;

    emit_insn (gen_rtx_SET (gen_rtx_SUBREG(SImode, operands[0], low),
                            operands[1]));

    emit_insn (gen_rtx_SET (gen_rtx_SUBREG (SImode, operands[0], high),
                            gen_rtx_ASHIFTRT (SImode,
                                              gen_rtx_SUBREG (SImode,
                                                              operands[0],
                                                              low),
                                              GEN_INT(31))));
    DONE;
  }"
)

(define_insn "extendhisi2"
  [(set (match_operand:SI                 0 "register_operand" "=b,r")
        (sign_extend:SI (match_operand:HI 1 "register_operand" "b, r")))]
  ""
  "sexth\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "isa"    "def,2e3")]
)

(define_insn "*cskyv2_sextend_ldhs"
  [(set (match_operand:SI                 0 "register_operand" "=r,r")
        (sign_extend:SI (match_operand:HI 1 "csky_addr_reg_disp" "Dm,Dp")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
   ld.hs\t%0, %1
   ldbi.hs\t%0, %1"
  [(set_attr "length" "4")
   (set_attr "type" "load")]
)

;; qi -> si
(define_insn "extendqisi2"
  [(set (match_operand:SI                 0 "register_operand" "=b,r")
        (sign_extend:SI (match_operand:QI 1 "register_operand" "b, r")))]
  ""
  "sextb\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "isa"    "def,2e3")]
)

(define_insn "*cskyv2_sextend_ldbs"
  [(set (match_operand:SI                 0 "register_operand" "=r,r")
        (sign_extend:SI (match_operand:QI 1 "csky_addr_reg_disp" "Dm,Dp")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
   ld.bs\t%0, %1
   ldbi.bs\t%0, %1"
  [(set_attr "length" "4")
   (set_attr "type" "load")]
)

;; qi -> hi
(define_insn "extendqihi2"
  [(set (match_operand:HI                 0 "register_operand" "=b,r")
        (sign_extend:HI (match_operand:QI 1 "register_operand" "b, r")))]
  ""
  "sextb\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "isa"    "def,2e3")]
)

;; -------------------------------------------------------------------------
;; And instructions
;; -------------------------------------------------------------------------

(define_expand "andsi3"
  [(set (match_operand:SI 0 "register_operand" "")
        (and:SI (match_operand:SI 1 "register_operand" "")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
  {
    int i;
    rtx not_value;

    if (GET_CODE(operands[2]) == CONST_INT)
    {
      for (i = 13; i <= 31; i++)
      {
        if ((((HOST_WIDE_INT) 1) << i) - 1 == INTVAL (operands[2]))
          {
            emit_insn (gen_extzvsi (operands[0], operands[1], GEN_INT (i),
                                    const0_rtx));
            DONE;
          }
        else if ((((HOST_WIDE_INT) 1) << i) - 1
             == ~INTVAL (operands[2]))
          {
            rtx shift = GEN_INT (i);
            rtx reg = gen_reg_rtx (SImode);

            emit_insn (gen_lshrsi3 (reg, operands[1], shift));
            emit_insn (gen_ashlsi3 (operands[0], reg, shift));
            DONE;
          }
      }

      not_value = GEN_INT (~INTVAL(operands[2]));

      /* Try to transform to andni insrtuction.  */
      if (CSKY_ISA_FEATURE(E2))
        {
          if(csky_arith_O_operand (not_value,SImode))
            {
              emit_insn(gen_cskyv2_andnsi3 (operands[0], not_value, operands[1]));
              DONE;
            }
        }

      /* Let it emit andi or bclri*2 if it could. Otherwise, try
         some other ways.  */
      if (!satisfies_constraint_Ue(operands[2])
          && !(CSKY_ISA_FEATURE(E2) && satisfies_constraint_O (operands[2])))
        {
          /* If it is a negitive number, it seems better to use andn,
             since the NOT_VALUE, is always smaller than the origin value.  */
          if (INTVAL(operands[2]) < 0)
            {
              operands[2] = copy_to_mode_reg(SImode, not_value);
              emit_insn(gen_cskyv2_andnsi3 (operands[0], operands[2], operands[1]));
              DONE;
            }

          /* If the above ways are all not working, mov the const
             to reg.  */
          operands[2] = copy_to_mode_reg(SImode, operands[2]);
        }
    }
 }"
)

;;FIXME describe the length more precisely here.
;;TODO split insn in rtx.
(define_insn "*cskyv2_andsi3"
  [(set (match_operand:SI         0 "register_operand"           "=r,r,r")
        (and:SI (match_operand:SI 1 "register_operand"           "%r,r,r")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "r, O,Ue")))]
  "CSKY_ISA_FEATURE(E2)
   && (CONST_INT_P(operands[2])
       || !can_trans_by_csky_shlshr (INTVAL (operands[2])))"
  "*{
    switch(which_alternative)
      {
      case 0: return \"and\t%0, %1, %2\";
      case 1: return \"andi\t%0, %1, %2\";
      case 2: return output_csky_bclri(operands[0],
                                       operands[1],
                                       INTVAL(operands[2]));
      default: gcc_unreachable();
      }
  }"
  [(set_attr "length" "4,4,8")
   (set_attr "type" "alu,alu,alu")
   (set_attr "predicable" "yes")]
)

(define_insn "*ck801_andsi3"
  [(set (match_operand:SI         0 "register_operand"      "=r,r")
        (and:SI (match_operand:SI 1 "register_operand"      "%0,0")
                (match_operand:SI 2 "csky_arith_Ue_operand" "r, Ue")))]
  "CSKY_ISA_FEATURE(E1)"
  "*{
    switch(which_alternative)
      {
      case 0: return \"and\t%0, %1, %2\";
      case 1: return output_csky_bclri(operands[0],
                                       operands[1],
                                       INTVAL(operands[2]));
      default: gcc_unreachable();
      }
  }"
  [(set_attr "length" "2,4")]
)

(define_insn "cskyv2_andnsi3"
  [(use (and:SI (not:SI (match_operand:SI 1 "csky_arith_O_operand" "b,r, O"))
        (match_operand:SI                 2 "register_operand"     "0,r, r")))
   (set (match_operand:SI                 0 "register_operand"     "=b,r,r")
        (and:SI (not:SI (match_dup 1))
                (match_dup 2)))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    andn\t%0, %2, %1
    andn\t%0, %2, %1
    andni\t%0, %2, %1"
  [(set_attr "type" "alu,alu,alu")
   (set_attr "length" "2,4,4")]
)

(define_insn "ck801_andnsi3"
  [(use (and:SI (not:SI (match_operand:SI 1 "register_operand" "r"))
                (match_operand:SI         2 "register_operand" "0")))
   (set (match_operand:SI                 0 "register_operand" "=r")
        (and:SI (not:SI (match_dup 1))
                (match_dup 2)))]
 "CSKY_ISA_FEATURE(E1)"
 "andn\t%0, %2, %1"
)

(define_expand "anddi3"
  [(set (match_operand:DI 0 "register_operand" "")
        (and:DI (match_operand:DI 1 "register_operand" "")
                (match_operand:DI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
  {
    if (GET_CODE(operands[2]) == CONST_INT)
      {
        HOST_WIDE_INT ival = INTVAL (operands[2]);
        if (ival == (HOST_WIDE_INT) 0xffffffff)
          {
            emit_move_insn (gen_lowpart (SImode, operands[0]), gen_lowpart (SImode, operands[1]));
            emit_move_insn (gen_highpart(SImode, operands[0]), const0_rtx);
            DONE;
          }
        else
          {
            FAIL;
          }
      }
  }"
)

;;TODO split insn in rtx.
(define_insn "*cskyv2_anddi3"
  [(set (match_operand:DI         0 "register_operand" "=&b,&r")
        (and:DI (match_operand:DI 1 "register_operand" "%0,r")
                (match_operand:DI 2 "register_operand" "b,r")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    and\t%0, %1, %2\;and\t%R0, %R1, %R2
    and\t%0, %1, %2\;and\t%R0, %R1, %R2"
    [(set_attr "length" "4,8")]
 )

(define_insn "*ck801_anddi3"
 [(set (match_operand:DI         0 "register_operand" "=&r")
       (and:DI (match_operand:DI 1 "register_operand" "%0")
               (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "and\t%0, %1, %2\;and\t%R0, %R1, %R2"
  [(set_attr "length" "4")]
)


;; -------------------------------------------------------------------------
;; Ior instructions
;; -------------------------------------------------------------------------

(define_expand "iorsi3"
  [(set (match_operand:SI 0 "register_operand" "")
        (ior:SI (match_operand:SI 1 "register_operand" "")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
  {
    if (CONST_INT_P (operands[2])
        && ((CSKY_ISA_FEATURE(E1) && !csky_arith_Uf_operand (operands[2],SImode))
            || (CSKY_ISA_FEATURE(E2)
                && !csky_literal_I_operand (operands[2],SImode)
                && !csky_arith_Uf_operand (operands[2],SImode))))
      {
        operands[2] = copy_to_mode_reg (SImode, operands[2]);
      }
  }")

(define_insn "*cskyv2_iorsi3"
  [(set (match_operand:SI         0 "register_operand"           "=r,b, r, b, r, b,r")
        (ior:SI (match_operand:SI 1 "register_operand"           "%r,0, r, 0, r, 0,r")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "I, Ub,Ub,Uf,Uf,b,r")))]
  "CSKY_ISA_FEATURE(E2)"
  "*{
     switch (which_alternative)
       {
       case 0: return \"ori\t%0, %1, %2\";
       case 1: return \"bseti\t%0, %1, %P2\";
       case 2: return \"bseti\t%0, %1, %P2\";
       case 3: return output_csky_bseti (operands[0], operands[1],
                                         INTVAL (operands[2]));
       case 4: return output_csky_bseti (operands[0], operands[1],
                                         INTVAL (operands[2]));
       case 5: return \"or\t%0, %1, %2\";
       case 6: return \"or\t%0, %1, %2\";
       default: gcc_unreachable ();
       }
  }"
  [(set_attr "length" "4,2,4,4,8,2,4")
   (set_attr "predicable" "yes")
   (set_attr "type" "alu,alu,alu,alu,alu,alu,alu")]
)

(define_insn "*ck801_iorsi3"
  [(set (match_operand:SI         0 "register_operand"      "=b,b, r")
        (ior:SI (match_operand:SI 1 "register_operand"      "%0,0, 0")
                (match_operand:SI 2 "csky_arith_Uf_operand" "Ub,Uf,r")))]
  "CSKY_ISA_FEATURE(E1)"
  "*{
     switch (which_alternative)
       {
       case 0: return \"bseti\t%0, %1, %P2\";
       case 1: return output_csky_bseti (operands[0], operands[1],
                                         INTVAL (operands[2]));
       case 2: return \"or\t%0, %1, %2\";
       default: gcc_unreachable ();
       }
  }"
  [(set_attr "length" "4,2,4")]
)


(define_expand "iordi3"
  [(set (match_operand:DI         0 "register_operand" "")
        (ior:DI (match_operand:DI 1 "register_operand" "")
                (match_operand:DI 2 "register_operand" "")))]
  ""
  ""
)

(define_insn "*cskyv2_iordi3"
  [(set (match_operand:DI         0 "register_operand" "=&r,&r")
        (ior:DI (match_operand:DI 1 "register_operand" "%0, r")
                (match_operand:DI 2 "register_operand" "r,  r")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    or\t%0, %1, %2\;or\t%R0, %R1, %R2
    or\t%0, %1, %2\;or\t%R0, %R1, %R2"
  [(set_attr "length" "8,8")]
)

(define_insn "*ck801_iordi3"
  [(set (match_operand:DI         0 "register_operand" "=&r")
        (ior:DI (match_operand:DI 1 "register_operand" "%0")
                (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "or\t%0, %1, %2\;or\t%R0, %R1, %R2"
  [(set_attr "length" "4")]
)

(define_insn "*cskyv2_norsi3"
  [(set (match_operand:SI                 0 "register_operand" "=b,r")
        (not:SI (ior:SI (match_operand:SI 1 "register_operand" "%0,r")
                        (match_operand:SI 2 "register_operand" "b,r"))))]
  "CSKY_ISA_FEATURE(E2)"
  "nor\t%0, %1, %2"
  [(set_attr "type" "alu,alu")
   (set_attr "predicable" "yes")
   (set_attr "length" "2,4")]
)

;; -------------------------------------------------------------------------
;; Xor instructions
;; -------------------------------------------------------------------------

(define_expand "xorsi3"
  [(set (match_operand:SI 0 "register_operand" "")
        (xor:SI (match_operand:SI 1 "register_operand" "")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
  {
    if (CONST_INT_P(operands[2])
        && (CSKY_ISA_FEATURE(E1) || !csky_arith_O_operand(operands[2],SImode)))
      {
        operands[2] = copy_to_mode_reg (SImode, operands[2]);
      }
  }"
)

(define_insn "*cskyv2_xorsi3"
  [(set (match_operand:SI         0 "register_operand"           "=b,r,r")
        (xor:SI (match_operand:SI 1 "register_operand"           "0,r, r")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "b,r, O")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    xor\t%0, %1, %2
    xor\t%0, %1, %2
    xori\t%0, %1, %2"
  [(set_attr "predicable" "yes")
   (set_attr "length" "2,4,4")]
)

(define_insn "*ck801_xorsi3"
  [(set (match_operand:SI         0 "register_operand"           "=r")
        (xor:SI (match_operand:SI 1 "register_operand"           "0")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "xor\t%0, %1, %2"
)

(define_expand "xordi3"
  [(set (match_operand:DI         0 "register_operand" "")
        (xor:DI (match_operand:DI 1 "register_operand" "")
                (match_operand:DI 2 "register_operand" "")))]
  ""
  ""
)
(define_insn "*cskyv2_xordi3"
  [(set (match_operand:DI         0 "register_operand" "=&r,&r")
        (xor:DI (match_operand:DI 1 "register_operand" "%0, r")
                (match_operand:DI 2 "register_operand" "r,  r")))]
  "CSKY_ISA_FEATURE(E2)"
  "@
    xor\t%0, %1, %2\;xor\t%R0, %R1, %R2
    xor\t%0, %1, %2\;xor\t%R0, %R1, %R2"
  [(set_attr "length" "8,8")]
)

(define_insn "*ck801_xordi3"
  [(set (match_operand:DI         0 "register_operand" "=&r")
        (xor:DI (match_operand:DI 1 "register_operand" "%0")
                (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E1)"
  "xor\t%0, %1, %2\;xor\t%R0, %R1, %R2"
  [(set_attr "length" "4")]
)


;; -------------------------------------------------------------------------
;; Div instructions
;; -------------------------------------------------------------------------

(define_insn "divsi3"
  [(set (match_operand:SI         0 "register_operand" "=r")
        (div:SI (match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(div)"
  "divs\t%0, %1, %2"
  [(set_attr "predicable" "yes")]
)

(define_insn "udivsi3"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (udiv:SI (match_operand:SI 1 "register_operand" "r")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(div)"
  "divu\t%0, %1, %2"
  [(set_attr "predicable" "yes")]
)


;; -----------------------------------------------------------------
;; Multiple load&store insn
;; -----------------------------------------------------------------

(define_expand "load_multiple"
  [(match_par_dup 3 [(set (match_operand:SI 0 "" "")
                          (match_operand:SI 1 "" ""))
                     (use (match_operand:SI 2 "" ""))])]
  "TARGET_MULTIPLE_STLD"
  "{
    int regno, count, i;
    rtx base,src;

    if (GET_CODE (operands[2])    != CONST_INT
        || INTVAL (operands[2])   < 2
        || INTVAL (operands[2])   > CSKY_MAX_MULTIPLE_STLD
        || GET_CODE (operands[1]) != MEM
        || !REG_P (XEXP (operands[1], 0))
        || XEXP (operands[1], 0)  != stack_pointer_rtx
        || GET_CODE (operands[0]) != REG
        || (REGNO (XEXP (operands[1], 0)) > REGNO (operands[0])
            && REGNO (XEXP (operands[1], 0)) < REGNO (operands[0]) + INTVAL (operands[2])))
      FAIL;

    count = INTVAL (operands[2]);
    regno = REGNO (operands[0]);

    operands[3] = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (count));

    base = force_reg (SImode, XEXP(operands[1], 0));
    src = replace_equiv_address (operands[1], base);

    for (i = 0; i < count; i++)
      {
        XVECEXP (operands[3], 0, i) = gen_rtx_SET (gen_rtx_REG (SImode, regno + i),
                                                   adjust_address_nv (src, SImode, i * 4));
      }
  }"
)

(define_expand "store_multiple"
  [(match_par_dup 3 [(set (match_operand:SI 0 "")
                          (match_operand:SI 1 ""))
                     (use (match_operand:SI 2 ""))])]
  "TARGET_MULTIPLE_STLD"
  "{
    int regno, count, i;
    rtx base, dest;

    /* Support only storing a constant number of registers to memory and
       only if at least two registers. */
    if (GET_CODE (operands[2])    != CONST_INT
        || INTVAL (operands[2])   < 2
        || INTVAL (operands[2])   > CSKY_MAX_MULTIPLE_STLD
        || GET_CODE (operands[0]) != MEM
        || !REG_P (XEXP (operands[0], 0))
        || XEXP (operands[0], 0)  != stack_pointer_rtx
        || GET_CODE (operands[1]) != REG
        || (REGNO (XEXP (operands[0], 0)) >= REGNO (operands[1])
            && REGNO (XEXP (operands[0], 0)) < REGNO (operands[1]) + INTVAL (operands[2])))
      FAIL;

    count = INTVAL (operands[2]);
    regno = REGNO (operands[1]);

    operands[3] = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (count));

    base = force_reg (SImode, XEXP(operands[0], 0));
    dest = replace_equiv_address (operands[0], base);

    for(i = 0; i < count; i++)
      {
        XVECEXP (operands[3], 0, i) = gen_rtx_SET (adjust_address_nv (dest, SImode, i * 4),
                                                   gen_rtx_REG (SImode, regno + i));
      }
  }"
)


(define_insn "*csky_ldmsi12"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
     (set (match_operand:SI 10 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 32))))
     (set (match_operand:SI 11 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 36))))
     (set (match_operand:SI 12 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 40))))
     (set (match_operand:SI 13 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 44))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 12"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi11"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
     (set (match_operand:SI 10 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 32))))
     (set (match_operand:SI 11 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 36))))
     (set (match_operand:SI 12 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 40))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 11"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi10"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
     (set (match_operand:SI 10 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 32))))
     (set (match_operand:SI 11 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 36))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 10"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi9"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
     (set (match_operand:SI 10 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 32))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 9"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi8"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
     (set (match_operand:SI 9 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 28))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 8"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi7"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
     (set (match_operand:SI 8 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 24))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 7"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_ldmsi6"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
     (set (match_operand:SI 7 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 20))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 6"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_ldmsi5"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
     (set (match_operand:SI 6 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 16))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 5"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_ldmsi4"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
     (set (match_operand:SI 5 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 12))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 4"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_ldmsi3"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
     (set (match_operand:SI 4 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 8))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 3"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_ldmsi2"
  [(match_parallel          0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "register_operand" "=r")
          (mem:SI (match_operand:SI   2 "register_operand" "r")))
     (set (match_operand:SI 3 "register_operand" "=r")
          (mem:SI (plus:SI (match_dup 2) (const_int 4))))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 2"
  "*{
    static char load_op[256] = {0};
    int count = REGNO (operands[1]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[count];
    sprintf (load_op, \"ldm\t%%1 - %s, (%%2)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_stmsi12"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 32)))
          (match_operand:SI 10 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 36)))
          (match_operand:SI 11 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 40)))
          (match_operand:SI 12 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 44)))
          (match_operand:SI 13 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 12"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi11"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 32)))
          (match_operand:SI 10 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 36)))
          (match_operand:SI 11 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 40)))
          (match_operand:SI 12 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 11"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi10"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 32)))
          (match_operand:SI 10 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 36)))
          (match_operand:SI 11 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 10"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi9"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 32)))
          (match_operand:SI 10 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 9"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi8"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 28)))
          (match_operand:SI 9 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 8"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi7"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 24)))
          (match_operand:SI 8 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 7"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi6"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 20)))
          (match_operand:SI 7 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 6"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)

(define_insn "*csky_stmsi5"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 16)))
          (match_operand:SI 6 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 5"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi4"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 12)))
          (match_operand:SI 5 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 4"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi3"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 8)))
          (match_operand:SI 4 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 3"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


(define_insn "*csky_stmsi2"
  [(match_parallel          0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI   1 "register_operand" "r"))
          (match_operand:SI 2 "register_operand" "r"))
     (set (mem:SI (plus:SI (match_dup 1) (const_int 4)))
          (match_operand:SI 3 "register_operand" "r"))
    ])]
  "TARGET_MULTIPLE_STLD && XVECLEN (operands[0], 0) == 2"
  "*{
    static char load_op[256] = {0};
    int end = REGNO (operands[2]) + XVECLEN (operands[0], 0) - 1;
    const char *reg_rz = reg_names[end];
    sprintf (load_op, \"stm\t%%2 - %s, (%%1)\", reg_rz);
    return load_op;
  }"
)


;; ------------------------------------------------------------------------
;; Jump and linkage insns
;; ------------------------------------------------------------------------

(define_expand "tablejump"
  [(parallel [(set (pc) (match_operand:SI 0 "register_operand" "r"))
              (use (label_ref (match_operand 1 "" "")))])]
  ""
  "
  {
    if (flag_pic)
      {
        operands[0] = expand_simple_binop (Pmode, PLUS, operands[0],
                                           pic_offset_table_rtx, NULL_RTX,
                                           1, OPTAB_DIRECT);
      }
  }"
)

(define_insn "*tablejump"
  [(set (pc) (match_operand:SI    0 "register_operand" "b,r"))
   (use (label_ref (match_operand 1 ""                 "")))]
  ""
  "jmp\t%0"
  [(set_attr "length" "2,4")
   (set_attr "type"   "branch_jmp,branch_jmp")
   (set_attr "isa"    "def,2e3")]
)

(define_expand "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  ""
)

(define_insn "*csky_jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  "CSKY_ISA_FEATURE(E2)"
  "*
  {
    if (get_attr_far_jump (insn) == FAR_JUMP_YES)
      {
        if (CSKY_ISA_FEATURE(2E3))
          return \"jmpi\\t%l0\";
        else
          return \"bsr\\t%l0\\t//too far jump\";
      }
    return \"jbr\\t%l0\";
  }"
  [(set_attr "type" "branch")
   (set (attr "length")
        (if_then_else (and (ge (minus (match_dup 0) (pc)) (const_int -1024))
                           (le (minus (match_dup 0) (pc)) (const_int 1022)))
                      (const_int 2)
                      (const_int 4)))
   (set (attr "far_jump")
        (if_then_else (and (ge (minus (match_dup 0) (pc)) (const_int -65536))
                           (le (minus (match_dup 0) (pc)) (const_int 65532)))
                      (const_string "no")
                      (const_string "yes")))]
)

;;FIXME the length of bsr is not really 5, it's used to distinguish
;;      from br32, use a better way here.
(define_insn "*ck801_jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  "CSKY_ISA_FEATURE(E1)"
  "*{
    if (get_attr_length(insn) != 5)
      return \"jbr\\t%l0\";
    else
      return \"bsr\\t%l0\\t//too far jump\";
  }"
  [(set_attr "type" "branch")
   (set (attr "far_jump")
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
  "jmp\t%0"
  [(set_attr "length" "2,4")
   (set_attr "type"   "branch_jmp,branch_jmp")
   (set_attr "isa"    "def,2e3")]
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

     if (CSKY_ISA_FEATURE(2E3)
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
  [(set (pc) (if_then_else (ne (reg:CC CSKY_CC_REGNUM) (const_int 0))
                           (label_ref (match_operand 0 "" ""))
                           (pc)))]
  "CSKY_ISA_FEATURE(E2)"
  "*
  {
    if (get_attr_far_jump (insn) == FAR_JUMP_YES)
      {
        if (CSKY_ISA_FEATURE(2E3))
          return \"jbf\\t.LCB%=\;jmpi\\t%l0\\t//too far jump\\n.LCB%=:\";
        else
          return \"jbf\\t.LCB%=\;bsr\\t%l0\\t//too far jump\\n.LCB%=:\";
      }
    return \"jbt\\t%l0\";
  }"
  [(set_attr "type" "cbranch")
   (set (attr "far_jump")
        (if_then_else (eq_attr "length" "6")
                      (const_string "yes")
                      (const_string "no")))
   (set (attr "length")
        (if_then_else (and (ge (minus (match_dup 0) (pc)) (const_int -1024))
                           (le (minus (match_dup 0) (pc)) (const_int 1022)))
                      (const_int 2)
                      (if_then_else (and (ge (minus (match_dup 0) (pc)) (const_int -65536))
                                         (le (minus (match_dup 0) (pc)) (const_int 65532)))
                                    (const_int 4)
                                    (const_int 6))))]
)

(define_insn "csky_jbf"
  [(set (pc) (if_then_else (eq (reg:CC CSKY_CC_REGNUM) (const_int 0))
                           (label_ref (match_operand 0 "" ""))
                           (pc)))]
  "CSKY_ISA_FEATURE(E2)"
  "*
  {
    if (get_attr_far_jump (insn) == FAR_JUMP_YES)
      {
        if (CSKY_ISA_FEATURE(2E3))
          return \"jbt\\t.LCB%=\;jmpi\\t%l0\\t//too far jump\\n.LCB%=:\";
        else
          return \"jbt\\t.LCB%=\;bsr\\t%l0\\t//too far jump\\n.LCB%=:\";
      }
    return \"jbf\\t%l0\";
  }"
  [(set_attr "type" "cbranch")
   (set (attr "far_jump")
        (if_then_else (eq_attr "length" "6")
                      (const_string "yes")
                      (const_string "no")))
   (set (attr "length")
        (if_then_else (and (ge (minus (match_dup 0) (pc)) (const_int -1024))
                           (le (minus (match_dup 0) (pc)) (const_int 1022)))
                      (const_int 2)
                      (if_then_else (and (ge (minus (match_dup 0) (pc)) (const_int -65536))
                                         (le (minus (match_dup 0) (pc)) (const_int 65532)))
                                    (const_int 4)
                                    (const_int 6))))]
)

;;FIXME the length of bsr is not really 7, it's used to distinguish
;;      from br32, use a better way here.
(define_insn "ck801_jbt"
  [(set (pc) (if_then_else (ne (reg:CC CSKY_CC_REGNUM) (const_int 0))
                           (label_ref (match_operand 0 "" ""))
                           (pc)))]
  "CSKY_ISA_FEATURE(E1)"
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
  [(set_attr "type" "cbranch")
   (set (attr "far_jump")
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
  [(set (pc) (if_then_else (eq (reg:CC CSKY_CC_REGNUM) (const_int 0))
                           (label_ref (match_operand 0 "" ""))
                           (pc)))]
  "CSKY_ISA_FEATURE(E1)"
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
  [(set_attr "type" "cbranch")
   (set (attr "far_jump")
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
  "CSKY_ISA_FEATURE(2E3)"
  "<inst>\t%0, %l1"
  [(set_attr "type" "cbranch")]
)

;; ------------------------------------------------------------------------
;; return insns
;; ------------------------------------------------------------------------

(define_insn "*csky_simple_return"
  [(simple_return)]
  "reload_completed"
  "*
    return output_csky_return_instruction();
  "
)

(define_expand "eh_return"
  [(use (match_operand 0 "general_operand" ""))]
  ""
  "{
    emit_insn (gen_csky_eh_return (operands[0]));
    DONE;
  }
  "
)

;; We can't expand this before we know where the link register is stored.
(define_insn_and_split "csky_eh_return"
  [(unspec_volatile [(match_operand:SI 0 "register_operand" "r")]
                    VUNSPEC_EH_RETURN)
   (clobber (match_scratch:SI 1 "=&r"))]
  ""
  "#"
  "&& reload_completed"
  [(const_int 0)]
  "{
    set_csky_return_address (operands[0], operands[1]);
    DONE;
  }"
)

;; -------------------------------------------------------------------------
;; SImode signed integer comparisons
;; -------------------------------------------------------------------------

(define_insn "*cmpnesi_r"
  [(set (reg:CC CSKY_CC_REGNUM) (ne:CC (match_operand:SI 0 "register_operand" "b,r")

                           (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmpne\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "type"   "cmp,cmp")
   (set_attr "isa"    "def,2e3")]
)

;;cmpnei is 0-31 for Smart MODE
(define_insn "*smart_cmpnesi_i"
  [(set (reg:CC CSKY_CC_REGNUM)  (ne:CC (match_operand:SI 0 "register_operand"       "a")
                            (match_operand:SI 1 "csky_literal_K_operand" "K")))]
  "CSKY_ISA_FEATURE(smart) || CSKY_ISA_FEATURE(E1)"
  "cmpnei\t%0, %1"
  [(set_attr "type" "cmp")
   (set_attr "length" "2")]
)

;;cmpnei is 0 - 65536 for Fast MODE
(define_insn "*fast_cmpnesi_i"
  [(set (reg:CC CSKY_CC_REGNUM) (ne:CC (match_operand:SI 0 "register_operand"       "a,r")
                           (match_operand:SI 1 "csky_literal_I_operand" "K,I")))]
  "!CSKY_ISA_FEATURE(smart) && CSKY_ISA_FEATURE(E2)"
  "cmpnei\t%0, %1"
  [(set_attr "type" "cmp")
   (set_attr "length" "2,4")]
)

(define_insn "*cmpgtsi"
  [(set (reg:CC CSKY_CC_REGNUM) (gt:CC (match_operand:SI 0 "register_operand" "b,r")
                           (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmplt\t%1, %0"
  [(set_attr "length" "2,4")
   (set_attr "type"   "cmp,cmp")
   (set_attr "isa"    "def,2e3")]
)

(define_insn "*cmpltsi_r"
  [(set (reg:CC CSKY_CC_REGNUM) (lt:CC (match_operand:SI 0 "register_operand" "b,r")
                           (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmplt\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "type"   "cmp,cmp")
   (set_attr "isa"    "def,2e3")]
)

;;cmplti is 1-32 for Smart MODE
(define_insn "*smart_cmpltsi_i"
  [(set (reg:CC CSKY_CC_REGNUM) (lt:CC (match_operand:SI 0 "register_operand"       "a")
                           (match_operand:SI 1 "csky_literal_J_operand" "J")))]
  "CSKY_ISA_FEATURE(smart) || CSKY_ISA_FEATURE(E1)"
  "cmplti\t%0, %1"
  [(set_attr "length" "2")
   (set_attr "type" "cmp")]
)


;;cmplti is 1-65536 for Fast MODE
(define_insn "*fast_cmpltsi_i"
  [(set (reg:CC CSKY_CC_REGNUM) (lt:CC (match_operand:SI 0 "register_operand"        "a,r")
                           (match_operand:SI 1 "csky_literal_Uk_operand" "J,Uk")))]
  "!CSKY_ISA_FEATURE(smart) && CSKY_ISA_FEATURE(E2)"
  "cmplti\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "type" "cmp")]
)

; covers cmplti x,0
(define_insn "*cskyv2_cmpltsi_0"
  [(set (reg:CC CSKY_CC_REGNUM) (lt:CC (match_operand:SI 0 "register_operand" "a,r")
                           (const_int 0)))]
  "CSKY_ISA_FEATURE(E2)"
  "btsti\t%0, 31"
  [(set_attr "type" "cmp")
   (set_attr "length" "2,4")]
)

(define_insn "*ck801_cmpltsi_0"
  [(set (reg:CC CSKY_CC_REGNUM) (lt:CC (match_operand:SI 0 "register_operand" "a")
                           (const_int 0)))]
  "CSKY_ISA_FEATURE(E1)"
  "btsti\t%0, 31"
  [(set_attr "type" "cmp")]
)

(define_insn "*cskyv2_tstsi2"
  [(set (reg:CC CSKY_CC_REGNUM) (ne:CC (and:SI (match_operand:SI 0 "register_operand" "b,r")
                                               (match_operand:SI 1 "register_operand" "b,r"))
                                       (const_int 0)))]
  "CSKY_ISA_FEATURE(E2)"
  "tst\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "type" "cmp,cmp")]
)

;; -------------------------------------------------------------------------
;; SImode unsigned integer comparisons
;; -------------------------------------------------------------------------

(define_insn "*cmpgeusi_r"
  [(set (reg:CC CSKY_CC_REGNUM) (geu:CC (match_operand:SI 0 "register_operand" "b,r")
                            (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmphs\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "type"   "cmp,cmp")
   (set_attr "isa"    "def,2e3")]
)

(define_insn "*smart_cmpgeusi_i"
  [(set (reg:CC CSKY_CC_REGNUM) (geu:CC (match_operand:SI 0 "register_operand"       "a")
                            (match_operand:SI 1 "csky_literal_J_operand" "J")))]
  "CSKY_ISA_FEATURE(smart) || CSKY_ISA_FEATURE(E1)"
  "cmphsi\t%0, %1"
  [(set_attr "length" "2")
   (set_attr "type" "cmp")]
)

(define_insn "*fast_cmpgeusi_i"
  [(set (reg:CC CSKY_CC_REGNUM) (geu:CC (match_operand:SI 0 "register_operand"        "a,r")
                            (match_operand:SI 1 "csky_literal_Uk_operand" "J,Uk")))]
  "!CSKY_ISA_FEATURE(smart) && CSKY_ISA_FEATURE(E2)"
  "cmphsi\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "type" "cmp")]
)

(define_insn "*cmpleusi"
  [(set (reg:CC CSKY_CC_REGNUM) (leu:CC (match_operand:SI 0 "register_operand" "b,r")
                            (match_operand:SI 1 "register_operand" "b,r")))]
  ""
  "cmphs\t%1, %0"
  [(set_attr "length" "2,4")
   (set_attr "type"   "cmp,cmp")
   (set_attr "isa"    "def,2e3")]
)

;; -------------------------------------------------------------------------
;; Function call insns
;; -------------------------------------------------------------------------

(define_expand "call"
  [(parallel [(call (match_operand:SI 0 "" "") (match_operand 1 "" ""))
              (clobber (reg:SI 15))])]
  ""
  "{
    rtx pic_ref;
    rtx addr_ref = XEXP (operands[0], 0);

    if (flag_pic
        && (CONSTANT_P (addr_ref)
            || symbol_mentioned_p (addr_ref)
            || label_mentioned_p (addr_ref)))
      {
        pic_ref = legitimize_pic_address (addr_ref, 0, 0);
        operands[0] = gen_rtx_MEM (GET_MODE (pic_ref), pic_ref);
      }

     if (GET_CODE (operands[0]) == MEM
         && ! register_operand (XEXP (operands[0], 0), SImode)
         && ! symbolic_csky_address_p (XEXP (operands[0], 0))
         && ! (flag_pic && csky_unspec_operand(XEXP (operands[0], 0), SImode)))
    {
      operands[0] = gen_rtx_MEM (GET_MODE (operands[0]),
                                 force_reg (Pmode, XEXP (operands[0], 0)));
    }
  }"
)


(define_insn "*call_internal"
  [(call (mem:SI (match_operand:SI 0 "csky_call_address_operand" "b,r,S"))
         (match_operand 1 "" ""))
   (clobber (reg:SI 15))]
  ""
  "@
    jsr\t%0
    jsr\t%0
    jbsr\t%0"
  [(set_attr "length" "2,4,4")
   (set_attr "type"   "call_jsr,call_jsr,call")
   (set_attr "isa"    "def,2e3,def")]
)

(define_insn "*call_internal_pic"
  [(call (mem:SI (match_operand:SI 0 "csky_unspec_operand" "X"))
         (match_operand            1 "" ""))
  (clobber (reg:SI 15))]
  "flag_pic"
  "* return csky_output_call (operands, 0);"
  [(set_attr "length" "4")]
)

(define_expand "call_value"
  [(parallel [(set (match_operand 0 "register_operand" "")
                   (call (match_operand:SI 1 "" "") (match_operand 2 "" "")))
              (clobber (reg:SI 15))])]
  ""
  "{
    rtx pic_ref;
    rtx addr_ref = XEXP (operands[1], 0);

    if (flag_pic
        && (CONSTANT_P (addr_ref)
            || symbol_mentioned_p (addr_ref)
            || label_mentioned_p (addr_ref)))
      {
        pic_ref = legitimize_pic_address (addr_ref, 0, 0);
        operands[1] = gen_rtx_MEM (GET_MODE (pic_ref), pic_ref);
      }

     if (GET_CODE (operands[1]) == MEM
         && ! register_operand (XEXP (operands[1], 0), SImode)
         && ! symbolic_csky_address_p (XEXP (operands[1], 0))
         && ! (flag_pic && csky_unspec_operand(XEXP (operands[1], 0), SImode)))
    {
      operands[1] = gen_rtx_MEM (GET_MODE (operands[1]),
                                 force_reg (Pmode, XEXP (operands[1], 0)));
    }
  }")

;; Call subroutine returning any type.

(define_expand "untyped_call"
  [(parallel [(call (match_operand 0 "" "")
        (const_int 0))
        (match_operand 1 "" "")
        (match_operand 2 "" "")])]
  "TARGET_HARD_FLOAT_ABI"
{
  int i;

  emit_call_insn (gen_call (operands[0], const0_rtx));

  for (i = 0; i < XVECLEN (operands[2], 0); i++)
    {
      rtx set = XVECEXP (operands[2], 0, i);
      emit_move_insn (SET_DEST (set), SET_SRC (set));
    }

  /* The optimizer does not know that the call sets the function value
     registers we stored in the result block.  We avoid problems by
     claiming that all hard registers are used and clobbered at this
     point.  */
  emit_insn (gen_blockage ());

  DONE;
})

;; UNSPEC_VOLATILE is considered to use and clobber all hard registers and
;; all of memory.  This blocks insns from being moved across this point.

(define_insn "blockage"
  [(unspec_volatile [(const_int 0)] VUNSPEC_BLOCKAGE)]
  ""
  ""
  [(set_attr "length" "0")])

(define_insn "*call_value_internal_vect"
  [(set (match_operand:VANY             0 "register_operand"          "=v,v,v")
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "b, r,S"))
              (match_operand 2 "" "")))
   (clobber (reg:SI 15))]
  "CSKY_ISA_FEATURE(vdsp)"
  "@
    jsr\t%1
    jsr\t%1
    jbsr\t%1"
  [(set_attr "length" "2,4,4")
   (set_attr "type"   "call_jsr,call_jsr,call")]
)

(define_insn "*call_value_internal_vs"
  [(set (match_operand:SF               0 "register_operand"          "=v,v,v")
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "b, r,S"))
              (match_operand 2 "" "")))
   (clobber (reg:SI 15))]
  "TARGET_HARD_FLOAT_ABI"
  "@
    jsr\t%1
    jsr\t%1
    jbsr\t%1"
  [(set_attr "length" "2,4,4")
   (set_attr "type"   "call_jsr,call_jsr,call")
   (set_attr "isa"    "def,2e3,def")]
)

(define_insn "*call_value_internal_vd"
  [(set (match_operand:DF               0 "register_operand"          "=v,v,v")
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "b, r,S"))
              (match_operand 2 "" "")))
   (clobber (reg:SI 15))]
  "TARGET_HARD_FLOAT_ABI && csky_fpu_index != TARGET_FPU_fpv2_sf"
  "@
    jsr\t%1
    jsr\t%1
    jbsr\t%1"
  [(set_attr "length" "2,4,4")
   (set_attr "type"   "call_jsr,call_jsr,call")]
)

(define_insn "*call_value_internal"
  [(set (match_operand                  0 "register_operand"          "=r,r,r")
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "b, r,S"))
              (match_operand 2 "" "")))
   (clobber (reg:SI 15))]
  ""
  "@
    jsr\t%1
    jsr\t%1
    jbsr\t%1"
  [(set_attr "length" "2,4,4")
   (set_attr "type"   "call_jsr,call_jsr,call")
   (set_attr "isa"    "def,2e3,def")]
)

(define_insn "*call_value_internal_pic_vs"
  [(set (match_operand:SF               0 "register_operand"    "=v")
        (call (mem:SI (match_operand:SI 1 "csky_unspec_operand" "X"))
                      (match_operand    2 "" "")))
   (clobber (reg:SI 15))]
  "flag_pic && TARGET_HARD_FLOAT_ABI"
  "* return csky_output_call (operands, 1);"
)

(define_insn "*call_value_internal_pic_vd"
  [(set (match_operand:DF               0 "register_operand"    "=v")
        (call (mem:SI (match_operand:SI 1 "csky_unspec_operand" "X"))
                      (match_operand    2 "" "")))
   (clobber (reg:SI 15))]
  "flag_pic && TARGET_HARD_FLOAT_ABI && csky_fpu_index != TARGET_FPU_fpv2_sf"
  "* return csky_output_call (operands, 1);"
)

(define_insn "*call_value_internal_pic"
  [(set (match_operand                  0 "register_operand"    "=r")
        (call (mem:SI (match_operand:SI 1 "csky_unspec_operand" "X"))
                      (match_operand    2 "" "")))
   (clobber (reg:SI 15))]
  "flag_pic"
  "* return csky_output_call (operands, 1);"
)

(define_insn "*call_value_struct"
  [(set (match_parallel 0 "" [(expr_list (match_operand 3 "register_operand" "")
                                         (match_operand 4 "immediate_operand" ""))
                              (expr_list (match_operand 5 "register_operand" "")
                                         (match_operand 6 "immediate_operand" ""))])
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "b,r,S"))
              (match_operand 2 "" "")))
        (clobber (reg:SI 15))]
  ""
  "@
    jsr\t%1
    jsr\t%1
    jbsr\t%1"
  [(set_attr "length" "2,4,4")
   (set_attr "type"   "call_jsr,call_jsr,call")
   (set_attr "isa"    "def,2e3,def")]
)

(define_insn "*call_value_struct_pic"
  [(set (match_parallel 0 "" [(expr_list (match_operand 3 "register_operand"  "")
                                         (match_operand 4 "immediate_operand" ""))
                              (expr_list (match_operand 5 "register_operand"  "")
                                         (match_operand 6 "immediate_operand" ""))])
        (call (mem:SI (match_operand:SI 1 "csky_unspec_operand" "X"))
                      (match_operand    2 "" "")))
   (clobber (reg:SI 15))]
  "flag_pic"
  "* return csky_output_call (operands, 1);"
)


;; -------------------------------------------------------------
;; prologue & epilogue
;; -------------------------------------------------------------

(define_expand "prologue"
  [(clobber (const_int 0))]
  ""
  "{
    csky_expand_prologue ();
    DONE;
  }"
)

(define_expand "epilogue"
  [(clobber (const_int 0))]
  ""
  "{
    /* Prevent optimaze */
    if (crtl->calls_eh_return)
      emit_insn (gen_force_register_use (gen_rtx_REG (Pmode, 2)));

    csky_expand_epilogue();
    DONE;
  }"
)

(define_insn "*epilogue_insns"
  [(unspec_volatile [(return)] FLAG_EPILOGUE)]
  ""
  "*
    return csky_unexpanded_epilogue();
  "
  [(set (attr "length")
        (symbol_ref "csky_get_unexpanded_epilogue_length ()"))]
)

/* TODO: pushpop */
;; Push multiple registers to the stack.  Registers are in parallel (use ...)
;; expressions.  For simplicity, the first register is also in the unspec
;; part.
;; To avoid the usage of GNU extension, the length attribute is computed
;; in a C function arm_attr_length_push_multi.
(define_insn "*push_multi"
  [(match_parallel 2 "registers_push"
    [(set (match_operand:BLK 0 "push_memory_operand" "")
          (unspec:BLK [(match_operand:SI 1 "register_operand" "")]
            UNSPEC_PUSHPOP_MULT))])]
  ""
  "*
  {
    int num_saves = XVECLEN (operands[2], 0);

    int i;
    char pattern[100];

    strcpy (pattern, \"push\\t%1\");

    for (i = 1; i < num_saves; i++)
      {
        strcat (pattern, \", \");
        strcat (pattern,
            reg_names[REGNO (XEXP (XVECEXP (operands[2], 0, i), 0))]);
      }

    output_asm_insn (pattern, operands);

    return \"\";
  }"
  [(set (attr "length")
        (symbol_ref "get_csky_pushpop_length (operands)"))]
)

;; Pop (as used in epilogue RTL)
;;
(define_insn "*pop_multi"
  [(match_parallel 2 "registers_pop"
    [(return)
     (set (match_operand:SI 1 "register_operand" "")
          (unspec:SI [(match_operand:SI 0 "pop_memory_operand" "")]
            UNSPEC_PUSHPOP_MULT))])]
  ""
  "*
  {
    int num_saves = XVECLEN (operands[2], 0);

    int i;
    char pattern[100];

    strcpy (pattern, \"pop\\t%1\");

    for (i = 2; i < num_saves; i++)
      {
        strcat (pattern, \", \");
        strcat (pattern,
            reg_names[REGNO (XEXP (XVECEXP (operands[2], 0, i), 0))]);
      }

    output_asm_insn (pattern, operands);

    return \"\";
  }"
  [(set (attr "length")
        (symbol_ref "get_csky_pushpop_length (operands)"))]
)


;; -------------------------------------------------------------------------
;; PIC related insns
;; -------------------------------------------------------------------------

(define_insn "prologue_get_pc"
  [(set (reg:SI 28)
        (match_operand:SI 0 "" "X"))]
  "(GET_CODE(operands[0]) == UNSPEC)
   && (XINT(operands[0], 1) == PIC_SYMBOL_GOTPC_GRS)"
  "*{
    operands[0] = XVECEXP(operands[0], 0, 0);
    output_asm_insn(\"grs\tgb, %0\", operands);
    default_internal_label (asm_out_file, \"L\",
                            CODE_LABEL_NUMBER (XEXP(operands[0], 0)));
    return \"\";
  }"
)

(define_insn "*pic_got_pc"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_GOTPC))]
  "flag_pic"
  "lrw\t%0, %1@GOTPC"
)

(define_insn "*pic_symbol_gotoff"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_GOTOFF))]
  "flag_pic"
  "lrw\t%0, %1@GOTOFF"
)

(define_insn "*pic_symbol_got"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_GOT))]
  "flag_pic"
  "lrw\t%0, %1@GOT"
)

(define_insn "*pic_symbol_plt"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_PLT))]
  "flag_pic"
  "lrw\t%0, %1@PLT"
)

(define_insn "*pic_symbol_grs"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "" "")] PIC_SYMBOL_GRS))]
  "flag_pic"
  "grs\t%0, %1"
)

(define_expand "builtin_setjmp_receiver"
  [(label_ref (match_operand 0 "" ""))]
  "flag_pic"
  "{
    rtx l1 = gen_label_rtx();
    rtx grs_label = gen_rtx_LABEL_REF(SImode, l1);
    rtx reg_gb = gen_rtx_REG(SImode, PIC_OFFSET_TABLE_REGNUM);
    rtx reg_temp = gen_rtx_REG(SImode, 12);

    rtx tmp0_unspec = gen_rtx_UNSPEC (Pmode,
                                      gen_rtvec (1, grs_label),
                                      PIC_SYMBOL_GOTPC_GRS);
    rtx tmp1_unspec = gen_rtx_UNSPEC (Pmode,
                                      gen_rtvec (1, grs_label),
                                      PIC_SYMBOL_GOTPC);

    emit_insn (gen_prologue_get_pc(tmp0_unspec));
    emit_move_insn(reg_temp, tmp1_unspec);
    emit_insn(gen_addsi3(reg_gb, reg_gb, reg_temp));
    emit_use (reg_gb);

    DONE;
  }"
)

;; -------------------------------------------------------------------------
;; TLS related insns
;; -------------------------------------------------------------------------

;;TODO split insn in rtx.
(define_insn "tls_do_add_pc"
  [(set (match_operand:SI             0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (const_int 8)
                    (match_operand    2 "" "")]
                   UNSPEC_TLS_BASE))
   (clobber (match_scratch:SI         3 "=&r"))]
  "CSKY_ISA_FEATURE(tls)"
  "*
    output_asm_insn(\"grs\t%3, .LTLS%2\", operands);
    output_asm_insn(\"addu\t%0, %1, %3\", operands);
    return \"\";
  "
  [(set_attr "length" "8")]
)

(define_insn "*tls_get_symbol_1"
  [(set (match_operand:SI                      0 "register_operand" "=r")
        (unspec:SI [(match_operand             1 "" "")
                    (match_operand             2 "" "")
                    (unspec:SI [(match_operand 3 "" "")] UNSPEC_TLS_LABEL)]
                   UNSPEC_TLS))]
  "CSKY_ISA_FEATURE(tls)"
  "*
    default_internal_label (asm_out_file, \"LTLS\", INTVAL (operands[3]));
    switch (INTVAL (operands[2]))
      {
      case TLS_GD32:
        return \"lrw\t%0, %1@TLSGD32\";
      case TLS_LDM32:
        return \"lrw\t%0, %1@TLSLDM32\";
      case TLS_IE32:
        return \"lrw\t%0, %1@GOTTPOFF\";
      default:
        return \"\";
      }
  "
)

(define_insn "*tls_get_symbol_2"
  [(set (match_operand:SI          0 "register_operand" "=r")
        (unspec:SI [(match_operand 1 "" "")
                    (match_operand 2 "" "")]
                   UNSPEC_TLS))]
  "CSKY_ISA_FEATURE(tls)"
  "*
    switch (INTVAL (operands[2]))
      {
      case TLS_LE32:
        return \"lrw\t%0, %1@TPOFF\";
      case TLS_LDO32:
        return \"lrw\t%0, %1@TLSLDO32\";
      default:
        return \"\";
      }
  "
)

(define_insn "load_tp_hard"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(const_int 0)] UNSPEC_TLS))]
  "CSKY_ISA_FEATURE(tls) && TARGET_HARD_TP"
  "mov\t%0, tls"
  [(set_attr "length" "2")]
)

;; Do not clobber r1-r3, must use r0 for the first operand.
(define_insn "load_tp_soft"
  [(set     (reg:SI CSKY_FIRST_RET_REG)
            (unspec:SI [(const_int 0)] UNSPEC_TLS))
   (clobber (reg:SI CSKY_LR_REGNUM))
   (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(tls) && TARGET_SOFT_TP"
  "jbsr\t__read_tp"
)

(define_insn "load_tp_soft_pic"
  [(set (reg:SI CSKY_FIRST_RET_REG)
        (unspec:SI [(const_int 0)] UNSPEC_TLS))
   (use (reg:SI CSKY_GB_REGNUM))
   (clobber (reg:SI CSKY_LR_REGNUM))
   (clobber (reg:CC CSKY_CC_REGNUM))]
  "flag_pic && CSKY_ISA_FEATURE(tls) && TARGET_SOFT_TP"
  "lrw\tr0, __read_tp@PLT\;addu\tr0, gb\;ld.w\tr0, (r0, 0)\;jsr\tr0"
)


;; -------------------------------------------------------------
;; Misc insns
;; -------------------------------------------------------------

(define_insn "nop"
  [(const_int 0)]
  ""
  "or\tr0, r0, r0"
  [(set_attr "length" "2")]
)

(define_insn "force_register_use"
  [(unspec:SI [(match_operand:SI 0 "register_operand" "")] UNSPEC_REGISTER_USE)]
  ""
  "# %0 needed"
  [(set_attr "length" "0")]
)

(define_insn "trap"
  [(trap_if (const_int 1) (const_int 0))]
  ""
  "bkpt"
  [(set (attr "length") (const_int 2))
   (set_attr "type" "alu")]
)

;;
;; Stack allocation -- in particular, for alloca().
;; this is *not* what we use for entry into functions.
;;
;; This is how we allocate stack space.  If we are allocating a
;; constant amount of space and we know it is less than 4096
;; bytes, we need do nothing.
;;
;; If it is more than 4096 bytes, we need to probe the stack
;; periodically.
;;
;; operands[1], the distance is a POSITIVE number indicating that we
;; are allocating stack space
;;

(define_expand "allocate_stack"
  [(set (reg:SI 0)
        (plus:SI (reg:SI 0)
                 (match_operand:SI 1 "general_operand" "")))
   (set (match_operand:SI 0 "register_operand" "=r")
        (match_dup 2))]
  ""
  "{
    /* If he wants no probing, just do it for him.  */
    if (csky_stack_increment == 0)
      {
        emit_insn (gen_addsi3 (stack_pointer_rtx,
                               stack_pointer_rtx, operands[1]));
        emit_move_insn (operands[0], virtual_stack_dynamic_rtx);
        DONE;
      }

    /* For small constant growth, we unroll the code.  */
    if (GET_CODE (operands[1]) == CONST_INT
        && INTVAL (operands[1]) < 8 * CSKY_STACK_UNITS_MAXSTEP)
      {
        HOST_WIDE_INT left = INTVAL(operands[1]);

        /* If it's a long way, get close enough for a last shot.  */
        if (left >= CSKY_STACK_UNITS_MAXSTEP)
          {
            rtx tmp = gen_reg_rtx (Pmode);
            emit_insn (gen_movsi (tmp, GEN_INT (CSKY_STACK_UNITS_MAXSTEP)));

            do
            {
              rtx memref = gen_rtx_MEM (SImode, stack_pointer_rtx);
              MEM_VOLATILE_P (memref) = 1;
              emit_insn (gen_subsi3 (stack_pointer_rtx,
                                     stack_pointer_rtx,
                                     tmp));
              emit_insn (gen_movsi (memref, stack_pointer_rtx));
              left -= CSKY_STACK_UNITS_MAXSTEP;
            } while (left > CSKY_STACK_UNITS_MAXSTEP);
          }

        /* Perform the final adjustment.  */
        emit_insn (gen_addsi3 (stack_pointer_rtx,
                               stack_pointer_rtx,
                               GEN_INT (-left)));
        emit_move_insn (operands[0], virtual_stack_dynamic_rtx);
        DONE;
      }
    else
      {
        rtx out_label = 0;
        rtx loop_label = gen_label_rtx ();
        rtx step = gen_reg_rtx (Pmode);
        rtx tmp = gen_reg_rtx (Pmode);
        rtx test, memref;

        emit_insn (gen_movsi (tmp, operands[1]));
        emit_insn (gen_movsi (step, GEN_INT (CSKY_STACK_UNITS_MAXSTEP)));

        if (GET_CODE (operands[1]) != CONST_INT)
          {
            out_label = gen_label_rtx ();
            test = gen_rtx_GEU (VOIDmode, step, tmp);   /* quick out */
            emit_jump_insn (gen_cbranchsi4 (test, step, tmp, out_label));
          }

        /* Run a loop that steps it incrementally.  */
        emit_label (loop_label);

        /* Extend a step, probe, and adjust remaining count.  */
        emit_insn(gen_subsi3(stack_pointer_rtx, stack_pointer_rtx, step));
        memref = gen_rtx_MEM (SImode, stack_pointer_rtx);
        MEM_VOLATILE_P (memref) = 1;
        emit_insn(gen_movsi(memref, stack_pointer_rtx));
        emit_insn(gen_subsi3(tmp, tmp, step));

        /* Loop condition -- going back up.  */
        test = gen_rtx_LTU (VOIDmode, step, tmp);
        emit_jump_insn (gen_cbranchsi4 (test, step, tmp, loop_label));

        if (out_label)
          emit_label (out_label);

        /* Bump the residual.  */
        emit_insn (gen_subsi3 (stack_pointer_rtx, stack_pointer_rtx, tmp));
        emit_move_insn (operands[0], virtual_stack_dynamic_rtx);
        DONE;
      }
  }"
)


;; -------------------------------------------------------------
;; Special patterns for dealing with the constant pool
;; -------------------------------------------------------------

(define_insn "align_4"
  [(unspec_volatile [(const_int 0)] VUNSPEC_ALIGN)]
  ""
  "*
  assemble_align(32);
  return \"\";
  "
  [(set_attr "length" "0")]
)

(define_insn "csky_constpool_label"
  [(unspec_volatile [(match_operand 0 "" "")] VUNSPEC_POOL_LABEL)]
  ""
  "*
  {
    char tmp_label[15];
    ASM_GENERATE_INTERNAL_LABEL(tmp_label, \"LCP\", INTVAL(operands[0]));
    assemble_label(asm_out_file, tmp_label);
    return \"\";
  }"
  [(set_attr "length" "0")]
)

(define_insn "consttable_4"
  [(unspec_volatile [(match_operand 0 "" "")] VUNSPEC_POOL_4)]
  ""
  "*
  assemble_integer(operands[0], 4, BITS_PER_WORD, 1);
  mark_symbol_refs_as_used(operands[0]);
  return \"\";
  "
  [(set_attr "length" "4")]
)

(define_insn "consttable_8"
  [(unspec_volatile [(match_operand 0 "" "")] VUNSPEC_POOL_8)]
  ""
  "*
  {
    assemble_integer (operands[0], 8, BITS_PER_WORD, 1);
    return \"\";
  }"
  [(set_attr "length" "8")]
)

;;FIXME record the deferred symbol_ref information with use insn
(define_insn "*cskyv2_use_symbol_ref"
 [(unspec_volatile [(match_operand 0 "" "")] VUNSPEC_SYMBOL_REF)]
 ""
 ""
 [(set_attr "length" "0")]
)


;; ------------------------------------------------------------
;; switch case optimize
;; ------------------------------------------------------------

(define_expand "casesi"
  [(match_operand:SI 0 "register_operand" "")   ; index to jump on
   (match_operand:SI 1 "const_int_operand" "")  ; lower bound
   (match_operand:SI 2 "const_int_operand" "")  ; total range        (max - min)
   (match_operand:SI 3 "" "")                   ; table label
   (match_operand:SI 4 "" "")]                  ; Out of range label (default:)
  "optimize_size && CSKY_ISA_FEATURE(casesi)"
  "{
    enum insn_code code;
    if (operands[1] != const0_rtx)
      {
        rtx reg = gen_reg_rtx (SImode);
        emit_insn (gen_subsi3 (reg,
                               operands[0],
                               GEN_INT (INTVAL (operands[1]))));
        operands[0] = reg;
      }

    code = CODE_FOR_csky_casesi_internal;

    if (!insn_data[(int) code].operand[1].predicate(operands[2], SImode))
      operands[2] = force_reg (SImode,operands[2]);

    emit_jump_insn (GEN_FCN ((int) code) (operands[0],operands[2],
                    operands[3],operands[4]));
    DONE;
  }"
)

(define_expand "csky_casesi_internal"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "csky_literal_Uk_operand" "")
   (match_operand    2 "" "")
   (match_operand    3 "" "")]
  ""
  {
    rtx reg0;
    rtx test = gen_rtx_GTU(VOIDmode, operands[0], operands[1]);
    emit_jump_insn (gen_cbranchsi4 (test,operands[0],operands[1], operands[3]));
    reg0 = gen_rtx_REG (SImode, 0);
    emit_move_insn (reg0, operands[0]);
    emit_jump_insn (gen_csky_casesi_dispatch (operands[2]/*, operands[3]*/));
    DONE;
  }
)

(define_insn "csky_casesi_dispatch"
  [(parallel [(set (pc) (unspec [(reg:SI 0) (label_ref (match_operand 0 "" ""))
;;                                          (label_ref (match_operand 1 "" ""))
                                ]
                                UNSPEC_CSKY_CASESI))
              (clobber (reg:SI 15))])]
  ""
  "*return csky_output_casesi(operands);"
  [(set_attr "length" "4")]
)


;; ------------------------------------------------------------
;; DSP insns
;; ------------------------------------------------------------

(define_expand "mulsidi3"
  [(set (match_operand:DI                          0 "register_operand" "")
        (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" ""))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" ""))))]
  "CSKY_ISA_FEATURE(dsp) || CSKY_ISA_FEATURE(3E3r1)"
  ""
)

(define_insn "*dsp_mulsidi3"
  [(set (match_operand:DI                          0 "register_operand" "=y")
        (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(dsp)"
  "muls\t%1, %2"
)

(define_insn "*ck803er1_mulsidi3"
  [(set (match_operand:DI                          0 "register_operand" "=r")
        (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mul.s32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_expand "umulsidi3"
  [(set (match_operand:DI                          0 "register_operand" "")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" ""))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" ""))))]
  "CSKY_ISA_FEATURE(dsp) || CSKY_ISA_FEATURE(3E3r1)"
  ""
)

(define_insn "*dsp_umulsidi3"
  [(set (match_operand:DI                          0 "register_operand" "=y")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulu\t%1, %2"
)

(define_insn "*ck803er1_umulsidi3"
  [(set (match_operand:DI                          0 "register_operand" "=r")
        (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" " r"))
                 (zero_extend:DI (match_operand:SI 2 "register_operand" " r"))))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mul.u32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "maddsidi4"
  [(set (match_operand:DI                                   0 "register_operand" "=y")
        (plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))
                 (match_operand:DI                          3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulsa\t%1, %2"
)

(define_insn "umaddsidi4"
  [(set (match_operand:DI                                   0 "register_operand" "=y")
        (plus:DI (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                          (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))
                 (match_operand:DI                          3 "register_operand" "0")))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulua\t%1, %2"
)

(define_insn "msubsidi4"
  [(set (match_operand:DI                                    0 "register_operand" "=y")
        (minus:DI (match_operand:DI                          3 "register_operand" "0")
                  (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
                           (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulss\t%1, %2"
)

(define_insn "umsubsidi4"
  [(set (match_operand:DI                                    0 "register_operand" "=y")
        (minus:DI (match_operand:DI                          3 "register_operand" "0")
                  (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
                           (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))))]
  "CSKY_ISA_FEATURE(dsp)"
  "mulus\t%1, %2"
)

(define_insn "*mula_32_l0"
  [(set (match_operand:SI 0 "register_operand"                   "+r")
        (plus:SI (match_dup 0)
                 (mult:SI (match_operand:SI 1 "register_operand" " r")
                          (match_operand:SI 2 "register_operand" " r"))))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mula.32.l\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*mula_32_l1"
  [(set (match_operand:SI 0 "register_operand"                   "+r")
        (plus:SI (mult:SI (match_operand:SI 1 "register_operand" " r")
                          (match_operand:SI 2 "register_operand" " r"))
                 (match_dup 0)))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mula.32.l\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*mula_u32_0"
  [(set (match_operand:DI                                   0 "register_operand" "+r")
        (plus:DI (match_dup 0)
                 (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" " r"))
                          (zero_extend:DI (match_operand:SI 2 "register_operand" " r")))))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mula.u32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*mula_u32_1"
  [(set (match_operand:DI                                   0 "register_operand" "+r")
        (plus:DI (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" " r"))
                          (zero_extend:DI (match_operand:SI 2 "register_operand" " r")))
                 (match_dup 0)))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mula.u32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*mula_s32_0"
  [(set (match_operand:DI                                   0 "register_operand" "+r")
        (plus:DI (match_dup 0)
                 (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
                          (sign_extend:DI (match_operand:SI 2 "register_operand" " r")))))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mula.s32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "*mula_s32_1"
  [(set (match_operand:DI                                   0 "register_operand" "+r")
        (plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
                          (sign_extend:DI (match_operand:SI 2 "register_operand" " r")))
                 (match_dup 0)))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mula.s32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

;; ------------------------------------------------------------------------
;; index insns
;; ------------------------------------------------------------------------

(define_insn "*cskyv2_indexdi_t"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI (ashift:SI (match_operand:SI 1 "register_operand" "r")
                            (const_int 3))
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(2E3)"
  "ixd\t%0, %2, %1"
)

(define_insn "*cskyv2_indexsi_t"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI (ashift:SI (match_operand:SI 1 "register_operand" "r")
                            (const_int 2))
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E2)"
  "ixw\t%0, %2, %1"
)

(define_insn "*cskyv2_indexhi_t"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (plus:SI (ashift:SI (match_operand:SI 1 "register_operand" "r")
                            (const_int 1))
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(E2)"
  "ixh\t%0, %2, %1"
)

;; ------------------------------------------------------------------------
;; swap insns
;; ------------------------------------------------------------------------

(define_insn "bswapsi2"
  [(set (match_operand:SI           0 "register_operand" "=b,r")
        (bswap:SI (match_operand:SI 1 "register_operand" "b, r")))]
  "CSKY_ISA_FEATURE(E2)"
  "revb\t%0, %1"
  [(set_attr "length" "2,4")
   (set_attr "isa"    "def,2e3")]
)

;; ------------------------------------------------------------------------
;; max & min insns
;; ------------------------------------------------------------------------

(define_insn "smaxsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (smax:SI (match_operand:SI 1 "register_operand" "r")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "max.s32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "umaxsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (umax:SI (match_operand:SI 1 "register_operand" "r")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "max.u32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "sminsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (smin:SI (match_operand:SI 1 "register_operand" "r")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "min.s32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

(define_insn "uminsi3"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (umin:SI (match_operand:SI 1 "register_operand" "r")
                 (match_operand:SI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "min.u32\t%0, %1, %2"
  [(set_attr "type"   "alu")
   (set_attr "length"   "4")])

;; ------------------------------------------------------------------------
;; Peephole optimize
;; ------------------------------------------------------------------------

;; optimize
;;   movi rx, const
;;   subi rx, rx, 1
;;   cmphs rx, ry
;;   bt label
;; To
;;   movi rx, const
;;   cmphs ry, rx
;;   bf label
;; const must not be zero to avoid subtraction overflow.
(define_peephole2
  [(set (match_operand:SI 0 "register_operand" "")
        (match_operand:SI 1 "const_int_operand" ""))
   (set (match_dup 0)
        (minus:SI (match_dup 0)
                  (const_int 1)))
   (set (reg:CC CSKY_CC_REGNUM)
        (leu:CC (match_operand:SI 3 "register_operand" "")
                (match_dup 0)))
   (set (pc)
        (if_then_else (ne (reg:CC CSKY_CC_REGNUM) (const_int 0))
                      (label_ref (match_operand 4 "" ""))
                      (pc)))]
  "(INTVAL (operands[1])) != 0"
  [(set (match_dup 0)
        (match_dup 1))
   (set (reg:CC CSKY_CC_REGNUM)
        (leu:CC (match_dup 0) (match_dup 3)))
   (set (pc)
        (if_then_else (eq (reg:CC CSKY_CC_REGNUM) (const_int 0))
                      (label_ref (match_dup 4))
                      (pc)))]
)

(define_peephole2
  [(set (match_operand:SI         0 "register_operand" "")
        (ior:SI (match_operand:SI 1 "register_operand" "")
                (match_operand:SI 2 "register_operand" "")))
   (set (match_operand:SI  3 "register_operand" "")
        (not:SI (match_dup 0)))
]
  "CSKY_ISA_FEATURE(E2)"
  [(set (match_dup 0)
        (not:SI (ior:SI (match_dup 1)
                        (match_dup 2))))]
)

(define_expand "doloop_begin"
 [(use (match_operand 0 "register_operand" ""))        ; loop pseudo
  (use (match_operand 1 "" ""))]                       ; doloop_end pattern
  "(CSKY_ISA_FEATURE(dspv2)||CSKY_ISA_FEATURE(3E3r2)) && flag_csky_doloop"
  {
    if (CSKY_ISA_FEATURE(dspv2) || CSKY_ISA_FEATURE(3E3r2))
    {
      rtx const1 = GEN_INT (1);
      emit_insn (gen_addsi3 (operands[0], operands[0], const1));
    }
    DONE;
  }
)

(define_expand "doloop_end"
 [(use (match_operand 0 "" ""))        ; loop pseudo
  (use (match_operand 1 "" ""))]       ; label
  "(CSKY_ISA_FEATURE(dspv2) || CSKY_ISA_FEATURE(3E3r2)) && flag_csky_doloop"
  {
    if (GET_MODE (operands[0]) != SImode || GET_CODE (operands[0]) != REG)
      FAIL;
    if (CSKY_ISA_FEATURE(3E3r2))
      emit_jump_insn (gen_fold_short_loop_with_bnezad (operands[0], operands[1]));
    else
      emit_jump_insn (gen_doloop_end_internal_loop (operands[0], operands[1]));
    DONE;
  }
)

(define_insn "doloop_end_internal_loop"
 [(set (pc)
       (if_then_else (ne (match_operand:SI 0 "register_operand" "+r,!m")
       (const_int 0))
         (label_ref (match_operand 1 "" ""))
         (pc)))
  (set (match_dup 0) (plus:SI (match_dup 0) (const_int -1)))
  (unspec [(const_int 0)] UNSPEC_DOLOOP)
  (clobber (match_scratch:SI 2 "=X,&r"))
  (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(dspv2) && !CSKY_ISA_FEATURE(3E3r2)"
  {
    switch (which_alternative)
    {
    case 0:
      if (get_attr_length (insn) == 4)
        return "bloop\t%0, %1 #LOOP.1.1";

      return "subi\t%0, %0, 1;\n\tjbnez\t%0, %1 # LOOP.1.1";
    case 1:
      return "ld.w\t%2, %0;\n\tsubi\t%2, %2, 1;\n\tst.w\t%2, %0;\n\tjbnez\t%2, %1 # LOOP.2.1";
    default:
      gcc_unreachable ();
    }
  }
  ;; FIXME(Jianping Zeng), describe precisely the length attribute.
  ;; 2018/4/28
 [(set (attr "length")
       (if_then_else (lt (abs (minus (match_dup 1) (pc)))
         (const_int 4095))
         (const_int 4)
         (const_int 12)))])

;; emit bnezad
(define_insn "fold_short_loop_with_bnezad"
 [(set (pc)
       (if_then_else (ne (match_operand:SI 0 "register_operand" "+r,!m")
       (const_int 0))
         (label_ref (match_operand 1 "" ""))
         (pc)))
  (set (match_dup 0) (plus:SI (match_dup 0) (const_int -1)))
  (unspec [(const_int 0)] UNSPEC_DOLOOP)
  (clobber (match_scratch:SI 2 "=X,&r"))
  (clobber (reg:CC CSKY_CC_REGNUM))]
  "CSKY_ISA_FEATURE(3E3r2)"
  {
    switch (which_alternative)
    {
    case 0:
      if (get_attr_length (insn) == 4)
        return "bnezad\t%0, %1 # short loop optimization";

      return "subi\t%0, %0, 1;\n\tjbnez\t%0, %1 # LOOP.1.1";
    case 1:
      return "ld.w\t%2, %0;\n\tsubi\t%2, %2, 1;\n\tst.w\t%2, %0;\n\tjbnez\t%2, %1 # LOOP.2.1";
    default:
      gcc_unreachable ();
    }
  }
  ;; FIXME(Jianping Zeng), describe precisely the length attribute.
  ;; 2018/4/28
 [(set (attr "length")
       (if_then_else (lt (abs (minus (match_dup 1) (pc)))
         (const_int 65534))
         (const_int 4)
         (const_int 12)))])

;;TODO emit decgt.
;;TODO emit declt.
;;TODO emit decne.
;;TODO emit dect.
;;TODO emit asrc.
;;TODO emit brev.
;;TODO emit ixd.
;;TODO emit revb.
