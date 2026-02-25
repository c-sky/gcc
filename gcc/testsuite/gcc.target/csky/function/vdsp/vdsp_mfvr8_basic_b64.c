/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

int func(__simd64_int8_t b)
{
  signed char *a=(signed char *)&b;
  return (int)(a[7]);

}
/* { dg-final { scan-assembler "vmfvr\.s8" } }*/
