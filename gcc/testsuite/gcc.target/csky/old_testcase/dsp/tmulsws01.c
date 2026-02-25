/*
 * tmulsws01.c - Test mulsws.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsw\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsws\t" 2 } } */
/* { dg-final { scan-assembler-times "mtlo\t" 1 } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */

void t_mulsws01(const short *ins1, const short *ins2, const int *in, long *out)
{
    long res;
    long temp;

    /* mulsw */
    res = ((unsigned long)(ins1[0] *  in[0])) >> 16;
    /* mulsws part1 */
    temp = ((unsigned long)(ins2[2] * in[2])) >> 16;
    /* Something like branch. */
    if (ins1[0] > ins2[0])
    {
      out[0] = ins1[0];
    }
    else
    {
      out[0] = ins2[0];
    }
    /* mulsws part2 */
    res -= temp;

    res -= ((unsigned long)(in[1]  * ins1[1])) >> 16;

    /* mflo */
    out[1] = res;
}
