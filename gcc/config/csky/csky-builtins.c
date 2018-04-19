#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "target.h"
#include "function.h"
#include "rtl.h"
#include "tree.h"
#include "gimple-expr.h"
#include "tm_p.h"
#include "optabs.h"
#include "emit-rtl.h"
#include "recog.h"
#include "diagnostic-core.h"
#include "fold-const.h"
#include "stor-layout.h"
#include "explow.h"
#include "expr.h"
#include "langhooks.h"
#include "case-cfn-macros.h"

typedef enum {
  CSKY_ARG_COPY_TO_REG,
  CSKY_ARG_CONSTANT,
  CSKY_ARG_LANE_INDEX,
  CSKY_ARG_STRUCT_LOAD_STORE_LANE_INDEX,
  CSKY_ARG_MEMORY,
  CSKY_ARG_IMM_UT,
  CSKY_ARG_INDEX03,
  CSKY_ARG_INDEX01,
  CSKY_ARG_INDEXV128,
  CSKY_ARG_OFFSET2K,
  CSKY_ARG_OFFSET4K,
  CSKY_ARG_IMM_U31,
  CSKY_ARG_INDEXV64,
  CSKY_ARG_STOP
} builtin_arg;

#define SIMD_MAX_BUILTIN_ARGS 5

enum csky_type_qualifiers
{
  /* T foo.  */
  qualifier_none = 0x0,
  /* unsigned T foo.  */
  qualifier_unsigned = 0x1, /* 1 << 0  */
  /* Used when expanding arguments if an operand could
     be an immediate.  */
  qualifier_immediate = 0x2, /* 1 << 1  */
  /* Used when expanding arguments if an operand could
     be an immediate or register .  */
  qualifier_maybe_immediate = 0x4, /* 1 << 2  */
  /* void foo (...).  */
  qualifier_void = 0x8, /* 1 << 3 */
  /* imm 0-15 */
  qualifier_immUt = 0x10, /* 1<<4 */
  /* index 0-3 */
  qualifier_index03 = 0x20, /* 1<<5 */
  /* index 0-1 */
  qualifier_index01 = 0x40, /* 1<<6 */
  /* index for vector 128, 0-15|0-7|0-3 */
  qualifier_indexv128 = 0x80, /* 1<<7 */
  /* offset +2k */
  qualifier_offset2k = 0x100, /* 1<<8 */
  /* offset +4k */
  qualifier_offset4k = 0x200, /* 1<<9 */
  /* imm 0-31 */
  qualifier_immU31 = 0x400, /* 1<<10 */
  /* index for vector 64, 0-7|0-3|0-1 */
  qualifier_indexv64 = 0x800 /* 1<<11 */
};

/* T (T).  */
static enum csky_type_qualifiers
csky_unop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none };
#define UNOP_QUALIFIERS (csky_unop_qualifiers)

/* unsigned T (unsigned T).  */
static enum csky_type_qualifiers
csky_unuop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned };
#define UNUOP_QUALIFIERS (csky_unuop_qualifiers)

/* T (T, T).  */
static enum csky_type_qualifiers
csky_binop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_none };
#define BINOP_QUALIFIERS (csky_binop_qualifiers)

/* unsigned T (unsigned T, unsigned T).  */
static enum csky_type_qualifiers
csky_binuop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned };
#define BINUOP_QUALIFIERS (csky_binuop_qualifiers)

/* T (T, T, T).  */
static enum csky_type_qualifiers
csky_ternop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_none, qualifier_none };
#define TERNOP_QUALIFIERS (csky_ternop_qualifiers)

/* unsigned T (unsigned T, unsigned T, unsigned T).  */
static enum csky_type_qualifiers
csky_ternuop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned, qualifier_unsigned };
#define TERNUOP_QUALIFIERS (csky_ternuop_qualifiers)

/* T (T, imm0-15, T, imm0-15).  */
static enum csky_type_qualifiers
csky_pkg_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_immUt, qualifier_none, qualifier_immUt };
#define PKG_QUALIFIERS (csky_pkg_qualifiers)

