/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-final {scan-assembler-times "\txor\t" 2}}*/
/* { dg-options "-std=c99" } */
long long xor(long long a,long long b)
{
	return a ^ b;
}
