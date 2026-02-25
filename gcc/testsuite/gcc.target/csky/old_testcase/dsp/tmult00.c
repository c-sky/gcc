/*
 * tmult00.c - Test mult.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mult\tr" 2 } } */
/* { dg-final { scan-assembler-times "asri\tr\[0-9\]*, 31" 1 } } */
#define ASR(val, bits) ((-2 >> 1 == -1) ? \
         ((long)(val)) >> (bits) : ((long) (val)) / (1 << (bits)))
#define ASR_64(val, bits) ((-2 >> 1 == -1) ? \
         ((long long)(val)) >> (bits) : ((long long) (val)) / (1 << (bits)))

void t_mult00(const long *in1, const long *in2, long *out)
{
    long long res;

    /* mult/asri */
    res = in1[0] * in2[0];
    /* mult */
    out[0] = in1[1] * in2[1];

    out[1] = ASR_64(res, 32);
}
