;;  Machine description the CSKY
;;  Copyright (C) 1993-2016 Free Software Foundation, Inc.
;;  Contributed by Motorola.

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;;- See file "rtl.def" for documentation on define_insn, match_*, et. al.



;; -------------------------------------------------------------------------
;; Constants
;; -------------------------------------------------------------------------

;; Register numbers -- All machine registers should be defined here
(define_constants
  [(CC_REGNUM      33)  ; Condition code pseudo register
   (LK_REGNUM      15)  ; Link register
   (GB_REGNUM      14)  ; GOT base register
  ]
)



;; -------------------------------------------------------------------------
;; Attributes
;; -------------------------------------------------------------------------

;; If a branch destination is within -2048..2047 bytes away from the
;; instruction it can be 2 bytes long.  All other conditional branches
;; are 10 bytes long, and all other unconditional branches are 8 bytes.
;;
;; the assembler handles the long-branch span case for us if we use
;; the "jb*" mnemonics for jumps/branches. This pushes the span
;; calculations and the literal table placement into the assembler,
;; where their interactions can be managed in a single place.

;; CSKY instruction set V1 instructions are two bytes long by default.

(define_attr "length" "" (const_int 2))

;; -------------------------------------------------------------------------
;; Unspecs
;; -------------------------------------------------------------------------

(define_c_enum "unspec" [
  UNSPEC_PIC
  UNSPEC_GET_PC
  UNSPEC_TLS
  UNSPEC_TLS_LABEL
  UNSPEC_STACK_SIZE
])

(define_c_enum "pic_type" [
  PIC_SYMBOL_GOTOFF
  PIC_SYMBOL_PLT
  PIC_SYMBOL_GOT
  PIC_SYMBOL_GOTPC
])

(define_c_enum "unspec_volatile" [
  VUNSPEC_EH_RETURN
  UNSPEC_PROLOGUE_USE
])

;; -------------------------------------------------------------------------
;; Predicates
;; -------------------------------------------------------------------------

(include "abiv1_predicates.md")
(include "abiv1_constraints.md")

;; -------------------------------------------------------------------------
;; Test and bit test
;; -------------------------------------------------------------------------

;;; This is created by combine.
(define_insn "*csky_btsti_t"
  [(set (reg:CC CC_REGNUM)
        (ne:CC (zero_extract:SI
                 (match_operand:SI 0 "csky_arith_reg_operand" "r")
                 (const_int 1)
                 (match_operand:SI 1 "csky_literal_K_operand" "K"))
                 (const_int 0)))]
  ""
  "btsti\t%0, %1"
  )

(define_insn "*csky_tst_t"
  [(set (reg:CC CC_REGNUM)
        (ne:CC (and:SI (match_operand:SI 0 "csky_arith_reg_operand" "r")
                 (match_operand:SI 1 "csky_arith_reg_operand" "r"))
                 (const_int 0)))]
  ""
  "tst\t%0, %1"
  )

;; -------------------------------------------------------------------------
;; SImode signed integer comparisons
;; -------------------------------------------------------------------------

(define_insn "*csky_decne_t"
  [(set (reg:CC CC_REGNUM)
        (ne:CC (plus:SI (match_operand:SI 0 "csky_arith_reg_operand" "+r")
                        (const_int -1))
               (const_int 0)))
   (set (match_dup 0)
        (plus:SI (match_dup 0) (const_int -1)))]
  ""
  "decne\t%0")

;; The combiner seems to prefer the following to the former.
;;
(define_insn ""
  [(set (reg:CC CC_REGNUM)
        (ne:CC (match_operand:SI 0 "csky_arith_reg_operand" "+r")
               (const_int 1)))
   (set (match_dup 0)
        (plus:SI (match_dup 0) (const_int -1)))]
  ""
  "decne\t%0")

(define_insn "cmpnesi_t"
  [(set (reg:CC CC_REGNUM)
        (ne:CC (match_operand:SI 0 "csky_arith_reg_operand" "r,r")
               (match_operand:SI 1 "csky_arith_K_operand" "r,K")))]
  ""
  "@
  cmpne\t%0, %1
  cmpnei\t%0, %1")

(define_insn "cmpgtsi_t"
  [(set (reg:CC CC_REGNUM)
        (gt:CC (match_operand:SI 0 "csky_arith_reg_operand" "r")
               (match_operand:SI 1 "csky_arith_reg_operand" "r")))]
  ""
  "cmplt\t%1, %0")

(define_insn ""
  [(set (reg:CC CC_REGNUM)
        (gt:CC (plus:SI (match_operand:SI 0 "csky_arith_reg_operand" "+r")
                        (const_int -1))
               (const_int 0)))
   (set (match_dup 0)
        (plus:SI (match_dup 0) (const_int -1)))]
  ""
  "decgt\t%0")

(define_insn "cmpltsi_t"
  [(set (reg:CC CC_REGNUM)
        (lt:CC (match_operand:SI 0 "csky_arith_reg_operand" "r,r")
               (match_operand:SI 1 "csky_arith_J_operand" "r,J")))]
  ""
  "@
  cmplt\t%0, %1
  cmplti\t%0, %1")

; covers cmplti x,0
(define_insn ""
  [(set (reg:CC CC_REGNUM)
        (lt:CC (match_operand:SI 0 "csky_arith_reg_operand" "r")
               (const_int 0)))]
  ""
  "btsti\t%0, 31")

(define_insn ""
  [(set (reg:CC CC_REGNUM)
        (lt:CC (plus:SI (match_operand:SI 0 "csky_arith_reg_operand" "+r")
                        (const_int -1))
               (const_int 0)))
   (set (match_dup 0) (plus:SI (match_dup 0) (const_int -1)))]
  ""
  "declt\t%0")

;; -------------------------------------------------------------------------
;; SImode unsigned integer comparisons
;; -------------------------------------------------------------------------

(define_insn "cmpgeusi_t"
  [(set (reg:CC CC_REGNUM)
        (geu:CC (match_operand:SI 0 "csky_arith_reg_operand" "r")
                (match_operand:SI 1 "csky_arith_reg_operand" "r")))]
  ""
  "cmphs\t%0, %1")

(define_insn "cmpgeusi_0"
  [(set (reg:CC CC_REGNUM)
        (geu:CC (match_operand:SI 0 "csky_arith_reg_operand" "r")
                (const_int 0)))]
  ""
  "cmpnei\t%0, 0")

(define_insn "cmpleusi_t"
  [(set (reg:CC CC_REGNUM)
        (leu:CC (match_operand:SI 0 "csky_arith_reg_operand" "r")
                (match_operand:SI 1 "csky_arith_reg_operand" "r")))]
  ""
  "cmphs\t%1, %0")

;; -------------------------------------------------------------------------
;; Logical operations
;; -------------------------------------------------------------------------

(define_insn "andnsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (and:SI (not:SI (match_operand:SI 1 "csky_arith_reg_operand" "r"))
                (match_operand:SI 2 "csky_arith_reg_operand" "0")))]
  ""
  "andn\t%0, %1")

