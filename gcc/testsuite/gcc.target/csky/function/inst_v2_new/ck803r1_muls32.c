/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803*r1"  }  }  */
/* { dg-options "-O2" } */

long long func (int a, int b)
{
  return (long long)a * b;
}

/* { dg-final { scan-assembler "mul\.s32" } }*/
