/*
 * tmulswa04.c - Test mulswa.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsw\tr" 1 } } */
/* { dg-final { scan-assembler-times "mulswa\tr" 7 } } */
/* { dg-final { scan-assembler-not "mfhi\t"  } } */
/* { dg-final { scan-assembler-times "mflo\t" 2 } } */
/* { dg-final { scan-assembler-not "mthi\t"  } } */
/* { dg-final { scan-assembler-times "mtlo\t" 2 } } */


static void t_span_func (void)
{
}


void t_mulswa04(const short *ins1, const short *ins2, const int *in, int *out)
{
    long res;

    /* mulsw */
    res = ((unsigned long)(ins1[0] *  in[0])) >> 16;
    /* mulswa */
    res += ((unsigned long)(ins2[1] * in[1])) >> 16;
    res += ((unsigned long)(ins2[2] * in[2])) >> 16;
    res += ((unsigned long)(ins2[3] * in[3])) >> 16;
    /* mfhi/mflo to save hi/lo reigster in General register */
    t_span_func ();
    /* mthi/mtlo, then mulswa again */
    res += ((unsigned long)(ins2[4] * in[4])) >> 16;
    res += ((unsigned long)(ins2[5] * in[5])) >> 16;
    res += ((unsigned long)(ins2[6] * in[6])) >> 16;
    res += ((unsigned long)(in[7] * ins1[7])) >> 16;

    /* mflo */
    out[0] = res;
}
