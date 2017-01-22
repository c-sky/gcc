
#ifndef GCC_CSKY_ISA_FEATURE_H
#define GCC_CSKY_ISA_FEATURE_H


#define CSKY_ISA_FEATURE_DEFINE (x) csky_isa_feature ## x
#define CSKY_ISA_FEATURE_GET(x)     CSKY_ISA_FEATURE_DEFINE(x)

enum csky_isa_feature
  {
    CSKY_ISA_FEATURE_DEFINE(none), /* Must be first.  */

    CSKY_ISA_FEATURE_DEFINE(base), /* base instructions.  */

    /* TODO  */

    /* Must be last, used to dimension arrays.  */
    CSKY_ISA_FEATURE_DEFINE(max)
  };

#define CSKY_ISA_CK801      CSKY_ISA_FEATURE_GET(none)
#define CSKY_ISA_CK802      CSKY_ISA_FEATURE_GET(none)
#define CSKY_ISA_CK803      CSKY_ISA_FEATURE_GET(none)
#define CSKY_ISA_CK803S     CSKY_ISA_FEATURE_GET(none)
#define CSKY_ISA_CK807      CSKY_ISA_FEATURE_GET(none)
#define CSKY_ISA_CK810      CSKY_ISA_FEATURE_GET(none)

#define CSKY_ISA_DSP        CSKY_ISA_FEATURE_GET(none)

#define CSKY_ISA_VFPv2      CSKY_ISA_FEATURE_GET(none)
#define CSKY_ISA_ALL_FPU    CSKY_ISA_VFPv2

#define CSKY_ISA_FEAT(x) x,


#endif /* GCC_CSKY_ISA_FEATURE_H */
