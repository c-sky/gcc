int main()
{
	int* p;
	int* a = new int[10];

	/* a[0] = 0; */
	p = a;
	*p = 0;

	delete a;

	return 0;
}
