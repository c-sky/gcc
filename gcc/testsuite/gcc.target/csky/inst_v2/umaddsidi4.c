
/* { dg-do compile } */

/* { dg-options "-O2" } */

/* { dg-skip-if "CSKY_ISA_FEATURE(dsp)" { csky-*-* } { "*" } { "-mdsp" } }  */

unsigned long long func(unsigned int a, unsigned int b)
{
  unsigned long long c = a * b;
  return (unsigned long long)a * b + c;
}

/* { dg-final { scan-assembler "mulua"} } */
