/* { dg-do compile } */
/* { dg-options "-march=ck510" } */
/* { dg-final {scan-assembler-not "\tlsri\t|\tlsr\t"}}*/

unsigned int xor(unsigned int a)
{
	return a >> 0x0;
}