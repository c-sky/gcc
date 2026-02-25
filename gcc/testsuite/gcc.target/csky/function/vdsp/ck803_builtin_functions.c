/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "-mcpu=ck803efr1" } */


__simd32_int8_t func1 (__simd32_int8_t a, __simd32_int8_t b)
{
  return __builtin_csky_paddv4qi (a, b);
}

/* { dg-final { scan-assembler "padd\.8" } } */

__simd32_int16_t func2 (__simd32_int16_t a, __simd32_int16_t b)
{
  return __builtin_csky_paddv2hi (a, b);
}

/* { dg-final { scan-assembler "padd\.16" } } */
