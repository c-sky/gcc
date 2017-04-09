/*
 * tmulsws03.c - Test mulsws in loop.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-final { scan-assembler-times "mulsw\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsws\t" 1 } } */
/* { dg-final { scan-assembler-times "mtlo\t" 1 } } */
/* { dg-final { scan-assembler-times "mflo\t" 1 } } */

void t_mulsws03(const short *in1, const long *in2, long *out, int ssize)
{
    int i;
    long res;

    /* mulsw for first HI/LO */
    res = ((unsigned long)(in1[0] * in2[0])) >> 16;

    for (i = 1; i < ssize; i++)
    {
        /* mulsws in loop */
        res -= ((unsigned long)(in1[i] * in2[i])) >> 16;
    }
    /* mflo */
    out[0] = res;
}
