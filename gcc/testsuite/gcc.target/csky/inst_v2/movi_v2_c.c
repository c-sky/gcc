/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O2" } */

long test()
{
	return 65535;
}
/* { dg-final { scan-assembler "\[ |\t\]movi\[^\n\]*, 65535" } } */
