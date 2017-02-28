/* { dg-do compile } */
/* { dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=ck801" }  { ""  }  }  */

int func (int a)
{
  return a ^ (0xf);
}
/* { dg-final { scan-assembler "xori" } } */


int func2 (int a)
{
  return a ^ (0xffffff);
}
/* { dg-final { scan-assembler "bmaski\[^\n\]*\n\[ |\t\]xor" } } */
