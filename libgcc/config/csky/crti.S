# This file just makes a stack frame for the contents of the .fini and
# .init sections.  Users may put any desired instructions in those
# sections.

  .file    "crti.S"

# The macro __gnu_linux mean to use glibc if it ddefines.
#if defined(__gnu_linux__)

#ifndef PREINIT_FUNCTION
# define PREINIT_FUNCTION __gmon_start__
#endif

#ifndef PREINIT_FUNCTION_WEAK
# define PREINIT_FUNCTION_WEAK 1
#endif

#if PREINIT_FUNCTION_WEAK
  .global PREINIT_FUNCTION
  .weak PREINIT_FUNCTION
#else
  .hidden PREINIT_FUNCTION
#endif

  .section .init,"ax",@progbits
  .align 4
  .globl _init
  .hidden _init
  .type _init, @function
_init:
  subi    sp, 8
  stw     lr, (sp, 0)
  stw     gb, (sp, 4)
  grs     t0, .Lgetpc
.Lgetpc:
  lrw     gb, .Lgetpc@GOTPC
  add     gb, t0
#if PREINIT_FUNCTION_WEAK
  lrw     a2, PREINIT_FUNCTION@GOT
  ldr.w   a2, (gb, a2 << 0)
  cmpnei  a2, 0
  bf      1f
  jsr     a2
1:
#else
  lrw     a2, PREINIT_FUNCTION@GOT
  ldr.w   a2, (gb, a2 << 0)
  jsr     a2
#endif
  br      2f
  .literals
  .align  4
2:

  .section .fini,"ax",@progbits
  .align 4
  .globl _fini
  .hidden _fini
  .type _fini, @function
_fini:
  subi    sp,4
  stw     lr, (sp, 0)
  br      2f
  .literals
  .align  4
2:
#else
  .section  ".init"
  .global  _init
  .hidden  _init
  .type  _init,@function
  .align  2
#  .align  4
_init:
#ifdef __CSKYABIV2__
  subi  sp, 16
  st.w  lr, (sp, 12)
  mov     r0, r0
#else
  subi    r0, 16
  st.w    r15, (r0, 12)
#endif

  # These nops are here to align the end of this code with a 16 byte
  # boundary.  The linker will start inserting code into the .init
  # section at such a boundary.

#  nop
#  nop
#  nop
#  nop
#  nop
#  nop


  .section  ".fini"
  .global  _fini
  .hidden  _fini
  .type  _fini,@function
  .align  2
_fini:
#ifdef __CSKYABIV2__
  subi  sp, 16
  st.w  lr, (sp, 12)
    mov     r0, r0
#else
    subi    r0, 16
    st.w    r15, (r0, 12)
#endif
  #nop
  #nop
  #nop
  #nop
  #nop
  #nop
#endif

