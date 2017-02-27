
/* { dg-do compile } */

/* { dg-options "-O2" } */

/* { dg-skip-if "CSKY_ISA_FEATURE(dsp)" { csky-*-* } { "*" } { "-mdsp" } }  */

unsigned long long func(unsigned int a, unsigned int b)
{
  return (unsigned long long)a * b;
}

/* { dg-final { scan-assembler "mulu"} } */
