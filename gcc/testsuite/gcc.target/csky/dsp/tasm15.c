/*
 * tasm00.c - Test "muls/mulsa" in in-line asm for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do assemble } */
/* { dg-options "-mdsp -O2" } */

#define CKCORE_ML0(hi, lo, x, y) \
asm ("muls  %0, %1"              \
     :                           \
     : "r" (x), "r" (y)          \
     : "hi", "lo");


#define CKCORE_MLA(hi, lo, x, y) \
asm ("mulsa %0, %1"              \
     :                           \
     : "r" (x), "r" (y)          \
     : "hi", "lo");

#define CKCORE_MLZ(hi, lo)       \
({                               \
   asm ("mfhi   %1\n\t"          \
        "mflo   %0"              \
        : "=r" (lo), "=r" (hi)); \
 })

struct DWstruct
{
    long high;
    long low;
};

typedef union
{
    struct DWstruct s;
    long long  ll;
} DWunion;


void t_asm_mulsa(long *in1, long *in2, long long *out)
{
    DWunion res;
    long long res1;
    long temp1;
    long temp2;

    res1 = (long long)in1[0] * in2[0];
    CKCORE_ML0 (temp1, temp2, in1[0], in2[0]);
    res1 += (long long)in1[2] * in2[2];
    CKCORE_MLA (temp1, temp2, in1[0], in2[0]);
    res1 += (long long)in1[5] * in2[5];
    CKCORE_MLA (temp1, temp2, in1[1], in2[1]);
    res1 += (long long)in1[6] * in2[6];
    CKCORE_MLA (temp1, temp2, in1[2], in2[2]);
    res1 += (long long)in1[7] * in2[7];

    CKCORE_MLZ (temp1, temp2);
    res.s.high = temp1;
    res.s.low = temp2;
    out[0] = res.ll;
    out[1] = res1;
}
