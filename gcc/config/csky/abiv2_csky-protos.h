
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
#define CSKY_SP_REGNUM                14
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

#define CSKY_NUM_REGS(MODE) \
  CSKY_NUM_WORDS(GET_MODE_SIZE (MODE))

#define CSKY_CONSTPOOL_LABEL_PREFIX   "LCP"

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

/* define these macros to describe the function type.  */
#define CSKY_FT_TYPE_MASK   ((1 << 3) - 1)
#define CSKY_FT_UNKNOWN     0               /*Type not been determined */
#define CSKY_FT_NORMAL      1               /*Normal function */
#define CSKY_FT_ISR         4               /*Interrupt service routine */
#define CSKY_FT_FIQ         5               /*Fast interrupt service routine */
#define CSKY_FT_EXCEPTION   6               /*Exception handler */

#endif /* GCC_CSKY_PROTOS_H */
