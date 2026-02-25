/* { dg-do compile } */
/* { dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803*r1"  }  }  */
/* { dg-options "-O2" } */

int func (int a, short *b, short *c)
{
  a += *b * *c;
  return a;
}

/* { dg-final { scan-assembler "mulall\.s16\.s" } }*/
