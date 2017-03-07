# crti.asm for ELF based systems

#   Copyright (C) 1992, 1998, 1999 Free Software Foundation, Inc.
#   Written By David Vinayak Henkel-Wallace, June 1992
# 
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2, or (at your option) any
# later version.
# 
# In addition to the permissions in the GNU General Public License, the
# Free Software Foundation gives you unlimited permission to link the
# compiled version of this file with other programs, and to distribute
# those programs without any restriction coming from the use of this
# file.  (The General Public License restrictions do apply in other
# respects; for example, they cover modification of the file, and
# distribution when not linked into another program.)
# 
# This file is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not, write to
# the Free Software Foundation, 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
# 
#    As a special exception, if you link this library with files
#    compiled with GCC to produce an executable, this does not cause
#    the resulting executable to be covered by the GNU General Public License.
#    This exception does not however invalidate any other reasons why
#    the executable file might be covered by the GNU General Public License.
# 

# This file just makes a stack frame for the contents of the .fini and
# .init sections.  Users may put any desired instructions in those
# sections.

	.file		"crti.asm"

#if defined(OPTION_GLIBC) && (OPTION_GLIBC == 1)

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

#if PREINIT_FUNCTION_WEAK
        .align 4
        .type call_weak_fn, %function
call_weak_fn:
        //push    lr
        subi    sp, 4
        stw     lr, (sp)
#ifdef  __PIC__
        lrw     a2, PREINIT_FUNCTION@GOT
        addu    a2, gb
        ldw     a2, (a2)
#else
        lrw     a2, PREINIT_FUNCTION
#endif
        cmpnei  a2, 0
        bf      1f
        jsr     a2
1:
        //pop lr
        ldw     lr, (sp)
        addi    sp, 4
        rts

        .align 4
#endif
        .section .init,"ax",@progbits
        .align 4
        .globl _init
        .type _init, @function
_init:
        subi    sp, 8
        stw     lr, (sp, 0)
#ifdef __PIC__
//        stw     gb, (sp, 4)
        bsr     .Lgetpc
.Lgetpc:
        lrw     gb, .Lgetpc@GOTPC
        add     gb, lr
#endif
#if PREINIT_FUNCTION_WEAK
#ifdef __PIC__
        lrw     a2, call_weak_fn@GOTOFF
        add     a2, gb
        jsr     a2
#else
        jsri    call_weak_fn
#endif
#else
#ifdef  __PIC__
        lrw     a2, PREINIT_FUNCTION@PLT
        addu    a2, gb
        ldw     a2, (a2)
        jsr     a2
#else
        jsri    PREINIT_FUNCTION
#endif

#endif
        br      2f
        .literals
        .align  4
2:

        .section .fini,"ax",@progbits
        .align 4
        .globl _fini
        .type _fini, @function
_fini:
        subi    sp,8
	stw     lr, (sp, 0)
        br      2f
        .literals
        .align  4
2:

#else
	.section	".init"
	.global	_init
	.type	_init,@function
	.align	2
#	.align	4
# amended by liub, 2006/08/09
_init:
#ifdef __CSKYABIV2__
	subi	sp, 16
	st.w	lr, (sp, 12)
    mov     r0, r0
#else
    subi    r0, 16
    st.w    r15, (r0, 12)
#endif

	# These nops are here to align the end of this code with a 16 byte
	# boundary.  The linker will start inserting code into the .init
	# section at such a boundary.
	
#	nop
#	nop
#	nop
#	nop
#	nop
#	nop

	
	.section	".fini"
	.global	_fini
	.type	_fini,@function
	.align	2
#	.align	4
# amended by liub, 2006/08/09
_fini:
#ifdef __CSKYABIV2__
	subi	sp, 16
	st.w	lr, (sp, 12)
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

