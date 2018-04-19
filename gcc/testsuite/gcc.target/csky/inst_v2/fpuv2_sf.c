/* { dg-do compile } */

/* { dg-skip-if "Signle precison float instructions." { csky-*-* } { "*"} { "-march=ck807" "-march=ck810" "-march=ck803s" } }  */

/* { dg-options "-mhard-float -O2" } */

float test_addsf (float a, float b)
{
  return (a + b);
}
/* { dg-final { scan-assembler "fadds" } } */

float test_subsf (float a, float b)
{
  return (a - b);
}
/* { dg-final { scan-assembler "fsubs" } } */

float test_multsf (float a, float b)
{
  return (a * b);
}
/* { dg-final { scan-assembler "fmuls" } } */

float test_numlsf (float a, float b)
{
  return (-a * b);
}
/* { dg-final { scan-assembler "fnmuls" } } */

float test_divsf (float a, float b)
{
  return (a / b);
}
/* { dg-final { scan-assembler "fdivs" } } */

float test_frecips (float a)
{
  return ((float)1.0 / a);
}
/* { dg-final { scan-assembler "frecips" } } */

float test_macs (float a, float b, float c)
{
  return (a + b * c);
}
/* { dg-final { scan-assembler "fmacs" } } */

float test_nmacs (float a, float b, float c)
{
  return (a - b * c);
}
/* { dg-final { scan-assembler "fnmacs" } } */

float test_mscs (float a, float b, float c)
{
  return (a * b - c);
}
/* { dg-final { scan-assembler "fmscs" } } */

float test_nmscs (float a, float b, float c)
{
  return -(a + b * c);
}
/* { dg-final { scan-assembler "fnmscs" } } */

float test_cmpnesf (float a, float b)
{
  return (a != b ? a : b);
}
/* { dg-final { scan-assembler "fcmpnes" } } */

float test_cmpgtsf (float a, float b)
{
  return (a > b ? a : b);
}
/* { dg-final { scan-assembler "fcmplts" } } */

float test_cmpgesf (float a, float b)
{
  return (a >= b ? a : b);
}
/* { dg-final { scan-assembler "fcmphss" } } */

float test_cmpzgesf (float a, float b)
{
  return (a >= (float)0.0 ? a : b);
}
/* { dg-final { scan-assembler "fcmpzhss" } } */

float test_cmpznesf (float a, float b)
{
  return (a != (float)0.0 ? a : b);
}
/* { dg-final { scan-assembler "fcmpznes" } } */

float test_si2sf (int a)
{
  return a;
}
/* { dg-final { scan-assembler "fsitos" } } */

float test_usi2sf (unsigned int a)
{
  return a;
}
/* { dg-final { scan-assembler "fuitos" } } */

int test_sf2si (float a)
{
  return a;
}
/* { dg-final { scan-assembler "fstosi.rz" } } */

unsigned int test_sf2usi (float a)
{
  return a;
}
/* { dg-final { scan-assembler "fstoui.rz" } } */

int test_cstoresf (float a, float b)
{
  return a > b;
}
/* { dg-final { scan-assembler "mvc" } } */
