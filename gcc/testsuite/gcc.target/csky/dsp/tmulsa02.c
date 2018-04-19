/*
 * tmulsa02.c - Test mulsa for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsa\t" 3 } } */


#define int32_t long

#define ASR(val, bits) ((-2 >> 1 == -1) ? \
      ((int32_t)(val)) >> (bits) : ((int32_t) (val)) / (1 << (bits)))
#define ASR_64(val, bits) ((-2 >> 1 == -1) ? \
      ((long long)(val)) >> (bits) : ((long long) (val)) / (1 << (bits)))

void t_mulsa02(const int32_t *in1, const int32_t *in2, long long *out)
{
    long long res;
    long long temp;

    /* muls & mfhi */
    res = (long long)in1[0] * in2[0];
    /* mulsa part1, combined with res += temp */
    temp = (long long)in1[2] * in2[2];
     /* Something like assignment. */
    out[0] = in2[0];
    out[1] = in2[1];
    /* mulss part2 */
    res += temp;
    res += (long long)in1[3] * in2[3];
    res += (long long)in1[4] * in2[4];

    out[2] = res;
}
