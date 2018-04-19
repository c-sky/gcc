/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

unsigned int func(__simd64_uint32_t b)
{
  unsigned int *a=(unsigned int *)&b;
  return a[1];

}
/* { dg-final { scan-assembler "vmfvr\.u32" } }*/
