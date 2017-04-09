/*
 * tasm04.c - Test "mulsw/mulswa" in in-line asm for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do assemble } */
/* { dg-options "-mdsp -O2" } */

#define CKCORE_MLW0(lo, x, y) \
asm ("mulsw  %0, %1\n\t"      \
     "mtlo   %0"              \
     :                        \
     : "r" (x), "r" (y)       \
     : "lo");


#define CKCORE_MLWA(lo, x, y) \
asm ("mulswa %0, %1"          \
     :                        \
     : "r" (x), "r" (y)       \
     : "lo");

#define CKCORE_MLWZ(lo)       \
({                            \
   asm ("mflo   %0"           \
        : "=r" (lo));         \
 })


void t_asm_mulswa(short *in1, long *in2, long *out)
{
    long res;

   CKCORE_MLW0 (res, in1[0], in2[0]);

   CKCORE_MLWA (res, in1[1], in2[1]);
   CKCORE_MLWA (res, in1[2], in2[2]);
   CKCORE_MLWA (res, in1[3], in2[3]);

   CKCORE_MLWZ (res);
   out[0] = res;
}
