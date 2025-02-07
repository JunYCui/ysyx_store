ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; ssbl PT_LOAD ; data PT_LOAD;  rodata PT_LOAD; };

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  sdram(rwx) : ORIGIN = 0xa0000000, LENGTH = 32M
  psram(rwx) :ORIGIN = 0x80000000, LENGTH = 4M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}


SECTIONS {
  . = ORIGIN(flash);
  .fsbl : {
    *(entry)
    *(.fsbl*)
  } >flash AT>flash : fsbl
  .ssbl :  {
    _ssbl_start = .;
    *(.ssbl*)
  } > sram AT>flash : ssbl
  .text :  {
    text_start = . ;
    *(.text*)
  } > sdram AT>flash : text
  .data.extra : {
    /* section information for finsh shell */
    __fsymtab_start = .;
    KEEP(*(FSymTab))
    __fsymtab_end = .;
    . = ALIGN(8);
    __vsymtab_start = .;
    KEEP(*(VSymTab))
    __vsymtab_end = .;
    . = ALIGN(8);

    /* section information for initial. */
    . = ALIGN(8);
    __rt_init_start = .;
    KEEP(*(SORT(.rti_fn*)))
    __rt_init_end = .;
    . = ALIGN(8);

    __rt_utest_tc_tab_start = .;
    KEEP(*(UtestTcTab))
    __rt_utest_tc_tab_end = .;

    . = ALIGN(8);
    __am_apps_data_start = .;
    *(__am_apps.data*)
    *(__am_apps.sdata*)
    __am_apps_data_end = .;
    . = ALIGN(8);
  } >sdram AT>flash
  .rodata :  {
    *(.srodata*)
    *(.rodata*)
    rodata_end = .;
  } > sdram AT>flash : rodata
    data_start = .;
  .data :  {
    *(.data*)
    *(.sdata*)
  } > sdram AT>flash : data
  .bss.extra : {
    . = ALIGN(8);
    __am_apps_bss_start = .;
    *(__am_apps.bss*)
    *(__am_apps.sbss*)
    *(__am_apps.scommon*)
    __am_apps_bss_end = .;
    . = ALIGN(8);
  } >sdram AT>flash
  .bss : {    	
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sdram AT>flash
  .rela : {
    *(.rela*)
  } 
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  text_load_start = LOADADDR(.text);
  data_load_start = LOADADDR(.data);
  _size2 = SIZEOF(.data);
  _size1 = rodata_end - text_start; 
  _heap_start = ORIGIN(sram);
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}