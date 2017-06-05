;; Predicate definitions for CSKY.
;; Copyright (C) 2005-2016 Free Software Foundation, Inc.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.
;;
;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;; Nonzero if OP is a normal arithmetic register.

(define_predicate "csky_arith_reg_operand"
  (match_code "reg,subreg")
{
  if (GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);

  return (REG_P (op)
    && (REGNO (op) >= FIRST_PSEUDO_REGISTER
         || REGNO_REG_CLASS (REGNO (op)) != C_REGS));

})

;; Nonzero if OP is a valid source operand for an arithmetic insn.

(define_predicate "csky_arith_J_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT && CONST_OK_FOR_J (INTVAL (op)))
    return 1;

  return 0;
})

;; Nonzero if OP is a valid source operand for an arithmetic insn.

(define_predicate "csky_arith_K_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT && CONST_OK_FOR_K (INTVAL (op)))
    return 1;

  return 0;
})

;; Nonzero if OP is a valid source operand for an arithmetic insn.

(define_predicate "csky_arith_S_operand"
  (match_code "reg,subreg,const_int")
{
  if (csky_arith_reg_operand (op, mode))
      return 1;

  if (CONST_INT_P (op) && CONST_OK_FOR_S (INTVAL(op)))
      return 1;

  return 0;
})

;; Nonzero if OP is a valid source operand for a shift or rotate insn.

(define_predicate "csky_arith_K_operand_not_0"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (   GET_CODE (op) == CONST_INT
      && CONST_OK_FOR_K (INTVAL (op))
      && INTVAL (op) != 0)
    return 1;

  return 0;
})

;; TODO: Add a comment here.

(define_predicate "csky_arith_M_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT && CONST_OK_FOR_M (INTVAL (op)))
    return 1;

  return 0;
})

;; TODO: Add a comment here.

(define_predicate "csky_arith_K_S_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT)
    {
      if (CONST_OK_FOR_K (INTVAL (op)) || (csky_num_zeros (INTVAL (op)) <= 2))
        return 1;
    }

  return 0;
})

;; Nonzero if OP is a valid source operand for a cmov with two consts
;; +/- 1.

(define_predicate "csky_arith_O_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT && CONST_OK_FOR_O (INTVAL (op)))
    return 1;

  return 0;
})

;; Nonzero if OP is a valid source operand for a 'or' insn.

(define_predicate "csky_arith_T_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT && CONST_OK_FOR_T (INTVAL (op)))
    return 1;

  return 0;
})

;; Nonzero if OP is a valid source operand for loading.

(define_predicate "csky_arith_imm_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT && const_ok_for_csky (INTVAL (op)))
    return 1;

  return 0;
})

;; TODO: Add a comment here.

(define_predicate "csky_arith_any_imm_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT)
    return 1;

  return 0;
})

;; Nonzero if OP is a valid source operand for a btsti.

(define_predicate "csky_literal_K_operand"
  (match_code "const_int")
{
  if (GET_CODE (op) == CONST_INT && CONST_OK_FOR_K (INTVAL (op)))
    return 1;

  return 0;
})

;; Nonzero if OP is a valid source operand for an add/sub insn.

(define_predicate "csky_addsub_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT)
    {
      /* We do need to check to make sure that the constant is not too
      big, especially if we are running on a 64-bit OS...  */
      if (trunc_int_for_mode (INTVAL (op), mode) != INTVAL (op))
        return 0;

      return 1;
    }

  return 0;
})

;; Nonzero if OP is a valid source operand for a compare operation.

(define_predicate "csky_compare_operand"
  (match_code "const_int,reg,subreg")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_INT && INTVAL (op) == 0)
    return 1;

  return 0;
})

;; Return 1 if OP is a load multiple operation.  It is known to be a
;; PARALLEL and the first section will be tested.

