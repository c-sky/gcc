/*
 * crt0.S -- startup codes for C-SKY CPU.
 *
 * Define a exception vector table
 *
 * Initial PSR register.
 * Initial VBR register.
 * Initial r0(stack pointer) register.
 * Initial MGU or MMU 
 * Initial Cache.
 * Initial BSS section to "0"
 * Then goto "main".
 *
 * Copyright (C) 2012  Hangzhou C-SKY Microsystems Co., Ltd
 */

.file "crt0.S"

/*
 * For importing variable or functions from linking script file "csky.ld".
 */
.import __mem_start	// The start of memory(SDRAM ...) 
.import __heap_start	// The start of heap (for malloc)
.import __heap_end	// The start of heap 
.import __FIQ_sp	// The fast interrupt stack pointer 
.import __initial_sp	// The stack pointer 
.import	__bss_start	// The start of bss 
.import __bss_end	// The end of bss 

/*
 * For importing variable or functions from other c or assemble files.
 */
.import main            // The c codes entry 
.import minilibc_init   // Initial csky Minilibc
.import _fini 
.import _init
/* For exporting varialbe or functions */
.export	csky_vsr_table	// Vector table base address. 
.export __start		// The system entry.
.export _exit
.export exit
.export __GI_exit
.export _abort
.export abort
.export __GI_abort


.macro INIT_FIQ_STACK
# ifdef CONFIG_USE_FIQ
        psrset  af
        lrw     r7, __FIQ_sp
        mov     sp, r7
        psrclr  af
# endif
.endm

.macro INIT_MMU_MGU
//# ifdef CONFIG_HAVE_MMU
	lrw     r8, __mem_start //get physical address of start RAM
	bmaski  r2, 12          // We use page size is 16M
	lsli    r2, 13
	
	movi    r5, 0x0000001e  //C = 011, D = 1, V = 1, G = 0, pfn = 0x0
	bgeni   r6, 18 
	or      r6, r5          //C = 011, D = 1, V = 1, G = 0, pfn = 0x40000
	movi    r7, 0x00000000  //VPN2 = 0x0, ASID = 0
	
	or      r7, r8          // VPN2 is bit 31-12 of phy addr
	lsri    r8, 6           // get bit 31-12 of phy addr
	or      r5, r8          //pfn
	or      r6, r8          //pfn

        bgeni   r1, 27
#if __CSKY__==1                // for ck610's MMU
	cpseti   cp15 
        cpwcr    r1, cpcr8     //invalid mmu jtlb(ASID)
	cpwcr    r2, cpcr6     // Set Page Mask Register
#else            
        mtcr     r1, cr<8, 15> //invalid mmu jtlb(ASID)
	mtcr     r2, cr<6, 15> // Set Page Mask Register
#endif
        /* Initial TLB */   
	bgeni    r2, 28        // TLBWR
#if __CSKY__==1
	cpwcr    r5, cpcr2
	cpwcr    r6, cpcr3
	cpwcr    r7, cpcr4
	cpwcr    r2, cpcr8
#else
	mtcr     r5, cr<2, 15>
	mtcr     r6, cr<3, 15>
	mtcr     r7, cr<4, 15>
	mtcr     r2, cr<8, 15>
#endif

	mfcr    r7, cr18
	bseti   r7, 0
	bclri   r7, 1
	mtcr    r7, cr18
	jsri    __to_real_vaddr   /* P2V, jump from physic address to virtual
                                         address */
__to_real_vaddr:
//#endif
.endm


/* The csky startup codes. */
.text
/* Vector table space. */
.align 10
csky_vsr_table:
.long	__start
.rept 255
.long __default_exception_handler
.endr

	/*
	 * This is the codes first entry point. This is where it all
	 * begins...
	 */
__start:
	/* Init psr value */
	psrclr  ie, fe
	psrset  ee
	
	/*
	 * Setup initial vector base table for interrupts and exceptions
	 */
	lrw	r1, csky_vsr_table
	mtcr	r1, vbr
	
	/* Initialize the stack pointer from the linker definition. */
	lrw	r7, __initial_sp
	mov	sp, r7 

	/* Initialize the FIQ stack pointer if config */
	INIT_FIQ_STACK

	/*
	 * Disable MGU/MMU & Cache.
	 */
	mfcr    r7, cr18
	/* bclri   r7, 0 1 2 3 6 */
	movi    r6, 0x3f
	andn    r7, r6
	mtcr    r7, cr18	

	/* Enable cache */
	movi    r7, 0x33
	mtcr    r7, cr17            /* Invalid Instruction/Data cache content */
	mfcr    r7, cr18
	bseti   r7, 2
	bseti   r7, 3
	mtcr    r7, cr18

	/* initial mmu or mmu ifconfig */
	INIT_MMU_MGU

/*if FPU supported, initial the FPU*/
//#ifdef CONFIG_CSKY_FPU
        cpseti 1
        movi   r7, 0x7
        mtcr   r7, cr15
        movi   r7, 0  /*FPC control register initial value,not care all fpu exception*/ 
        cpwcr  r7, cpcr1
//#endif


	/*
	 * Zero out the bss region.
	 */
	lrw	r1, __bss_start	/* Get start of bss from linking script file */
	lrw	r2, __bss_end 	/* Get end of bss from linking script file */
	subu	r2, r1		/* Calculate size of bss */
	lsri	r2, 2		/* Size of whole words */
	cmpnei	r2, 0
	bf	__goto_c
	movi	r3, 0		/* Set zero value to write */
__clear_bss:
	stw	r3, (r1)	/* Zero next word */
	addi	r1, 4		/* Increase bss pointer */
	subi	r2, 1		/* Decrease counter */
	cmpnei	r2, 0		/* cmp r2 & 0 */
	bt	__clear_bss	/* Repeat for all bss */

	
	/*
	 * Assember start up done, start code proper.
	 * C codes start here!
	 */

__goto_c:
        jsri main
exit:
__GI_exit:
_exit:
    bkpt
    br _exit
abort:
__GI_abort:
_abort:
    movi  r2, 1
    rsubi r2, 0
    bkpt
    br _abort
__default_exception_handler:
    mfcr  r2, psr
    bkpt
    br __default_exception_handler
    rte

