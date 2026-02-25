/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/*  {  dg-skip-if  ""  { csky-*-* }  { "-mvdsp-width=64" }  { " "  }  }  */
/* { dg-options " -mvdsp-width=128  -O2" } */

__simd128_uint16_t func(unsigned short a,__simd128_uint16_t b)
{
  unsigned short *d=(unsigned short *)&b;
  d[5] = a;
  return b;

}
/* { dg-final { scan-assembler "vmtvr\.u16" } }*/
