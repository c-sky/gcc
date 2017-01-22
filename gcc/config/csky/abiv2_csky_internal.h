
#ifndef GCC_CSKY_INTERNAL_H
#define GCC_CSKY_INTERNAL_H


#include "sbitmap.h"
#include "abiv2_csky_isa.h"

/* The various CSKY cores.  */
enum csky_processor_type
{
#undef CSKY_CORE
#define CSKY_CORE(NAME, INTERNAL_IDENT, IDENT, ARCH, ISA) \
  TARGET_CPU_##INTERNAL_IDENT,
#include "abiv2_csky_cores.def"
#undef CSKY_CORE
  /* Used to indicate that no processor has been specified.  */
  TARGET_CPU_csky_none
};

/* The various CSKY architectures.  */
enum csky_base_architecture
{
  CSKY_BASE_ARCH_NONE,
#undef CSKY_ARCH
#define CSKY_ARCH(NAME, CORE_IDENT, ARCH, ISA) \
  CSKY_BASE_ARCH_##ARCH,
#include "abiv2_csky_arches.def"
#undef CSKY_ARCH
   CSKY_BASE_ARCH_MAX
};

struct csky_processors
{
  const char *const name;
  enum csky_processor_type core;
  const char *arch;
  enum csky_base_architecture base_arch;
  enum csky_isa_feature isa_bits[CSKY_ISA_FEATURE_GET(max)];
};

/* The various CSKY FPUs.  */
enum csky_fpu_type
{
#undef CSKY_FPU
#define CSKY_FPU(NAME, CNAME, ISA) TARGET_FPU_##CNAME,
#include "abiv2_csky_fpus.def"
  TARGET_FPU_auto
#undef CSKY_FPU
};

struct csky_fpu_desc
{
  const char *name;
  enum csky_isa_feature isa_bits[CSKY_ISA_FEATURE_GET(max)];
};

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
