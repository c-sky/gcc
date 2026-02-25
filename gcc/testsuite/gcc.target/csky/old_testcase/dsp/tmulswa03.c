/*
 * tmulswa03.c - Test mulswa in loop.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsw\t" 1 } } */
/* { dg-final { scan-assembler-not "mfhi\t"  } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */
/* { dg-final { scan-assembler-times "mulswa\t" 1 } } */


void t_mulswa03(const short *in1, const long *in2, long *out, int asize)
{
    int i;
    long res;

    /* mulsw for first HI/LO */
    res = ((unsigned long)(in1[0] * in2[0])) >> 16;

    for (i = 1; i < asize; i++)
    {
        /* mulswa in loop */
        res += ((unsigned long)(in1[i] * in2[i])) >> 16;
    }
    /* mflo */
    out[0] = res;
}
