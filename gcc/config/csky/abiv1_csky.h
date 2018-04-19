/* Definitions of target machine for GNU compiler,
   for CSKY Processor.
   Copyright (C) 1993-2016 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#ifndef GCC_ABIV1_CSKY_H
#define GCC_ABIV1_CSKY_H

extern unsigned long arch_flags;

/* instruction set option mask */
#define MASK_INST_CSKYV1    (1 << 0)
#define MASK_INST_CSKYV2    (1 << 1)

/* architecture option mask  */
#define MASK_ARCH_CK510     (1 << 16)
#define MASK_ARCH_CK610     (1 << 17)
#define MASK_ARCH_CK802     (1 << 18)
#define MASK_ARCH_CK803     (1 << 19)
#define MASK_ARCH_CK810     (1 << 20)


#define COPROCESSOR_MASKS  \
    MASK_DSP | MASK_SIMD | MASK_FPUV1 | MASK_FPUV2 |  \
    MASK_SECURITY | MASK_CP | MASK_MP

#define CSKY_MASKS          \
    MASK_INST_CSKYV1 | MASK_INST_CSKYV2 |   \
    MASK_ARCH_CK510 | MASK_ARCH_CK610 | MASK_ARCH_CK802 |    \
    MASK_ARCH_CK803 | MASK_ARCH_CK810


#define TARGET_CK510    (arch_flags & MASK_ARCH_CK510)
#define TARGET_CK610    (arch_flags & MASK_ARCH_CK610)
#define TARGET_CK802    (arch_flags & MASK_ARCH_CK802)
#define TARGET_CK803    (arch_flags & MASK_ARCH_CK803)
#define TARGET_CK810    (arch_flags & MASK_ARCH_CK810)

#define TARGET_CSKYV1   (arch_flags & MASK_INST_CSKYV1)
#define TARGET_CSKYV2   (arch_flags & MASK_INST_CSKYV2)
#define TARGET_EITHER   1

extern unsigned long csky_flags;
/* Subclass of Csky instructions */
/* The MU subclass instructions that what's different
     between arch_ck802 and arch_ck803 */
#define MASK_MU             (1 << 0)

#define TARGET_MU           (csky_flags & MASK_MU)

/* Run-time Target Specification.  */
#define TARGET_SOFT_FLOAT   (csky_float_abi == CSKY_FLOAT_ABI_SOFT)
/* Use hardware floating point instructions. */
#define TARGET_HARD_FLOAT   (csky_float_abi != CSKY_FLOAT_ABI_SOFT)

/*  TARGET SEPC   */
#define MULTILIB_DEFAULTS \
  {"mlittle-endian", "mcpu=ck610", "mno-stm", "mfloat-abi=soft"}

/* Support for a compile-time default CPU, et cetera.  The rules are:
   --with-arch is ignored if -march or -mcpu are specified.
   --with-cpu is ignored if -march or -mcpu are specified, and is overridden
    by --with-arch. */
#define OPTION_DEFAULT_SPECS \
  {"arch", "%{!march=*:%{!mcpu=*:-march=%(VALUE)}}" }, \
  {"cpu", "%{!march=*:%{!mcpu=*:-mcpu=%(VALUE)}}" }, \
  {"endian", "%{!mbig-endian:%{!mlittle-endian:-m%(VALUE)-endian}}" }, \
  {"float", "%{!mfloat-abi=*:-mfloat-abi=%(VALUE)}" },

/* debugging info */
#undef  DWARF2_DEBUGGING_INFO
#define DWARF2_DEBUGGING_INFO 1
#define PREFERRED_DEBUGGING_TYPE  DWARF2_DEBUG

#define DWARF2_UNWIND_INFO 1

extern int const csky_dbg_register_map[];
#define DBX_REGISTER_NUMBER(regno)  csky_dbg_register_map[regno]
#define DWARF_FRAME_REGNUM(REG)  DBX_REGISTER_NUMBER (REG)

#define DWARF_FRAME_RETURN_COLUMN    DWARF_FRAME_REGNUM (LK_REGNUM)

/* Use a0-a1 to pass exception handling information, should define 4 regs if has enough regs.*/
#define EH_RETURN_DATA_REGNO(N)    (((N) < 2) ? (N + 2) : INVALID_REGNUM)


/* The register that holds a stack adjustment to be applied before function
   return.  This is used to unwind the stack to an exception handler's call
   frame. */
#define CSKY_EH_STACKADJ_REGNUM  4
#define EH_RETURN_STACKADJ_RTX  gen_rtx_REG (SImode, CSKY_EH_STACKADJ_REGNUM)

/******************************************************************
 *               Run-time Target Specification                    *
 ******************************************************************/
