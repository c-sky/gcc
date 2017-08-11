/*
 * ckcore.ld  -- The ckcore linking script file.
 */

ENTRY (__start)

MEMORY
{
	ISRAM : ORIGIN = 0x88000000, LENGTH = 0x800000
}

PROVIDE (__heap_start = 0x88200000);
PROVIDE (__heap_end = 0x882f0000);

PROVIDE (__stack = 0x887ffff8);

SECTIONS {
	.text : {
		. = ALIGN(0x4) ;
		__stext = . ;

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
	} > ISRAM
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
	} > ISRAM
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
		*(.data.*)
		*(.gnu.linkonce.d*)
		*(.data1)
		*(.eh_frame)
		*(.gcc_except_table)
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
	} > ISRAM
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
		__ebss = . ;
		__end = . ;
		end = . ;
	} > ISRAM

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

