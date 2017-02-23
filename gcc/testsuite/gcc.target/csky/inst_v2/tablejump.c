
/* { dg-do compile } */

/* { dg-options "-O0" } */

void func(void)
{
  int a = 0;

  switch (a)
    {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
    }
}

/* { dg-final { scan-assembler "lrw\t\[ral\]\[0-9\]+, .L\[0-9\]+\naddu\t\[ral\]\[0-9\]+, \[ral\]\[0-9\]+, \[ral\]\[0-9\]+jmp\t\[ral\]\[0-9\]+"} } */
