/* { dg-do compile } */

/* { dg-skip-if "Signle precison float instructions." { csky-*-* } { "*"} { "-march=ck807" "-march=ck810"} }  */

/* { dg-options "-mhard-float -O2" } */

double test_adddf (double a, double b)
{
  return (a + b);
}
/* { dg-final { scan-assembler "faddd" } } */

double test_subdf (double a, double b)
{
  return (a - b);
}
/* { dg-final { scan-assembler "fsubd" } } */

double test_multdf (double a, double b)
{
  return (a * b);
}
/* { dg-final { scan-assembler "fmuld" } } */

double test_numuld (double a, double b)
{
  return (-a * b);
}
/* { dg-final { scan-assembler "fnmuld" } } */

double test_numuld2 (double a, double b)
{
  return -(a * b);
}
/* { dg-final { scan-assembler "fnmuld" } } */

double test_fmacd (double a, double b, double c)
{
  return (a * b + c);
}
/* { dg-final { scan-assembler "fmacd" } } */

double test_fnmacd (double a, double b, double c)
{
  return (a - b * c);
}
/* { dg-final { scan-assembler "fnmacd" } } */

double test_fmscd (double a, double b, double c)
{
  return (a * b - c);
}
/* { dg-final { scan-assembler "fmscd" } } */

double test_fnmscd (double a, double b, double c)
{
  return -(a * b + c);
}
/* { dg-final { scan-assembler "fnmscd" } } */

double test_cmpnedf (double a, double b)
{
  return (a != b ? a : b);
}
/* { dg-final { scan-assembler "fcmpned" } } */

double test_cmpgtdf (double a, double b)
{
  return (a > b ? a : b);
}
/* { dg-final { scan-assembler "fcmpltd" } } */

double test_cmpgedf (double a, double b)
{
  return (a >= b ? a : b);
}
/* { dg-final { scan-assembler "fcmphsd" } } */

double test_cmpzgedf (double a, double b)
{
  return (a >= (double)0.0 ? a : b);
}
/* { dg-final { scan-assembler "fcmpzhsd" } } */

double test_cmpznedf (double a, double b)
{
  return (a != (double)0.0 ? a : b);
}
/* { dg-final { scan-assembler "fcmpzned" } } */

double test_si2df (int a)
{
  return a;
}
/* { dg-final { scan-assembler "fsitod" } } */

double test_usi2df (unsigned int a)
{
  return a;
}
/* { dg-final { scan-assembler "fuitod" } } */

int test_sf2si (double a)
{
  return a;
}
/* fdtosi.rz*/

unsigned int test_df2usi (double a)
{
  return a;
}
/* fdtoui.rz*/

double test_sf2df (float a)
{
  return a;
}
/* { dg-final { scan-assembler "fstod" } } */

float test_df2sf (double a)
{
  return a;
}
/* { dg-final { scan-assembler "fdtos" } } */

int test_cstoredf (double a, double b)
{
  return a > b;
}
/* { dg-final { scan-assembler "mvc" } } */
