/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-march=ck803"  }  }  */
/* { dg-options "-mcpu=ck803eftr1 -O2" } */

void func(char *a,char *b)
{
  int i = 0;
  for(;i<10;i++)
  a[i]=b[i];
}

/* { dg-final { scan-assembler "ldbi\.b" } }*/
/* { dg-final { scan-assembler "stbi\.b" } }*/
