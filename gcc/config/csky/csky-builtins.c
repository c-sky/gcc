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
  CSKY_ARG_VOID,
  CSKY_ARG_COPY_TO_REG,
  CSKY_ARG_CONSTANT,
  CSKY_ARG_LANE_INDEX,
  CSKY_ARG_STRUCT_LOAD_STORE_LANE_INDEX,
  CSKY_ARG_MEMORY,
  CSKY_ARG_IMM_UT,
  CSKY_ARG_IMM_IMMUW,
  CSKY_ARG_IMM_IMMUHW,
  CSKY_ARG_IMM_IMMUU,
  CSKY_ARG_IMM_IMMJ,
  CSKY_ARG_IMM_ELEMENTSIZE0,
  CSKY_ARG_IMM_ELEMENTSIZE1,
  CSKY_ARG_IMM_ELEMENTSIZE2,
  CSKY_ARG_INDEX03,
  CSKY_ARG_INDEX01,
  CSKY_ARG_INDEXV128,
  CSKY_ARG_INDEXV128_B8,
  CSKY_ARG_INDEXV128_M1,
  CSKY_ARG_OFFSET2K,
  CSKY_ARG_OFFSET4K,
  CSKY_ARG_IMM_U31,
  CSKY_ARG_IMM_U63_D15,
  CSKY_ARG_INDEXV64,
  CSKY_ARG_FIXEDDV,
  CSKY_ARG_GEN_REG,
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
  qualifier_indexv64 = 0x800, /* 1<<11 */
  /* imm 1-16 */
  qualifier_immUu = 0x1000, /* 1<<12 */
  /* imm 1-32 */
  qualifier_immJ = 0x2000,/* 1<<13 */
  /* imm 0 ~ (element_size-1)  */
  qualifier_elementsize0 = 0x4000,/* 1<<14 */
  /* imm 1 ~ (element_size)*/
  qualifier_elementsize1 = 0x8000, /* 1<<15 */
  /* imm 0 ~ (2*element_size -1) */
  qualifier_elementsize2 = 0x10000, /*1<<16*/
  /* 8-bits of index each element for vector 128, |0-3|0-1 */
  qualifier_indexv128_b8 = 0x20000,/*1<<17*/
  /* imm8 (-128~127) */
  qualifier_immUw = 0x40000, /*1<<18*/
  /* imm8 (fixed-point(binary point 0-15)) */
  qualifier_fixedDv = 0x80000, /*1<<19*/
  /* imm7 (0~127)<<size size = 00(v16qi)/01(v8hi)/10(v4si)  */
  qualifier_immUhw = 0x100000, /*1<<20*/
  /* imm 0 ~ (128/element_size-2) */
  qualifier_indexv128_m1 = 0x200000, /* 1<<21 */
  /* imm 0-31 but the last four bit isn't 1 entirely */
  qualifier_immU63_d15 = 0x400000 /* 1<<22 */
};

/* unsigned T (void T).  */
static enum csky_type_qualifiers
csky_zerouop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_void };
#define ZEROUOP_QUALIFIERS (csky_zerouop_qualifiers)

/* T (T).  */
static enum csky_type_qualifiers
csky_unop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none };
#define UNOP_QUALIFIERS (csky_unop_qualifiers)

/* void T (unsigned T).  */
static enum csky_type_qualifiers
csky_unuop_vu_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_void, qualifier_unsigned };
#define UNUOP_VU_QUALIFIERS (csky_unuop_vu_qualifiers)

/* unsigned T (unsigned T).  */
static enum csky_type_qualifiers
csky_unuop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned };
#define UNUOP_QUALIFIERS (csky_unuop_qualifiers)

/* T (imm8).  */
static enum csky_type_qualifiers
csky_unop_simm8_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_immUw };
#define UNOP_SIMM8_QUALIFIERS (csky_unop_simm8_qualifiers)

/* T (imm8 fixed-point (binary point 0-15)). */
static enum csky_type_qualifiers
csky_unop_simmfixp_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_fixedDv };
#define UNOP_SIMMFIXP_QUALIFIERS (csky_unop_simmfixp_qualifiers)

/* unsigned T (imm8).  */
static enum csky_type_qualifiers
csky_unop_uimm8_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_immUw };
#define UNOP_UIMM8_QUALIFIERS (csky_unop_uimm8_qualifiers)

