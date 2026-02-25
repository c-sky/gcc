/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck810" } */

long test()
{
	return 117280;
}

/* { dg-final { scan-assembler "movi\[ |\t\]"} } */
/* { dg-final { scan-assembler "\[ |\t\]*bseti\[ |\t\]"} } */
