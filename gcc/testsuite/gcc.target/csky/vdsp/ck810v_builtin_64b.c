/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810"  { csky-*-* }  { "*" }  { "-mcpu=ck810*v*"  }  }  */
/* { dg-options "-O2 -mvdsp-width=64" } */

#define TEST(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a, __simd64_int8_t b) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, b);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (__simd64_int16_t a, __simd64_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, b);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (__simd64_int32_t a, __simd64_int32_t b) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, b);               \
    }                                                          \
  __simd64_sat8_t f_##func##_v8qq (__simd64_sat8_t a, __simd64_sat8_t b) \
    {                                                          \
      return __builtin_csky_##func##v8qq (a, b);               \
    }                                                          \
  __simd64_sat16_t f_##func##_v4hq (__simd64_sat16_t a, __simd64_sat16_t b) \
    {                                                          \
      return __builtin_csky_##func##v4hq (a, b);               \
    }                                                          \
  __simd64_sat32_t f_##func##_v2sq (__simd64_sat32_t a, __simd64_sat32_t b) \
    {                                                          \
      return __builtin_csky_##func##v2sq (a, b);               \
    }                                                          \
  __simd64_usat8_t f_##func##_v8uqq (__simd64_usat8_t a, __simd64_usat8_t b) \
    {                                                          \
      return __builtin_csky_##func##v8uqq (a, b);               \
    }                                                          \
  __simd64_usat16_t f_##func##_v4uhq (__simd64_usat16_t a, __simd64_usat16_t b) \
    {                                                          \
      return __builtin_csky_##func##v4uhq (a, b);               \
    }                                                          \
  __simd64_usat32_t f_##func##_v2usq (__simd64_usat32_t a, __simd64_usat32_t b) \
    {                                                          \
      return __builtin_csky_##func##v2usq (a, b);               \
    }
TEST(vadd)
/* { dg-final { scan-assembler "vadd\.u8" } }*/
/* { dg-final { scan-assembler "vadd\.u16" } }*/
/* { dg-final { scan-assembler "vadd\.u32" } }*/
/* { dg-final { scan-assembler "vadd\.s8.s" } }*/
/* { dg-final { scan-assembler "vadd\.s16.s" } }*/
/* { dg-final { scan-assembler "vadd\.s32.s" } }*/
/* { dg-final { scan-assembler "vadd\.u8.s" } }*/
/* { dg-final { scan-assembler "vadd\.u16.s" } }*/
/* { dg-final { scan-assembler "vadd\.u32.s" } }*/
TEST(vsub)
/* { dg-final { scan-assembler "vsub\.u8" } }*/
/* { dg-final { scan-assembler "vsub\.u16" } }*/
/* { dg-final { scan-assembler "vsub\.u32" } }*/
/* { dg-final { scan-assembler "vsub\.s8.s" } }*/
/* { dg-final { scan-assembler "vsub\.s16.s" } }*/
/* { dg-final { scan-assembler "vsub\.s32.s" } }*/
/* { dg-final { scan-assembler "vsub\.u8.s" } }*/
/* { dg-final { scan-assembler "vsub\.u16.s" } }*/
/* { dg-final { scan-assembler "vsub\.u32.s" } }*/

#define TEST1(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a, __simd64_int8_t b) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, b);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (__simd64_int16_t a, __simd64_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, b);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (__simd64_int32_t a, __simd64_int32_t b) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, b);               \
    }
