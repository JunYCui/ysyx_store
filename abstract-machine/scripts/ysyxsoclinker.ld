ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; data PT_LOAD;ssbl PT_LOAD ; rodata PT_LOAD;bss PT_LOAD;data_extra PT_LOAD;};

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
  .ssbl : {
    _ssbl_start = .;
    *(.ssbl*)
  } > sram AT> flash : ssbl
  .text : {
    text_start = . ;
    *(.text*)
    . = ALIGN(8);
  } > sdram AT> flash : text
  .data : {
    *(.sdata*)
    *(.data*)
    data_end = .;
  } > sdram AT> flash : data
  .rodata : {
    *(.srodata*)
    *(.rodata*)
    . = ALIGN(8);
  } > sdram AT > flash : rodata
  .bss : {    	
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sdram AT> flash : bss
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  text_load_start = LOADADDR(.text);
  _size = data_end - text_start; 
  _heap_start = ALIGN (0x1000);
  _end = .;
  _stack_top = ORIGIN(psram);
  . = ORIGIN(psram) + LENGTH(psram);
  _stack_pointer = .;
  end = .;
}