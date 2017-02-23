/* { dg-do compile } */

long long func (long long a)
{
  return a | (long long)0x33;
}
/* { dg-final { scan-assembler "or\[^\n\]*\n\[ |\t\]or" } } */
