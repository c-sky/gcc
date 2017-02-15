
#ifndef GCC_CSKY_PROTOS_H
#define GCC_CSKY_PROTOS_H


#define CSKY_STACK_BOUNDARY_BYTES (STACK_BOUNDARY/BITS_PER_UNIT)

#define CSKY_NPARM_REGS               4
#define CSKY_FIRST_PARM_REG           0
#define CSKY_NGPR_REGS                32
#define CSKY_FIRST_RET_REG            0
#define CSKY_FIRST_VFP_REGNUM         52
#define CSKY_LAST_VFP_REGNUM          67
#define CSKY_FIRST_HIGH_REGNUM        16
#define CSKY_LAST_HIGH_REGNUM         (CSKY_NGPR_REGS - 1)
#define CSKY_FIRST_MINI_REGNUM        0
#define CSKY_LAST_MINI_REGNUM         7
#define CSKY_CC_REGNUM                33
#define CSKY_HI_REGNUM                34
#define CSKY_LO_REGNUM                35
#define CSKY_LR_REGNUM                15
#define CSKY_LAST_HIGH_UNFIXED_REGNUM 25
#define CSKY_GB_REGNUM                28

#define CSKY_LD16_MAX_OFFSET(MODE)    (31 * GET_MODE_SIZE(MODE))
#define CSKY_LD32_MAX_OFFSET(MODE)    (4095 * GET_MODE_SIZE(MODE))
#define CSKY_LD16_OFFSET_MASK(MODE)   (CSKY_LD16_MAX_OFFSET (MODE) \
                                       + GET_MODE_SIZE (MODE) - 1)
#define CSKY_ADDI_MAX_IMM             256
#define CSKY_SUBI_MAX_IMM             256

#define CSKY_NUM_WORDS(SIZE) ((SIZE + UNITS_PER_WORD - 1) / UNITS_PER_WORD)

#define CSKY_GENERAL_REGNO_P(N) \
  (((N) < CSKY_NGPR_REGS && (N) >= 0))

#define CSKY_VREG_P(N)    \
  ((unsigned int)((int) (N) - CSKY_FIRST_VFP_REGNUM) < CSKY_FIRST_VFP_REGNUM)

#define CSKY_HILO_REG_P(N)   \
  ((N == CSKY_HI_REGNUM) || (N == CSKY_LO_REGNUM))

#define CSKY_NUM_REGS(MODE) \
  CSKY_NUM_WORDS(GET_MODE_SIZE (MODE))

#define CSKY_CONSTPOOL_LABEL_PREFIX   "LCP"

/* Helper macro for constraints and predicates.  */
#define VALUE_BETWEEN(VALUE, LOW, HIGH)    \
  ((VALUE) >= (LOW) && (VALUE) <= (HIGH))

#define CSKY_CONST_OK_FOR_I(VALUE)  \
  (VALUE_BETWEEN((VALUE), 0, 65535))

#define CSKY_CONST_OK_FOR_K(VALUE)  \
  (VALUE_BETWEEN(VALUE, 0, 31))

#define CSKY_CONST_OK_FOR_Ub(VALUE)  \
  (exact_log2 (VALUE & 0xFFFFFFFF) >= 0)

#define CSKY_CONST_OK_FOR_Uc(VALUE)          \
  ((VALUE) == (HOST_WIDE_INT)-1              \
   || (exact_log2 ((VALUE) + 1) >= 0         \
       && exact_log2 ((VALUE) + 1) <= 31))

#define CSKY_CONST_OK_FOR_MOVIH(VALUE)  \
  ( ((VALUE) & 0xFFFF) == 0 )

#define CSKY_CONST_OK_FOR_T(VALUE)  \
  (VALUE_BETWEEN(VALUE, -256, -1))

#define CSKY_CONST_OK_FOR_US(VALUE) \
  (VALUE_BETWEEN(VALUE, -8, -1))

#define CSKY_CONST_OK_FOR_N(VALUE)  \
  (VALUE_BETWEEN(VALUE, 1, 256))

#define CSKY_CONST_OK_FOR_L(VALUE)  \
  (VALUE_BETWEEN((VALUE), 1, 8))

#define CSKY_CONST_OK_FOR_M(VALUE)  \
  (VALUE_BETWEEN((VALUE), 1, 4096))

#define CSKY_CONST_OK_FOR_P(VALUE)  \
  ((((VALUE) & 0x3) == 0)           \
   && VALUE_BETWEEN(VALUE, 4, 508))

#define CSKY_CONST_OK_FOR_Ug(VALUE)  \
  ((((VALUE) & 0x3) == 0)            \
   && VALUE_BETWEEN(VALUE, -508, -4))

#define CSKY_CONST_OK_FOR_Uj(VALUE)  \
  ((((VALUE) & 0x3) == 0)            \
   && VALUE_BETWEEN(VALUE, 1, 1024))

#define CSKY_CONST_OK_FOR_Um(VALUE)  \
  (VALUE_BETWEEN((VALUE), -4096, -1))

