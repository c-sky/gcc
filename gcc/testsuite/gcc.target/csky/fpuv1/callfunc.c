/*
 * main.c: hard double float point "|*|" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */
/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction fpv v1.0"  { csky-*-* }  { "-march=*" }  { "-march=ck\[68\]*"  }  }  */
/* { dg-options { -O2 -fno-inline  -mhard-float } } */
/* { dg-final { scan-assembler-times "fabsd\tfr\[0-9\]*, fr\[0-9\]*, r\[0-9\]*"  3 } }*/
#include "math.h"

#define F_TYPE double

  F_TYPE fresult = 0;
  F_TYPE fresult1 = 0;
  F_TYPE fresult2 = 0;
F_TYPE fadd1 = 987.1;
F_TYPE fadd2 = 12345.43;

#define PASS 0
#define FAIL 1

F_TYPE call_func ()
{
  F_TYPE temp;

  temp = fabs(fadd2);
  return temp;
}

void fabsd_test(F_TYPE *fres, F_TYPE fsrc1)
{
  F_TYPE temp;

  temp = fabs(fsrc1);
  temp += call_func ();
  temp = fabs (temp);
  *fres = temp;
}



int main (int argc, char **argv)
{
 fabsd_test(&fresult, fadd1);
 return 0;
}
