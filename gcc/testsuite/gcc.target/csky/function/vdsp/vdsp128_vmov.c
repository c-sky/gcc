/* { dg-do compile } */
/*  {  dg-skip-if  "test is specific to ck810fv"  { csky-*-* }  { "*" }  { "-mcpu=ck810*fv*"  }  }  */
/* { dg-options "-O2 -mvdsp-width=128 -mhard-float -mcpu=ck810fv  -D__CSKY_VDSP128__" } */
#include "csky_vdsp.h"


#define TS(i) __simd128_int ## i ## _t
#define TU(i) __simd128_uint ## i ## _t
#define FUNCS(i) funcs ## i
#define BFUNCS(i) vmov_s ## i
#define FUNCU(i) funcu ## i
#define BFUNCU(i) vmov_u ## i

TS(8) FUNCS(8) (TS(8) a, TS(8) b){
	return BFUNCS(8)(b);
}

/* { dg-final { scan-assembler "vmov" } }*/

TS(16) FUNCS(16) (TS(16) a, TS(16) b){
	return BFUNCS(16)(b);
}

/* { dg-final { scan-assembler "vmov" } }*/


TS(32) FUNCS(32) (TS(32) a, TS(32) b){
	return BFUNCS(32)(b);
}

/* { dg-final { scan-assembler "vmov" } }*/


TU(8) FUNCU(8) (TU(8) a, TU(8) b){
	return BFUNCU(8)(b);
}

/* { dg-final { scan-assembler "vmov" } }*/

TU(16) FUNCU(16) (TU(16) a, TU(16) b){
	return BFUNCU(16)(b);
}

/* { dg-final { scan-assembler "vmov" } }*/


TU(32) FUNCU(32) (TU(32) a, TU(32) b){
	return BFUNCU(32)(b);
}

/* { dg-final { scan-assembler "vmov" } }*/