/* T (unsigned T).  */
static enum csky_type_qualifiers
csky_unop_su_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_unsigned };
#define UNOP_SU_QUALIFIERS (csky_unop_su_qualifiers)

/* unsigned T (T).  */
static enum csky_type_qualifiers
csky_unop_us_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_none };
#define UNOP_US_QUALIFIERS (csky_unop_us_qualifiers)

/* T (T, T).  */
static enum csky_type_qualifiers
csky_binop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_none };
#define BINOP_QUALIFIERS (csky_binop_qualifiers)

/* unsigned T (T, T).  */
static enum csky_type_qualifiers
csky_binop_uss_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_none, qualifier_none };
#define BINOP_USS_QUALIFIERS (csky_binop_uss_qualifiers)

/* unsigned T (unsigned T, T).  */
static enum csky_type_qualifiers
csky_binop_uus_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned, qualifier_none };
#define BINOP_UUS_QUALIFIERS (csky_binop_uus_qualifiers)

/* T (T, unsigned T).  */
static enum csky_type_qualifiers
csky_binop_ssu_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_unsigned };
#define BINOP_SSU_QUALIFIERS (csky_binop_ssu_qualifiers)

/* void T(T, T).  */
static enum csky_type_qualifiers
csky_binopvoid_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_void, qualifier_none, qualifier_none };
#define BINOPVOID_QUALIFIERS (csky_binopvoid_qualifiers)

/* T (imm8, indexv128_b8).  */
static enum csky_type_qualifiers
csky_binop_simm8v128b8_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_immUw, qualifier_indexv128_b8 };
#define BINOP_SIMM8V128B8_QUALIFIERS (csky_binop_simm8v128b8_qualifiers)

/* unsigned T (imm8, indexv128_b8).  */
static enum csky_type_qualifiers
csky_binop_uimm8v128b8_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_immUw, qualifier_indexv128_b8 };
#define BINOP_UIMM8V128B8_QUALIFIERS (csky_binop_uimm8v128b8_qualifiers)

/* T (T, imm 1-16).  */
static enum csky_type_qualifiers
csky_binop_ssi1_16_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_immUu };
#define BINOP_SSI1_16_QUALIFIERS (csky_binop_ssi1_16_qualifiers)

/* T (T, imm 1-32).  */
static enum csky_type_qualifiers
csky_binop_ssi1_32_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_immJ };
#define BINOP_SSI1_32_QUALIFIERS (csky_binop_ssi1_32_qualifiers)

/* unsigned T (unsigned T, unsigned T).  */
static enum csky_type_qualifiers
csky_binuop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned };
#define BINUOP_QUALIFIERS (csky_binuop_qualifiers)

/* unsigned T (unsigned T, imm 1-16).  */
static enum csky_type_qualifiers
csky_binop_uui1_16_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_unsigned, qualifier_immUu };
#define BINOP_UUI1_16_QUALIFIERS (csky_binop_uui1_16_qualifiers)

/* T (T, T, T).  */
static enum csky_type_qualifiers
csky_ternop_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_none, qualifier_none };
#define TERNOP_QUALIFIERS (csky_ternop_qualifiers)

/* T (T, T, unsigned T).  */
static enum csky_type_qualifiers
csky_ternop_sssu_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_none, qualifier_unsigned };
#define TERNOP_SSSU_QUALIFIERS (csky_ternop_sssu_qualifiers)

/* void (T, T, T).  */
static enum csky_type_qualifiers
csky_ternopvoid_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_void, qualifier_none, qualifier_none, qualifier_none };
#define TERNOPVOID_QUALIFIERS (csky_ternopvoid_qualifiers)

/* void T (unsigned T, imm1-32, imm0-31).  */
static enum csky_type_qualifiers
csky_ternop_vui0_31i0_31_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_void, qualifier_unsigned, qualifier_immJ, qualifier_immU31 };
#define TERNOP_VUI0_31I0_31_QUALIFIERS (csky_ternop_vui0_31i0_31_qualifiers)

/* unsigned T (T, imm 1-16).  */
static enum csky_type_qualifiers
csky_binop_usi1_16_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_none, qualifier_immUu };
#define BINOP_USI1_16_QUALIFIERS (csky_binop_usi1_16_qualifiers)

