/*
 * main.c: hard float point "+" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */

#define F_TYPE double

  F_TYPE fresult = 0;
F_TYPE fadd1 = 987.1;
F_TYPE fadd2 = 12345.43;

#define PASS 0
#define FAIL 1

int fcmpled_test(F_TYPE *fres, F_TYPE fsrc1, F_TYPE fsrc2)
{
  /* <= */
  if (fsrc1 <= fsrc2)
  {
    *fres = fsrc1 / fsrc2;
  }
}



int main (int argc, char **argv)
{
 fcmpled_test(&fresult, fadd1, fadd2);
 return 0;
}