#define TARGET_CPU_CPP_BUILTINS()                   \
  do                                                \
    {                                               \
      builtin_define ("__csky__=1");                \
      builtin_define ("__CSKY__=1");                \
      builtin_define ("__ckcore__=1");              \
      builtin_define ("__CKCORE__=1");              \
                                                    \
      builtin_define ("__CSKYABIV1__");             \
      builtin_define ("__cskyabiv1__");             \
      builtin_define ("__CSKYABI__=1");             \
      builtin_define ("__cskyabi__=1");             \
                                                    \
      if (TARGET_LITTLE_ENDIAN)                     \
        {                                           \
          builtin_define ("__ckcoreLE__");          \
          builtin_define ("__cskyLE__");            \
          builtin_define ("__cskyle__");            \
          builtin_define ("__CSKYLE__");            \
        }                                           \
      else                                          \
        {                                           \
          builtin_define ("__ckcoreBE__");          \
          builtin_define ("__cskyBE__");            \
          builtin_define ("__cskybe__");            \
          builtin_define ("__CSKYBE__");            \
        }                                           \
                                                    \
      if (TARGET_CK510)                             \
        {                                           \
          builtin_define ("__ck510__");             \
          builtin_define ("__CK510__");             \
        }                                           \
      else if (TARGET_CK610)                        \
        {                                           \
          builtin_define ("__ck610__");             \
          builtin_define ("__CK610__");             \
        }                                           \
                                                    \
      if (TARGET_DSP)                               \
        {                                           \
          builtin_define ("__csky_dsp__");          \
          builtin_define ("__CSKY_DSP__");          \
        }                                           \
      if (TARGET_FPUV1)                             \
        {                                           \
          builtin_define ("__csky_fpuv1__");        \
          builtin_define ("__CSKY_FPUV1__");        \
        }                                           \
      if (TARGET_FPUV2)                             \
        {                                           \
          builtin_define ("__csky_fpuv2__");        \
          builtin_define ("__CSKY_FPUV2__");        \
        }                                           \
      if (TARGET_SECURITY)                          \
        {                                           \
          builtin_define ("__csky_security__");     \
          builtin_define ("__CSKY_SECURITY__");     \
        }                                           \
                                                    \
      if (TARGET_HARD_FLOAT)                        \
        {                                           \
          builtin_define ("__csky_hard_float__");   \
          builtin_define ("__CSKY_HARD_FLOAT__");   \
        }                                           \
      else                                          \
        {                                           \
          builtin_define ("__csky_soft_float__");   \
          builtin_define ("__CSKY_SOFT_FLOAT__");   \
        }                                           \
                                                    \
    }                                               \
  while (0)

/* implementation of TARGET_DEFAULT_TARGET_FLAGS */
#define TARGET_DEFAULT      \
    ( MASK_HARDLIT          \
    | MASK_DIV              \
    | MASK_HIGH_REGISTERS   \
    | MASK_LITTLE_ENDIAN    \
    /*| MASK_LRA*/ )

/* Target machine storage Layout.  */

/* Define this if most significant bit is lowest numbered
   in instructions that operate on numbered bit-fields.  */
#define BITS_BIG_ENDIAN  0

/* Define this if most significant byte of a word is the lowest numbered.  */
#define BYTES_BIG_ENDIAN (! TARGET_LITTLE_ENDIAN)

/* Define this if most significant word of a multiword number is the lowest
   numbered.  */
#define WORDS_BIG_ENDIAN (! TARGET_LITTLE_ENDIAN)

/* Width of a word, in units (bytes).  */
#define UNITS_PER_WORD 4

/* Set MODE to word_mode if MODE is an integer mode narrower than BITS_PER_WORD.
   UNSIGNEDP depends on the faster one of zext and sext. */
#define PROMOTE_MODE(MODE,UNSIGNEDP,TYPE)       \
  if (GET_MODE_CLASS (MODE) == MODE_INT         \
      && GET_MODE_SIZE (MODE) < UNITS_PER_WORD) \
    {                                           \
      (MODE) = SImode;                          \
    }


/* Allocation boundary (in *bits*) for storing arguments in argument list.  */
#define PARM_BOUNDARY   32

/* Boundary (in *bits*) on which stack pointer should be aligned.  */
#define STACK_BOUNDARY  64

/* Allocation boundary (in *bits*) for the code of a function.  */
#define FUNCTION_BOUNDARY   32

/* FIXME */
/* Alignment of field after `int : 0' in a structure.  */
#define EMPTY_FIELD_BOUNDARY  32

/* No data type wants to be aligned rounder than this.  */
#define BIGGEST_ALIGNMENT  64

/* The best alignment to use in cases where we have a choice.  */
#define FASTEST_ALIGNMENT 32

/* Every structures size must be a multiple of 8 bits.  */
#define STRUCTURE_SIZE_BOUNDARY 8

/* Look at the fundamental type that is used for a bit-field and use
   that to impose alignment on the enclosing structure.
   struct s {int a:8}; should have same alignment as "int", not "char".  */
#define PCC_BITFIELD_TYPE_MATTERS 1

/* Largest integer machine mode for structures.  If undefined, the default
   is GET_MODE_SIZE(DImode).  */
#define MAX_FIXED_MODE_SIZE 64

/* Make strings word-aligned so strcpy from constants will be faster.  */
#define CONSTANT_ALIGNMENT(EXP, ALIGN)  \
  ((TREE_CODE (EXP) == STRING_CST       \
    && (ALIGN) < FASTEST_ALIGNMENT)     \
   ? FASTEST_ALIGNMENT : (ALIGN))

/* Align definitions of arrays, unions and structures so that
   initializations and copies can be made more efficient.  This is not
   ABI-changing, so it only affects places where we can see the
   definition. Increasing the alignment tends to introduce padding,
   so don't do this when optimizing for size/conserving stack space. */
#define CSKY_EXPAND_ALIGNMENT(COND, EXP, ALIGN) \
  (((COND) && ((ALIGN) < BITS_PER_WORD)         \
    && (TREE_CODE (EXP) == ARRAY_TYPE           \
  || TREE_CODE (EXP) == UNION_TYPE              \
  || TREE_CODE (EXP) == RECORD_TYPE)) ? FASTEST_ALIGNMENT : (ALIGN))

/* Make arrays and unions and records word-aligned for the same reasons.  */
#define DATA_ALIGNMENT(EXP, ALIGN)        \
  CSKY_EXPAND_ALIGNMENT(1, EXP, ALIGN)

