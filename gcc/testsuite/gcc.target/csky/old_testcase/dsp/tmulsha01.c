/*
 * tmulsha01.c - Test mulsha for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsha\t" 2 } } */
#define MUL(dst, a, b)   { dst =  (long)a * b; }
#define MULA(dst, a, b)  { dst += (long )a * b; }

void t_mulsha01(const short *in1, const short *in2, long *out)
{
    long result;
    long temp;

    /* mulsh, mtlo */
    MUL (result, in1[0], in2[0]);
    /* mulsha part1,  is used with "result += temp"? */
    MUL(temp, in1[1], in2[1]);
    /* Something like branch. */
    if (in1[3] > in2[3])
    {
        out[0] = in2[3];
    }
    else
    {
        out[0] = in1[3];
    }
    /* mulsha part2 */
    result += temp;
    MULA (result, in1[0], in2[0]);

    /* mflo */
    out[1] = result;
}

