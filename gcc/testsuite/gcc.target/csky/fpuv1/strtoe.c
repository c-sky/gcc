/*
 * main.c: hard float point "+" testing for FPU V1.0
 *
 * Copyright (C) 2009 Hangzhou C-SKY Microsystems co,. ltd.
 *
 */

/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction fpv v1.0"  { csky-*-* }  { "-march=*" }  { "-march=ck\[68\]*"  }  }  */
/* { dg-options { -O2 -fno-inline  -mhard-float } } */
/* { dg-final { scan-assembler "fdtos\tfr\[0-9\]*, fr\[0-9\]*, r\[0-9\]*"  } }*/
/* { dg-final { scan-assembler "fstod\tfr\[0-9\]*, fr\[0-9\]*, r\[0-9\]*"  } }*/

#include "math.h"

#define F_TYPE float

  F_TYPE fresult = 0;
F_TYPE fadd1 = 987.1;

#define PASS 0
#define FAIL 1

typedef long double __fpmax_t;

extern __fpmax_t __strtofpmax(const char *str, char **endptr, int exp_adjust);
extern void __fp_range_check(__fpmax_t y, __fpmax_t x);

F_TYPE strtof(const char *str, char **endptr )
{
        long double x;
        F_TYPE y;

        x = __strtofpmax(str, endptr, 0 );
        y = (F_TYPE) x;

        __fp_range_check(y, x);

        return y;

}

const char  startstr[] = "123445.213";
char **endptr = (char**) &startstr;

int main (int argc, char **argv)
{
 fresult = strtof(startstr, endptr);
 return 0;
}

