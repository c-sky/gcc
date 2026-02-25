/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803e*r1"  }  }  */
/* { dg-options "-O2" } */

unsigned long long func (unsigned long long a4, unsigned int b2, unsigned int c2)
{
  a4 = a4 + (unsigned long long)b2 * c2;
  return a4;
}

/* { dg-final { scan-assembler "mula\.u32" } }*/
