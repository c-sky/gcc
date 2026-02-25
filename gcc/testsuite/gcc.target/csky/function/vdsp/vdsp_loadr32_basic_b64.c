/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

__simd64_int32_t func2(__simd64_int32_t *b, unsigned int j)
{
return b[j];
}

/* { dg-final { scan-assembler "vldrd\.32" } }*/
