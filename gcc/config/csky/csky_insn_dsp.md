;; C-SKY DSP instruction descriptions.
;; Copyright (C) 2018-2023 Free Software Foundation, Inc.
;; Contributed by C-SKY Microsystems and Mentor Graphics.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify it
;; under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.
;;
;; GCC is distributed in the hope that it will be useful, but
;; WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;; General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.  */

;; ------------------------------------------------------------
;; DSP insns
;; ------------------------------------------------------------

(define_expand "mulsidi3"
  [(set (match_operand:DI			   0 "register_operand" "")
	(mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" ""))
		 (sign_extend:DI (match_operand:SI 2 "register_operand" ""))))]
  "TARGET_DSP || CSKY_ISA_FEATURE(3E3r1)"
  ""
)

(define_insn "*dsp_mulsidi3"
  [(set (match_operand:DI			   0 "register_operand" "=y")
	(mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
		 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "TARGET_DSP"
  "muls\t%1, %2"
  [(set_attr "type" "alu")
   (set_attr "length" "4")])

(define_insn "*3er1_mulsidi3"
  [(set (match_operand:DI			   0 "register_operand" "=r")
	(mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
		 (sign_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mul.s32\t%0, %1, %2"
  [(set_attr "type" "alu")
   (set_attr "length" "4")])

(define_expand "umulsidi3"
  [(set (match_operand:DI			   0 "register_operand" "")
	(mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" ""))
		 (zero_extend:DI (match_operand:SI 2 "register_operand" ""))))]
  "TARGET_DSP || CSKY_ISA_FEATURE(3E3r1)"
  ""
)

(define_insn "*dsp_umulsidi3"
  [(set (match_operand:DI			   0 "register_operand" "=y")
	(mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
		 (zero_extend:DI (match_operand:SI 2 "register_operand" "r"))))]
  "TARGET_DSP"
  "mulu\t%1, %2"
)

(define_insn "*3er1_umulsidi3"
  [(set (match_operand:DI			   0 "register_operand" "=r")
	(mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" " r"))
		 (zero_extend:DI (match_operand:SI 2 "register_operand" " r"))))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "mul.u32\t%0, %1, %2"
  [(set_attr "type" "alu")
   (set_attr "length" "4")])

(define_expand "maddsidi4"
  [(set (match_operand:DI				    0 "register_operand" "")
	(plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" ""))
			  (sign_extend:DI (match_operand:SI 2 "register_operand" "")))
		 (match_operand:DI			    3 "register_operand" "")))]
  "TARGET_DSP || CSKY_ISA_FEATURE(3E3r1)"
  ""
)

(define_insn "*dsp_maddsidi4"
  [(set (match_operand:DI				    0 "register_operand" "=y")
	(plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
			  (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))
		 (match_operand:DI			    3 "register_operand" "0")))]
  "TARGET_DSP"
  "mulsa\t%1, %2"
)

(define_insn_and_split "*3e3r1_maddsidi4"
  [(set (match_operand:DI				    0 "register_operand" "=r,&r")
	(plus:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r,r"))
			  (sign_extend:DI (match_operand:SI 2 "register_operand" "r,r")))
		 (match_operand:DI			    3 "register_operand" "0,r")))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "@
   mula.s32\t%0, %1, %2
   #"
  "reload_completed && !rtx_equal_p (operands[0], operands[3])"
  [(const_int 0)]
  {
    emit_move_insn (operands[0], operands[3]);
    emit_insn (gen_maddsidi4 (operands[0], operands[1], operands[2], operands[0]));
    DONE;
  }
  [(set_attr "type" "alu,alu")
   (set_attr "length" "4,6")])

(define_expand "umaddsidi4"
  [(set (match_operand:DI				    0 "register_operand" "")
	(plus:DI (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" ""))
			  (zero_extend:DI (match_operand:SI 2 "register_operand" "")))
		 (match_operand:DI			    3 "register_operand" "")))]
  "TARGET_DSP || CSKY_ISA_FEATURE(3E3r1)"
  ""
)

(define_insn "*dsp_umaddsidi4"
  [(set (match_operand:DI				    0 "register_operand" "=y")
	(plus:DI (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
			  (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))
		 (match_operand:DI			    3 "register_operand" "0")))]
  "TARGET_DSP"
  "mulua\t%1, %2"
)

(define_insn_and_split "*3e3r1_umaddsidi4"
  [(set (match_operand:DI				    0 "register_operand" "=r,&r")
	(plus:DI (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r,r"))
			  (zero_extend:DI (match_operand:SI 2 "register_operand" "r,r")))
		 (match_operand:DI			    3 "register_operand" "0,r")))]
  "CSKY_ISA_FEATURE(3E3r1)"
  "@
   mula.u32\t%0, %1, %2
   #"
  "reload_completed && !rtx_equal_p (operands[0], operands[3])"
  [(const_int 0)]
  {
    emit_move_insn (operands[0], operands[3]);
    emit_insn (gen_umaddsidi4 (operands[0], operands[1], operands[2], operands[0]));
    DONE;
  }
  [(set_attr "type" "alu,alu")
   (set_attr "length" "4,6")])

(define_insn "msubsidi4"
  [(set (match_operand:DI				     0 "register_operand" "=y")
	(minus:DI (match_operand:DI			     3 "register_operand" "0")
		  (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
			   (sign_extend:DI (match_operand:SI 2 "register_operand" "r")))))]
  "TARGET_DSP"
  "mulss\t%1, %2"
)

(define_insn "umsubsidi4"
  [(set (match_operand:DI				     0 "register_operand" "=y")
	(minus:DI (match_operand:DI			     3 "register_operand" "0")
		  (mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" "r"))
			   (zero_extend:DI (match_operand:SI 2 "register_operand" "r")))))]
  "TARGET_DSP"
  "mulus\t%1, %2"
)

(define_insn "*mulall_s16_0"
  [(set (match_operand:SI 0 "register_operand"			 "=r")
	(plus:SI (match_operand:SI 3 "register_operand"		 " 0")
		 (mult:SI (match_operand:SI 1 "register_operand" " r")
			  (match_operand:SI 2 "register_operand" " r"))))]
  "CSKY_ISA_FEATURE (3E3r1)"
  "mula.32.l\t%0, %1, %2"
  [(set_attr "type" "alu")
   (set_attr "length" "4")])

(define_insn "*mulall_s16_1"
  [(set (match_operand:SI 0 "register_operand"			 "=r")
	(plus:SI (mult:SI (match_operand:SI 1 "register_operand" " r")
			  (match_operand:SI 2 "register_operand" " r"))
		 (match_operand:SI 3 "register_operand"		 " 0")))]
  "CSKY_ISA_FEATURE (3E3r1)"
  "mula.32.l\t%0, %1, %2"
  [(set_attr "type" "alu")
   (set_attr "length" "4")])

;; ------------------------------------------------------------
;; DSPV2 insns
;; ------------------------------------------------------------

(define_insn "dspv2_adddi3"
  [(set (match_operand:DI          0 "register_operand" "=r")
	(plus:DI (match_operand:DI 1 "register_operand" "%r")
		 (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "add.64\t%0, %1, %2"
  [(set_attr "length" "4")]
)

(define_insn "dspv2_subdi3"
  [(set (match_operand:DI          0 "register_operand" "=r")
        (minus:DI (match_operand:DI 1 "register_operand" "r")
                  (match_operand:DI 2 "register_operand" "r")))]
  "CSKY_ISA_FEATURE(dspv2)"
  "sub.64\t%0, %1, %2"
  [(set_attr "length" "4")]
)

(define_insn "*dspv2_addhusi3"
  [(set (match_operand:SI			0 "register_operand"  "=r")
	(lshiftrt:SI (plus:SI (match_operand:SI 1 "register_operand"  "%r")
			      (match_operand:SI 2 "register_operand"  "r"))
		     (const_int 1)))]
  "CSKY_ISA_FEATURE(dspv2)"
  "addh.u32\t%0, %1, %2"
  [(set_attr "length" "4")]
)

(define_insn "*dspv2_subhusi3"
  [(set (match_operand:SI			 0 "register_operand"  "=r")
	(lshiftrt:SI (minus:SI (match_operand:SI 1 "register_operand"  "%r")
			       (match_operand:SI 2 "register_operand"  "r"))
		     (const_int 1)))]
  "CSKY_ISA_FEATURE(dspv2)"
  "subh.u32\t%0, %1, %2"
  [(set_attr "length" "4")]
)

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

(define_insn "smulsi3_highpart"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(truncate:SI
	  (lshiftrt:DI (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
				(sign_extend:DI (match_operand:SI 2 "register_operand" "r")))
                       (const_int 32))))]
  "CSKY_ISA_FEATURE(dspv2)"
  "mul.s32.h\t%0, %1, %2"
  [(set_attr "type" "alu")
   (set_attr "length" "4")])
