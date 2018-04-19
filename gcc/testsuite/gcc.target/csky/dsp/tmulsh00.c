/*
 * tmulsh00.c - Test mulsh for compiler.
 *
 * Copyright (C): 2009 Hangzhou C-SKY Microsystem Co.,LTD.
 */
/* { dg-do compile } */
/* { dg-options "-mdsp -O2" } */
/* { dg-final { scan-assembler-times "mulsh\t" 3 } } */

#define MUL(dst, a, b)   { dst =  (long)a * b; }


void t_mulsh00(const short in1[3], const short in2[3], long out[3])
{
   /* mulsh */
   MUL(out[0],  in1[0], in2[0]);
   MUL(out[1],  in1[1], in2[1]);
   MUL(out[2],  in1[2], in2[2]);
}