/* T (T, imm0-31).  */
static enum csky_type_qualifiers
csky_binopu31_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_immU31 };
#define BINOPU31_QUALIFIERS (csky_binopu31_qualifiers)

/* unsigned T (unsigned T, imm0-31).  */
static enum csky_type_qualifiers
csky_binopu31u_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned, qualifier_immU31 };
#define BINOPU31U_QUALIFIERS (csky_binopu31u_qualifiers)

/* T (T, index0-3).  */
static enum csky_type_qualifiers
csky_binopi3_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_index03 };
#define BINOPI3_QUALIFIERS (csky_binopi3_qualifiers)

/* T (T, index0-1).  */
static enum csky_type_qualifiers
csky_binopi1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_index01 };
#define BINOPI1_QUALIFIERS (csky_binopi1_qualifiers)

/* T (T, indexv128).  */
static enum csky_type_qualifiers
csky_binopv128_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_indexv128 };
#define BINOPV128_QUALIFIERS (csky_binopv128_qualifiers)

/* unsigned T (unsigned T, indexv128).  */
static enum csky_type_qualifiers
csky_binuopv128_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned, qualifier_indexv128 };
#define BINUOPV128_QUALIFIERS (csky_binuopv128_qualifiers)

/* T (indexv128, T).  */
static enum csky_type_qualifiers
csky_binoptv128_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_indexv128, qualifier_none };
#define BINOPTV128_QUALIFIERS (csky_binoptv128_qualifiers)

/* unsigned T (indexv128, unsigned T).  */
static enum csky_type_qualifiers
csky_binuoptv128_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_indexv128, qualifier_unsigned };
#define BINUOPTV128_QUALIFIERS (csky_binuoptv128_qualifiers)

/* T (T, indexv64).  */
static enum csky_type_qualifiers
csky_binopv64_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_indexv64 };
#define BINOPV64_QUALIFIERS (csky_binopv64_qualifiers)

/* unsigned T (unsigned T, indexv64).  */
static enum csky_type_qualifiers
csky_binuopv64_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned, qualifier_indexv64 };
#define BINUOPV64_QUALIFIERS (csky_binuopv64_qualifiers)

/* T (indexv64, T).  */
static enum csky_type_qualifiers
csky_binoptv64_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_indexv64, qualifier_none };
#define BINOPTV64_QUALIFIERS (csky_binoptv64_qualifiers)

/* unsigned T (indexv64, unsigned T).  */
static enum csky_type_qualifiers
csky_binuoptv64_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_indexv64, qualifier_unsigned };
#define BINUOPTV64_QUALIFIERS (csky_binuoptv64_qualifiers)

/* T (T, offset2k).  */
static enum csky_type_qualifiers
csky_binopo2k_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_offset2k };
#define BINOPO2K_QUALIFIERS (csky_binopo2k_qualifiers)

/* T (T, offset4k).  */
static enum csky_type_qualifiers
csky_binopo4k_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_offset4k };
#define BINOPO4K_QUALIFIERS (csky_binopo4k_qualifiers)

/* T (T, T, index0-3).  */
static enum csky_type_qualifiers
csky_ternopi3_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_none, qualifier_index03 };
#define TERNOPI3_QUALIFIERS (csky_ternopi3_qualifiers)

/* T (indexv128, T, indexv128).  */
static enum csky_type_qualifiers
csky_ternopv128_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_indexv128, qualifier_none, qualifier_indexv128 };
#define TERNOPV128_QUALIFIERS (csky_ternopv128_qualifiers)

/* T (indexv64, T, indexv64).  */
static enum csky_type_qualifiers
csky_ternopv64_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_indexv64, qualifier_none, qualifier_indexv64 };
#define TERNOPV64_QUALIFIERS (csky_ternopv64_qualifiers)

/* T (T, T, int).  */
static enum csky_type_qualifiers
csky_bshift_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_maybe_immediate };
#define BSHIFT_QUALIFIERS (csky_bshift_qualifiers)

#define ENTRY(E, M, Q, S, T, G) E,
enum csky_simd_type
{
#include "csky-simd-builtin-types.def"
  __TYPE_FINAL
};
#undef ENTRY

struct csky_simd_type_info
{
  enum csky_simd_type type;

