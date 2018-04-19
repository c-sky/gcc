/* { dg-do run } */

int mov(int a,int b, int c)
{
	if(a != 1)
		a = b;
	else
		a = c;
	return a;
}

int main(void)
{
	int a;

	a = mov(0, 2, 3);
	
	if(a != 2)
		return 1;
		
	a = mov(1, 2, 3);
	
	if(a != 3)
		return 1;
		
	return 0;	
}
