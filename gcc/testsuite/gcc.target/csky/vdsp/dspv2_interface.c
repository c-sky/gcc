/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck803"  { csky-*-* }  { "*" }  { "-mcpu=ck803er*" "-mcpu=ck803efr*" }  }  */
/* { dg-options "-O2" } */
#include <csky_vdsp.h>

#define TEST(func) \
  int8x4_t f_##func##_v4qi (int8x4_t a, int8x4_t b) \
    {                                                          \
      return func##_8 (a, b);               \
    }                                                          \
  int16x2_t f_##func##_v2hi (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_16 (a, b);               \
    }                                                          \
  sat8x4_t f_##func##_v4qq (sat8x4_t a, sat8x4_t b) \
    {                                                          \
      return func##_s8_s (a, b);               \
    }                                                          \
  sat16x2_t f_##func##_v2hq (sat16x2_t a, sat16x2_t b) \
    {                                                          \
      return func##_s16_s (a, b);               \
    }                                                          \
  usat8x4_t f_##func##_v4uqq (usat8x4_t a, usat8x4_t b) \
    {                                                          \
      return func##_u8_s (a, b);               \
    }                                                          \
  usat16x2_t f_##func##_v2uhq (usat16x2_t a, usat16x2_t b) \
    {                                                          \
      return func##_u16_s (a, b);               \
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

#define TEST2(func) \
  int16x2_t f_##func##_v2hi (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_16 (a, b);               \
    }                                                          \
  sat16x2_t f_##func##_v2hq (sat16x2_t a, sat16x2_t b) \
    {                                                          \
      return func##_s16_s (a, b);               \
    }                                                          \
  usat16x2_t f_##func##_v2uhq (usat16x2_t a, usat16x2_t b) \
    {                                                          \
      return func##_u16_s (a, b);               \
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
  int16x2_t f_##func##_v2hi (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }                                                          \
  uint16x2_t f_##func##_v2hiu (uint16x2_t a, uint16x2_t b) \
    {                                                          \
      return func##_u16 (a, b);               \
    }
TEST3(psaxh)
/* { dg-final { scan-assembler "psaxh\.s16" } }*/
/* { dg-final { scan-assembler "psaxh\.u16" } }*/
TEST3(pasxh)
/* { dg-final { scan-assembler "pasxh\.s16" } }*/
/* { dg-final { scan-assembler "pasxh\.u16" } }*/

#define TEST4(func) \
  int8x4_t f_##func##_v4qi (int8x4_t a, int8x4_t b) \
    {                                                          \
      return func##_8 (a, b);               \
    }                                                          \
  int16x2_t f_##func##_v2hi (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_16 (a, b);               \
    }
TEST4(pcmpne)
/* { dg-final { scan-assembler "pcmpne\.8" } }*/
/* { dg-final { scan-assembler "pcmpne\.16" } }*/


#define TEST5(func) \
  int8x4_t f_##func##_v4qi (int8x4_t a, int8x4_t b) \
    {                                                          \
      return func##_s8 (a, b);               \
    }                                                          \
  uint8x4_t f_##func##_v4qiu (uint8x4_t a, uint8x4_t b) \
    {                                                          \
      return func##_u8 (a, b);               \
    }                                         \
  int16x2_t f_##func##_v2hi (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }                                                          \
  uint16x2_t f_##func##_v2hiu (uint16x2_t a, uint16x2_t b) \
    {                                                          \
      return func##_u16 (a, b);               \
    }
TEST5(pcmplt)
/* { dg-final { scan-assembler "pcmplt\.s8" } }*/
/* { dg-final { scan-assembler "pcmplt\.u8" } }*/
/* { dg-final { scan-assembler "pcmplt\.s16" } }*/
/* { dg-final { scan-assembler "pcmplt\.u16" } }*/
TEST5(pcmphs)
/* { dg-final { scan-assembler "pcmphs\.s8" } }*/
/* { dg-final { scan-assembler "pcmphs\.u8" } }*/
/* { dg-final { scan-assembler "pcmphs\.s16" } }*/
/* { dg-final { scan-assembler "pcmphs\.u16" } }*/
TEST5(max)
/* { dg-final { scan-assembler "pmax\.s8" } }*/
/* { dg-final { scan-assembler "pmax\.u8" } }*/
/* { dg-final { scan-assembler "pmax\.s16" } }*/
/* { dg-final { scan-assembler "pmax\.u16" } }*/
TEST5(min)
/* { dg-final { scan-assembler "pmin\.s8" } }*/
/* { dg-final { scan-assembler "pmin\.u8" } }*/
/* { dg-final { scan-assembler "pmin\.s16" } }*/
/* { dg-final { scan-assembler "pmin\.u16" } }*/

#define TEST6(func) \
  int16x4_t f_##func##_v4qi (int8x4_t a) \
    {                                                          \
      return func##_s8_e (a);               \
    }                                                          \
  uint16x4_t f_##func##_v4qiu (uint8x4_t a) \
    {                                                          \
      return func##_u8_e (a);               \
    }
TEST6(pext)
/* { dg-final { scan-assembler "pext\.s8.e" } }*/
/* { dg-final { scan-assembler "pext\.u8.e" } }*/
TEST6(pextx)
/* { dg-final { scan-assembler "pextx\.s8.e" } }*/
/* { dg-final { scan-assembler "pextx\.u8.e" } }*/

#define TEST7(func) \
  int16x2_t f_##func##_v2hi (int16x2_t a, int b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }                                                          \
  uint16x2_t f_##func##_v2hiu (uint16x2_t a, int b) \
    {                                                          \
      return func##_u16 (a, b);               \
    }
