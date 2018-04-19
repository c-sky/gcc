/*
 * tasm02.c - Test "mulus" in in-line asm for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do assemble } */
/* { dg-options "-mdsp -O2" } */

#define CKCORE_UML0(hi, lo, x, y) \
asm ("mulu  %0, %1"               \
     :                            \
     : "r" (x), "r" (y)           \
     : "hi", "lo");


#define CKCORE_UMLS(hi, lo, x, y) \
asm ("mulus %0, %1"               \
     :                            \
     : "r" (x), "r" (y)           \
     : "hi", "lo");

#define CKCORE_UMLZ(hi, lo)       \
({                                \
   asm ("mfhi   %1\n\t"           \
        "mflo   %0"               \
        : "=r" (lo), "=r" (hi));  \
 })

struct DWstruct
{
    unsigned long high;
    unsigned long low;
};

typedef union
{
    struct DWstruct s;
    unsigned long long  ll;
} DWunion;


void t_asm_mulus(
    unsigned long *in1, unsigned long *in2, unsigned long long *out)
{
    DWunion res;

   CKCORE_UML0 (res.s.high, res.s.low, in1[0], in2[0]);

   CKCORE_UMLS (res.s.high, res.s.low, in1[0], in2[0]);
   CKCORE_UMLS (res.s.high, res.s.low, in1[1], in2[1]);
   CKCORE_UMLS (res.s.high, res.s.low, in1[2], in2[2]);

   CKCORE_UMLZ (res.s.high, res.s.low);
   out[0] = res.ll;
}
