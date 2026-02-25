/* { dg-do compile } */
/* { dg-options "-S -O2 " } */

long test()
{
	return 84720;
}

/* { dg-final { scan-assembler "\[ |\t\]movi\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]bseti\[ |\t\]" } } */
