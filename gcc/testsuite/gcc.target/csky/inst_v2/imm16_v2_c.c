/* { dg-do compile } */
/* { dg-options -S -O2 -march=ck810} */
/* { dg-final {scan-assembler "movih.*65522\[ |\t\]*not\[ |\t\]"}}*/

int test()
{
	return 0xdffff;
}
