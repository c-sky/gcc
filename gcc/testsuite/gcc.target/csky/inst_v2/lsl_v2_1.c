/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler-not "\[ |\t\]lsli\[ |\t\] | \[ |\t\]lsl\[ |\t\]" } } */

int lsl(int a)
{
	return a << 0x1;
}
