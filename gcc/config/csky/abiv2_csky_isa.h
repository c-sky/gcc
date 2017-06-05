
#ifndef GCC_CSKY_ISA_FEATURE_H
#define GCC_CSKY_ISA_FEATURE_H


#ifndef CSKY_ISA_MACRO
#define CSKY_ISA_MACRO
#endif

#define CSKY_ISA_FEATURE_DEFINE(x)  isa_bit_ ## x
#define CSKY_ISA_FEATURE_GET(x)     CSKY_ISA_FEATURE_DEFINE(x)

enum csky_isa_feature
  {
    CSKY_ISA_FEATURE_DEFINE(none),
#undef  CSKY_ISA
#define CSKY_ISA(IDENT, DESC) \
    CSKY_ISA_FEATURE_DEFINE(IDENT),
#include "abiv2_csky_isa.def"
#undef  CSKY_ISA
    CSKY_ISA_FEATURE_DEFINE(max)
  };

#define CSKY_ISA_FEAT(x) x,
#define CSKY_ISA_FEAT_NONE CSKY_ISA_FEAT(isa_bit_none)


#endif /* GCC_CSKY_ISA_FEATURE_H */