/* unsigned T (T, imm 0-127).  */
static enum csky_type_qualifiers
csky_binop_imm7_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_immUhw };
#define BINOP_IMM7_QUALIFIERS (csky_binop_imm7_qualifiers)

/* void T (T, T, imm 0-127).  */
static enum csky_type_qualifiers
csky_ternop_imm7_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_void, qualifier_none, qualifier_none, qualifier_immUhw };
#define TERNOP_IMM7_QUALIFIERS (csky_ternop_imm7_qualifiers)

/* unsigned T (unsigned T, imm 1-16).  */
static enum csky_type_qualifiers
csky_binop_uu1_16_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_immUu };
#define BINOP_UUI1_16_QUALIFIERS (csky_binop_uu1_16_qualifiers)

/* unsigned T (unsigned T, imm 0-(2*element_size-1)).  */
static enum csky_type_qualifiers
csky_binuop_immes2_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_elementsize2};
#define BINUOP_IMMES2_QUALIFIERS (csky_binuop_immes2_qualifiers)

/*  T ( T, imm 0- (2*element_size-1)).  */
static enum csky_type_qualifiers
csky_binop_immes2_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_elementsize2};
#define BINOP_IMMES2_QUALIFIERS (csky_binop_immes2_qualifiers)

/* unsigned T (unsigned T, imm 1-(element_size)).  */
static enum csky_type_qualifiers
csky_binuop_immes1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_elementsize1};
#define BINUOP_IMMES1_QUALIFIERS (csky_binuop_immes1_qualifiers)

/*  T ( T, imm 1- (element_size)).  */
static enum csky_type_qualifiers
csky_binop_immes1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_elementsize1};
#define BINOP_IMMES1_QUALIFIERS (csky_binop_immes1_qualifiers)

/* unsigned T (unsigned T, unsigned T, imm 1-(element_size)).  */
static enum csky_type_qualifiers
csky_ternuop_immes1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned, qualifier_elementsize1};
#define TERNUOP_IMMES1_QUALIFIERS (csky_ternuop_immes1_qualifiers)

/*  T ( T, T, imm 1- (element_size)).  */
static enum csky_type_qualifiers
csky_ternop_immes1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_none, qualifier_elementsize1};
#define TERNOP_IMMES1_QUALIFIERS (csky_ternop_immes1_qualifiers)

/* unsigned T (unsigned T, imm 0~(element_size-1)).  */
static enum csky_type_qualifiers
csky_binuop_immes0_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_elementsize0};
#define BINUOP_IMMES0_QUALIFIERS (csky_binuop_immes0_qualifiers)

/*  T ( T, imm 0 ~ (element_size-1)).  */
static enum csky_type_qualifiers
csky_binop_immes0_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_elementsize0};
#define BINOP_IMMES0_QUALIFIERS (csky_binop_immes0_qualifiers)

/* T (unsigned T, imm 1-16).  */
static enum csky_type_qualifiers
csky_binop_sui1_16_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_unsigned, qualifier_immUu };
#define BINOP_SUI1_16_QUALIFIERS (csky_binop_sui1_16_qualifiers)

/* unsigned T (T, imm 1-32).  */
static enum csky_type_qualifiers
csky_binop_usi1_32_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_unsigned, qualifier_none, qualifier_immJ };
#define BINOP_USI1_32_QUALIFIERS (csky_binop_usi1_32_qualifiers)

/* T (unsigned T, imm 1-32).  */
static enum csky_type_qualifiers
csky_binop_sui1_32_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_unsigned, qualifier_immJ };
#define BINOP_SUI1_32_QUALIFIERS (csky_binop_sui1_32_qualifiers)

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

/* T (T, T, indexv128).  */
static enum csky_type_qualifiers
csky_ternop_sssiv128_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_none, qualifier_indexv128 };
#define TERNOP_SSSIV128_QUALIFIERS (csky_ternop_sssiv128_qualifiers)

/* T (T, T, immU63d15).  */
static enum csky_type_qualifiers
csky_ternop_immu63d15_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_none, qualifier_immU63_d15 };
#define TERNOP_IMMU63D15_QUALIFIERS (csky_ternop_immu63d15_qualifiers)