TEST1(vand)
/* { dg-final { scan-assembler "vand\.8" } }*/
/* { dg-final { scan-assembler "vand\.16" } }*/
/* { dg-final { scan-assembler "vand\.32" } }*/
TEST1(vsmax)
/* { dg-final { scan-assembler "vmax\.s8" } }*/
/* { dg-final { scan-assembler "vmax\.s16" } }*/
/* { dg-final { scan-assembler "vmax\.s32" } }*/
TEST1(vsmin)
/* { dg-final { scan-assembler "vmin\.s8" } }*/
/* { dg-final { scan-assembler "vmin\.s16" } }*/
/* { dg-final { scan-assembler "vmin\.s32" } }*/
TEST1(vmul)
/* { dg-final { scan-assembler "vmul\.u8" } }*/
/* { dg-final { scan-assembler "vmul\.u16" } }*/
/* { dg-final { scan-assembler "vmul\.u32" } }*/
TEST1(vor)
/* { dg-final { scan-assembler "vor\.8" } }*/
/* { dg-final { scan-assembler "vor\.16" } }*/
/* { dg-final { scan-assembler "vor\.32" } }*/
TEST1(vxor)
/* { dg-final { scan-assembler "vxor\.8" } }*/
/* { dg-final { scan-assembler "vxor\.16" } }*/
/* { dg-final { scan-assembler "vxor\.32" } }*/
TEST1(vaddhs)
/* { dg-final { scan-assembler "vaddh\.s8" } }*/
/* { dg-final { scan-assembler "vaddh\.s16" } }*/
/* { dg-final { scan-assembler "vaddh\.s32" } }*/
TEST1(vaddhrs)
/* { dg-final { scan-assembler "vaddh\.s8.r" } }*/
/* { dg-final { scan-assembler "vaddh\.s16.r" } }*/
/* { dg-final { scan-assembler "vaddh\.s32.r" } }*/
TEST1(vandn)
/* { dg-final { scan-assembler "vandn\.8" } }*/
/* { dg-final { scan-assembler "vandn\.16" } }*/
/* { dg-final { scan-assembler "vandn\.32" } }*/
TEST1(vcadds)
/* { dg-final { scan-assembler "vcadd\.s8" } }*/
/* { dg-final { scan-assembler "vcadd\.s16" } }*/
/* { dg-final { scan-assembler "vcadd\.s32" } }*/
TEST1(vcmaxs)
/* { dg-final { scan-assembler "vcmax\.s8" } }*/
/* { dg-final { scan-assembler "vcmax\.s16" } }*/
/* { dg-final { scan-assembler "vcmax\.s32" } }*/
TEST1(vcmins)
/* { dg-final { scan-assembler "vcmin\.s8" } }*/
/* { dg-final { scan-assembler "vcmin\.s16" } }*/
/* { dg-final { scan-assembler "vcmin\.s32" } }*/
TEST1(vcmphss)
/* { dg-final { scan-assembler "vcmphs\.s8" } }*/
/* { dg-final { scan-assembler "vcmphs\.s16" } }*/
/* { dg-final { scan-assembler "vcmphs\.s32" } }*/
TEST1(vcmplts)
/* { dg-final { scan-assembler "vcmplt\.s8" } }*/
/* { dg-final { scan-assembler "vcmplt\.s16" } }*/
/* { dg-final { scan-assembler "vcmplt\.s32" } }*/
TEST1(vcmpnes)
/* { dg-final { scan-assembler "vcmpne\.s8" } }*/
/* { dg-final { scan-assembler "vcmpne\.s16" } }*/
/* { dg-final { scan-assembler "vcmpne\.s32" } }*/
TEST1(vdch)
/* { dg-final { scan-assembler "vdch\.8" } }*/
/* { dg-final { scan-assembler "vdch\.16" } }*/
/* { dg-final { scan-assembler "vdch\.32" } }*/
TEST1(vdcl)
/* { dg-final { scan-assembler "vdcl\.8" } }*/
/* { dg-final { scan-assembler "vdcl\.16" } }*/
/* { dg-final { scan-assembler "vdcl\.32" } }*/
TEST1(vich)
/* { dg-final { scan-assembler "vich\.8" } }*/
/* { dg-final { scan-assembler "vich\.16" } }*/
/* { dg-final { scan-assembler "vich\.32" } }*/
TEST1(vicl)
/* { dg-final { scan-assembler "vicl\.8" } }*/
/* { dg-final { scan-assembler "vicl\.16" } }*/
/* { dg-final { scan-assembler "vicl\.32" } }*/
TEST1(vnor)
/* { dg-final { scan-assembler "vnor\.8" } }*/
/* { dg-final { scan-assembler "vnor\.16" } }*/
/* { dg-final { scan-assembler "vnor\.32" } }*/
TEST1(vsabss)
/* { dg-final { scan-assembler "vsabs\.s8" } }*/
/* { dg-final { scan-assembler "vsabs\.s16" } }*/
/* { dg-final { scan-assembler "vsabs\.s32" } }*/
TEST1(vshls)
/* { dg-final { scan-assembler "vshl\.s8" } }*/
/* { dg-final { scan-assembler "vshl\.s16" } }*/
/* { dg-final { scan-assembler "vshl\.s32" } }*/
TEST1(vshrs)
/* { dg-final { scan-assembler "vshr\.s8" } }*/
/* { dg-final { scan-assembler "vshr\.s16" } }*/
/* { dg-final { scan-assembler "vshr\.s32" } }*/
TEST1(vshrrs)
/* { dg-final { scan-assembler "vshr\.s8.r" } }*/
/* { dg-final { scan-assembler "vshr\.s16.r" } }*/
/* { dg-final { scan-assembler "vshr\.s32.r" } }*/
TEST1(vsubhs)
/* { dg-final { scan-assembler "vsubh\.s8" } }*/
/* { dg-final { scan-assembler "vsubh\.s16" } }*/
/* { dg-final { scan-assembler "vsubh\.s32" } }*/
TEST1(vsubhrs)
/* { dg-final { scan-assembler "vsubh\.s8.r" } }*/
/* { dg-final { scan-assembler "vsubh\.s16.r" } }*/
/* { dg-final { scan-assembler "vsubh\.s32.r" } }*/
TEST1(vtrch)
/* { dg-final { scan-assembler "vtrch\.8" } }*/
/* { dg-final { scan-assembler "vtrch\.16" } }*/
/* { dg-final { scan-assembler "vtrch\.32" } }*/
TEST1(vtrcl)
/* { dg-final { scan-assembler "vtrcl\.8" } }*/
/* { dg-final { scan-assembler "vtrcl\.16" } }*/
/* { dg-final { scan-assembler "vtrcl\.32" } }*/
TEST1(vtst)
/* { dg-final { scan-assembler "vtst\.8" } }*/
/* { dg-final { scan-assembler "vtst\.16" } }*/
/* { dg-final { scan-assembler "vtst\.32" } }*/


#define TEST1_1(func) \
  __simd64_uint8_t f_##func##_v8qi (__simd64_uint8_t a, __simd64_uint8_t b) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, b);               \
    }                                                          \
  __simd64_uint16_t f_##func##_v4hi (__simd64_uint16_t a, __simd64_uint16_t b) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, b);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v2si (__simd64_uint32_t a, __simd64_uint32_t b) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, b);               \
    }
