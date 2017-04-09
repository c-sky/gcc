/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-options "-O2" } */

unsigned int test(unsigned int a, unsigned int b)
{
	return a/b;
}
/* { dg-final { scan-assembler "divu\t.*r1" } } */
