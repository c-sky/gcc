/*
 * tmulss00.c - Test mulss in loop.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\t" 1 } } */
/* { dg-final { scan-assembler-times "mfhi\t" 1 } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */
/* { dg-final { scan-assembler-not "mthi\t"  } } */
/* { dg-final { scan-assembler-not "mtlo\t"  } } */
/* { dg-final { scan-assembler-times "mulss\t" 6 } } */


void t_mulss00(const long *in1, const long *in2, const long *in3, long long *out)
{
    long long res;

    /* muls for first HI/LO */
    res =  (long long)in2[0] * in3[0];
    /* mulss */
    res -= (long long)in2[2] * in3[2];
    res -= (long long)in2[3] * in3[3];
    res -= (long long)in1[4] * in2[4];
    res -= (long long)in1[5] * in2[5];
    res -= (long long)in2[6] * in1[6];
    res -= (long long)in1[7] * in3[7];

    /* mfhi/mflo */
    out[0] = res;
}
