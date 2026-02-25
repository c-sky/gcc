/*
 * tmulss05.c - Test mulss in loop.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\t" 1 } } */
/* { dg-final { scan-assembler-times "mfhi\t" 1 } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */
/* { dg-final { scan-assembler-times "mulss\t" 1 } } */

void t_mulss05(const long *in1, const long *in2, long long *out, int ssize)
{
    int i;
    long long res;

    /* muls */
    res = (long long)in1[0] * in2[0];
    for (i = 1; i < ssize; i++)
    {
        /* mulss */
        res -= (long long)in1[i] * in2[i];
    }
    /* mfhi/mflo */
    out[0] = res;
}
