/*
 * tmulsa00.c - Test mulsa for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "\tmuls\tr\[0-9\]*, r\[0-9\]*\n\[^\n\]*\tmfhi\tr\[0-9\]*" 1 } } */
/* { dg-final { scan-assembler-times "\tmulsa\tr\[0-9\]*, r\[0-9\]*" 6 } } */
/* { dg-final { scan-assembler-times "\tmult\tr\[0-9\]*, r\[0-9\]*" 1 } } */

#define int32_t long

#define ASR(val, bits) ((-2 >> 1 == -1) ? \
      ((int32_t)(val)) >> (bits) : ((int32_t) (val)) / (1 << (bits)))
#define ASR_64(val, bits) ((-2 >> 1 == -1) ? \
      ((long long)(val)) >> (bits) : ((long long) (val)) / (1 << (bits)))

void t_mulsa00(const int32_t *in1, const int32_t *in2, long long *out)
{
    long long res;

    /* muls & mfhi */
    res = (long long)in1[0] * in2[0];
    out[0] = ASR_64(res, 32);
    /* mulsa */
    res += (long long)in1[2] * in2[2];
    res += (long long)in1[3] * in2[3];
    res += (long long)in1[4] * in2[4];
    res += (long long)in1[5] * in2[5];
    res += (long long)in1[6] * in2[6];
    res += (long long)in1[7] * in2[7];
    /* mult, mfhi/mflo, addc */
    res += in1[1] * in2[1];
    out[1] = res;
}
