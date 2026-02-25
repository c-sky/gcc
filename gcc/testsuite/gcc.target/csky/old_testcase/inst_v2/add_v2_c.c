/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options " -O2" } */

int test(int i)
{
	return (i + (-0x1000));
}
/* { dg-final { scan-assembler-not "\[ |\t\]addi\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]subi\[ |\t\]" } } */