/* Similarly, make sure that objects on the stack are sensibly aligned.  */
#define LOCAL_ALIGNMENT(EXP, ALIGN)       \
  CSKY_EXPAND_ALIGNMENT(1, EXP, ALIGN)

/* Set this nonzero if move instructions will actually fail to work
   when given unaligned data.  */
#define STRICT_ALIGNMENT 1


/* Standard register usage.  */

/* Register allocation for our first guess

 r0  stack pointer
 r1  scratch, target reg for xtrb?
 r2-r7  arguments.
 r8-r14  call saved
 r15  link register
 ap  arg pointer (doesn't really exist, always eliminated)
 c               c bit
 fp  frame pointer (doesn't really exist, always eliminated)
  hi,lo mul/div auxiliary reg
  epc   exception pc back-up reg.  */

/* Number of actual hardware registers.
   The hardware registers are assigned numbers for the compiler
   from 0 to just below FIRST_PSEUDO_REGISTER.
   All registers that the compiler knows about must be given numbers,
   even those that are not normally considered general registers.  */

#define FIRST_PSEUDO_REGISTER 70

#define R1_REG  1		/* Where literals are forced.  */
#define LK_REG  15		/* Overloaded on general register.  */
#define AP_REG  32		/* Fake arg pointer register.  */
#define CC_REG  33		/* Can't name it C_REG.  */
#define FP_REG  34		/* Fake frame pointer register.  */
#define HI_REG  36		/* hi register.  */
#define LO_REG  37		/* lo register.  */
#define FPU_REG_FIRST  38	/* first fpu register.  */
#define FPU_REG_LAST   69	/* last fpu register.  */

#define FPU_REG_NUM (FPU_REG_LAST - FPU_REG_FIRST + 1)
#define FPU_REG_P(N)  \
  ((unsigned int)((int) (N) - FPU_REG_FIRST) < FPU_REG_NUM)
#define HILO_REG_P(N) (((N) == HI_REG) || ((N) == LO_REG))
#define GENERAL_REG_P(N) (((unsigned int)(N) <= AP_REG) || ((N) == FP_REG))

/* Specify the registers used for certain standard purposes.
   The values of these macros are register numbers.  */


#undef PC_REGNUM		/* Define this if the program counter is overloaded on a register.  */
#define STACK_POINTER_REGNUM 0	/* Register to use for pushing function arguments.  */
#define FRAME_POINTER_REGNUM 34	/* When we need FP, use fpvirtual.  */
#define HARD_FRAME_POINTER_REGNUM 8	/* The actual hard FP  */

/* The assembler's names for the registers.  RFP need not always be used as
   the Real framepointer; it can also be used as a normal general register.
   Note that the name `fp' is horribly misleading since `fp' is in fact only
   the argument-and-return-context pointer.  */
#define REGISTER_NAMES                                          \
{                                                               \
  "sp", "r1", "r2",  "r3",  "r4",  "r5",  "r6",  "r7",          \
  "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",         \
  "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",       \
  "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",       \
  "apvirtual",  "c", "fpvirtual", "epc",                        \
  "hi", "lo",                                                   \
  "fr0", "fr1", "fr2",  "fr3",  "fr4",  "fr5",  "fr6",  "fr7",  \
  "fr8", "fr9", "fr10", "fr11", "fr12", "fr13", "fr14", "fr15", \
  "fr16","fr17","fr18", "fr19", "fr20", "fr21", "fr22", "fr23", \
  "fr24","fr25","fr26", "fr27", "fr28", "fr29", "fr30", "fr31"  \
}

/* This macro defines additional names for hard registers. For inline asm */
#define ADDITIONAL_REGISTER_NAMES                     \
{                                                     \
    {"r0",   0},                                      \
    {"r1",   1},                                      \
    {"a0",   2},                                      \
    {"a1",   3},                                      \
    {"a2",   4},                                      \
    {"a3",   5},                                      \
    {"a4",   6},                                      \
    {"a5",   7},                                      \
    {"l0",   8},                                      \
    {"l1",   9},                                      \
    {"l2",  10},                                      \
    {"l3",  11},                                      \
    {"l4",  12},                                      \
    {"l5",  13},                                      \
    {"l10", 14}, {"gb", 14},                          \
    {"lr",  15},                                      \
    {"l6",  16},                                      \
    {"l7",  17},                                      \
    {"l8",  18},                                      \
    {"l9",  19},                                      \
    {"t0",  20},                                      \
    {"t1",  21},                                      \
    {"t2",  22},                                      \
    {"t3",  23},                                      \
    {"t4",  24},                                      \
    {"t5",  25},                                      \
    {"r26", 26},                                      \
    {"r27", 27},                                      \
    {"r28", 28},                                      \
    {"r29", 29},                                      \
    {"r30", 30},                                      \
    {"tls", 31}                                       \
}


/* 1 for registers that have pervasive standard uses
   and are not available for the register allocator.  */
