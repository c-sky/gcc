/* { dg-do compile } */

int func (int a)
{
  return a ^ (0xf);
}
/* { dg-final { scan-assembler "movi\[^\n\]*\n\[ |\t\]xor" } } */


int func2 (int a)
{
  return a ^ (0xffffff);
}
/* { dg-final { scan-assembler "lrw\[^\n\]*\n\[ |\t\]xor" } } */
