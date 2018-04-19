/* { dg-do compile } */
/* { dg-options "-march=ck510" } */
/* { dg-final {scan-assembler "\tlsri\[^\n\]*,31$"}}*/

unsigned int xor(unsigned int a)
{
	return a >> 31;
}