#define FIXED_REGISTERS                                                 \
 /*  sp   r1   r2   r3   r4   r5   r6   r7  */                          \
   { 1,   1,   0,   0,   0,   0,   0,   0,                              \
 /*  r8   r9   r10  r11  r12  r13  r14  r15 */                          \
     0,   0,   0,   0,   0,   0,   0,   0,                              \
 /*  r16  r17  r18  r19  r20  r21  r22  r23 */                          \
     0,   0,   0,   0,   0,   0,   0,   0,                              \
 /*  r24  r25  r26  r27  r28  r29  r30  tls */                          \
     0,   0,   1,   1,   1,   1,   1,   1,                              \
 /*  vap  c    vfp  epc  hi   lo */                                     \
     1,   1,   1,   1,                                                  \
 /*  hi,  lo */                                                         \
     0,   0,                                                            \
 /* fr0   fr1   fr2   fr3   fr4   fr5   fr6   fr7 */                    \
     0,    0,    0,    0,    0,    0,    0,    0,                       \
 /* fr8   fr9   fr10  fr11  fr12  fr13  fr14  fr15 */                   \
     0,    0,    0,    0,    0,    0,    0,    0,                       \
 /* fr16  fr17  fr18  fr19  fr20  fr21  fr22  fr23 */                   \
     0,    0,    0,    0,    0,    0,    0,    0,                       \
 /* fr24  fr25  fr26  fr27  fr28  fr29  fr30  fr31 */                   \
     0,    0,    0,    0,    0,    0,    0,    0                        \
   }

/* 1 for registers not available across function calls.
   These must include the FIXED_REGISTERS and also any
   registers that can be used without being saved.
   The latter must include the registers where values are returned
   and the register where structure-value addresses are passed.
   Aside from that, you can include as many other registers as you like.  */

/* RBE: r15 {link register} not available across calls,
   But we don't mark it that way here....  */
#define CALL_USED_REGISTERS                                             \
 /*  sp   r1   r2   r3   r4   r5   r6   r7  */                          \
   { 1,   1,   1,   1,   1,   1,   1,   1,                              \
 /*  r8   r9   r10  r11  r12  r13  r14  r15 */                          \
     0,   0,   0,   0,   0,   0,   0,   0,                              \
 /*  r16  r17  r18  r19  r20  r21  r22  r23 */                          \
     0,   0,   0,   0,   1,   1,   1,   1,                              \
 /*  r24  r25  r26  r27  r28  r29  r30  r31 */                          \
     1,   1,   1,   1,   1,   1,   1,   1,                              \
 /*  vap  c    vfp  epc  hi   lo */                                     \
     1,   1,   1,   1,   1,   1,                                        \
 /* fr0   fr1   fr2   fr3   fr4   fr5   fr6   fr7 */                    \
     1,    1,    1,    1,    1,    1,    1,    1,                       \
 /* fr8   fr9   fr10  fr11  fr12  fr13  fr14  fr15 */                   \
     1,    1,    1,    1,    1,    1,    1,    1,                       \
 /* fr16  fr17  fr18  fr19  fr20  fr21  fr22  fr23 */                   \
     1,    1,    1,    1,    1,    1,    1,    1,                       \
 /* fr24  fr25  fr26  fr27  fr28  fr29  fr30  fr31 */                   \
     1,    1,    1,    1,    1,    1,    1,    1                        \
   }

/* Like `CALL_USED_REGISTERS' but used to overcome a historical
   problem which makes CALL_USED_REGISTERS *always* include
   all the FIXED_REGISTERS.  Until this problem has been
   resolved this macro can be used to overcome this situation.
   In particular, block_propagate() requires this list
   be accurate, or we can remove registers which should be live.
   This macro is used in get_csky_live_regs().  */
#define CALL_REALLY_USED_REGISTERS                                      \
 /*  sp   r1   r2   r3   r4   r5   r6   r7  */                          \
   { 1,   1,   1,   1,   1,   1,   1,   1,                              \
 /*  r8   r9   r10  r11  r12  r13  r14  r15 */                          \
     0,   0,   0,   0,   0,   0,   0,   0,                              \
 /*  r16  r17  r18  r19  r20  r21  r22  r23 */                          \
     0,   0,   0,   0,   1,   1,   1,   1,                              \
 /*  r24  r25  r26  r27  r28  r29  r30  r31 */                          \
     1,   1,   1,   1,   1,   1,   1,   1,                              \
 /*  vap  c    vfp  epc  hi   lo */                                     \
     1,   1,   1,   1,   1,   1,                                        \
 /* fr0   fr1   fr2   fr3   fr4   fr5   fr6   fr7 */                    \
     1,    1,    1,    1,    1,    1,    1,    1,                       \
 /* fr8   fr9   fr10  fr11  fr12  fr13  fr14  fr15 */                   \
     1,    1,    1,    1,    1,    1,    1,    1,                       \
 /* fr16  fr17  fr18  fr19  fr20  fr21  fr22  fr23 */                   \
     1,    1,    1,    1,    1,    1,    1,    1,                       \
 /* fr24  fr25  fr26  fr27  fr28  fr29  fr30  fr31 */                   \
     1,    1,    1,    1,    1,    1,    1,    1                        \
   }

/* The order in which register should be allocated.  */
#define REG_ALLOC_ORDER  \
/*   r7    r6    r5    r4    r3    r2   r15   r14     */        \
  {   7,    6,    5,    4,    3,    2,   15,   14,              \
/*  r13   r12   r11   r10    r9    r8   r25   r24     */        \
     13,   12,   11,   10,    9,    8,   25,   24,              \
/*  r23   r22   r21   r20   r19   r18   r17   r16     */        \
     23,   22,   21,   20,   19,   18,   17,   16,              \
/*  r26   r27   r28   r29   r30    hi    lo    r1     */        \
     26,   27,   28,   29,   30,   36,   37,    1,              \
/*  fr0   fr1   fr2   fr3   fr4   fr5   fr6   fr7 */            \
     38,   39,   40,   41,   42,   43,   44,   45,              \
/*  fr8   fr9   fr10  fr11  fr12  fr13  fr14  fr15 */           \
     46,   47,   48,   49,   50,   51,   52,   53,              \
/*  fr16  fr17  fr18  fr19  fr20  fr21  fr22  fr23 */           \
     54,   55,   56,   57,   58,   59,   60,   61,              \
/*  fr24, fr25, fr26, fr27, fr28, fr29, fr30, fr31 */           \
     62,   63,   64,   65,   66,   67,   68,   69,              \
/*   sp   tls   vfp    c     vap  epc  */                       \
     0,    31,   34,   33,   32,   35   }

