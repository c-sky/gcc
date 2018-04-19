/* { dg-do compile } */
/* { dg-options "-S -O2 -mdsp" } */

unsigned long long test(unsigned long *a, unsigned long *b)
{
	long long result;
	result = (unsigned long long)a[0]*b[0];
	result -= (unsigned long long)a[1]*b[1];
	result -= (unsigned long long)a[2]*b[2];
	result -= (unsigned long long)a[3]*b[3];
	return result;
}

/* { dg-final { scan-assembler-times "\[ |\t\]mulu\[ |\t\]" 1 } } */
/* { dg-final { scan-assembler-times "\[ |\t\]mulus\[ |\t\]" 3 } } */
/* { dg-final { scan-assembler "\[ |\t\]mfhi\[ |\t\]" } } */
/* { dg-final { scan-assembler "\[ |\t\]mflo\[ |\t\]" } } */
