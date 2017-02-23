/* { dg-do compile } */

long long func (long long a)
{
  return a ^ (long long)0xf;
}
/* { dg-final { scan-assembler "xor\[^\n\]*\n\[ |\t\]xor" } } */