(define_expand "andsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (and:SI (match_operand:SI 1 "csky_arith_reg_operand" "")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
{
  if (can_create_pseudo_p ()
      && CONST_INT_P (operands[2]) && INTVAL (operands[2]) < 0
      && ! csky_arith_S_operand (operands[2], SImode))
    {
      HOST_WIDE_INT not_value = ~ INTVAL (operands[2]);

      if (CONST_OK_FOR_I (not_value)
          || CONST_OK_FOR_M (not_value)
          || CONST_OK_FOR_N (not_value))
        {
          operands[2] = copy_to_mode_reg (SImode, GEN_INT (not_value));
          emit_insn (gen_andnsi3 (operands[0], operands[2], operands[1]));
          DONE;
        }
    }

  if (can_create_pseudo_p () && ! csky_arith_K_S_operand (operands[2], SImode))
    operands[2] = copy_to_mode_reg (SImode, operands[2]);
}")

(define_insn "*cskyv1_andsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r,r")
        (and:SI (match_operand:SI 1 "csky_arith_reg_operand" "%0,0,0")
                (match_operand:SI 2 "csky_arith_K_S_operand" "r,K,S")))]
  "TARGET_CSKYV1"
  "*
{
   switch (which_alternative)
     {
     case 0: return \"and\t%0, %2\";
     case 1: return \"andi\t%0, %2\";
     case 2: return csky_output_bclri (operands[0], INTVAL (operands[2]));
     default: gcc_unreachable ();
     }
}")


; need an expand to resolve ambiguity betw. the two iors below.
(define_expand "iorsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (ior:SI (match_operand:SI 1 "csky_arith_reg_operand" "")
                (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
{
   if (can_create_pseudo_p () && ! csky_arith_T_operand (operands[2], SImode))
      operands[2] = copy_to_mode_reg (SImode, operands[2]);
}")

(define_insn "*csky1_iorsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r,r")
        (ior:SI (match_operand:SI 1 "csky_arith_reg_operand" "%0,0,0")
                (match_operand:SI 2 "csky_arith_T_operand" "r,M,T")))]
  "TARGET_CSKYV1"
  "*
{
   switch (which_alternative)
     {
     case 0: return \"or\t%0, %2\";
     case 1: return \"bseti\t%0, %P2\";
     case 2: return csky_output_bseti (operands[0], INTVAL (operands[2]));
     default: gcc_unreachable ();
     }
}")

(define_insn "xorsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (xor:SI (match_operand:SI 1 "csky_arith_reg_operand" "%0")
                (match_operand:SI 2 "csky_arith_reg_operand" "r")))]
  ""
  "xor\t%0, %2")

;; -------------------------------------------------------------------------
;; Shifts and rotates
;; -------------------------------------------------------------------------

;; We can only do constant rotates, which is what this pattern provides.
;; The combiner will put it together for us when we do:
;;  (x << N) | (x >> (32 - N)) (x should be unsigned)
(define_insn "rotlsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (rotate:SI (match_operand:SI   1 "csky_arith_reg_operand"  "0")
                   (match_operand:SI 2 "csky_literal_K_operand"  "K")))]
  ""
  "rotli\t%0, %2"
  )

(define_insn "ashlsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r")
        (ashift:SI (match_operand:SI 1 "csky_arith_reg_operand" "0,0")
                   (match_operand:SI 2 "csky_arith_K_operand_not_0" "r,K")))]
  ""
  "@
  lsl\t%0, %2
  lsli\t%0, %2"
  )

(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (ashift:SI (const_int 1)
                   (match_operand:SI 1 "csky_arith_reg_operand" "r")))]
  ""
  "bgenr\t%0, %1"
  )

(define_insn "ashrsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r")
        (ashiftrt:SI (match_operand:SI 1 "csky_arith_reg_operand" "0,0")
                     (match_operand:SI 2 "csky_arith_K_operand_not_0" "r,K")))]
  ""
  "@
  asr\t%0, %2
  asri\t%0, %2"
  )

(define_insn "lshrsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r")
        (lshiftrt:SI (match_operand:SI 1 "csky_arith_reg_operand" "0,0")
                     (match_operand:SI 2 "csky_arith_K_operand_not_0" "r,K")))]
  ""
  "@
  lsr\t%0, %2
  lsri\t%0, %2"
  )

;; -------------------------------------------------------------------------
;; Index instructions
;; -------------------------------------------------------------------------

;; indexing longs (4 bytes)

(define_insn "*indexsi_t"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (plus:SI (ashift:SI (match_operand:SI 1 "csky_arith_reg_operand" "r")
                            (const_int 2))
                 (match_operand:SI 2 "csky_arith_reg_operand" "0")))]
  ""
  "ixw\t%0, %1")

;; indexing shorts (2 bytes)

(define_insn "*indexhi_t"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (plus:SI (ashift:SI (match_operand:SI 1 "csky_arith_reg_operand" "r")
                            (const_int 1))
                 (match_operand:SI 2 "csky_arith_reg_operand" "0")))]
  ""
  "ixh\t%0, %1")

;;
;; Other sizes may be handy for indexing.
;; the tradeoffs to consider when adding these are
;;  code size, execution time [vs. mul it is easy to win],
;;  and register pressure -- these patterns don't use an extra
;;  register to build the offset from the base
;;  and whether the compiler will not come up with some other idiom.
;;

;; -------------------------------------------------------------------------
;; Addition, Subtraction instructions
;; -------------------------------------------------------------------------

(define_expand "addsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (plus:SI (match_operand:SI 1 "csky_arith_reg_operand" "")
                 (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
{
  /* If this is an add to the frame pointer, then accept it as it is so
     that we can later fold in the fp/sp offset from frame pointer
     elimination.  */
  if (! (flag_omit_frame_pointer
      && GET_CODE (operands[1]) == REG
      && (REGNO (operands[1]) == VIRTUAL_STACK_VARS_REGNUM
    || REGNO (operands[1]) == FRAME_POINTER_REGNUM)))
  {
    if (can_create_pseudo_p () && ! csky_addsub_operand (operands[2], SImode))
      operands[2] = copy_to_mode_reg (SImode, operands[2]);
  }
}")

(define_insn "*cskyv1_addsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r,r")
        (plus:SI (match_operand:SI 1 "csky_arith_reg_operand" "%0,0,0")
                 (match_operand:SI 2 "csky_arith_any_imm_operand" "r,J,L")))]
  "TARGET_CSKYV1"
  "@
  addu\t%0, %2
  addi\t%0, %2
  subi\t%0, %M2")

