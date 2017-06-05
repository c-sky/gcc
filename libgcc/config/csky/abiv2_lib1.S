/* libgcc routines for the CSKYCPU.
   Copyright (C) 1993, 1999, 2000, 2009 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */
#define CONCAT1(a, b) CONCAT2(a, b)
#define CONCAT2(a, b) a ## b
/* Use the right prefix for global labels.  */

#define SYM(x) CONCAT1 (__, x)

#ifdef __ELF__
#define TYPE(x) .type SYM (x),@function
#define SIZE(x) .size SYM (x), . - SYM (x)
#else
#define TYPE(x)
#define SIZE(x)
#endif

.macro FUNC_START name
        .text
    .align  2
        .globl SYM (\name)
        TYPE (\name)
SYM (\name):
.endm

.macro FUNC_END name
        SIZE (\name)
.endm

#if defined(__CK801__)
// attention: rx must not be zero, or cpu will in closed loop
// put result in rx, clobering ry.
.macro FF1_M rx, ry
    movi    \rx, 32
10:
    cmphsi  \ry, 1
    bf      11f
    subi    \rx, \rx, 1
    lsri    \ry, \ry, 1
    br      10b
11:
.endm
#else
.macro FF1_M rx, ry
    ff1     \rx, \ry
.endm
#endif

#if defined(__CK801__)
.macro LSLC_M rx
    cmpne   \rx, \rx
    addc    \rx, \rx
.endm
#else
.macro LSLC_M rx
    lslc    \rx
.endm
#endif

#if  defined(__CK802__)
// attention: r1 will be clobbered by rsubi
.macro ABS_M rx
    btsti   \rx, 31
    bf      10f
// FIXME rsubi \rx, 0
    not    \rx
    addi   \rx, 1
10:
.endm
#elif defined(__CK801__)
.macro ABS_M rx
    cmplti  \rx, 1
    bf      10f
    not     \rx
    addi    \rx, 1
10:
.endm
#else
.macro ABS_M rx
    abs     \rx
.endm
#endif

#if defined(__CK801__)
.macro LDBS_M rx, ry
    ld.b \rx, (\ry, 0x0)
    sextb \rx, \rx
.endm
#else
.macro LDBS_M rx, ry
    ld.bs \rx, (\ry, 0x0)
.endm
#endif

#if defined(__CK801__)
.macro LDHS_M rx, ry
    ld.h \rx, (\ry, 0x0)
    sexth \rx, \rx
.endm
#else
.macro LDHS_M rx, ry
    ld.hs \rx, (\ry, 0x0)
.endm
#endif

#ifdef  L_udivsi3
FUNC_START udiv32
FUNC_START udivsi3
    cmpnei  a1, 0       // look for 0 divisor
    bt      9f
    trap    3           // divide by 0
9:
// control iterations, skip across high order 0 bits in dividend
    cmpnei  a0, 0
    bt      8f
    jmp     lr         // 0 dividend quick return
8:
    push    l0
    movi    a2, 1       // a2 is quotient (1 for a sentinel)
    mov     a3, a0
    FF1_M   l0, a3      // figure distance to skip
    lsl     a2, l0      // move the sentinel along (with 0's behind)
    lsl     a0, l0      // and the low 32 bits of numerator

// FIXME maybe to be wrong... shangyh
    mov     a3, a1      // looking at divisor
    FF1_M   l0, a3      // I can move 32-l0 more bits to left.
    addi    l0, 1       // ok, one short of that...
    mov     a3, a0
    lsr     a3, l0      // bits that came from low order...
    not     l0          // l0 == "32-n" == LEFT distance
    addi    l0, 33      // this is (32-n)
    lsl     a2,l0       // fixes the high 32 (quotient)
    lsl     a0,l0
    cmpnei  a2,0
    bf          4f      // the sentinel went away...

// run the remaining bits

1:
    LSLC_M  a0          // 1 bit left shift of a3-a0
    addc    a3, a3
    cmphs   a3, a1      // upper 32 of dividend >= divisor?
    bf      2f
    subu    a3, a1      // if yes, subtract divisor
2:
    addc    a2, a2      // shift by 1 and count subtracts
    bf      1b          // if sentinel falls out of quotient, stop

4:
    mov     a0, a2      // return quotient
    mov     a1, a3      // and piggyback the remainder
    pop     l0
FUNC_END udiv32
FUNC_END udivsi3
#endif

#ifdef  L_umodsi3
FUNC_START urem32
FUNC_START umodsi3
    cmpnei  a1, 0       // look for 0 divisor
    bt      9f
    trap    3           // divide by 0
9:
// control iterations, skip across high order 0 bits in dividend
    cmpnei  a0, 0
    bt      8f
    jmp     lr         // 0 dividend quick return