TEST1_1(vumax)
/* { dg-final { scan-assembler "vmax\.u8" } }*/
/* { dg-final { scan-assembler "vmax\.u16" } }*/
/* { dg-final { scan-assembler "vmax\.u32" } }*/
TEST1_1(vumin)
/* { dg-final { scan-assembler "vmin\.u8" } }*/
/* { dg-final { scan-assembler "vmin\.u16" } }*/
/* { dg-final { scan-assembler "vmin\.u32" } }*/
TEST1_1(vaddhu)
/* { dg-final { scan-assembler "vaddh\.u8" } }*/
/* { dg-final { scan-assembler "vaddh\.u16" } }*/
/* { dg-final { scan-assembler "vaddh\.u32" } }*/
TEST1_1(vaddhru)
/* { dg-final { scan-assembler "vaddh\.u8.r" } }*/
/* { dg-final { scan-assembler "vaddh\.u16.r" } }*/
/* { dg-final { scan-assembler "vaddh\.u32.r" } }*/
TEST1_1(vcaddu)
/* { dg-final { scan-assembler "vcadd\.u8" } }*/
/* { dg-final { scan-assembler "vcadd\.u16" } }*/
/* { dg-final { scan-assembler "vcadd\.u32" } }*/
TEST1_1(vcmaxu)
/* { dg-final { scan-assembler "vcmax\.u8" } }*/
/* { dg-final { scan-assembler "vcmax\.u16" } }*/
/* { dg-final { scan-assembler "vcmax\.u32" } }*/
TEST1_1(vcminu)
/* { dg-final { scan-assembler "vcmin\.u8" } }*/
/* { dg-final { scan-assembler "vcmin\.u16" } }*/
/* { dg-final { scan-assembler "vcmin\.u32" } }*/
TEST1_1(vcmphsu)
/* { dg-final { scan-assembler "vcmphs\.u8" } }*/
/* { dg-final { scan-assembler "vcmphs\.u16" } }*/
/* { dg-final { scan-assembler "vcmphs\.u32" } }*/
TEST1_1(vcmpltu)
/* { dg-final { scan-assembler "vcmplt\.u8" } }*/
/* { dg-final { scan-assembler "vcmplt\.u16" } }*/
/* { dg-final { scan-assembler "vcmplt\.u32" } }*/
TEST1_1(vcmpneu)
/* { dg-final { scan-assembler "vcmpne\.u8" } }*/
/* { dg-final { scan-assembler "vcmpne\.u16" } }*/
/* { dg-final { scan-assembler "vcmpne\.u32" } }*/
TEST1_1(vsabsu)
/* { dg-final { scan-assembler "vsabs\.u8" } }*/
/* { dg-final { scan-assembler "vsabs\.u16" } }*/
/* { dg-final { scan-assembler "vsabs\.u32" } }*/
TEST1_1(vshlu)
/* { dg-final { scan-assembler "vshl\.u8" } }*/
/* { dg-final { scan-assembler "vshl\.u16" } }*/
/* { dg-final { scan-assembler "vshl\.u32" } }*/
TEST1_1(vshru)
/* { dg-final { scan-assembler "vshr\.u8" } }*/
/* { dg-final { scan-assembler "vshr\.u16" } }*/
/* { dg-final { scan-assembler "vshr\.u32" } }*/
TEST1_1(vshrru)
/* { dg-final { scan-assembler "vshr\.u8.r" } }*/
/* { dg-final { scan-assembler "vshr\.u16.r" } }*/
/* { dg-final { scan-assembler "vshr\.u32.r" } }*/
TEST1_1(vsubhu)
/* { dg-final { scan-assembler "vsubh\.u8" } }*/
/* { dg-final { scan-assembler "vsubh\.u16" } }*/
/* { dg-final { scan-assembler "vsubh\.u32" } }*/
TEST1_1(vsubhru)
/* { dg-final { scan-assembler "vsubh\.u8.r" } }*/
/* { dg-final { scan-assembler "vsubh\.u16.r" } }*/
/* { dg-final { scan-assembler "vsubh\.u32.r" } }*/

#define TEST1_2(func) \
  __simd64_sat8_t f_##func##_v8qq (__simd64_sat8_t a, __simd64_sat8_t b) \
    {                                                          \
      return __builtin_csky_##func##v8qq (a, b);               \
    }                                                          \
  __simd64_sat16_t f_##func##_v4hq (__simd64_sat16_t a, __simd64_sat16_t b) \
    {                                                          \
      return __builtin_csky_##func##v4hq (a, b);               \
    }                                                          \
  __simd64_sat32_t f_##func##_v2sq (__simd64_sat32_t a, __simd64_sat32_t b) \
    {                                                          \
      return __builtin_csky_##func##v2sq (a, b);               \
    } \
  __simd64_usat8_t f_##func##_v8uqq (__simd64_usat8_t a, __simd64_usat8_t b) \
    {                                                          \
      return __builtin_csky_##func##v8uqq (a, b);               \
    }                                                          \
  __simd64_usat16_t f_##func##_v4uhq (__simd64_usat16_t a, __simd64_usat16_t b) \
    {                                                          \
      return __builtin_csky_##func##v4uhq (a, b);               \
    }                                                          \
  __simd64_usat32_t f_##func##_v2usq (__simd64_usat32_t a, __simd64_usat32_t b) \
    {                                                          \
      return __builtin_csky_##func##v2usq (a, b);               \
    }
