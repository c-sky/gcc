/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

int func(__simd64_int16_t b)
{
  short *a=(short *)&b;
  return (int)(a[3]);

}
/* { dg-final { scan-assembler "vmfvr\.s16" } }*/
