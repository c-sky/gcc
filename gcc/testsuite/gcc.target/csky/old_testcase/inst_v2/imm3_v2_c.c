/* { dg-do compile } */
/* { dg-options "-S -O2" } */

long test()
{
	return 0x1fffff34;
}

/* { dg-final { scan-assembler "\[ |\t\]movih\[ |\t\]" } } */
/* { dg-final { scan-assembler "\subi\[ |\t\]" } } */
