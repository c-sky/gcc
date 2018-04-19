/* { dg-do compile } */
/* { dg-options "-march=ck510" } */
/* { dg-final {scan-assembler "\tlsri\[^\n\]*,1$"}}*/

unsigned int xor(unsigned int a)
{
	return a >> 0x1;
}
