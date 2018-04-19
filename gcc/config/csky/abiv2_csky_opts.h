
#ifndef CSKY_OPTS_H
#define CSKY_OPTS_H


/* The various CSKY cores.  */
enum csky_processor_type
{
#undef CSKY_CORE
#define CSKY_CORE(NAME, INTERNAL_IDENT, IDENT, ARCH, ISA, T) \
  TARGET_CPU_##INTERNAL_IDENT,
#include "abiv2_csky_cores.def"
#undef CSKY_CORE
  /* Used to indicate that no processor has been specified.  */
  TARGET_CPU_csky_none
};
#define CSKY_TARGET_CORE_GET(name) TARGET_CPU_ ## name

/* The various CSKY architectures.  */
enum csky_base_architecture
{
#undef CSKY_ARCH
#define CSKY_ARCH(NAME, CORE_IDENT, ARCH, ISA) \
  CSKY_BASE_ARCH_##ARCH,
#include "abiv2_csky_cores.def"
#undef CSKY_ARCH
  CSKY_BASE_ARCH_NONE
};
#define CSKY_TARGET_ARCH_GET(name) CSKY_BASE_ARCH_ ## name

/* The various CSKY FPUs.  */
enum csky_fpu_type
{
#undef CSKY_FPU
#define CSKY_FPU(NAME, CNAME, ISA) TARGET_FPU_##CNAME,
#include "abiv2_csky_cores.def"
  TARGET_FPU_auto
#undef CSKY_FPU
};
#define CSKY_TARGET_FPU_GET(name) TARGET_FPU_ ## name

enum float_abi_type
{
  CSKY_FLOAT_ABI_SOFT,
  CSKY_FLOAT_ABI_SOFTFP,
  CSKY_FLOAT_ABI_HARD
};

#endif /* CSKY_OPTS_H */
