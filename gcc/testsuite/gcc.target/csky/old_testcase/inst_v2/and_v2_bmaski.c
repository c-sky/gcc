/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]bmaski\[ |\t\]\[^\n\]*, 28\[^\n\]*\n\[ |\t\]and\[ |\t\]" } } */

int and(int a)
{
	return a & 0x0fffffff;
}
