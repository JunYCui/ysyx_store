ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; data PT_LOAD;data_extra PT_LOAD ; ssbl PT_LOAD ; rodata PT_LOAD; bss PT_LOAD;};

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
  .ssbl : AT(ALIGN(LOADADDR(.fsbl )+SIZEOF(.fsbl),2)) {
    _ssbl_start = .;
    *(.ssbl*)
  } > sram : ssbl
  .text : AT(ALIGN(LOADADDR(.ssbl )+SIZEOF(.ssbl),2)) {
    text_start = . ;
    *(.text*)
  } > psram : text
  .rodata : AT(ALIGN(LOADADDR(.text )+SIZEOF(.text),2)) {
    *(.rodata*)
    *(.srodata*)
    *(fill*)
  } > psram : rodata
  .data : AT(ALIGN(LOADADDR(.rodata )+SIZEOF(.rodata)+1,2)) {
    *(.sdata*)
    *(.data*)
  } > psram : data
  .data.extra : AT(ALIGN(LOADADDR(.data )+SIZEOF(.data),2)) {
    *(.data*)
    *(.sdata*)
    *(FSymTab)
  } > psram : data_extra
  .bss : AT(ALIGN(LOADADDR(.data.extra )+SIZEOF(.data.extra),2)) {    	
    *(.bss*)
    *(.sbss*)
    *(.scommon)
    bss_end = .;
  } > psram : bss 
  .rela : AT(ALIGN(LOADADDR(.data.extra )+SIZEOF(.data.extra),0x4))  {
    *(.rela*)
  } > psram
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  text_load_start = LOADADDR(.text);
  _size = bss_end - text_start; 
  _heap_start = ORIGIN(sram);
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}