TEST1_2(vshl)
/* { dg-final { scan-assembler "vshl\.s8.s" } }*/
/* { dg-final { scan-assembler "vshl\.s16.s" } }*/
/* { dg-final { scan-assembler "vshl\.s32.s" } }*/
/* { dg-final { scan-assembler "vshl\.u8.s" } }*/
/* { dg-final { scan-assembler "vshl\.u16.s" } }*/
/* { dg-final { scan-assembler "vshl\.u32.s" } }*/

#define TEST2(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a, __simd64_int8_t b, __simd64_int8_t c) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, b, c);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (__simd64_int16_t a, __simd64_int16_t b, __simd64_int16_t c) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, b, c);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (__simd64_int32_t a, __simd64_int32_t b, __simd64_int32_t c) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, b, c);               \
    }
TEST2(vmula)
/* { dg-final { scan-assembler "vmula\.u8" } }*/
/* { dg-final { scan-assembler "vmula\.u16" } }*/
/* { dg-final { scan-assembler "vmula\.u32" } }*/
TEST2(vmuls)
/* { dg-final { scan-assembler "vmuls\.u8" } }*/
/* { dg-final { scan-assembler "vmuls\.u16" } }*/
/* { dg-final { scan-assembler "vmuls\.u32" } }*/
TEST2(vsabsas)
/* { dg-final { scan-assembler "vsabsa\.s8" } }*/
/* { dg-final { scan-assembler "vsabsa\.s16" } }*/
/* { dg-final { scan-assembler "vsabsa\.s32" } }*/

#define TEST2_1(func) \
  __simd64_uint8_t f_##func##_v8qiu (__simd64_uint8_t a, __simd64_uint8_t b, __simd64_uint8_t c) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, b, c);               \
    }                                                          \
  __simd64_uint16_t f_##func##_v4hiu (__simd64_uint16_t a, __simd64_uint16_t b, __simd64_uint16_t c) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, b, c);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v2siu (__simd64_uint32_t a, __simd64_uint32_t b, __simd64_uint32_t c) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, b, c);               \
    }
TEST2_1(vsabsau)
/* { dg-final { scan-assembler "vsabsa\.u8" } }*/
/* { dg-final { scan-assembler "vsabsa\.u16" } }*/
/* { dg-final { scan-assembler "vsabsa\.u32" } }*/

#define TEST3(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a, __simd64_int8_t b) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, b);               \
    }
TEST3(vbperm)
/* { dg-final { scan-assembler "vbperm\.8" } }*/
TEST3(vbpermz)
/* { dg-final { scan-assembler "vbpermz\.8" } }*/

#define TEST4(func) \
  __simd64_uint16_t f_##func##_v8qiu (__simd64_uint8_t a, __simd64_uint8_t b) \
    {                                                          \
      return __builtin_csky_##func##uv8qi (a, b);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v4hiu (__simd64_uint16_t a, __simd64_uint16_t b) \
    {                                                          \
      return __builtin_csky_##func##uv4hi (a, b);               \
    } \
  __simd64_int16_t f_##func##_v8qis (__simd64_int8_t a, __simd64_int8_t b) \
    {                                                          \
      return __builtin_csky_##func##sv8qi (a, b);               \
    }                                                          \
  __simd64_int32_t f_##func##_v4his (__simd64_int16_t a, __simd64_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##sv4hi (a, b);               \
    }
TEST4(vadde)
/* { dg-final { scan-assembler "vadd\.eu8" } }*/
/* { dg-final { scan-assembler "vadd\.eu16" } }*/
/* { dg-final { scan-assembler "vadd\.es8" } }*/
/* { dg-final { scan-assembler "vadd\.es16" } }*/
TEST4(vmule)
/* { dg-final { scan-assembler "vmul\.eu8" } }*/
/* { dg-final { scan-assembler "vmul\.eu16" } }*/
/* { dg-final { scan-assembler "vmul\.es8" } }*/
/* { dg-final { scan-assembler "vmul\.es16" } }*/
TEST4(vsabse)
/* { dg-final { scan-assembler "vsabs\.eu8" } }*/
/* { dg-final { scan-assembler "vsabs\.eu16" } }*/
/* { dg-final { scan-assembler "vsabs\.es8" } }*/
/* { dg-final { scan-assembler "vsabs\.es16" } }*/
TEST4(vsube)
/* { dg-final { scan-assembler "vsub\.eu8" } }*/
/* { dg-final { scan-assembler "vsub\.eu16" } }*/
/* { dg-final { scan-assembler "vsub\.es8" } }*/
/* { dg-final { scan-assembler "vsub\.es16" } }*/
TEST4(vcadde)
/* { dg-final { scan-assembler "vcadd\.eu8" } }*/
/* { dg-final { scan-assembler "vcadd\.eu16" } }*/
/* { dg-final { scan-assembler "vcadd\.es8" } }*/
/* { dg-final { scan-assembler "vcadd\.es16" } }*/

