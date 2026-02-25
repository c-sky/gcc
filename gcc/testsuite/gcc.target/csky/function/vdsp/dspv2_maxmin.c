/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "" } */

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
