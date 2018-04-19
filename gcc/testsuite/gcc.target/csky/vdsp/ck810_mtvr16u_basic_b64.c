/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

__simd64_uint16_t func(unsigned short a,__simd64_uint16_t b)
{
  unsigned short *d=(unsigned short *)&b;
  d[1] = a;
  return b;

}
/* { dg-final { scan-assembler "vmtvr\.u16" } }*/
