/* { dg-do compile } */
/* { dg-csky-options "-mcpu=ck803efr1 -O2" } */

void
func (int *a, int *b)
{
  int i = 0;
  for (; i < 10; i++)
    a[i] = b[i];
}

/* { dg-final { scan-assembler "ldbi\.w" } }*/
/* { dg-final { scan-assembler "stbi\.w" } }*/
