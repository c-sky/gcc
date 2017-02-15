
#ifndef GCC_CSKY_ISA_FEATURE_H
#define GCC_CSKY_ISA_FEATURE_H


#define CSKY_ISA_FEATURE_DEFINE(x)  csky_isa_feature ## x
#define CSKY_ISA_FEATURE_GET(x)     CSKY_ISA_FEATURE_DEFINE(x)

enum csky_isa_feature
  {
    CSKY_ISA_FEATURE_DEFINE(none),
#undef  CSKY_ISA
#define CSKY_ISA(NAME, IDENT) \
    CSKY_ISA_FEATURE_DEFINE(IDENT),
#include "abiv2_csky_isa.def"
#undef  CSKY_ISA
    CSKY_ISA_FEATURE_DEFINE(max)
  };

#define CSKY_ISA_CK801      CSKY_ISA_FEATURE_GET(ck801)
#define CSKY_ISA_CK802      CSKY_ISA_FEATURE_GET(base)
#define CSKY_ISA_CK803      CSKY_ISA_CK802, CSKY_ISA_FEATURE_GET(ck803)
#define CSKY_ISA_CK803S     CSKY_ISA_CK803, CSKY_ISA_FEATURE_GET(ck803s)
#define CSKY_ISA_CK807      CSKY_ISA_CK803S, CSKY_ISA_FEATURE_GET(ck807)
#define CSKY_ISA_CK810      CSKY_ISA_CK807, CSKY_ISA_FEATURE_GET(ck810)

#define CSKY_ISA_DSP        CSKY_ISA_FEATURE_GET(dsp)

#define CSKY_ISA_VFPv2      CSKY_ISA_FEATURE_GET(vfpv2)
#define CSKY_ISA_ALL_FPU    CSKY_ISA_VFPv2, CSKY_ISA_FEATURE_GET(fp_dbl)

#define CSKY_ISA_FEAT(x) x,


#endif /* GCC_CSKY_ISA_FEATURE_H */
