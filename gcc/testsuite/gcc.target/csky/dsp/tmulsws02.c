/*
 * tmulsws02.c - Test mulsws.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsw\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsws\t" 3 } } */
/* { dg-final { scan-assembler-times "mtlo\t" 1 } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */

void t_mulsws02(const short *ins1, const short *ins2, const int *in, long *out)
{
    long res;
    long temp;

    /* mulsw */
    res = ((unsigned long)(ins1[0] *  in[0])) >> 16;
    /* mulsws part1 */
    temp = ((unsigned long)(ins2[2] * in[2])) >> 16;
    /* Something like assignment. */
    out[0] = ins1[3];
    out[1] = ins1[4];
    /* mulsws part2 */
    res -= temp;

    res -= ((unsigned long)(in[1]  * ins1[1])) >> 16;
    res -= ((unsigned long)(in[5]  * ins1[5])) >> 16;

    /* mflo */
    out[2] = res;
}
