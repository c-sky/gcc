/*
 * tmulshs04.c - Test to compile hi/lo register spanning a function.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\t" 1 } } */
/* { dg-final { scan-assembler-times "mulshs\t" 6 } } */
/* { dg-final { scan-assembler-times "mflo\t" 2 } } */
/* { dg-final { scan-assembler-times "mtlo\t" 2 } } */



static void t_span_func (void)
{
}

void t_mulshs04(short *in1, short *in2, long *out)
{
    long res;

    /* mulsh */
    res  = (long)in1[0] * in2[0];
    /* mulshs */
    res -= (long)in1[2] * in2[2];
    res -= (long)in1[3] * in2[3];
    res -= (long)in1[4] * in2[4];
    /* mfhi/mflo to save hi/lo reigster in General register */
    t_span_func ();
    /* mthi/mtlo, then mulshs again */
    res -= (long)in1[5] * in2[5];
    res -= (long)in1[6] * in2[6];
    res -= (long)in1[7] * in2[7];

    out[0] = res;
}
