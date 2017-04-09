/* { dg-do compile } */
/* { dg-options"-mcpu=ck810 -O2" } */
/* { dg-final {scan-assembler "rsub\[ |\t\]"}}*/


int test(int a, int b)
{
	b =  a-b;
	return b;
}