#define TEST5(func) \
  __simd64_uint16_t f_##func##_v8qiu (__simd64_uint8_t a, __simd64_uint8_t b, __simd64_uint16_t c) \
    {                                                          \
      return __builtin_csky_##func##uv8qi (a, b, c);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v4hiu (__simd64_uint16_t a, __simd64_uint16_t b, __simd64_uint32_t c) \
    {                                                          \
      return __builtin_csky_##func##uv4hi (a, b, c);               \
    } \
__simd64_int16_t f_##func##_v8qis (__simd64_int8_t a, __simd64_int8_t b, __simd64_int16_t c) \
    {                                                          \
      return __builtin_csky_##func##sv8qi (a, b, c);               \
    }                                                          \
  __simd64_int32_t f_##func##_v4his (__simd64_int16_t a, __simd64_int16_t b, __simd64_int32_t c) \
    {                                                          \
      return __builtin_csky_##func##sv4hi (a, b, c);               \
    }
TEST5(vmulae)
/* { dg-final { scan-assembler "vmula\.eu8" } }*/
/* { dg-final { scan-assembler "vmula\.eu16" } }*/
/* { dg-final { scan-assembler "vmula\.es8" } }*/
/* { dg-final { scan-assembler "vmula\.es16" } }*/
TEST5(vmulse)
/* { dg-final { scan-assembler "vmuls\.eu8" } }*/
/* { dg-final { scan-assembler "vmuls\.eu16" } }*/
/* { dg-final { scan-assembler "vmuls\.es8" } }*/
/* { dg-final { scan-assembler "vmuls\.es16" } }*/
TEST5(vsabsae)
/* { dg-final { scan-assembler "vsabsa\.eu8" } }*/
/* { dg-final { scan-assembler "vsabsa\.eu16" } }*/
/* { dg-final { scan-assembler "vsabsa\.es8" } }*/
/* { dg-final { scan-assembler "vsabsa\.es16" } }*/

#define TEST6(func) \
  __simd64_uint16_t f_##func##_v4hiu (__simd64_uint8_t a, __simd64_uint16_t b) \
    {                                                          \
      return __builtin_csky_##func##uv4hi (a, b);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v2siu (__simd64_uint16_t a, __simd64_uint32_t b) \
    {                                                          \
      return __builtin_csky_##func##uv2si (a, b);               \
    } \
  __simd64_int16_t f_##func##_v4his (__simd64_int8_t a, __simd64_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##sv4hi (a, b);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2sis (__simd64_int16_t a, __simd64_int32_t b) \
    {                                                          \
      return __builtin_csky_##func##sv2si (a, b);               \
    }
TEST6(vaddx)
/* { dg-final { scan-assembler "vadd\.xu16" } }*/
/* { dg-final { scan-assembler "vadd\.xu32" } }*/
/* { dg-final { scan-assembler "vadd\.xs16" } }*/
/* { dg-final { scan-assembler "vadd\.xs32" } }*/
TEST6(vsubx)
/* { dg-final { scan-assembler "vsub\.xu16" } }*/
/* { dg-final { scan-assembler "vsub\.xu32" } }*/
/* { dg-final { scan-assembler "vsub\.xs16" } }*/
/* { dg-final { scan-assembler "vsub\.xs32" } }*/

#define TEST6_1(func) \
  __simd64_uint8_t f_##func##_v4hiu (__simd64_uint8_t a, __simd64_uint16_t b) \
    {                                                          \
      return __builtin_csky_##func##uv4hi (a, b);               \
    }                                                          \
  __simd64_uint16_t f_##func##_v2siu (__simd64_uint16_t a, __simd64_uint32_t b) \
    {                                                          \
      return __builtin_csky_##func##uv2si (a, b);               \
    } \
  __simd64_int8_t f_##func##_v4his (__simd64_int8_t a, __simd64_int16_t b) \
    {                                                          \
      return __builtin_csky_##func##sv4hi (a, b);               \
    }                                                          \
  __simd64_int16_t f_##func##_v2sis (__simd64_int16_t a, __simd64_int32_t b) \
    {                                                          \
      return __builtin_csky_##func##sv2si (a, b);               \
    }
TEST6_1(vaddxsl)
/* { dg-final { scan-assembler "vadd\.xu16.sl" } }*/
/* { dg-final { scan-assembler "vadd\.xu32.sl" } }*/
/* { dg-final { scan-assembler "vadd\.xs16.sl" } }*/
/* { dg-final { scan-assembler "vadd\.xs32.sl" } }*/

#define TEST7(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2si (a);               \
    }                                                          \
  __simd64_sat8_t f_##func##_v8qq (__simd64_sat8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qq (a);               \
    }                                                          \
  __simd64_sat16_t f_##func##_v4hq (__simd64_sat16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hq (a);               \
    }                                                          \
  __simd64_sat32_t f_##func##_v2sq (__simd64_sat32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2sq (a);               \
    }                                                          \
  __simd64_usat8_t f_##func##_v8uqq (__simd64_usat8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8uqq (a);               \
    }                                                          \
  __simd64_usat16_t f_##func##_v4uhq (__simd64_usat16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4uhq (a);               \
    }                                                          \
  __simd64_usat32_t f_##func##_v2usq (__simd64_usat32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2usq (a);               \
    }
