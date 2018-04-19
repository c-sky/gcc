/*
 * crt0.S -- startup codes for CK-CPU.
 *
 * Define a exception vector table
 *
 * Initial PSR register.
 * Initial VBR register, relocate exception vector table.
 * Initial sp(stack pointer) register.
 * Initial MGU (for ckcpu having MGU)
 * Initial Cache.
 * Initial SPM (for ckcpu having SPM).
 * Initial BSS section to "0"
 * Then goto "main".
 *
 * Copyright (C) 2008~2010  Hangzhou C-SKY Microsystems Co., Ltd
 */

#include "config.h"

.file "crt0.S"
.global __exit
/*
 *         MGU & CACHE macro from "ck5a6.h"
 *
 * CONFIG_CKCPU_MGU_BLOCKS	---- MGU block priority setting value
 * CONFIG_CKCPU_MGU_REGION(1-4)
 *                          ---- MGU (1-4) block base address and size.
 * CONFIG_CKCPU_ICACHE		---- Instruction cache enable
 * CONFIG_CKCPU_DCACHE		---- Data cache enable
 *
 *         SPM macro from "ck5a6.h"
 *
 * CONFIG_CKCPU_SPM		---- CKCPU having SPM ?
 * CONFIG_CKCPU_SPM_ENABLE	---- SPM Enable
 * CONFIG_CKCPU_ISPM_MODE	---- Instruction SPM Mode(cache/local memory)
 * CONFIG_CKCPU_DSPM_MODE	---- Data SPM Mode (cache/local memory)
 * CONFIG_CKCPU_ISPM_ADDRESS
 *                          ---- Instruction SPM external memory base address,
 *                               Just for Local Memory Mode
 * CONFIG_CKCPU_DSPM_ADDRESS
 *                          ---- Data SPM external memory base address, Just
 *				                 for Local Memory Mode
 * CONFIG_CKCPU_ISPM_TRANSFER
 *                          ---- The content in Instruction SPM must be
 *                               initialed, Just for Local Memory Mode
 * CONFIG_CKCPU_DSPM_TRANSFER
 *                          ---- The content in Data SPM must be initialed,
 *                               Just for Local Memory Mode 
 */

/*
 * For importing variable or functions from script file "ckcpu.ld".
 */
.import __stack		/* The stack pointer from linking script file */
.import __fstack	/* The fast interrupt stack from linking script file */
.import	__sbss		/* The end of bss from linking script file */
.import __ebss		/* The end of bss from linking script file */

/*
 * For importing variable or functions from other c or assemble files.
 */
.import main				/* The c codes entry */
.import spm_init			/* Initial ckcpu SPM */

/*
 * For importing variable or functions from entry.S.
 */
//.import default_exception_handler /* default exception service routine */

/* For exporting varialbe or functions */
.export	ckcpu_vsr_table	/* Vector table base address. */
.export __start				/* The system entry. */
.export __abort
.export abort


.text
/* Vector table space. */
.align 10
ckcpu_vsr_table:
.rept 128
.long __default_exception_handler
.endr

/* The ckcpu startup codes. */
.text
	/*
	 *	
	 * This is the codes first entry point. This is where it all
	 * begins...
	 */
.long __start

__start:
	/*
	 * Init psr value, enable exception, disable interrupt and fast interrupt.
	 * psr = 0x80000100
	 */
	lrw	r7, 0
	bseti	r7, 31
	bseti	r7, 8
	mtcr	r7, psr
	
	/*
	 * Setup initial vector base table for interrupts and exceptions
	 */
	lrw		r6, ckcpu_vsr_table
	mtcr	r6, vbr
	
	/* Initialize the normal stack pointer from the linker definition. */
	lrw		r7, __stack
	mov		sp, r7

#ifdef FAST_INTERRUPT_ENABLE
	/* Initialize the fast interrupt stack pointer . */
	psrset	af
	lrw		r6, __fstack
	mov		sp, r6
	psrclr	af
#endif

	/*
	 * Initial CKCPU MGU & Cache
	 * Step 1: Disable MGU & Cache.
	 */
	movi	r7, 0
	mtcr	r7, cr18