8:
    mov     a2, a0
    FF1_M   a3, a2         // figure distance to skip
    movi    a2, 1       // a2 is quotient (1 for a sentinel)
    lsl     a2, a3      // move the sentinel along (with 0's behind)
    lsl     a0, a3      // and the low 32 bits of numerator
    movi    a3, 0

1:
    LSLC_M  a0          // 1 bit left shift of a3-a0
    addc    a3, a3
    cmphs   a3, a1      // upper 32 of dividend >= divisor?
    bf      2f
    subu    a3, a1      // if yes, subtract divisor
2:
    addc    a2, a2      // shift by 1 and count subtracts
    bf      1b          // if sentinel falls out of quotient, stop

4:
    mov     a0, a3      // and piggyback the remainder
    jmp     lr
FUNC_END urem32
FUNC_END umodsi3
#endif


#ifdef  L_divsi3
FUNC_START div32
FUNC_START divsi3
    cmpnei  a1, 0       // look for 0 divisor
    bt      9f
    trap    3           // divide by 0
9:
// control iterations, skip across high order 0 bits in dividend
    cmpnei  a0, 0
    bt      8f
    jmp     lr         // 0 dividend quick return
8:
    push    l0, l1
    mov     l1, a0
    xor     l1, a1      //// calc sign of quotient
    ABS_M   a0
    ABS_M   a1
    movi    a2, 1       // a2 is quotient (1 for a sentinel)
    mov     a3, a0
    FF1_M   l0, a3      // figure distance to skip
    lsl     a2, l0      // move the sentinel along (with 0's behind)
    lsl     a0, l0      // and the low 32 bits of numerator

// FIXME maybe to be wrong... shangyh
    mov     a3, a1      // looking at divisor
    FF1_M   l0, a3      // I can move 32-l0 more bits to left.
    addi    l0, 1       // ok, one short of that...
    mov     a3, a0
    lsr     a3, l0      // bits that came from low order...
    not     l0          // l0 == "32-n" == LEFT distance
    addi    l0, 33      // this is (32-n)
    lsl     a2,l0       // fixes the high 32 (quotient)
    lsl     a0,l0
    cmpnei  a2,0
    bf          4f      // the sentinel went away...

// run the remaining bits

1:
    LSLC_M  a0          // 1 bit left shift of a3-a0
    addc    a3, a3
    cmphs   a3, a1      // upper 32 of dividend >= divisor?
    bf      2f
    subu    a3, a1      // if yes, subtract divisor
2:
    addc    a2, a2      // shift by 1 and count subtracts
    bf      1b          // if sentinel falls out of quotient, stop

4:
    mov     a0, a2      // return quotient
    mov     a1, a3      // and piggyback the remainder
    LSLC_M  l1          // after adjusting for sign
    bf      3f
    not     a0
    addi    a0, 1
    not     a1
    addi    a1, 1
3:
    pop     l0, l1
FUNC_END div32
FUNC_END divsi3
#endif

#ifdef  L_modsi3
FUNC_START rem32
FUNC_START modsi3
    push     l0
    cmpnei  a1, 0       // look for 0 divisor
    bt      9f
    trap    3           // divide by 0
9:
// control iterations, skip across high order 0 bits in dividend
    cmpnei  a0, 0
    bt      8f
    pop     l0         // 0 dividend quick return
8:
    mov     l0, a0
    ABS_M   a0
    ABS_M   a1
    mov     a2, a0
    FF1_M   a3, a2      // figure distance to skip
    movi    a2, 1       // a2 is quotient (1 for a sentinel)
    lsl     a2, a3      // move the sentinel along (with 0's behind)
    lsl     a0, a3      // and the low 32 bits of numerator
    movi    a3, 0

// run the remaining bits

1:
    LSLC_M  a0          // 1 bit left shift of a3-a0
    addc    a3, a3
    cmphs   a3, a1      // upper 32 of dividend >= divisor?
    bf      2f
    subu    a3, a1      // if yes, subtract divisor
2:
    addc    a2, a2      // shift by 1 and count subtracts
    bf      1b          // if sentinel falls out of quotient, stop

4:
    mov     a0, a3      // and piggyback the remainder
    LSLC_M  l0      // after adjusting for sign
    bf      3f
    not     a0
    addi    a0, 1
3:
    pop     l0
FUNC_END rem32
FUNC_END modsi3
#endif

#ifdef L_csky_case_sqi
FUNC_START _gnu_csky_case_sqi
    subi    sp, 4
    st.w    a1, (sp, 0x0)
    mov     a1, lr
    add     a1, a1, a0
    LDBS_M  a1, a1
    lsli    a1, a1, 1
    add     lr, lr, a1
    ld.w    a1, (sp, 0x0)
    addi    sp, 4
    rts
