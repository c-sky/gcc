/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]bseti\[ |\t\]\[^\n\]*, 30\n\[ |\t\]bseti\[ |\t\]\[^\n\]*, 31" } } */

int or(int a)
{
	return a | 0xc0000000;
}
