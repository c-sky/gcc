/*
 * main.c: hard float point "+" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */
/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction fpv v1.0"  { csky-*-* }  { "-march=*" }  { "-march=ck\[68\]*"  }  }  */
/* { dg-options { -O2 -fno-inline  -mhard-float } } */
/* { dg-final { scan-assembler "fnmacs\tfr\[0-9\]*, fr\[0-9\]*, fr\[0-9\]*, r\[0-9\]*"  } }*/


#define F_TYPE float

  F_TYPE fresult = 0;
  F_TYPE fresult1 = 0;
  F_TYPE fresult2 = 0;
F_TYPE fadd1 = 987.1;
F_TYPE fadd2 = 12345.43;

#define PASS 0
#define FAIL 1

static int fmscs_test(
    F_TYPE *fres, F_TYPE fsrc1, F_TYPE fsrc2, F_TYPE fsrc3, F_TYPE fsrc4)
{
  F_TYPE temp;

  temp = fsrc1 * fsrc2;
  temp = -temp;
  temp += fsrc3 * fsrc4;
  *fres = temp;
}


static int fmscs_test1(
    F_TYPE *fres, F_TYPE fsrc1, F_TYPE fsrc2, F_TYPE fsrc3, F_TYPE fsrc4)
{
  F_TYPE temp;

  temp = fsrc1 * fsrc2;
  temp = -temp + fsrc3 * fsrc4;
  *fres = temp;
}


int main (int argc, char **argv)
{
 fmscs_test(&fresult, fadd1, fadd2, fadd1, fadd2);
 fmscs_test1(&fresult, fadd1, fadd2, fadd1, fadd2);
 return 0;
}