(define_expand "subsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (minus:SI (match_operand:SI 1 "csky_arith_reg_operand" "")
                  (match_operand:SI 2 "csky_arith_any_imm_operand" "")))]
  ""
  "
{
  if (can_create_pseudo_p () && ! csky_addsub_operand (operands[2], SImode))
    operands[2] = copy_to_mode_reg (SImode, operands[2]);
}")

(define_insn "*cskyv1_subsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r,r")
        (minus:SI (match_operand:SI 1 "csky_arith_reg_operand" "0,0,r")
                  (match_operand:SI 2 "csky_arith_J_operand" "r,J,0")))]
  "TARGET_CSKYV1"
  "@
  subu\t%0, %2
  subi\t%0, %2
  rsub\t%0, %1")

(define_insn "*cskyv1_subsi3_i"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (minus:SI (match_operand:SI 1 "csky_literal_K_operand" "K")
                  (match_operand:SI 2 "csky_arith_reg_operand" "0")))]
  "TARGET_CSKYV1"
  "rsubi\t%0, %1")

(define_expand "adddi3"
  [(parallel [
    (set (match_operand:DI 0 "csky_arith_reg_operand" "")
         (plus:DI (match_operand:DI 1 "csky_arith_reg_operand" "")
                  (match_operand:DI 2 "csky_arith_int1m1_operand" "")))
    (clobber (reg:CC CC_REGNUM))])]
 ""
 "")

(define_insn "*cskyv1_adddi3"
 [(set (match_operand:DI 0 "csky_arith_reg_operand" "=&r")
       (plus:DI (match_operand:DI 1 "csky_arith_reg_operand" "%0")
                (match_operand:DI 2 "register_operand" "r")))
 (clobber (reg:CC CC_REGNUM))]
 "TARGET_CSKYV1"
 "addc64\t%0, %0, %2"
 [(set_attr "length" "6")])

;; special case for "longlong += 1"
(define_insn ""
  [(set (match_operand:DI 0 "csky_arith_reg_operand" "=&r")
        (plus:DI (match_operand:DI 1 "csky_arith_reg_operand" "0")
                 (const_int 1)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "*
  {
   if (TARGET_LITTLE_ENDIAN)
      return \"addi\t%0, 1\;cmpnei\t%0, 0\;incf\t%R0\";
    return \"addi\t%R0, 1\;cmpnei\t%R0, 0\;incf\t%0\";
  }"
  [(set_attr "length" "6")])

;; special case for "longlong -= 1"
(define_insn ""
  [(set (match_operand:DI 0 "csky_arith_reg_operand" "=&r")
        (plus:DI (match_operand:DI 1 "csky_arith_reg_operand" "0")
                 (const_int -1)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "*
  {
    if (TARGET_LITTLE_ENDIAN)
       return \"cmpnei\t%0, 0\;decf\t%R0\;subi\t%0, 1\";
    return \"cmpnei\t%R0, 0\;decf\t%0\;subi\t%R0, 1\";
  }"
  [(set_attr "length" "6")])

(define_insn "subdi3"
  [(set (match_operand:DI 0 "csky_arith_reg_operand" "=&r")
        (minus:DI (match_operand:DI 1 "csky_arith_reg_operand" "0")
                  (match_operand:DI 2 "csky_arith_reg_operand" "r")))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "subc64\t%0, %0, %2"
  [(set_attr "length" "6")])

;; -------------------------------------------------------------------------
;; Multiplication instructions
;; -------------------------------------------------------------------------

(define_insn "mulsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (mult:SI (match_operand:SI 1 "csky_arith_reg_operand" "%0")
                 (match_operand:SI 2 "csky_arith_reg_operand" "r")))]
  ""
  "mult\t%0, %2")

;;
;; 32/32 signed division
;;
(define_expand "divsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (div:SI (match_operand:SI 1 "csky_arith_reg_operand" "")
                (match_operand:SI 2 "csky_arith_reg_operand" "")))]
  "TARGET_DIV"
  "")

;; divs is a pseudu instruction, it will be spilit into
;;  "mov r1, rx" and "div rz, r1" by assembler
;;  modify by shangyh    06/08/2013
(define_insn "*cskyv1_divsi3"
 [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
       (div:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")
               (match_operand:SI 2 "csky_arith_reg_operand" "r")))]
 "TARGET_DIV && TARGET_CSKYV1"
 "divs\t%0, %2")

;;
;; 32/32 unsigned division
;;
(define_expand "udivsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (udiv:SI (match_operand:SI 1 "csky_arith_reg_operand" "")
                 (match_operand:SI 2 "csky_arith_reg_operand" "")))]
  "TARGET_DIV"
  "")

(define_insn "*cskyv1_udivsi3"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (udiv:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")
                 (match_operand:SI 2 "csky_arith_reg_operand" "r")))]
  "TARGET_DIV && TARGET_CSKYV1"
  "divu\t%0, %2")

;; -------------------------------------------------------------------------
;; Unary arithmetic
;; -------------------------------------------------------------------------

(define_insn "negsi2"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (neg:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")))]
  ""
  "rsubi\t%0, 0")


(define_insn "abssi2"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (abs:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")))]
  ""
  "abs\t%0")

(define_insn "one_cmplsi2"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (not:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")))]
  ""
  "not\t%0")

;; -------------------------------------------------------------------------
;; Zero extension instructions
;; -------------------------------------------------------------------------

(define_expand "zero_extendhisi2"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (zero_extend:SI (match_operand:HI 1 "nonimmediate_operand" "")))]
  ""
  "")

(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r")
        (zero_extend:SI (match_operand:HI 1 "nonimmediate_operand" "0,m")))]
  "TARGET_CSKYV1"
  "@
  zexth\t%0
  ld.h\t%0, %1"
  )

(define_expand "zero_extendqisi2"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (zero_extend:SI (match_operand:QI 1 "nonimmediate_operand" "")))]
  ""
  "")

(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,r")
        (zero_extend:SI (match_operand:QI 1 "nonimmediate_operand" "0,m")))]
  ""
  "@
  zextb\t%0
  ld.b\t%0, %1"
  )

