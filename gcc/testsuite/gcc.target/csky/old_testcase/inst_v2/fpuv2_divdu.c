/* { dg-do compile } */

/* { dg-skip-if "Signle precison float instructions." { csky-*-* } { "*"} { "-march=ck807" "-march=ck810"} }  */

/* { dg-options "-mhard-float -O2 -mfdivdu" } */

double func13 (double a, double b)
{
  return (a / b);
}
/* { dg-final { scan-assembler "fdivd" } } */

double func14 (double a)
{
  return ((double)1.0 / a);
}
/* { dg-final { scan-assembler "frecipd" } } */
