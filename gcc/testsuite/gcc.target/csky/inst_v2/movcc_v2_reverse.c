/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final {scan-assembler "\[ |\t\]cmpnei\[ |\t\]\[^\n\]*,1\n\[ |\t\]movf\[^\n\]*\n\[ |\t\]movt\[ |\t\]"}}*/

int mov(int a,int b, int c)
{
	if(a == 1)
		a = b;
	else
		a = c;
	return a;
}
