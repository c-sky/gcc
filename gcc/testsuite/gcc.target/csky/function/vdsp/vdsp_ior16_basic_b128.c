/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=128 " } */

__simd128_int16_t func (__simd128_int16_t a ,__simd128_int16_t b)
{
return a | b;

}
/* { dg-final { scan-assembler "vor\.16" } }*/
