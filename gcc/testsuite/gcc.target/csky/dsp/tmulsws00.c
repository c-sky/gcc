/*
 * tmulsws00.c - Test mulsws.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsw\t" 1 } } */
/* { dg-final { scan-assembler-times "\tmult\tr\[0-9\]*, r\[0-9\]*\n\[^\n\]*\tasri\tr\[0-9\]*, 16\n\[^\n\]*\tmflo\tr\[0-9\]*" 2 } } */
/* { dg-final { scan-assembler-not "mfhi\t"  } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */
/* { dg-final { scan-assembler-times "mtlo\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsws\t" 5 } } */


void t_mulsws00(const short *ins1, const short *ins2, const int *in, int *out)
{
    long res;

    /* mulsw */
    res = ((unsigned long)(ins1[0] *  in[0])) >> 16;
    /* mulsws can not be used. sexth/mult/asri/mflo/subu/mtloi, instead */
    res -= (ins2[1] * in[1]) >> 16;
    res -= (ins1[2] * in[2]) >> 16;
    /* mulsws */
    res -= ((unsigned long)(ins2[3] * in[3])) >> 16;
    res -= ((unsigned long)(ins2[4] * in[4])) >> 16;
    res -= ((unsigned long)(ins2[5] * in[5])) >> 16;
    res -= ((unsigned long)(ins2[6] * in[6])) >> 16;
    res -= ((unsigned long)(in[7] * ins1[7])) >> 16;

    /* mflo */
    out[0] = res;
}
