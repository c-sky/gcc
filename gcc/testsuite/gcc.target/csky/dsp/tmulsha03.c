/*
 * tmulsha03.c - Test mulsha for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-not "mulsh\tr"  } } */
/* { dg-final { scan-assembler-times "sexth\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulsha\tr" 1 } } */
/* { dg-final { scan-assembler-times "mtlo\tr" 1 } } */
/* { dg-final { scan-assembler-times "mflo\tr" 1 } } */


long t_mulsha03(const short b, short c, short d)
{
    long a;

    /* mtlo, mulsha, mflo */
    a = b + c * d;
    return a;
}
