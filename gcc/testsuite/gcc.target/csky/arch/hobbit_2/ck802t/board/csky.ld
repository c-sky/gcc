/*
 * 
 */

ENTRY(__start)

MEMORY
{
        MEM0   : ORIGIN = 0x0        , LENGTH = 0x1FF    /* ROM  512B*/
        MEM1   : ORIGIN = 0x10014800 , LENGTH = 0x3F7FF  /* E-FLASH 80KB*/
        MEM2   : ORIGIN = 0x60000000 , LENGTH = 0xC000    /* on-chip SRAM 4KB*/
        MEM3   : ORIGIN = 0x60010000 , LENGTH = 0x4000    /* on-chip SRAM 4KB*/
        MEM4   : ORIGIN = 0x6001c000 , LENGTH = 0x200    /* on-chip SRAM 4KB*/
        MEM5   : ORIGIN = 0x6001c200 , LENGTH = 0x200    /* on-chip SRAM 4KB*/


}

PROVIDE (__heap_start = 0x60014000 - 0x1000 - 0x8);
PROVIDE (__heap_end =   0x60014000 - 0x8);

PROVIDE (__fstack =  0x60014000 - 0x1000 - 0x8);
PROVIDE (__stack =   0x60014000 - 0x1000 - 0x8);

REGION_ALIAS("REGION_TEXT",   MEM2);
REGION_ALIAS("REGION_RODATA", MEM2);
REGION_ALIAS("REGION_DATA",   MEM3);
REGION_ALIAS("REGION_BSS",    MEM3);

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
        *(.rodata.str1.4)
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
            *(.data)
            *(.tdata)
            *(.tdata.*)
            *(.gcc_exc);
            *(.gcc_except_table)   
            . = ALIGN(4) ;
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