TEST7(pclip)
/* { dg-final { scan-assembler "pclip\.s16" } }*/
/* { dg-final { scan-assembler "pclip\.u16" } }*/

#define TEST8(func) \
  int16x2_t f_##func##_v2hi (int16x2_t a) \
    {                                                          \
      return func##_s16 (a, 14);               \
    }                                                          \
  uint16x2_t f_##func##_v2hiu (uint16x2_t a) \
    {                                                          \
      return func##_u16 (a, 14);               \
    }
TEST8(pclipi)
/* { dg-final { scan-assembler "pclipi\.s16" } }*/
/* { dg-final { scan-assembler "pclipi\.u16" } }*/


#define TEST9(func) \
  sat8x4_t f_##func##_v4qq (sat8x4_t a) \
    {                                                          \
      return func##_s8_s (a);               \
    }                                                          \
  sat16x2_t f_##func##_v2hq (sat16x2_t a) \
    {                                                          \
      return func##_s16_s (a);               \
    }
TEST9(pabs)
/* { dg-final { scan-assembler "pabs\.s8\.s" } }*/
/* { dg-final { scan-assembler "pabs\.s16\.s" } }*/
TEST9(pneg)
/* { dg-final { scan-assembler "pneg\.s8\.s" } }*/
/* { dg-final { scan-assembler "pneg\.s16\.s" } }*/

#define TEST10(func)\
  uint32x2_t f_##func##_v2hiu (uint16x2_t a, uint16x2_t b) \
    {                                                          \
      return func##_u16 (a, b);               \
    }                                       \
  int32x2_t f_##func##_v2hi (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }
TEST10(pmul)
/* { dg-final { scan-assembler "pmul\.s16" } }*/
/* { dg-final { scan-assembler "pmul\.u16" } }*/
TEST10(pmulx)
/* { dg-final { scan-assembler "pmulx\.s16" } }*/
/* { dg-final { scan-assembler "pmulx\.u16" } }*/

#define TEST11(func)\
  int32x2_t f_##func##_v2hi (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }
TEST11(prmul)
/* { dg-final { scan-assembler "prmul\.s16" } }*/
TEST11(prmulx)
/* { dg-final { scan-assembler "prmulx\.s16" } }*/

#define TEST12(func)\
  int16x2_t f_##func##_v2hih (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_s16_h (a, b);               \
    }   \
  int16x2_t f_##func##_v2hirh (int16x2_t a, int16x2_t b) \
    {                                                          \
      return func##_s16_rh (a, b);               \
    }
TEST12(prmul)
/* { dg-final { scan-assembler "prmul\.s16\.h" } }*/
/* { dg-final { scan-assembler "prmul\.s16\.rh" } }*/
TEST12(prmulx)
/* { dg-final { scan-assembler "prmulx\.s16\.h" } }*/
/* { dg-final { scan-assembler "prmulx\.s16\.rh" } }*/


#define TEST13(func) \
  unsigned int f_##func##_v4qi (uint8x4_t a, uint8x4_t b) \
    {                                                          \
      return func##_u8 (a, b);               \
    }
TEST13(psabsa)
/* { dg-final { scan-assembler "psabsa\.u8" } }*/
TEST13(psabsaa)
/* { dg-final { scan-assembler "psabsaa\.u8" } }*/

#define TEST14(func) \
  int16x2_t f_##func##_v2hi (int16x2_t a) \
    {                                                          \
      return func##_s16 (a, 13);               \
    }
TEST14(pasri)
/* { dg-final { scan-assembler "pasri\.s16" } }*/
TEST14(plsli)
/* { dg-final { scan-assembler "plsli\.s16" } }*/

#define TEST15(func) \
  int16x2_t f_##func##_v2hi (int16x2_t a, int b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }
TEST15(pasr)
/* { dg-final { scan-assembler "pasr\.s16" } }*/
TEST15(plsl)
/* { dg-final { scan-assembler "plsl\.s16" } }*/

#define TEST16(func) \
  uint16x2_t f_##func##_v2hi (uint16x2_t a) \
    {                                                          \
      return func##_s16 (a, 13);               \
    }

TEST16(plsri)
/* { dg-final { scan-assembler "plsri\.u16" } }*/

#define TEST17(func) \
  uint16x2_t f_##func##_v2hi (uint16x2_t a, int b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }
TEST17(plsr)
/* { dg-final { scan-assembler "plsr\.u16" } }*/

#define TEST18(func) \
  sat16x2_t f_##func##_v2hq (sat16x2_t a) \
    {                                                          \
      return func##_s16_s (a, 13);               \
    }
TEST18(plsli)
/* { dg-final { scan-assembler "plsli\.s16\.s" } }*/

#define TEST19(func) \
  sat16x2_t f_##func##_v2hq (sat16x2_t a, int b) \
    {                                                          \
      return func##_s16_s (a, b);               \
    }
TEST19(plsl)
/* { dg-final { scan-assembler "plsl\.s16\.s" } }*/

#define TEST20(func) \
  usat16x2_t f_##func##_v2uhq (usat16x2_t a) \
    {                                                          \
      return func##_u16_s (a, 13);               \
    }
TEST20(plsli)
/* { dg-final { scan-assembler "plsli\.u16\.s" } }*/

#define TEST21(func) \
  usat16x2_t f_##func##_v2uhq (usat16x2_t a, int b) \
    {                                                          \
      return func##_u16_s (a, b);               \
    }
TEST21(plsl)
/* { dg-final { scan-assembler "plsl\.u16\.s" } }*/
