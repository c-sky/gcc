/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]bclri\[ |\t\]\[^\n\]*, 12" } } */

int and(int a)
{
	return a & 0xffffefff;
}
