
/* { dg-do compile } */

/* { dg-options "-O2" } */

/* { dg-skip-if "CSKY_ISA_FEATURE(dsp)" { csky-*-* } { "*" } { "-mdsp" } }  */

long long func(int a, int b)
{
  long long c = a * b;
  return (long long)a * b + c;
}

/* { dg-final { scan-assembler "mulsa"} } */
