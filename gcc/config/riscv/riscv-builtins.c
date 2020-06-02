/* Subroutines used for expanding RISC-V builtins.
   Copyright (C) 2011-2019 Free Software Foundation, Inc.
   Contributed by Andrew Waterman (andrew@sifive.com).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "tree.h"
#include "gimple-expr.h"
#include "memmodel.h"
#include "expmed.h"
#include "profile-count.h"
#include "optabs.h"
#include "recog.h"
#include "diagnostic-core.h"
#include "stor-layout.h"
#include "expr.h"
#include "langhooks.h"
#include "stringpool.h"

/* Macros to create an enumeration identifier for a function prototype.  */
#define RISCV_FTYPE_NAME1(A, B) RISCV_##A##_FTYPE_##B
#define RISCV_FTYPE_NAME2(A, B, C) RISCV_##A##_FTYPE_##B##_##C
#define RISCV_FTYPE_NAME3(A, B, C, D) RISCV_##A##_FTYPE_##B##_##C##_##D
#define RISCV_FTYPE_NAME4(A, B, C, D, E) RISCV_##A##_FTYPE_##B##_##C##_##D##_##E
#define RISCV_FTYPE_NAME5(A, B, C, D, E, F) RISCV_##A##_FTYPE_##B##_##C##_##D##_##E##_##F
#define RISCV_FTYPE_NAME6(A, B, C, D, E, F, G) RISCV_##A##_FTYPE_##B##_##C##_##D##_##E##_##F##_##G

/* Classifies the prototype of a built-in function.  */
enum riscv_function_type {
#define DEF_RISCV_FTYPE(NARGS, LIST) RISCV_FTYPE_NAME##NARGS LIST,
#include "config/riscv/riscv-ftypes.def"
#include "config/riscv/riscv-ftypes-v.def"
#undef DEF_RISCV_FTYPE
  RISCV_MAX_FTYPE_MAX
};

/* Specifies how a built-in function should be converted into rtl.  */
enum riscv_builtin_type {
  /* The function corresponds directly to an .md pattern.  */
  RISCV_BUILTIN_DIRECT,

  /* Likewise, but with return type VOID.  */
  RISCV_BUILTIN_DIRECT_NO_TARGET
};

/* Declare an availability predicate for built-in functions.  */
#define AVAIL(NAME, COND)		\
 static unsigned int			\
 riscv_builtin_avail_##NAME (void)	\
 {					\
   return (COND);			\
 }

/* This structure describes a single built-in function.  */
struct riscv_builtin_description {
  /* The code of the main .md file instruction.  See riscv_builtin_type
     for more information.  */
  enum insn_code icode;

  /* The name of the built-in function.  */
  const char *name;

  /* Specifies how the function should be expanded.  */
  enum riscv_builtin_type builtin_type;

  /* The function's prototype.  */
  enum riscv_function_type prototype;

  /* Whether the function is available.  */
  unsigned int (*avail) (void);
};

AVAIL (hard_float, TARGET_HARD_FLOAT)
AVAIL (vector, TARGET_VECTOR)
AVAIL (vector64, TARGET_VECTOR_VLEN(64))
AVAIL (vector128, TARGET_VECTOR_VLEN(128))
AVAIL (vector64_hardfloat, TARGET_VECTOR_VLEN(64) && TARGET_HARD_FLOAT)
AVAIL (vector128_hardfloat, TARGET_VECTOR_VLEN(128) && TARGET_HARD_FLOAT)

/* Construct a riscv_builtin_description from the given arguments.

   INSN is the name of the associated instruction pattern, without the
   leading CODE_FOR_riscv_.

   NAME is the name of the function itself, without the leading
   "__builtin_riscv_".

   BUILTIN_TYPE and FUNCTION_TYPE are riscv_builtin_description fields.

   AVAIL is the name of the availability predicate, without the leading
   riscv_builtin_avail_.  */
