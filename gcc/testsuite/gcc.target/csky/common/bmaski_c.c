/* { dg-do compile } */
/* { dg-options "-S -O2" } */

long test()
{
	return 0xffffff;
}
/* { dg-final { scan-assembler "bmaski\t" } } */
