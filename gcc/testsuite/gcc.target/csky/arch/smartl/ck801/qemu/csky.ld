/*
 * 
 */

ENTRY(__start)

MEMORY
{
	DATA   : ORIGIN = 0x20000000 , LENGTH = 0x01000000  /* 16M */
	INST   : ORIGIN = 0x60000000 , LENGTH = 0x01000000  /* 16M*/
	EEPROM : ORIGIN = 0x00000000 , LENGTH = 0x01000000  /* 16M*/
}

PROVIDE (__stack =  0x01000000 - 0x8);
PROVIDE (__heap_start = 0x00000100);
PROVIDE (__heap_end = 0x00900000);


REGION_ALIAS("REGION_TEXT",   INST);
REGION_ALIAS("REGION_RODATA", DATA);
REGION_ALIAS("REGION_DATA",   DATA);
REGION_ALIAS("REGION_BSS",    DATA);

SECTIONS
{
	.text : {
        _start_text = .;
            *(.text)
            *(.text*)
            *(.text.*)
            /*
             * The instruction space will be in SPM
             * 16KBytes
             */
            __ckcpu_ispm = .;
            *(.spmtext)
            __ckcpu_ispm_end = .;
            . = ALIGN(4) ;
        _end_text = .;
    } > REGION_TEXT

    .rodata : {
        *(.rodata)
        *(.rodata.*)
        *(.rodata.cst4)
        *(.rodata.cst8)
        *(.rdata)
        *(.rdata*)
        *(.rdata1)
        *(.rdata.*)
    } > REGION_RODATA

    .data : {
        _start_data = .;
            *(.shdata)
            *(.sdata)
            *(.sdata.*)
            *(.tdata)
            *(.tdata.*)
            *(.data)
            *(.gcc_exc);
            *(.gcc_except_table)   
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
            *(.data*)
            *(.data.*)
            /*
             * The Data space will be in SPM
             * 8KBytes
             */
            __ckcpu_dspm = .;
            *(.spmdata)
            __ckcpu_dspm_end = .;
        _end_data = .;
     } > REGION_DATA

     .bss : {
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
    } > REGION_BSS
	
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
