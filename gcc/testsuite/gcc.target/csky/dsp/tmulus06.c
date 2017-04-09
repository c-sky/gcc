/*
 * tmulus06.c - Test to compile hi/lo register spanning a function.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulu\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulus\tr" 6 } } */
/* { dg-final { scan-assembler-times "mfhi\t" 2 } } */
/* { dg-final { scan-assembler-times "mflo\t" 2 } } */
/* { dg-final { scan-assembler-times "mthi\t" 1 } } */
/* { dg-final { scan-assembler-times "mtlo\t" 1 } } */


static void t_span_func (void)
{
}

void t_mulus06(unsigned long *in1, unsigned long *in2, unsigned long long *out)
{
    unsigned long long res;

    /* mulu */
    res  = (unsigned long long)in1[0] * in2[0];
    /* mulus */
    res -= (unsigned long long)in1[2] * in2[2];
    res -= (unsigned long long)in1[3] * in2[3];
    res -= (unsigned long long)in1[4] * in2[4];
    /* mfhi/mflo to save hi/lo reigster in General register */
    t_span_func ();
    /* mthi/mtlo, then mulus again */
    res -= (unsigned long long)in1[5] * in2[5];
    res -= (unsigned long long)in1[6] * in2[6];
    res -= (unsigned long long)in1[7] * in2[7];

    out[0] = res;
}
