/*
 * tpmulss03.c - Test mulsa & mulss in parellel.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\tr" 2 } } */
/* { dg-final { scan-assembler-times "mulss\tr" 3   } } */
/* { dg-final { scan-assembler-times "mulsa\tr" 3   } } */
/* { dg-final { scan-assembler-times "mfhi\t" 2 } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */
/* { dg-final { scan-assembler-not "mthi\t" } } */
/* { dg-final { scan-assembler-not "mtlo\t" } } */

#define ASR(val, bits) ((-2 >> 1 == -1) ? \
         ((long)(val)) >> (bits) : ((long) (val)) / (1 << (bits)))
#define ASR_64(val, bits) ((-2 >> 1 == -1) ? \
         ((long long)(val)) >> (bits) : ((long long) (val)) / (1 << (bits)))

/* 
 * mulsa first, then mulss
 */
void t_mulss04(long *in1, long *in2, long long *out)
{
    long long res;
    long long res1;

    /* muls */
    res   = (long long)in1[0] * in2[0];
    /* mulsa */
    res  += (long long)in1[2] * in2[2];
    res  += (long long)in1[4] * in2[4];
    res  += (long long)in1[6] * in2[6];

    out[0] = res;

    /* muls*/
    res1  = (long long)in1[1] * in2[1];
    /* mulss */
    res1 -= (long long)in1[3] * in2[3];
    res1 -= (long long)in1[5] * in2[5];
    res1 -= (long long)in1[7] * in2[7];

    out[1] = ASR_64(res1, 32);
}
