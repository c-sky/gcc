/*
 * tasm00.c - Test "muls/mulsa" in in-line asm for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do assemble } */
/* { dg-options "-mdsp -O2" } */

#define CKCORE_ML0(hi, lo, x, y) \
asm ("muls  %2, %3"              \
     : "=h" (hi), "=l" (lo)      \
     : "r" (x), "r" (y));


#define CKCORE_MLA(hi, lo, x, y) \
asm ("mulsa %2, %3"              \
     : "+h" (hi), "+l" (lo)      \
     : "r" (x), "r" (y));

#define CKCORE_MLZ(hi, lo)       \
({                               \
   asm ("mflo   %1\n\t"          \
        "mfhi   %0"              \
        : "=r" (hi), "=r" (lo)); \
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
    long res1, res2;

   CKCORE_ML0 (res1, res2, in1[0], in2[0]);

   CKCORE_MLA (res1, res2, in1[0], in2[0]);
   CKCORE_MLA (res1, res2, in1[1], in2[1]);
   CKCORE_MLA (res1, res2, in1[2], in2[2]);

   CKCORE_MLZ (res1, res2);

   res.s.high = res1;
   res.s.low = res2;
   out[0] = res.ll;
}
