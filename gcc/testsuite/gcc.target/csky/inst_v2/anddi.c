/* { dg-do compile } */

long long func (long long a)
{
  return a & (long long)(0xff3);
}
/* { dg-final { scan-assembler "\[ |\t\]and\[^\n\]*\n\[ |\t\]and" } } */
