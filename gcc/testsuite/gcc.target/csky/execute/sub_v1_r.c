/* { dg-do run } */
/* { dg-options "-S -O2 -march=ck510" } */
int c = 129;
int a = 128;
int b = -1;
int result;
int main(void)
{
	result = a - b;
  	if (result != c)
    	return 1;
	return 0;
}