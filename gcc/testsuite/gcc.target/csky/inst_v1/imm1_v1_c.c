/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck510" } */

long test()
{
	return 0xfff2;
}

/* { dg-final { scan-assembler "bmaski\t.*subi" } } */
