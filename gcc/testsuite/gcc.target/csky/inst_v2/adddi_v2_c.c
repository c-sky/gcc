/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v22"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O2" } */

long long test(long long a, long long b)
{
	return (a + b);
}
/* { dg-final { scan-assembler "cmplt\[ |\t\].*addc\[ |\t\]" } } */
/* { dg-final { scan-assembler-times "addc\[ |\t\]" 2 } } */

