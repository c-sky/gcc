/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck510" } */

long test()
{
	return 369;
}

/* { dg-final { scan-assembler "movi\t.*bseti\t" } } */
