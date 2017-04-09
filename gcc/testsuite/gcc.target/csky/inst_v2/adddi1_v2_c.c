/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O2" } */

long long test(long long a)
{
	return ( a + 1);
}
/* { dg-final { scan-assembler "\[ |\t\]addi\[ |\t\]\[^\n\]*\n\[ |\t\]cmpnei\[^\n\]*\n\[ |\t\]incf\[ |\t\]\[^\n\]*" } } */
