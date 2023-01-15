/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803er1 -O2" } */

int smax(int a, int b)
{
  return (a > b) ? a : b;
}

/* { dg-final { scan-assembler "max\.s32" } }*/

unsigned int umax(unsigned int a, unsigned int b)
{
  return (a > b) ? a : b;
}

/* { dg-final { scan-assembler "max\.u32" } }*/

int smin(int a, int b)
{
  return (a < b) ? a : b;
}

/* { dg-final { scan-assembler "min\.s32" } }*/

unsigned int umin(unsigned int a, unsigned int b)
{
  return (a < b) ? a : b;
}

/* { dg-final { scan-assembler "min\.u32" } }*/
