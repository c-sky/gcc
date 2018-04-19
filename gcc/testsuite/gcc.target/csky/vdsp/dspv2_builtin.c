/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "" } */

#define TEST(func) \
  __simd32_int8_t f_##func##_v4qi (__simd32_int8_t a, __simd32_int8_t b) \
    {                                                          \
      return __builtin_csky_##func##v4qi (a, b);               \
    }                                                          \
  __simd32_int16_t f_##func##_v2hi (__simd32_int16_t a, __simd32_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }                                                          \
  __simd32_sat8_t f_##func##_v4qq (__simd32_sat8_t a, __simd32_sat8_t b) \
    {                                                          \
      return __builtin_csky_##func##v4qq (a, b);               \
    }                                                          \
  __simd32_sat16_t f_##func##_v2hq (__simd32_sat16_t a, __simd32_sat16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hq (a, b);               \
    }                                                          \
  __simd32_usat8_t f_##func##_v4uqq (__simd32_usat8_t a, __simd32_usat8_t b) \
    {                                                          \
      return __builtin_csky_##func##v4uqq (a, b);               \
    }                                                          \
  __simd32_usat16_t f_##func##_v2uhq (__simd32_usat16_t a, __simd32_usat16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2uhq (a, b);               \
    }
TEST(padd)
/* { dg-final { scan-assembler "padd\.8" } }*/
/* { dg-final { scan-assembler "padd\.16" } }*/
/* { dg-final { scan-assembler "padd\.s8\.s" } }*/
/* { dg-final { scan-assembler "padd\.s16\.s" } }*/
/* { dg-final { scan-assembler "padd\.u8\.s" } }*/
/* { dg-final { scan-assembler "padd\.u16\.s" } }*/
TEST(psub)
/* { dg-final { scan-assembler "psub\.8" } }*/
/* { dg-final { scan-assembler "psub\.16" } }*/
/* { dg-final { scan-assembler "psub\.s8\.s" } }*/
/* { dg-final { scan-assembler "psub\.s16\.s" } }*/
/* { dg-final { scan-assembler "psub\.u8\.s" } }*/
/* { dg-final { scan-assembler "psub\.u16\.s" } }*/

#define TEST1(func) \
  __simd32_int8_t f_##func##_v4qi (__simd32_int8_t a, __simd32_int8_t b) \
    {                                                          \
      return __builtin_csky_##func##v4qi (a, b);               \
    }                                                          \
  __simd32_int16_t f_##func##_v2hi (__simd32_int16_t a, __simd32_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST1(paddhs)
/* { dg-final { scan-assembler "paddh\.s8" } }*/
/* { dg-final { scan-assembler "paddh\.s16" } }*/
TEST1(psubhs)
/* { dg-final { scan-assembler "psubh\.s8" } }*/
/* { dg-final { scan-assembler "psubh\.s16" } }*/
TEST1(pcmpne)
/* { dg-final { scan-assembler "pcmpne\.8" } }*/
/* { dg-final { scan-assembler "pcmpne\.16" } }*/
TEST1(pcmplts)
/* { dg-final { scan-assembler "pcmplt\.s8" } }*/
/* { dg-final { scan-assembler "pcmplt\.s16" } }*/
TEST1(pcmphss)
/* { dg-final { scan-assembler "pcmphs\.s8" } }*/
/* { dg-final { scan-assembler "pcmphs\.s16" } }*/
TEST1(smax)
/* { dg-final { scan-assembler "pmax\.s8" } }*/
/* { dg-final { scan-assembler "pmax\.s16" } }*/
TEST1(smin)
/* { dg-final { scan-assembler "pmin\.s8" } }*/
/* { dg-final { scan-assembler "pmin\.s16" } }*/

#define TEST1_1(func) \
  __simd32_uint8_t f_##func##_v4qi (__simd32_uint8_t a, __simd32_uint8_t b) \
    {                                                          \
      return __builtin_csky_##func##v4qi (a, b);               \
    }                                                          \
  __simd32_uint16_t f_##func##_v2hi (__simd32_uint16_t a, __simd32_uint16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST1_1(paddhu)
