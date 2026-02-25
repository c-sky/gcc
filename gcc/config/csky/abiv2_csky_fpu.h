
#ifndef GCC_CSKY_FPU_H
#define GCC_CSKY_FPU_H

/* vector support */
#define TARGET_SUPPORT_VDSP (CSKY_ISA_FEATURE(vdsp64) \
                             || CSKY_ISA_FEATURE(vdsp128))

#define TARGET_SUPPORT_VDSP128 (CSKY_ISA_FEATURE(vdsp128))

#define TARGET_SUPPORT_FPV3 (CSKY_ISA_FEATURE(fpv3_hf)    \
                             || CSKY_ISA_FEATURE(fpv3_sf) \
                             || CSKY_ISA_FEATURE(fpv3_df))

/* Run-time Target Specification.  */
#define TARGET_SOFT_FLOAT       (csky_float_abi == CSKY_FLOAT_ABI_SOFT)
/* Use hardware floating point instructions. */
#define TARGET_HARD_FLOAT       (csky_float_abi != CSKY_FLOAT_ABI_SOFT)
/* Use hardware floating point calling convention.  */
#define TARGET_HARD_FLOAT_ABI   (csky_float_abi == CSKY_FLOAT_ABI_HARD)
/* Use hardware vector register.  */
#define TARGET_SUPPORT_VREGS    (TARGET_HARD_FLOAT || TARGET_SUPPORT_VDSP)

#define TARGET_SUPPORT_VREGS3   (TARGET_SUPPORT_FPV3)

#define CSKY_FIRST_VFP_REGNUM         52
#define CSKY_LAST_VFP_REGNUM          67

#define CSKY_FIRST_VFP3_REGNUM        71
#define CSKY_LAST_VFP3_REGNUM         86

#define CSKY_NPARM_FREGS              4

#define CSKY_VREG_LOW_P(N) \
  ((N) >= CSKY_FIRST_VFP_REGNUM \
   && (N) <= CSKY_LAST_VFP_REGNUM)

#define CSKY_VREG_HI_P(N) \
  ((N) >= CSKY_FIRST_VFP3_REGNUM \
   && (N) <= CSKY_LAST_VFP3_REGNUM)

#define CSKY_VREG_P(N)    \
  (CSKY_VREG_LOW_P(N)     \
   || CSKY_VREG_HI_P(N))

#define CSKY_VREG_MODE_P(M)               \
  ((M) == SFmode || (M) == DFmode         \
   || (CSKY_ISA_FEATURE(fpv3_hf) && (M) == HFmode))

#define FUNCTION_VARG_REGNO_P(REGNO)      \
  (TARGET_HARD_FLOAT_ABI                  \
   && IN_RANGE ((REGNO), CSKY_FIRST_VFP_REGNUM, \
                CSKY_FIRST_VFP_REGNUM + CSKY_NPARM_FREGS - 1))

#endif
