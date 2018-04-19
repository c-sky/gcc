/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "-O2" } */

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
