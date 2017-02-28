/* { dg-do compile } */

int func (int a)
{
  return a | 0x3;
}
/* { dg-final { scan-assembler "bseti\[^\n\]*\n\[ |\t\]bseti" } } */

int func2 (int a)
{
  return a | 0x100000;
}
/* { dg-final { scan-assembler "bseti" } } */

int func3 (int a)
{
  return a | 0x300000;
}
/* { dg-final { scan-assembler "bseti\[^\n\]*\n\[ |\t\]bseti" } } */

int func4 (int a)
{
  return a | 0x700000;
}
/* { dg-final { scan-assembler "movi\[^\n\]*\n\[ |\t\]lsli\[^\n\]*\n\[|\t\]or" } } */
