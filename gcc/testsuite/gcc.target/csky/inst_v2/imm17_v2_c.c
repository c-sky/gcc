/* { dg-do compile } */
/* { dg-options -S -O2 -march=ck810} */
/* { dg-final {scan-assembler "movih.*13"}}*/

int test()
{
	return 0xd0000;
}