(define_expand "zero_extendqihi2"
  [(set (match_operand:HI 0 "csky_arith_reg_operand" "")
        (zero_extend:HI (match_operand:QI 1 "nonimmediate_operand" "")))]
  ""
  "")

(define_insn ""
  [(set (match_operand:HI 0 "csky_arith_reg_operand" "=r,r")
        (zero_extend:HI (match_operand:QI 1 "nonimmediate_operand" "0,m")))]
  ""
  "@
  zextb\t%0
  ld.b\t%0, %1"
  )

;; -------------------------------------------------------------------------
;; Sign extension instructions
;; -------------------------------------------------------------------------

(define_expand "extendsidi2"
  [(set (match_operand:DI 0 "csky_arith_reg_operand" "=r")
        (match_operand:SI 1 "csky_arith_reg_operand" "r"))]
  ""
  "
  {
    int low, high;

    if (TARGET_LITTLE_ENDIAN)
      low = 0, high = 4;
    else
      low = 4, high = 0;

    emit_insn (gen_rtx_SET (gen_rtx_SUBREG (SImode, operands[0], low),
        operands[1]));
    emit_insn (gen_rtx_SET (gen_rtx_SUBREG (SImode, operands[0], high),
        gen_rtx_ASHIFTRT (SImode,
             gen_rtx_SUBREG (SImode, operands[0], low),
             GEN_INT (31))));
    DONE;
  }"
)

(define_insn "extendhisi2"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (sign_extend:SI (match_operand:HI 1 "csky_arith_reg_operand" "0")))]
  ""
  "sexth\t%0")

(define_insn "extendqisi2"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (sign_extend:SI (match_operand:QI 1 "csky_arith_reg_operand" "0")))]
  ""
  "sextb\t%0")

(define_insn "extendqihi2"
  [(set (match_operand:HI 0 "csky_arith_reg_operand" "=r")
        (sign_extend:HI (match_operand:QI 1 "csky_arith_reg_operand" "0")))]
  ""
  "sextb\t%0")

;; -------------------------------------------------------------------------
;; Move instructions
;; -------------------------------------------------------------------------

;; SImode

(define_expand "movsi"
  [(set (match_operand:SI 0 "general_operand" "")
        (match_operand:SI 1 "general_operand" ""))]
  ""
  "
{
  if (MEM_P (operands[0]))
    operands[1] = force_reg (SImode, operands[1]);
  else if (csky_tls_referenced_p (operands[1]))
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

      tmp = legitimize_tls_address (tmp,
            !can_create_pseudo_p () ? operands[0] : 0);
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
      operands[1] = legitimize_pic_address (operands[1], SImode,
            (!can_create_pseudo_p () ? operands[0] : 0), 1);
    }
}")

(define_insn "*cskyv1_movsi"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=r,r,a,a,r,m,r,r,y,r,f")
        (match_operand:SI 1 "general_operand"       "r,P,i,F,m,r,c,y,r,f,r"))]
  "TARGET_CSKYV1"
  "* return csky_output_move (insn, operands, SImode);"
  [(set_attr "length" "2,4,2,2,2,2,2,2,2,2,2")])

;;
;; HImode
;;

