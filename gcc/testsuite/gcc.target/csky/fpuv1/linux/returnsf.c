/*
 * main.c: hard float point "+" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */
/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction fpv v1.0"  { csky-*-* }  { "-march=*" }  { "-march=ck\[68\]*"  }  }  */
/* { dg-options { -O2 -fno-inline  -mhard-float } } */
/* { dg-final { scan-assembler "bclri\tr2, 31"  } }*/

#include "math.h"

#define F_TYPE float

  F_TYPE fresult = 0;
F_TYPE fadd1 = 987.1;

#define PASS 0
#define FAIL 1

F_TYPE fabss_test(F_TYPE fsrc1)
{
  F_TYPE temp;

  temp = fabsf(fsrc1);

  return temp;
}



int main (int argc, char **argv)
{
 fresult = fabss_test(fadd1);
 return 0;
}
