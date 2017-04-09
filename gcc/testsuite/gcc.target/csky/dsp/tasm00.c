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

   CKCORE_ML0 (res.s.high, res.s.low, in1[0], in2[0]);

   CKCORE_MLA (res.s.high, res.s.low, in1[0], in2[0]);
   CKCORE_MLA (res.s.high, res.s.low, in1[1], in2[1]);
   CKCORE_MLA (res.s.high, res.s.low, in1[2], in2[2]);

   CKCORE_MLZ (res.s.high, res.s.low);
   out[0] = res.ll;
}
