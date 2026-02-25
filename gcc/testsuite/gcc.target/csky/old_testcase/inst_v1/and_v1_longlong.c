/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-final { scan-assembler-times "\tand\tr" 2 } } */
/* { dg-options "-std=c99" } */

long long and(long long a,long long b)
{
	return a & b;
}
