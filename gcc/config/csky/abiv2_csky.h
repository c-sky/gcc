
#ifndef GCC_CSKY_H
#define GCC_CSKY_H


/******************************************************************
 *     Defining data structures for per-function information      *
 ******************************************************************/


/* A C structure for machine-specific, per-function data.
   This is added to the cfun structure.  */
typedef struct GTY(()) machine_function
{
  /* Records if LR has to be saved for far jumps.  */
  int far_jump_used;
  /* Records the type of the current function.  */
  unsigned long func_type;
  /* Record if the function has a variable argument list.  */
  int uses_anonymous_args;
  /* Record the number of regs before varargs.  */
  int number_of_regs_before_varargs;
}
machine_function;


/******************************************************************
 *                         Storage Layout                         *
 ******************************************************************/


/* Define this if most significant bit is lowest numbered
   in instructions that operate on numbered bit-fields.  */
#define BITS_BIG_ENDIAN  0

/* Define this if most significant byte of a word is the lowest numbered.  */
#define BYTES_BIG_ENDIAN (TARGET_BIG_ENDIAN != 0)

/* Define this if most significant word of a multiword number is the lowest.  */
#define WORDS_BIG_ENDIAN (BYTES_BIG_ENDIAN)

/* Width of a word, in units (bytes).  */
#define UNITS_PER_WORD 4

/* Define this macro if it is advisable to hold scalars in registers
   in a wider mode than that declared by the program.  In such cases,
   the value is constrained to be within the bounds of the declared
   type, but kept valid in the wider mode.  The signedness of the
   extension may differ from that of the type.  */
#define PROMOTE_MODE(MODE, UNSIGNEDP, TYPE)     \
  if (GET_MODE_CLASS (MODE) == MODE_INT         \
      && GET_MODE_SIZE (MODE) < UNITS_PER_WORD) \
    {                                           \
      (MODE) = SImode;                          \
    }

/* Allocation boundary (in *bits*) for storing arguments in argument list.  */
#define PARM_BOUNDARY   32

/* Boundary (in *bits*) on which stack pointer should be aligned.  */
#define STACK_BOUNDARY  32

/* Make strings word-aligned so strcpy from constants will be faster.  */
#define CONSTANT_ALIGNMENT(EXP, ALIGN)      \
  ((TREE_CODE (EXP) == STRING_CST           \
    && !optimize_size                       \
    && (ALIGN) < BITS_PER_WORD)             \
   ? BITS_PER_WORD : (ALIGN))

/* Align definitions of arrays, unions and structures so that
   initializations and copies can be made more efficient.  This is not
   ABI-changing, so it only affects places where we can see the
   definition. Increasing the alignment tends to introduce padding,
   so don't do this when optimizing for size/conserving stack space. */
#define CSKY_EXPAND_ALIGNMENT(COND, EXP, ALIGN) \
    (((COND) && ((ALIGN) < BITS_PER_WORD)       \
      && (TREE_CODE(EXP) == ARRAY_TYPE          \
          || TREE_CODE(EXP) == UNION_TYPE       \
          || TREE_CODE(EXP) == RECORD_TYPE))    \
     ? BITS_PER_WORD : (ALIGN))

/* Align global data. */
#define DATA_ALIGNMENT(EXP, ALIGN)      \
  CSKY_EXPAND_ALIGNMENT(!optimize_size, EXP, ALIGN)

/* Similarly, make sure that objects on the stack are sensibly aligned.  */
#define LOCAL_ALIGNMENT(EXP, ALIGN)       \
  CSKY_EXPAND_ALIGNMENT(!flag_conserve_stack, EXP, ALIGN)

/* No data type wants to be aligned rounder than this.  */
#define BIGGEST_ALIGNMENT 32

/* Every structures size must be a multiple of 8 bits.  */
#define STRUCTURE_SIZE_BOUNDARY 8

/* Look at the fundamental type that is used for a bit-field and use
   that to impose alignment on the enclosing structure.
   struct s {int a:8}; should have same alignment as "int", not "char".  */
#define PCC_BITFIELD_TYPE_MATTERS 1

/* Largest integer machine mode for structures.  If undefined, the default
   is GET_MODE_SIZE(DImode).  */
#define MAX_FIXED_MODE_SIZE 64

/* Allocation boundary (in *bits*) for the code of a function.
   we prefer to performance, but we care about much more for size like ck801
   and so on.  */
#define FUNCTION_BOUNDARY (((TARGET_CK801 || TARGET_CK802) \
                            && optimize_size) ? 16 : 32)

/* Set this nonzero if move instructions will actually fail to work
   when given unaligned data.  */
#define STRICT_ALIGNMENT    (TARGET_STRICT_ALIGNMENT)


