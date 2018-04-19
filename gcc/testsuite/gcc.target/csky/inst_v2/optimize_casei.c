
/* { dg-do compile } */

/* { dg-options "-Os -mconstpool" } */

/* { dg-skip-if "Switch case optimize" { csky-*-* } { "*" } { "-march=ck801" "-march=ck802" } }  */

int func(int x, int y)
{
  int a = x + y;

  switch (a)
    {
      case 1:
        a += 1;
        break;
      case 2:
        a += 2;
        break;
      case 3:
        a += 3;
        break;
      case 4:
        a += 4;
        break;
      case 5:
        a += 5;
        break;
    }
    return a;
}

/* { dg-final { scan-assembler "jbsr\t___gnu_csky_case_[us][qh]*i"} } */
