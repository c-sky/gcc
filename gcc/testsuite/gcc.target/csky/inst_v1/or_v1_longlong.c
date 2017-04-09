/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-final { scan-assembler-times "\tor64\t" 1 } }*/
/* { dg-options "-std=c99" } */
long long or(long long a, long long b)
{
	return a | b;
}