#define RISCV_BUILTIN(INSN, NAME, BUILTIN_TYPE,	FUNCTION_TYPE, AVAIL)	\
  { CODE_FOR_riscv_ ## INSN, "__builtin_riscv_" NAME,			\
    BUILTIN_TYPE, FUNCTION_TYPE, riscv_builtin_avail_ ## AVAIL }

/* Define __builtin_riscv_<INSN>, which is a RISCV_BUILTIN_DIRECT function
   mapped to instruction CODE_FOR_riscv_<INSN>,  FUNCTION_TYPE and AVAIL
   are as for RISCV_BUILTIN.  */
#define DIRECT_BUILTIN(INSN, FUNCTION_TYPE, AVAIL)			\
  RISCV_BUILTIN (INSN, #INSN, RISCV_BUILTIN_DIRECT, FUNCTION_TYPE, AVAIL)

/* Define __builtin_riscv_<INSN>, which is a RISCV_BUILTIN_DIRECT_NO_TARGET
   function mapped to instruction CODE_FOR_riscv_<INSN>,  FUNCTION_TYPE
   and AVAIL are as for RISCV_BUILTIN.  */
#define DIRECT_NO_TARGET_BUILTIN(INSN, FUNCTION_TYPE, AVAIL)		\
  RISCV_BUILTIN (INSN, #INSN, RISCV_BUILTIN_DIRECT_NO_TARGET,		\
		FUNCTION_TYPE, AVAIL)

/* Argument types.  */
#define RISCV_ATYPE_VOID void_type_node
#define RISCV_ATYPE_UQI unsigned_intQI_type_node
#define RISCV_ATYPE_QI intQI_type_node
#define RISCV_ATYPE_UHI unsigned_intHI_type_node
#define RISCV_ATYPE_HI intHI_type_node
#define RISCV_ATYPE_USI unsigned_intSI_type_node
#define RISCV_ATYPE_SI intSI_type_node
#define RISCV_ATYPE_UDI unsigned_intDI_type_node
#define RISCV_ATYPE_DI intDI_type_node
#define RISCV_ATYPE_SF float_type_node
#define RISCV_ATYPE_DF double_type_node
#define RISCV_ATYPE_TF float128_type_node
#define RISCV_ATYPE_POINTER ptr_type_node
/* Vector Argument types.  */
#define RISCV_ATYPE_V8TI riscv_build_vector_type (intTI_type_node, V8TImode)
#define RISCV_ATYPE_V4TI riscv_build_vector_type (intTI_type_node, V4TImode)
#define RISCV_ATYPE_V2TI riscv_build_vector_type (intTI_type_node, V2TImode)
#define RISCV_ATYPE_V1TI riscv_build_vector_type (intTI_type_node, V1TImode)
#define RISCV_ATYPE_UV8TI riscv_build_vector_type (unsigned_intTI_type_node, V8TImode)
#define RISCV_ATYPE_UV4TI riscv_build_vector_type (unsigned_intTI_type_node, V4TImode)
#define RISCV_ATYPE_UV2TI riscv_build_vector_type (unsigned_intTI_type_node, V2TImode)
#define RISCV_ATYPE_UV1TI riscv_build_vector_type (unsigned_intTI_type_node, V1TImode)

#define RISCV_ATYPE_V16DI riscv_build_vector_type (intDI_type_node, V16DImode)
#define RISCV_ATYPE_V8DI riscv_build_vector_type (intDI_type_node, V8DImode)
#define RISCV_ATYPE_V4DI riscv_build_vector_type (intDI_type_node, V4DImode)
#define RISCV_ATYPE_V2DI riscv_build_vector_type (intDI_type_node, V2DImode)
#define RISCV_ATYPE_V1DI riscv_build_vector_type (intDI_type_node, V1DImode)
#define RISCV_ATYPE_UV16DI riscv_build_vector_type (unsigned_intDI_type_node, V16DImode)
#define RISCV_ATYPE_UV8DI riscv_build_vector_type (unsigned_intDI_type_node, V8DImode)
#define RISCV_ATYPE_UV4DI riscv_build_vector_type (unsigned_intDI_type_node, V4DImode)
#define RISCV_ATYPE_UV2DI riscv_build_vector_type (unsigned_intDI_type_node, V2DImode)
#define RISCV_ATYPE_UV1DI riscv_build_vector_type (unsigned_intDI_type_node, V1DImode)

#define RISCV_ATYPE_V32SI riscv_build_vector_type (intSI_type_node, V32SImode)
#define RISCV_ATYPE_V16SI riscv_build_vector_type (intSI_type_node, V16SImode)
#define RISCV_ATYPE_V8SI riscv_build_vector_type (intSI_type_node, V8SImode)
#define RISCV_ATYPE_V4SI riscv_build_vector_type (intSI_type_node, V4SImode)
#define RISCV_ATYPE_V2SI riscv_build_vector_type (intSI_type_node, V2SImode)
#define RISCV_ATYPE_UV32SI riscv_build_vector_type (unsigned_intSI_type_node, V32SImode)
#define RISCV_ATYPE_UV16SI riscv_build_vector_type (unsigned_intSI_type_node, V16SImode)
#define RISCV_ATYPE_UV8SI riscv_build_vector_type (unsigned_intSI_type_node, V8SImode)
#define RISCV_ATYPE_UV4SI riscv_build_vector_type (unsigned_intSI_type_node, V4SImode)
#define RISCV_ATYPE_UV2SI riscv_build_vector_type (unsigned_intSI_type_node, V2SImode)

#define RISCV_ATYPE_V64HI riscv_build_vector_type (intHI_type_node, V64HImode)
#define RISCV_ATYPE_V32HI riscv_build_vector_type (intHI_type_node, V32HImode)
#define RISCV_ATYPE_V16HI riscv_build_vector_type (intHI_type_node, V16HImode)
#define RISCV_ATYPE_V8HI riscv_build_vector_type (intHI_type_node, V8HImode)
#define RISCV_ATYPE_V4HI riscv_build_vector_type (intHI_type_node, V4HImode)
#define RISCV_ATYPE_V2HI riscv_build_vector_type (intHI_type_node, V2HImode)
#define RISCV_ATYPE_UV64HI riscv_build_vector_type (unsigned_intHI_type_node, V64HImode)
#define RISCV_ATYPE_UV32HI riscv_build_vector_type (unsigned_intHI_type_node, V32HImode)
#define RISCV_ATYPE_UV16HI riscv_build_vector_type (unsigned_intHI_type_node, V16HImode)
#define RISCV_ATYPE_UV8HI riscv_build_vector_type (unsigned_intHI_type_node, V8HImode)
#define RISCV_ATYPE_UV4HI riscv_build_vector_type (unsigned_intHI_type_node, V4HImode)
#define RISCV_ATYPE_UV2HI riscv_build_vector_type (unsigned_intHI_type_node, V2HImode)

#define RISCV_ATYPE_V128QI riscv_build_vector_type (intQI_type_node, V128QImode)
#define RISCV_ATYPE_V64QI riscv_build_vector_type (intQI_type_node, V64QImode)
#define RISCV_ATYPE_V32QI riscv_build_vector_type (intQI_type_node, V32QImode)
#define RISCV_ATYPE_V16QI riscv_build_vector_type (intQI_type_node, V16QImode)
#define RISCV_ATYPE_V8QI riscv_build_vector_type (intQI_type_node, V8QImode)
#define RISCV_ATYPE_V4QI riscv_build_vector_type (intQI_type_node, V4QImode)
#define RISCV_ATYPE_UV128QI riscv_build_vector_type (unsigned_intQI_type_node, V128QImode)
#define RISCV_ATYPE_UV64QI riscv_build_vector_type (unsigned_intQI_type_node, V64QImode)
#define RISCV_ATYPE_UV32QI riscv_build_vector_type (unsigned_intQI_type_node, V32QImode)
#define RISCV_ATYPE_UV16QI riscv_build_vector_type (unsigned_intQI_type_node, V16QImode)
#define RISCV_ATYPE_UV8QI riscv_build_vector_type (unsigned_intQI_type_node, V8QImode)
#define RISCV_ATYPE_UV4QI riscv_build_vector_type (unsigned_intQI_type_node, V4QImode)

#define RISCV_ATYPE_V8TF riscv_build_vector_type (float128_type_node, V8TFmode)
#define RISCV_ATYPE_V4TF riscv_build_vector_type (float128_type_node, V4TFmode)
#define RISCV_ATYPE_V2TF riscv_build_vector_type (float128_type_node, V2TFmode)
#define RISCV_ATYPE_V1TF riscv_build_vector_type (float128_type_node, V1TFmode)

#define RISCV_ATYPE_V16DF riscv_build_vector_type (double_type_node, V16DFmode)
#define RISCV_ATYPE_V8DF riscv_build_vector_type (double_type_node, V8DFmode)
#define RISCV_ATYPE_V4DF riscv_build_vector_type (double_type_node, V4DFmode)
#define RISCV_ATYPE_V2DF riscv_build_vector_type (double_type_node, V2DFmode)
#define RISCV_ATYPE_V1DF riscv_build_vector_type (double_type_node, V1DFmode)

#define RISCV_ATYPE_V32SF riscv_build_vector_type (float_type_node, V32SFmode)
#define RISCV_ATYPE_V16SF riscv_build_vector_type (float_type_node, V16SFmode)
#define RISCV_ATYPE_V8SF riscv_build_vector_type (float_type_node, V8SFmode)
#define RISCV_ATYPE_V4SF riscv_build_vector_type (float_type_node, V4SFmode)
#define RISCV_ATYPE_V2SF riscv_build_vector_type (float_type_node, V2SFmode)
#define RISCV_ATYPE_V1SF riscv_build_vector_type (float_type_node, V1SFmode)

static tree riscv_vector_intZI8_type_node = NULL_TREE;
static tree riscv_vector_intWI7_type_node = NULL_TREE;
static tree riscv_vector_intEI3_type_node = NULL_TREE;
static tree riscv_vector_intZI2_type_node = NULL_TREE;
static tree riscv_vector_intFI5_type_node = NULL_TREE;
static tree riscv_vector_intRI7_type_node = NULL_TREE;
static tree riscv_vector_intZI4_type_node = NULL_TREE;
static tree riscv_vector_intTI2_type_node = NULL_TREE;
static tree riscv_vector_intCI3_type_node = NULL_TREE;
static tree riscv_vector_intXI2_type_node = NULL_TREE;
static tree riscv_vector_intYI6_type_node = NULL_TREE;
static tree riscv_vector_intXI4_type_node = NULL_TREE;
static tree riscv_vector_intCI6_type_node = NULL_TREE;
static tree riscv_vector_intYI3_type_node = NULL_TREE;
static tree riscv_vector_intVI5_type_node = NULL_TREE;
static tree riscv_vector_intXI8_type_node = NULL_TREE;
static tree riscv_vector_intOI4_type_node = NULL_TREE;
static tree riscv_vector_intOI2_type_node = NULL_TREE;

#include "config/riscv/riscv-builtins-v-a.def"

/* Pointer Argument types. */
#define RISCV_ATYPE_DIPTR build_pointer_type (intDI_type_node)
#define RISCV_ATYPE_QIPTR build_pointer_type (intQI_type_node)
#define RISCV_ATYPE_HIPTR build_pointer_type (intHI_type_node)
#define RISCV_ATYPE_SIPTR build_pointer_type (intSI_type_node)

#define RISCV_ATYPE_UDIPTR build_pointer_type (unsigned_intDI_type_node)
#define RISCV_ATYPE_UQIPTR build_pointer_type (unsigned_intQI_type_node)
#define RISCV_ATYPE_UHIPTR build_pointer_type (unsigned_intHI_type_node)
#define RISCV_ATYPE_USIPTR build_pointer_type (unsigned_intSI_type_node)

#define RISCV_ATYPE_DFPTR build_pointer_type (double_type_node)
#define RISCV_ATYPE_SFPTR build_pointer_type (float_type_node)

/* RISCV_FTYPE_ATYPESN takes N RISCV_FTYPES-like type codes and lists
   their associated RISCV_ATYPEs.  */
#define RISCV_FTYPE_ATYPES1(A, B) \
  RISCV_ATYPE_##A, RISCV_ATYPE_##B
#define RISCV_FTYPE_ATYPES2(A, B, C)   \
  RISCV_ATYPE_##A, RISCV_FTYPE_ATYPES1(B, C)
#define RISCV_FTYPE_ATYPES3(A, B, C, D)       \
  RISCV_ATYPE_##A, RISCV_FTYPE_ATYPES2(B, C, D)
#define RISCV_FTYPE_ATYPES4(A, B, C, D, E)       \
  RISCV_ATYPE_##A, RISCV_FTYPE_ATYPES3(B, C, D, E)
#define RISCV_FTYPE_ATYPES5(A, B, C, D, E, F)       \
  RISCV_ATYPE_##A, RISCV_FTYPE_ATYPES4(B, C, D, E, F)
#define RISCV_FTYPE_ATYPES6(A, B, C, D, E, F, G)       \
  RISCV_ATYPE_##A, RISCV_FTYPE_ATYPES5(B, C, D, E, F, G)

static const struct riscv_builtin_description riscv_builtins[] = {
  DIRECT_BUILTIN (frflags, RISCV_USI_FTYPE_VOID, hard_float),
  DIRECT_NO_TARGET_BUILTIN (fsflags, RISCV_VOID_FTYPE_USI, hard_float),
  #include "config/riscv/riscv-builtins-v.def"
};

/* Index I is the function declaration for riscv_builtins[I], or null if the
   function isn't defined on this target.  */
static GTY(()) tree riscv_builtin_decls[ARRAY_SIZE (riscv_builtins)];

/* Get the index I of the function declaration for riscv_builtin_decls[I]
   using the instruction code or return null if not defined for the target.  */
static GTY(()) int riscv_builtin_decl_index[NUM_INSN_CODES];

#define GET_BUILTIN_DECL(CODE) \
  riscv_builtin_decls[riscv_builtin_decl_index[(CODE)]]

/* MODE is a vector mode whose elements have type TYPE.  Return the type
   of the vector itself.  */

static tree
riscv_build_vector_type (tree type, machine_mode mode)
{
  static tree types[2 * (int) MAX_MACHINE_MODE];
  int mode_index;

  mode_index = (int) mode;

  if (TREE_CODE (type) == INTEGER_TYPE && TYPE_UNSIGNED (type))
    mode_index += MAX_MACHINE_MODE;

  if (types[mode_index] == NULL_TREE)
    types[mode_index] = build_vector_type_for_mode (type, mode);
  return types[mode_index];
}

/* Return the function type associated with function prototype TYPE.  */

static tree
riscv_build_function_type (enum riscv_function_type type)
{
  static tree types[(int) RISCV_MAX_FTYPE_MAX];

  if (types[(int) type] == NULL_TREE)
    switch (type)
      {
#define DEF_RISCV_FTYPE(NUM, ARGS)					\
  case RISCV_FTYPE_NAME##NUM ARGS:					\
    types[(int) type]							\
      = build_function_type_list (RISCV_FTYPE_ATYPES##NUM ARGS,		\
				  NULL_TREE);				\
    break;
#include "config/riscv/riscv-ftypes.def"
#include "config/riscv/riscv-ftypes-v.def"
#undef DEF_RISCV_FTYPE
      default:
	gcc_unreachable ();
      }

  return types[(int) type];
}

struct {
  tree *node;
  const char *name;
  machine_mode mode;
} riscv_vector_types[] = {
  { &riscv_vector_intZI8_type_node, "__builtin_riscv_zi8", ZI8mode},
  { &riscv_vector_intWI7_type_node, "__builtin_riscv_wi7", WI7mode},
  { &riscv_vector_intEI3_type_node, "__builtin_riscv_ei3", EI3mode},
  { &riscv_vector_intZI2_type_node, "__builtin_riscv_zi2", ZI2mode},
  { &riscv_vector_intFI5_type_node, "__builtin_riscv_fi5", FI5mode},
  { &riscv_vector_intRI7_type_node, "__builtin_riscv_ri7", RI7mode},
  { &riscv_vector_intZI4_type_node, "__builtin_riscv_zi4", ZI4mode},
  { &riscv_vector_intTI2_type_node, "__builtin_riscv_ti2", TI2mode},
  { &riscv_vector_intCI3_type_node, "__builtin_riscv_ci3", CI3mode},
  { &riscv_vector_intXI2_type_node, "__builtin_riscv_xi2", XI2mode},
  { &riscv_vector_intYI6_type_node, "__builtin_riscv_yi6", YI6mode},
  { &riscv_vector_intXI4_type_node, "__builtin_riscv_xi4", XI4mode},
  { &riscv_vector_intCI6_type_node, "__builtin_riscv_ci6", CI6mode},
  { &riscv_vector_intYI3_type_node, "__builtin_riscv_yi3", YI3mode},
  { &riscv_vector_intVI5_type_node, "__builtin_riscv_vi5", VI5mode},
  { &riscv_vector_intXI8_type_node, "__builtin_riscv_xi8", XI8mode},
  { &riscv_vector_intOI4_type_node, "__builtin_riscv_oi4", OI4mode},
  { &riscv_vector_intOI2_type_node, "__builtin_riscv_oi2", OI2mode},
};

static void
riscv_init_vector_types (void)
{
  tree tdecl;

  for (int i = 0; i < ARRAY_SIZE(riscv_vector_types); i++)
    {
      if (riscv_vector_types[i].node == NULL)
        continue;
      *(riscv_vector_types[i].node) = make_signed_type (GET_MODE_PRECISION (riscv_vector_types[i].mode));
      SET_TYPE_MODE (*(riscv_vector_types[i].node), riscv_vector_types[i].mode);
      tdecl = add_builtin_type
        (riscv_vector_types[i].name , *(riscv_vector_types[i].node));
      TYPE_NAME (*(riscv_vector_types[i].node)) = tdecl;
    }
}

const char *
riscv_mangle_builtin_type (const_tree type)
{
  for (int i = 0; i < ARRAY_SIZE(riscv_vector_types); i++)
    {
      if (TREE_CODE (TYPE_NAME (type)) == TYPE_DECL
          && DECL_NAME (TYPE_NAME (type))
          && !strcmp (IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (type))), riscv_vector_types[i].name))
        return riscv_vector_types[i].name;
    }
  return NULL;
}

