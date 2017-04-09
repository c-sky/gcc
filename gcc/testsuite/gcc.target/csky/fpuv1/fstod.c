/*
 * main.c: hard double float point "|*|" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */

/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction fpv v1.0"  { csky-*-* }  { "-march=*" }  { "-march=ck\[68\]*"  }  }  */
/* { dg-options { -O2 -fno-inline  -mhard-float } } */
/* { dg-final { scan-assembler "fstod\tfr\[0-9\]*, fr\[0-9\]*, r\[0-9\]*"  } }*/
#include "math.h"

  double fresult = 0;
float fadd1 = 987.1;

#define PASS 0
#define FAIL 1

void fstod_test(double *fres, float fsrc1)
{
  double temp;

  temp = (double)fsrc1;
  *fres = temp;
}



int main (int argc, char **argv)
{
 fstod_test(&fresult, fadd1);
 return 0;
}
