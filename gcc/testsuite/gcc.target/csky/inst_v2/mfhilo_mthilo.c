/* { dg-do compile } */
/* { dg-options "-S -O2 -mdsp" } */
/* { dg-final { scan-assembler "mfhi" } } */
/* { dg-final { scan-assembler-not "mflo" } } */

int func(int *a, int *b)
{
    long long m = 0x1111111122222222;
    int i;

    for(i = 0; i < 10; i++)
        m += (long long)a[i] * b[i];

    return m>>32;
}
