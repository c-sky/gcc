/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck810" } */

long test()
{
	return 0x8000ffff;
}

/* { dg-final { scan-assembler "\[ |\t\]movih\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]not\[ |\t\]" } } */