(define_predicate "csky_load_multiple_operation"
  (match_code "parallel")
{
  int count = XVECLEN (op, 0);
  int dest_regno;
  rtx src_addr;
  int i;

  /* Perform a quick check so we don't blow up below.  */
  if (count <= 1
      || GET_CODE (XVECEXP (op, 0, 0)) != SET
      || GET_CODE (SET_DEST (XVECEXP (op, 0, 0))) != REG
      || GET_CODE (SET_SRC (XVECEXP (op, 0, 0))) != MEM)
    return 0;

  dest_regno = REGNO (SET_DEST (XVECEXP (op, 0, 0)));
  src_addr = XEXP (SET_SRC (XVECEXP (op, 0, 0)), 0);

  for (i = 1; i < count; i++)
    {
      rtx elt = XVECEXP (op, 0, i);

      if (GET_CODE (elt) != SET
          || GET_CODE (SET_DEST (elt)) != REG
          || GET_MODE (SET_DEST (elt)) != SImode
          || REGNO (SET_DEST (elt))    != (unsigned) (dest_regno + i)
          || GET_CODE (SET_SRC (elt))  != MEM
          || GET_MODE (SET_SRC (elt))  != SImode
          || GET_CODE (XEXP (SET_SRC (elt), 0)) != PLUS
          || ! rtx_equal_p (XEXP (XEXP (SET_SRC (elt), 0), 0), src_addr)
          || GET_CODE (XEXP (XEXP (SET_SRC (elt), 0), 1)) != CONST_INT
          || INTVAL (XEXP (XEXP (SET_SRC (elt), 0), 1)) != i * 4)
        return 0;
    }

  return 1;
})

;; Similar, but tests for store multiple.

(define_predicate "csky_store_multiple_operation"
  (match_code "parallel")
{
  int count = XVECLEN (op, 0);
  int src_regno;
  rtx dest_addr;
  int i;

  /* Perform a quick check so we don't blow up below.  */
  if (count <= 1
      || GET_CODE (XVECEXP (op, 0, 0)) != SET
      || GET_CODE (SET_DEST (XVECEXP (op, 0, 0))) != MEM
      || GET_CODE (SET_SRC (XVECEXP (op, 0, 0))) != REG)
    return 0;

  src_regno = REGNO (SET_SRC (XVECEXP (op, 0, 0)));
  dest_addr = XEXP (SET_DEST (XVECEXP (op, 0, 0)), 0);

  for (i = 1; i < count; i++)
    {
      rtx elt = XVECEXP (op, 0, i);

      if (GET_CODE (elt) != SET
          || GET_CODE (SET_SRC (elt)) != REG
          || GET_MODE (SET_SRC (elt)) != SImode
          || REGNO (SET_SRC (elt)) != (unsigned) (src_regno + i)
          || GET_CODE (SET_DEST (elt)) != MEM
          || GET_MODE (SET_DEST (elt)) != SImode
          || GET_CODE (XEXP (SET_DEST (elt), 0)) != PLUS
          || ! rtx_equal_p (XEXP (XEXP (SET_DEST (elt), 0), 0), dest_addr)
          || GET_CODE (XEXP (XEXP (SET_DEST (elt), 0), 1)) != CONST_INT
          || INTVAL (XEXP (XEXP (SET_DEST (elt), 0), 1)) != i * 4)
        return 0;
    }

  return 1;
})

;; TODO: Add a comment here.

(define_predicate "csky_call_address_operand"
  (match_code "reg,subreg,symbol_ref")
{
  if (!flag_pic && (GET_CODE (op) == SYMBOL_REF))
    return 1;
  if (csky_arith_reg_operand (op, mode))
    return 1;
  return 0;
})

;; Nonzero if OP is a register or constant value of +/-1

(define_predicate "csky_arith_int1m1_operand"
    (match_code "reg,subreg,const_int")
{
    if (csky_arith_reg_operand (op, mode))
        return 1;

    if (op == const1_rtx || op == constm1_rtx)
        return 1;

    return 0;
})

;; Accept the floating point constant 0

(define_predicate "csky_const_float_0"
  (and (match_code "const_double")
       (match_test "op == CONST0_RTX (mode)")))

;; Accept the floating point constant 1

(define_predicate "csky_const_float_1"
  (and (match_code "const_double")
       (match_test "op == CONST1_RTX (mode)")))

;; Nonzero if OP is a valid source operand for a compare operation.

(define_predicate "csky_compare_operand_float"
  (match_code "const_double,reg,subreg")
{
    if (csky_arith_reg_operand (op, mode))
        return 1;

    if (GET_CODE (op) == CONST_DOUBLE
          && csky_const_float_0 (op, mode))
        return 1;

    return 0;
})

;; Nonzero if OP is a valid source operand for an arithmetic insn or float 1.

(define_predicate "csky_arith_float1_operand"
  (match_code "reg,subreg,const_double")
{
  if (csky_arith_reg_operand (op, mode))
    return 1;

  if (GET_CODE (op) == CONST_DOUBLE
        && csky_const_float_1 (op, mode))
    return 1;

  return 0;
})