/* Implement TARGET_INIT_BUILTINS.  */

void
riscv_init_builtins (void)
{
  riscv_init_vector_types();

  for (size_t i = 0; i < ARRAY_SIZE (riscv_builtins); i++)
    {
      const struct riscv_builtin_description *d = &riscv_builtins[i];
      if (d->avail ())
	{
	  tree type = riscv_build_function_type (d->prototype);
          size_t fcode = i;
          if (TARGET_VECTOR)
            fcode = 0;
	  riscv_builtin_decls[i]
	    = add_builtin_function (d->name, type, fcode, BUILT_IN_MD, NULL, NULL);
	  riscv_builtin_decl_index[d->icode] = i;
	}
    }
}

/* Implement TARGET_BUILTIN_DECL.  */

tree
riscv_builtin_decl (unsigned int code, bool initialize_p ATTRIBUTE_UNUSED)
{
  if (code >= ARRAY_SIZE (riscv_builtins))
    return error_mark_node;
  return riscv_builtin_decls[code];
}

/* Take argument ARGNO from EXP's argument list and convert it into
   an expand operand.  Store the operand in *OP.  */

static void
riscv_prepare_builtin_arg (struct expand_operand *op, tree exp, unsigned argno)
{
  tree arg = CALL_EXPR_ARG (exp, argno);
  create_input_operand (op, expand_normal (arg), TYPE_MODE (TREE_TYPE (arg)));
}

