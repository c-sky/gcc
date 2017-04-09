/*
 * tmulsa01.c - Test to compile with "mulsa".
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsa\t" 2 } } */


void t_mulsa01(const long *in1, const long *in2, const long *in3, long long *out)
{
    long long res;
    long long temp;

    /* muls for first HI/LO */
    res =  (long long)in2[0] * in3[0];
    /* mulsa part1 */
    temp = (long long)in2[2] * in3[2];
    /* Something like branch. */
    if (in2[3] > in3[3])
    {
        out[0] = in3[3];
    }
    else
    {
        out[0] = in2[3];
    }
    /* mulsa part2 */
    res += temp;
    res += (long long)in1[1] * in3[1];

    /* mfhi/mflo */
    out[1] = res;
}