/* { dg-final { scan-assembler "paddh\.u8" } }*/
/* { dg-final { scan-assembler "paddh\.u16" } }*/
TEST1_1(psubhu)
/* { dg-final { scan-assembler "psubh\.u8" } }*/
/* { dg-final { scan-assembler "psubh\.u16" } }*/
TEST1_1(pcmpltu)
/* { dg-final { scan-assembler "pcmplt\.u8" } }*/
/* { dg-final { scan-assembler "pcmplt\.u16" } }*/
TEST1_1(pcmphsu)
/* { dg-final { scan-assembler "pcmphs\.u8" } }*/
/* { dg-final { scan-assembler "pcmphs\.u16" } }*/
TEST1_1(umax)
/* { dg-final { scan-assembler "pmax\.u8" } }*/
/* { dg-final { scan-assembler "pmax\.u16" } }*/
TEST1_1(umin)
/* { dg-final { scan-assembler "pmin\.u8" } }*/
/* { dg-final { scan-assembler "pmin\.u16" } }*/


#define TEST2(func) \
  __simd32_int16_t f_##func##_v2hi (__simd32_int16_t a, __simd32_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }                                                          \
  __simd32_sat16_t f_##func##_v2hq (__simd32_sat16_t a, __simd32_sat16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hq (a, b);               \
    }                                                          \
  __simd32_usat16_t f_##func##_v2uhq (__simd32_usat16_t a, __simd32_usat16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2uhq (a, b);               \
    }
TEST2(psax)
/* { dg-final { scan-assembler "psax\.16" } }*/
/* { dg-final { scan-assembler "psax\.s16\.s" } }*/
/* { dg-final { scan-assembler "psax\.u16\.s" } }*/
TEST2(pasx)
/* { dg-final { scan-assembler "pasx\.16" } }*/
/* { dg-final { scan-assembler "pasx\.s16\.s" } }*/
/* { dg-final { scan-assembler "pasx\.u16\.s" } }*/

#define TEST3(func) \
  __simd32_int16_t f_##func##_v2hi (__simd32_int16_t a, __simd32_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST3(psaxhs)
/* { dg-final { scan-assembler "psaxh\.s16" } }*/
TEST3(pasxhs)
/* { dg-final { scan-assembler "pasxh\.s16" } }*/
TEST3(prmulsh)
/* { dg-final { scan-assembler "prmul\.s16\.h" } }*/
TEST3(prmulsrh)
/* { dg-final { scan-assembler "prmul\.s16\.rh" } }*/
TEST3(prmulxsh)
/* { dg-final { scan-assembler "prmulx\.s16\.h" } }*/
TEST3(prmulxsrh)
/* { dg-final { scan-assembler "prmulx\.s16\.rh" } }*/

#define TEST3_1(func) \
  __simd32_uint16_t f_##func##_v2hi (__simd32_uint16_t a, __simd32_uint16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST3_1(psaxhu)
/* { dg-final { scan-assembler "psaxh\.u16" } }*/
TEST3_1(pasxhu)
/* { dg-final { scan-assembler "pasxh\.u16" } }*/

#define TEST4(func) \
  int f_##func##_si (int a, int b, int c) \
    {                                                          \
      return __builtin_csky_##func##si (a, b, c);               \
    }
TEST4(sel)
/* { dg-final { scan-assembler "sel" } }*/

#define TEST5(func) \
  int f_##func##_si (int a, int b) \
    {                                                          \
      return __builtin_csky_##func##si (a, b);               \
    }
TEST5(pkgll)
/* { dg-final { scan-assembler "pkgll" } }*/
TEST5(pkghh)
/* { dg-final { scan-assembler "pkghh" } }*/
TEST5(narl)
/* { dg-final { scan-assembler "narl" } }*/
TEST5(narh)
/* { dg-final { scan-assembler "narh" } }*/
TEST5(narlx)
/* { dg-final { scan-assembler "narlx" } }*/
TEST5(narhx)
/* { dg-final { scan-assembler "narhx" } }*/

#define TEST6(func) \
  int fi_##func##_si (int a, int b) \
    {                                                          \
      return __builtin_csky_##func##si (a, b, 30);               \
    }                                                          \
  int fio_##func##_si (int a, int b) \
    {                                                          \
      return __builtin_csky_##func##si (a, b, 32);               \
    }                                                          \
  int f_##func##_si (int a, int b, int c) \
    {                                                          \
      return __builtin_csky_##func##si (a, b, c);               \
    }
TEST6(dext)
/* { dg-final { scan-assembler "dexti" } }*/
/* { dg-final { scan-assembler "dext" } }*/
/* { dg-final { scan-assembler "dext" } }*/

