
/* { dg-do compile } */

/* { dg-options "-O2" } */

/* { dg-skip-if "CSKY_ISA_FEATURE(2E3)" { csky-*-* } { "-march=ck801" "-march=ck802" } { "" } }  */

typedef struct bitfield
{
  short eight1: 8;
  short four: 4;
  short eight2: 8;
} bitfield;

int func (bitfield a)
{
  return a.eight2;
}

/* { dg-final { scan-assembler "sext"} } */
