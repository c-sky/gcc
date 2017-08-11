/* { dg-skip-if "not a testcase" { "csky-*-*" } { "*" } { "" } } */

.file "crt0.S"
.import __stack
.import __sbss
.import __ebss



.import main



.export __vbrbase
.export __start
.export _exit
.export exit
.export __GI_exit
.export _abort
.export abort
.export __GI_abort
.data

.align 10
__vbrbase:
.rept 128
.long __default_exception_handler
.endr


.text
__start:

        lrw r1, 0x80000100
        mtcr r1, psr

        lrw r1, __vbrbase
        mtcr r1, vbr

        lrw r7, __stack
        mov r0, r7
        
/*	mfcr r7, cr18
        bclri r7, 0
        bclri r7, 1
        bclri r7, 2
        bclri r7, 3
        bclri r7, 6
        mtcr r7, cr18
*/
        movi r7, 0
        mtcr r7, cr18
       
        lrw r7, 0xff06
        mtcr r7, cr19


        movi r10, 0
        mtcr r10, cr21

        lrw r7, 0x3f
        mtcr r7, cr20

        movi r10, 1
        mtcr r10, cr21

        lrw r7, 0x800002f
        mtcr r7, cr20

        movi r10, 2
        mtcr r10, cr21

        lrw r7, 0x2f
        mtcr r7, cr20


        movi r10, 3
        mtcr r10, cr21


        movi r7, 0
        mtcr r7, cr20


        mfcr r7, cr18
        bseti r7, 0
        bclri r7, 1
        mtcr r7, cr18

        mfcr r7, cr18
        bseti r7, 6
        bseti r7, 5
        bseti r7, 4
        mtcr r7, cr18

        mfcr r7, cr17
        bseti r7, 0
        bclri r7, 1
        bclri r7, 2
        bseti r7, 4
        mtcr r7, cr17

        mfcr r7, cr18
        bseti r7, 2
        mtcr r7, cr18

        mfcr r7, cr17
        bclri r7, 0
        bseti r7, 1
        bclri r7, 2
        bseti r7, 4
        mtcr r7, cr17
        mfcr r7, cr18
        bseti r7, 3
        mtcr r7, cr18

#ifdef CONFIG_CSKY_FPU
//        movi   r7, 0
//        mtcr   r7, cr<1, 2>
        cpseti 1
        movi   r7, 0x7
        mtcr   r7, cr15
        movi   r7, 0  /*FPC control register initial value,not care all fpu exception*/
        cpwcr  r7, cpcr1
#endif

        lrw r1, __sbss
        lrw r2, __ebss
        subu r2, r1
        lsri r2, 2
        cmpnei r2, 0
        bf __goto_c
        movi r3, 0

__clear_bss:
        stw r3, (r1)
        addi r1, 4
        decne r2
        bt __clear_bss



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
