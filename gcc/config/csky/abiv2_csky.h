
#ifndef GCC_CSKY_H
#define GCC_CSKY_H


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


#endif /* GCC_CSKY_H */
