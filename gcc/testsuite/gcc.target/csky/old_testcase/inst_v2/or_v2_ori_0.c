/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler-not "\[ |\t\]ori\[ |\t\]" } } */

int or(int a)
{
	return a | 0x0;
}