/* Expand instruction ICODE as part of a built-in function sequence.
   Use the first NOPS elements of OPS as the instruction's operands.
   HAS_TARGET_P is true if operand 0 is a target; it is false if the
   instruction has no target.

   Return the target rtx if HAS_TARGET_P, otherwise return const0_rtx.  */

static rtx
riscv_expand_builtin_insn (enum insn_code icode, unsigned int n_ops,
			   struct expand_operand *ops, bool has_target_p)
{
  if (!maybe_expand_insn (icode, n_ops, ops))
    {
      error ("invalid argument to built-in function");
      return has_target_p ? gen_reg_rtx (ops[0].mode) : const0_rtx;
    }

  return has_target_p ? ops[0].value : const0_rtx;
}

/* Expand a RISCV_BUILTIN_DIRECT or RISCV_BUILTIN_DIRECT_NO_TARGET function;
   HAS_TARGET_P says which.  EXP is the CALL_EXPR that calls the function
   and ICODE is the code of the associated .md pattern.  TARGET, if nonnull,
   suggests a good place to put the result.  */

static rtx
riscv_expand_builtin_direct (enum insn_code icode, rtx target, tree exp,
			     bool has_target_p)
{
  struct expand_operand ops[MAX_RECOG_OPERANDS];

  /* Map any target to operand 0.  */
  int opno = 0;
  if (has_target_p)
    create_output_operand (&ops[opno++], target, TYPE_MODE (TREE_TYPE (exp)));

  /* Map the arguments to the other operands.  */
  gcc_assert (opno + call_expr_nargs (exp)
	      == insn_data[icode].n_generator_args);
  for (int argno = 0; argno < call_expr_nargs (exp); argno++)
    riscv_prepare_builtin_arg (&ops[opno++], exp, argno);

  return riscv_expand_builtin_insn (icode, opno, ops, has_target_p);
}

