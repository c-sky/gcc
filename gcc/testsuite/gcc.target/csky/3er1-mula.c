/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803r1 -O2" } */

long long mula(long long a, int b, int c)
{
  return a + (long long)b * (long long)c;
}

unsigned long long mula_u(unsigned long long a, unsigned int b, unsigned int c)
{
  return a + (unsigned long long)b * (unsigned long long)c;
}

/* { dg-final { scan-assembler "mula.s32" } } */
/* { dg-final { scan-assembler "mula.u32" } } */