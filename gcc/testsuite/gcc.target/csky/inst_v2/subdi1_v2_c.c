/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options " -O2" } */

long long test(long long i)
{
	return (i - 1);
}
/* { dg-final { scan-assembler "\[ |\t\]cmpnei\[ |\t\].*\[^\n\]*\n\[ |\t\]decf\[ |\t\]\[^\n\]*\n\[ |\t\]subi\[ |\t\]\[^\n\]*" } } */
