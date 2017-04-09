/*
 * tmulua.c - Test mulua.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulu\t" 1 } } */
/* { dg-final { scan-assembler-times "mulua\t" 2 } } */

void t_mulua01(
    const unsigned long *in1, const unsigned long *in2, unsigned long *out)
{
    unsigned long long res;
    unsigned long long temp;

    /* mulu */
    res  = (unsigned long long)in1[0] * in2[0];
    /* mulua part1 */
    temp = (unsigned long long)in1[2] * in2[2];
    /* Something like branch. */
    if (in1[0] > in2[0])
    {
      out[0] = in1[0];
    }
    else
    {
      out[0] = in2[0];
    }
    /* mulua part2 */
    res += temp;
    res += (unsigned long long)in1[1] * in2[1];

    out[1] = res;
}
