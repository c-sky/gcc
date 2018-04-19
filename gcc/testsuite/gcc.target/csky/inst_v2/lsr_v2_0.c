/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler-not "\[ |\t\]lsri\[ |\t\]|\[ |\t\]lsr\[ |\t\]" } } */

unsigned int lsr(unsigned int a)
{
	return a >> 0x0;
} 
