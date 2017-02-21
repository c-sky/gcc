
(define_constants
  [(PIC_SYMBOL_GOTPC       14)
   (PIC_SYMBOL_GOTPC_GRS   15)
   (PIC_SYMBOL_GOTOFF      1)
   (PIC_SYMBOL_GOT         2)
   (PIC_SYMBOL_PLT         3)
   (PIC_SYMBOL_BSR         4)
   (PIC_SYMBOL_GRS         5)

   (FLAG_PUSH              8)
   (FLAG_POP               9)
   (FLAG_EPILOGUE          10)

   (UNSPEC_TLS_BASE        19)
   (UNSPEC_TLS             20)
   (UNSPEC_TLS_LABEL       21)
   (VUNSPEC_EH_RETURN      22)
   ; this unspec is used to prevent the deletion of
   ; instructions setting registers for EH handling
   ; and stack frame generation.  Operand 0 is the
   ; register to "use"
   ; As USE insns are not meaningful after reload,
   (UNSPEC_REGISTER_USE    23)
   (UNSPEC_CSKY_CASESI     24)
])

(define_constants
  [(VUNSPEC_ALIGN          0)
   (VUNSPEC_POOL_LABEL     1)
   (VUNSPEC_POOL_4         2)
   (VUNSPEC_SYMBOL_REF     3)
])

