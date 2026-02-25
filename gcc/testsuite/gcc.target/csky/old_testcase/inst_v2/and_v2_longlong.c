/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler-times "\[ |\t\]and\[ |\t\]" 2 } } */

long long f_and(long long a,long long b)
{
	return a & b;
}