/* Return number of consecutive hard regs needed starting at reg REGNO
   to hold something of mode MODE.
   This is ordinarily the length in words of a value of mode MODE
   but can be less for certain modes in special long registers.

   On the CSKY regs are UNITS_PER_WORD bits wide; */
#define HARD_REGNO_NREGS(REGNO, MODE)  \
   (((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD))

/* Value is 1 if hard register REGNO can hold a value of machine-mode MODE.
   We may keep double values in even registers.  */
#define HARD_REGNO_MODE_OK(REGNO, MODE)  \
  ((GET_MODE_SIZE (MODE) > UNITS_PER_WORD) ? ((REGNO) & 1) == 0 : 1)

/* Value is 1 if it is a good idea to tie two pseudo registers
   when one has mode MODE1 and one has mode MODE2.
   If HARD_REGNO_MODE_OK could produce different values for MODE1 and MODE2,
   for any hard reg, then this must be 0 for correct output.  */
#define MODES_TIEABLE_P(MODE1, MODE2) \
  ((MODE1) == (MODE2) || GET_MODE_CLASS (MODE1) == GET_MODE_CLASS (MODE2))

/* Definitions for register eliminations.

   We have two registers that can be eliminated on the CSKY.  First, the
   frame pointer register can often be eliminated in favor of the stack
   pointer register.  Secondly, the argument pointer register can always be
   eliminated; it is replaced with either the stack or frame pointer.  */

/* Base register for access to arguments of the function.  */
#define ARG_POINTER_REGNUM 32

/* Macro called for initialize any target specific information.
   The alignment of vap is initialized here. */
#define INIT_EXPANDERS                                              \
  do                                                                \
    {                                                               \
      if (crtl->emit.regno_pointer_align)                           \
        {                                                           \
          REGNO_POINTER_ALIGN (ARG_POINTER_REGNUM) = BITS_PER_WORD; \
        }                                                           \
    } while (0);

/* Register in which the static-chain is passed to a function.  */
#define STATIC_CHAIN_REGNUM 1

/* This is an array of structures.  Each structure initializes one pair
   of eliminable registers.  The "from" register number is given first,
   followed by "to".  Eliminations of the same "from" register are listed
   in order of preference.  */
#define ELIMINABLE_REGS    \
{{ ARG_POINTER_REGNUM,   STACK_POINTER_REGNUM      }, \
 { ARG_POINTER_REGNUM,   FRAME_POINTER_REGNUM      }, \
 { ARG_POINTER_REGNUM,   HARD_FRAME_POINTER_REGNUM }, \
 { FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM      }, \
 { FRAME_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM }}

/* Define the offset between two registers, one to be eliminated, and the other
   its replacement, at the start of a routine.  */
#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET) \
  OFFSET = csky_initial_elimination_offset (FROM, TO)

/* Define the classes of registers for register constraints in the
   machine description.  Also define ranges of constants.

   One of the classes must always be named ALL_REGS and include all hard regs.
   If there is more than one class, another class must be named NO_REGS
   and contain no registers.

   The name GENERAL_REGS must be the name of a class (or an alias for
   another name such as ALL_REGS).  This is the class of registers
   that is allowed by "g" or "r" in a register constraint.
   Also, registers outside this class are allocated only when
   instructions express preferences for them.

   The classes must be numbered in nondecreasing order; that is,
   a larger-numbered class must never be contained completely
   in a smaller-numbered class.

   For any two classes, it is very desirable that there be another
   class that represents their union.  */

enum reg_class
{
  NO_REGS,
  RWCPCR_REGS,
  LRW_REGS,
  GENERAL_REGS,
  C_REGS,
  HI_REGS,
  LO_REGS,
  HILO_REGS,
  FPU_REGS,
  OTHER_REGS,
  ALL_REGS,
  LIM_REG_CLASSES
};

#define N_REG_CLASSES  (int) LIM_REG_CLASSES


/* Give names of register classes as strings for dump file.  */
#define REG_CLASS_NAMES     \
{                           \
  "NO_REGS",                \
  "RWCPCR_REGS",            \
  "LRW_REGS",               \
  "GENERAL_REGS",           \
  "C_REGS",                 \
  "HI_REGS",                \
  "LO_REGS",                \
  "HILO_REGS",              \
  "FPU_REGS",               \
  "OTHER_REGS",             \
  "ALL_REGS",               \
}


/* Define which registers fit in which classes.
   This is an initializer for a vector of HARD_REG_SET
   of length N_REG_CLASSES.  */
#define REG_CLASS_CONTENTS                                        \
{                                                                 \
  {0x00000000, 0x00000000, 0x00000000 },  /* NO_REGS           */ \
  {0x000000FF, 0x00000000, 0x00000000 },  /* RWCPCR_REGS       */ \
  {0x00007FFE, 0x00000000, 0x00000000 },  /* LRW_REGS          */ \
  {0xFFFFFFFF, 0x00000005, 0x00000000 },  /* GENERAL_REGS      */ \
  {0x00000000, 0x00000002, 0x00000000 },  /* C_REGS            */ \
  {0x00000000, 0x00000010, 0x00000000 },  /* HI_REG            */ \
  {0x00000000, 0x00000020, 0x00000000 },  /* LO_REG            */ \
  {0x00000000, 0x00000030, 0x00000000 },  /* HILO_REGS         */ \
  {0x00000000, 0xFFFFFFC0, 0x0000003F },  /* FPU_REGS          */ \
  {0x00000000, 0x00000008, 0x00000000 },  /* OTHER_REGS        */ \
  {0xFFFFFFFF, 0xFFFFFFFF, 0x0000003F },  /* ALL_REGS          */ \
}


/* The same information, inverted:
   Return the class number of the smallest class containing
   reg number REGNO.  This could be a conditional expression
   or could index an array.  */

extern const enum reg_class regno_reg_class[FIRST_PSEUDO_REGISTER];
#define REGNO_REG_CLASS(REGNO) ((REGNO) < FIRST_PSEUDO_REGISTER ? regno_reg_class[REGNO] : NO_REGS)

/* When this hook returns true for MODE, the compiler allows
   registers explicitly used in the rtl to be used as spill registers
   but prevents the compiler from extending the lifetime of these
   registers.  */
#define TARGET_SMALL_REGISTER_CLASSES_FOR_MODE_P hook_bool_mode_true

/* The class value for index registers, and the one for base regs.  */
#define INDEX_REG_CLASS  NO_REGS
#define BASE_REG_CLASS  GENERAL_REGS

/* Convenience wrappers around insn_const_int_ok_for_constraint.  */
#define CONST_OK_FOR_I(VALUE) \
  IN_RANGE (VALUE, 0, 127)
#define CONST_OK_FOR_J(VALUE) \
  IN_RANGE (VALUE, 1, 32)
#define CONST_OK_FOR_K(VALUE) \
  IN_RANGE (VALUE, 0, 31)
#define CONST_OK_FOR_L(VALUE) \
  IN_RANGE (VALUE, -32, -1)
#define CONST_OK_FOR_M(VALUE) \
  (exact_log2 (VALUE) >= 0 && exact_log2 (VALUE) <= 31)
#define CONST_OK_FOR_N(VALUE)             \
  ((VALUE) == (HOST_WIDE_INT)-1           \
   || (exact_log2 ((VALUE) + 1) >= 0      \
        && exact_log2 ((VALUE) + 1) <= 31))
#define CONST_OK_FOR_O(VALUE) \
  IN_RANGE (VALUE, -31, 0)
#define CONST_OK_FOR_S(VALUE) \
  csky_num_zeros(VALUE) <= 2
#define CONST_OK_FOR_T(VALUE) \
  csky_num_ones(VALUE) <= 2


/* Return the maximum number of consecutive registers
   needed to represent mode MODE in a register of class CLASS.

   On CSKY this is the size of MODE in words.  */
#define CLASS_MAX_NREGS(CLASS, MODE)  \
     (ROUND_ADVANCE (GET_MODE_SIZE (MODE)))

/* Stack layout; function entry, exit and calling.  */

/* Define the number of register that can hold parameters.
   These two macros are used only in other macro definitions below.  */
#define NPARM_REGS 6
#define FIRST_PARM_REG 2
#define FIRST_RET_REG 2

/* Define this if pushing a word on the stack
   makes the stack pointer a smaller address.  */
#define STACK_GROWS_DOWNWARD 1

/* Define this to nonzero if the address of local variable slots
   are negative offsets frome the frame pointer. */
#define FRAME_GROWS_DOWNWARD 0

/* Offset within stack frame to start allocating local variables at.
   If FRAME_GROWS_DOWNWARD, this is the offset to the END of the
   first local allocated.  Otherwise, it is the offset to the BEGINNING
   of the first local allocated.  */
#define STARTING_FRAME_OFFSET  0

/* If defined, the maximum amount of space required for outgoing arguments
   will be computed and placed into the variable
   `crtl->outgoing_args_size'.  No space will be pushed
   onto the stack for each call; instead, the function prologue should
   increase the stack frame size by this amount.  */
#define ACCUMULATE_OUTGOING_ARGS 1

/* Offset of first parameter from the argument pointer register value.  */
#define FIRST_PARM_OFFSET(FNDECL)  0

/* Don't default to pcc-struct-return, because gcc is the only compiler, and
   we want to retain compatibility with older gcc versions.  */
#define DEFAULT_PCC_STRUCT_RETURN 0

/* Define how to find the value returned by a library function
   assuming the value has mode MODE.  */
#define LIBCALL_VALUE(MODE)  gen_rtx_REG (MODE, FIRST_RET_REG)

/* 1 if N is a possible register number for function argument passing.  */
#define FUNCTION_ARG_REGNO_P(REGNO)  \
  ((REGNO) >= FIRST_PARM_REG && (REGNO) < (NPARM_REGS + FIRST_PARM_REG))

/* Define a data type for recording info about an argument list
   during the scan of that argument list.  This data type should
   hold all necessary information about the function itself
   and about the args processed so far, enough to enable macros
   such as FUNCTION_ARG to determine where the next arg should go.

   On CSKY, this is a single integer, which is a number of words
   of arguments scanned so far (including the invisible argument,
   if any, which holds the structure-value-address).
   Thus NARGREGS or more means all following args should go on the stack.  */
#define CUMULATIVE_ARGS  int

#define ROUND_ADVANCE(SIZE) \
  ((SIZE + UNITS_PER_WORD - 1) / UNITS_PER_WORD)

/* Round a register number up to a proper boundary for an arg of mode
   MODE.

   We round to an even reg for things larger than a word.  */
#define ROUND_REG(X, MODE)     \
  ((GET_MODE_UNIT_SIZE ((MODE)) > UNITS_PER_WORD)  \
   ? ((X) + ((X) & 1)) : (X))


/* Initialize a variable CUM of type CUMULATIVE_ARGS
   for a call to a function whose data type is FNTYPE.
   For a library call, FNTYPE is 0.

   On CSKY, the offset always starts at 0: the first parm reg is always
   the same reg.  */
#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, INDIRECT, N_NAMED_ARGS) \
  ((CUM) = 0)

/* Call the function profiler with a given profile label.  */
/* FIXME */
#define FUNCTION_PROFILER(STREAM,LABELNO)                       \
{                                                               \
  fprintf (STREAM, " // ELF TOOL PROFILE NOT IMPLEMENT ...\n"); \
}

/* EXIT_IGNORE_STACK should be nonzero if, when returning from a function,
   the stack pointer does not matter.  The value is tested only in
   functions that have frame pointers.
   No definition is equivalent to always zero.

   On the CSKY, the function epilogue recovers the stack pointer from the
   frame.  */
#define EXIT_IGNORE_STACK 1

/* Length in units of the trampoline for entering a nested function.  */
#define TRAMPOLINE_SIZE  12

/* Alignment required for a trampoline in bits.  */
#define TRAMPOLINE_ALIGNMENT  32

/* Macros to check register numbers against specific register classes.  */

/* These assume that REGNO is a hard or pseudo reg number.
   They give nonzero only if REGNO is a hard reg of the suitable class
   or a pseudo reg currently allocated to a suitable hard reg.
   Since they use reg_renumber, they are safe only once reg_renumber
   has been allocated, which happens in reginfo.c during register
   allocation.  */
#define REGNO_OK_FOR_BASE_P(REGNO)                \
  (GENERAL_REG_P(REGNO) || GENERAL_REG_P((unsigned) reg_renumber[(REGNO)]))

#define REGNO_OK_FOR_INDEX_P(REGNO)   0

/* Maximum number of registers that can appear in a valid memory
   address.  */
#define MAX_REGS_PER_ADDRESS 1

/* Recognize any constant value that is a valid address.  */
#define CONSTANT_ADDRESS_P(X)   (GET_CODE (X) == LABEL_REF)

/* Specify the machine mode that this machine uses
   for the index in the tablejump instruction.  */
#define CASE_VECTOR_MODE SImode

/* 'char' is unsigned by default for backward compatiblity.  */
#define DEFAULT_SIGNED_CHAR  0

#undef SIZE_TYPE
#define SIZE_TYPE "unsigned int"

#undef PTRDIFF_TYPE
#define PTRDIFF_TYPE "int"

#undef WCHAR_TYPE
#define WCHAR_TYPE "long int"

#undef UINT_LEAST32_TYPE
#define UINT_LEAST32_TYPE "unsigned int"

#undef WCHAR_TYPE_SIZE
#define WCHAR_TYPE_SIZE BITS_PER_WORD

/* Max number of bytes we can move from memory to memory
   in one reasonably fast instruction.  */
#define MOVE_MAX 4

/* Define if operations between registers always perform the operation
   on the full register even if a narrower mode is specified.  */
#define WORD_REGISTER_OPERATIONS 1

/* Define if loading in MODE, an integral mode narrower than BITS_PER_WORD
   will either zero-extend or sign-extend.  The value of this macro should
   be the code that says which one of the two operations is implicitly
   done, UNKNOWN if none.  */
#define LOAD_EXTEND_OP(MODE) ZERO_EXTEND

/* Nonzero if access to memory by bytes is slow and undesirable.  */
#define SLOW_BYTE_ACCESS 0

/* Shift counts are truncated to 6-bits (0 to 63) instead of the expected
   5-bits, so we can not define SHIFT_COUNT_TRUNCATED to true for this
   target.  */
#define SHIFT_COUNT_TRUNCATED 0

/* All integers have the same format so truncation is easy.  */
#define TRULY_NOOP_TRUNCATION(OUTPREC,INPREC)  1

/* Define this if addresses of constant functions
   shouldn't be put through pseudo regs where they can be cse'd.
   Desirable on machines where ordinary constants are expensive
   but a CALL with constant address is cheap.  */
/* Calling from registers is a massive pain. */
#define NO_FUNCTION_CSE 1

/* Try to generate sequences that don't involve branches, we can then use
   conditional instructions.  */
#define BRANCH_COST(speed_p, predictable_p) \
  (global_options_set.x_csky_branch_cost ? csky_branch_cost \
   : csky_default_branch_cost (speed_p, predictable_p))

/* False if short circuit operation is preferred.  */
#define LOGICAL_OP_NON_SHORT_CIRCUIT \
  (csky_default_logical_op_non_short_circuit ())

/* The machine modes of pointers and functions.  */
#define Pmode          SImode
#define FUNCTION_MODE  Pmode

/* Define if operations between registers always perform the operation
   on the full register even if a narrower mode is specified.  */
#define WORD_REGISTER_OPERATIONS 1

/* Assembler output control.  */
#define ASM_COMMENT_START "\t//"

#define ASM_APP_ON "// inline asm begin\n"
#define ASM_APP_OFF "// inline asm end\n"

#define FILE_ASM_OP     "\t.file\n"

/* Switch to the text or data segment.  */
#define TEXT_SECTION_ASM_OP  "\t.text"
#define DATA_SECTION_ASM_OP  "\t.data"

/* The subroutine calls in the .init and .fini sections create literal
   pools which must be jumped around...  */
#define FORCE_CODE_SECTION_ALIGN  asm ("br 1f ; .literals ; .align 2 ; 1:");

#define RETURN_ADDR_RTX(COUNT, FRAME)  csky_return_addr (COUNT, FRAME)
#define INCOMING_RETURN_ADDR_RTX gen_rtx_REG (Pmode, LK_REG)

/* This is how to output an insn to push a register on the stack.
   It need not be very fast code.  */
#define ASM_OUTPUT_REG_PUSH(FILE,REGNO)               \
  fprintf (FILE, "\tsubi\t %s,%d\n\tstw\t %s,(%s)\n", \
    reg_names[STACK_POINTER_REGNUM],                  \
    (STACK_BOUNDARY / BITS_PER_UNIT),                 \
    reg_names[REGNO],                                 \
    reg_names[STACK_POINTER_REGNUM])

/* This is how to output an insn to pop a register from the stack.  */
#define ASM_OUTPUT_REG_POP(FILE,REGNO)                \
  fprintf (FILE, "\tldw\t %s,(%s)\n\taddi\t %s,%d\n", \
    reg_names[REGNO],                                 \
    reg_names[STACK_POINTER_REGNUM],                  \
    reg_names[STACK_POINTER_REGNUM],                  \
    (STACK_BOUNDARY / BITS_PER_UNIT))


/* Output a reference to a label.  */
#undef  ASM_OUTPUT_LABELREF
#define ASM_OUTPUT_LABELREF(STREAM, NAME)     \
  fprintf (STREAM, "%s%s", user_label_prefix, \
    (* targetm.strip_name_encoding) (NAME))

/* This is how to output an assembler line
   that says to advance the location counter
   to a multiple of 2**LOG bytes.  */
#define ASM_OUTPUT_ALIGN(FILE,LOG)            \
  if ((LOG) != 0)                             \
    fprintf (FILE, "\t.align\t%d\n", LOG)

/* Globalizing directive for a label.  */
#define GLOBAL_ASM_OP "\t.global\t"

/* Make an internal label into a string.  */
#undef  ASM_GENERATE_INTERNAL_LABEL
#define ASM_GENERATE_INTERNAL_LABEL(STRING, PREFIX, NUM)  \
  sprintf (STRING, "*.%s%ld", PREFIX, (long) NUM)

/* Jump tables must be 32 bit aligned.  */
#undef  ASM_OUTPUT_CASE_LABEL
#define ASM_OUTPUT_CASE_LABEL(STREAM,PREFIX,NUM,TABLE) \
  fprintf (STREAM, "\t.align 2\n.%s%d:\n", PREFIX, NUM);

/* Output an element of a dispatch table.  */
#define ASM_OUTPUT_ADDR_VEC_ELT(STREAM,VALUE)  \
    fprintf (STREAM, "\t.long\t.L%d\n", VALUE)

/* Output various types of constants.  */

/* This is how to output an assembler line
   that says to advance the location counter by SIZE bytes.  */
#undef  ASM_OUTPUT_SKIP
#define ASM_OUTPUT_SKIP(FILE,SIZE)  \
  fprintf (FILE, "\t.fill %d, 1\n", (int)(SIZE))

/* This says how to output an assembler line
   to define a global common symbol, with alignment information.  */
/* XXX - for now we ignore the alignment.  */
#undef  ASM_OUTPUT_ALIGNED_COMMON
#define ASM_OUTPUT_ALIGNED_COMMON(FILE, NAME, SIZE, ALIGN)  \
    do                                                      \
    {                                                       \
        fputs ("\t.comm\t", FILE);                          \
        assemble_name (FILE, NAME);                         \
        fprintf (FILE, ",%lu, %u\n",                        \
                 (unsigned long)(SIZE),                     \
                 (ALIGN) / BITS_PER_UNIT);                  \
    }                                                       \
    while (0)

/* ... and how to define a local common symbol whose alignment
   we wish to specify.  ALIGN comes in as bits, we have to turn
   it into bytes.  */
#undef  ASM_OUTPUT_ALIGNED_LOCAL
#define ASM_OUTPUT_ALIGNED_LOCAL(FILE, NAME, SIZE, ALIGN)   \
  do                                                        \
    {                                                       \
      fputs ("\t.bss\t", (FILE));                           \
      assemble_name ((FILE), (NAME));                       \
      fprintf ((FILE), ",%d, %d\n",                         \
               (int)(SIZE),                                 \
               (ALIGN) / BITS_PER_UNIT);                    \
    }                                                       \
  while (0)

/* Position Independent Code. */
#define PIC_OFFSET_TABLE_REGNUM 14

#define LEGITIMATE_PIC_OPERAND_P(X)   \
  (!(symbol_mentioned_p (X) || label_mentioned_p (X)) || tls_mentioned_p (X))

#if defined(__MINGW32__)
/* Add for mingw32 toolchain build to avoid mingw changing
   it.  */
#undef NATIVE_SYSTEM_HEADER_DIR
#define NATIVE_SYSTEM_HEADER_DIR "/usr/include"
#endif

#define FUNCTION_ARG_PADDING(MODE, TYPE) \
  (csky_pad_arg_upward (MODE, TYPE) ? upward : downward)

#define BLOCK_REG_PADDING(MODE, TYPE, FIRST) \
  (csky_pad_reg_upward (MODE, TYPE, FIRST) ? upward : downward)

#define PAD_VARARGS_DOWN (BYTES_BIG_ENDIAN && INTEGRAL_TYPE_P (type))

#endif /* ! GCC_ABIV1_CSKY_H */
