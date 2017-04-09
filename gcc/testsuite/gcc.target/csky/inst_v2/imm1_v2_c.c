/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck810" } */

long test()
{
	return 65535;
}

/* { dg-final { scan-assembler "movi\[ |\t\]" } } */