/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O0 " } */

int test(int i)
{
	return i;
}

/* { dg-final { scan-assembler "\[ |\t\]stw\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]ldw\[ |\t\]" } } */
