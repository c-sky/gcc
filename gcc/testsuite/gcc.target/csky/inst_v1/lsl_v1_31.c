/* { dg-do compile } */
/* { dg-final { scan-assembler "\tlsli\[^\n\]*, 31" } } */

int xor(int a)
{
	return a << 31;
}
