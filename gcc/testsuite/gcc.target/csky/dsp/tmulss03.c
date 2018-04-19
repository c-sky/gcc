/*
 * tpmulss03.c - Test mulsa & mulss in parellel.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\t" 2 } } */
/* { dg-final { scan-assembler-times "mulss\t" 3 } } */
/* { dg-final { scan-assembler-times "mulsa\t" 3 } } */


#define ASR(val, bits) ((-2 >> 1 == -1) ? \
         ((long)(val)) >> (bits) : ((long) (val)) / (1 << (bits)))
#define ASR_64(val, bits) ((-2 >> 1 == -1) ? \
         ((long long)(val)) >> (bits) : ((long long) (val)) / (1 << (bits)))

/*
 * mulsa & mulss in the same time.
 * but compiling result must be same with t_p_mulsa_mulss_1.
 *
 * Can same to t_mulss04
 */
void t__mulss03(long *in1, long *in2, long long *out)
{
    long long res;
    long long res1;

    /* muls followed by "res  += (long long)in1[2] * in2[2];" */
    res   = (long long)in1[0] * in2[0];
    /* muls followed by " res1 -= (long long)in1[3] * in2[3];" */
    res1  = (long long)in1[1] * in2[1];
    /* mulsa without mf/mt HI/LO */
    res  += (long long)in1[2] * in2[2];
    /* mulss without mf/mt HI/LO */
    res1 -= (long long)in1[3] * in2[3];
    res  += (long long)in1[4] * in2[4];
    res1 -= (long long)in1[5] * in2[5];
    res  += (long long)in1[6] * in2[6];
    res1 -= (long long)in1[7] * in2[7];

    out[0] = res;
    out[1] = ASR_64(res1, 32);
}
