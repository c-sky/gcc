/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck810" } */

int test(int a, int b)
{
	return a * b;
}

/* { dg-final { scan-assembler "mult\[ |\t\]" } } */
