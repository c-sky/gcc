/* { dg-do compile } */
/* { dg-options "-S -O2 -march=ck510" } */

long test()
{
	return 0x8000000F;
}

/* { dg-final { scan-assembler "bgeni\t.*addi\t" } } */