#define TEST7(func) \
  int fi_##func##_si (int a) \
    {                                                          \
      return __builtin_csky_##func##si (a, 31);               \
    }                                                          \
  int fib_##func##_si (int a) \
    {                                                          \
      return __builtin_csky_##func##si (a, 32);               \
    }                                                          \
  int fio_##func##_si (int a) \
    {                                                          \
      return __builtin_csky_##func##si (a, 33);               \
    }                                                          \
  int f_##func##_si (int a, int b) \
    {                                                          \
      return __builtin_csky_##func##si (a, b);               \
    }
TEST7(clipu)
/* { dg-final { scan-assembler "clipi\.u32" } }*/
/* { dg-final { scan-assembler "clip\.u32" } }*/
/* { dg-final { scan-assembler "clip\.u32" } }*/
/* { dg-final { scan-assembler "clip\.u32" } }*/
TEST7(clips)
/* { dg-final { scan-assembler "clipi\.s32" } }*/
/* { dg-final { scan-assembler "clipi\.s32" } }*/
/* { dg-final { scan-assembler "clip\.s32" } }*/
/* { dg-final { scan-assembler "clip\.s32" } }*/

#define TEST8(func) \
  __simd32_sat8_t f_##func##_v4qq (__simd32_sat8_t a) \
    {                                                          \
      return __builtin_csky_##func##v4qq (a);               \
    }                                                          \
  __simd32_sat16_t f_##func##_v2hq (__simd32_sat16_t a) \
    {                                                          \
      return __builtin_csky_##func##v2hq (a);               \
    }                                                          \
  long _Sat _Fract f_##func##_sq (long _Sat _Fract a) \
    {                                                          \
      return __builtin_csky_##func##sq (a);               \
    }
TEST8(ssabs)
/* { dg-final { scan-assembler "pabs\.s8\.s" } }*/
/* { dg-final { scan-assembler "pabs\.s16\.s" } }*/
/* { dg-final { scan-assembler "abs\.s32\.s" } }*/
TEST8(ssneg)
/* { dg-final { scan-assembler "pneg\.s8\.s" } }*/
/* { dg-final { scan-assembler "pneg\.s16\.s" } }*/
/* { dg-final { scan-assembler "neg\.s32\.s" } }*/

#define TEST9(func) \
  int f_##func##_si (int a, int b) \
    {                                                          \
      return __builtin_csky_##func##si (a, 13, b, 15);               \
    }
TEST9(pkg)
/* { dg-final { scan-assembler "pkg" } }*/

#define TEST10(func) \
  __simd64_int16_t f_##func##_v4qi (__simd32_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v4qi (a);               \
    }
TEST10(pexts)
/* { dg-final { scan-assembler "pext\.s8\.e" } }*/
TEST10(pextxs)
/* { dg-final { scan-assembler "pextx\.s8\.e" } }*/

#define TEST10_1(func) \
  __simd64_uint16_t f_##func##_v4qi (__simd32_uint8_t a) \
    {                                                          \
      return __builtin_csky_##func##v4qi (a);               \
    }
TEST10_1(pextu)
/* { dg-final { scan-assembler "pext\.u8\.e" } }*/
TEST10_1(pextxu)
/* { dg-final { scan-assembler "pextx\.u8\.e" } }*/

#define TEST11(func) \
  int f_##func##_v4qi (__simd32_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v4qi (a, 2);               \
    } \
  int f_##func##_v2hi (__simd32_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, 1);               \
    }
TEST11(dup)
/* { dg-final { scan-assembler "dup\.8" } }*/
/* { dg-final { scan-assembler "dup\.16" } }*/

#define TEST12(func) \
  __simd32_int16_t fi_##func##_v2hi (__simd32_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, 15);               \
    }                                                          \
  __simd32_int16_t fio_##func##_v2hi (__simd32_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, 16);               \
    }                                                          \
  __simd32_int16_t f_##func##_v2hi (__simd32_int16_t a, int b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST12(pclips)
/* { dg-final { scan-assembler "pclipi\.s16" } }*/
/* { dg-final { scan-assembler "pclip\.s16" } }*/
/* { dg-final { scan-assembler "pclip\.s16" } }*/

#define TEST12_1(func) \
  __simd32_uint16_t fi_##func##_v2hi (__simd32_uint16_t a) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, 15);               \
    }                                                          \
  __simd32_uint16_t fio_##func##_v2hi (__simd32_uint16_t a) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, 16);               \
    }                                                          \
  __simd32_uint16_t f_##func##_v2hi (__simd32_uint16_t a, int b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST12_1(pclipu)