  /* Internal type name.  */
  const char *name;

  /* Internal type name(mangled).To qualify for emission with the mangled names
     defined in that document, a vector type must not only be of the correct mode
     but also be of the correct internal vector type (e.g. __simd64_int8_t);
     these types are registered by arm_init_simd_builtin_types ().  In other
     words, vector types defined in other ways e.g. via vector_size attribute
     will get default mangled names.  */
  const char *mangle;

  /* Internal type.  */
  tree itype;

  /* Element type.  */
  tree eltype;

  /* Machine mode the internal type maps to.  */
  machine_mode mode;

  /* Qualifiers.  */
  enum csky_type_qualifiers q;
};

#define ENTRY(E, M, Q, S, T, G)         \
  {E,                                   \
   "__simd" #S "_" #T "_t",             \
   #G "__simd" #S "_" #T "_t",          \
   NULL_TREE, NULL_TREE, M##mode, qualifier_##Q},
static struct csky_simd_type_info csky_simd_types [] = {
#include "csky-simd-builtin-types.def"
};
#undef ENTRY

#define v2si_UP   V2SImode
#define v2hi_UP   V2HImode
#define v4qi_UP   V4QImode
#define si_UP     SImode
#define sq_UP     SQmode
#define v2sq_UP   V2SQmode
#define v2hq_UP   V2HQmode
#define v4qq_UP   V4QQmode
#define v2usq_UP  V2USQmode
#define v2uhq_UP  V2UHQmode
#define v4uqq_UP  V4UQQmode

#define v4si_UP    V4SImode
#define v8hi_UP    V8HImode
#define v16qi_UP   V16QImode
#define v4sq_UP    V4SQmode
#define v8hq_UP    V8HQmode
#define v16qq_UP   V16QQmode
#define v4usq_UP   V4USQmode
#define v8uhq_UP   V8UHQmode
#define v16uqq_UP  V16UQQmode

#define v2si_UP    V2SImode
#define v4hi_UP    V4HImode
#define v8qi_UP    V8QImode
#define v2sq_UP    V2SQmode
#define v4hq_UP    V4HQmode
#define v8qq_UP    V8QQmode
#define v2usq_UP   V2USQmode
#define v4uhq_UP   V4UHQmode
#define v8uqq_UP   V8UQQmode

#define UP(X) X##_UP

typedef struct {
  /* Decide if the current CPU contains this builtin function.  */
  enum csky_isa_feature isa_flag;
  const char *name;
  machine_mode mode;
  const enum insn_code code;
  unsigned int fcode;
  enum csky_type_qualifiers *qualifiers;
} csky_builtin_datum;

#define CF(N,X) CODE_FOR_csky_##N##X

#define VAR1(I, T, N, A) \
  {CSKY_ISA_FEATURE_GET(I), #N #A, UP (A), CF (N, A), 0, T##_QUALIFIERS},

#define VAR2(I, T, N, A, B) \
  VAR1 (I, T, N, A) \
  VAR1 (I, T, N, B)
#define VAR3(I, T, N, A, B, C) \
  VAR2 (I, T, N, A, B) \
  VAR1 (I, T, N, C)
#define VAR4(I, T, N, A, B, C, D) \
  VAR3 (I, T, N, A, B, C) \
  VAR1 (I, T, N, D)
#define VAR5(I, T, N, A, B, C, D, E) \
  VAR4 (I, T, N, A, B, C, D) \
  VAR1 (I, T, N, E)
#define VAR6(I, T, N, A, B, C, D, E, F) \
  VAR5 (I, T, N, A, B, C, D, E) \
  VAR1 (I, T, N, F)
#define VAR7(I, T, N, A, B, C, D, E, F, G) \
  VAR6 (I, T, N, A, B, C, D, E, F) \
  VAR1 (I, T, N, G)
#define VAR8(I, T, N, A, B, C, D, E, F, G, H) \
  VAR7 (I, T, N, A, B, C, D, E, F, G) \
  VAR1 (I, T, N, H)
#define VAR9(I, T, N, A, B, C, D, E, F, G, H, J) \
  VAR8 (I, T, N, A, B, C, D, E, F, G, H) \
  VAR1 (I, T, N, J)

/* The csky builtin data can be found in csky_builtins.def.
   The mode entries in the following table correspond to the "key" type of the
   instruction variant, i.e. equivalent to that which would be specified after
   the assembler mnemonic, which usually refers to the last vector operand.
   The modes listed per instruction should be the same as those defined for
   that instruction's pattern in csky_builtins.md.  */

static csky_builtin_datum csky_builtin_data[] =
{
#include "csky_builtins.def"
};

#undef CF
#undef VAR1

#define VAR1(I, T, N, X) \
  CSKY_BUILTIN_##N##X,

enum csky_builtins
{
  #include "csky_builtins.def"
  CSKY_BUILTIN_MAX
};

#define CSKY_BUILTIN_PATTERN_START \
  (CSKY_BUILTIN_MAX - ARRAY_SIZE (csky_builtin_data))

#undef CF
#undef VAR1
#undef VAR2
#undef VAR3
#undef VAR4
#undef VAR5
#undef VAR6
#undef VAR7
#undef VAR8
#undef VAR9

static GTY(()) tree csky_builtin_decls[CSKY_BUILTIN_MAX];

void
csky_init_simd_builtin_types (void)
{
  int i;
  int nelts = sizeof (csky_simd_types) / sizeof (csky_simd_types[0]);
  tree tdecl;

  csky_simd_types[Int8x4_t].eltype = intQI_type_node;
  csky_simd_types[Int8x8_t].eltype = intQI_type_node;
  csky_simd_types[Int8x16_t].eltype = intQI_type_node;
  csky_simd_types[Int16x2_t].eltype = intHI_type_node;
  csky_simd_types[Int16x4_t].eltype = intHI_type_node;
  csky_simd_types[Int16x8_t].eltype = intHI_type_node;
  csky_simd_types[Int32x2_t].eltype = intSI_type_node;
  csky_simd_types[Int32x4_t].eltype = intSI_type_node;

  csky_simd_types[UInt8x4_t].eltype =unsigned_intQI_type_node;
  csky_simd_types[UInt8x8_t].eltype =unsigned_intQI_type_node;
  csky_simd_types[UInt8x16_t].eltype =unsigned_intQI_type_node;
  csky_simd_types[UInt16x2_t].eltype =unsigned_intHI_type_node;
  csky_simd_types[UInt16x4_t].eltype =unsigned_intHI_type_node;
  csky_simd_types[UInt16x8_t].eltype =unsigned_intHI_type_node;
  csky_simd_types[UInt32x2_t].eltype =unsigned_intSI_type_node;
  csky_simd_types[UInt32x4_t].eltype =unsigned_intSI_type_node;

  csky_simd_types[Sat16x2_t].eltype = sat_fract_type_node;
  csky_simd_types[USat16x2_t].eltype = sat_unsigned_fract_type_node;
  csky_simd_types[Sat8x4_t].eltype = sat_short_fract_type_node;
  csky_simd_types[USat8x4_t].eltype = sat_unsigned_short_fract_type_node;

  csky_simd_types[Sat16x8_t].eltype = sat_fract_type_node;
  csky_simd_types[USat16x8_t].eltype = sat_unsigned_fract_type_node;
  csky_simd_types[Sat8x16_t].eltype = sat_short_fract_type_node;
  csky_simd_types[USat8x16_t].eltype = sat_unsigned_short_fract_type_node;
  csky_simd_types[Sat32x4_t].eltype = sat_long_fract_type_node;
  csky_simd_types[USat32x4_t].eltype = sat_unsigned_long_fract_type_node;

  csky_simd_types[Sat16x4_t].eltype = sat_fract_type_node;
  csky_simd_types[USat16x4_t].eltype = sat_unsigned_fract_type_node;
  csky_simd_types[Sat8x8_t].eltype = sat_short_fract_type_node;
  csky_simd_types[USat8x8_t].eltype = sat_unsigned_short_fract_type_node;
  csky_simd_types[Sat32x2_t].eltype = sat_long_fract_type_node;
  csky_simd_types[USat32x2_t].eltype = sat_unsigned_long_fract_type_node;

  for(i = 0; i < nelts; i++)
    {
      tree eltype = csky_simd_types[i].eltype;
      enum machine_mode mode = csky_simd_types[i].mode;

      if(csky_simd_types[i].itype == NULL)
          csky_simd_types[i].itype =
            build_distinct_type_copy
              (build_vector_type (eltype, GET_MODE_NUNITS (mode)));

      tdecl = add_builtin_type (csky_simd_types[i].name,
                                csky_simd_types[i].itype);
      TYPE_NAME (csky_simd_types[i].itype) = tdecl;
      SET_TYPE_STRUCTURAL_EQUALITY (csky_simd_types[i].itype);
    }
}

static tree
csky_simd_builtin_std_type (enum machine_mode mode)
{
  switch (mode)
    {
      case SImode:
        return intSI_type_node;
      case DImode:
        return intDI_type_node;
      case HImode:
        return intHI_type_node;
      case QImode:
        return intQI_type_node;
      case SQmode:
        return sat_long_fract_type_node;
      default:
        gcc_unreachable ();
    }
}

static tree
csky_lookup_simd_builtin_type (enum machine_mode mode,
                               enum csky_type_qualifiers q)
{
  unsigned int i;
  unsigned int nelts = sizeof (csky_simd_types) / sizeof (csky_simd_types [0]);

  if (!VECTOR_MODE_P (mode))
    return csky_simd_builtin_std_type (mode);
  for (i = 0; i < nelts; i++)
    if (csky_simd_types[i].mode == mode
        && csky_simd_types[i].q == q)
      return csky_simd_types[i].itype;

  return NULL_TREE;
}

static tree
csky_simd_builtin_type (enum machine_mode mode,
                        bool unsigned_p)
{
  if (unsigned_p)
    return csky_lookup_simd_builtin_type (mode, qualifier_unsigned);
  else
    return csky_lookup_simd_builtin_type (mode, qualifier_none);
}

void
csky_init_builtins (void)
{
  unsigned int i, fcode = CSKY_BUILTIN_PATTERN_START;

  csky_init_simd_builtin_types ();

  for (i = 0; i < ARRAY_SIZE (csky_builtin_data); i++, fcode++)
    {
      csky_builtin_datum *d = &csky_builtin_data[i];
      tree ftype = NULL;
      char namebuf[60];
      tree fndecl = NULL;

      if (!csky_arch_isa_features[d->isa_flag])
        continue;

      d->fcode = fcode;

      int op_num = insn_data[d->code].n_operands - 1;
      int arg_num = d->qualifiers[0] & qualifier_void
        ? op_num + 1
        : op_num;
      tree return_type = void_type_node, args = void_list_node;
      tree eltype;

      for (; op_num >= 0; arg_num--, op_num--)
        {
          machine_mode op_mode = insn_data[d->code].operand[op_num].mode;
          enum csky_type_qualifiers qualifiers = d->qualifiers[arg_num];

          eltype = csky_simd_builtin_type (
            op_mode, (qualifiers & qualifier_unsigned) != 0);
          gcc_assert (eltype != NULL);

          if (arg_num == 0)
            return_type = eltype;
          else
            args = tree_cons (NULL_TREE, eltype, args);
        }

        ftype = build_function_type (return_type, args);
        gcc_assert (ftype != NULL);

        snprintf (namebuf, sizeof (namebuf), "__builtin_csky_%s",
                  d->name);

        fndecl = add_builtin_function (namebuf, ftype, fcode, BUILT_IN_MD,
                                       NULL, NULL_TREE);
        csky_builtin_decls[fcode] = fndecl;
    }
}

static rtx
csky_expand_args (rtx target, machine_mode map_mode, int fcode,
                  int icode, int have_retval, tree exp,
                  builtin_arg *args)
{
  machine_mode tmode = insn_data[icode].operand[0].mode;
  int argc = 0;
  rtx pat;
  rtx op[SIMD_MAX_BUILTIN_ARGS];
  tree arg[SIMD_MAX_BUILTIN_ARGS];
  machine_mode mode[SIMD_MAX_BUILTIN_ARGS];

  if (have_retval
      && (!target
          || GET_MODE (target) == tmode
          || !(*insn_data[icode].operand[0].predicate) (target, tmode)))
    target = gen_reg_rtx (tmode);

  for (;;)
    {
      builtin_arg thisarg = args[argc];

      if (thisarg == CSKY_ARG_STOP)
        break;
      else
        {
          int opno = argc + have_retval;
          arg[argc] = CALL_EXPR_ARG (exp, argc);
          mode[argc] = insn_data[icode].operand[opno].mode;

          op[argc] = expand_expr (arg[argc], NULL_RTX, VOIDmode,
                                  (thisarg == CSKY_ARG_MEMORY
                                   ? EXPAND_MEMORY : EXPAND_NORMAL));

          switch (thisarg)
            {
              case CSKY_ARG_COPY_TO_REG:
                if (POINTER_TYPE_P (TREE_TYPE (arg[argc])))
                  op[argc] = convert_memory_address (Pmode, op[argc]);
/* FIXME: when does this code needed?
          If it is enabled, HI mode arg when be assert and should
          be fixed.  */
#if 1
                if (!(*insn_data[icode].operand[opno].predicate) (op[argc],
                                                                  mode[argc]))
                  op[argc] = copy_to_mode_reg (mode[argc], op[argc]);
#endif
                break;
              case CSKY_ARG_IMM_UT:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 0 || imm > 15)
                      error ("%Kargument %d must be in 0 to 15", exp, argc+1);
                  }
                goto constant_arg;
              case CSKY_ARG_IMM_U31:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 0 || imm > 31)
                      error ("%Kargument %d must be in 0 to 31", exp, argc+1);
                  }
                goto constant_arg;
              case CSKY_ARG_INDEX03:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 0 || imm > 3)
                      error ("%Kargument %d must be in 0 to 3", exp, argc+1);
                  }
                goto constant_arg;
              case CSKY_ARG_INDEX01:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 0 || imm > 1)
                      error ("%Kargument %d must be in 0 to 1", exp, argc+1);
                  }
                goto constant_arg;
              case CSKY_ARG_INDEXV128:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    tree vec_type;
                    if (argc == 0)
                      vec_type = csky_simd_builtin_type(tmode, false);
                    else
                      vec_type = csky_simd_builtin_type(mode[argc-1], false);
                    int limit = TYPE_VECTOR_SUBPARTS(vec_type) - 1;
                    gcc_assert (limit == 15 || limit == 7 || limit == 3);
                    if (imm < 0 || imm > limit)
                      error ("%Kargument %d must be in 0 to %d",
                             exp, argc+1, limit);
                  }
                goto constant_arg;
              case CSKY_ARG_INDEXV64:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    tree vec_type;
                    if (argc == 0)
                      vec_type = csky_simd_builtin_type(tmode, false);
                    else
                      vec_type = csky_simd_builtin_type(mode[argc-1], false);
                    int limit = TYPE_VECTOR_SUBPARTS(vec_type) - 1;
                    gcc_assert (limit == 7 || limit == 3 || limit == 1);
                    if (imm < 0 || imm > limit)
                      error ("%Kargument %d must be in 0 to %d",
                             exp, argc+1, limit);
                  }
                goto constant_arg;
              case CSKY_ARG_OFFSET2K:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 0 || imm > 2040 || imm % 8)
                      error ("%Kargument %d must be in 0 to 2040, and 8 aligned",
                             exp, argc+1);
                  }
                goto constant_arg;
              case CSKY_ARG_OFFSET4K:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 0 || imm > 4080 || imm % 16)
                      error ("%Kargument %d must be in 0 to 4080, and 16 aligned",
                             exp, argc+1);
                  }
                goto constant_arg;
              case CSKY_ARG_CONSTANT:
