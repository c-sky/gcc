
#ifndef GCC_CSKY_INTERNAL_H
#define GCC_CSKY_INTERNAL_H


#include "abiv2_csky_isa.h"
#include "abiv2_csky_opts.h"

struct csky_processors
{
  const char *const name;
  enum csky_processor_type core;
  const char *arch;
  enum csky_base_architecture base_arch;
  enum csky_isa_feature isa_bits[CSKY_ISA_FEATURE_GET(max)];
  int flags;
};

struct csky_fpu_desc
{
  const char *name;
  enum csky_isa_feature isa_bits[CSKY_ISA_FEATURE_GET(max)];
};

/* Active target architecture.  */
struct csky_build_target
{
  /* Name of the target CPU, if known, or NULL if the target CPU was not
     specified by the user (and inferred from the -march option).  */
  const char *core_name;
  /* Name of the target ARCH.  NULL if there is a selected CPU.  */
  const char *arch_name;
  /* Preprocessor substring (never NULL).  */
  const char *arch_pp_name;
  /* CPU identifier for the core we're compiling for (architecturally).  */
  enum csky_processor_type arch_core;
  /* The base architecture value.  */
  enum csky_base_architecture base_arch;
  /* Bitmap encapsulating the isa_bits for the target environment.  */
  sbitmap isa;
};


#endif /* GCC_CSKY_INTERNAL_H */
