/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/*  {  dg-skip-if  ""  { csky-*-* }  { "-mvdsp-width=64" }  { " "  }  }  */
/* { dg-options " -mvdsp-width=128  -O2" } */

__simd128_int32_t func4(int *a, unsigned int i)
{
int *b = a + i;
return *(__simd128_int32_t *)b;
}

/* { dg-final { scan-assembler "vldrq\.32" } }*/
