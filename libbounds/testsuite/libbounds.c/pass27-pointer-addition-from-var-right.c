int main()
{
	int* p;
	int a[10];
	int i = 9;

	/* a[9] = 0; */
	p = a;
	p = p + i;
	*p = 0;

	return 0;
}
