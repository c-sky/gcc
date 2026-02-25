/* { dg-do run } */
/* { dg-options "-S -O2 -march=ck810" } */
int c = 131074;
int a = 65538;
int b = -65536;
int result;
int main(void)
{
	result = a - b;
  	if (result != c)
    	return 1;
	return 0;
}
