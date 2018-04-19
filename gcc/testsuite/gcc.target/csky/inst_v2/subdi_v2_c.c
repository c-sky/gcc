/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O2" } */

long long test(long long a, long long b)
{
	return (a - b);
}
/* { dg-final { scan-assembler "\[ |\t\]cmphs\[ |\t\].*\[^\n\]*\n\[ |\t\]subc\[ |\t\]\[^\n\]*\n" } } */
/* { dg-final { scan-assembler-times "subc\[ |\t\]" 2 } } */
