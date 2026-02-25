/*
 * tmulss02.c - Test to compile with "mulss".
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulss\tr" 3   } } */


void t_mulss02(const long *in1, const long *in2, const long *in3, long long *out)
{
    long long res;
    long long temp;

    /* muls for first HI/LO */
    res =  (long long)in2[0] * in3[0];
    /* mulss part1 */
    temp = (long long)in2[2] * in3[2];
    /* Something like assignment. */
    out[0] = in3[3];
    out[1] = in2[4];
    /* mulss part2 */
    res -= temp;
    res -= (long long)in1[1] * in3[1];
    res -= (long long)in1[5] * in3[5];

    /* mfhi/mflo */
    out[2] = res;
}
