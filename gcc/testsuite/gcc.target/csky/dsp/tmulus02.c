/*
 * tmulus02.c - Test mulus.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulu\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulus\tr" 3 } } */
/* { dg-final { scan-assembler-not "mtlo\tr"  } } */
/* { dg-final { scan-assembler-times "mflo\tr" 1 } } */

void t_mulus02(
    const unsigned long *in1, const unsigned long *in2, unsigned long *out)
{
    unsigned long long res;
    unsigned long long temp;

    /* mulu */
    res  = (unsigned long long)in1[0] * in2[0];
    /* mulus part1 */
    temp   = (unsigned long long)in1[2] * in2[2];
    /* Something like assignment */
    out[0] = in1[3];
    out[1] = in1[4];
    /* mulus part2 */
    res -= temp;
    res -= (unsigned long long)in1[1] * in2[1];
    res -= (unsigned long long)in1[5] * in2[5];

    out[2] = res;
}