/* unsined T (unsigned T, unsigned T, immU63d15).  */
static enum csky_type_qualifiers
csky_ternuop_immu63d15_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned, qualifier_immU63_d15 };
#define TERNUOP_IMMU63D15_QUALIFIERS (csky_ternuop_immu63d15_qualifiers)

/* T (T, T, T, indexv128).  */
static enum csky_type_qualifiers
csky_quanop_ssssiv128_qualifiers[SIMD_MAX_BUILTIN_ARGS]
  = { qualifier_none, qualifier_none, qualifier_none, qualifier_none, qualifier_indexv128 };
#define QUANOP_SSSSIV128_QUALIFIERS (csky_quanop_ssssiv128_qualifiers)

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

/* T (T, T, imm 1-16).  */
static enum csky_type_qualifiers
csky_ternop_imm1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_none, qualifier_immUt };
#define TERNOP_IMM1_QUALIFIERS (csky_ternop_imm1_qualifiers)


/* T (T, T, indexv128).  */
static enum csky_type_qualifiers
csky_ternop_index1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_none, qualifier_indexv128 };
#define TERNOP_INDEX1_QUALIFIERS (csky_ternop_index1_qualifiers)

/* T (T, T, indexv128m1).  */
static enum csky_type_qualifiers
csky_ternop_indexm1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_none, qualifier_indexv128_m1 };
#define TERNOP_INDEXM1_QUALIFIERS (csky_ternop_indexm1_qualifiers)

/* T (T, imm 1-16, imm 1-16).  */
static enum csky_type_qualifiers
csky_ternop_imm2_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_indexv128, qualifier_immUt};
#define TERNOP_IMM2_QUALIFIERS (csky_ternop_imm2_qualifiers)

/* unsigned T (unsigned T, unsigned T, imm 1-16).  */
static enum csky_type_qualifiers
csky_ternuop_imm1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned, qualifier_immUt };
#define TERNUOP_IMM1_QUALIFIERS (csky_ternuop_imm1_qualifiers)

/* unsigned T (unsigned T, unsigned T, indexv128).  */
static enum csky_type_qualifiers
csky_ternuop_index1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned, qualifier_indexv128 };
#define TERNUOP_INDEX1_QUALIFIERS (csky_ternuop_index1_qualifiers)

/* unsigned T (unsigned T, unsigned T, indexv128m1).  */
static enum csky_type_qualifiers
csky_ternuop_indexm1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned, qualifier_indexv128_m1 };
#define TERNUOP_INDEXM1_QUALIFIERS (csky_ternuop_indexm1_qualifiers)

/* T (T, T, T, index).  */
static enum csky_type_qualifiers
csky_fourop_index1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_none, qualifier_indexv128, qualifier_none};
#define FOUROP_INDEX1_QUALIFIERS (csky_fourop_index1_qualifiers)

/* T (T,index1, T,index2).  */
static enum csky_type_qualifiers
csky_fourop_index2_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_indexv128, qualifier_none, qualifier_indexv128};
#define FOUROP_INDEX2_QUALIFIERS (csky_fourop_index2_qualifiers)

/* T (T, T, T, imm 1-16).  */
static enum csky_type_qualifiers
csky_fourop_imm1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_none, qualifier_immUt, qualifier_none};
#define FOUROP_IMM1_QUALIFIERS (csky_fourop_imm1_qualifiers)

/* T (T, T, T, index).  */
static enum csky_type_qualifiers
csky_fourop_imm2_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_none, qualifier_none, qualifier_none, qualifier_indexv128, qualifier_immUt};
#define FOUROP_IMM2_QUALIFIERS (csky_fourop_imm2_qualifiers)

/* unsigned T (unsigned T, unsigned T, unsigned T, index).  */
static enum csky_type_qualifiers
csky_fouruop_index1_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned, qualifier_unsigned, qualifier_indexv128, qualifier_unsigned};
#define FOURUOP_INDEX1_QUALIFIERS (csky_fouruop_index1_qualifiers)

/* unsigned T (unsigned T, index1, unsigned T, index2).  */
static enum csky_type_qualifiers
csky_fouruop_index2_qualifiers[SIMD_MAX_BUILTIN_ARGS]
        = { qualifier_unsigned, qualifier_unsigned,  qualifier_indexv128, qualifier_unsigned, qualifier_indexv128};