/******************************************************************
 *              Layout of Source Language Data Types              *
 ******************************************************************/


/* 'char' is unsigned by default for backward compatiblity  */
#define DEFAULT_SIGNED_CHAR    0


/******************************************************************
 *              Stack Layout and Calling Conventions              *
 ******************************************************************/


/* Basic Stack Layout  */


/* Define this if pushing a word on the stack
   makes the stack pointer a smaller address.  */
#define STACK_GROWS_DOWNWARD    1

/* Define this to nonzero if the nominal address of the stack frame
   is at the high-address end of the local variables;
   that is, each additional local variable allocated
   goes at a more negative offset in the frame.  */
#define FRAME_GROWS_DOWNWARD    1

/* Offset within stack frame to start allocating local variables at.
   If FRAME_GROWS_DOWNWARD, this is the offset to the END of the
   first local allocated.  Otherwise, it is the offset to the BEGINNING
   of the first local allocated.  */
#define STARTING_FRAME_OFFSET   0

/* Offset of first parameter from the argument pointer register value.  */
#define FIRST_PARM_OFFSET(FNDECL) 0

/* A C expression whose value is RTL representing the value of the return
   address for the frame COUNT steps up from the current frame.  */
#define RETURN_ADDR_RTX(COUNT, FRAME) \
  csky_return_addr (COUNT, FRAME)

/* Pick up the return address upon entry to a procedure. Used for
   dwarf2 unwind information.  This also enables the table driven
   mechanism.  */
#define INCOMING_RETURN_ADDR_RTX  gen_rtx_REG (Pmode, LR_REGNUM)


/* Registers That Address the Stack Frame  */


/* Register to use for pushing function arguments.  */
#define STACK_POINTER_REGNUM  SP_REGNUM

/* Base register for access to local variables of the function.  */
#define FRAME_POINTER_REGNUM  8

/* Base register for access to arguments of the function.  */
#define ARG_POINTER_REGNUM    32

/* TODO  */
#define STATIC_CHAIN_REGNUM   (TARGET_CK801 ? 7 : 12)


/* Eliminating Frame Pointer and Arg Pointer  */


/* Definitions for register eliminations.

   This is an array of structures.  Each structure initializes one pair
   of eliminable registers.  The "from" register number is given first,
   followed by "to".  Eliminations of the same "from" register are listed
   in order of preference.

   We have two registers that can be eliminated on the CSKY.  First, the
   arg pointer register can often be eliminated in favor of the stack
   pointer register.  Secondly, the pseudo frame pointer register can always
   be eliminated; it is replaced with the stack pointer.  */
#define ELIMINABLE_REGS           \
{{ ARG_POINTER_REGNUM,        STACK_POINTER_REGNUM            },\
 { ARG_POINTER_REGNUM,        FRAME_POINTER_REGNUM            },\
 { FRAME_POINTER_REGNUM,      STACK_POINTER_REGNUM            }}

/* Define the offset between two registers, one to be eliminated, and the
   other its replacement, at the start of a routine.  */
#define INITIAL_ELIMINATION_OFFSET(FROM, TO, OFFSET)      \
  (OFFSET) = csky_initial_elimination_offset (FROM, TO)


/* Passing Function Arguments on the Stack  */


/* Define this if the maximum size of all the outgoing args is to be
   accumulated and pushed during the prologue.  The amount can be
   found in the variable crtl->outgoing_args_size.  */
#define ACCUMULATE_OUTGOING_ARGS 1


/* Passing Arguments in Registers  */


/* A C type for declaring a variable that is used as the first argument of
   TARGET_ FUNCTION_ARG and other related values.  */
#define CUMULATIVE_ARGS  int

/* Initialize a variable CUM of type CUMULATIVE_ARGS
   for a call to a function whose data type is FNTYPE.
   For a library call, FNTYPE is 0.

   On CSKY, the offset always starts at 0: the first parm reg is always
   the same reg.  */
#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, INDIRECT, N_NAMED_ARGS) \
  ((CUM) = 0)

/* 1 if N is a possible register number for function argument passing.
   On the CSKY, r0-r3 are used to pass args.  */
#define FUNCTION_ARG_REGNO_P(REGNO)         \
  ((REGNO) >= CSKY_FIRST_PARM_REG           \
   && (REGNO) < (CSKY_NPARM_REGS + CSKY_FIRST_PARM_REG))


/* How Large Values Are Returned  */


/* Define DEFAULT_PCC_STRUCT_RETURN to 1 if all structure and union return
   values must be in memory.  On the CSKY, small
   structures (eight bytes or fewer) are returned in
   the register pair r0/r1.  */
#define DEFAULT_PCC_STRUCT_RETURN 0


#endif /* GCC_CSKY_H */
