/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803e*r1"  }  }  */
/* { dg-options "-O2" } */

int func (int a, int b, int c)
{
  return a + b * c;
}

/* { dg-final { scan-assembler "mula\.32\.l" } }*/
