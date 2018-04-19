/* { dg-do compile } */
/* { dg-options "-S -O2 " } */

long test()
{
	return 0x12341000;
}

/* { dg-final { scan-assembler "\[ |\t\]movih\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]bseti\[ |\t\]" } } */
