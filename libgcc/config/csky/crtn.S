# This file just makes sure that the .fini and .init sections do in
# fact return.  Users may put any desired instructions in those sections.
# This file is the last thing linked into any executable.

  .file    "crtn.S"

# The macro __gnu_linux mean to use glibc if it ddefines.
#if defined(__gnu_linux__)
   .section .init,"ax",@progbits
   ldw     lr, (sp, 0)
   ldw     gb, (sp, 4)
   addi    sp, 8
   rts

   .section .fini,"ax",@progbits
   ldw     lr, (sp, 0)
   addi    sp, 4
   rts
#else

  .section  ".init"
  ldw     lr, (sp, 12)
  addi    sp, 16
  jmp     lr

  .section  ".fini"
  ldw     lr, (sp, 12)
  addi    sp, 16
  jmp     lr

# Th-th-th-that is all folks!
#endif
