#ifndef _GCC_CSKY_VDSP_H
#define _GCC_CSKY_VDSP_H 1

#if defined (__CSKY_DSPV2__)
typedef __simd32_int8_t    int8x4_t;
typedef __simd32_int16_t   int16x2_t;
typedef __simd64_int16_t   int16x4_t;
typedef __simd64_int32_t   int32x2_t;
typedef __simd32_uint8_t   uint8x4_t;
typedef __simd32_uint16_t  uint16x2_t;
typedef __simd64_uint16_t  uint16x4_t;
typedef __simd64_uint32_t  uint32x2_t;
typedef __simd32_sat8_t    sat8x4_t;
typedef __simd32_sat16_t   sat16x2_t;
typedef __simd32_usat8_t   usat8x4_t;
typedef __simd32_usat16_t  usat16x2_t;

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
padd_8 (int8x4_t __a, int8x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
padd_16 (int16x2_t __a, int16x2_t __b)
{
  return __a + __b;
}

__extension__ static __inline sat8x4_t __attribute__ ((__always_inline__))
padd_s8_s (sat8x4_t __a, sat8x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline sat16x2_t __attribute__ ((__always_inline__))
padd_s16_s (sat16x2_t __a, sat16x2_t __b)
{
  return __a + __b;
}

__extension__ static __inline usat8x4_t __attribute__ ((__always_inline__))
padd_u8_s (usat8x4_t __a, usat8x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline usat16x2_t __attribute__ ((__always_inline__))
padd_u16_s (usat16x2_t __a, usat16x2_t __b)
{
  return __a + __b;
}

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
psub_8 (int8x4_t __a, int8x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
psub_16 (int16x2_t __a, int16x2_t __b)
{
  return __a - __b;
}

__extension__ static __inline sat8x4_t __attribute__ ((__always_inline__))
psub_s8_s (sat8x4_t __a, sat8x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline sat16x2_t __attribute__ ((__always_inline__))
psub_s16_s (sat16x2_t __a, sat16x2_t __b)
{
  return __a - __b;
}

__extension__ static __inline usat8x4_t __attribute__ ((__always_inline__))
psub_u8_s (usat8x4_t __a, usat8x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline usat16x2_t __attribute__ ((__always_inline__))
psub_u16_s (usat16x2_t __a, usat16x2_t __b)
{
  return __a - __b;
}

__extension__ static __inline uint8x4_t __attribute__ ((__always_inline__))
paddh_u8 (uint8x4_t __a, uint8x4_t __b)
{
  return __builtin_csky_paddhuv4qi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
paddh_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_paddhuv2hi (__a, __b);
}

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
paddh_s8 (int8x4_t __a, int8x4_t __b)
{
  return __builtin_csky_psubhsv4qi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
paddh_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_psubhsv2hi (__a, __b);
}

__extension__ static __inline uint8x4_t __attribute__ ((__always_inline__))
psubh_u8 (uint8x4_t __a, uint8x4_t __b)
{
  return __builtin_csky_psubhuv4qi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
psubh_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_psubhuv2hi (__a, __b);
}

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
psubh_s8 (int8x4_t __a, int8x4_t __b)
{
  return __builtin_csky_psubhsv4qi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
psubh_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_psubhsv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pasx_16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_pasxv2hi (__a, __b);
}

__extension__ static __inline sat16x2_t __attribute__ ((__always_inline__))
pasx_s16_s (sat16x2_t __a, sat16x2_t __b)
{
  return __builtin_csky_pasxv2hq (__a, __b);
}

__extension__ static __inline usat16x2_t __attribute__ ((__always_inline__))
pasx_u16_s (usat16x2_t __a, usat16x2_t __b)
{
  return __builtin_csky_pasxv2uhq (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
psax_16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_psaxv2hi (__a, __b);
}

__extension__ static __inline sat16x2_t __attribute__ ((__always_inline__))
psax_s16_s (sat16x2_t __a, sat16x2_t __b)
{
  return __builtin_csky_psaxv2hq (__a, __b);
}

__extension__ static __inline usat16x2_t __attribute__ ((__always_inline__))
psax_u16_s (usat16x2_t __a, usat16x2_t __b)
{
  return __builtin_csky_psaxv2uhq (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
pasxh_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_pasxhuv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pasxh_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_pasxhsv2hi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
psaxh_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_psaxhuv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
psaxh_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_psaxhsv2hi (__a, __b);
}

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
pcmpne_8 (int8x4_t __a, int8x4_t __b)
{
  return __builtin_csky_pcmpnev4qi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pcmpne_16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_pcmpnev2hi (__a, __b);
}

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
pcmphs_s8 (int8x4_t __a, int8x4_t __b)
{
  return __builtin_csky_pcmphssv4qi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pcmphs_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_pcmphssv2hi (__a, __b);
}

__extension__ static __inline uint8x4_t __attribute__ ((__always_inline__))
pcmphs_u8 (uint8x4_t __a, uint8x4_t __b)
{
  return __builtin_csky_pcmphsuv4qi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
pcmphs_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_pcmphsuv2hi (__a, __b);
}

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
pcmplt_s8 (int8x4_t __a, int8x4_t __b)
{
  return __builtin_csky_pcmpltsv4qi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pcmplt_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_pcmpltsv2hi (__a, __b);
}

__extension__ static __inline uint8x4_t __attribute__ ((__always_inline__))
pcmplt_u8 (uint8x4_t __a, uint8x4_t __b)
{
  return __builtin_csky_pcmpltuv4qi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
pcmplt_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_pcmpltuv2hi (__a, __b);
}

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
max_s8 (int8x4_t __a, int8x4_t __b)
{
  return __builtin_csky_smaxv4qi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
max_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_smaxv2hi (__a, __b);
}

__extension__ static __inline uint8x4_t __attribute__ ((__always_inline__))
max_u8 (uint8x4_t __a, uint8x4_t __b)
{
  return __builtin_csky_umaxv4qi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
max_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_umaxv2hi (__a, __b);
}

__extension__ static __inline int8x4_t __attribute__ ((__always_inline__))
min_s8 (int8x4_t __a, int8x4_t __b)
{
  return __builtin_csky_sminv4qi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
min_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_sminv2hi (__a, __b);
}

__extension__ static __inline uint8x4_t __attribute__ ((__always_inline__))
min_u8 (uint8x4_t __a, uint8x4_t __b)
{
  return __builtin_csky_uminv4qi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
min_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_uminv2hi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
pext_s8_e (int8x4_t __a)
{
  return __builtin_csky_pextsv4qi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
pext_u8_e (uint8x4_t __a)
{
  return __builtin_csky_pextuv4qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
pextx_s8_e (int8x4_t __a)
{
  return __builtin_csky_pextxsv4qi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
pextx_u8_e (uint8x4_t __a)
{
  return __builtin_csky_pextxuv4qi (__a);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
pclipi_u16 (uint16x2_t __a, const int __b)
{
  return __builtin_csky_pclipuv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pclipi_s16 (int16x2_t __a, const int __b)
{
  return __builtin_csky_pclipsv2hi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
pclip_u16 (uint16x2_t __a, int __b)
{
  return __builtin_csky_pclipuv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pclip_s16 (int16x2_t __a, int __b)
{
  return __builtin_csky_pclipsv2hi (__a, __b);
}

__extension__ static __inline sat8x4_t __attribute__ ((__always_inline__))
pabs_s8_s (sat8x4_t __a)
{
  return __builtin_csky_ssabsv4qq(__a);
}

__extension__ static __inline sat16x2_t __attribute__ ((__always_inline__))
pabs_s16_s (sat16x2_t __a)
{
  return __builtin_csky_ssabsv2hq(__a);
}

__extension__ static __inline sat8x4_t __attribute__ ((__always_inline__))
pneg_s8_s (sat8x4_t __a)
{
  return -__a;
}

__extension__ static __inline sat16x2_t __attribute__ ((__always_inline__))
pneg_s16_s (sat16x2_t __a)
{
  return -__a;
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
pmul_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_pmuluv2hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
pmul_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_pmulsv2hi (__a, __b);
}


__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
pmulx_u16 (uint16x2_t __a, uint16x2_t __b)
{
  return __builtin_csky_pmulxuv2hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
pmulx_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_pmulxsv2hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
prmul_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_prmulsv2hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
prmulx_s16 (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_prmulxsv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
prmul_s16_h (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_prmulshv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
prmul_s16_rh (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_prmulsrhv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
prmulx_s16_h (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_prmulxshv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
prmulx_s16_rh (int16x2_t __a, int16x2_t __b)
{
  return __builtin_csky_prmulxsrhv2hi (__a, __b);
}

__extension__ static __inline unsigned int __attribute__ ((__always_inline__))
psabsa_u8 (uint8x4_t __a, uint8x4_t __b)
{
  return __builtin_csky_psabsav4qi (__a, __b);
}

__extension__ static __inline unsigned int __attribute__ ((__always_inline__))
psabsaa_u8 (uint8x4_t __a, uint8x4_t __b)
{
  return __builtin_csky_psabsaav4qi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pasri_s16 (int16x2_t __a, const int __b)
{
  return __a >> __b;
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pasr_s16 (int16x2_t __a, int __b)
{
  return __a >> __b;
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
plsri_s16 (uint16x2_t __a, const int __b)
{
  return __a >> __b;
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
plsr_s16 (uint16x2_t __a, int __b)
{
  return __a >> __b;
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
plsli_s16 (int16x2_t __a, const int __b)
{
  return __a << __b;
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
plsl_s16 (int16x2_t __a, int __b)
{
  return __a << __b;
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pasri_s16_r (int16x2_t __a, const int __b)
{
  return __builtin_csky_pasrirv2hi (__a, __b);
}

__extension__ static __inline int16x2_t __attribute__ ((__always_inline__))
pasr_s16_r (int16x2_t __a, int __b)
{
  return __builtin_csky_pasrrv2hi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
plsri_s16_r (uint16x2_t __a, const int __b)
{
  return __builtin_csky_plsrirv2hi (__a, __b);
}

__extension__ static __inline uint16x2_t __attribute__ ((__always_inline__))
plsr_s16_r (uint16x2_t __a, int __b)
{
  return __builtin_csky_plsrrv2hi (__a, __b);
}

__extension__ static __inline sat16x2_t __attribute__ ((__always_inline__))
plsli_s16_s (sat16x2_t __a, const int __b)
{
  return __builtin_csky_plslissv2hq (__a, __b);
}

__extension__ static __inline sat16x2_t __attribute__ ((__always_inline__))
plsl_s16_s (sat16x2_t __a, int __b)
{
  return __builtin_csky_plslssv2hq (__a, __b);
}

__extension__ static __inline usat16x2_t __attribute__ ((__always_inline__))
plsli_u16_s (usat16x2_t __a, const int __b)
{
  return __builtin_csky_plsliusv2uhq (__a, __b);
}

__extension__ static __inline usat16x2_t __attribute__ ((__always_inline__))
plsl_u16_s (usat16x2_t __a, int __b)
{
  return __builtin_csky_plslusv2uhq (__a, __b);
}

#endif
#if defined (__CSKY_VDSP64__)
typedef __simd64_int8_t     int8x8_t;
typedef __simd64_uint8_t    uint8x8_t;
typedef __simd64_int16_t    int16x4_t;
typedef __simd64_uint16_t   uint16x4_t;
typedef __simd64_int32_t    int32x2_t;
typedef __simd64_uint32_t   uint32x2_t;
typedef __simd64_sat8_t     sat8x8_t;
typedef __simd64_usat8_t    usat8x8_t;
typedef __simd64_sat16_t    sat16x4_t;
typedef __simd64_usat16_t   usat16x4_t;
typedef __simd64_sat32_t    sat32x2_t;
typedef __simd64_usat32_t   usat32x2_t;

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vabs_s8 (int8x8_t __a)
{
  return __builtin_csky_vabsv8qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vabs_s16 (int16x4_t __a)
{
  return __builtin_csky_vabsv4hi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vabs_s32 (int32x2_t __a)
{
  return __builtin_csky_vabsv2si (__a);
}

__extension__ static __inline sat8x8_t __attribute__ ((__always_inline__))
vabs_s8_s (sat8x8_t __a)
{
  return __builtin_csky_vabsv8qq (__a);
}

__extension__ static __inline sat16x4_t __attribute__ ((__always_inline__))
vabs_s16_s (sat16x4_t __a)
{
  return __builtin_csky_vabsv4hq (__a);
}

__extension__ static __inline sat32x2_t __attribute__ ((__always_inline__))
vabs_s32_s (sat32x2_t __a)
{
  return __builtin_csky_vabsv2sq (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vadd_es8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vaddesv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vadd_eu8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vaddeuv8qi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vadd_es16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vaddesv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vadd_eu16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vaddeuv4hi (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vadd_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __a + __b;
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vadd_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vadd_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __a + __b;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vadd_s8 (int8x8_t __a, int8x8_t __b)
{
  return __a + __b;
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vadd_s16 (int16x4_t __a, int16x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vadd_s32 (int32x2_t __a, int32x2_t __b)
{
  return __a + __b;
}

__extension__ static __inline usat8x8_t __attribute__ ((__always_inline__))
vadd_u8_s (usat8x8_t __a, usat8x8_t __b)
{
  return __a + __b;
}

__extension__ static __inline usat16x4_t __attribute__ ((__always_inline__))
vadd_u16_s (usat16x4_t __a, usat16x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline usat32x2_t __attribute__ ((__always_inline__))
vadd_u32_s (usat32x2_t __a, usat32x2_t __b)
{
  return __a + __b;;
}

__extension__ static __inline sat8x8_t __attribute__ ((__always_inline__))
vadd_s8_s (sat8x8_t __a, sat8x8_t __b)
{
  return __a + __b;
}

__extension__ static __inline sat16x4_t __attribute__ ((__always_inline__))
vadd_s16_s (sat16x4_t __a, sat16x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline sat32x2_t __attribute__ ((__always_inline__))
vadd_s32_s (sat32x2_t __a, sat32x2_t __b)
{
  return __a + __b;
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vsub_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __a - __b;
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsub_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsub_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __a - __b;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vsub_s8 (int8x8_t __a, int8x8_t __b)
{
  return __a - __b;
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsub_s16 (int16x4_t __a, int16x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsub_s32 (int32x2_t __a, int32x2_t __b)
{
  return __a - __b;
}

__extension__ static __inline usat8x8_t __attribute__ ((__always_inline__))
vsub_u8_s (usat8x8_t __a, usat8x8_t __b)
{
  return __a - __b;
}

__extension__ static __inline usat16x4_t __attribute__ ((__always_inline__))
vsub_u16_s (usat16x4_t __a, usat16x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline usat32x2_t __attribute__ ((__always_inline__))
vsub_u32_s (usat32x2_t __a, usat32x2_t __b)
{
  return __a - __b;;
}

__extension__ static __inline sat8x8_t __attribute__ ((__always_inline__))
vsub_s8_s (sat8x8_t __a, sat8x8_t __b)
{
  return __a - __b;
}

__extension__ static __inline sat16x4_t __attribute__ ((__always_inline__))
vsub_s16_s (sat16x4_t __a, sat16x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline sat32x2_t __attribute__ ((__always_inline__))
vsub_s32_s (sat32x2_t __a, sat32x2_t __b)
{
  return __a - __b;
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vadd_xu16 (uint8x8_t __a, uint16x4_t __b)
{
  return __builtin_csky_vaddxuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vadd_xu32 (uint16x4_t __a, uint32x2_t __b)
{
  return __builtin_csky_vaddxuv2si (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vadd_xs16 (int8x8_t __a, int16x4_t __b)
{
  return __builtin_csky_vaddxsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vadd_xs32 (int16x4_t __a, int32x2_t __b)
{
  return __builtin_csky_vaddxsv2si (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsub_xu16 (uint8x8_t __a, uint16x4_t __b)
{
  return __builtin_csky_vsubxuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsub_xu32 (uint16x4_t __a, uint32x2_t __b)
{
  return __builtin_csky_vsubxuv2si (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsub_xs16 (int8x8_t __a, int16x4_t __b)
{
  return __builtin_csky_vsubxsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsub_xs32 (int16x4_t __a, int32x2_t __b)
{
  return __builtin_csky_vsubxsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vadd_xu16_sl (uint8x8_t __a, uint16x4_t __b)
{
  return __builtin_csky_vaddxsluv4hi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vadd_xu32_sl (uint16x4_t __a, uint32x2_t __b)
{
  return __builtin_csky_vaddxsluv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vadd_xs16_sl (int8x8_t __a, int16x4_t __b)
{
  return __builtin_csky_vaddxslsv4hi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vadd_xs32_sl (int16x4_t __a, int32x2_t __b)
{
  return __builtin_csky_vaddxslsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vaddh_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vaddhuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vaddh_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vaddhuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vaddh_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vaddhuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vaddh_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vaddhsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vaddh_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vaddhsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vaddh_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vaddhsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vaddh_u8_r (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vaddhruv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vaddh_u16_r (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vaddhruv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vaddh_u32_r (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vaddhruv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vaddh_s8_r (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vaddhrsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vaddh_s16_r (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vaddhrsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vaddh_s32_r (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vaddhrsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vsubh_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vsubhuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsubh_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vsubhuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsubh_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vsubhuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vsubh_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vsubhsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsubh_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vsubhsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsubh_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vsubhsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vsubh_u8_r (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vsubhruv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsubh_u16_r (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vsubhruv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsubh_u32_r (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vsubhruv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vsubh_s8_r (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vsubhrsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsubh_s16_r (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vsubhrsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsubh_s32_r (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vsubhrsv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vand_8 (int8x8_t __a, int8x8_t __b)
{
  return __a & __b;
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vand_16 (int16x4_t __a, int16x4_t __b)
{
  return __a & __b;
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vand_32 (int32x2_t __a, int32x2_t __b)
{
  return __a & __b;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vandn_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vandnv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vandn_16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vandnv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vandn_32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vandnv2si (__a, __b);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vbperm_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vbpermv8qi (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vbpermz_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vbpermzv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcadd_es8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vcaddesv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcadd_eu8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vcaddeuv8qi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcadd_es16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vcaddesv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcadd_eu16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vcaddeuv4hi (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcadd_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vcadduv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcadd_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vcadduv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcadd_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vcadduv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcadd_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vcaddsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcadd_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vcaddsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcadd_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vcaddsv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcls_s8 (int8x8_t __a)
{
  return __builtin_csky_vclssv8qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcls_s16 (int16x4_t __a)
{
  return __builtin_csky_vclssv4hi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcls_s32 (int32x2_t __a)
{
  return __builtin_csky_vclssv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vclz_8 (int8x8_t __a)
{
  return __builtin_csky_vclzv8qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vclz_16 (int16x4_t __a)
{
  return __builtin_csky_vclzv4hi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vclz_32 (int32x2_t __a)
{
  return __builtin_csky_vclzv2si (__a);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcmax_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vcmaxuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcmax_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vcmaxuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcmax_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vcmaxuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcmax_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vcmaxsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcmax_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vcmaxsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcmax_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vcmaxsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcmin_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vcminuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcmin_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vcminuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcmin_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vcminuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcmin_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vcminsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcmin_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vcminsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcmin_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vcminsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcmphs_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vcmphsuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcmphs_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vcmphsuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcmphs_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vcmphsuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcmphs_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vcmphssv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcmphs_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vcmphssv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcmphs_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vcmphssv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcmphsz_u8 (uint8x8_t __a)
{
  return __builtin_csky_vcmphszuv8qi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcmphsz_u16 (uint16x4_t __a)
{
  return __builtin_csky_vcmphszuv4hi (__a);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcmphsz_u32 (uint32x2_t __a)
{
  return __builtin_csky_vcmphszuv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcmphsz_s8 (int8x8_t __a)
{
  return __builtin_csky_vcmphszsv8qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcmphsz_s16 (int16x4_t __a)
{
  return __builtin_csky_vcmphszsv4hi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcmphsz_s32 (int32x2_t __a)
{
  return __builtin_csky_vcmphszsv2si (__a);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcmplt_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vcmpltuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcmplt_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vcmpltuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcmplt_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vcmpltuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcmplt_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vcmpltsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcmplt_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vcmpltsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcmplt_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vcmpltsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcmpltz_u8 (uint8x8_t __a)
{
  return __builtin_csky_vcmpltzuv8qi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcmpltz_u16 (uint16x4_t __a)
{
  return __builtin_csky_vcmpltzuv4hi (__a);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcmpltz_u32 (uint32x2_t __a)
{
  return __builtin_csky_vcmpltzuv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcmpltz_s8 (int8x8_t __a)
{
  return __builtin_csky_vcmpltzsv8qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcmpltz_s16 (int16x4_t __a)
{
  return __builtin_csky_vcmpltzsv4hi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcmpltz_s32 (int32x2_t __a)
{
  return __builtin_csky_vcmpltzsv2si (__a);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcmpne_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vcmpneuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcmpne_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vcmpneuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcmpne_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vcmpneuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcmpne_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vcmpnesv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcmpne_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vcmpnesv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcmpne_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vcmpnesv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vcmpnez_u8 (uint8x8_t __a)
{
  return __builtin_csky_vcmpnezuv8qi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vcmpnez_u16 (uint16x4_t __a)
{
  return __builtin_csky_vcmpnezuv4hi (__a);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vcmpnez_u32 (uint32x2_t __a)
{
  return __builtin_csky_vcmpnezuv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcmpnez_s8 (int8x8_t __a)
{
  return __builtin_csky_vcmpnezsv8qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vcmpnez_s16 (int16x4_t __a)
{
  return __builtin_csky_vcmpnezsv4hi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vcmpnez_s32 (int32x2_t __a)
{
  return __builtin_csky_vcmpnezsv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vcnt1_8 (int8x8_t __a)
{
  return __builtin_csky_vcnt1v8qi (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vdch_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vdchv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vdch_16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vdchv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vdch_32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vdchv2si (__a, __b);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vdcl_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vdclv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vdcl_16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vdclv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vdcl_32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vdclv2si (__a, __b);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vdup_8 (int8x8_t __a, const int __b)
{
  return __builtin_csky_vdupv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vdup_16 (int16x4_t __a, const int __b)
{
  return __builtin_csky_vdupv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vdup_32 (int32x2_t __a, const int __b)
{
  return __builtin_csky_vdupv2si (__a, __b);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vich_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vichv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vich_16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vichv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vich_32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vichv2si (__a, __b);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vicl_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_viclv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vicl_16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_viclv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vicl_32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_viclv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vins_8 (const int __a, int8x8_t __b, const int __c)
{
  return __builtin_csky_vinsv8qi (__a, __b, __c);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vins_16 (const int __a, int16x4_t __b, const int __c)
{
  return __builtin_csky_vinsv4hi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vins_32 (const int __a, int32x2_t __b, const int __c)
{
  return __builtin_csky_vinsv2si (__a, __b, __c);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vldd_8 (int __a, const int __b)
{
  return __builtin_csky_vlddv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vldd_16 (int __a, const int __b)
{
  return __builtin_csky_vlddv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vldd_32 (int __a, const int __b)
{
  return __builtin_csky_vlddv2si (__a, __b);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vldq_8 (int __a, const int __b)
{
  return __builtin_csky_vldqv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vldq_16 (int __a, const int __b)
{
  return __builtin_csky_vldqv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vldq_32 (int __a, const int __b)
{
  return __builtin_csky_vldqv2si (__a, __b);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vstd_8 (int __a, const int __b)
{
  return __builtin_csky_vstdv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vstd_16 (int __a, const int __b)
{
  return __builtin_csky_vstdv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vstd_32 (int __a, const int __b)
{
  return __builtin_csky_vstdv2si (__a, __b);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vstq_8 (int __a, const int __b)
{
  return __builtin_csky_vstqv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vstq_16 (int __a, const int __b)
{
  return __builtin_csky_vstqv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vstq_32 (int __a, const int __b)
{
  return __builtin_csky_vstqv2si (__a, __b);;
}



__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vldrd_8 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrdv8qi (__a, __b, __c);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vldrd_16 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrdv4hi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vldrd_32 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrdv2si (__a, __b, __c);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vldrq_8 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrqv8qi (__a, __b, __c);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vldrq_16 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrqv4hi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vldrq_32 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrqv2si (__a, __b, __c);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vstrd_8 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrdv8qi (__a, __b, __c);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vstrd_16 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrdv4hi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vstrd_32 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrdv2si (__a, __b, __c);;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vstrq_8 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrqv8qi (__a, __b, __c);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vstrq_16 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrqv4hi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vstrq_32 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrqv2si (__a, __b, __c);;
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmax_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vumaxv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmax_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vumaxv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmax_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vumaxv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmax_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vsmaxv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmax_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vsmaxv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmax_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vsmaxv2si (__a, __b);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmin_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vuminv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmin_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vuminv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmin_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vuminv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmin_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vsminv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmin_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vsminv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmin_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vsminv2si (__a, __b);
}


__extension__ static __inline unsigned char __attribute__ ((__always_inline__))
vmfvr_u8 (uint8x8_t __a, const int __b)
{
  return __builtin_csky_vmfvruv8qi (__a, __b);
}

__extension__ static __inline unsigned short __attribute__ ((__always_inline__))
vmfvr_u16 (uint16x4_t __a, const int __b)
{
  return __builtin_csky_vmfvruv4hi (__a, __b);
}

__extension__ static __inline unsigned int __attribute__ ((__always_inline__))
vmfvr_u32 (uint32x2_t __a, const int __b)
{
  return __builtin_csky_vmfvruv2si (__a, __b);
}

__extension__ static __inline char __attribute__ ((__always_inline__))
vmfvr_s8 (int8x8_t __a, const int __b)
{
  return __builtin_csky_vmfvrsv8qi (__a, __b);
}

__extension__ static __inline short __attribute__ ((__always_inline__))
vmfvr_s16 (int16x4_t __a, const int __b)
{
  return __builtin_csky_vmfvrsv4hi (__a, __b);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmtvr_u8 (const int __a, unsigned char __b)
{
  return __builtin_csky_vmtvruv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmtvr_u16 (const int __a, unsigned short __b)
{
  return __builtin_csky_vmtvruv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmtvr_u32 (const int __a, unsigned int __b)
{
  return __builtin_csky_vmtvruv2si (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmov_es8 (int8x8_t __a)
{
  return __builtin_csky_vmovesv8qi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmov_eu8 (uint8x8_t __a)
{
  return __builtin_csky_vmoveuv8qi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmov_es16 (int16x4_t __a)
{
  return __builtin_csky_vmovesv4hi (__a);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmov_eu16 (uint16x4_t __a)
{
  return __builtin_csky_vmoveuv4hi (__a);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmov_u16_h (uint16x4_t __a)
{
  return __builtin_csky_vmovhuv4hi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmov_u32_h (uint32x2_t __a)
{
  return __builtin_csky_vmovhuv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmov_s16_h (int16x4_t __a)
{
  return __builtin_csky_vmovhsv4hi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmov_s32_h (int32x2_t __a)
{
  return __builtin_csky_vmovhsv2si (__a);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmov_u16_l (uint16x4_t __a)
{
  return __builtin_csky_vmovluv4hi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmov_u32_l (uint32x2_t __a)
{
  return __builtin_csky_vmovluv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmov_s16_l (int16x4_t __a)
{
  return __builtin_csky_vmovlsv4hi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmov_s32_l (int32x2_t __a)
{
  return __builtin_csky_vmovlsv2si (__a);
}



__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmov_u16_rh (uint16x4_t __a)
{
  return __builtin_csky_vmovrhuv4hi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmov_u32_rh (uint32x2_t __a)
{
  return __builtin_csky_vmovrhuv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmov_s16_rh (int16x4_t __a)
{
  return __builtin_csky_vmovrhsv4hi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmov_s32_rh (int32x2_t __a)
{
  return __builtin_csky_vmovrhsv2si (__a);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmov_u16_sl (uint16x4_t __a)
{
  return __builtin_csky_vmovsluv4hi (__a);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmov_u32_sl (uint32x2_t __a)
{
  return __builtin_csky_vmovsluv2si (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmov_s16_sl (int16x4_t __a)
{
  return __builtin_csky_vmovslsv4hi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmov_s32_sl (int32x2_t __a)
{
  return __builtin_csky_vmovslsv2si (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmul_es8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vmulesv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmul_eu8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vmuleuv8qi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmul_es16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vmulesv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmul_eu16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vmuleuv4hi (__a, __b);
}


__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmula_es8 (int8x8_t __a, int8x8_t __b, int16x4_t __c)
{
  return __builtin_csky_vmulaesv8qi (__a, __b, __c);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmula_eu8 (uint8x8_t __a, uint8x8_t __b, uint16x4_t __c)
{
  return __builtin_csky_vmulaeuv8qi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmula_es16 (int16x4_t __a, int16x4_t __b, int32x2_t __c)
{
  return __builtin_csky_vmulaesv4hi (__a, __b, __c);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmula_eu16 (uint16x4_t __a, uint16x4_t __b, uint32x2_t __c)
{
  return __builtin_csky_vmulaeuv4hi (__a, __b, __c);
}


__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmuls_es8 (int8x8_t __a, int8x8_t __b, int16x4_t __c)
{
  return __builtin_csky_vmulsesv8qi (__a, __b, __c);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmuls_eu8 (uint8x8_t __a, uint8x8_t __b, uint16x4_t __c)
{
  return __builtin_csky_vmulseuv8qi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmuls_es16 (int16x4_t __a, int16x4_t __b, int32x2_t __c)
{
  return __builtin_csky_vmulsesv4hi (__a, __b, __c);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmuls_eu16 (uint16x4_t __a, uint16x4_t __b, uint32x2_t __c)
{
  return __builtin_csky_vmulseuv4hi (__a, __b, __c);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmula_u8 (uint8x8_t __a, uint8x8_t __b, uint8x8_t __c)
{
  return __builtin_csky_vmulauv8qi (__a, __b, __c);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmula_u16 (uint16x4_t __a, uint16x4_t __b, uint16x4_t __c)
{
  return __builtin_csky_vmulauv4hi (__a, __b, __c);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmula_u32 (uint32x2_t __a, uint32x2_t __b, uint32x2_t __c)
{
  return __builtin_csky_vmulauv2si (__a, __b, __c);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmula_s8 (int8x8_t __a, int8x8_t __b, int8x8_t __c)
{
  return __builtin_csky_vmulasv8qi (__a, __b, __c);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmula_s16 (int16x4_t __a, int16x4_t __b, int16x4_t __c)
{
  return __builtin_csky_vmulasv4hi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmula_s32 (int32x2_t __a, int32x2_t __b, int32x2_t __c)
{
  return __builtin_csky_vmulasv2si (__a, __b, __c);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmuls_u8 (uint8x8_t __a, uint8x8_t __b, uint8x8_t __c)
{
  return __builtin_csky_vmulsuv8qi (__a, __b, __c);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmuls_u16 (uint16x4_t __a, uint16x4_t __b, uint16x4_t __c)
{
  return __builtin_csky_vmulsuv4hi (__a, __b, __c);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmuls_u32 (uint32x2_t __a, uint32x2_t __b, uint32x2_t __c)
{
  return __builtin_csky_vmulsuv2si (__a, __b, __c);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmuls_s8 (int8x8_t __a, int8x8_t __b, int8x8_t __c)
{
  return __builtin_csky_vmulssv8qi (__a, __b, __c);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmuls_s16 (int16x4_t __a, int16x4_t __b, int16x4_t __c)
{
  return __builtin_csky_vmulssv4hi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmuls_s32 (int32x2_t __a, int32x2_t __b, int32x2_t __c)
{
  return __builtin_csky_vmulssv2si (__a, __b, __c);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vmul_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vmul_uv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vmul_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vmul_uv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vmul_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vmul_uv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vmul_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vmul_sv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vmul_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vmul_sv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vmul_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vmul_sv2si (__a, __b);
}


__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vneg_s8 (int8x8_t __a)
{
  return __builtin_csky_vnegv8qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vneg_s16 (int16x4_t __a)
{
  return __builtin_csky_vnegv4hi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vneg_s32 (int32x2_t __a)
{
  return __builtin_csky_vnegv2si (__a);
}

__extension__ static __inline sat8x8_t __attribute__ ((__always_inline__))
vneg_s8_s (sat8x8_t __a)
{
  return __builtin_csky_vnegv8qq (__a);
}

__extension__ static __inline sat16x4_t __attribute__ ((__always_inline__))
vneg_s16_s (sat16x4_t __a)
{
  return __builtin_csky_vnegv4hq (__a);
}

__extension__ static __inline sat32x2_t __attribute__ ((__always_inline__))
vneg_s32_s (sat32x2_t __a)
{
  return __builtin_csky_vnegv2sq (__a);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vor_8 (int8x8_t __a, int8x8_t __b)
{
  return __a | __b;
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vor_16 (int16x4_t __a, int16x4_t __b)
{
  return __a | __b;
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vor_32 (int32x2_t __a, int32x2_t __b)
{
  return __a | __b;
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vrev_8 (int8x8_t __a)
{
  return __builtin_csky_vrevv8qi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vrev_16 (int16x4_t __a)
{
  return __builtin_csky_vrevv4hi (__a);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vrev_32 (int32x2_t __a)
{
  return __builtin_csky_vrevv2si (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsabs_es8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vsabsesv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsabs_eu8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vsabseuv8qi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsabs_es16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vsabsesv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsabs_eu16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vsabseuv4hi (__a, __b);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vsabs_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vsabsuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsabs_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vsabsuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsabs_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vsabsuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vsabs_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vsabssv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsabs_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vsabssv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsabs_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vsabssv2si (__a, __b);
}


__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsabsa_es8 (int8x8_t __a, int8x8_t __b, int16x4_t __c)
{
  return __builtin_csky_vsabsaesv8qi (__a, __b, __c);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsabsa_eu8 (uint8x8_t __a, uint8x8_t __b, uint16x4_t __c)
{
  return __builtin_csky_vsabsaeuv8qi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsabsa_es16 (int16x4_t __a, int16x4_t __b, int32x2_t __c)
{
  return __builtin_csky_vsabsaesv4hi (__a, __b, __c);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsabsa_eu16 (uint16x4_t __a, uint16x4_t __b, uint32x2_t __c)
{
  return __builtin_csky_vsabsaeuv4hi (__a, __b, __c);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vsabsa_u8 (uint8x8_t __a, uint8x8_t __b, uint8x8_t __c)
{
  return __builtin_csky_vsabsauv8qi (__a, __b, __c);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsabsa_u16 (uint16x4_t __a, uint16x4_t __b, uint16x4_t __c)
{
  return __builtin_csky_vsabsauv4hi (__a, __b, __c);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsabsa_u32 (uint32x2_t __a, uint32x2_t __b, uint32x2_t __c)
{
  return __builtin_csky_vsabsauv2si (__a, __b, __c);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vsabsa_s8 (int8x8_t __a, int8x8_t __b, int8x8_t __c)
{
  return __builtin_csky_vsabsasv8qi (__a, __b, __c);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsabsa_s16 (int16x4_t __a, int16x4_t __b, int16x4_t __c)
{
  return __builtin_csky_vsabsasv4hi (__a, __b, __c);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsabsa_s32 (int32x2_t __a, int32x2_t __b, int32x2_t __c)
{
  return __builtin_csky_vsabsasv2si (__a, __b, __c);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vshl_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vshluv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vshl_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vshluv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vshl_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vshluv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vshl_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vshlsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vshl_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vshlsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vshl_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vshlsv2si (__a, __b);
}

__extension__ static __inline usat8x8_t __attribute__ ((__always_inline__))
vshl_u8_s (usat8x8_t __a, usat8x8_t __b)
{
  return __builtin_csky_vshlv8uqq (__a, __b);
}

__extension__ static __inline usat16x4_t __attribute__ ((__always_inline__))
vshl_u16_s (usat16x4_t __a, usat16x4_t __b)
{
  return __builtin_csky_vshlv4uhq (__a, __b);
}

__extension__ static __inline usat32x2_t __attribute__ ((__always_inline__))
vshl_u32_s (usat32x2_t __a, usat32x2_t __b)
{
  return __builtin_csky_vshlv2usq (__a, __b);
}

__extension__ static __inline sat8x8_t __attribute__ ((__always_inline__))
vshl_s8_s (sat8x8_t __a, sat8x8_t __b)
{
  return __builtin_csky_vshlv8qq (__a, __b);
}

__extension__ static __inline sat16x4_t __attribute__ ((__always_inline__))
vshl_s16_s (sat16x4_t __a, sat16x4_t __b)
{
  return __builtin_csky_vshlv4hq (__a, __b);
}

__extension__ static __inline sat32x2_t __attribute__ ((__always_inline__))
vshl_s32_s (sat32x2_t __a, sat32x2_t __b)
{
  return __builtin_csky_vshlv2sq (__a, __b);
}



__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vshli_u8 (uint8x8_t __a, const int __b)
{
  return __builtin_csky_vshliuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vshli_u16 (uint16x4_t __a, const int __b)
{
  return __builtin_csky_vshliuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vshli_u32 (uint32x2_t __a, const int __b)
{
  return __builtin_csky_vshliuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vshli_s8 (int8x8_t __a, const int __b)
{
  return __builtin_csky_vshlisv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vshli_s16 (int16x4_t __a, const int __b)
{
  return __builtin_csky_vshlisv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vshli_s32 (int32x2_t __a, const int __b)
{
  return __builtin_csky_vshlisv2si (__a, __b);
}

__extension__ static __inline usat8x8_t __attribute__ ((__always_inline__))
vshli_u8_s (usat8x8_t __a, const int __b)
{
  return __builtin_csky_vshliv8uqq (__a, __b);
}

__extension__ static __inline usat16x4_t __attribute__ ((__always_inline__))
vshli_u16_s (usat16x4_t __a, const int __b)
{
  return __builtin_csky_vshliv4uhq (__a, __b);
}

__extension__ static __inline usat32x2_t __attribute__ ((__always_inline__))
vshli_u32_s (usat32x2_t __a, const int __b)
{
  return __builtin_csky_vshliv2usq (__a, __b);
}

__extension__ static __inline sat8x8_t __attribute__ ((__always_inline__))
vshli_s8_s (sat8x8_t __a, const int __b)
{
  return __builtin_csky_vshliv8qq (__a, __b);
}

__extension__ static __inline sat16x4_t __attribute__ ((__always_inline__))
vshli_s16_s (sat16x4_t __a, const int __b)
{
  return __builtin_csky_vshliv4hq (__a, __b);
}

__extension__ static __inline sat32x2_t __attribute__ ((__always_inline__))
vshli_s32_s (sat32x2_t __a, const int __b)
{
  return __builtin_csky_vshliv2sq (__a, __b);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vshr_u8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vshruv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vshr_u16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vshruv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vshr_u32 (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vshruv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vshr_s8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vshrsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vshr_s16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vshrsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vshr_s32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vshrsv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vshr_u8_r (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vshrruv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vshr_u16_r (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vshrruv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vshr_u32_r (uint32x2_t __a, uint32x2_t __b)
{
  return __builtin_csky_vshrruv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vshr_s8_r (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vshrrsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vshr_s16_r (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vshrrsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vshr_s32_r (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vshrrsv2si (__a, __b);
}


__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vshri_u8 (uint8x8_t __a, const int __b)
{
  return __builtin_csky_vshriuv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vshri_u16 (uint16x4_t __a, const int __b)
{
  return __builtin_csky_vshriuv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vshri_u32 (uint32x2_t __a, const int __b)
{
  return __builtin_csky_vshriuv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vshri_s8 (int8x8_t __a, const int __b)
{
  return __builtin_csky_vshrisv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vshri_s16 (int16x4_t __a, const int __b)
{
  return __builtin_csky_vshrisv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vshri_s32 (int32x2_t __a, const int __b)
{
  return __builtin_csky_vshrisv2si (__a, __b);
}

__extension__ static __inline uint8x8_t __attribute__ ((__always_inline__))
vshri_u8_r (uint8x8_t __a, const int __b)
{
  return __builtin_csky_vshriruv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vshri_u16_r (uint16x4_t __a, const int __b)
{
  return __builtin_csky_vshriruv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vshri_u32_r (uint32x2_t __a, const int __b)
{
  return __builtin_csky_vshriruv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vshri_s8_r (int8x8_t __a, const int __b)
{
  return __builtin_csky_vshrirsv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vshri_s16_r (int16x4_t __a, const int __b)
{
  return __builtin_csky_vshrirsv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vshri_s32_r (int32x2_t __a, const int __b)
{
  return __builtin_csky_vshrirsv2si (__a, __b);
}


__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vstou_s16_sl (int16x4_t __a)
{
  return __builtin_csky_vstouslsv4hi (__a);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vstou_s32_sl (int32x2_t __a)
{
  return __builtin_csky_vstouslsv2si (__a);
}


__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vtrch_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vtrchv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vtrch_16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vtrchv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vtrch_32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vtrchv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vtrcl_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vtrclv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vtrcl_16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vtrclv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vtrcl_32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vtrclv2si (__a, __b);
}

__extension__ static __inline int8x8_t __attribute__ ((__always_inline__))
vtst_8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vtstv8qi (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vtst_16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vtstv4hi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vtst_32 (int32x2_t __a, int32x2_t __b)
{
  return __builtin_csky_vtstv2si (__a, __b);
}

__extension__ static __inline int16x4_t __attribute__ ((__always_inline__))
vsub_es8 (int8x8_t __a, int8x8_t __b)
{
  return __builtin_csky_vsubesv8qi (__a, __b);
}

__extension__ static __inline uint16x4_t __attribute__ ((__always_inline__))
vsub_eu8 (uint8x8_t __a, uint8x8_t __b)
{
  return __builtin_csky_vsubeuv8qi (__a, __b);
}

__extension__ static __inline int32x2_t __attribute__ ((__always_inline__))
vsub_es16 (int16x4_t __a, int16x4_t __b)
{
  return __builtin_csky_vsubesv4hi (__a, __b);
}

__extension__ static __inline uint32x2_t __attribute__ ((__always_inline__))
vsub_eu16 (uint16x4_t __a, uint16x4_t __b)
{
  return __builtin_csky_vsubeuv4hi (__a, __b);
}
#endif
#if defined (__CSKY_VDSP128__)
typedef __simd128_int8_t     int8x16_t;
typedef __simd128_uint8_t    uint8x16_t;
typedef __simd128_int16_t    int16x8_t;
typedef __simd128_uint16_t   uint16x8_t;
typedef __simd128_int32_t    int32x4_t;
typedef __simd128_uint32_t   uint32x4_t;
typedef __simd128_sat8_t     sat8x16_t;
typedef __simd128_usat8_t    usat8x16_t;
typedef __simd128_sat16_t    sat16x8_t;
typedef __simd128_usat16_t   usat16x8_t;
typedef __simd128_sat32_t    sat32x4_t;
typedef __simd128_usat32_t   usat32x4_t;

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vabs_s8 (int8x16_t __a)
{
  return __builtin_csky_vabsv16qi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vabs_s16 (int16x8_t __a)
{
  return __builtin_csky_vabsv8hi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vabs_s32 (int32x4_t __a)
{
  return __builtin_csky_vabsv4si (__a);
}

__extension__ static __inline sat8x16_t __attribute__ ((__always_inline__))
vabs_s8_s (sat8x16_t __a)
{
  return __builtin_csky_vabsv16qq (__a);
}

__extension__ static __inline sat16x8_t __attribute__ ((__always_inline__))
vabs_s16_s (sat16x8_t __a)
{
  return __builtin_csky_vabsv8hq (__a);
}

__extension__ static __inline sat32x4_t __attribute__ ((__always_inline__))
vabs_s32_s (sat32x4_t __a)
{
  return __builtin_csky_vabsv4sq (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vadd_es8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vaddesv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vadd_eu8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vaddeuv16qi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vadd_es16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vaddesv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vadd_eu16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vaddeuv8hi (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vadd_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __a + __b;
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vadd_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __a + __b;
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vadd_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vadd_s8 (int8x16_t __a, int8x16_t __b)
{
  return __a + __b;
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vadd_s16 (int16x8_t __a, int16x8_t __b)
{
  return __a + __b;
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vadd_s32 (int32x4_t __a, int32x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline usat8x16_t __attribute__ ((__always_inline__))
vadd_u8_s (usat8x16_t __a, usat8x16_t __b)
{
  return __a + __b;
}

__extension__ static __inline usat16x8_t __attribute__ ((__always_inline__))
vadd_u16_s (usat16x8_t __a, usat16x8_t __b)
{
  return __a + __b;
}

__extension__ static __inline usat32x4_t __attribute__ ((__always_inline__))
vadd_u32_s (usat32x4_t __a, usat32x4_t __b)
{
  return __a + __b;;
}

__extension__ static __inline sat8x16_t __attribute__ ((__always_inline__))
vadd_s8_s (sat8x16_t __a, sat8x16_t __b)
{
  return __a + __b;
}

__extension__ static __inline sat16x8_t __attribute__ ((__always_inline__))
vadd_s16_s (sat16x8_t __a, sat16x8_t __b)
{
  return __a + __b;
}

__extension__ static __inline sat32x4_t __attribute__ ((__always_inline__))
vadd_s32_s (sat32x4_t __a, sat32x4_t __b)
{
  return __a + __b;
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vsub_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __a - __b;
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsub_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __a - __b;
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsub_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vsub_s8 (int8x16_t __a, int8x16_t __b)
{
  return __a - __b;
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsub_s16 (int16x8_t __a, int16x8_t __b)
{
  return __a - __b;
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsub_s32 (int32x4_t __a, int32x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline usat8x16_t __attribute__ ((__always_inline__))
vsub_u8_s (usat8x16_t __a, usat8x16_t __b)
{
  return __a - __b;
}

__extension__ static __inline usat16x8_t __attribute__ ((__always_inline__))
vsub_u16_s (usat16x8_t __a, usat16x8_t __b)
{
  return __a - __b;
}

__extension__ static __inline usat32x4_t __attribute__ ((__always_inline__))
vsub_u32_s (usat32x4_t __a, usat32x4_t __b)
{
  return __a - __b;;
}

__extension__ static __inline sat8x16_t __attribute__ ((__always_inline__))
vsub_s8_s (sat8x16_t __a, sat8x16_t __b)
{
  return __a - __b;
}

__extension__ static __inline sat16x8_t __attribute__ ((__always_inline__))
vsub_s16_s (sat16x8_t __a, sat16x8_t __b)
{
  return __a - __b;
}

__extension__ static __inline sat32x4_t __attribute__ ((__always_inline__))
vsub_s32_s (sat32x4_t __a, sat32x4_t __b)
{
  return __a - __b;
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vadd_xu16 (uint8x16_t __a, uint16x8_t __b)
{
  return __builtin_csky_vaddxuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vadd_xu32 (uint16x8_t __a, uint32x4_t __b)
{
  return __builtin_csky_vaddxuv4si (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vadd_xs16 (int8x16_t __a, int16x8_t __b)
{
  return __builtin_csky_vaddxsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vadd_xs32 (int16x8_t __a, int32x4_t __b)
{
  return __builtin_csky_vaddxsv4si (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsub_xu16 (uint8x16_t __a, uint16x8_t __b)
{
  return __builtin_csky_vsubxuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsub_xu32 (uint16x8_t __a, uint32x4_t __b)
{
  return __builtin_csky_vsubxuv4si (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsub_xs16 (int8x16_t __a, int16x8_t __b)
{
  return __builtin_csky_vsubxsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsub_xs32 (int16x8_t __a, int32x4_t __b)
{
  return __builtin_csky_vsubxsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vadd_xu16_sl (uint8x16_t __a, uint16x8_t __b)
{
  return __builtin_csky_vaddxsluv8hi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vadd_xu32_sl (uint16x8_t __a, uint32x4_t __b)
{
  return __builtin_csky_vaddxsluv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vadd_xs16_sl (int8x16_t __a, int16x8_t __b)
{
  return __builtin_csky_vaddxslsv8hi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vadd_xs32_sl (int16x8_t __a, int32x4_t __b)
{
  return __builtin_csky_vaddxslsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vaddh_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vaddhuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vaddh_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vaddhuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vaddh_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vaddhuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vaddh_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vaddhsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vaddh_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vaddhsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vaddh_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vaddhsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vaddh_u8_r (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vaddhruv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vaddh_u16_r (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vaddhruv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vaddh_u32_r (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vaddhruv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vaddh_s8_r (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vaddhrsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vaddh_s16_r (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vaddhrsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vaddh_s32_r (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vaddhrsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vsubh_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vsubhuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsubh_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vsubhuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsubh_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vsubhuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vsubh_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vsubhsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsubh_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vsubhsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsubh_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vsubhsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vsubh_u8_r (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vsubhruv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsubh_u16_r (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vsubhruv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsubh_u32_r (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vsubhruv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vsubh_s8_r (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vsubhrsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsubh_s16_r (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vsubhrsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsubh_s32_r (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vsubhrsv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vand_8 (int8x16_t __a, int8x16_t __b)
{
  return __a & __b;
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vand_16 (int16x8_t __a, int16x8_t __b)
{
  return __a & __b;
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vand_32 (int32x4_t __a, int32x4_t __b)
{
  return __a & __b;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vandn_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vandnv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vandn_16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vandnv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vandn_32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vandnv4si (__a, __b);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vbperm_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vbpermv16qi (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vbpermz_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vbpermzv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcadd_es8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vcaddesv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcadd_eu8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vcaddeuv16qi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcadd_es16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vcaddesv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcadd_eu16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vcaddeuv8hi (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcadd_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vcadduv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcadd_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vcadduv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcadd_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vcadduv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcadd_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vcaddsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcadd_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vcaddsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcadd_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vcaddsv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcls_s8 (int8x16_t __a)
{
  return __builtin_csky_vclssv16qi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcls_s16 (int16x8_t __a)
{
  return __builtin_csky_vclssv8hi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcls_s32 (int32x4_t __a)
{
  return __builtin_csky_vclssv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vclz_8 (int8x16_t __a)
{
  return __builtin_csky_vclzv16qi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vclz_16 (int16x8_t __a)
{
  return __builtin_csky_vclzv8hi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vclz_32 (int32x4_t __a)
{
  return __builtin_csky_vclzv4si (__a);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcmax_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vcmaxuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcmax_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vcmaxuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcmax_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vcmaxuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcmax_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vcmaxsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcmax_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vcmaxsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcmax_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vcmaxsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcmin_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vcminuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcmin_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vcminuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcmin_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vcminuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcmin_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vcminsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcmin_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vcminsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcmin_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vcminsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcmphs_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vcmphsuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcmphs_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vcmphsuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcmphs_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vcmphsuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcmphs_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vcmphssv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcmphs_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vcmphssv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcmphs_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vcmphssv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcmphsz_u8 (uint8x16_t __a)
{
  return __builtin_csky_vcmphszuv16qi (__a);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcmphsz_u16 (uint16x8_t __a)
{
  return __builtin_csky_vcmphszuv8hi (__a);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcmphsz_u32 (uint32x4_t __a)
{
  return __builtin_csky_vcmphszuv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcmphsz_s8 (int8x16_t __a)
{
  return __builtin_csky_vcmphszsv16qi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcmphsz_s16 (int16x8_t __a)
{
  return __builtin_csky_vcmphszsv8hi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcmphsz_s32 (int32x4_t __a)
{
  return __builtin_csky_vcmphszsv4si (__a);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcmplt_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vcmpltuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcmplt_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vcmpltuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcmplt_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vcmpltuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcmplt_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vcmpltsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcmplt_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vcmpltsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcmplt_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vcmpltsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcmpltz_u8 (uint8x16_t __a)
{
  return __builtin_csky_vcmpltzuv16qi (__a);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcmpltz_u16 (uint16x8_t __a)
{
  return __builtin_csky_vcmpltzuv8hi (__a);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcmpltz_u32 (uint32x4_t __a)
{
  return __builtin_csky_vcmpltzuv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcmpltz_s8 (int8x16_t __a)
{
  return __builtin_csky_vcmpltzsv16qi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcmpltz_s16 (int16x8_t __a)
{
  return __builtin_csky_vcmpltzsv8hi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcmpltz_s32 (int32x4_t __a)
{
  return __builtin_csky_vcmpltzsv4si (__a);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcmpne_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vcmpneuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcmpne_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vcmpneuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcmpne_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vcmpneuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcmpne_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vcmpnesv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcmpne_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vcmpnesv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcmpne_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vcmpnesv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vcmpnez_u8 (uint8x16_t __a)
{
  return __builtin_csky_vcmpnezuv16qi (__a);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vcmpnez_u16 (uint16x8_t __a)
{
  return __builtin_csky_vcmpnezuv8hi (__a);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vcmpnez_u32 (uint32x4_t __a)
{
  return __builtin_csky_vcmpnezuv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcmpnez_s8 (int8x16_t __a)
{
  return __builtin_csky_vcmpnezsv16qi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vcmpnez_s16 (int16x8_t __a)
{
  return __builtin_csky_vcmpnezsv8hi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vcmpnez_s32 (int32x4_t __a)
{
  return __builtin_csky_vcmpnezsv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vcnt1_8 (int8x16_t __a)
{
  return __builtin_csky_vcnt1v16qi (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vdch_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vdchv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vdch_16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vdchv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vdch_32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vdchv4si (__a, __b);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vdcl_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vdclv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vdcl_16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vdclv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vdcl_32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vdclv4si (__a, __b);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vdup_8 (int8x16_t __a, const int __b)
{
  return __builtin_csky_vdupv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vdup_16 (int16x8_t __a, const int __b)
{
  return __builtin_csky_vdupv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vdup_32 (int32x4_t __a, const int __b)
{
  return __builtin_csky_vdupv4si (__a, __b);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vich_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vichv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vich_16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vichv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vich_32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vichv4si (__a, __b);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vicl_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_viclv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vicl_16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_viclv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vicl_32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_viclv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vins_8 (const int __a, int8x16_t __b, const int __c)
{
  return __builtin_csky_vinsv16qi (__a, __b, __c);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vins_16 (const int __a, int16x8_t __b, const int __c)
{
  return __builtin_csky_vinsv8hi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vins_32 (const int __a, int32x4_t __b, const int __c)
{
  return __builtin_csky_vinsv4si (__a, __b, __c);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vldd_8 (int __a, const int __b)
{
  return __builtin_csky_vlddv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vldd_16 (int __a, const int __b)
{
  return __builtin_csky_vlddv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vldd_32 (int __a, const int __b)
{
  return __builtin_csky_vlddv4si (__a, __b);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vldq_8 (int __a, const int __b)
{
  return __builtin_csky_vldqv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vldq_16 (int __a, const int __b)
{
  return __builtin_csky_vldqv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vldq_32 (int __a, const int __b)
{
  return __builtin_csky_vldqv4si (__a, __b);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vstd_8 (int __a, const int __b)
{
  return __builtin_csky_vstdv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vstd_16 (int __a, const int __b)
{
  return __builtin_csky_vstdv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vstd_32 (int __a, const int __b)
{
  return __builtin_csky_vstdv4si (__a, __b);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vstq_8 (int __a, const int __b)
{
  return __builtin_csky_vstqv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vstq_16 (int __a, const int __b)
{
  return __builtin_csky_vstqv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vstq_32 (int __a, const int __b)
{
  return __builtin_csky_vstqv4si (__a, __b);;
}



__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vldrd_8 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrdv16qi (__a, __b, __c);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vldrd_16 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrdv8hi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vldrd_32 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrdv4si (__a, __b, __c);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vldrq_8 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrqv16qi (__a, __b, __c);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vldrq_16 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrqv8hi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vldrq_32 (int __a, int __b, const int __c)
{
  return __builtin_csky_vldrqv4si (__a, __b, __c);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vstrd_8 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrdv16qi (__a, __b, __c);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vstrd_16 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrdv8hi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vstrd_32 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrdv4si (__a, __b, __c);;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vstrq_8 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrqv16qi (__a, __b, __c);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vstrq_16 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrqv8hi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vstrq_32 (int __a, int __b, const int __c)
{
  return __builtin_csky_vstrqv4si (__a, __b, __c);;
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmax_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vumaxv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmax_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vumaxv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmax_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vumaxv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmax_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vsmaxv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmax_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vsmaxv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmax_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vsmaxv4si (__a, __b);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmin_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vuminv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmin_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vuminv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmin_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vuminv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmin_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vsminv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmin_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vsminv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmin_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vsminv4si (__a, __b);
}


__extension__ static __inline unsigned char __attribute__ ((__always_inline__))
vmfvr_u8 (uint8x16_t __a, const int __b)
{
  return __builtin_csky_vmfvruv16qi (__a, __b);
}

__extension__ static __inline unsigned short __attribute__ ((__always_inline__))
vmfvr_u16 (uint16x8_t __a, const int __b)
{
  return __builtin_csky_vmfvruv8hi (__a, __b);
}

__extension__ static __inline unsigned int __attribute__ ((__always_inline__))
vmfvr_u32 (uint32x4_t __a, const int __b)
{
  return __builtin_csky_vmfvruv4si (__a, __b);
}

__extension__ static __inline char __attribute__ ((__always_inline__))
vmfvr_s8 (int8x16_t __a, const int __b)
{
  return __builtin_csky_vmfvrsv16qi (__a, __b);
}

__extension__ static __inline short __attribute__ ((__always_inline__))
vmfvr_s16 (int16x8_t __a, const int __b)
{
  return __builtin_csky_vmfvrsv8hi (__a, __b);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmtvr_u8 (const int __a, unsigned char __b)
{
  return __builtin_csky_vmtvruv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmtvr_u16 (const int __a, unsigned short __b)
{
  return __builtin_csky_vmtvruv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmtvr_u32 (const int __a, unsigned int __b)
{
  return __builtin_csky_vmtvruv4si (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmov_es8 (int8x16_t __a)
{
  return __builtin_csky_vmovesv16qi (__a);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmov_eu8 (uint8x16_t __a)
{
  return __builtin_csky_vmoveuv16qi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmov_es16 (int16x8_t __a)
{
  return __builtin_csky_vmovesv8hi (__a);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmov_eu16 (uint16x8_t __a)
{
  return __builtin_csky_vmoveuv8hi (__a);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmov_u16_h (uint16x8_t __a)
{
  return __builtin_csky_vmovhuv8hi (__a);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmov_u32_h (uint32x4_t __a)
{
  return __builtin_csky_vmovhuv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmov_s16_h (int16x8_t __a)
{
  return __builtin_csky_vmovhsv8hi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmov_s32_h (int32x4_t __a)
{
  return __builtin_csky_vmovhsv4si (__a);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmov_u16_l (uint16x8_t __a)
{
  return __builtin_csky_vmovluv8hi (__a);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmov_u32_l (uint32x4_t __a)
{
  return __builtin_csky_vmovluv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmov_s16_l (int16x8_t __a)
{
  return __builtin_csky_vmovlsv8hi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmov_s32_l (int32x4_t __a)
{
  return __builtin_csky_vmovlsv4si (__a);
}



__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmov_u16_rh (uint16x8_t __a)
{
  return __builtin_csky_vmovrhuv8hi (__a);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmov_u32_rh (uint32x4_t __a)
{
  return __builtin_csky_vmovrhuv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmov_s16_rh (int16x8_t __a)
{
  return __builtin_csky_vmovrhsv8hi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmov_s32_rh (int32x4_t __a)
{
  return __builtin_csky_vmovrhsv4si (__a);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmov_u16_sl (uint16x8_t __a)
{
  return __builtin_csky_vmovsluv8hi (__a);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmov_u32_sl (uint32x4_t __a)
{
  return __builtin_csky_vmovsluv4si (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmov_s16_sl (int16x8_t __a)
{
  return __builtin_csky_vmovslsv8hi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmov_s32_sl (int32x4_t __a)
{
  return __builtin_csky_vmovslsv4si (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmul_es8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vmulesv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmul_eu8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vmuleuv16qi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmul_es16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vmulesv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmul_eu16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vmuleuv8hi (__a, __b);
}


__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmula_es8 (int8x16_t __a, int8x16_t __b, int16x8_t __c)
{
  return __builtin_csky_vmulaesv16qi (__a, __b, __c);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmula_eu8 (uint8x16_t __a, uint8x16_t __b, uint16x8_t __c)
{
  return __builtin_csky_vmulaeuv16qi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmula_es16 (int16x8_t __a, int16x8_t __b, int32x4_t __c)
{
  return __builtin_csky_vmulaesv8hi (__a, __b, __c);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmula_eu16 (uint16x8_t __a, uint16x8_t __b, uint32x4_t __c)
{
  return __builtin_csky_vmulaeuv8hi (__a, __b, __c);
}


__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmuls_es8 (int8x16_t __a, int8x16_t __b, int16x8_t __c)
{
  return __builtin_csky_vmulsesv16qi (__a, __b, __c);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmuls_eu8 (uint8x16_t __a, uint8x16_t __b, uint16x8_t __c)
{
  return __builtin_csky_vmulseuv16qi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmuls_es16 (int16x8_t __a, int16x8_t __b, int32x4_t __c)
{
  return __builtin_csky_vmulsesv8hi (__a, __b, __c);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmuls_eu16 (uint16x8_t __a, uint16x8_t __b, uint32x4_t __c)
{
  return __builtin_csky_vmulseuv8hi (__a, __b, __c);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmula_u8 (uint8x16_t __a, uint8x16_t __b, uint8x16_t __c)
{
  return __builtin_csky_vmulauv16qi (__a, __b, __c);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmula_u16 (uint16x8_t __a, uint16x8_t __b, uint16x8_t __c)
{
  return __builtin_csky_vmulauv8hi (__a, __b, __c);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmula_u32 (uint32x4_t __a, uint32x4_t __b, uint32x4_t __c)
{
  return __builtin_csky_vmulauv4si (__a, __b, __c);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmula_s8 (int8x16_t __a, int8x16_t __b, int8x16_t __c)
{
  return __builtin_csky_vmulasv16qi (__a, __b, __c);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmula_s16 (int16x8_t __a, int16x8_t __b, int16x8_t __c)
{
  return __builtin_csky_vmulasv8hi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmula_s32 (int32x4_t __a, int32x4_t __b, int32x4_t __c)
{
  return __builtin_csky_vmulasv4si (__a, __b, __c);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmuls_u8 (uint8x16_t __a, uint8x16_t __b, uint8x16_t __c)
{
  return __builtin_csky_vmulsuv16qi (__a, __b, __c);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmuls_u16 (uint16x8_t __a, uint16x8_t __b, uint16x8_t __c)
{
  return __builtin_csky_vmulsuv8hi (__a, __b, __c);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmuls_u32 (uint32x4_t __a, uint32x4_t __b, uint32x4_t __c)
{
  return __builtin_csky_vmulsuv4si (__a, __b, __c);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmuls_s8 (int8x16_t __a, int8x16_t __b, int8x16_t __c)
{
  return __builtin_csky_vmulssv16qi (__a, __b, __c);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmuls_s16 (int16x8_t __a, int16x8_t __b, int16x8_t __c)
{
  return __builtin_csky_vmulssv8hi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmuls_s32 (int32x4_t __a, int32x4_t __b, int32x4_t __c)
{
  return __builtin_csky_vmulssv4si (__a, __b, __c);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vmul_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vmul_uv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vmul_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vmul_uv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vmul_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vmul_uv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vmul_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vmul_sv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vmul_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vmul_sv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vmul_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vmul_sv4si (__a, __b);
}


__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vneg_s8 (int8x16_t __a)
{
  return __builtin_csky_vnegv16qi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vneg_s16 (int16x8_t __a)
{
  return __builtin_csky_vnegv8hi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vneg_s32 (int32x4_t __a)
{
  return __builtin_csky_vnegv4si (__a);
}

__extension__ static __inline sat8x16_t __attribute__ ((__always_inline__))
vneg_s8_s (sat8x16_t __a)
{
  return __builtin_csky_vnegv16qq (__a);
}

__extension__ static __inline sat16x8_t __attribute__ ((__always_inline__))
vneg_s16_s (sat16x8_t __a)
{
  return __builtin_csky_vnegv8hq (__a);
}

__extension__ static __inline sat32x4_t __attribute__ ((__always_inline__))
vneg_s32_s (sat32x4_t __a)
{
  return __builtin_csky_vnegv4sq (__a);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vor_8 (int8x16_t __a, int8x16_t __b)
{
  return __a | __b;
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vor_16 (int16x8_t __a, int16x8_t __b)
{
  return __a | __b;
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vor_32 (int32x4_t __a, int32x4_t __b)
{
  return __a | __b;
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vrev_8 (int8x16_t __a)
{
  return __builtin_csky_vrevv16qi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vrev_16 (int16x8_t __a)
{
  return __builtin_csky_vrevv8hi (__a);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vrev_32 (int32x4_t __a)
{
  return __builtin_csky_vrevv4si (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsabs_es8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vsabsesv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsabs_eu8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vsabseuv16qi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsabs_es16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vsabsesv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsabs_eu16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vsabseuv8hi (__a, __b);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vsabs_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vsabsuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsabs_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vsabsuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsabs_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vsabsuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vsabs_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vsabssv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsabs_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vsabssv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsabs_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vsabssv4si (__a, __b);
}


__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsabsa_es8 (int8x16_t __a, int8x16_t __b, int16x8_t __c)
{
  return __builtin_csky_vsabsaesv16qi (__a, __b, __c);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsabsa_eu8 (uint8x16_t __a, uint8x16_t __b, uint16x8_t __c)
{
  return __builtin_csky_vsabsaeuv16qi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsabsa_es16 (int16x8_t __a, int16x8_t __b, int32x4_t __c)
{
  return __builtin_csky_vsabsaesv8hi (__a, __b, __c);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsabsa_eu16 (uint16x8_t __a, uint16x8_t __b, uint32x4_t __c)
{
  return __builtin_csky_vsabsaeuv8hi (__a, __b, __c);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vsabsa_u8 (uint8x16_t __a, uint8x16_t __b, uint8x16_t __c)
{
  return __builtin_csky_vsabsauv16qi (__a, __b, __c);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsabsa_u16 (uint16x8_t __a, uint16x8_t __b, uint16x8_t __c)
{
  return __builtin_csky_vsabsauv8hi (__a, __b, __c);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsabsa_u32 (uint32x4_t __a, uint32x4_t __b, uint32x4_t __c)
{
  return __builtin_csky_vsabsauv4si (__a, __b, __c);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vsabsa_s8 (int8x16_t __a, int8x16_t __b, int8x16_t __c)
{
  return __builtin_csky_vsabsasv16qi (__a, __b, __c);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsabsa_s16 (int16x8_t __a, int16x8_t __b, int16x8_t __c)
{
  return __builtin_csky_vsabsasv8hi (__a, __b, __c);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsabsa_s32 (int32x4_t __a, int32x4_t __b, int32x4_t __c)
{
  return __builtin_csky_vsabsasv4si (__a, __b, __c);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vshl_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vshluv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vshl_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vshluv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vshl_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vshluv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vshl_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vshlsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vshl_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vshlsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vshl_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vshlsv4si (__a, __b);
}

__extension__ static __inline usat8x16_t __attribute__ ((__always_inline__))
vshl_u8_s (usat8x16_t __a, usat8x16_t __b)
{
  return __builtin_csky_vshlv16uqq (__a, __b);
}

__extension__ static __inline usat16x8_t __attribute__ ((__always_inline__))
vshl_u16_s (usat16x8_t __a, usat16x8_t __b)
{
  return __builtin_csky_vshlv8uhq (__a, __b);
}

__extension__ static __inline usat32x4_t __attribute__ ((__always_inline__))
vshl_u32_s (usat32x4_t __a, usat32x4_t __b)
{
  return __builtin_csky_vshlv4usq (__a, __b);
}

__extension__ static __inline sat8x16_t __attribute__ ((__always_inline__))
vshl_s8_s (sat8x16_t __a, sat8x16_t __b)
{
  return __builtin_csky_vshlv16qq (__a, __b);
}

__extension__ static __inline sat16x8_t __attribute__ ((__always_inline__))
vshl_s16_s (sat16x8_t __a, sat16x8_t __b)
{
  return __builtin_csky_vshlv8hq (__a, __b);
}

__extension__ static __inline sat32x4_t __attribute__ ((__always_inline__))
vshl_s32_s (sat32x4_t __a, sat32x4_t __b)
{
  return __builtin_csky_vshlv4sq (__a, __b);
}



__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vshli_u8 (uint8x16_t __a, const int __b)
{
  return __builtin_csky_vshliuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vshli_u16 (uint16x8_t __a, const int __b)
{
  return __builtin_csky_vshliuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vshli_u32 (uint32x4_t __a, const int __b)
{
  return __builtin_csky_vshliuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vshli_s8 (int8x16_t __a, const int __b)
{
  return __builtin_csky_vshlisv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vshli_s16 (int16x8_t __a, const int __b)
{
  return __builtin_csky_vshlisv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vshli_s32 (int32x4_t __a, const int __b)
{
  return __builtin_csky_vshlisv4si (__a, __b);
}

__extension__ static __inline usat8x16_t __attribute__ ((__always_inline__))
vshli_u8_s (usat8x16_t __a, const int __b)
{
  return __builtin_csky_vshliv16uqq (__a, __b);
}

__extension__ static __inline usat16x8_t __attribute__ ((__always_inline__))
vshli_u16_s (usat16x8_t __a, const int __b)
{
  return __builtin_csky_vshliv8uhq (__a, __b);
}

__extension__ static __inline usat32x4_t __attribute__ ((__always_inline__))
vshli_u32_s (usat32x4_t __a, const int __b)
{
  return __builtin_csky_vshliv4usq (__a, __b);
}

__extension__ static __inline sat8x16_t __attribute__ ((__always_inline__))
vshli_s8_s (sat8x16_t __a, const int __b)
{
  return __builtin_csky_vshliv16qq (__a, __b);
}

__extension__ static __inline sat16x8_t __attribute__ ((__always_inline__))
vshli_s16_s (sat16x8_t __a, const int __b)
{
  return __builtin_csky_vshliv8hq (__a, __b);
}

__extension__ static __inline sat32x4_t __attribute__ ((__always_inline__))
vshli_s32_s (sat32x4_t __a, const int __b)
{
  return __builtin_csky_vshliv4sq (__a, __b);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vshr_u8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vshruv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vshr_u16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vshruv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vshr_u32 (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vshruv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vshr_s8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vshrsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vshr_s16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vshrsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vshr_s32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vshrsv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vshr_u8_r (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vshrruv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vshr_u16_r (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vshrruv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vshr_u32_r (uint32x4_t __a, uint32x4_t __b)
{
  return __builtin_csky_vshrruv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vshr_s8_r (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vshrrsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vshr_s16_r (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vshrrsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vshr_s32_r (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vshrrsv4si (__a, __b);
}


__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vshri_u8 (uint8x16_t __a, const int __b)
{
  return __builtin_csky_vshriuv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vshri_u16 (uint16x8_t __a, const int __b)
{
  return __builtin_csky_vshriuv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vshri_u32 (uint32x4_t __a, const int __b)
{
  return __builtin_csky_vshriuv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vshri_s8 (int8x16_t __a, const int __b)
{
  return __builtin_csky_vshrisv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vshri_s16 (int16x8_t __a, const int __b)
{
  return __builtin_csky_vshrisv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vshri_s32 (int32x4_t __a, const int __b)
{
  return __builtin_csky_vshrisv4si (__a, __b);
}

__extension__ static __inline uint8x16_t __attribute__ ((__always_inline__))
vshri_u8_r (uint8x16_t __a, const int __b)
{
  return __builtin_csky_vshriruv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vshri_u16_r (uint16x8_t __a, const int __b)
{
  return __builtin_csky_vshriruv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vshri_u32_r (uint32x4_t __a, const int __b)
{
  return __builtin_csky_vshriruv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vshri_s8_r (int8x16_t __a, const int __b)
{
  return __builtin_csky_vshrirsv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vshri_s16_r (int16x8_t __a, const int __b)
{
  return __builtin_csky_vshrirsv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vshri_s32_r (int32x4_t __a, const int __b)
{
  return __builtin_csky_vshrirsv4si (__a, __b);
}


__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vstou_s16_sl (int16x8_t __a)
{
  return __builtin_csky_vstouslsv8hi (__a);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vstou_s32_sl (int32x4_t __a)
{
  return __builtin_csky_vstouslsv4si (__a);
}


__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vtrch_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vtrchv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vtrch_16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vtrchv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vtrch_32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vtrchv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vtrcl_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vtrclv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vtrcl_16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vtrclv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vtrcl_32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vtrclv4si (__a, __b);
}

__extension__ static __inline int8x16_t __attribute__ ((__always_inline__))
vtst_8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vtstv16qi (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vtst_16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vtstv8hi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vtst_32 (int32x4_t __a, int32x4_t __b)
{
  return __builtin_csky_vtstv4si (__a, __b);
}

__extension__ static __inline int16x8_t __attribute__ ((__always_inline__))
vsub_es8 (int8x16_t __a, int8x16_t __b)
{
  return __builtin_csky_vsubesv16qi (__a, __b);
}

__extension__ static __inline uint16x8_t __attribute__ ((__always_inline__))
vsub_eu8 (uint8x16_t __a, uint8x16_t __b)
{
  return __builtin_csky_vsubeuv16qi (__a, __b);
}

__extension__ static __inline int32x4_t __attribute__ ((__always_inline__))
vsub_es16 (int16x8_t __a, int16x8_t __b)
{
  return __builtin_csky_vsubesv8hi (__a, __b);
}

__extension__ static __inline uint32x4_t __attribute__ ((__always_inline__))
vsub_eu16 (uint16x8_t __a, uint16x8_t __b)
{
  return __builtin_csky_vsubeuv8hi (__a, __b);
}
#endif

#endif
