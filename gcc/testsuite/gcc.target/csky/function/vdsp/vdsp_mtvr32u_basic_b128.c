/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/*  {  dg-skip-if  ""  { csky-*-* }  { "-mvdsp-width=64" }  { " "  }  }  */
/* { dg-options " -mvdsp-width=128  -O2" } */

__simd128_uint32_t func(unsigned int a,__simd128_uint32_t b)
{
  unsigned int *d=(unsigned int *)&b;
  d[1] = a;
  return b;

}
/* { dg-final { scan-assembler "vmtvr\.u32" } }*/
