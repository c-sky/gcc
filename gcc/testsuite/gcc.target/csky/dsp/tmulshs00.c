/*
 * tmulshs00.c - Test compiling mulshs.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulshs\tr" 7 } } */
/* { dg-final { scan-assembler-times "mflo\tr" 1 } } */
/* { dg-final { scan-assembler-times "mtlo\tr" 1 } } */


#define MUL(dst, a, b)   { dst =  (long)a * b; }
#define MULS(dst, a, b)  { dst -= (long )a * b; }


void t_mulshs00(const short *in1, const short *in2, long *out)
{
    long res;

    /* mulsh, mtlo */
    MUL (res, in1[0], in2[0]);
    /* mulshs */
    MULS(res, in1[1], in2[1]);
    MULS(res, in1[2], in2[2]);
    MULS(res, in1[3], in2[3]);
    MULS(res, in1[4], in2[4]);
    MULS(res, in1[5], in2[5]);
    MULS(res, in1[6], in2[6]);
    MULS(res, in1[7], in2[7]);

    /* mflo */
    out[0] = res;
}
