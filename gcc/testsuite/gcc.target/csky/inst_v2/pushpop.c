/* { dg-do compile } */
/* { dg-options "-O2" } */

extern void func1 (int a, int b, int c, int d);
extern void func2 (int *);

int func (int a, int b, int c, int d)
{
  int e,f,h,i;
  int j[0x8000];
  func1 (e,f,h,i);
  func2 (j);
  return 0;
}
/* { dg-final { scan-assembler "push\tl0, lr" } } */
/* { dg-final { scan-assembler "pop\tl0, lr" } } */
