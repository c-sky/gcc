int main()
{
	int* p;
	int a[10];

	/* a[-1] = 0; */
	p = a;
	p --;
	*p = 0;

	return 0;
}
/* { dg-output "bounds violation.*" } */
/* { dg-do run { xfail *-*-* } } */
