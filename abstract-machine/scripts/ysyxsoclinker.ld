ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; data PT_LOAD; ssbl PT_LOAD;}

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
  .ssbl : AT(ALIGN(LOADADDR(.fsbl )+SIZEOF(.fsbl),0x04)) {
    _ssbl_start = .;
    *(.ssbl*)
  } > sram : ssbl
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  .text : AT(ALIGN(LOADADDR(.ssbl )+SIZEOF(.ssbl),0x04)) {
    data_start = . ;
  *(.text*)
  } > psram : text
  .data : AT(ALIGN(LOADADDR(.text )+SIZEOF(.text),0x04)) {
    *(.data*)
    *(.sdata*)
  } > psram : data
  .data.extra : AT(ALIGN(LOADADDR(.data )+SIZEOF(.data),0x04)) {
    *(FSymTab)
    *(.data*)
    *(.sdata*)
  } > psram 
  .rodata : AT(ALIGN(LOADADDR(.data.extra )+SIZEOF(.data.extra),0x04)) {
    *(.rodata*)
    *(.srodata*)
  } > psram 
  .bss : AT(ALIGN(LOADADDR(.rodata )+SIZEOF(.rodata),0x04)) {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > psram 
  _heap_start = ORIGIN(sdram);
  . = ORIGIN(sdram) + LENGTH(sdram);
  data_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.text) + SIZEOF(.rodata) + SIZEOF(.data.extra) ;
  data_load_start = LOADADDR(.text);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}