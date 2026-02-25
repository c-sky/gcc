/*
 * tmulswa01.c - Test to compile mulswa.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsw\t" 1 } } */
/* { dg-final { scan-assembler-times "mulswa\t" 2 } } */


void t_mulswa01(short *ins1, short *ins2, const int *in, long *out)
{
    long res;
    long temp;

    /* mulsw */
    res = ((unsigned long)(ins1[0] *  in[0])) >> 16;
    /* mulswa part1 */
    temp = ((unsigned long)(ins2[1] * in[1])) >> 16;
    /* Something like branch. */
    if (ins1[0] > ins2[0])
    {
      out[0] = ins1[0];
    }
    else
    {
      out[0] = ins2[0];
    }

    /* mulswa part2 */
    res += temp;
    res += ((unsigned long)(in[2]  * ins1[2])) >> 16;

    /* mflo */
    out[1] =  res;
}
