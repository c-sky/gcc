/*
 * tmulshs01.c - Test compiling mulshs.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulshs\tr" 3 } } */
/* { dg-final { scan-assembler-times "mflo\tr" 1 } } */
/* { dg-final { scan-assembler-times "mtlo\tr" 1 } } */


#define MUL(dst, a, b)   { dst =  (long)a * b; }
#define MULS(dst, a, b)  { dst -= (long )a * b; }


void t_mulshs01(const short *in1, const short *in2, long *out)
{
    long res;
    long temp;

    /* mulsh, mtlo */
    MUL (res, in1[0], in2[0]);
    /* mulshs part1, later with "res += temp" */
    MUL(temp, in1[1], in2[1]);
    /* Something like branch. */
    if (in1[2] > in2[2])
    {
        out[0] = in1[2];
    }
    else
    {
        out[0] = in2[2];
    }
    /* mulshs part2 */
    res -= temp;

    MULS(res, in1[3], in2[3]);
    MULS(res, in1[4], in2[4]);

    /* mflo */
    out[1] = res;
}