#define FOURUOP_INDEX2_QUALIFIERS (csky_fouruop_index2_qualifiers)


#define ISA_MAX_BUILTIN_VERSIONS 3 /* 2 + 1(none) */

enum csky_isa_feature
cEcr1_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(3E3r1),CSKY_ISA_FEATURE_GET(none)};
#define CECR1_FLAGS (cEcr1_flags)

enum csky_isa_feature
fcr_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(fcr),CSKY_ISA_FEATURE_GET(none)};
#define FCR_FLAGS (fcr_flags)

enum csky_isa_feature
dspv2_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(dspv2),CSKY_ISA_FEATURE_GET(none)};
#define DSPV2_FLAGS (dspv2_flags)

enum csky_isa_feature
vdsp128_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(vdsp128),CSKY_ISA_FEATURE_GET(none)};
#define VDSP128_FLAGS (vdsp128_flags)

enum csky_isa_feature
vdsp64_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(vdsp64),CSKY_ISA_FEATURE_GET(none)};
#define VDSP64_FLAGS (vdsp64_flags)

enum csky_isa_feature
vdspv2_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(vdspv2),CSKY_ISA_FEATURE_GET(none)};
#define VDSPV2_FLAGS (vdspv2_flags)

enum csky_isa_feature
vdspv2_f_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(vdspv2_f),CSKY_ISA_FEATURE_GET(none)};
#define VDSPV2_F_FLAGS (vdspv2_f_flags)

enum csky_isa_feature
vdsp_128_v2_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(vdsp128),CSKY_ISA_FEATURE_GET(vdspv2),CSKY_ISA_FEATURE_GET(none)};
#define VDSP_128_V2_FLAGS (vdsp_128_v2_flags)

enum csky_isa_feature
none_flags[ISA_MAX_BUILTIN_VERSIONS]
        = {CSKY_ISA_FEATURE_GET(none)};
#define NONE_FLAGS (none_flags)

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
     these types are registered by csky_init_simd_builtin_types ().  In other
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
#define qi_UP     QImode
#define sq_UP     SQmode
#define v2sq_UP   V2SQmode
#define v2hq_UP   V2HQmode
#define v4qq_UP   V4QQmode
#define v2usq_UP  V2USQmode
#define v2uhq_UP  V2UHQmode
#define v4uqq_UP  V4UQQmode

#define v2di_UP    V2DImode
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

#define hf_UP   HFmode
#define sf_UP   SFmode

#define v8hf_UP   V8HFmode
#define v4sf_UP   V4SFmode
#define v2df_UP   V2DFmode

#define UP(X) X##_UP

typedef struct {
  /* Decide if the current CPU contains this builtin function.  */
  enum csky_isa_feature *isa_flag;
  const char *name;
  machine_mode mode;
  const enum insn_code code;
  unsigned int fcode;
  enum csky_type_qualifiers *qualifiers;
} csky_builtin_datum;

#define CF(N,X) CODE_FOR_csky_##N##X

