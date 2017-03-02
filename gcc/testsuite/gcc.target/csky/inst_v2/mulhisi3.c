
/* { dg-do compile } */

/* { dg-options "-O2" } */

/* { dg-skip-if "CSKY_ISA_FEATURE(2E3)" { csky-*-* } { "-march=ck801" "-march=ck802" } { "" } }  */

int func(short a, short b)
{
  return a * b;
}

/* { dg-final { scan-assembler "mulsh"} } */
