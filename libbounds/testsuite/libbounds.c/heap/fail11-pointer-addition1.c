#include <stdlib.h>

int main ()
{
	int *p;
	p = (int *) malloc( 10 * sizeof(int) );

	/* p[9] = 0; */
	p = p + 10;
	*p = 0;

	free( p );

	return 0;
}
/* { dg-output "bounds violation.*" } */
/* { dg-do run { xfail *-*-* } } */
