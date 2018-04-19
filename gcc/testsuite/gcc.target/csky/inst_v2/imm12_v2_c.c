/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O0 " } */

char test(char i)
{
	return i;
}

/* { dg-final { scan-assembler "\[ |\t\]st\.b\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]ld\.b\[ |\t\]" } } */