TEST7(vabs)
/* { dg-final { scan-assembler "vabs\.s8" } }*/
/* { dg-final { scan-assembler "vabs\.s16" } }*/
/* { dg-final { scan-assembler "vabs\.s32" } }*/
/* { dg-final { scan-assembler "vabs\.s8.s" } }*/
/* { dg-final { scan-assembler "vabs\.s16.s" } }*/
/* { dg-final { scan-assembler "vabs\.s32.s" } }*/
/* { dg-final { scan-assembler "vabs\.u8.s" } }*/
/* { dg-final { scan-assembler "vabs\.u16.s" } }*/
/* { dg-final { scan-assembler "vabs\.u32.s" } }*/

#define TEST8(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2si (a);               \
    }
TEST8(vclss)
/* { dg-final { scan-assembler "vcls\.s8" } }*/
/* { dg-final { scan-assembler "vcls\.s16" } }*/
/* { dg-final { scan-assembler "vcls\.s32" } }*/
TEST8(vclz)
/* { dg-final { scan-assembler "vclz\.8" } }*/
/* { dg-final { scan-assembler "vclz\.16" } }*/
/* { dg-final { scan-assembler "vclz\.32" } }*/
TEST8(vrev)
/* { dg-final { scan-assembler "vrev\.8" } }*/
/* { dg-final { scan-assembler "vrev\.16" } }*/
/* { dg-final { scan-assembler "vrev\.32" } }*/

#define TEST9(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2si (a);               \
    }                                                          \
  __simd64_sat8_t f_##func##_v8qq (__simd64_sat8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qq (a);               \
    }                                                          \
  __simd64_sat16_t f_##func##_v4hq (__simd64_sat16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hq (a);               \
    }                                                          \
  __simd64_sat32_t f_##func##_v2sq (__simd64_sat32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2sq (a);               \
    }
TEST9(vneg)
/* { dg-final { scan-assembler "vneg\.s8" } }*/
/* { dg-final { scan-assembler "vneg\.s16" } }*/
/* { dg-final { scan-assembler "vneg\.s32" } }*/
/* { dg-final { scan-assembler "vneg\.s8.s" } }*/
/* { dg-final { scan-assembler "vneg\.s16.s" } }*/
/* { dg-final { scan-assembler "vneg\.s32.s" } }*/

#define TEST10(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a);               \
    }
TEST10(vcnt1)
/* { dg-final { scan-assembler "vcnt1\.8" } }*/

#define TEST11(func) \
  __simd64_uint16_t f_##func##_v8qiu (__simd64_uint8_t a) \
    {                                                          \
      return __builtin_csky_##func##uv8qi (a);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v4hiu (__simd64_uint16_t a) \
    {                                                          \
      return __builtin_csky_##func##uv4hi (a);               \
    } \
  __simd64_int16_t f_##func##_v8qis (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##sv8qi (a);               \
    }                                                          \
  __simd64_int32_t f_##func##_v4his (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##sv4hi (a);               \
    }
TEST11(vmove)
/* { dg-final { scan-assembler "vmov\.eu8" } }*/
/* { dg-final { scan-assembler "vmov\.eu16" } }*/
/* { dg-final { scan-assembler "vmov\.es8" } }*/
/* { dg-final { scan-assembler "vmov\.es16" } }*/

#define TEST12(func) \
  __simd64_uint8_t f_##func##_v4hiu (__simd64_uint16_t a) \
    {                                                          \
      return __builtin_csky_##func##uv4hi (a);               \
    }                                                          \
  __simd64_uint16_t f_##func##_v2siu (__simd64_uint32_t a) \
    {                                                          \
      return __builtin_csky_##func##uv2si (a);               \
    } \
  __simd64_int8_t f_##func##_v4his (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##sv4hi (a);               \
    }                                                          \
  __simd64_int16_t f_##func##_v2sis (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##sv2si (a);               \
    }
TEST12(vmovh)
/* { dg-final { scan-assembler "vmov\.u16\.h" } }*/
/* { dg-final { scan-assembler "vmov\.u32\.h" } }*/
/* { dg-final { scan-assembler "vmov\.s16\.h" } }*/
/* { dg-final { scan-assembler "vmov\.s32\.h" } }*/
TEST12(vmovl)
/* { dg-final { scan-assembler "vmov\.u16\.l" } }*/
/* { dg-final { scan-assembler "vmov\.u32\.l" } }*/
/* { dg-final { scan-assembler "vmov\.s16\.l" } }*/
/* { dg-final { scan-assembler "vmov\.s32\.l" } }*/
TEST12(vmovrh)
/* { dg-final { scan-assembler "vmov\.u16\.rh" } }*/
/* { dg-final { scan-assembler "vmov\.u32\.rh" } }*/
/* { dg-final { scan-assembler "vmov\.s16\.rh" } }*/
/* { dg-final { scan-assembler "vmov\.s32\.rh" } }*/
TEST12(vmovsl)
/* { dg-final { scan-assembler "vmov\.u16\.sl" } }*/
/* { dg-final { scan-assembler "vmov\.u32\.sl" } }*/
/* { dg-final { scan-assembler "vmov\.s16\.sl" } }*/
/* { dg-final { scan-assembler "vmov\.s32\.sl" } }*/

#define TEST13(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, 7);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, 3);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, 1);               \
    }
TEST13(vdup)
/* { dg-final { scan-assembler "vdup\.8" } }*/
/* { dg-final { scan-assembler "vdup\.16" } }*/
/* { dg-final { scan-assembler "vdup\.32" } }*/


