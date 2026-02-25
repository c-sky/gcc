/* { dg-do compile } */
/* { dg-skip-if  "test is specific to ck860f"  { csky-*-* }  { "*" }  { "-mcpu=ck860*f* -mfloat-abi=hard" "-mcpu=ck860*f* -mhard-float"  }  }  */
/* { dg-options "-O1 -mfpu=fpv3" } */

//int
//float16_to_fixed32 (__fp16 f)
//{
//  return ((int) (f * (1 << 15)));
//}
//
//unsigned int
//float16_to_fixedu32 (__fp16 f)
//{
//  return ((unsigned int) (f * (1 << 15)));
//}
//
//
//int
//float32_to_fixed32 (float f)
//{
//  return ((int) (f * (1 << 30)));
//}
//
//unsigned int
//float32_to_fixedu32 (float f)
//{
//  return ((unsigned int) (f * (1 << 30)));
//}
//
//int
//float64_to_fixed32 (double f)
//{
//  return ((int) (f * (1 << 30)));
//}
//
//unsigned int
//float64_to_fixedu32 (double f)
//{
//  return ((unsigned int) (f * (1 << 30)));
//}
//
//short
//float16_to_fixed16 (__fp16 f)
//{
//  return ((short) (f * (1 << 15)));
//}
//
//unsigned short
//float16_to_fixedu16 (__fp16 f)
//{
//  return ((unsigned short) (f * (1 << 15)));
//}
//
//short
//float32_to_fixed16 (float f)
//{
//  return ((short) (f * (1 << 16)));
//}
//
//unsigned short
//float32_to_fixedu16 (float f)
//{
//  return ((unsigned short) (f * (1 << 16)));
//}
//
//short
//float64_to_fixed16 (double f)
//{
//  return ((short) (f * (1 << 16)));
//}
//
//unsigned short
//float64_to_fixedu16 (double f)
//{
//  return ((unsigned short) (f * (1 << 16)));
//}

