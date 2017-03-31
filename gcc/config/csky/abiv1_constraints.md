;; Constraint definitions for the CSKY
;; Copyright (C) 2011-2016 Free Software Foundation, Inc.

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

;; Register constraints.
(define_register_constraint "a" "LRW_REGS" "R1 - R14")

(define_register_constraint "b" "RWCPCR_REGS" "R0 - R7")

(define_register_constraint "c" "C_REGS" "C")

(define_register_constraint "y" "HILO_REGS" "HI & LO")

(define_register_constraint "l" "LO_REGS" "LO")

(define_register_constraint "h" "HI_REGS" "HI")

(define_register_constraint "f" "FPU_REGS" "FPU REGS")

;; Integer constraints.
(define_constraint "I"
  "An integer in the range 0 to 127."
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_I (ival)")))

(define_constraint "J"
  "An integer in the range 1 to 32."
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_J (ival)")))

(define_constraint "K"
  "A shift operand, an integer in the range 0 to 31."
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_K (ival)")))

(define_constraint "L"
  "A negative arithmetic operand in the range -32 to -1."
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_L (ival)")))

(define_constraint "M"
  "A constant loadable by bgeni."
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_M (ival)")))

(define_constraint "N"
  "A constant loadable by bmaski, including -1."
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_N (ival)")))

(define_constraint "O"
  "Constant in range [-31,0]"
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_O (ival)")))

(define_constraint "P"
  "A value that can be generated without an lrw instruction."
  (and (match_code "const_int")
       (match_test "csky_const_ok_for_inline (ival)")))

;; Other constraints.
(define_constraint "R"
  "memory operands whose address only accept label_ref"
  (and (match_code "mem")
       (match_test "GET_CODE (XEXP (op, 0)) == LABEL_REF")))

(define_constraint "S"
  "An integer constant with 0, 1, or 2 bits clear."
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_S (ival)")))

(define_constraint "T"
  "An integer constant with 2 set bits."
  (and (match_code "const_int")
       (match_test "CONST_OK_FOR_T (ival)")))

(define_constraint "Ua"
  "The integer constant zero."
  (and (match_code "const_int")
       (match_test "ival == 0")))
