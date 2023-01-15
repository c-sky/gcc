/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803r2 -O2 -fno-unroll-loops" } */

unsigned int
foo (unsigned int l, int *a)
{
  unsigned int i;
  for(i = 0;i < l; i++)
    a[i] = i;
  return l;
}

/* { dg-final { scan-assembler "bnezad" } } */
