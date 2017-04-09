/* { dg-do compile } */
/* { dg-final { scan-assembler-not "\tlsl" } }*/

int xor(int a)
{
	return a << 0x0;
}
