
#ifndef CSKY_OPTS_H
#define CSKY_OPTS_H


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

/* The various CSKY FPUs.  */
enum csky_fpu_type
{
#undef CSKY_FPU
#define CSKY_FPU(NAME, CNAME, ISA) TARGET_FPU_##CNAME,
#include "abiv2_csky_fpus.def"
  TARGET_FPU_auto
#undef CSKY_FPU
};


#endif /* CSKY_OPTS_H */
