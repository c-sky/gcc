/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck510" } */

long test()
{
	return 0x000001fe;
}

/* { dg-final { scan-assembler "\tbmaski\t.*\n\tsubi\t" } } */
