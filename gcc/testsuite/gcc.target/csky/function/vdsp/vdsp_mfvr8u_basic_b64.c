/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

unsigned int func(__simd64_uint8_t b)
{
  char *a=(char *)&b;
  return (unsigned int)(a[7]);

}
/* { dg-final { scan-assembler "vmfvr\.u8" } }*/
