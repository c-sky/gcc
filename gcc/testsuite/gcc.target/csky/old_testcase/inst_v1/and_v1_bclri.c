/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */

/* { dg-final { scan-assembler "\tbclri\t.*\[^\n\]*, 12" } }*/

int and(int a)
{
	return a & 0xffffefff;
}
