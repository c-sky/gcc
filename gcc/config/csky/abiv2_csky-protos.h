
#ifndef GCC_CSKY_PROTOS_H
#define GCC_CSKY_PROTOS_H


#define CSKY_STACK_BOUNDARY_BYTES (STACK_BOUNDARY/BITS_PER_UNIT)

#define CSKY_NPARM_REGS               4
#define CSKY_FIRST_PARM_REG           0
#define CSKY_NGPR_REGS                32
#define CSKY_FIRST_RET_REG            0
#define CSKY_NPARM_FREGS              4
#define CSKY_FIRST_VFP_REGNUM         52
#define CSKY_LAST_VFP_REGNUM          67
#define CSKY_FIRST_PERESERVED_VFP     60
#define CSKY_LAST_PERESERVED_VFP      67
#define CSKY_NVFP_REGS                16
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
#define CSKY_TLS_REGNUM               31

#define CSKY_LD16_MAX_OFFSET(MODE)    (31 * GET_MODE_SIZE(MODE))
#define CSKY_LD32_MAX_OFFSET(MODE)    (4095 * GET_MODE_SIZE(MODE))
#define CSKY_LD16_OFFSET_MASK(MODE)   (CSKY_LD16_MAX_OFFSET (MODE) \
                                       + GET_MODE_SIZE (MODE) - 1)
#define CSKY_ADDI16_MAX_IMM           256
#define CSKY_SUBI16_MAX_IMM           256

#define CSKY_MULTIPLE_LDST_THRESHOLD  3
#define CSKY_MAX_MULTIPLE_STLD        12

#define CSKY_NUM_WORDS(SIZE) ((SIZE + UNITS_PER_WORD - 1) / UNITS_PER_WORD)

#define CSKY_GENERAL_REGNO_P(N) \
  ((N) < CSKY_NGPR_REGS && (N) >= 0)

#define CSKY_VREG_P(N)               \
  (((N) >= CSKY_FIRST_VFP_REGNUM)    \
   && ((N) <= CSKY_LAST_VFP_REGNUM))

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

#define CSKY_CONST_OK_FOR_Ul(VALUE)  \
  ((((VALUE) & 0x3) == 0)            \
   && VALUE_BETWEEN(VALUE, -1024, -4))

#define CSKY_CONST_OK_FOR_Um(VALUE)  \
  (VALUE_BETWEEN((VALUE), -4096, -1))

#define CSKY_CONST_OK_FOR_J(VALUE)  \
  (VALUE_BETWEEN((VALUE), 1, 32))

#define CSKY_CONST_OK_FOR_Uk(VALUE)  \
  (VALUE_BETWEEN(VALUE, 1, 65536))

#define CSKY_CONST_OK_FOR_Uh(VALUE)  \
  (VALUE_BETWEEN(VALUE, -31, 0))

#define CSKY_CONST_OK_FOR_Ue(VALUE)      \
  (get_csky_int_zeros(VALUE) <= 2 &&     \
   get_csky_int_zeros(VALUE) == get_csky_int_zeros((VALUE) & 0xFFFFFFFF))

#define CSKY_CONST_OK_FOR_Uf(VALUE)      \
  (get_csky_int_ones(VALUE) <= 2 &&      \
   get_csky_int_ones(VALUE) == get_csky_int_ones((VALUE) & 0xFFFFFFFF))

#define CSKY_CONST_OK_FOR_O(VALUE)  \
  (VALUE_BETWEEN(VALUE, 0, 4095))

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
  int freg_size;      /* Non-volatile float reg saves (bytes).  */
  int reg_mask;       /* non-volatile general reg saves */
  int freg_mask;      /* non-volatile float reg saves */
  int local_size;     /* locals */
  int outbound_size;  /* arg overflow on calls out */

  int pad_outbound;
  int pad_local;
  int pad_reg;
  int pad_arg;
}
csky_stack_frame;

