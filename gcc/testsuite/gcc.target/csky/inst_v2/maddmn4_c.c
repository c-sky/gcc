/* { dg-do compile } */
/* { dg-options "-S -O2 -mdsp" } */

long long test(long *a, long *b)
{
	long long result;
	result = (long long)a[0]*b[0];
	result += (long long)a[1]*b[1];
	result += (long long)a[2]*b[2];
	result += (long long)a[3]*b[3];
	return result;
}

/* { dg-final { scan-assembler-times "\[ |\t\]muls\[ |\t\]r*"  1} } */
/* { dg-final { scan-assembler-times "\[ |\t\]mulsa\[ |\t\]*" 3 } } */
/* { dg-final { scan-assembler "\[ |\t\]mulsa\[ |\t\].*\[^\n\]*\n\[ |\t\]mfhi\[ |\t\]\[^\n\]*\n\[ |\t\]mflo\[ |\t\]\[^\n\]*" } } */
