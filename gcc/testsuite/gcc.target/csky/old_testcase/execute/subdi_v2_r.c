/* { dg-do run } */
/* { dg-options "-O2" } */
long long c = 65537;
long long a = 1;
long long b = -65536;
long long result;
int main(void)
{
	result = a - b;
  	if (result != c)
    	return 1;
	return 0;
}
