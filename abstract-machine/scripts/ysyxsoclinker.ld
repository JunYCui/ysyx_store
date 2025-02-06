ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; data PT_LOAD; ssbl PT_LOAD;data_extra PT_LOAD;rodata PT_LOAD;bss PT_LOAD;}

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
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  .text :  {
    data_start = . ;
  *(.text*)
  } > sdram AT>flash  : text
  .data :  {
    *(.data*)
    *(.sdata*)
  } > sdram AT>flash  : data
  .data.extra :  {
    *(FSymTab)
    *(.data*)
    *(.sdata*)
  } > sdram AT>flash : data_extra
  .rodata : {
    *(.rodata*)
    *(.srodata*)
  } > sdram : rodata
  .bss :  {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sdram AT>flash  : bss
  _heap_start = ORIGIN(sram);
  . = ORIGIN(sram) + LENGTH(sram);
  data_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.text) + SIZEOF(.rodata) + SIZEOF(.data.extra) ;
  data_load_start = LOADADDR(.text);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}