#define VAR1(I, T, N, A) \
  {I##_FLAGS, #N #A, UP (A), CF (N, A), 0, T##_QUALIFIERS},

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

static tree csky_floatHF_type_node = NULL_TREE;
static tree csky_simd_intOI_type_node = NULL_TREE;
static tree csky_simd_intCI_type_node = NULL_TREE;
static tree csky_simd_intXI_type_node = NULL_TREE;

const char *csky_scalar_builtin_types[] = {
    "__builtin_csky_oi",
    "__builtin_csky_ci",
    "__builtin_csky_xi",
    "__fp16",
    NULL,
  };

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
  csky_simd_types[Int64x2_t].eltype = intDI_type_node;

  csky_simd_types[UInt8x4_t].eltype =unsigned_intQI_type_node;
  csky_simd_types[UInt8x8_t].eltype =unsigned_intQI_type_node;
  csky_simd_types[UInt8x16_t].eltype =unsigned_intQI_type_node;
  csky_simd_types[UInt16x2_t].eltype =unsigned_intHI_type_node;
  csky_simd_types[UInt16x4_t].eltype =unsigned_intHI_type_node;
  csky_simd_types[UInt16x8_t].eltype =unsigned_intHI_type_node;
  csky_simd_types[UInt32x2_t].eltype =unsigned_intSI_type_node;
  csky_simd_types[UInt32x4_t].eltype =unsigned_intSI_type_node;
  csky_simd_types[UInt64x2_t].eltype =unsigned_intDI_type_node;

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

  csky_simd_types[Float16x8_t].eltype = csky_floatHF_type_node;
  csky_simd_types[Float32x4_t].eltype = float_type_node;
  csky_simd_types[Float64x2_t].eltype = double_type_node;

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

  csky_simd_intOI_type_node = make_signed_type (GET_MODE_PRECISION (OImode));
  csky_simd_intCI_type_node = make_signed_type (GET_MODE_PRECISION (CImode));
  csky_simd_intXI_type_node = make_signed_type (GET_MODE_PRECISION (XImode));

  tdecl = add_builtin_type
            ("__builtin_csky_oi" , csky_simd_intOI_type_node);
  TYPE_NAME (csky_simd_intOI_type_node) = tdecl;

  tdecl = add_builtin_type
            ("__builtin_csky_ci" , csky_simd_intCI_type_node);
  TYPE_NAME (csky_simd_intCI_type_node) = tdecl;

  tdecl = add_builtin_type
            ("__builtin_csky_xi" , csky_simd_intXI_type_node);
  TYPE_NAME (csky_simd_intXI_type_node) = tdecl;
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
      case OImode:
        return csky_simd_intOI_type_node;
      case CImode:
        return csky_simd_intCI_type_node;
      case XImode:
        return csky_simd_intXI_type_node;
      case SQmode:
        return sat_long_fract_type_node;
      case HFmode:
        return csky_floatHF_type_node;
      case SFmode:
        return float_type_node;
      case DFmode:
        return double_type_node;
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

static void
csky_init_fp16_builtins (void)
{
  csky_floatHF_type_node = make_node (REAL_TYPE);
  TYPE_PRECISION (csky_floatHF_type_node) = GET_MODE_PRECISION (HFmode);
  layout_type (csky_floatHF_type_node);
  (*lang_hooks.types.register_builtin_type) (csky_floatHF_type_node, "__fp16");
}

const char *
csky_mangle_builtin_type (const_tree type)
{
  int i = 0;

  while (csky_scalar_builtin_types[i] != NULL)
    {
      const char *name = csky_scalar_builtin_types[i];

      if (TREE_CODE (TYPE_NAME (type)) == TYPE_DECL
          && DECL_NAME (TYPE_NAME (type))
          && !strcmp (IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (type))), name))
        return csky_scalar_builtin_types[i];
      i++;
    }
  return NULL;
}

static int
op_num_of_insn(const struct insn_data_d a_insn_data)
{
  int op_num = a_insn_data.n_operands - 1;
  if (a_insn_data.operand[op_num].predicate == scratch_operand)
    op_num -= 1;

  return op_num;
}

