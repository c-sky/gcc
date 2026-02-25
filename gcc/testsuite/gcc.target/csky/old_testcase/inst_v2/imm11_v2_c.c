/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to the instruction v2"  { csky-*-* }  { "-march=*" }  { "-march=ck8*"  }  }  */
/* { dg-options "-O0 " } */
short test(short i)
{
	return i;
}

/* { dg-final { scan-assembler "\[ |\t\]st.h\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]ld.h\[ |\t\]" } } */
