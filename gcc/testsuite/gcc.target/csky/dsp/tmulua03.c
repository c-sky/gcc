/*
 * tmulua03.c - Test mulua in loop.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulu\tr" 1} } */
/* { dg-final { scan-assembler-times "mulua\tr" 1 } } */
/* { dg-final { scan-assembler-times "mfhi\tr" 1 } } */
/* { dg-final { scan-assembler-times "mflo\tr" 1 } } */

void t_mulua03(const unsigned long *in1, const unsigned long *in2,
               unsigned long long *out, int asize)
{
    int i;
    unsigned long long res;

    /* mulu for first HI/LO */
    res = (unsigned long long)in1[0] * in2[0];

    for (i = 1; i < asize; i++)
    {
        /* mulua in loop */
        res += (unsigned long long)in1[i] * in2[i];
    }
    /* mfhi/mflo */
    out[0] = res;
}
