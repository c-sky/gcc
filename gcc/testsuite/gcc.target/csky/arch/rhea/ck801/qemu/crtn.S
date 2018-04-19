	.file	"initfini.c"
#APP
	
	.section .init
#NO_APP
	.align	2
	.globl	_init
	.type	_init, @function
#NO_APP
	ldw     lr, (sp)    /* load return address from stack */
        addi    sp, 4        /* increase stack pointer */
        rts
	.size	_init, .-_init
#APP
	
	.section .fini
#NO_APP
	.align	2
	.globl	_fini
	.type	_fini, @function
#NO_APP
	ldw     lr, (sp)  /*  load return address from stack */
        addi    sp, 4      /* increase stack pointer */
        rts
	.size	_fini, .-_fini
#APP
	
	.ident	"GCC: (GNU) 3.3.2"
