/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-final { scan-assembler "\[ |\t\]asri\[^\n\]*, 1" } } */

int asr(int a)
{
	return a >> 0x1;
}
