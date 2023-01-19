/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803efr1 -O2" } */

void
func (unsigned int *a, unsigned short *b)
{
  int i = 0;
  for (; i < 10; i++)
    a[i] = b[i];
}

/* { dg-final { scan-assembler "ldbi\.h" } }*/
