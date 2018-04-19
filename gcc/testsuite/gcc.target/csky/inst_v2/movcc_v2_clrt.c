/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final {scan-assembler "\[ |\t\]cmpnei\[ |\t\]\[^\n\]*,1\n\[ |\t\]clrt\[^\n\]*\n\[ |\t\]movf\[ |\t\]"}}*/

int movcc(int a,int b)
{
	if(a != 1)
		a = 0;
	else
		a = b;
	return a;
}
