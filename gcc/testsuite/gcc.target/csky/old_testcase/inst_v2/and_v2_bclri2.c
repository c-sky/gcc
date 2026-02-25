/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]bclri\[ |\t\]\[^\n\]*, 29\n\[ |\t\]bclri\[ |\t\]\[^\n\]*, 31" } } */

int and(int a)
{
	return a & 0x5fffffff;
}
