/* { dg-do run } */
/* { dg-options " -O2 " } */
int c = 2;
int a = 65538;
int b = -65536;
int result;
int main(void)
{
	result = a + b;
  	if (result != c)
    	return 1;
	return 0;
}

