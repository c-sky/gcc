/* cross section of shift tests specific for shift-left.
 * This is a counterpart to the fold-vec-shift-left-frwapv test.  */

/* { dg-do compile } */
/* { dg-require-effective-target powerpc_p8vector_ok } */
/* { dg-options "-mpower8-vector -O2" } */

#include <altivec.h>

vector signed long long
testsl_signed_longlong (vector signed long long x, vector unsigned long long y)
{
  return vec_sl (x, y);
}

vector unsigned long long
testsl_unsigned_longlong (vector unsigned long long x, vector unsigned long long y)
{
  return vec_sl (x, y);
}

/* { dg-final { scan-assembler-times "vsld" 2 } } */
