/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck810" } */

long test()
{
	return 0x10001234;
}

/* { dg-final { scan-assembler "\[ |\t\]movi\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]bseti\[ |\t\]" } } */
