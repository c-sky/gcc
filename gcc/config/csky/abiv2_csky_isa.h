
#ifndef GCC_CSKY_ISA_FEATURE_H
#define GCC_CSKY_ISA_FEATURE_H


#define CSKY_ISA_FEATURE_DEFINE (x) csky_isa_feature ## x
#define CSKY_ISA_FEATURE_GET(x)     CSKY_ISA_FEATURE_DEFINE(x)

enum csky_isa_feature
  {
    CSKY_ISA_FEATURE_DEFINE(none),  /* Must be first.  */

    CSKY_ISA_FEATURE_DEFINE(base),  /* Base instructions, base on ck802.  */

    CSKY_ISA_FEATURE_DEFINE(ck803),	/* Extended insns for arch ck803.  */
    CSKY_ISA_FEATURE_DEFINE(ck803s),/* Extended insns for arch ck803s.  */
    CSKY_ISA_FEATURE_DEFINE(ck807), /* Extended insns for arch ck807.  */
    CSKY_ISA_FEATURE_DEFINE(ck810), /* Extended insns for arch ck810.  */

    /* Specific insns mode */
    CSKY_ISA_FEATURE_DEFINE(ck801), /* ck801 instructions.  */
    CSKY_ISA_FEATURE_DEFINE(smart), /* TODO.  */

    /* Extended specific functions */
    CSKY_ISA_FEATURE_DEFINE(dsp),   /* Extended insns for DSP.  */

    /* VFP */
    CSKY_ISA_FEATURE_DEFINE(vfpv2),
    CSKY_ISA_FEATURE_DEFINE(fp_dbl),/* Double precision operations supported.  */

    /* Must be last, used to dimension arrays.  */
    CSKY_ISA_FEATURE_DEFINE(max)
  };

#define CSKY_ISA_CK801      CSKY_ISA_FEATURE_GET(ck801)
#define CSKY_ISA_CK802      CSKY_ISA_FEATURE_GET(base)
#define CSKY_ISA_CK803      CSKY_ISA_CK802, CSKY_ISA_FEATURE_DEFINE(ck803)
#define CSKY_ISA_CK803S     CSKY_ISA_CK803, CSKY_ISA_FEATURE_GET(ck803s)
#define CSKY_ISA_CK807      CSKY_ISA_CK803S, CSKY_ISA_FEATURE_GET(ck807)
#define CSKY_ISA_CK810      CSKY_ISA_CK807, CSKY_ISA_FEATURE_GET(ck810)

#define CSKY_ISA_DSP        CSKY_ISA_FEATURE_GET(dsp)

#define CSKY_ISA_VFPv2      CSKY_ISA_FEATURE_GET(vfpv2)
#define CSKY_ISA_ALL_FPU    CSKY_ISA_VFPv2, CSKY_ISA_FEATURE_GET(fp_dbl)

#define CSKY_ISA_FEAT(x) x,


#endif /* GCC_CSKY_ISA_FEATURE_H */
