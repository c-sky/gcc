/*
 * tmulsha02.c - Test mulsha for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\tr" 2 } } */
/* { dg-final { scan-assembler-times "mulsha\tr" 2 } } */
/* { dg-final { scan-assembler-times "mtlo\tr" 1 } } */
/* { dg-final { scan-assembler-times "mflo\tr" 1 } } */

#define MUL(dst, a, b)   { dst =  (long)a * b; }
#define MULA(dst, a, b)  { dst += (long )a * b; }

void t_mulsha02(const short *in1, const short *in2, long *out)
{
    long result;
    long temp;

    /* mulsh, mtlo */
    MUL (result, in1[0], in2[0]);
    /* mulsha part1,  is used with "result += temp"? */
    MUL(temp, in1[1], in2[1]);
    /* Something like assignment. */
    out[0] = in1[3];
    out[1] = in1[4];
    out[2] = in1[5] * in1[0];
    /* mulsha part2 */
    result += temp;
    MULA (result, in1[0], in2[0]);

    /* mflo */
    out[3] = result;
}