/* Implement TARGET_EXPAND_BUILTIN.  */

rtx
riscv_expand_builtin (tree exp, rtx target, rtx subtarget ATTRIBUTE_UNUSED,
		      machine_mode mode ATTRIBUTE_UNUSED,
		      int ignore ATTRIBUTE_UNUSED)
{
  tree fndecl = TREE_OPERAND (CALL_EXPR_FN (exp), 0);
  unsigned int fcode = DECL_FUNCTION_CODE (fndecl);
  const struct riscv_builtin_description *d = &riscv_builtins[fcode];

  if (TARGET_VECTOR)
    {
      tree id = DECL_NAME(fndecl);
      for (size_t i = 0; i < ARRAY_SIZE(riscv_builtins); i++)
        {
          d = &riscv_builtins[i];
          if (d->avail () && id == get_identifier(d->name))
            break;
        }

      if (!d->avail () || id != get_identifier(d->name))
        gcc_unreachable();
    }

  switch (d->builtin_type)
    {
    case RISCV_BUILTIN_DIRECT:
      return riscv_expand_builtin_direct (d->icode, target, exp, true);

    case RISCV_BUILTIN_DIRECT_NO_TARGET:
      return riscv_expand_builtin_direct (d->icode, target, exp, false);
    }

  gcc_unreachable ();
}

/* Implement TARGET_ATOMIC_ASSIGN_EXPAND_FENV.  */

void
riscv_atomic_assign_expand_fenv (tree *hold, tree *clear, tree *update)
{
  if (!TARGET_HARD_FLOAT)
    return;

  tree frflags = GET_BUILTIN_DECL (CODE_FOR_riscv_frflags);
  tree fsflags = GET_BUILTIN_DECL (CODE_FOR_riscv_fsflags);
  tree old_flags = create_tmp_var_raw (RISCV_ATYPE_USI);

  *hold = build2 (MODIFY_EXPR, RISCV_ATYPE_USI, old_flags,
		  build_call_expr (frflags, 0));
  *clear = build_call_expr (fsflags, 1, old_flags);
  *update = NULL_TREE;
}
