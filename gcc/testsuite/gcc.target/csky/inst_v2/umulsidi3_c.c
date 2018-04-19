/* { dg-do compile } */
/* { dg-options "-S -O2 -mdsp" } */

unsigned long long test(unsigned long long a, unsigned long long b)
{
	return a*b;
}
/* { dg-final { scan-assembler "\[ |\t\]mulu\[ |\t\].*\[^\n\]*\n\[ |\t\]mfhi\[ |\t\]\[^\n\]*\n\[ |\t\]mflo\[ |\t\]\[^\n\]*" } } */
