/*
 * main.c: hard float point "+" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */
/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction fpv v1.0"  { csky-*-* }  { "-march=*" }  { "-march=ck\[68\]*"  }  }  */
/* { dg-options { -O2 -fno-inline  -mhard-float } } */
/* { dg-final { scan-assembler "fcmpzned\tfr\[0-9\]*, r\[0-9\]*"  } }*/


#define F_TYPE double

  F_TYPE fresult = 0;
F_TYPE fadd1 = 987.1;
F_TYPE fadd2 = 12345.43;

#define PASS 0
#define FAIL 1

int fcmpzeqd_test1(F_TYPE *fres, F_TYPE fsrc1)
{
  /* == */
  if (fsrc1 == (-0)) 
  { 
    *fres += fsrc1 * fadd1;
  }
}

int fcmpzeqd_test2(F_TYPE *fres, F_TYPE fsrc1)
{
  /* == */
  if (fsrc1 == 0)
  {
    *fres += fsrc1 * fadd1;
    *fres -= (-0.0) * fsrc1;
    *fres -= 0.0 * fsrc1;
  }
}


int main (int argc, char **argv)
{
 fcmpzeqd_test1(&fresult, fadd1);
 fcmpzeqd_test2(&fresult, fadd1);
 return 0;
}
