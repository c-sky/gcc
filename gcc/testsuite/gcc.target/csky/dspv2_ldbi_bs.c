/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803efr1 -O2" } */

void
func1 (int *a, signed char *b)
{
  int i = 0;
  for (; i < 10; i++)
    a[i] = b[i];
}

int
func2 (signed char *a)
{
  return a[5];
}

/* { dg-final { scan-assembler "ldbi\.bs" } }*/
/* { dg-final { scan-assembler "ld\.bs" } }*/
