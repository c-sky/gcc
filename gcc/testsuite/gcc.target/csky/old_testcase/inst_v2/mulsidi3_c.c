/* { dg-do compile } */
/* { dg-options "-S -O2 -mdsp" } */

long long test(long long a, long long b)
{
	return a*b;
}
/* { dg-final { scan-assembler "\[ |\t\]mulu\[ |\t\].*\[^\n\]*\n\[ |\t\]mfhi\[ |\t\]\[^\n\]*\n\[ |\t\]mflo\[ |\t\]\[^\n\]*" } } */
