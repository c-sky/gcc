/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

unsigned int func(__simd64_uint16_t b)
{
  unsigned short *a=(unsigned short *)&b;
  return (unsigned int)(a[3]);

}
/* { dg-final { scan-assembler "vmfvr\.u16" } }*/
