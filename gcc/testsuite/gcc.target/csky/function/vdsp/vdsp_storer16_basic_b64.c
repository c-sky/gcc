/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64  -O2" } */

__simd64_int16_t bb;

__simd64_int16_t func2(__simd64_int16_t *b, unsigned int j)
{
 b[j]=bb;
}

/* { dg-final { scan-assembler "vstrd\.16" } }*/
