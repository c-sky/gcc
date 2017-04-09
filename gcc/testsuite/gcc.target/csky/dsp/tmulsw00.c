/*
 * tmulsw00.c - Test mulsw in loop.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */

/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mult\tr" 4 } } */
/* { dg-final { scan-assembler-times "asri\tr\[0-9\]*, 16" 4 } } */
/* { dg-final { scan-assembler-times "mulsw\tr" 2 } } */



void t_mulsw00(const short *ins, const int *in1, const long *in2,
               long *out)
{
    /* mulsw can not be used, mult & asri instead */
    out[0] = (in1[0] * in2[0]) >> 16;
    out[1] = (in1[1] * in2[1]) >> 16;
    /* mulsw can not be used, sexth, mult & asri instead */
    out[2] = ((ins[2] * in2[2])) >> 16;
    out[3] = ((ins[3] * in2[3])) >> 16;
    /* mulsw */
    out[4] = ((unsigned long)(ins[4] * in2[4])) >> 16;
    out[5] = ((unsigned long)(in1[5] * ins[5])) >> 16;
}
