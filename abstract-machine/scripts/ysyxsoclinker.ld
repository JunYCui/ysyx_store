ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; data PT_LOAD;rodata PT_LOAD; bss PT_LOAD;data_extra PT_LOAD ; ssbl PT_LOAD;}

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  psram(rwx) :ORIGIN = 0x80000000, LENGTH = 4M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
  sdram(rwx) : ORIGIN = 0xa0000000, LENGTH = 32M
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
  } > sdram : text
  .rodata : AT(ALIGN(LOADADDR(.text )+SIZEOF(.text),0x04)) {
    *(.rodata*)
    *(.srodata*)
  } > sdram : rodata
  .data.extra : AT(ALIGN(LOADADDR(.rodata )+SIZEOF(.rodata),0x04)) {
    *(FSymTab)
    *(.data*)
    *(.sdata*)
  } > sdram : data_extra
  .data : AT(ALIGN(LOADADDR(.data.extra )+SIZEOF(.data.extra),0x04)) {
    *(.data*)
    *(.sdata*)
  } > sdram : data
  .bss : AT(ALIGN(LOADADDR(.data )+SIZEOF(.data),0x04)) {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sdram : bss
  data_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.text) + SIZEOF(.rodata) + SIZEOF(.data.extra) ;
  data_load_start = LOADADDR(.text);
  _heap_start = ORIGIN(sram);
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}