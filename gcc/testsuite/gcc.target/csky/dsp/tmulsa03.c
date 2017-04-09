/*
 * tmulsa03.c - Test mulsa in parellel.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "muls\t" 2 } } */
/* { dg-final { scan-assembler-times "mulsa\t" 6 } } */
/* { dg-final { scan-assembler-times "mfhi\t" 2 } } */
/* { dg-final { scan-assembler-times "mflo\t" 2 } } */


/* 
 * Can same to  t_mulsa04 ?
 */
void t_mulsa03(long *in1, long *in2, long long *out)
{
    long long res;
    long long res1;

    /* muls followed by "res  += (long long)in1[2] * in2[2];" */
    res   = (long long)in1[0] * in2[0];
    /* muls followed by " res1 += (long long)in1[3] * in2[3];" */
    res1  = (long long)in1[1] * in2[1];
    /* mulsa without mf/mt HI/LO */
    res  += (long long)in1[2] * in2[2];
    /* mulsa without mf/mt HI/LO */
    res1 += (long long)in1[3] * in2[3];
    res  += (long long)in1[4] * in2[4];
    res1 += (long long)in1[5] * in2[5];
    res  += (long long)in1[6] * in2[6];
    res1 += (long long)in1[7] * in2[7];

    out[0] = res;
    out[1] = res1;
}
