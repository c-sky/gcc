/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/*  {  dg-skip-if  ""  { csky-*-* }  { "-mvdsp-width=64" }  { " "  }  }  */
/* { dg-options " -mvdsp-width=128 " } */

__simd128_int32_t func (__simd128_int32_t a ,__simd128_int32_t b)
{
return a + b;

}

/* { dg-final { scan-assembler "vldq\.32" } }*/
/* { dg-final { scan-assembler "vadd\.u32" } }*/
/* { dg-final { scan-assembler "vstq\.32" } }*/
