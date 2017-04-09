/* { dg-do run } */

int addcc(int a,int b)
{
	if(a == 1)
		a = b;
	else
		a = b + 1;
	return a;
}

int main(void)
{
	int a;
	
	a = addcc(1,2);
	
	if(a != 2)
		return 1;
	
	a = addcc(0,2);
	
	if(a == 2)
		return 1;
		
	return 0;	
}
