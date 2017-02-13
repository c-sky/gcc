
#ifndef GCC_CSKY_INTERNAL_H
#define GCC_CSKY_INTERNAL_H


#include "sbitmap.h"
#include "abiv2_csky_isa.h"
#include "abiv2_csky_opts.h"

struct csky_processors
{
  const char *const name;
  enum csky_processor_type core;
  const char *arch;
  enum csky_base_architecture base_arch;
  enum csky_isa_feature isa_bits[CSKY_ISA_FEATURE_GET(max)];
};

struct csky_fpu_desc
{
  const char *name;
  enum csky_isa_feature isa_bits[CSKY_ISA_FEATURE_GET(max)];
};


#endif /* GCC_CSKY_INTERNAL_H */
