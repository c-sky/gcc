/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O2 " } */

int test(int i)
{
	return (i - 0xfffff000);
}
/* { dg-final { scan-assembler-not "\[ |\t\]subi\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]addi\[ |\t\]" } } */
