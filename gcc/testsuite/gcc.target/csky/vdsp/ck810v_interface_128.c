/* { dg-do compile } */
/* { dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options "-O2 -mvdsp-width=128" } */

#include <csky_vdsp.h>

#define TEST(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_s8 (a);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a) \
    {                                                          \
      return func##_s16 (a);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a) \
    {                                                          \
      return func##_s32 (a);               \
    }                                                          \
  sat8x16_t f_##func##_v16qq (sat8x16_t a) \
    {                                                          \
      return func##_s8_s (a);               \
    }                                                          \
  sat16x8_t f_##func##_v8hq (sat16x8_t a) \
    {                                                          \
      return func##_s16_s (a);               \
    }                                                          \
  sat32x4_t f_##func##_v4sq (sat32x4_t a) \
    {                                                          \
      return func##_s32_s (a);               \
    }
TEST(vabs)
/* { dg-final { scan-assembler "vabs\.s8" } }*/
/* { dg-final { scan-assembler "vabs\.s16" } }*/
/* { dg-final { scan-assembler "vabs\.s32" } }*/
/* { dg-final { scan-assembler "vabs\.s8.s" } }*/
/* { dg-final { scan-assembler "vabs\.s16.s" } }*/
/* { dg-final { scan-assembler "vabs\.s32.s" } }*/
TEST(vneg)
/* { dg-final { scan-assembler "vneg\.s8" } }*/
/* { dg-final { scan-assembler "vneg\.s16" } }*/
/* { dg-final { scan-assembler "vneg\.s32" } }*/
/* { dg-final { scan-assembler "vneg\.s8.s" } }*/
/* { dg-final { scan-assembler "vneg\.s16.s" } }*/
/* { dg-final { scan-assembler "vneg\.s32.s" } }*/

#define TEST2(func) \
  int16x8_t f_##func##_v16qise (int8x16_t a, int8x16_t b) \
    {                                                          \
      return func##_es8 (a, b);               \
    }                                                          \
  uint16x8_t f_##func##_v16qiue (uint8x16_t a, uint8x16_t b) \
    {                                                          \
      return func##_eu8 (a, b);               \
    }   \
  int32x4_t f_##func##_v8hise (int16x8_t a, int16x8_t b) \
    {                                                          \
      return func##_es16 (a, b);               \
    }                                                          \
  uint32x4_t f_##func##_v8hiue (uint16x8_t a, uint16x8_t b) \
    {                                                          \
      return func##_eu16 (a, b);               \
    }
TEST2(vadd)
/* { dg-final { scan-assembler "vadd\.es8" } }*/
/* { dg-final { scan-assembler "vadd\.eu8" } }*/
/* { dg-final { scan-assembler "vadd\.es16" } }*/
/* { dg-final { scan-assembler "vadd\.eu16" } }*/
TEST2(vsub)
/* { dg-final { scan-assembler "vsub\.es8" } }*/
/* { dg-final { scan-assembler "vsub\.eu8" } }*/
/* { dg-final { scan-assembler "vsub\.es16" } }*/
/* { dg-final { scan-assembler "vsub\.eu16" } }*/
TEST2(vcadd)
/* { dg-final { scan-assembler "vcadd\.eu8" } }*/
/* { dg-final { scan-assembler "vcadd\.es8" } }*/
/* { dg-final { scan-assembler "vcadd\.eu16" } }*/
/* { dg-final { scan-assembler "vcadd\.es16" } }*/
TEST2(vmul)
/* { dg-final { scan-assembler "vmul\.es8" } }*/
/* { dg-final { scan-assembler "vmul\.eu8" } }*/
/* { dg-final { scan-assembler "vmul\.es16" } }*/
/* { dg-final { scan-assembler "vmul\.eu16" } }*/
TEST2(vsabs)
/* { dg-final { scan-assembler "vsabs\.es8" } }*/
/* { dg-final { scan-assembler "vsabs\.eu8" } }*/
/* { dg-final { scan-assembler "vsabs\.es16" } }*/
/* { dg-final { scan-assembler "vsabs\.eu16" } }*/

#define TEST3(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a, int8x16_t b) \
    {                                                          \
      return func##_s8 (a, b);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a, int16x8_t b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a, int32x4_t b) \
    {                                                          \
      return func##_s32 (a, b);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiu (uint8x16_t a, uint8x16_t b) \
    {                                                          \
      return func##_u8 (a, b);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiu (uint16x8_t a, uint16x8_t b) \
    {                                                          \
      return func##_u16 (a, b);               \
    }                                                          \
  uint32x4_t f_##func##_v4siu (uint32x4_t a, uint32x4_t b) \
    {                                                          \
      return func##_u32 (a, b);               \
    }                                                          \
  sat8x16_t f_##func##_v16qq (sat8x16_t a, sat8x16_t b) \
    {                                                          \
      return func##_s8_s (a, b);               \
    }                                                          \
  sat16x8_t f_##func##_v8hq (sat16x8_t a, sat16x8_t b) \
    {                                                          \
      return func##_s16_s (a, b);               \
    }                                                          \
  sat32x4_t f_##func##_v4sq (sat32x4_t a, sat32x4_t b) \
    {                                                          \
      return func##_s32_s (a, b);               \
    }                                                          \
  usat8x16_t f_##func##_v16uqq (usat8x16_t a, usat8x16_t b) \
    {                                                          \
      return func##_u8_s (a, b);               \
    }                                                          \
  usat16x8_t f_##func##_v8uhq (usat16x8_t a, usat16x8_t b) \
    {                                                          \
      return func##_u16_s (a, b);               \
    }                                                          \
  usat32x4_t f_##func##_v4usq (usat32x4_t a, usat32x4_t b) \
    {                                                          \
      return func##_u32_s (a, b);               \
    }
TEST3(vadd)
/* { dg-final { scan-assembler "vadd\.u8" } }*/
/* { dg-final { scan-assembler "vadd\.u16" } }*/
/* { dg-final { scan-assembler "vadd\.u32" } }*/
/* { dg-final { scan-assembler "vadd\.u8" } }*/
/* { dg-final { scan-assembler "vadd\.u16" } }*/
/* { dg-final { scan-assembler "vadd\.u32" } }*/
/* { dg-final { scan-assembler "vadd\.s8.s" } }*/
/* { dg-final { scan-assembler "vadd\.s16.s" } }*/
/* { dg-final { scan-assembler "vadd\.s32.s" } }*/
/* { dg-final { scan-assembler "vadd\.u8.s" } }*/
/* { dg-final { scan-assembler "vadd\.u16.s" } }*/
/* { dg-final { scan-assembler "vadd\.u32.s" } }*/
TEST3(vsub)
/* { dg-final { scan-assembler "vsub\.u8" } }*/
/* { dg-final { scan-assembler "vsub\.u16" } }*/
/* { dg-final { scan-assembler "vsub\.u32" } }*/
/* { dg-final { scan-assembler "vsub\.u8" } }*/
/* { dg-final { scan-assembler "vsub\.u16" } }*/
/* { dg-final { scan-assembler "vsub\.u32" } }*/
/* { dg-final { scan-assembler "vsub\.s8.s" } }*/
/* { dg-final { scan-assembler "vsub\.s16.s" } }*/
/* { dg-final { scan-assembler "vsub\.s32.s" } }*/
/* { dg-final { scan-assembler "vsub\.u8.s" } }*/
/* { dg-final { scan-assembler "vsub\.u16.s" } }*/
/* { dg-final { scan-assembler "vsub\.u32.s" } }*/
TEST3(vshl)
/* { dg-final { scan-assembler "vshl\.s8" } }*/
/* { dg-final { scan-assembler "vshl\.s16" } }*/
/* { dg-final { scan-assembler "vshl\.s32" } }*/
/* { dg-final { scan-assembler "vshl\.u8" } }*/
/* { dg-final { scan-assembler "vshl\.u16" } }*/
/* { dg-final { scan-assembler "vshl\.u32" } }*/
/* { dg-final { scan-assembler "vshl\.s8.s" } }*/
/* { dg-final { scan-assembler "vshl\.s16.s" } }*/
/* { dg-final { scan-assembler "vshl\.s32.s" } }*/
/* { dg-final { scan-assembler "vshl\.u8.s" } }*/
/* { dg-final { scan-assembler "vshl\.u16.s" } }*/
/* { dg-final { scan-assembler "vshl\.u32.s" } }*/


#define TEST4(func) \
  uint16x8_t f_##func##_v8hixu (uint8x16_t a, uint16x8_t b) \
    {                                                          \
      return func##_xu16 (a, b);               \
    }                                                          \
  uint32x4_t f_##func##_v4sixu (uint16x8_t a, uint32x4_t b) \
    {                                                          \
      return func##_xu32 (a, b);               \
    }   \
  int16x8_t f_##func##_v8hix (int8x16_t a, int16x8_t b) \
    {                                                          \
      return func##_xs16 (a, b);               \
    }                                                          \
  int32x4_t f_##func##_v4six (int16x8_t a, int32x4_t b) \
    {                                                          \
      return func##_xs32 (a, b);               \
    }
TEST4(vadd)
/* { dg-final { scan-assembler "vadd\.xu16" } }*/
/* { dg-final { scan-assembler "vadd\.xu32" } }*/
/* { dg-final { scan-assembler "vadd\.xs16" } }*/
/* { dg-final { scan-assembler "vadd\.xs32" } }*/
TEST4(vsub)
/* { dg-final { scan-assembler "vsub\.xu16" } }*/
/* { dg-final { scan-assembler "vsub\.xu32" } }*/
/* { dg-final { scan-assembler "vsub\.xs16" } }*/
/* { dg-final { scan-assembler "vsub\.xs32" } }*/

#define TEST5(func) \
  uint8x16_t f_##func##_v8hixusl (uint8x16_t a, uint16x8_t b) \
    {                                                          \
      return func##_xu16_sl (a, b);               \
    }                                                          \
  uint16x8_t f_##func##_v4sixusl (uint16x8_t a, uint32x4_t b) \
    {                                                          \
      return func##_xu32_sl (a, b);               \
    }   \
  int8x16_t f_##func##_v8hixsl (int8x16_t a, int16x8_t b) \
    {                                                          \
      return func##_xs16_sl (a, b);               \
    }                                                          \
  int16x8_t f_##func##_v4sixsl (int16x8_t a, int32x4_t b) \
    {                                                          \
      return func##_xs32_sl (a, b);               \
    }
TEST5(vadd)
/* { dg-final { scan-assembler "vadd\.xu16\.sl" } }*/
/* { dg-final { scan-assembler "vadd\.xu32\.sl" } }*/
/* { dg-final { scan-assembler "vadd\.xs16\.sl" } }*/
/* { dg-final { scan-assembler "vadd\.xs32\.sl" } }*/

#define TEST6(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a, int8x16_t b) \
    {                                                          \
      return func##_s8 (a, b);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a, int16x8_t b) \
    {                                                          \
      return func##_s16 (a, b);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a, int32x4_t b) \
    {                                                          \
      return func##_s32 (a, b);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiu (uint8x16_t a, uint8x16_t b) \
    {                                                          \
      return func##_u8 (a, b);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiu (uint16x8_t a, uint16x8_t b) \
    {                                                          \
      return func##_u16 (a, b);               \
    }                                                          \
  uint32x4_t f_##func##_v4siu (uint32x4_t a, uint32x4_t b) \
    {                                                          \
      return func##_u32 (a, b);               \
    }
TEST6(vaddh)
/* { dg-final { scan-assembler "vaddh\.s8" } }*/
/* { dg-final { scan-assembler "vaddh\.s16" } }*/
/* { dg-final { scan-assembler "vaddh\.s32" } }*/
/* { dg-final { scan-assembler "vaddh\.u8" } }*/
/* { dg-final { scan-assembler "vaddh\.u16" } }*/
/* { dg-final { scan-assembler "vaddh\.u32" } }*/
TEST6(vsubh)
/* { dg-final { scan-assembler "vsubh\.s8" } }*/
/* { dg-final { scan-assembler "vsubh\.s16" } }*/
/* { dg-final { scan-assembler "vsubh\.s32" } }*/
/* { dg-final { scan-assembler "vsubh\.u8" } }*/
/* { dg-final { scan-assembler "vsubh\.u16" } }*/
/* { dg-final { scan-assembler "vsubh\.u32" } }*/
TEST6(vcadd)
/* { dg-final { scan-assembler "vcadd\.s8" } }*/
/* { dg-final { scan-assembler "vcadd\.s16" } }*/
/* { dg-final { scan-assembler "vcadd\.s32" } }*/
/* { dg-final { scan-assembler "vcadd\.u8" } }*/
/* { dg-final { scan-assembler "vcadd\.u16" } }*/
/* { dg-final { scan-assembler "vcadd\.u32" } }*/
TEST6(vcmax)
/* { dg-final { scan-assembler "vcmax\.s8" } }*/
/* { dg-final { scan-assembler "vcmax\.s16" } }*/
/* { dg-final { scan-assembler "vcmax\.s32" } }*/
/* { dg-final { scan-assembler "vcmax\.u8" } }*/
/* { dg-final { scan-assembler "vcmax\.u16" } }*/
/* { dg-final { scan-assembler "vcmax\.u32" } }*/
TEST6(vcmin)
/* { dg-final { scan-assembler "vcmin\.s8" } }*/
/* { dg-final { scan-assembler "vcmin\.s16" } }*/
/* { dg-final { scan-assembler "vcmin\.s32" } }*/
/* { dg-final { scan-assembler "vcmin\.u8" } }*/
/* { dg-final { scan-assembler "vcmin\.u16" } }*/
/* { dg-final { scan-assembler "vcmin\.u32" } }*/
TEST6(vcmphs)
/* { dg-final { scan-assembler "vcmphs\.s8" } }*/
/* { dg-final { scan-assembler "vcmphs\.s16" } }*/
/* { dg-final { scan-assembler "vcmphs\.s32" } }*/
/* { dg-final { scan-assembler "vcmphs\.u8" } }*/
/* { dg-final { scan-assembler "vcmphs\.u16" } }*/
/* { dg-final { scan-assembler "vcmphs\.u32" } }*/
TEST6(vcmplt)
/* { dg-final { scan-assembler "vcmplt\.s8" } }*/
/* { dg-final { scan-assembler "vcmplt\.s16" } }*/
/* { dg-final { scan-assembler "vcmplt\.s32" } }*/
/* { dg-final { scan-assembler "vcmplt\.u8" } }*/
/* { dg-final { scan-assembler "vcmplt\.u16" } }*/
/* { dg-final { scan-assembler "vcmplt\.u32" } }*/
TEST6(vcmpne)
/* { dg-final { scan-assembler "vcmpne\.s8" } }*/
/* { dg-final { scan-assembler "vcmpne\.s16" } }*/
/* { dg-final { scan-assembler "vcmpne\.s32" } }*/
/* { dg-final { scan-assembler "vcmpne\.u8" } }*/
/* { dg-final { scan-assembler "vcmpne\.u16" } }*/
/* { dg-final { scan-assembler "vcmpne\.u32" } }*/
TEST6(vmax)
/* { dg-final { scan-assembler "vmax\.s8" } }*/
/* { dg-final { scan-assembler "vmax\.s16" } }*/
/* { dg-final { scan-assembler "vmax\.s32" } }*/
/* { dg-final { scan-assembler "vmax\.u8" } }*/
/* { dg-final { scan-assembler "vmax\.u16" } }*/
/* { dg-final { scan-assembler "vmax\.u32" } }*/
TEST6(vmin)
/* { dg-final { scan-assembler "vmin\.s8" } }*/
/* { dg-final { scan-assembler "vmin\.s16" } }*/
/* { dg-final { scan-assembler "vmin\.s32" } }*/
/* { dg-final { scan-assembler "vmin\.u8" } }*/
/* { dg-final { scan-assembler "vmin\.u16" } }*/
/* { dg-final { scan-assembler "vmin\.u32" } }*/
TEST6(vmul)
/* { dg-final { scan-assembler "vmul\.u8" } }*/
/* { dg-final { scan-assembler "vmul\.u16" } }*/
/* { dg-final { scan-assembler "vmul\.u32" } }*/
/* { dg-final { scan-assembler "vmul\.u8" } }*/
/* { dg-final { scan-assembler "vmul\.u16" } }*/
/* { dg-final { scan-assembler "vmul\.u32" } }*/
TEST6(vsabs)
/* { dg-final { scan-assembler "vsabs\.s8" } }*/
/* { dg-final { scan-assembler "vsabs\.s16" } }*/
/* { dg-final { scan-assembler "vsabs\.s32" } }*/
/* { dg-final { scan-assembler "vsabs\.u8" } }*/
/* { dg-final { scan-assembler "vsabs\.u16" } }*/
/* { dg-final { scan-assembler "vsabs\.u32" } }*/
TEST6(vshr)
/* { dg-final { scan-assembler "vshr\.s8" } }*/
/* { dg-final { scan-assembler "vshr\.s16" } }*/
/* { dg-final { scan-assembler "vshr\.s32" } }*/
/* { dg-final { scan-assembler "vshr\.u8" } }*/
/* { dg-final { scan-assembler "vshr\.u16" } }*/
/* { dg-final { scan-assembler "vshr\.u32" } }*/

#define TEST7(func) \
  int8x16_t f_##func##_v16qir (int8x16_t a, int8x16_t b) \
    {                                                          \
      return func##_s8_r (a, b);               \
    }                                                          \
  int16x8_t f_##func##_v8hir (int16x8_t a, int16x8_t b) \
    {                                                          \
      return func##_s16_r (a, b);               \
    }                                                          \
  int32x4_t f_##func##_v4sir (int32x4_t a, int32x4_t b) \
    {                                                          \
      return func##_s32_r (a, b);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiur (uint8x16_t a, uint8x16_t b) \
    {                                                          \
      return func##_u8_r (a, b);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiur (uint16x8_t a, uint16x8_t b) \
    {                                                          \
      return func##_u16_r (a, b);               \
    }                                                          \
  uint32x4_t f_##func##_v4siur (uint32x4_t a, uint32x4_t b) \
    {                                                          \
      return func##_u32_r (a, b);               \
    }
TEST7(vaddh)
/* { dg-final { scan-assembler "vaddh\.s8.r" } }*/
/* { dg-final { scan-assembler "vaddh\.s16.r" } }*/
/* { dg-final { scan-assembler "vaddh\.s32.r" } }*/
/* { dg-final { scan-assembler "vaddh\.u8.r" } }*/
/* { dg-final { scan-assembler "vaddh\.u16.r" } }*/
/* { dg-final { scan-assembler "vaddh\.u32.r" } }*/
TEST7(vsubh)
/* { dg-final { scan-assembler "vsubh\.s8.r" } }*/
/* { dg-final { scan-assembler "vsubh\.s16.r" } }*/
/* { dg-final { scan-assembler "vsubh\.s32.r" } }*/
/* { dg-final { scan-assembler "vsubh\.u8.r" } }*/
/* { dg-final { scan-assembler "vsubh\.u16.r" } }*/
/* { dg-final { scan-assembler "vsubh\.u32.r" } }*/

#define TEST8(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a, int8x16_t b) \
    {                                                          \
      return func##_8 (a, b);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a, int16x8_t b) \
    {                                                          \
      return func##_16 (a, b);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a, int32x4_t b) \
    {                                                          \
      return func##_32 (a, b);               \
    }
TEST8(vand)
/* { dg-final { scan-assembler "vand\.8" } }*/
/* { dg-final { scan-assembler "vand\.16" } }*/
/* { dg-final { scan-assembler "vand\.32" } }*/
TEST8(vor)
/* { dg-final { scan-assembler "vor\.8" } }*/
/* { dg-final { scan-assembler "vor\.16" } }*/
/* { dg-final { scan-assembler "vor\.32" } }*/
TEST8(vandn)
/* { dg-final { scan-assembler "vandn\.8" } }*/
/* { dg-final { scan-assembler "vandn\.16" } }*/
/* { dg-final { scan-assembler "vandn\.32" } }*/
TEST8(vdch)
/* { dg-final { scan-assembler "vdch\.8" } }*/
/* { dg-final { scan-assembler "vdch\.16" } }*/
/* { dg-final { scan-assembler "vdch\.32" } }*/
TEST8(vdcl)
/* { dg-final { scan-assembler "vdcl\.8" } }*/
/* { dg-final { scan-assembler "vdcl\.16" } }*/
/* { dg-final { scan-assembler "vdcl\.32" } }*/
TEST8(vich)
/* { dg-final { scan-assembler "vich\.8" } }*/
/* { dg-final { scan-assembler "vich\.16" } }*/
/* { dg-final { scan-assembler "vich\.32" } }*/
TEST8(vicl)
/* { dg-final { scan-assembler "vicl\.8" } }*/
/* { dg-final { scan-assembler "vicl\.16" } }*/
/* { dg-final { scan-assembler "vicl\.32" } }*/
TEST8(vtrch)
/* { dg-final { scan-assembler "vtrch\.8" } }*/
/* { dg-final { scan-assembler "vtrch\.16" } }*/
/* { dg-final { scan-assembler "vtrch\.32" } }*/
TEST8(vtrcl)
/* { dg-final { scan-assembler "vtrcl\.8" } }*/
/* { dg-final { scan-assembler "vtrcl\.16" } }*/
/* { dg-final { scan-assembler "vtrcl\.32" } }*/
TEST8(vtst)
/* { dg-final { scan-assembler "vtst\.8" } }*/
/* { dg-final { scan-assembler "vtst\.16" } }*/
/* { dg-final { scan-assembler "vtst\.32" } }*/

#define TEST9(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a, int8x16_t b) \
    {                                                          \
      return func##_8 (a, b);               \
    }
TEST9(vbperm)
/* { dg-final { scan-assembler "vbperm\.8" } }*/
TEST9(vbpermz)
/* { dg-final { scan-assembler "vbpermz\.8" } }*/

#define TEST10(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_s8 (a);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a) \
    {                                                          \
      return func##_s16 (a);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a) \
    {                                                          \
      return func##_s32 (a);               \
    }
TEST10(vcls)
/* { dg-final { scan-assembler "vcls\.s8" } }*/
/* { dg-final { scan-assembler "vcls\.s16" } }*/
/* { dg-final { scan-assembler "vcls\.s32" } }*/

#define TEST11(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_8 (a);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a) \
    {                                                          \
      return func##_16 (a);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a) \
    {                                                          \
      return func##_32 (a);               \
    }
TEST11(vclz)
/* { dg-final { scan-assembler "vclz\.8" } }*/
/* { dg-final { scan-assembler "vclz\.16" } }*/
/* { dg-final { scan-assembler "vclz\.32" } }*/
TEST11(vrev)
/* { dg-final { scan-assembler "vrev\.8" } }*/
/* { dg-final { scan-assembler "vrev\.16" } }*/
/* { dg-final { scan-assembler "vrev\.32" } }*/

#define TEST12(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_s8 (a);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a) \
    {                                                          \
      return func##_s16 (a);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a) \
    {                                                          \
      return func##_s32 (a);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiu (uint8x16_t a) \
    {                                                          \
      return func##_u8 (a);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiu (uint16x8_t a) \
    {                                                          \
      return func##_u16 (a);               \
    }                                                          \
  uint32x4_t f_##func##_v4siu (uint32x4_t a) \
    {                                                          \
      return func##_u32 (a);               \
    }
TEST12(vcmphsz)
/* { dg-final { scan-assembler "vcmphsz\.s8" } }*/
/* { dg-final { scan-assembler "vcmphsz\.s16" } }*/
/* { dg-final { scan-assembler "vcmphsz\.s32" } }*/
/* { dg-final { scan-assembler "vcmphsz\.u8" } }*/
/* { dg-final { scan-assembler "vcmphsz\.u16" } }*/
/* { dg-final { scan-assembler "vcmphsz\.u32" } }*/
TEST12(vcmpltz)
/* { dg-final { scan-assembler "vcmpltz\.s8" } }*/
/* { dg-final { scan-assembler "vcmpltz\.s16" } }*/
/* { dg-final { scan-assembler "vcmpltz\.s32" } }*/
/* { dg-final { scan-assembler "vcmpltz\.u8" } }*/
/* { dg-final { scan-assembler "vcmpltz\.u16" } }*/
/* { dg-final { scan-assembler "vcmpltz\.u32" } }*/
TEST12(vcmpnez)
/* { dg-final { scan-assembler "vcmpnez\.s8" } }*/
/* { dg-final { scan-assembler "vcmpnez\.s16" } }*/
/* { dg-final { scan-assembler "vcmpnez\.s32" } }*/
/* { dg-final { scan-assembler "vcmpnez\.u8" } }*/
/* { dg-final { scan-assembler "vcmpnez\.u16" } }*/
/* { dg-final { scan-assembler "vcmpnez\.u32" } }*/

#define TEST13(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_8 (a);               \
    }
TEST13(vcnt1)
/* { dg-final { scan-assembler "vcnt1\.8" } }*/


#define TEST14(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_8 (a, 15);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a) \
    {                                                          \
      return func##_16 (a, 7);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a) \
    {                                                          \
      return func##_32 (a, 3);               \
    }
TEST14(vdup)
/* { dg-final { scan-assembler "vdup\.8" } }*/
/* { dg-final { scan-assembler "vdup\.16" } }*/
/* { dg-final { scan-assembler "vdup\.32" } }*/

#define TEST15(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_8 (15, a, 15);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a) \
    {                                                          \
      return func##_16 (7, a, 7);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a) \
    {                                                          \
      return func##_32 (3, a, 3);               \
    }
TEST15(vins)
/* { dg-final { scan-assembler "vins\.8" } }*/
/* { dg-final { scan-assembler "vins\.16" } }*/
/* { dg-final { scan-assembler "vins\.32" } }*/

#define TEST16(func) \
  int8x16_t f_##func##_v16qi (int a) \
    {                                                          \
      return func##_8 (a, 2032);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int a) \
    {                                                          \
      return func##_16 (a, 2032);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int a) \
    {                                                          \
      return func##_32 (a, 2032);               \
    }
TEST16(vldd)
/* { dg-final { scan-assembler "vldd\.8" } }*/
/* { dg-final { scan-assembler "vldd\.16" } }*/
/* { dg-final { scan-assembler "vldd\.32" } }*/
TEST16(vldq)
/* { dg-final { scan-assembler "vldq\.8" } }*/
/* { dg-final { scan-assembler "vldq\.16" } }*/
/* { dg-final { scan-assembler "vldq\.32" } }*/
TEST16(vstd)
/* { dg-final { scan-assembler "vstd\.8" } }*/
/* { dg-final { scan-assembler "vstd\.16" } }*/
/* { dg-final { scan-assembler "vstd\.32" } }*/
TEST16(vstq)
/* { dg-final { scan-assembler "vstq\.8" } }*/
/* { dg-final { scan-assembler "vstq\.16" } }*/
/* { dg-final { scan-assembler "vstq\.32" } }*/

#define TEST17(func) \
  int8x16_t f_##func##_v16qi (int a, int b) \
    {                                                          \
      return func##_8 (a, b, 1);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int a, int b) \
    {                                                          \
      return func##_16 (a, b, 2);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int a, int b) \
    {                                                          \
      return func##_32 (a, b, 3);               \
    }
TEST17(vldrd)
/* { dg-final { scan-assembler "vldrd\.8" } }*/
/* { dg-final { scan-assembler "vldrd\.16" } }*/
/* { dg-final { scan-assembler "vldrd\.32" } }*/
TEST17(vldrq)
/* { dg-final { scan-assembler "vldrq\.8" } }*/
/* { dg-final { scan-assembler "vldrq\.16" } }*/
/* { dg-final { scan-assembler "vldrq\.32" } }*/
TEST17(vstrd)
/* { dg-final { scan-assembler "vstrd\.8" } }*/
/* { dg-final { scan-assembler "vstrd\.16" } }*/
/* { dg-final { scan-assembler "vstrd\.32" } }*/
TEST17(vstrq)
/* { dg-final { scan-assembler "vstrq\.8" } }*/
/* { dg-final { scan-assembler "vstrq\.16" } }*/
/* { dg-final { scan-assembler "vstrq\.32" } }*/

#define TEST18(func) \
  unsigned char f_##func##_v16qi (uint8x16_t a) \
    {                                                          \
      return func##_u8 (a, 15);               \
    }                                                          \
  unsigned short f_##func##_v8hi (uint16x8_t a) \
    {                                                          \
      return func##_u16 (a, 7);               \
    }                                                          \
  unsigned int f_##func##_v4si (uint32x4_t a) \
    {                                                          \
      return func##_u32 (a, 3);               \
    } \
  char f_##func##_v16qis (int8x16_t a) \
    {                                                          \
      return func##_s8 (a, 15);               \
    }                                                          \
  short f_##func##_v8his (int16x8_t a) \
    {                                                          \
      return func##_s16 (a, 7);               \
    }
TEST18(vmfvr)
/* { dg-final { scan-assembler "vmfvr\.u8" } }*/
/* { dg-final { scan-assembler "vmfvr\.u16" } }*/
/* { dg-final { scan-assembler "vmfvr\.u32" } }*/
/* { dg-final { scan-assembler "vmfvr\.s8" } }*/
/* { dg-final { scan-assembler "vmfvr\.s16" } }*/


#define TEST19(func) \
  uint8x16_t f_##func##_v16qi (unsigned char a) \
    {                                                          \
      return __builtin_csky_##func##v16qi (15, a);               \
    }                                                          \
  uint16x8_t f_##func##_v8hi (unsigned short a) \
    {                                                          \
      return __builtin_csky_##func##v8hi (7, a);               \
    }                                                          \
  uint32x4_t f_##func##_v4si (unsigned int a) \
    {                                                          \
      return __builtin_csky_##func##v4si (3, a);               \
    }
TEST19(vmtvru)
/* { dg-final { scan-assembler "vmtvr\.u8" } }*/
/* { dg-final { scan-assembler "vmtvr\.u16" } }*/
/* { dg-final { scan-assembler "vmtvr\.u32" } }*/

#define TEST20(func) \
  int16x8_t f_##func##_v16qise (int8x16_t a) \
    {                                                          \
      return func##_es8 (a);               \
    }                                                          \
  uint16x8_t f_##func##_v16qiue (uint8x16_t a) \
    {                                                          \
      return func##_eu8 (a);               \
    }   \
  int32x4_t f_##func##_v8hise (int16x8_t a) \
    {                                                          \
      return func##_es16 (a);               \
    }                                                          \
  uint32x4_t f_##func##_v8hiue (uint16x8_t a) \
    {                                                          \
      return func##_eu16 (a);               \
    }
TEST20(vmov)
/* { dg-final { scan-assembler "vmov\.es8" } }*/
/* { dg-final { scan-assembler "vmov\.eu8" } }*/
/* { dg-final { scan-assembler "vmov\.es16" } }*/
/* { dg-final { scan-assembler "vmov\.eu16" } }*/

#define TEST21(func, type) \
  uint8x16_t f_##func##_v8hiu##type (uint16x8_t a) \
    {                                                          \
      return func##_u16_##type (a);               \
    }                                                          \
  uint16x8_t f_##func##_v4siu##type (uint32x4_t a) \
    {                                                          \
      return func##_u32_##type (a);               \
    } \
  int8x16_t f_##func##_v8his##type (int16x8_t a) \
    {                                                          \
      return func##_s16_##type (a);               \
    }                                                          \
  int16x8_t f_##func##_v4sis##type (int32x4_t a) \
    {                                                          \
      return func##_s32_##type (a);               \
    }
TEST21(vmov, h)
/* { dg-final { scan-assembler "vmov\.u16\.h" } }*/
/* { dg-final { scan-assembler "vmov\.u32\.h" } }*/
/* { dg-final { scan-assembler "vmov\.s16\.h" } }*/
/* { dg-final { scan-assembler "vmov\.s32\.h" } }*/
TEST21(vmov, l)
/* { dg-final { scan-assembler "vmov\.u16\.l" } }*/
/* { dg-final { scan-assembler "vmov\.u32\.l" } }*/
/* { dg-final { scan-assembler "vmov\.s16\.l" } }*/
/* { dg-final { scan-assembler "vmov\.s32\.l" } }*/
TEST21(vmov, rh)
/* { dg-final { scan-assembler "vmov\.u16\.rh" } }*/
/* { dg-final { scan-assembler "vmov\.u32\.rh" } }*/
/* { dg-final { scan-assembler "vmov\.s16\.rh" } }*/
/* { dg-final { scan-assembler "vmov\.s32\.rh" } }*/
TEST21(vmov, sl)
/* { dg-final { scan-assembler "vmov\.u16\.sl" } }*/
/* { dg-final { scan-assembler "vmov\.u32\.sl" } }*/
/* { dg-final { scan-assembler "vmov\.s16\.sl" } }*/
/* { dg-final { scan-assembler "vmov\.s32\.sl" } }*/

#define TEST22(func) \
  uint16x8_t f_##func##_v16qiu (uint8x16_t a, uint8x16_t b, uint16x8_t c) \
    {                                                          \
      return func##_eu8 (a, b, c);               \
    }                                                          \
  uint32x4_t f_##func##_v8hiu (uint16x8_t a, uint16x8_t b, uint32x4_t c) \
    {                                                          \
      return func##_eu16 (a, b, c);               \
    } \
  int16x8_t f_##func##_v16qis (int8x16_t a, int8x16_t b, int16x8_t c) \
    {                                                          \
      return func##_es8 (a, b, c);               \
    }                                                          \
  int32x4_t f_##func##_v8hi (int16x8_t a, int16x8_t b, int32x4_t c) \
    {                                                          \
      return func##_es16 (a, b, c);               \
    }
TEST22(vmula)
/* { dg-final { scan-assembler "vmula\.eu8" } }*/
/* { dg-final { scan-assembler "vmula\.eu16" } }*/
/* { dg-final { scan-assembler "vmula\.es8" } }*/
/* { dg-final { scan-assembler "vmula\.es16" } }*/
TEST22(vmuls)
/* { dg-final { scan-assembler "vmuls\.eu8" } }*/
/* { dg-final { scan-assembler "vmuls\.eu16" } }*/
/* { dg-final { scan-assembler "vmuls\.es8" } }*/
/* { dg-final { scan-assembler "vmuls\.es16" } }*/
TEST22(vsabsa)
/* { dg-final { scan-assembler "vsabsa\.eu8" } }*/
/* { dg-final { scan-assembler "vsabsa\.eu16" } }*/
/* { dg-final { scan-assembler "vsabsa\.es8" } }*/
/* { dg-final { scan-assembler "vsabsa\.es16" } }*/

#define TEST23(func) \
  int8x16_t f_##func##_v16qir (int8x16_t a, int8x16_t b, int8x16_t c) \
    {                                                          \
      return func##_s8 (a, b, c);               \
    }                                                          \
  int16x8_t f_##func##_v8hir (int16x8_t a, int16x8_t b, int16x8_t c) \
    {                                                          \
      return func##_s16 (a, b, c);               \
    }                                                          \
  int32x4_t f_##func##_v4sir (int32x4_t a, int32x4_t b, int32x4_t c) \
    {                                                          \
      return func##_s32 (a, b, c);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiur (uint8x16_t a, uint8x16_t b, uint8x16_t c) \
    {                                                          \
      return func##_u8 (a, b, c);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiur (uint16x8_t a, uint16x8_t b, uint16x8_t c) \
    {                                                          \
      return func##_u16 (a, b, c);               \
    }                                                          \
  uint32x4_t f_##func##_v4siur (uint32x4_t a, uint32x4_t b, uint32x4_t c) \
    {                                                          \
      return func##_u32 (a, b, c);               \
    }
TEST23(vmula)
/* { dg-final { scan-assembler "vmula\.u8" } }*/
/* { dg-final { scan-assembler "vmula\.u16" } }*/
/* { dg-final { scan-assembler "vmula\.u32" } }*/
/* { dg-final { scan-assembler "vmula\.u8" } }*/
/* { dg-final { scan-assembler "vmula\.u16" } }*/
/* { dg-final { scan-assembler "vmula\.u32" } }*/
TEST23(vmuls)
/* { dg-final { scan-assembler "vmuls\.u8" } }*/
/* { dg-final { scan-assembler "vmuls\.u16" } }*/
/* { dg-final { scan-assembler "vmuls\.u32" } }*/
/* { dg-final { scan-assembler "vmuls\.u8" } }*/
/* { dg-final { scan-assembler "vmuls\.u16" } }*/
/* { dg-final { scan-assembler "vmuls\.u32" } }*/
TEST23(vsabsa)
/* { dg-final { scan-assembler "vsabsa\.u8" } }*/
/* { dg-final { scan-assembler "vsabsa\.u16" } }*/
/* { dg-final { scan-assembler "vsabsa\.u32" } }*/
/* { dg-final { scan-assembler "vsabsa\.u8" } }*/
/* { dg-final { scan-assembler "vsabsa\.u16" } }*/
/* { dg-final { scan-assembler "vsabsa\.u32" } }*/


#define TEST24(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_s8 (a, 3);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a) \
    {                                                          \
      return func##_s16 (a, 3);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a) \
    {                                                          \
      return func##_s32 (a, 3);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiu (uint8x16_t a) \
    {                                                          \
      return func##_u8 (a, 3);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiu (uint16x8_t a) \
    {                                                          \
      return func##_u16 (a, 3);               \
    }                                                          \
  uint32x4_t f_##func##_v4siu (uint32x4_t a) \
    {                                                          \
      return func##_u32 (a, 3);               \
    }                                                          \
  sat8x16_t f_##func##_v16qq (sat8x16_t a) \
    {                                                          \
      return func##_s8_s (a, 3);               \
    }                                                          \
  sat16x8_t f_##func##_v8hq (sat16x8_t a) \
    {                                                          \
      return func##_s16_s (a, 3);               \
    }                                                          \
  sat32x4_t f_##func##_v4sq (sat32x4_t a) \
    {                                                          \
      return func##_s32_s (a, 3);               \
    }                                                          \
  usat8x16_t f_##func##_v16uqq (usat8x16_t a) \
    {                                                          \
      return func##_u8_s (a, 3);               \
    }                                                          \
  usat16x8_t f_##func##_v8uhq (usat16x8_t a) \
    {                                                          \
      return func##_u16_s (a, 3);               \
    }                                                          \
  usat32x4_t f_##func##_v4usq (usat32x4_t a) \
    {                                                          \
      return func##_u32_s (a, 3);               \
    }
TEST24(vshli)
/* { dg-final { scan-assembler "vshli\.u8" } }*/
/* { dg-final { scan-assembler "vshli\.u16" } }*/
/* { dg-final { scan-assembler "vshli\.u32" } }*/
/* { dg-final { scan-assembler "vshli\.u8" } }*/
/* { dg-final { scan-assembler "vshli\.u16" } }*/
/* { dg-final { scan-assembler "vshli\.u32" } }*/
/* { dg-final { scan-assembler "vshli\.s8.s" } }*/
/* { dg-final { scan-assembler "vshli\.s16.s" } }*/
/* { dg-final { scan-assembler "vshli\.s32.s" } }*/
/* { dg-final { scan-assembler "vshli\.u8.s" } }*/
/* { dg-final { scan-assembler "vshli\.u16.s" } }*/
/* { dg-final { scan-assembler "vshli\.u32.s" } }*/



#define TEST25(func, type) \
  int8x16_t f_##func##_v16qi_##type (int8x16_t a, int8x16_t b) \
    {                                                          \
      return func##_s8_##type (a, b);               \
    }                                                          \
  int16x8_t f_##func##_v8hi_##type (int16x8_t a, int16x8_t b) \
    {                                                          \
      return func##_s16_##type (a, b);               \
    }                                                          \
  int32x4_t f_##func##_v4si_##type (int32x4_t a, int32x4_t b) \
    {                                                          \
      return func##_s32_##type (a, b);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiu_##type (uint8x16_t a, uint8x16_t b) \
    {                                                          \
      return func##_u8_##type (a, b);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiu_##type (uint16x8_t a, uint16x8_t b) \
    {                                                          \
      return func##_u16_##type (a, b);               \
    }                                                          \
  uint32x4_t f_##func##_v4siu_##type (uint32x4_t a, uint32x4_t b) \
    {                                                          \
      return func##_u32_##type (a, b);               \
    }
  TEST25(vshr, r)
/* { dg-final { scan-assembler "vshr\.s8.r" } }*/
/* { dg-final { scan-assembler "vshr\.s16.r" } }*/
/* { dg-final { scan-assembler "vshr\.s32.r" } }*/
/* { dg-final { scan-assembler "vshr\.u8.r" } }*/
/* { dg-final { scan-assembler "vshr\.u16.r" } }*/
/* { dg-final { scan-assembler "vshr\.u32.r" } }*/


#define TEST26(func) \
  int8x16_t f_##func##_v16qi (int8x16_t a) \
    {                                                          \
      return func##_s8 (a, 3);               \
    }                                                          \
  int16x8_t f_##func##_v8hi (int16x8_t a) \
    {                                                          \
      return func##_s16 (a, 3);               \
    }                                                          \
  int32x4_t f_##func##_v4si (int32x4_t a) \
    {                                                          \
      return func##_s32 (a, 3);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiu (uint8x16_t a) \
    {                                                          \
      return func##_u8 (a, 3);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiu (uint16x8_t a) \
    {                                                          \
      return func##_u16 (a, 3);               \
    }                                                          \
  uint32x4_t f_##func##_v4siu (uint32x4_t a) \
    {                                                          \
      return func##_u32 (a, 3);               \
    }
TEST26(vshri)
/* { dg-final { scan-assembler "vshri\.u8" } }*/
/* { dg-final { scan-assembler "vshri\.u16" } }*/
/* { dg-final { scan-assembler "vshri\.u32" } }*/
/* { dg-final { scan-assembler "vshri\.u8" } }*/
/* { dg-final { scan-assembler "vshri\.u16" } }*/
/* { dg-final { scan-assembler "vshri\.u32" } }*/

#define TEST27(func, type) \
  int8x16_t f_##func##_v16qi##type (int8x16_t a) \
    {                                                          \
      return func##_s8_##type (a, 3);               \
    }                                                          \
  int16x8_t f_##func##_v8hi##type (int16x8_t a) \
    {                                                          \
      return func##_s16_##type (a, 3);               \
    }                                                          \
  int32x4_t f_##func##_v4si##type (int32x4_t a) \
    {                                                          \
      return func##_s32_##type (a, 3);               \
    }                                                          \
  uint8x16_t f_##func##_v16qiu##type (uint8x16_t a) \
    {                                                          \
      return func##_u8_##type (a, 3);               \
    }                                                          \
  uint16x8_t f_##func##_v8hiu##type (uint16x8_t a) \
    {                                                          \
      return func##_u16_##type (a, 3);               \
    }                                                          \
  uint32x4_t f_##func##_v4siu##type (uint32x4_t a) \
    {                                                          \
      return func##_u32_##type (a, 3);               \
    }
TEST27(vshri, r)
/* { dg-final { scan-assembler "vshri\.u8.r" } }*/
/* { dg-final { scan-assembler "vshri\.u16.r" } }*/
/* { dg-final { scan-assembler "vshri\.u32.r" } }*/
/* { dg-final { scan-assembler "vshri\.u8.r" } }*/
/* { dg-final { scan-assembler "vshri\.u16.r" } }*/
/* { dg-final { scan-assembler "vshri\.u32.r" } }*/

#define TEST28(func, type) \
  int8x16_t f_##func##_v8his##type (int16x8_t a) \
    {                                                          \
      return func##_s16_##type (a);               \
    }                                                          \
  int16x8_t f_##func##_v4sis##type (int32x4_t a) \
    {                                                          \
      return func##_s32_##type (a);               \
    }
TEST28(vstou, sl)
/* { dg-final { scan-assembler "vstou\.s16\.sl" } }*/
/* { dg-final { scan-assembler "vstou\.s32\.sl" } }*/