/*
 * tmulu00.c - Test mulu.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulu\tr" 2 } } */
/* { dg-final { scan-assembler-times "mfhi\tr\[0-9\]*" 2 } } */
/* { dg-final { scan-assembler-times "mflo\tr\[0-9\]*" 1 } } */
/* { dg-final { scan-assembler-not "mult\tr" } } */


#define ASR(val, bits) ((-2 >> 1 == -1) ? \
                 ((unsigned long)(val)) >> (bits) : \
                 ((unsigned long) (val)) / (1 << (bits)))
#define ASR_64(val, bits) ((-2 >> 1 == -1) ? \
                 ((unsigned long long)(val)) >> (bits) : \
                 ((unsigned long long) (val)) / (1 << (bits)))

void t_mulu00(const unsigned long *in1, const unsigned long *in2,
              const unsigned long *in3, unsigned long long *out)
{
    unsigned long long res1;
    unsigned long long res2;
    unsigned long long res3;

    /* mulu/mfhi,mflo */
    res1 = (unsigned long long)in3[0] * in1[0];
    /* mulu/mfhi,mflo */
    res2 = (unsigned long long)in2[1] * in1[1];
    /* mult, res3[63:32] = 0, res3[31:0] = in2[2] * in1[2] */
    res3 = in2[2] * in1[2];

    out[0] = res1;

    out[1] = ASR_64(res2, 32);
    //out[2] = ASR_64(res3, 32);
    out[2] = res3;
}