/* { dg-final { scan-assembler "pclipi\.u16" } }*/
/* { dg-final { scan-assembler "pclip\.u16" } }*/
/* { dg-final { scan-assembler "pclip\.u16" } }*/

#define TEST13(func) \
  int f_##func##_v4qi (__simd32_uint8_t a, __simd32_uint8_t b) \
    {                                                          \
      return __builtin_csky_##func##v4qi (a, b);               \
    }
TEST13(psabsa)
/* { dg-final { scan-assembler "psabsa\.u8" } }*/
TEST13(psabsaa)
/* { dg-final { scan-assembler "psabsaa\.u8" } }*/


#define TEST14(func) \
  int f_##func##_v4qi (__simd32_int8_t a, __simd32_int8_t b) \
    {                                                          \
      return __builtin_csky_##func##v4qi (a, b);               \
    }                                                          \
  int f_##func##_v2hi (__simd32_int16_t a, __simd32_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST14(mulaca)
/* { dg-final { scan-assembler "mulaca\.s8" } }*/
/* { dg-final { scan-assembler "mulaca\.s16" } }*/

#define TEST15(func)\
  __simd64_int32_t f_##func##_v2hi (__simd32_int16_t a, __simd32_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST15(pmuls)
/* { dg-final { scan-assembler "pmul\.s16" } }*/
TEST15(pmulxs)
/* { dg-final { scan-assembler "pmulx\.s16" } }*/
TEST15(prmuls)
/* { dg-final { scan-assembler "prmul\.s16" } }*/
TEST15(prmulxs)
/* { dg-final { scan-assembler "prmulx\.s16" } }*/

#define TEST15_1(func)\
  __simd64_uint32_t f_##func##_v2hi (__simd32_uint16_t a, __simd32_uint16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }

TEST15_1(pmulu)
/* { dg-final { scan-assembler "pmul\.u16" } }*/
TEST15_1(pmulxu)
/* { dg-final { scan-assembler "pmulx\.u16" } }*/


#define TEST16(func) \
  int f_##func##_v2hi (__simd32_int16_t a, __simd32_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST16(mulca)
/* { dg-final { scan-assembler "mulca\.s16\.s" } }*/
TEST16(mulcax)
/* { dg-final { scan-assembler "mulcax\.s16\.s" } }*/
TEST16(mulcs)
/* { dg-final { scan-assembler "mulcs\.s16" } }*/
TEST16(mulcsr)
/* { dg-final { scan-assembler "mulcsr\.s16" } }*/
TEST16(mulcsx)
/* { dg-final { scan-assembler "mulcsx\.s16" } }*/
TEST16(mulacax)
/* { dg-final { scan-assembler "mulacax\.s16\.s" } }*/
TEST16(mulacs)
/* { dg-final { scan-assembler "mulacs\.s16\.s" } }*/
TEST16(mulacsr)
/* { dg-final { scan-assembler "mulacsr\.s16\.s" } }*/
TEST16(mulacsx)
/* { dg-final { scan-assembler "mulacsx\.s16\.s" } }*/
TEST16(mulsca)
/* { dg-final { scan-assembler "mulsca\.s16\.s" } }*/
TEST16(mulscax)
/* { dg-final { scan-assembler "mulscax\.s16\.s" } }*/

#define TEST17(func) \
  long long f_##func##_v2hi (__simd32_int16_t a, __simd32_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v2hi (a, b);               \
    }
TEST17(mulacae)
/* { dg-final { scan-assembler "mulaca\.s16\.e" } }*/
TEST17(mulacaxe)
/* { dg-final { scan-assembler "mulacax\.s16\.e" } }*/
TEST17(mulacse)
/* { dg-final { scan-assembler "mulacs\.s16\.e" } }*/
TEST17(mulacsre)
/* { dg-final { scan-assembler "mulacsr\.s16\.e" } }*/
TEST17(mulacsxe)
/* { dg-final { scan-assembler "mulacsx\.s16\.e" } }*/
TEST17(mulscae)
/* { dg-final { scan-assembler "mulsca\.s16\.e" } }*/
TEST17(mulscaxe)
/* { dg-final { scan-assembler "mulscax\.s16\.e" } }*/
