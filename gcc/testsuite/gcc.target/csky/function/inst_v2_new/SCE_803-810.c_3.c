/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803/ck807/ck810"  { csky-*-* }  { "*" }  {"-march=ck803" "-march=ck807" "-march=ck810" }  }  */
/* { dg-options "-O1" } */

unsigned int func(int a,int b,unsigned int x,unsigned int y,unsigned int z)
{
  if (a == b)
    {
      x=~y;
      z=x/y;
    }
  else
    {
      y=x>>y;
      z=x|y;
    }
 return z;
}

/* { dg-final { scan-assembler "sce\t" } }*/
/* { dg-final { scan-assembler "not" } }*/
/* { dg-final { scan-assembler "divu" } }*/
/* { dg-final { scan-assembler "lsr" } }*/
/* { dg-final { scan-assembler "or" } }*/
