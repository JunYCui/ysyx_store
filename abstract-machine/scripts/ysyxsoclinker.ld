ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; ssbl PT_LOAD ; data PT_LOAD;  rodata PT_LOAD; bss PT_LOAD; };

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  sdram(rwx) : ORIGIN = 0xa0000000, LENGTH = 32M
  psram(rwx) :ORIGIN = 0x80000000, LENGTH = 4M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}


SECTIONS {
  .fsbl : {
    *(entry)
    *(.fsbl*)
    . = ALIGN(8);
  } >flash AT>flash : fsbl
  .ssbl :  {
    _ssbl_start = .;
    *(.ssbl*)
    . = ALIGN(8);
  } > sram AT>flash : ssbl
  .text :  {
    text_start = . ;
    *(.text*)
    . = ALIGN(8);
  } > sdram AT>flash : text
  .rodata :  {
    *(.srodata*)
    *(.rodata*)
    . = ALIGN(8);
  } > sdram AT>flash : rodata
  .data :  {
    *(.data*)
    *(.sdata*)
    data_end = . ;
  } > sdram AT>flash : data
  .bss : {    	
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sdram AT>flash : bss
  .rela : {
    *(.rela*)
  } > sdram AT>flash
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  text_load_start = LOADADDR(.text);
  _size1 = data_end - text_start; 
  _heap_start = ORIGIN(psram) ;
  _stack_top =  ORIGIN(psram) + 0x300000 ;
  . = ORIGIN(psram) + LENGTH(psram);
  _stack_pointer = .;
  end = .;
  _end = .;
}