/* Constant can gen by bseti(16,30) + subi.  */
#define CSKY_CONST_OK_FOR_BS(VALUE)                                               \
  (exact_log2 ((unsigned HOST_WIDE_INT)(VALUE & 0xFFFFF000) + (1 << 12)) >= 1     \
   && exact_log2 ((unsigned HOST_WIDE_INT)(VALUE & 0xFFFFF000) + (1 << 12)) <= 30 \
   && ((VALUE) & 0xFFF) != 0)

/* Structure used to hold the function stack frame layout.  */
typedef struct GTY(()) csky_stack_frame
{
  int arg_size;       /* stdarg spills (bytes) */
  int reg_size;       /* non-volatile reg saves (bytes) */
  int reg_mask;       /* non-volatile reg saves */
  int local_size;     /* locals */
  int outbound_size;  /* arg overflow on calls out */

  int pad_outbound;
  int pad_local;
  int pad_reg;
  int pad_arg;
}
csky_stack_frame;

/* FIXME the csky_frame should be transforming to csky_stack_frame.  */
struct csky_frame
{
    int arg_size;			/* stdarg spills (bytes) */
    int reg_size;			/* non-volatile reg saves (bytes) */
    int reg_mask;			/* non-volatile reg saves */
    int local_size;		/* locals */
    int outbound_size;		/* arg overflow on calls out */
    int pad_outbound;
    int pad_local;
    int pad_reg;
    int pad_arg;
  /* Describe the steps we'll use to grow it.  */
#define	MAX_STACK_GROWS	4	/* gives us some spare space */
    int growth[MAX_STACK_GROWS];
    int arg_offset;
    int reg_offset;
    int reg_growth;
    int local_growth;
};

/* Define these macros to describe the function type.  */
#define CSKY_FT_TYPE_MASK   ((1 << 3) - 1)
#define CSKY_FT_UNKNOWN     0               /* Type not been determined */
#define CSKY_FT_NORMAL      1               /* Normal function */
#define CSKY_FT_ISR         4               /* Interrupt service routine */
#define CSKY_FT_FIQ         5               /* Fast interrupt service routine */
#define CSKY_FT_EXCEPTION   6               /* Exception handler */
#define CSKY_FT_INTERRUPT   (1 << 2)        /*overlap CSKY_FT_ISR */
#define CSKY_FT_NAKED       (1 << 3)        /*No prologue and epilogue */
#define CSKY_FUNCTION_TYPE(t)   (t & CSKY_FT_TYPE_MASK)

struct csky_address
{
  rtx base, index, symbol, label, disp;
  HOST_WIDE_INT scale;
};

/* A type to distinguish the different forms of outputing
   inline const.  */

enum csky_inline_const_type
{
  IC_UNINLINALE = 0,  /* Not inibale */
  IC_SINGLE,          /* Single instruction */
  IC_APPEND_NOT,      /* Signle instruction followed by a not */
  IC_APPEND_ADDI,     /* Single insn followed by an addi */
  IC_APPEND_SUBI,     /* Single insn followed by a subi */
  IC_BGENI_ADDI,      /* Single insn(bgeni) followed by an addi */
  IC_BGENI_SUBI,      /* Single insn(bgeni) followed by a subi */
  IC_APPEND_BSETI,    /* Single insn followed by bseti */
  IC_APPEND_MOVI,     /* Single insn followed by movi */
  IC_APPEND_BCLRI,    /* Single insn followed by bclri */
  IC_APPEND_ROTLI,    /* Single insn followed by rotli */
  IC_APPEND_LSLI,     /* Single insn followed by lsli */
  IC_APPEND_IXH,      /* Single insn followed by ixh */
  IC_APPEND_IXW       /* Single insn followed by ixw */
};

/* Declare for mds */
extern int constant_csky_inlinable (HOST_WIDE_INT value);
extern bool shiftable_csky_imm8_const (unsigned HOST_WIDE_INT val);
extern const char *output_csky_move (rtx insn ATTRIBUTE_UNUSED, rtx operands[],
                                     enum machine_mode mode ATTRIBUTE_UNUSED);
extern const char *output_csky_movedouble (rtx operands[],
                                           enum machine_mode mode ATTRIBUTE_UNUSED);
extern const char *output_ck801_move (rtx insn ATTRIBUTE_UNUSED, rtx operands[],
                                      enum machine_mode mode ATTRIBUTE_UNUSED);
extern int symbolic_csky_address_p (rtx);

extern int csky_hard_regno_mode_ok (unsigned int regno, enum machine_mode mode);
extern rtx csky_return_addr (int count, rtx frame ATTRIBUTE_UNUSED);
extern void csky_init_expanders (void);
extern HOST_WIDE_INT csky_initial_elimination_offset (int, int);

/* The following are used in the .md file as equivalents to bits.  */
#include "abiv2_csky_isa.h"
extern int csky_arch_isa_features[];
#define CSKY_ISA_FEATURE_GET2MD(IDENT) \
  csky_arch_isa_features[CSKY_ISA_FEATURE_GET(IDENT)]
#define CSKY_ISA_FEATURE_FAST !CSKY_ISA_FEATURE_GET2MD(smart)



extern char *csky_tolower (char *lo, const char *up);


#endif /* GCC_CSKY_PROTOS_H */
