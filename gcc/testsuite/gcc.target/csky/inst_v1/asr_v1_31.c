/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-final { scan-assembler "\tasri\t.*\[^\n\]*, 31" } }*/

int xor(int a)
{
	return a >> 31;
}
