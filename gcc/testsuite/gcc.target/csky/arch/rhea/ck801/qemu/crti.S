	.file	"initfini.c"
#APP
	
	.section .init
#NO_APP
	.align	2
	.globl	_init
	.type	_init, @function
_init:
        subi    sp, 4       /* make a word room in stack */
        stw     lr, (sp)   /* save return address in stack */
        
#APP
	
	.align 2
	
	
	.section .fini
#NO_APP
	.align	2
	.globl	_fini
	.type	_fini, @function
_fini:
        subi    sp, 4     /* make a word room in stack */
        stw     lr, (sp) /* save return address in stack */
#APP
	.align 2
	
	
	.ident	"GCC: (GNU) 3.3.2"
