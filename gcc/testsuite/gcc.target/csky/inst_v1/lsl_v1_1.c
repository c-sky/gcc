/* { dg-do compile } */
/* { dg-final { scan-assembler "\tlsli\[^\n\]*, 2" } } */

int xor(int a)
{
	return a << 0x2;
}