constant_arg:
                if (!(*insn_data[icode].operand[opno].predicate)
                       (op[argc], mode[argc]))
                  {
                    error ("%Kargument %d must be a constant immediate",
                           exp, argc + 1);
                    return const0_rtx;
                  }
                break;
              case CSKY_ARG_STOP:
              default:
                gcc_unreachable ();
            }
        }
      argc++;
    }

  if (have_retval)
    switch (argc)
      {
        case 1:
          pat = GEN_FCN (icode) (target, op[0]);
          break;
        case 2:
          pat = GEN_FCN (icode) (target, op[0], op[1]);
          break;
        case 3:
          pat = GEN_FCN (icode) (target, op[0], op[1], op[2]);
          break;
        case 4:
          pat = GEN_FCN (icode) (target, op[0], op[1], op[2], op[3]);
          break;
        default:
          gcc_unreachable ();
      }
  else
    switch (argc)
      {
        case 1:
          pat = GEN_FCN (icode) (op[0]);
          break;
        case 2:
          pat = GEN_FCN (icode) (op[0], op[1]);
          break;
        case 3:
          pat = GEN_FCN (icode) (op[0], op[1], op[2]);
          break;
        case 4:
          pat = GEN_FCN (icode) (op[0], op[1], op[2], op[3]);
          break;
        default:
          gcc_unreachable ();
      }

  if (!pat)
    return 0;

  emit_insn (pat);

  return target;
}

