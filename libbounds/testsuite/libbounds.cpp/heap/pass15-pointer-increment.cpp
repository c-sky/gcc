int main ()
{
	int *p;
	p = new int[10];

	/* p[9] = 0; */
	p = &p[8];
	p ++;
	*p = 0;

	return 0;
}
