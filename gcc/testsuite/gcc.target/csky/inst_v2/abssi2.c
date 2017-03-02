
/* { dg-do compile } */

/* { dg-skip-if "CSKY_ISA_FEATURE(2E3)" { csky-*-* } { "-march=ck801" "-march=ck802" } { "" } }  */

int func(int a)
{
  return abs(a);
}

/* { dg-final { scan-assembler "abs"} } */
