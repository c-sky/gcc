/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=128 " } */

__simd128_int32_t func (__simd128_int32_t a ,__simd128_int32_t b)
{
return a * b;

}
/* { dg-final { scan-assembler "vmul\.u32" } }*/
