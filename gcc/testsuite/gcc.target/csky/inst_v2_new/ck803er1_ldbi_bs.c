/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803e*r1"  }  }  */
/* { dg-options "-O2" } */

void func1(int *a,signed char *b)
{
  int i = 0;
  for(;i<10;i++)
  a[i]=b[i];
}

int func2(signed char *a)
{
  return a[5];
}

/* { dg-final { scan-assembler "ldbi\.bs" } }*/
/* { dg-final { scan-assembler "ld\.bs" } }*/
