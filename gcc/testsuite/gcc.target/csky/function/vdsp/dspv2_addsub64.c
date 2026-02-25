/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "" } */

long long add64 (long long a, long long b)
{
  return a + b;
}

/* { dg-final { scan-assembler "add\.64" } }*/

long long sub64 (long long a, long long b)
{
  return a - b;
}

/* { dg-final { scan-assembler "sub\.64" } }*/
