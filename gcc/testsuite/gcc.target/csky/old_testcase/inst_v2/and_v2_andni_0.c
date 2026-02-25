/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler-not "\[ |\t\]andni\[ |\t\]|\[ |\t\]andn\[ |\t\]" } } */


int and(int a)
{
	return a & (~0);
}
