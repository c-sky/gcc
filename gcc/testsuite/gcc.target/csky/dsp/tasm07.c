/*
 * tasm07.c - Test "mulsh/mulshs" in in-line asm for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do assemble } */
/* { dg-options "-mdsp -O2" } */

#define CKCORE_MLH0(lo, x, y) \
asm ("mulsh  %0, %1\n\t"      \
     "mtlo   %0"              \
     :                        \
     : "r" (x), "r" (y)       \
     : "lo");


#define CKCORE_MLHS(lo, x, y) \
asm ("mulshs %0, %1"          \
     :                        \
     : "r" (x), "r" (y)       \
     : "lo");

#define CKCORE_MLHZ(lo)       \
({                            \
   asm ("mflo   %0"           \
        : "=r" (lo));         \
 })


void t_asm_mulsha(short *in1, short *in2, long *out)
{
    long res;

   CKCORE_MLH0 (res, in1[0], in2[0]);

   CKCORE_MLHS (res, in1[1], in2[1]);
   CKCORE_MLHS (res, in1[2], in2[2]);
   CKCORE_MLHS (res, in1[3], in2[3]);

   CKCORE_MLHZ (res);
   out[0] = res;
}
