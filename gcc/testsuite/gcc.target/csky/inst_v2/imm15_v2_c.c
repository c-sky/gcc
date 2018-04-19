/* { dg-do compile } */
/* { dg-options -S -O2 -march=ck810} */
/* { dg-final {scan-assembler "movi\[ |\t\]*rotli.*16"}}*/

int test()
{
	return 0xa7ff0000;
}