(define_expand "movhi"
  [(set (match_operand:HI 0 "general_operand" "")
        (match_operand:HI 1 "general_operand"  ""))]
  ""
  "
{
  if (can_create_pseudo_p ())
    {
      if (MEM_P (operands[0]))
        operands[1] = force_reg (HImode, operands[1]);
      else if (CONST_INT_P (operands[1]))
        {
          rtx reg = gen_reg_rtx (SImode);
          emit_insn (gen_movsi (reg, operands[1]));
          operands[1] = gen_lowpart (HImode, reg);
        }
    }
}")

(define_insn "*cskyv1_movhi"
  [(set (match_operand:HI 0 "nonimmediate_operand" "=r,r,a,a,r,m,r,y,r,f")
        (match_operand:HI 1 "general_operand"       "r,P,i,F,m,r,y,r,f,r"))]
  "TARGET_CSKYV1"
  "* return csky_output_move (insn, operands, HImode);"
  [(set_attr "length" "2,4,2,2,2,2,2,2,2,2")])

;;
;; QImode
;;

(define_expand "movqi"
  [(set (match_operand:QI 0 "general_operand" "")
        (match_operand:QI 1 "general_operand"  ""))]
  ""
  "
{
  if (can_create_pseudo_p ())
    {
      if (MEM_P (operands[0]))
        operands[1] = force_reg (QImode, operands[1]);
      else if (CONST_INT_P (operands[1]))
        {
          rtx reg = gen_reg_rtx (SImode);
          emit_insn (gen_movsi (reg, operands[1]));
          operands[1] = gen_lowpart (QImode, reg);
        }
    }
}")

(define_insn "*cskyv1_movqi"
  [(set (match_operand:QI 0 "nonimmediate_operand" "=r,r,a,a,r,m,r,y,r,f")
        (match_operand:QI 1 "general_operand"  "r,P,i,F,m,r,y,r,f,r"))]
  "TARGET_CSKYV1"
  "* return csky_output_move (insn, operands, QImode);"
   [(set_attr "length" "2,4,2,2,2,2,2,2,2,2")])


;; DImode

(define_expand "movdi"
  [(set (match_operand:DI 0 "general_operand" "")
        (match_operand:DI 1 "general_operand" ""))]
  ""
  "
{
  if (can_create_pseudo_p () && MEM_P (operands[0]))
    operands[1] = force_reg (DImode, operands[1]);
  else if (CONST_INT_P (operands[1]))
    {
      int i;
      for (i = 0; i < UNITS_PER_WORD * 2; i += UNITS_PER_WORD)
        emit_move_insn (simplify_gen_subreg (SImode, operands[0], DImode, i),
            simplify_gen_subreg (SImode, operands[1], DImode, i));
      DONE;
    }
}")

(define_insn "*cskyv1_movdi"
  [(set (match_operand:DI 0 "nonimmediate_operand" "=r,r,m,r,y,r,f")
        (match_operand:DI 1 "general_operand" "r,m,r,y,r,f,r"))]
  ""
  "* return csky_output_movedouble (operands, DImode);"
  [(set_attr "length" "4,4,4,4,4,4,4")])

;; Load/store multiple

(define_expand "load_multiple"
  [(match_par_dup 3 [(set (match_operand:SI 0 "" "")
                          (match_operand:SI 1 "" ""))
                     (use (match_operand:SI 2 "" ""))])]
  "TARGET_MULTIPLE_STLD"
  "
{
  int regno, count, i;

  /* Support only loading a constant number of registers from memory and
     only if at least two registers.  The last register must be r15.  */
  if (GET_CODE (operands[2]) != CONST_INT
      || INTVAL (operands[2]) < 2
      || GET_CODE (operands[1]) != MEM
      || XEXP (operands[1], 0) != stack_pointer_rtx
      || GET_CODE (operands[0]) != REG
      || REGNO (operands[0]) + INTVAL (operands[2]) != 16)
    FAIL;

  count = INTVAL (operands[2]);
  regno = REGNO (operands[0]);

  operands[3] = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (count));

  for (i = 0; i < count; i++)
    XVECEXP (operands[3], 0, i)
      = gen_rtx_SET (gen_rtx_REG (SImode, regno + i),
     gen_rtx_MEM (SImode, plus_constant (Pmode, stack_pointer_rtx,
                 i * 4)));
}")

(define_insn "*cskyv1_load_multiple"
  [(match_parallel 0 "csky_load_multiple_operation"
    [(set (match_operand:SI 1 "csky_arith_reg_operand" "=r")
          (mem:SI (match_operand:SI 2 "register_operand" "r")))])]
  "TARGET_MULTIPLE_STLD && TARGET_CSKYV1 &&
   GET_CODE (operands[2]) == REG && REGNO (operands[2]) == STACK_POINTER_REGNUM"
  "ldm\t%1-r15,(%2)")

(define_expand "store_multiple"
  [(match_par_dup 3 [(set (match_operand:SI 0 "" "")
                          (match_operand:SI 1 "" ""))
                     (use (match_operand:SI 2 "" ""))])]
  "TARGET_MULTIPLE_STLD"
  "
{
  int regno, count, i;

  /* Support only storing a constant number of registers to memory and
     only if at least two registers.  The last register must be r15.  */
  if (GET_CODE (operands[2]) != CONST_INT
      || INTVAL (operands[2]) < 2
      || GET_CODE (operands[0]) != MEM
      || XEXP (operands[0], 0) != stack_pointer_rtx
      || GET_CODE (operands[1]) != REG
      || REGNO (operands[1]) + INTVAL (operands[2]) != 16)
    FAIL;

  count = INTVAL (operands[2]);
  regno = REGNO (operands[1]);

  operands[3] = gen_rtx_PARALLEL (VOIDmode, rtvec_alloc (count));

  for (i = 0; i < count; i++)
    XVECEXP (operands[3], 0, i)
      = gen_rtx_SET (
     gen_rtx_MEM (SImode, plus_constant (Pmode, stack_pointer_rtx,
                 i * 4)),
     gen_rtx_REG (SImode, regno + i));
}")

(define_insn "*cskyv1_store_multiple"
  [(match_parallel 0 "csky_store_multiple_operation"
    [(set (mem:SI (match_operand:SI 2 "register_operand" "r"))
          (match_operand:SI 1 "csky_arith_reg_operand" "r"))])]
  "TARGET_MULTIPLE_STLD && TARGET_CSKYV1 &&
   GET_CODE (operands[2]) == REG && REGNO (operands[2]) == STACK_POINTER_REGNUM"
  "stm\t%1-r15,(%2)")

;; ------------------------------------------------------------------------
;; Define the real conditional branch instructions.
;; ------------------------------------------------------------------------

;; At top-level, condition test are eq/ne, because we
;; are comparing against the condition register (which
;; has the result of the true relational test

(define_insn "csky_jbt"
  [(set (pc)
        (if_then_else (ne (reg:CC CC_REGNUM) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "jbt\t%l0"
  )

(define_insn "csky_jbf"
  [(set (pc)
        (if_then_else (eq (reg:CC CC_REGNUM) (const_int 0))
                      (label_ref (match_operand 0 "" ""))
                      (pc)))]
  ""
  "jbf\t%l0"
  )

;; Conditional branch insns

(define_expand "cbranchsi4"
  [(set (pc)
        (if_then_else (match_operator 0 "ordered_comparison_operator"
                        [(match_operand:SI 1 "csky_compare_operand")
                         (match_operand:SI 2 "nonmemory_operand")])
                      (label_ref (match_operand 3 ""))
                      (pc)))]
  ""
  "
{
  bool invert;
  invert = csky_gen_compare (GET_CODE (operands[0]),
            operands[1], operands[2]);

  if (invert)
    emit_jump_insn (gen_csky_jbf (operands[3]));
  else
    emit_jump_insn (gen_csky_jbt (operands[3]));
  DONE;
}")



;; ------------------------------------------------------------------------
;; Jump and linkage insns
;; ------------------------------------------------------------------------

(define_insn "*jump_real"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  "jbr\t%l0"
  )

(define_expand "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  "")

(define_insn "indirect_jump"
  [(set (pc)
        (match_operand:SI 0 "csky_arith_reg_operand" "r"))]
  ""
  "jmp\t%0"
  )

(define_expand "call"
  [(parallel[(call (match_operand:SI 0 "" "")
                   (match_operand 1 "" ""))
             (clobber (reg:SI LK_REGNUM))])]
  ""
  "
{
  rtx pic_ref;
  rtx addr_ref = XEXP (operands[0], 0);

  if (flag_pic
    && (CONSTANT_P (addr_ref)
      || symbol_mentioned_p (addr_ref)
      || label_mentioned_p (addr_ref)))
  {
    pic_ref = legitimize_pic_address (addr_ref, SImode, 0, 0);
    operands[0] = gen_rtx_MEM (GET_MODE (pic_ref), pic_ref);
  }
  else if (GET_CODE (operands[0]) == MEM
      && ! register_operand (XEXP (operands[0], 0), SImode)
      && ! csky_symbolic_address_p (XEXP (operands[0], 0)))
    operands[0] = gen_rtx_MEM (GET_MODE (operands[0]),
         force_reg (Pmode, XEXP (operands[0], 0)));
}")

(define_insn "call_internal"
  [(call (mem:SI (match_operand:SI 0 "csky_call_address_operand" "ri"))
         (match_operand 1 "" ""))
   (clobber (reg:SI LK_REGNUM))]
  ""
  "* return csky_output_call (operands, 0);")

(define_expand "call_value"
  [(parallel[(set (match_operand 0 "register_operand" "")
                  (call (match_operand:SI 1 "" "")
                        (match_operand 2 "" "")))
             (clobber (reg:SI LK_REGNUM))])]
  ""
  "
{
  rtx pic_ref;
  rtx addr_ref = XEXP (operands[1], 0);

  if (flag_pic
    && (CONSTANT_P (addr_ref)
      || symbol_mentioned_p (addr_ref)
      || label_mentioned_p (addr_ref)))
    {

      pic_ref = legitimize_pic_address (addr_ref, SImode, 0, 0);
      operands[1] = gen_rtx_MEM (GET_MODE (pic_ref), pic_ref);
    }
  else if (GET_CODE (operands[0]) == MEM
      && ! register_operand (XEXP (operands[0], 0), SImode)
      && ! csky_symbolic_address_p (XEXP (operands[0], 0)))
    operands[1] = gen_rtx_MEM (GET_MODE (operands[1]),
                               force_reg (Pmode,
                                          XEXP (operands[1], 0)));
}")

(define_insn "call_value_internal"
  [(set (match_operand 0 "register_operand" "=r")
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "ri"))
              (match_operand 2 "" "")))
   (clobber (reg:SI LK_REGNUM))]
  ""
  "* return csky_output_call (operands, 1);")

;; For BLKmode value return
(define_insn "call_value_struct"
  [(set (match_parallel 0 ""
          [(expr_list (match_operand:SI 3 "register_operand" "")
                      (match_operand:SI 4 "immediate_operand" ""))
           (expr_list (match_operand:SI 5 "register_operand" "")
                      (match_operand:SI 6 "immediate_operand" ""))])
        (call (mem:SI (match_operand:SI 1 "csky_call_address_operand" "ri"))
              (match_operand 2 "" "")))
   (clobber (reg:SI LK_REGNUM))]
  ""
  "* return csky_output_call (operands, 1);"
)


;; ------------------------------------------------------------------------
;; Misc insns
;; ------------------------------------------------------------------------

(define_insn "nop"
  [(const_int 0)]
  ""
  "or  r0,r0")

(define_expand "tablejump"
  [(parallel [(set (pc)
                   (match_operand:SI 0 "csky_arith_reg_operand" "r"))
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
}")

(define_insn "*tablejump"
  [(set (pc) (match_operand:SI 0 "csky_arith_reg_operand" "r"))
   (use (label_ref (match_operand 1 "" "")))]
  ""
  "jmp\t%0"
)

(define_insn "*return"
 [(return)]
 "reload_completed && ! csky_naked_function_p ()"
 "rts"
 )

(define_insn "*no_return"
 [(return)]
 "reload_completed && csky_naked_function_p ()"
 ""
 )

(define_insn "prologue_use"
  [(unspec:SI [(match_operand:SI 0 "register_operand" "")] UNSPEC_PROLOGUE_USE)]
  ""
  ""
)

(define_expand "prologue"
  [(const_int 0)]
  ""
  "csky_expand_prolog (); DONE;")

(define_expand "epilogue"
  [(return)]
  ""
  "
  {
    if (crtl->calls_eh_return)
      emit_insn (gen_prologue_use (gen_rtx_REG (Pmode, 4)));

    csky_expand_epilog ();
  }")

;; ------------------------------------------------------------------------
;; Scc instructions
;; ------------------------------------------------------------------------

(define_insn "mvc"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (ne:SI (reg:CC CC_REGNUM) (const_int 0)))]
  ""
  "mvc\t%0"
  )

(define_insn "mvcv"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (eq:SI (reg:CC CC_REGNUM) (const_int 0)))]
  ""
  "mvcv\t%0"
  )

(define_expand "cstoresi4"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (match_operator:SI 1 "ordered_comparison_operator"
          [(match_operand:SI 2 "csky_compare_operand" "")
           (match_operand:SI 3 "csky_arith_any_imm_operand" "")]))]
  ""
  "
{
  bool invert;
  invert = csky_gen_compare (GET_CODE (operands[1]),
            operands[2], operands[3]);

  if (invert)
    emit_insn (gen_mvcv (operands[0]));
  else
    emit_insn (gen_mvc (operands[0]));
  DONE;
}")

(define_insn "incscc"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (plus:SI (ne (reg:CC CC_REGNUM) (const_int 0))
                 (match_operand:SI 1 "csky_arith_reg_operand" "0")))]
  ""
  "inct\t%0")

(define_insn "incscc_false"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (plus:SI (eq (reg:CC CC_REGNUM) (const_int 0))
                 (match_operand:SI 1 "csky_arith_reg_operand" "0")))]
  ""
  "incf\t%0")

(define_insn "decscc"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (minus:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")
                  (ne (reg:CC CC_REGNUM) (const_int 0))))]
  ""
  "dect\t%0")

(define_insn "decscc_false"
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (minus:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")
                  (eq (reg:CC CC_REGNUM) (const_int 0))))]
  ""
  "decf\t%0")

;; ------------------------------------------------------------------------
;; Conditional move patterns.
;; ------------------------------------------------------------------------

(define_expand "smaxsi3"
  [(set (reg:CC CC_REGNUM)
        (lt:CC (match_operand:SI 1 "csky_arith_reg_operand" "")
               (match_operand:SI 2 "csky_arith_reg_operand" "")))
   (set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (if_then_else:SI (eq (reg:CC CC_REGNUM) (const_int 0))
                         (match_dup 1) (match_dup 2)))]
  ""
  "")

(define_expand "sminsi3"
  [(set (reg:CC CC_REGNUM)
        (lt:CC (match_operand:SI 1 "csky_arith_reg_operand" "")
               (match_operand:SI 2 "csky_arith_reg_operand" "")))
   (set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (if_then_else:SI (ne (reg:CC CC_REGNUM) (const_int 0))
                         (match_dup 1) (match_dup 2)))]
  ""
  "")

(define_expand "umaxsi3"
  [(set (reg:CC CC_REGNUM)
        (geu:CC (match_operand:SI 1 "csky_arith_reg_operand" "")
                (match_operand:SI 2 "csky_arith_reg_operand" "")))
   (set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (if_then_else:SI (eq (reg:CC CC_REGNUM) (const_int 0))
                         (match_dup 2) (match_dup 1)))]
  ""
  "")

(define_expand "uminsi3"
  [(set (reg:CC CC_REGNUM)
        (geu:CC (match_operand:SI 1 "csky_arith_reg_operand" "")
                (match_operand:SI 2 "csky_arith_reg_operand" "")))
   (set (match_operand:SI 0 "csky_arith_reg_operand" "")
        (if_then_else:SI (ne (reg:CC CC_REGNUM) (const_int 0))
                         (match_dup 2) (match_dup 1)))]
  ""
  "")

;; ------------------------------------------------------------------------
;; conditional move patterns really start here
;; ------------------------------------------------------------------------

(define_expand "movsicc"
 [(set (match_operand:SI 0 "register_operand" "")
       (if_then_else:SI (match_operand 1 "ordered_comparison_operator" "")
                        (match_operand:SI 2 "nonmemory_operand" "")
                        (match_operand:SI 3 "nonmemory_operand" "")))]
 ""
 "
 {
   bool invert;
   invert = csky_gen_compare (GET_CODE (operands[1]),
                              XEXP (operands[1], 0),
                              XEXP (operands[1], 1));
   if(invert)
     emit_insn(gen_movf(operands[0],operands[2],operands[3]));
   else
     emit_insn(gen_movt(operands[0],operands[2],operands[3]));
   DONE;
 }")

(define_insn "movt"
 [(set (match_operand:SI 0 "register_operand" "=r,r,r")
       (if_then_else:SI (ne (reg:CC CC_REGNUM) (const_int 0))
                        (match_operand:SI 1 "general_operand" "r,r,Ua")
                        (match_operand:SI 2 "general_operand" "r,Ua,r")))]
 ""
 "*{
  switch (which_alternative)
  {
    case 0:
      if ( rtx_equal_p (operands[0], operands[1]) )
        return \"movf\t%0, %2\";
      else if ( rtx_equal_p (operands[0], operands[2]) )
        return \"movt\t%0, %1\";
      else
        return \"movtf\t%0, %1, %2\";
    case 1:
      if ( rtx_equal_p (operands[0], operands[1]) )
        return \"clrf\t%0\";
      else
        return \"movt\t%0, %1\;clrf\t%0\";
    case 2:
      if ( rtx_equal_p (operands[0], operands[2]) )
        return \"clrt\t%0\";
      else
        return \"clrt\t%0\;movf\t%0, %2\";
    default:
      gcc_unreachable();  /* never reach here */
  }
 }"
 [(set_attr "length" "4,4,4")])

(define_insn "movf"
 [(set (match_operand:SI 0 "register_operand" "=r,r,r")
       (if_then_else:SI (eq (reg:CC CC_REGNUM) (const_int 0))
                        (match_operand:SI 1 "general_operand" "r,r,Ua")
                        (match_operand:SI 2 "general_operand" "r,Ua,r")))]
 ""
 "*{
  switch (which_alternative)
  {
    case 0:
      if ( rtx_equal_p (operands[0], operands[1]) )
        return \"movt\t%0, %2\";
      else if ( rtx_equal_p (operands[0], operands[2]) )
        return \"movf\t%0, %1\";
      else
        return \"movtf\t%0, %2, %1\";
    case 1:
      if ( rtx_equal_p (operands[0], operands[1]) )
        return \"clrt\t%0\";
      else
        return \"movf\t%0, %1\;clrt\t%0\";
    case 2:
      if ( rtx_equal_p (operands[0], operands[2]) )
        return \"clrf\t%0\";
      else
        return \"clrf\t%0\;movt\t%0, %2\";
    default:
      gcc_unreachable();  /* never reach here */
  }
 }"
 [(set_attr "length" "4,4,4")])