/* Define these macros to describe the function type.  */
#define CSKY_FT_TYPE_MASK   ((1 << 3) - 1)
#define CSKY_FT_UNKNOWN     0               /* Type not been determined */
#define CSKY_FT_NORMAL      1               /* Normal function */
#define CSKY_FT_ISR         4               /* Interrupt service routine */
#define CSKY_FT_FIQ         5               /* Fast interrupt service routine */
#define CSKY_FT_EXCEPTION   6               /* Exception handler */
#define CSKY_FT_INTERRUPT   (1 << 2)        /* overlap CSKY_FT_ISR */
#define CSKY_FT_NAKED       (1 << 3)        /* No prologue and epilogue */
#define CSKY_FUNCTION_TYPE(t)         (t & CSKY_FT_TYPE_MASK)
#define CSKY_FUNCTION_IS_INTERRUPT(t) (t & CSKY_FT_INTERRUPT)
#define CSKY_FUNCTION_IS_NAKED(t)     (t & CSKY_FT_NAKED)

struct csky_address
{
  rtx base, index, symbol, label, disp, post_inc_reg;
  HOST_WIDE_INT scale;
};

/* A type to distinguish the different forms of outputing
   inline const.  */

enum csky_inline_const_type
{
  IC_UNINLINABLE = 0, /* Not inibale */
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
extern const char *output_ck801_movedouble (rtx operands[],
                                           enum machine_mode mode ATTRIBUTE_UNUSED);
extern int symbolic_csky_address_p (rtx);
extern bool decompose_csky_address (rtx, struct csky_address *);
extern const char *output_csky_bclri (rtx, rtx, int);
extern const char *output_csky_bseti (rtx, rtx, int);
extern int get_csky_int_ones (HOST_WIDE_INT);
extern int get_csky_int_zeros (HOST_WIDE_INT);
extern bool can_trans_by_csky_shlshr (unsigned HOST_WIDE_INT);
extern int is_csky_const_float_1 (rtx, enum machine_mode);
extern int is_csky_const_float_0 (rtx, enum machine_mode);
extern int get_cskyv2_mem_constraint (const char *, rtx);
#ifdef RTX_CODE
extern bool gen_csky_compare (enum rtx_code, rtx, rtx);
extern bool gen_csky_compare_float (enum rtx_code, rtx, rtx);
extern int csky_split_constant (enum rtx_code, machine_mode, rtx,
                                HOST_WIDE_INT, rtx, rtx, int);
extern bool csky_can_split_constant (enum rtx_code, rtx,
                                     HOST_WIDE_INT);
#endif /* RTX_CODE */

extern int csky_hard_regno_mode_ok (unsigned int regno, enum machine_mode mode);
extern rtx csky_return_addr (int count, rtx frame ATTRIBUTE_UNUSED);
extern void csky_init_expanders (void);
extern HOST_WIDE_INT csky_initial_elimination_offset (int, int);
extern void csky_expand_prologue(void);
extern void csky_expand_epilogue(void);
extern const char *output_csky_return_instruction(void);
extern const char *csky_unexpanded_epilogue(void);
extern void set_csky_return_address (rtx source, rtx scratch);

extern int symbol_mentioned_p (rtx x);
extern int label_mentioned_p (rtx x);
extern rtx legitimize_pic_address (rtx orig, rtx reg, int flag);
extern char *csky_output_call (rtx operands[], int index);

extern int tls_mentioned_p(rtx x);
extern bool csky_tls_referenced_p (rtx x);
extern rtx legitimize_tls_address (rtx x, rtx reg);

extern const char *csky_output_casesi (rtx *operands);
extern int get_csky_pushpop_length (rtx*);

extern void csky_init_cumulative_args (CUMULATIVE_ARGS *, tree, rtx, tree);
extern int const_ok_for_cskyv2 (HOST_WIDE_INT);

/* The following are used in the .md file as equivalents to bits.  */
#include "abiv2_csky_isa.h"
extern int csky_arch_isa_features[];
#define CSKY_ISA_FEATURE(IDENT) \
  csky_arch_isa_features[CSKY_ISA_FEATURE_GET(IDENT)]
#define CSKY_ISA_FEATURE_FAST !CSKY_ISA_FEATURE(smart)

#define TARGET_SOFT_TP      !TARGET_HARD_TP

#define TARGET_SOFT_FPU     (csky_fpu_index == TARGET_FPU_fpv2_sf)

#include "abiv2_csky_internal.h"
extern const struct tune_params *current_tune;

#endif /* GCC_CSKY_PROTOS_H */
