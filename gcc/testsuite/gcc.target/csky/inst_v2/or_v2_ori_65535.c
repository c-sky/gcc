/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]ori\[ |\t\]\[^\n\]*, 65535" } } */

int or(int a)
{
	return a | 0xffff;
}
