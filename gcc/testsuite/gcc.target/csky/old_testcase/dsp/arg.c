/*
 * tmuls00.c - Test mulss for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-std=c99" } */
/* { dg-final { scan-assembler-not "muls\t" } }*/
/* { dg-final { scan-assembler-not "mfhi\t" } }*/
/* { dg-final { scan-assembler-not "mflo\t" } }*/

#define int32_t long

#define ASR(val, bits) ((-2 >> 1 == -1) ? \
         ((int32_t)(val)) >> (bits) : ((int32_t) (val)) / (1 << (bits)))
#define ASR_64(val, bits) ((-2 >> 1 == -1) ? \
         ((long long)(val)) >> (bits) : ((long long) (val)) / (1 << (bits)))


int t_muls00(const int32_t *in1, const int32_t *in2,
             long long *out1, int32_t *out2)
{
    long long res1;
    long long res2;
    long long res3;

    /* muls, mfhi/mflo */
    res1 = (long long)in1[0] * in2[0];
    res2 = (long long)in1[1] * in2[1];

    /* mult */
    res3 = in1[2] * in2[2];

    out1[0] = res1;
    out2[1] = ASR_64(res2, 32);
    out2[2] = ASR_64(res3, 32);

    return 0;
}
