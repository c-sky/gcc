/* { dg-do run } */
/* { dg-options "-S -O2 -march=ck810" } */
long long c = -65535;
long long a = -65536;
long long result;
int main(void)
{
	result = a + 1;
  	if (result != c)
    	return 1;
	return 0;
}

