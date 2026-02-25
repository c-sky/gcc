/*
 * main.c: hard float point "+" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */

#define F_TYPE double

  F_TYPE fresult = 0;
  F_TYPE fresult1 = 0;
  F_TYPE fresult2 = 0;
F_TYPE fadd1 = 987.1;
F_TYPE fadd2 = 12345.43;

#define PASS 0
#define FAIL 1

static int fnmscd_test1(
    F_TYPE *fres, F_TYPE fsrc1, F_TYPE fsrc2, F_TYPE fsrc3, F_TYPE fsrc4)
{
  F_TYPE temp;

  temp = fsrc1 * fsrc2;
  temp = -temp;
  temp -= fsrc3 * fsrc4;
  *fres = temp;
}


static int fnmscd_test2(
    F_TYPE *fres, F_TYPE fsrc1, F_TYPE fsrc2, F_TYPE fsrc3, F_TYPE fsrc4)
{
  F_TYPE temp;

  temp = fsrc1 * fsrc2;
  temp = -temp - fsrc3 * fsrc4;
  *fres = temp;
}

static int fnmscd_test3(
    F_TYPE *fres, F_TYPE fsrc1, F_TYPE fsrc2, F_TYPE fsrc3, F_TYPE fsrc4)
{
  *fres = -*fres - fsrc3 * fsrc4;
}

int main (int argc, char **argv)
{
 fnmscd_test1(&fresult, fadd1, fadd2, fadd1, fadd2);
 fnmscd_test2(&fresult, fadd1, fadd2, fadd1, fadd2);
 fnmscd_test3(&fresult, fadd1, fadd2, fadd1, fadd2);
 return 0;
}
