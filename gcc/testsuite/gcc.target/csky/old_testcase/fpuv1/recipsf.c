/*
 * main.c: hard single float point "1 / *" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */
/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction fpv v1.0"  { csky-*-* }  { "-march=*" }  { "-march=ck\[68\]*"  }  }  */
/* { dg-options { -O2 -fno-inline  -mhard-float } } */
/* { dg-final { scan-assembler-times "frecips\tfr\[0-9\]*, fr\[0-9\]*, r\[0-9\]*" 1 } }*/


#define F_TYPE float

  F_TYPE fresult = 0;
  F_TYPE fadd1 = 0.123454;
  F_TYPE fresult2 = 0;

#define PASS 0
#define FAIL 1

int frecips_test1(F_TYPE *fres, F_TYPE fsrc1)
{
  F_TYPE temp;

  temp = 1 / fsrc1;
  *fres = temp * 10.123;
}

int frecips_test2(F_TYPE *fres, F_TYPE fsrc1)
{
  F_TYPE temp;

  temp = 121.0 - fsrc1;
  temp += 111.0 / fsrc1;
  *fres = temp * (float)10.123;
}

int main (int argc, char **argv)
{
 frecips_test1(&fresult, fadd1);
 frecips_test2(&fresult, fadd1);
 return 0;
}
