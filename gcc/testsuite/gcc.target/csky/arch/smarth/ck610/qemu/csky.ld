/*
PROVIDE (__stack = 0x8000000);
 * ckcore.ld  -- The ckcore linking script file.
 */

ENTRY (__start)

MEMORY
{
	flatmem : ORIGIN = 0x8000000, LENGTH = 0x800000
}
PROVIDE (__heap_start = 0x8200000);
PROVIDE (__heap_end = 0x8400000);
PROVIDE (__stack = 0x87ffff8);

SECTIONS {
	.text : {
		. = ALIGN(0x4) ;
		__stext = . ;

		*crt0.o(.text)
		*(.text)
		*(.text*)
		*(.text.*)
		*(.gnu.warning)
		*(.stub)
		*(.gnu.linkonce.t*)
		*(.glue_7t)
		*(.glue_7)
		*(.jcr)
		*(.init)
		*(.fini)
		
		/* This is special code area at the end of the normal
		   text section.  It contains a small lookup table at
		   the start followed by the code pointed to by entries
		   in the lookup table.  
		 */
		. = ALIGN (4) ;
		PROVIDE(__ctbp = .);
		*(.call_table_data)
		*(.call_table_text)

		. = ALIGN(0x10);
		__etext = . ;
	} > flatmem
	.rodata : {
		. = ALIGN(0x4);

		__srodata = .;
		*(.rdata)
		*(.rdata*)
		*(.rdata1)
		*(.rdata.*)
		*(.rodata)
		*(.rodata1)
		*(.rodata*)
		*(.rodata.*)
		*(.rodata.str1.4)

		. = ALIGN(0x10) ;
		__erodata = .;
	} > flatmem
	.data : {
		. = ALIGN(0x4) ;
		__sdata = . ;

		__data_start = . ;
		data_start = . ;
		*(.got.plt)
		*(.got)
		FILL(0) ;
		. = ALIGN(0x20) ; 
		LONG(-1)
		. = ALIGN(0x20) ;
		*(.gnu.linkonce.r*)
		*(.data)
		*(.data*)
		*(.data1)
                *(.tdata)
                *(.tdata.*)
		*(.data.*)
		*(.gnu.linkonce.d*)
		*(.data1)
		*(.eh_frame)
		*(.gcc_except_table)
		*(.gcc_except_table.*)
		*(.sdata) 
		*(.sdata.*)
		*(.gnu.linkonce.s.*)
		*(__libc_atexit)
		*(__libc_subinit)
		*(__libc_subfreeres)
		*(.note.ABI-tag)

		. = ALIGN(4) ;
		__CTOR_LIST__ = .;
		LONG( (__CTOR_LIST_END__ - __CTOR_LIST__) / 4 - 2 )
		KEEP(*(SORT(.ctors*)))
		__CTOR_END__ = .;
		LONG( 0 )
		__CTOR_LIST_END__ = .;
		__DTOR_LIST__ = .;
		LONG( (__DTOR_END__ - __DTOR_LIST__) / 4 - 2 )
		KEEP (*(SORT(.dtors*)))
		LONG( 0 )
		__DTOR_END__ = .;

		. = ALIGN(0x10) ; 
		__edata = . ;
		__fini_array_end = .;
	        __fini_array_start = .;
	        __preinit_array_end = .;
	        __preinit_array_start = .;
	        __init_array_end = .;
	        __init_array_start = .;
	} > flatmem
	.bss : {
		. = ALIGN(0x4) ;
		__sbss = ALIGN(0x4) ;

		__bss_start = . ;
		*(.dynsbss)
		*(.sbss)
		*(.sbss.*)
		*(.scommon)
		*(.dynbss)
		*(.bss)
		*(.bss.*)
		*(COMMON)

		. = ALIGN(0x10) ;
                __bss_end = . ;
		__ebss = . ;
		__end = . ;
		end = . ;
	} > flatmem
	.junk 0 : { *(.rel*) *(.rela*) }
	/* Stabs debugging sections.    */
	.stab 0 : { *(.stab) }
	.stabstr 0 : { *(.stabstr) }
	.stab.excl 0 : { *(.stab.excl) }
	.stab.exclstr 0 : { *(.stab.exclstr) }
	.stab.index 0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment 0 : { *(.comment) }
	.debug_abbrev 0 : { *(.debug_abbrev) }
	.debug_info 0 : { *(.debug_info) }
	.debug_line 0 : { *(.debug_line) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_aranges 0 : { *(.debug_aranges) }
}

