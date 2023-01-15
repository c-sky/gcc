/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803er1 -O2" } */

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
