/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

__simd64_uint32_t func(unsigned int a,__simd64_uint32_t b)
{
  unsigned int *d=(unsigned int *)&b;
  d[1] = a;
  return b;

}
/* { dg-final { scan-assembler "vmtvr\.u32" } }*/