#define TEST13_1(func) \
  __simd64_uint8_t f_##func##_v8qiu (__simd64_uint8_t a) \
    {                                                          \
      return __builtin_csky_##func##uv8qi (a, 15);               \
    }                                                          \
  __simd64_uint16_t f_##func##_v4hiu (__simd64_uint16_t a) \
    {                                                          \
      return __builtin_csky_##func##uv4hi (a, 7);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v2siu (__simd64_uint32_t a) \
    {                                                          \
      return __builtin_csky_##func##uv2si (a, 3);               \
    } \
  __simd64_int8_t f_##func##_v8qis (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##sv8qi (a, 15);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4his (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##sv4hi (a, 7);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2sis (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##sv2si (a, 3);               \
    }
TEST13_1(vshli)
/* { dg-final { scan-assembler "vshli\.u8" } }*/
/* { dg-final { scan-assembler "vshli\.u16" } }*/
/* { dg-final { scan-assembler "vshli\.u32" } }*/
/* { dg-final { scan-assembler "vshli\.s8" } }*/
/* { dg-final { scan-assembler "vshli\.s16" } }*/
/* { dg-final { scan-assembler "vshli\.s32" } }*/
TEST13_1(vshri)
/* { dg-final { scan-assembler "vshri\.u8" } }*/
/* { dg-final { scan-assembler "vshri\.u16" } }*/
/* { dg-final { scan-assembler "vshri\.u32" } }*/
/* { dg-final { scan-assembler "vshri\.s8" } }*/
/* { dg-final { scan-assembler "vshri\.s16" } }*/
/* { dg-final { scan-assembler "vshri\.s32" } }*/
TEST13_1(vshrir)
/* { dg-final { scan-assembler "vshri\.u8.r" } }*/
/* { dg-final { scan-assembler "vshri\.u16.r" } }*/
/* { dg-final { scan-assembler "vshri\.u32.r" } }*/
/* { dg-final { scan-assembler "vshri\.s8.r" } }*/
/* { dg-final { scan-assembler "vshri\.s16.r" } }*/
/* { dg-final { scan-assembler "vshri\.s32.r" } }*/

#define TEST13_2(func) \
  __simd64_usat8_t f_##func##_v8uqq (__simd64_usat8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8uqq (a, 15);               \
    }                                                          \
  __simd64_usat16_t f_##func##_v4uhq (__simd64_usat16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4uhq (a, 7);               \
    }                                                          \
  __simd64_usat32_t f_##func##_v2usq (__simd64_usat32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2usq (a, 3);               \
    } \
  __simd64_sat8_t f_##func##_v8qq (__simd64_sat8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qq (a, 15);               \
    }                                                          \
  __simd64_sat16_t f_##func##_v4hq (__simd64_sat16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hq (a, 7);               \
    }                                                          \
  __simd64_sat32_t f_##func##_v2sq (__simd64_sat32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2sq (a, 3);               \
    }
TEST13_2(vshli)
/* { dg-final { scan-assembler "vshli\.u8.s" } }*/
/* { dg-final { scan-assembler "vshli\.u16.s" } }*/
/* { dg-final { scan-assembler "vshli\.u32.s" } }*/
/* { dg-final { scan-assembler "vshli\.s8.s" } }*/
/* { dg-final { scan-assembler "vshli\.s16.s" } }*/
/* { dg-final { scan-assembler "vshli\.s32.s" } }*/

#define TEST14(func) \
  __simd64_int8_t f_##func##_v8qi (int a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, 2032);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (int a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, 2032);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (int a) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, 2032);               \
    }
TEST14(vldd)
/* { dg-final { scan-assembler "vldd\.8" } }*/
/* { dg-final { scan-assembler "vldd\.16" } }*/
/* { dg-final { scan-assembler "vldd\.32" } }*/
TEST14(vldq)
/* { dg-final { scan-assembler "vldq\.8" } }*/
/* { dg-final { scan-assembler "vldq\.16" } }*/
/* { dg-final { scan-assembler "vldq\.32" } }*/
TEST14(vstd)
/* { dg-final { scan-assembler "vstd\.8" } }*/
/* { dg-final { scan-assembler "vstd\.16" } }*/
/* { dg-final { scan-assembler "vstd\.32" } }*/
TEST14(vstq)
/* { dg-final { scan-assembler "vstq\.8" } }*/
/* { dg-final { scan-assembler "vstq\.16" } }*/
/* { dg-final { scan-assembler "vstq\.32" } }*/

#define TEST15(func) \
  __simd64_int8_t f_##func##_v8qi (int a, int b) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, b, 1);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (int a, int b) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, b, 2);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (int a, int b) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, b, 3);               \
    }
TEST15(vldrd)
/* { dg-final { scan-assembler "vldrd\.8" } }*/
/* { dg-final { scan-assembler "vldrd\.16" } }*/
/* { dg-final { scan-assembler "vldrd\.32" } }*/
TEST15(vldrq)
/* { dg-final { scan-assembler "vldrq\.8" } }*/
/* { dg-final { scan-assembler "vldrq\.16" } }*/
/* { dg-final { scan-assembler "vldrq\.32" } }*/
TEST15(vstrd)
/* { dg-final { scan-assembler "vstrd\.8" } }*/
/* { dg-final { scan-assembler "vstrd\.16" } }*/
/* { dg-final { scan-assembler "vstrd\.32" } }*/
TEST15(vstrq)
/* { dg-final { scan-assembler "vstrq\.8" } }*/
/* { dg-final { scan-assembler "vstrq\.16" } }*/
/* { dg-final { scan-assembler "vstrq\.32" } }*/

