/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*" }  }  */

/* { dg-options "-O2 " } */
/* { dg-final { scan-assembler-times "ldr\.w" 21 } } */

#define swapcplx(p0,p1)                                                 \
  t = p0; t1 = *(&(p0)+1); p0 = p1; *(&(p0)+1) = *(&(p1)+1); p1 = t; *(&(p1)+1) = t1

#define NUM_FFT_SIZES 2
static const int nfftlog2Tab[NUM_FFT_SIZES] ={6, 9};

void BitReverse(int *inout, int tabidx, unsigned char* p)
{
  int *part0, *part1;
	int a,b, t,t1;
	const unsigned char* tab = p;
	int nbits = nfftlog2Tab[tabidx];

	part0 = inout;
  part1 = inout + (1 << nbits);

	while ((a = *tab++) != 0) {
    b = *tab++;

    swapcplx(part0[4*a+0], part0[4*b+0]);	/* 0xxx0 <-> 0yyy0 */
    swapcplx(part0[4*a+2], part1[4*b+0]);	/* 0xxx1 <-> 1yyy0 */
    swapcplx(part1[4*a+0], part0[4*b+2]);	/* 1xxx0 <-> 0yyy1 */
    swapcplx(part1[4*a+2], part1[4*b+2]);	/* 1xxx1 <-> 1yyy1 */
  }

  do {
    swapcplx(part0[4*a+2], part1[4*a+0]);	/* 0xxx1 <-> 1xxx0 */
  } while ((a = *tab++) != 0);
}
