/*
 * tmulswa02.c - Test mulswa.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsw\t" 1 } } */
/* { dg-final { scan-assembler-times "mulswa\t" 3 } } */

void t_mulswa02(const short *ins1, const short *ins2, const int *in, long *out)
{
    long res;
    long temp;

    /* mulsw */
    res = ((unsigned long)(ins1[0] *  in[0])) >> 16;
    /* mulswa part1 */
    temp = ((unsigned long)(ins2[2] * in[2])) >> 16;
    /* Something like assignment. */
    out[0] = ins1[3];
    out[1] = ins1[4];
    /* mulswa part2 */
    res += temp;

    res += ((unsigned long)(in[1]  * ins1[1])) >> 16;
    res += ((unsigned long)(in[5]  * ins1[5])) >> 16;

    /* mflo */
    out[2] = res;
}