;; ------------------------------------------------------------------------
;; Bitfield extract (xtrbN)
;; ------------------------------------------------------------------------

(define_expand "extv"
  [(parallel [
     (set (match_operand:SI 0 "csky_arith_reg_operand" "")
          (sign_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "")
                           (match_operand:SI 2 "const_int_operand" "")
                           (match_operand:SI 3 "const_int_operand" "")))
     (clobber (reg:CC CC_REGNUM))])]
  ""
  "
{
  if (INTVAL (operands[2]) != 8 || INTVAL (operands[3]) % 8 != 0)
    FAIL;
}")

(define_expand "extzv"
  [(parallel [
     (set (match_operand:SI 0 "csky_arith_reg_operand" "")
          (zero_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "")
                           (match_operand:SI 2 "const_int_operand" "")
                           (match_operand:SI 3 "const_int_operand" "")))
     (clobber (reg:CC CC_REGNUM))])]
  ""
  "
{
  if (INTVAL (operands[2]) == 8 && INTVAL (operands[3]) % 8 == 0)
    {
       /* 8-bit field, aligned properly, use the xtrb[0123] sequence.  */
       /* Let the template generate some RTL....  */
    }
  else if (CONST_OK_FOR_K ((1 << INTVAL (operands[2])) - 1))
    {
      /* A narrow bit-field (<=5 bits) means we can do a shift to put
         it in place and then use an andi to extract it.
         This is as good as a shiftleft/shiftright.  */

      rtx shifted;
      rtx mask = GEN_INT ((1 << INTVAL (operands[2])) - 1);

      if (INTVAL (operands[3]) == 0)
        {
          shifted = operands[1];
        }
      else
        {
          rtx rshft = GEN_INT (INTVAL (operands[3]));
          shifted = gen_reg_rtx (SImode);
          emit_insn (gen_rtx_SET (shifted,
                         gen_rtx_LSHIFTRT (SImode, operands[1], rshft)));
        }
      emit_insn (gen_rtx_SET (operands[0],
                       gen_rtx_AND (SImode, shifted, mask)));
      DONE;
    }
  else
    {
      FAIL;
    }
}")

