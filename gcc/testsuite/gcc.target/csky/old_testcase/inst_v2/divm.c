/* { dg-do compile } */
/* { dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=ck801" "-match=ck802" }  { ""}  }  */


int func (int a, int b)
{
  return a / b;
}
/* { dg-final { scan-assembler "div" } } */

unsigned int func2 (unsigned int a, unsigned int b)
{
  return a / b;
}
/* { dg-final { scan-assembler "divu" } } */
