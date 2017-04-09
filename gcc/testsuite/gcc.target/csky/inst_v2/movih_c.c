/* { dg-do compile } */
/* { dg-options "-S -O2" } */

int test()
{
	return 0x12340000;
}
/* { dg-final { scan-assembler "movih\[ |\t\]" } } */
