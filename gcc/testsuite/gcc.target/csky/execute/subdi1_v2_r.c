/* { dg-do run } */
/* { dg-options "-O2" } */
long long c = -65537;
long long a = -65536;
long long result;
int main(void)
{
	result = a - 1;
  	if (result != c)
    	return 1;
	return 0;
}