#define TEST16(func) \
  __simd64_int8_t f_##func##_v8qi (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (7, a, 7);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4hi (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (3, a, 3);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2si (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2si (1, a, 1);               \
    }
TEST16(vins)
/* { dg-final { scan-assembler "vins\.8" } }*/
/* { dg-final { scan-assembler "vins\.16" } }*/
/* { dg-final { scan-assembler "vins\.32" } }*/

#define TEST17(func) \
  unsigned char f_##func##_v8qi (__simd64_uint8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, 7);               \
    }                                                          \
  unsigned short f_##func##_v4hi (__simd64_uint16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, 3);               \
    }                                                          \
  unsigned int f_##func##_v2si (__simd64_uint32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2si (a, 1);               \
    }
TEST17(vmfvru)
/* { dg-final { scan-assembler "vmfvr\.u8" } }*/
/* { dg-final { scan-assembler "vmfvr\.u16" } }*/
/* { dg-final { scan-assembler "vmfvr\.u32" } }*/

#define TEST18(func) \
  char f_##func##_v8qi (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (a, 7);               \
    }                                                          \
  short f_##func##_v4hi (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a, 3);               \
    }
TEST18(vmfvrs)
/* { dg-final { scan-assembler "vmfvr\.s8" } }*/
/* { dg-final { scan-assembler "vmfvr\.s16" } }*/


#define TEST19(func) \
  __simd64_uint8_t f_##func##_v8qi (unsigned char a) \
    {                                                          \
      return __builtin_csky_##func##v8qi (7, a);               \
    }                                                          \
  __simd64_uint16_t f_##func##_v4hi (unsigned short a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (3, a);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v2si (unsigned int a) \
    {                                                          \
      return __builtin_csky_##func##v2si (1, a);               \
    }
TEST19(vmtvru)
/* { dg-final { scan-assembler "vmtvr\.u8" } }*/
/* { dg-final { scan-assembler "vmtvr\.u16" } }*/
/* { dg-final { scan-assembler "vmtvr\.u32" } }*/

#define TEST21(func) \
  __simd64_uint8_t f_##func##_v8qiu (__simd64_uint8_t a) \
    {                                                          \
      return __builtin_csky_##func##uv8qi (a);               \
    }                                                          \
  __simd64_uint16_t f_##func##_v4hiu (__simd64_uint16_t a) \
    {                                                          \
      return __builtin_csky_##func##uv4hi (a);               \
    }                                                          \
  __simd64_uint32_t f_##func##_v2siu (__simd64_uint32_t a) \
    {                                                          \
      return __builtin_csky_##func##uv2si (a);               \
    } \
  __simd64_int8_t f_##func##_v8qis (__simd64_int8_t a) \
    {                                                          \
      return __builtin_csky_##func##sv8qi (a);               \
    }                                                          \
  __simd64_int16_t f_##func##_v4his (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##sv4hi (a);               \
    }                                                          \
  __simd64_int32_t f_##func##_v2sis (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##sv2si (a);               \
    }
TEST21(vcmphsz)
/* { dg-final { scan-assembler "vcmphsz\.u8" } }*/
/* { dg-final { scan-assembler "vcmphsz\.u16" } }*/
/* { dg-final { scan-assembler "vcmphsz\.u32" } }*/
/* { dg-final { scan-assembler "vcmphsz\.s8" } }*/
/* { dg-final { scan-assembler "vcmphsz\.s16" } }*/
/* { dg-final { scan-assembler "vcmphsz\.s32" } }*/
TEST21(vcmpltz)
/* { dg-final { scan-assembler "vcmpltz\.u8" } }*/
/* { dg-final { scan-assembler "vcmpltz\.u16" } }*/
/* { dg-final { scan-assembler "vcmpltz\.u32" } }*/
/* { dg-final { scan-assembler "vcmpltz\.s8" } }*/
/* { dg-final { scan-assembler "vcmpltz\.s16" } }*/
/* { dg-final { scan-assembler "vcmpltz\.s32" } }*/
TEST21(vcmpnez)
/* { dg-final { scan-assembler "vcmpnez\.u8" } }*/
/* { dg-final { scan-assembler "vcmpnez\.u16" } }*/
/* { dg-final { scan-assembler "vcmpnez\.u32" } }*/
/* { dg-final { scan-assembler "vcmpnez\.s8" } }*/
/* { dg-final { scan-assembler "vcmpnez\.s16" } }*/
/* { dg-final { scan-assembler "vcmpnez\.s32" } }*/

#define TEST22(func) \
  __simd64_int8_t f_##func##_v4hi (__simd64_int16_t a) \
    {                                                          \
      return __builtin_csky_##func##v4hi (a);               \
    }                                                          \
  __simd64_int16_t f_##func##_v2si (__simd64_int32_t a) \
    {                                                          \
      return __builtin_csky_##func##v2si (a);               \
    }
TEST22(vstousls)
/* { dg-final { scan-assembler "vstou\.s16.sl" } }*/
/* { dg-final { scan-assembler "vstou\.s32.sl" } }*/
