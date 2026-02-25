/*
 * tmulus00.c - Test mulus.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulu\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulus\tr" 6 } } */
/* { dg-final { scan-assembler-times "mult\tr" 1 } } */
/* { dg-final { scan-assembler-times "mfhi\tr" 2 } } */
/* { dg-final { scan-assembler-not "mthi\tr"  } } */
/* { dg-final { scan-assembler-times "mflo\tr" 1 } } */
/* { dg-final { scan-assembler-not "mtlo\tr"  } } */



#define ASR(val, bits) ((-2 >> 1 == -1) ? \
                 ((unsigned long)(val)) >> (bits) : \
                 ((unsigned long) (val)) / (1 << (bits)))
#define ASR_64(val, bits) ((-2 >> 1 == -1) ? \
                 ((unsigned long long)(val)) >> (bits) : \
                 ((unsigned long long) (val)) / (1 << (bits)))

void t_mulus00(
    const unsigned long *in1, const unsigned long *in2, unsigned long *out)
{
    unsigned long long res;

    /* mulu */
    res  = (unsigned long long)in1[0] * in2[0];
    /* mfhi */
    out[0] = ASR_64(res, 32);
    /* mulus */
    res -= (unsigned long long)in1[2] * in2[2];
    res -= (unsigned long long)in1[3] * in2[3];
    res -= (unsigned long long)in1[4] * in2[4];
    res -= (unsigned long long)in1[5] * in2[5];
    res -= (unsigned long long)in1[6] * in2[6];
    res -= (unsigned long long)in1[7] * in2[7];

    /* mult, mfhi/mflo, subc */
    res -= in1[1] * in2[1];

    out[1] = res;
}
