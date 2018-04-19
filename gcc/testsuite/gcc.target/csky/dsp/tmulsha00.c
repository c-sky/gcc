/*
 * tmulsha00.c - Test mulsha for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulsha\tr" 8 } } */
/* { dg-final { scan-assembler-not "mfhi\tr"  } } */
/* { dg-final { scan-assembler-not "mthi\tr"  } } */
/* { dg-final { scan-assembler-times "mflo\tr" 2 } } */
/* { dg-final { scan-assembler-times "mtlo\tr" 2 } } */
/* { dg-final { scan-assembler-times "sexth\tr" 1 } } */
#define MUL(dst, a, b)   { dst =  (long)a * b; }
#define MULA(dst, a, b)  { dst += (long )a * b; }

void t_mulsha00(const short *in1, const short *in2, long *out)
{
    long result;

    /* mulsh, mtlo */
    MUL (result, in1[0], in2[0]);
    /* mulsha */
    MULA(result, in1[1], in2[1]);
    MULA(result, in1[2], in2[2]);
    MULA(result, in1[3], in2[3]);
    MULA(result, in1[4], in2[4]);
    MULA(result, in1[5], in2[5]);
    MULA(result, in1[6], in2[6]);
    MULA(result, in1[7], in2[7]);

    /* mflo */
    out[0] = result;
}

long t_mulsha_2(const short b, short c, short d)
{
    long a;

    /* mtlo, mulsha, mflo */
    a = b + c * d;
    return a;
}
