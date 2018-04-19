/* { dg-do run } */
/* { dg-options "-O2" } */
int c = 127;
int a = 128;
int b = -1;
int result;
int main(void)
{
	result = a + b;
  	if (result != c)
    	return 1;
	return 0;
}
