/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803er1 -O2" } */

unsigned int addhu (unsigned int a, unsigned int b)
{
  return (a+b)/2;
}

/* { dg-final { scan-assembler "addh\.u32" } }*/

unsigned int subhu (unsigned int a, unsigned int b)
{
  return (a-b)/2;
}

/* { dg-final { scan-assembler "subh\.u32" } }*/