FUNC_END _gnu_csky_case_sqi
#endif

#ifdef L_csky_case_uqi
FUNC_START _gnu_csky_case_uqi
    subi    sp, 4
    st.w    a1, (sp, 0x0)
    mov     a1, lr
    add     a1, a1, a0
    ld.b    a1, (a1, 0x0)
    lsli    a1, a1, 1
    add     lr, lr, a1
    ld.w    a1, (sp, 0x0)
    addi    sp, 4
    rts
FUNC_END _gnu_csky_case_uqi
#endif

#ifdef L_csky_case_shi
FUNC_START _gnu_csky_case_shi
    subi    sp, 8
    st.w    a0, (sp, 0x4)
    st.w    a1, (sp, 0x0)
    mov     a1, lr
    lsli    a0, a0, 1
    add     a1, a1, a0
    LDHS_M  a1, a1
    lsli    a1, a1, 1
    add     lr, lr, a1
    ld.w    a0, (sp, 0x4)
    ld.w    a1, (sp, 0x0)
    addi    sp, 8
    rts
FUNC_END _gnu_csky_case_shi
#endif

#ifdef L_csky_case_uhi
FUNC_START _gnu_csky_case_uhi
    subi    sp, 8
    st.w    a0, (sp, 0x4)
    st.w    a1, (sp, 0x0)
    mov     a1, lr
    lsli    a0, a0, 1
    add     a1, a1, a0
    ld.h    a1, (a1, 0x0)
    lsli    a1, a1, 1
    add     lr, lr, a1
    ld.w    a0, (sp, 0x4)
    ld.w    a1, (sp, 0x0)
    addi    sp, 8
    rts
FUNC_END _gnu_csky_case_uhi
#endif

#ifdef L_csky_case_si
FUNC_START _gnu_csky_case_si
    subi    sp, 8
    st.w    a0, (sp, 0x4)
    st.w    a1, (sp, 0x0)
    mov     a1, lr
    addi    a1, a1, 2  /* Align to word.  */
    bclri   a1, a1, 1
    mov     lr, a1
    lsli    a0, a0, 2
    add     a1, a1, a0
    ld.w    a0, (a1, 0x0)
    add     lr, lr, a0
    ld.w    a0, (sp, 0x4)
    ld.w    a1, (sp, 0x0)
    addi    sp, 8
    rts
FUNC_END _gnu_csky_case_si
#endif

/* GCC expects that {__eq,__ne,__gt,__ge,__le,__lt}{df2,sf2}
   will behave as __cmpdf2. So, we stub the implementations to
   jump on to __cmpdf2 and __cmpsf2.

   All of these shortcircuit the return path so that __cmp{sd}f2
   will go directly back to the caller.  */

.macro  COMPARE_DF_JUMP name
        .import SYM (cmpdf2)
FUNC_START \name
        jmpi SYM (cmpdf2)
FUNC_END \name
.endm

#ifdef  L_eqdf2
COMPARE_DF_JUMP eqdf2
#endif /* L_eqdf2 */

#ifdef  L_nedf2
COMPARE_DF_JUMP nedf2
#endif /* L_nedf2 */

#ifdef  L_gtdf2
COMPARE_DF_JUMP gtdf2
#endif /* L_gtdf2 */

#ifdef  L_gedf2
COMPARE_DF_JUMP gedf2
#endif /* L_gedf2 */

#ifdef  L_ltdf2
COMPARE_DF_JUMP ltdf2
#endif /* L_ltdf2 */

#ifdef  L_ledf2
COMPARE_DF_JUMP ledf2
#endif /* L_ledf2 */

/* SINGLE PRECISION FLOATING POINT STUBS */

.macro  COMPARE_SF_JUMP name
        .import SYM (cmpsf2)
FUNC_START \name
        jmpi SYM (cmpsf2)
FUNC_END \name
.endm

#ifdef  L_eqsf2
COMPARE_SF_JUMP eqsf2
#endif /* L_eqsf2 */

#ifdef  L_nesf2
COMPARE_SF_JUMP nesf2
#endif /* L_nesf2 */

#ifdef  L_gtsf2
COMPARE_SF_JUMP gtsf2
#endif /* L_gtsf2 */

#ifdef  L_gesf2
COMPARE_SF_JUMP __gesf2
#endif /* L_gesf2 */

#ifdef  L_ltsf2
COMPARE_SF_JUMP __ltsf2
#endif /* L_ltsf2 */

#ifdef  L_lesf2
COMPARE_SF_JUMP lesf2
#endif /* L_lesf2 */
