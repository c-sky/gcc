/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck810" } */

long test()
{
	return 0x0001fffe;
}

/* { dg-final { scan-assembler "\[ |\t\]bmaski\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]subi\[ |\t\]" } } */
