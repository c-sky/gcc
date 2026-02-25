/*
 * tmulshs02.c - Test compiling mulshs.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\t" 4 } } */
/* { dg-final { scan-assembler-times "mulshs\t" 3 } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */
/* { dg-final { scan-assembler-times "mtlo\t" 1 } } */


#define MUL(dst, a, b)   { dst =  (long)a * b; }
#define MULS(dst, a, b)  { dst -= (long )a * b; }


void t_mulshs02(const short *in1, const short *in2, long *out)
{
    long res;
    long temp;

    /* mulsh, mtlo */
    MUL (res, in1[0], in2[0]);
    /* mulshs part1, later with "res += temp" */
    MUL(temp, in1[1], in2[1]);
    /* Something like mulsh and assignment */
    MUL(out[0], in1[2], in2[2]);
    MUL(out[1], in1[3], in2[3]);
    MUL(out[2], in1[4], in2[4]);
    /* mulshs, part2 */
    res -= temp;

    MULS(res, in1[6], in2[6]);
    MULS(res, in1[7], in2[7]);

    /* mflo */
    out[0] = res;
}
