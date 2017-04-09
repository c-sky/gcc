/*
 * tmulus05.c - Test mulus in parellel.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulu\t" 2 } } */
/* { dg-final { scan-assembler-times "mfhi\t" 2 } } */
/* { dg-final { scan-assembler-times "mflo\t" 2 } } */
/* { dg-final { scan-assembler-times "mulus\t" 6 } } */

void t_mulus05(unsigned long *in1, unsigned long *in2, unsigned long long *out)
{
    unsigned long long res;
    unsigned long long res1;

    /* mulu */
    res   = (unsigned long long)in1[0] * in2[0];
    res1  = (unsigned long long)in1[1] * in2[1];
    /* mulus */
    res  -= (unsigned long long)in1[2] * in2[2];
    res1 -= (unsigned long long)in1[3] * in2[3];
    res  -= (unsigned long long)in1[4] * in2[4];
    res1 -= (unsigned long long)in1[5] * in2[5];
    res  -= (unsigned long long)in1[6] * in2[6];
    res1 -= (unsigned long long)in1[7] * in2[7];

    out[0] = res;
    out[1] = res1;
}
