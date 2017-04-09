/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v1"  { csky-*-* }  { "-march=*" }  { "-march=ck\[56\]*"  }  }  */
/* { dg-final { scan-assembler "\tbmaski\t.*\[^\n\]*, 28.*\n\tandn" } }*/

int and(int a)
{
	return a & 0xf0000000;
}
