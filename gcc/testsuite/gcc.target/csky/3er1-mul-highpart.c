/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803r1 -O2" } */

int mul_h(int b, int c)
{
  long long a = (long long)b * (long long)c;
  return (int)((a & 0xffffffff00000000ULL) >> 32);
}

/* { dg-final { scan-assembler "mul.s32.h" } } */
