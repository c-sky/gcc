/* { dg-do run } */

int storecc(int a,int b)
{
	return (a != b);
}

int main(void)
{
		int a;
		
		a = storecc(1,2);
		
		if(a != 1)
			return 1;
			
		a = storecc(1,1);
		
		if(a == 1)
			return 1;
			
		return 0;
}
