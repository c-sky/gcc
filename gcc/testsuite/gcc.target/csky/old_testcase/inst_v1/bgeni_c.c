/* { dg-do compile } */
/* { dg-options "-S -O2" } */

long test()
{
	return 0x1000;
}

/* { dg-final { scan-assembler "bgeni\t" } } */