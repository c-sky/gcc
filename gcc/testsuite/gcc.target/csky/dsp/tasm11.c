/*
 * tasm11.c - Test "vmulsw/vmulsws" in in-line asm for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do assemble } */
/* { dg-options "-mdsp -O2" } */

#define CKCORE_VMLW0(hi, lo, x, y) \
asm ("vmulsw  %0, %1"              \
     :                             \
     : "r" (x), "r" (y)            \
     : "hi", "lo");


#define CKCORE_VMLWS(hi, lo, x, y) \
asm ("vmulsws %0, %1"              \
     :                             \
     : "r" (x), "r" (y)            \
     : "hi", "lo");

#define CKCORE_VMLWZ(hi, lo)       \
({                                 \
   asm ("mflo   %0\n\t"            \
        "mfhi   %1"                \
        : "=r" (lo), "=r" (hi));   \
 })


void t_asm_vmulsws(long *in1, long *in2, long *out)
{
    long res1;
    long res2;

   CKCORE_VMLW0 (res1, res2, in1[0], in2[0]);

   CKCORE_VMLWS (res1, res2, in1[1], in2[1]);
   CKCORE_VMLWS (res1, res2, in1[2], in2[2]);
   CKCORE_VMLWS (res1, res2, in1[3], in2[3]);

   CKCORE_VMLWZ (res1, res2);
   out[0] = res1;
   out[1] = res2;
}
