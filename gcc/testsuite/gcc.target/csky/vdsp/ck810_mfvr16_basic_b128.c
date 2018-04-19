/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/*  {  dg-skip-if  ""  { csky-*-* }  { "-mvdsp-width=64" }  { " "  }  }  */
/* { dg-options " -mvdsp-width=128  -O2" } */

int func(__simd128_int16_t b)
{
  short *a=(short *)&b;
  return (int)(a[7]);

}
/* { dg-final { scan-assembler "vmfvr\.s16" } }*/
