/* { dg-do compile } */

int addcc(int a,int b)
{
	if(a != 1)
		a = b;
	else
		a = b + 1;
	return a;
}

int main(void)
{
	int a;
	
	a = addcc(2,3);
	
	if(a != 3)
		return 1;
	
	a = addcc(1,3);
	
	if(a == 3)
		return 1;
		
	return 0;	
}
