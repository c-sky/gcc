/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

__simd64_uint8_t func(char a,__simd64_uint8_t b)
{
  char *d=(char*)&b;
  d[5] = a;
  return b;

}
/* { dg-final { scan-assembler "vmtvr\.u8" } }*/
