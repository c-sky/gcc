/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-final { scan-assembler "\tcmpne\t\.*\tmvcv\t" } } */

int storecc(int a,int b)
{
	return (a == b);
}
