
#ifndef GCC_CSKY_PROTOS_H
#define GCC_CSKY_PROTOS_H


#define CSKY_STACK_BOUNDARY_BYTES (STACK_BOUNDARY/BITS_PER_UNIT)

#define CSKY_NPARM_REGS       4
#define CSKY_FIRST_PARM_REG   0
#define CSKY_NGPR_REGS        32
#define CSKY_FIRST_RET_REG    0

#define CSKY_NUM_WORDS(SIZE) ((SIZE + UNITS_PER_WORD - 1) / UNITS_PER_WORD)

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


#endif /* GCC_CSKY_PROTOS_H */
