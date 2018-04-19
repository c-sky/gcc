/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-options "-O2" } */

int test(int i)
{
	return ( i - 1);
}
/* { dg-final { scan-assembler "subi\t" } } */
