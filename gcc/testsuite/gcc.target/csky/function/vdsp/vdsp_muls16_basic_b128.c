/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=128  -O2" } */

__simd128_int16_t func (__simd128_int16_t a ,__simd128_int16_t b, __simd128_int16_t c)
{
  return a * b - c;

}
/* { dg-final { scan-assembler "vmuls\.u16" } }*/
