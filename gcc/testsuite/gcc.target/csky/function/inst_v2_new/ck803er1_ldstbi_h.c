/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803e*r1"  }  }  */
/* { dg-options "-O2" } */

void func(short *a,short *b)
{
  int i = 0;
  for(;i<10;i++)
  a[i]=b[i];
}

/* { dg-final { scan-assembler "ldbi\.h" } }*/
/* { dg-final { scan-assembler "stbi\.h" } }*/
