/*
 * main.c: hard double float point "1 / *" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */
/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction fpv v1.0"  { csky-*-* }  { "-march=*" }  { "-march=ck\[68\]*"  }  }  */
/* { dg-options { -O2 -fno-inline  -mhard-float } } */
/* { dg-final { scan-assembler-times "frecipd\tfr\[0-9\]*, fr\[0-9\]*, r\[0-9\]*" 2 } }*/

#define F_TYPE double

  F_TYPE fresult = 0;
  F_TYPE fadd1 = 0.123454;
  F_TYPE fresult2 = 0;

#define PASS 0
#define FAIL 1

static int frecipdf_test1(F_TYPE *fres, F_TYPE fsrc1)
{
  F_TYPE temp;

  temp = 1 / fsrc1;
  *fres = temp;
}

static int frecipdf_test2(F_TYPE *fres, F_TYPE fsrc1)
{
  F_TYPE temp;

  temp = 1 - fsrc1;
  *fres = temp;
  *fres += 1 / fsrc1;
}


int main (int argc, char **argv)
{
 frecipdf_test1(&fresult, fadd1);
 frecipdf_test2(&fresult, fadd1);
 return 0;
}