void
csky_init_builtins (void)
{
  bool suc = false;
  unsigned int i, fcode = CSKY_BUILTIN_PATTERN_START;

  csky_init_fp16_builtins ();

  csky_init_simd_builtin_types ();

  for (i = 0; i < ARRAY_SIZE (csky_builtin_data); i++, fcode++)
    {
      csky_builtin_datum *d = &csky_builtin_data[i];
      tree ftype = NULL;
      char namebuf[60];
      tree fndecl = NULL;

      while (d->isa_flag)
        {
          if (*(d->isa_flag) == CSKY_ISA_FEATURE_GET(none))
            break;
          if (csky_arch_isa_features[*(d->isa_flag)])
            {
              suc = true;
              break;
            }

          d->isa_flag++;
        }

      if (suc == false)
        continue;

      d->fcode = fcode;

      int op_num = op_num_of_insn(insn_data[d->code]);
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

          if ((d->qualifiers[1] & qualifier_void) != 0)
            args = NULL;
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

          if (thisarg != CSKY_ARG_GEN_REG)
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
	      case CSKY_ARG_GEN_REG:
		op[argc] = gen_reg_rtx(mode[argc]);
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
              case CSKY_ARG_IMM_U63_D15:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 0 || imm > 63)
                      error ("%Kargument %d must be in 0 to 63", exp, argc+1);
                    else if ((imm & 15) == 15)
                      error ("the last four bits of %Kargument %d must not be 1 entirely", exp, argc+1);
                  }
                goto constant_arg;
              case CSKY_ARG_IMM_IMMUU:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 1 || imm > 16)
                      error ("%Kargument %d must be in 1 to 16", exp, argc+1);
                  }
              goto constant_arg;
              case CSKY_ARG_IMM_IMMJ:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < 1 || imm > 32)
                      error ("%Kargument %d must be in 1 to 32", exp, argc+1);
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
              case CSKY_ARG_IMM_IMMUW:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    if (imm < -128 || imm > 127)
                      error ("%Kargument %d must be in -128 to 127(signed) or 0 to 255 (unsigned)", exp, argc+1);
                  }
                goto constant_arg;
            case CSKY_ARG_IMM_IMMUHW:
              if (CONST_INT_P (op[argc]))
              {
                machine_mode tmode = target ? GET_MODE(target) : mode[0];
                int scale = 1;
                switch(tmode)
                {
                  case V16QImode:
                    scale = 1;
                    break;
                  case V8HImode:
                  case V8HFmode:
                    scale = 2;
                    break;
                  case V4SImode:
                  case V4SFmode:
                    scale = 4;
                    break;
                  case V2DImode:
                    scale = 8;
                    break;
                  default:
                    gcc_unreachable();
                }
                int imm = INTVAL (op[argc]);
                if(imm % scale != 0 || imm/scale < 0 || imm/scale > 127)
                  error ("%Kargument %d must be in (0 to 127)x%d (unsigned/signed)", exp, argc+1,scale);
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
                    /* csky don't have real (128*2/3/4) reg, but in two 128 regs,
                       so index should be as 128*/
                    int scale = 1;
                    int limit;
                    if(CSKY_VDSP_STRUCT_MODE_P(mode[argc-1]))
                      {
                        limit = 15;
                      }
                    else
                      limit = TYPE_VECTOR_SUBPARTS(vec_type)/scale - 1;

                    gcc_assert (limit == 15 || limit == 7 || limit == 3 || limit == 1);
                    if (imm < 0 || imm > limit)
                      error ("%Kargument %d must be in 0 to %d",
                             exp, argc+1, limit);
                  }
                goto constant_arg;
              case CSKY_ARG_INDEXV128_B8:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    tree vec_type;
                    /* op0(return value)'s mode is vect mode, but else argument is not. */
                    vec_type = csky_simd_builtin_type(tmode, false);
                    int limit = (128 / TYPE_VECTOR_SUBPARTS(vec_type)) / 8 - 1;
                    gcc_assert (limit == 1 || limit == 3);
                    if (imm < 0 || imm > limit)
                      error ("%Kargument %d must be in 0 to %d",
                             exp, argc+1, limit);
                  }
                goto constant_arg;
              case CSKY_ARG_INDEXV128_M1:
                if (CONST_INT_P (op[argc]))
                {
                  int imm = INTVAL (op[argc]);
                  tree vec_type;
                  if (argc == 0)
                    vec_type = csky_simd_builtin_type(tmode, false);
                  else
                    vec_type = csky_simd_builtin_type(mode[argc-1], false);
                  /* csky dont have real 256 reg, but in two 128 regs, so index should be as 128*/
                  int scale = 1;
                  int limit;
                    if(mode[argc-1] == OImode)
                      {
                        limit = 14;
                      }
                    else
                      limit = TYPE_VECTOR_SUBPARTS(vec_type)/scale - 2;

                  gcc_assert (limit == 14 || limit == 6 || limit == 2 || limit == 0);
                  if (imm < 0 || imm > limit)
                    error ("%Kargument %d must be in 0 to %d",
                           exp, argc+1, limit);
                }
                goto constant_arg;
              case CSKY_ARG_IMM_ELEMENTSIZE0:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    tree vec_type;
                    if (argc == 0)
                      vec_type = csky_simd_builtin_type(tmode, false);
                    else
                      vec_type = csky_simd_builtin_type(mode[argc-1], false);
                    int limit = 128 / (TYPE_VECTOR_SUBPARTS(vec_type)) - 1;
                    gcc_assert (limit == 7 || limit == 15 || limit == 31 || limit == 63);
                    if (imm < 0 || imm > limit)
                      error ("%Kargument %d must be in 0 to %d",
                             exp, argc+1, limit);
                  }
                goto constant_arg;
              case CSKY_ARG_IMM_ELEMENTSIZE1:
                if (CONST_INT_P (op[argc]))
                  {
                    int imm = INTVAL (op[argc]);
                    tree vec_type;
                    if (argc == 0)
                      vec_type = csky_simd_builtin_type(tmode, false);
                    else
                      vec_type = csky_simd_builtin_type(mode[argc-1], false);
                    int limit = 128 / (TYPE_VECTOR_SUBPARTS(vec_type));
                    gcc_assert (limit == 8 || limit == 16 || limit == 32 || limit == 64);
                    if (imm < 1 || imm > limit)
                      error ("%Kargument %d must be in 1 to %d",
                             exp, argc+1, limit);
                  }
                goto constant_arg;
              case CSKY_ARG_IMM_ELEMENTSIZE2:
                if (CONST_INT_P (op[argc]))
                {
                  int imm = INTVAL (op[argc]);
                  tree vec_type;
                  if (argc == 0)
                    vec_type = csky_simd_builtin_type(tmode, false);
                  else
                    vec_type = csky_simd_builtin_type(mode[argc-1], false);
                  int limit = 2* (128 / (TYPE_VECTOR_SUBPARTS(vec_type))) - 1;
                  gcc_assert (limit == 15 || limit == 31 || limit == 63 || limit == 127);
                  if (imm < 0 || imm > limit)
                    error ("%Kargument %d must be in 1 to %d",
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
              case CSKY_ARG_FIXEDDV:
                if (!fp3_const_double_rtx (op[argc]))
                  error ("%Kargument %d must be correct fixed point number",
                             exp, argc+1);
                break;
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
              case CSKY_ARG_VOID:
                argc--;
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
        case 0:
          pat = GEN_FCN (icode) (target);
          break;
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

      if (insn_data[d->code].operand[k].predicate == scratch_operand)
	{
	  args[k] = CSKY_ARG_GEN_REG;
	}
      else if (d->qualifiers[k] & qualifier_maybe_immediate)
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
      else if (d->qualifiers[k] & qualifier_immUw)
        {
          args[k] = CSKY_ARG_IMM_IMMUW;
        }
      else if (d->qualifiers[k] & qualifier_immUhw)
      {
        args[k] = CSKY_ARG_IMM_IMMUHW;
      }
      else if (d->qualifiers[k] & qualifier_index01)
        {
          args[k] = CSKY_ARG_INDEX01;
        }
      else if (d->qualifiers[k] & qualifier_indexv128)
        {
          args[k] = CSKY_ARG_INDEXV128;
        }
      else if (d->qualifiers[k] & qualifier_indexv128_b8)
        {
          args[k] = CSKY_ARG_INDEXV128_B8;
        }
      else if(d->qualifiers[k] & qualifier_indexv128_m1)
        {
          args[k] = CSKY_ARG_INDEXV128_M1;
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
      else if (d->qualifiers[k] & qualifier_immU63_d15)
        {
          args[k] = CSKY_ARG_IMM_U63_D15;
        }
      else if (d->qualifiers[k] & qualifier_immUu)
        {
          args[k] = CSKY_ARG_IMM_IMMUU;
        }
      else if (d->qualifiers[k] & qualifier_immJ)
        {
          args[k] = CSKY_ARG_IMM_IMMJ;
        }
      else if (d->qualifiers[k] & qualifier_elementsize0)
        {
          args[k] = CSKY_ARG_IMM_ELEMENTSIZE0;
        }
      else if (d->qualifiers[k] & qualifier_elementsize1)
        {
          args[k] = CSKY_ARG_IMM_ELEMENTSIZE1;
        }
      else if (d->qualifiers[k] & qualifier_elementsize2)
        {
          args[k] = CSKY_ARG_IMM_ELEMENTSIZE2;
        }
      else if (d->qualifiers[k] & qualifier_fixedDv)
        {
          args[k] = CSKY_ARG_FIXEDDV;
        }
      else if (d->qualifiers[k] & qualifier_void)
        {
          args[k] = CSKY_ARG_VOID;
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
