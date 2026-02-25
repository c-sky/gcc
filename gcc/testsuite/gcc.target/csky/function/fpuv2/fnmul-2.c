/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*f*"  }  }  */
/* { dg-options "-mhard-float -O2 -frounding-math" } */

double
fnmuld (double a, double b)
{
  /* { dg-final { scan-assembler "fnegd" } } */
  /* { dg-final { scan-assembler "fmuld" } } */
  return -a * b;
}

float
fnmuls (float a, float b)
{
  /* { dg-final { scan-assembler "fnegs" } } */
  /* { dg-final { scan-assembler "fmuls" } } */
  return -a * b;
}

