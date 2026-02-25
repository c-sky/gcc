
#ifndef GCC_CSKY_TUNE_TABLES_H
#define GCC_CSKY_TUNE_TABLES_H


const struct cpu_cost_table generic_extra_costs =
{
  /* ALU */
  {
    0,			/* arith.  */
  },
};

#define BASE_TUNE \
  &generic_extra_costs, \
  NULL, \
  csky_default_branch_cost, \
  csky_default_logical_op_non_short_circuit,

const struct tune_params csky_generic_tune =
{
  BASE_TUNE
  NULL,
};

const struct tune_params csky_ck803_tune =
{
  BASE_TUNE
  "fpv2_sf",
};

const struct tune_params csky_ck807_tune =
{
  BASE_TUNE
  "fpv2_divd",
};
#define csky_ck810_tune csky_ck807_tune

const struct tune_params csky_ck860_tune =
{
  BASE_TUNE
  "fpv3_sdf",
};

#define CSKY_TUNE_GET(name) &csky_ ## name ## _tune


#endif
