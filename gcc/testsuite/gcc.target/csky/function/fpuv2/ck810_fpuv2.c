/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*f*"  }  }  */
/* { dg-options "-O2 -mhard-float" } */

float fadd (float a, float b)
{
  return a + b;
}

/* { dg-final { scan-assembler "fadds" } }*/

double dadd (double a, double b)
{
  return a + b;
}

/* { dg-final { scan-assembler "faddd" } }*/

float fsub (float a, float b)
{
  return a - b;
}

/* { dg-final { scan-assembler "fsubs" } }*/

double dsub (double a, double b)
{
  return a - b;
}

/* { dg-final { scan-assembler "fsubd" } }*/

float fmul (float a, float b)
{
  return a * b;
}

/* { dg-final { scan-assembler "fmuls" } }*/

double dmul (double a, double b)
{
  return a * b;
}

/* { dg-final { scan-assembler "fmuld" } }*/
