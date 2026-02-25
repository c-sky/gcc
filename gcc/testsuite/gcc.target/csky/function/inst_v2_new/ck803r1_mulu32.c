/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803*r1"  }  }  */
/* { dg-options "-O2" } */

unsigned long long func (unsigned int a, unsigned int b)
{
  return (unsigned long long)a * b;
}

/* { dg-final { scan-assembler "mul\.u32" } }*/
