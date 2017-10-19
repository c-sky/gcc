
#ifndef GCC_CSKY_INTERNAL_H
#define GCC_CSKY_INTERNAL_H


#include "abiv2_csky_isa.h"
#include "abiv2_csky_opts.h"

/* RTX cost table definitions.  These are used when tuning for speed rather
   than for size and should reflect the _additional_ cost over the cost
   of the fastest instruction in the machine, which is COSTS_N_INSNS (1).
   Therefore it's okay for some costs to be 0.
   Costs may not have a negative value.  */
struct alu_cost_table
{
  const int arith;      /* ADD/SUB.  */
};

struct cpu_cost_table
{
  const struct alu_cost_table alu;
};

struct tune_params
{
  const struct cpu_cost_table *insn_extra_cost;
  bool (*sched_adjust_cost) (rtx_insn *, int, rtx_insn *, int *);

  int (*branch_cost) (bool, bool);
  bool (*logical_op_non_short_circuit) (void);
};


struct csky_option2isa
{
  int flag;
  enum csky_isa_feature isa_bits[CSKY_ISA_FEATURE_GET(max)];
};

struct csky_processors
{
  const char *const name;
  enum csky_processor_type core;
  const char *arch;
  enum csky_base_architecture base_arch;
  enum csky_isa_feature isa_bits[CSKY_ISA_FEATURE_GET(max)];
  const struct tune_params *const tune;
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
  /* Tables with more detailed tuning information.  */
  const struct tune_params *tune;
};


#endif /* GCC_CSKY_INTERNAL_H */
