/*
 * tmulsha04.c - Test mulsha in loop.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\tr" 1} } */
/* { dg-final { scan-assembler-times "mulsha\tr" 1 } } */
/* { dg-final { scan-assembler-times "mtlo\tr" 1 } } */
/* { dg-final { scan-assembler-times "mflo\tr" 1 } } */

#define MUL(dst, a, b)   { dst =  (long)a * b; }
#define MULA(dst, a, b)  { dst += (long )a * b; }


void t_mulsha04(const short *in1, const short *in2, long *out, long asize)
{
    int i;
    long res;

    /* mulsh, mtlo */
    MUL(res,  in1[0], in2[0]);
    for (i = 1; i < asize; i++)
    {
        /* mulsha in loop */
        MULA(res, in1[i], in2[i]);
    }
    /* mflo */
    out[0] =  res;
}
