/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]bseti\[ |\t\]\[^\n\]*, 28" } } */

int or(int a)
{
	return a | 0x10000000;
}
