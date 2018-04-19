/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options " -mvdsp-width=64 " } */

__simd64_int32_t func (__simd64_int32_t a)
{
return -a;

}
/* { dg-final { scan-assembler "vneg\.s32" } }*/
