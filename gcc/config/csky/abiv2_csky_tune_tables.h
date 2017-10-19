
#ifndef GCC_CSKY_TUNE_TABLES_H
#define GCC_CSKY_TUNE_TABLES_H


const struct cpu_cost_table generic_extra_costs =
{
  /* ALU */
  {
    0,			/* arith.  */
  },
};

const struct tune_params csky_generic_tune =
{
  &generic_extra_costs,			/* Insn extra costs.  */
  NULL,                     /* Sched adj cost.  */
  csky_default_branch_cost,
  csky_default_logical_op_non_short_circuit,
};

#define CSKY_TUNE_GET(name) &csky_ ## name ## _tune


#endif
