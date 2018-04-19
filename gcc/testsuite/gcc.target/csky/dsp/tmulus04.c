/*
 * tmulus04.c - Test mulus in parellel.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulu\tr" 2 } } */
/* { dg-final { scan-assembler-times "mulus\tr" 6  } } */
/* { dg-final { scan-assembler-times "mtlo\tr" 2 } } */
/* { dg-final { scan-assembler-times "mflo\tr" 2 } } */
/* { dg-final { scan-assembler-times "mthi\tr" 2 } } */
/* { dg-final { scan-assembler-times "mfhi\tr" 2 } } */

void t_mulus04(unsigned long *in1, unsigned long *in2, unsigned long long *out)
{
    unsigned long long res;
    unsigned long long res1;

    /* mulu */
    res   = (unsigned long long)in1[0] * in2[0];
    /* mulus */
    res  -= (unsigned long long)in1[2] * in2[2];
    res  -= (unsigned long long)in1[4] * in2[4];
    res  -= (unsigned long long)in1[6] * in2[6];

    out[0] = res;

    /* mulu */
    res1  = (unsigned long long)in1[1] * in2[1];
    /* mulus */
    res1 -= (unsigned long long)in1[3] * in2[3];
    res1 -= (unsigned long long)in1[5] * in2[5];
    res1 -= (unsigned long long)in1[7] * in2[7];

    out[1] = res1;
}
