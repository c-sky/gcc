/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final {scan-assembler "\[ |\t\]cmpnei\[ |\t\]\[^\n\]*, 1\n\[ |\t\]movt\[^\n\]*\n\[ |\t\]clrf\[ |\t\]"}}*/

int mov(int a,int b)
{
	if(a != 1)
		a = b;
	else
		a = 0;
	return a;
}
