/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*f*"  }  }  */
/* { dg-options "-mhard-float -O2" } */

double
fnmuld (double a, double b)
{
  /* { dg-final { scan-assembler "fnmuld" } } */
  return -(a * b);
}

float
fnmuls (float a, float b)
{
  /* { dg-final { scan-assembler "fnmuls" } } */
  return -(a * b);
}