(define_expand "insv"
  [(set (zero_extract:SI (match_operand:SI 0 "csky_arith_reg_operand" "")
       (match_operand:SI 1 "const_int_operand" "")
       (match_operand:SI 2 "const_int_operand" ""))
       (match_operand:SI 3 "general_operand" ""))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "
{
  if (csky_expand_insv (operands))
    {
      DONE;
    }
  else
    {
      FAIL;
    }
}")

;;
;; the xtrb[0123] instructions handily get at 8-bit fields on nice boundaries.
;; but then, they do force you through r1.
;;
;; the combiner will build such patterns for us, so we'll make them available
;; for its use.
;;
;; Note that we have both SIGNED and UNSIGNED versions of these...
;;

;;
;; FIXME: Consider the clobbering of CC bit; not sure this is
;; good...
;; remember that xtrb may be split by the assembler
;;
;; the SIGNED versions of these
;;
(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,b")
        (sign_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "0,r")
                         (const_int 8) (const_int 24)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "@
  asri\t%0, 24
  xtrb0\t%0, %1\;sextb\t%0"
  [(set_attr "length" "2,6")])

(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=b")
        (sign_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "r")
                         (const_int 8) (const_int 16)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "xtrb1\t%0, %1\;sextb\t%0"
  [(set_attr "length" "6")])

(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=b")
        (sign_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "r")
                         (const_int 8) (const_int 8)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "xtrb2\t%0, %1\;sextb\t%0"
  [(set_attr "length" "6")])

(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (sign_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")
                         (const_int 8) (const_int 0)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "sextb\t%0"
  )

;; the UNSIGNED uses of xtrb[0123]
;;
(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r,b")
        (zero_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "0,r")
                         (const_int 8) (const_int 24)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "@
  lsri\t%0, 24
  xtrb0\t%0, %1"
  [(set_attr "length" "2,4")])

(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=b")
        (zero_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "r")
                         (const_int 8) (const_int 16)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "xtrb1\t%0, %1"
  [(set_attr "length" "4")])

(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=b")
        (zero_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "r")
                         (const_int 8) (const_int 8)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "xtrb2\t%0, %1"
  [(set_attr "length" "4")])

;; This can be peepholed if it follows a ldb ...
(define_insn ""
  [(set (match_operand:SI 0 "csky_arith_reg_operand" "=r")
        (zero_extract:SI (match_operand:SI 1 "csky_arith_reg_operand" "0")
                         (const_int 8) (const_int 0)))
   (clobber (reg:CC CC_REGNUM))]
  ""
  "zextb\t%0"
  )

;; TLS support
;; Load tls table pointer into r2
;; Doesn't clobber R3-R7.
(define_insn "load_tp_soft"
  [(set (reg:SI 2) (unspec:SI [(const_int 0)] UNSPEC_TLS))
   (clobber (reg:SI LK_REGNUM))
   (clobber (reg:CC CC_REGNUM))]
  "!flag_pic"
  "jbsr\t__read_tp"
)

(define_insn "load_tp_soft_pic"
  [(set (reg:SI 2) (unspec:SI [(const_int 0)] UNSPEC_TLS))
   (use (reg:SI GB_REGNUM))
   (clobber (reg:SI LK_REGNUM))
   (clobber (reg:CC CC_REGNUM))]
  "flag_pic"
  "lrw\tr2, __read_tp@PLT\;addu\tr2, gb\;ld.w\tr2, (r2, 0)\;jsr\tr2"
)

(define_insn "tls_get_symbol_1"
  [(set (match_operand:SI 0 "register_operand" "=a")
    (unspec:SI [(match_operand 1 "" "")
                (match_operand 2 "" "")
                (match_operand 3 "" "")]
                UNSPEC_TLS))
  (clobber (reg:SI LK_REGNUM))]
  ""
  "*
     /* Insert \".no_literal_dump 1\" to avoid dumping literals
        pool after bsr in assembler.  */
    asm_fprintf (asm_out_file, \"\t.no_literal_dump 1\\n\");
    output_asm_insn(\"bsr\t.LTLS%3\", operands);
    default_internal_label (asm_out_file, \"LTLS\",
                                INTVAL (operands[3]));
    switch (INTVAL (operands[2]))
      {
        case TLS_GD32:
            output_asm_insn(\"lrw\t%0, %1@TLSGD32\", operands);
            return \"addu\t%0, r15\";
        case TLS_LDM32:
            output_asm_insn(\"lrw\t%0, %1@TLSLDM32\", operands);
            return \"addu\t%0, r15\";
        case TLS_IE32:
            output_asm_insn(\"lrw\t%0, %1@GOTTPOFF\", operands);
            return \"addu\t%0, r15\";
        default:
            return \"\";
      }
  "
)

(define_insn "tls_get_symbol_2"
  [(set (match_operand:SI 0 "register_operand" "=a")
    (unspec:SI [(match_operand 1 "" "")
                (match_operand 2 "" "")]
                UNSPEC_TLS))]
  ""
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

(define_insn "pic_get_symbol"
  [(set (match_operand:SI 0 "register_operand" "=a")
    (unspec:SI [(match_operand 1 "" "")
                (match_operand 2 "" "")] UNSPEC_PIC))]
  ""
  "*
    switch (INTVAL (operands[2]))
      {
        case PIC_SYMBOL_GOTOFF:
          return \"lrw\t%0, %1@GOTOFF\";
        case PIC_SYMBOL_PLT:
          return \"lrw\t%0, %1@PLT\";
        case PIC_SYMBOL_GOT:
          return \"lrw\t%0, %1@GOT\";
        case PIC_SYMBOL_GOTPC:
          return \"lrw\t%0, %1@GOTPC\";
        default:
          gcc_unreachable ();
      }
  "
)

(define_insn "prologue_get_pc"
  [(set (reg:SI LK_REGNUM)
     (unspec:SI [(match_operand 0 "" "")] UNSPEC_GET_PC))]
  ""
  "*
  {
    /* Insert \".no_literal_dump 1\" to avoid dumping literals
       pool after bsr in assembler.  */
    asm_fprintf (asm_out_file, \"\t.no_literal_dump 1\\n\");
    output_asm_insn(\"bsr\t%l0\", operands);
    default_internal_label (asm_out_file, \"L\",
                   CODE_LABEL_NUMBER (XEXP(operands[0], 0)));
    return \"\";
  }
 "
)

;; Patterns for exception handling

(define_expand "eh_return"
  [(use (match_operand 0 "general_operand" ""))]
  "TARGET_EITHER"
  "
  {
    emit_insn (gen_csky_eh_return (operands[0]));
    DONE;
  }"
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
  "
  {
    csky_set_eh_return_address (operands[0], operands[1]);
    DONE;
  }"
)

;;-----------------------------------------------------------
;; Recompute gb in front of that which longjmp jump to.
;;-----------------------------------------------------------

(define_expand "builtin_setjmp_receiver"
  [(label_ref (match_operand 0 "" ""))]
  "flag_pic"
  "
{
  if (GB_REGNUM != INVALID_REGNUM)
    {
      rtx l1 = gen_label_rtx();
      rtx bsr_label = gen_rtx_LABEL_REF(SImode, l1);
      rtx reg_gb = gen_rtx_REG(SImode, GB_REGNUM);
      rtx reg_pc = gen_rtx_REG(SImode, LK_REGNUM);

      emit_insn (gen_prologue_get_pc (bsr_label));
      emit_insn (gen_pic_get_symbol
                 (reg_gb, bsr_label, GEN_INT (PIC_SYMBOL_GOTPC)));
      emit_insn (gen_addsi3 (reg_gb, reg_gb, reg_pc));
      emit_use (reg_gb);
    }
  DONE;
}")

;; patterns to generate stack size for callgraph
(define_insn "stack_size"
  [(unspec [(match_operand 0 "" "")
            (match_operand 1 "" "")]
    UNSPEC_STACK_SIZE)]
  ""
  ".stack_size\t%0, %1"
  [(set_attr "length"  "0")]
  )

(define_insn "trap"
  [(trap_if (const_int 1) (const_int 0))]
  ""
  "bkpt"
)

(include "fpuv1.md")
(include "dspv1.md")

