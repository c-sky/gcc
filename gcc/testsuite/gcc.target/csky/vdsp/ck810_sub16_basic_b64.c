/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64 " } */

__simd64_int16_t func (__simd64_int16_t a ,__simd64_int16_t b)
{
return a - b;

}
/* { dg-final { scan-assembler "vsub\.u16" } }*/
