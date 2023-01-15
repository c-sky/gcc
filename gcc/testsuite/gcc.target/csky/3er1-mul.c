/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803fr1 -O2" } */

long long mul(int b, int c)
{
  return (long long)b * (long long)c;
}

unsigned long long mulu(unsigned int b, unsigned int c)
{
  return (unsigned long long)b * (unsigned long long)c;
}

/* { dg-final { scan-assembler "mul.s32" } } */
/* { dg-final { scan-assembler "mul.u32" } } */