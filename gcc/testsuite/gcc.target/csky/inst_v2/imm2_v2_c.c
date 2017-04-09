/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck810" } */

long test()
{
	return 65537;
}

/* { dg-final { scan-assembler "\[ |\t\]movih\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]addi\[ |\t\]" } } */
