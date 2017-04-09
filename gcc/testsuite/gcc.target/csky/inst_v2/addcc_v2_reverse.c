/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O2" } */
/* { dg-final { scan-assembler "\[ |\t\]cmplt\[ |\t\]\[^\n\]*\n\[ |\t\]movt\[^\n\]*\n\[ |\t\]incf\[ |\t\]\[^\n\]*, 13" } } */

int addcc(int a,int b,int c)
{
	if(a > b)
		c = b;
	else
		c = b + 13;
	return c;
}
