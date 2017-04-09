/*
 * tmulsa05.c - Test mulsa in loop.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\t" 1 } } */
/* { dg-final { scan-assembler-times "mfhi\t" 1 } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsa\t" 1 } } */


void t_mulsa05(const long *in1, const long *in2, long long *out, int asize)
{
    int i;
    long long res;

    /* muls for first HI/LO */
    res = (long long)in1[0] * in2[0];

    for (i = 1; i < asize; i++)
    {
        /* mulsa in loop */
        res += (long long)in1[i] * in2[i];
    }
    /* mfhi/mflo */
    out[0] = res;
}