rtx
csky_expand_builtin (tree exp,
                     rtx target,
                     rtx subtarget ATTRIBUTE_UNUSED,
                     machine_mode mode ATTRIBUTE_UNUSED,
                     int ignore ATTRIBUTE_UNUSED)
{
  tree fndecl = TREE_OPERAND (CALL_EXPR_FN (exp), 0);
  unsigned int fcode = DECL_FUNCTION_CODE (fndecl);
  csky_builtin_datum *d = &csky_builtin_data[fcode];
  enum insn_code icode = d->code;
  builtin_arg args[SIMD_MAX_BUILTIN_ARGS + 1];
  int num_args = insn_data[d->code].n_operands;
  int k;
  int is_void = 0;

  is_void = !!(d->qualifiers[0] & qualifier_void);

  num_args += is_void;

  for (k = 1; k < num_args; k++)
    {
      int operands_k = k - is_void;
      int expr_args_k = k - 1;

      if (d->qualifiers[k] & qualifier_maybe_immediate)
        {
          rtx arg = expand_normal (CALL_EXPR_ARG (exp,
                                   (expr_args_k)));
          /* Handle constants only if the predicate allows it.  */
          bool op_const_int_p =
            (CONST_INT_P (arg)
             && (*insn_data[icode].operand[operands_k].predicate)
                   (arg, insn_data[icode].operand[operands_k].mode));
          args[k] = op_const_int_p ? CSKY_ARG_CONSTANT : CSKY_ARG_COPY_TO_REG;
        }
      else if (d->qualifiers[k] & qualifier_immUt)
        {
          args[k] = CSKY_ARG_IMM_UT;
        }
      else if (d->qualifiers[k] & qualifier_index03)
        {
          args[k] = CSKY_ARG_INDEX03;
        }
      else if (d->qualifiers[k] & qualifier_index01)
        {
          args[k] = CSKY_ARG_INDEX01;
        }
      else if (d->qualifiers[k] & qualifier_indexv128)
        {
          args[k] = CSKY_ARG_INDEXV128;
        }
      else if (d->qualifiers[k] & qualifier_indexv64)
        {
          args[k] = CSKY_ARG_INDEXV64;
        }
      else if (d->qualifiers[k] & qualifier_offset2k)
        {
          args[k] = CSKY_ARG_OFFSET2K;
        }
      else if (d->qualifiers[k] & qualifier_offset4k)
        {
          args[k] = CSKY_ARG_OFFSET4K;
        }
      else if (d->qualifiers[k] & qualifier_immU31)
        {
          args[k] = CSKY_ARG_IMM_U31;
        }
      else
        args[k] = CSKY_ARG_COPY_TO_REG;
    }
  args[k] = CSKY_ARG_STOP;

  return csky_expand_args
    (target, d->mode, fcode, icode, !is_void, exp, &args[1]);
}

tree
csky_builtin_decl (unsigned code, bool initialize_p ATTRIBUTE_UNUSED)
{
  if (code >= CSKY_BUILTIN_MAX)
    return error_mark_node;

  return csky_builtin_decls[code];
}

#include "gt-csky-builtins.h"
