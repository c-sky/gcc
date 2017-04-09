/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]cmpne\[ |\t\]\[^\n\]*\n\[ |\t\]mvcv\[ |\t\]" } } */

int storecc(int a,int b)
{
	return (a == b);
}