//
//	/*
//	 * Initial CKCPU MGU & Cache
//	 * Step 2: priority setting, ff -- read and write
//	 */
//	lrw		r6, 0xff00
//	mtcr	r6, cr19
//
//	/*
//	 * Initial CKCPU MGU & Cache
//	 * Step 3: set MGU block
//	 */
//
//   	/* The first block */
//	movi	r5, 0
//	mtcr	r5, cr21
//#ifdef CONFIG_CKCPU_MGU_REGION1
//	lrw		r7, CONFIG_CKCPU_MGU_REGION1
//	mtcr	r7, cr20
//#else
//	mtcr	r5, cr20
//	
//#endif
//	/* The second block */
//	movi	r4, 1
//	mtcr	r4, cr21
//#ifdef 	CONFIG_CKCPU_MGU_REGION2
//	lrw		r7, CONFIG_CKCPU_MGU_REGION2
//	mtcr	r7, cr20
//#else
//	mtcr	r5, cr20
//#endif
//	/* The third block */
//	movi	r4, 2
//	mtcr	r4, cr21
//#ifdef CONFIG_CKCPU_MGU_REGION3
//	lrw		r7, CONFIG_CKCPU_MGU_REGION3
//	mtcr	r7, cr20
//#else
//	mtcr	r5, cr20
//#endif
//	/* The forth block */
//	movi	r4, 3
//	mtcr	r4, cr21
//#ifdef CONFIG_CKCPU_MGU_REGION4
//	lrw		r7, CONFIG_CKCPU_MGU_REGION4
//	mtcr	r7, cr20
//#else
//	mtcr	r5, cr20
//#endif
//
//	/*
//	 * Initial CKCPU MGU & Cache
//	 * Step 4: enable instruction & data cache
//	 */
//#if CONFIG_CKCPU_ICACHE
//	/* Invalid Instruction cache content */
//	movi    r7, 0x11
//	mtcr	r7, cr17
//
//	/* Enable instruction cache */
//	mfcr	r6, cr18
//	bseti	r6, 2
//	mtcr	r6, cr18
//#endif /* #ifdef CONFIG_CKCPU_ICACHE */
//
//#if CONFIG_CKCPU_DCACHE
//	/* Invalid Data cache content */
//	movi	r7, 0x12
//	mtcr	r7, cr17
//
//	/* Enable Data cache */
//	mfcr	r7, cr18
//	bseti	r7, 3
//	mtcr	r7, cr18
//#endif /* #ifdef CONFIG_CKCPU_DCACHE */
//
//	/*
//	 * Initial CKCPU MGU & Cache
//	 * Step 5: enable MGU
//	 */
//	mfcr	r7, cr18
//	/* cr18[1~0]: enable MGU */
//	bseti	r7, 0
//	bclri	r7, 1
//	/* cr18[4]: enable write back, ck610 only */
//	bseti	r7, 4
//	/* cr18[5]: enable return stack, ck610 only */
//	bseti	r7, 5
//	/* cr18[6]: enable branch predictor */
//	bseti	r7, 6
//	mtcr	r7, cr18
//
//	/*
//	 *  Initial CKCPU SPM.
//	 */
//#if CONFIG_CKCPU_SPM
//	/* Step 1: disable data & instruction spm */
//	movi    r2, 0
//	jsri    spm_enable_instruction
//	movi    r2, 0
//	jsri    spm_enable_data
//#if CONFIG_CKCPU_SPM_ENABLE
//	/* Step 2: config instrunction and data spm */
//	lrw		r2, CONFIG_CKCPU_ISPM_MODE
//	lrw		r3, CONFIG_CKCPU_DSPM_MODE
//	lrw		r4, CONFIG_CKCPU_ISPM_ADDRESS
//	lrw		r5, CONFIG_CKCPU_DSPM_ADDRESS
//	/* Instruction SPM must be transfered? */
//	lrw		r6, CONFIG_CKCPU_ISPM_TRANSFER
//	/* Data SPM must be transfered */
//	lrw		r7, CONFIG_CKCPU_DSPM_TRANSFER
//	jsri	spm_init
//	cmpnei	r2, 0  /* Error?  when transfer to spm. */
//	bt	1f
//
//	/* Step 3:  enable instruction and data spm */
//	movi	r2, 1
//	jsri	spm_enable_instruction
//	movi	r2, 1
//	jsri	spm_enable_data
//1:
//#endif  /* CONFIG_CKCPU_SPM_ENABLE */
//#endif  /* CONFIG_CKCPU_SPM */
//
	/*
	 * Zero out the bss region.
	 * NOTE: __sbss must align 4
	 */
	lrw		r7, __sbss	/* Get start of bss from linking script file */
	lrw		r6, __ebss	/* Get end of bss from linking script file */
	subu	r6, r7		/* Calculate size of bss */
	lsri	r6, r6, 2		/* Size of whole words */
	cmpnei	r6, 0
	bf		__goto_c
	movi	r5, 0		/* Set zero value to write */
2:
	stw		r5, (r7)	/* Zero next word */
	addi	r7, 4		/* Increase bss pointer */
	subi	r6, 1			/* Decrease counter */
	cmpnei	r6, 0
	bt		2b			/* Repeat for all bss */

	/*
         * Disable PWRM
         */
//	lrw	r1, 0xe000ef90
//	movi	r2, 0x0
//	st.w	r2, (r1, 0x0)

	/*
	 * Assember start up done, C codes start here.
	 */
__goto_c:
	/*jsri	main*/
	lrw	r5, main
	jsr	r5
	
	/* Should never get here. */
__exit:
//	/*qemu test*/
//	lrw     r4, 0x10002000
//	lrw     r5, 0x2002
//	stw     r5, (r4, 0)
//	stw     r5, (r4, 0)
    	bkpt
	br	__exit

__default_exception_handler:
    	bmaski r0, 32
    	bkpt
    	br  __default_exception_handler
    	rte
abort:
__abort:
   	bkpt
   	br __abort
