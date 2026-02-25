/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803e*r1"  }  }  */
/* { dg-options "-O2" } */

long long func (long long a4, int b2, int c2)
{
  a4 = a4 + (long long)b2 * c2;
  return a4;
}

/* { dg-final { scan-assembler "mula\.s32" } }*/
