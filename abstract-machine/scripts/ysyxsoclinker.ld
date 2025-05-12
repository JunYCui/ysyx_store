ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; data PT_LOAD;ssbl PT_LOAD ;data_extra PT_LOAD;rodata PT_LOAD;};

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  psram(rwx) :ORIGIN = 0x80000000, LENGTH = 4M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
  sdram(rwx) : ORIGIN = 0xa0000000, LENGTH = 32M
}


SECTIONS {
  . = ORIGIN(flash);
  .fsbl : {
    . = ALIGN(4);
    *(entry)
    *(.fsbl*)
    . = ALIGN(4);
  } >flash AT>flash : fsbl
  .ssbl : {
    . = ALIGN(4);
    _ssbl_start = .;
    *(.ssbl*)
    . = ALIGN(4);
  } > sram AT> flash : ssbl
  .text : {
    . = ALIGN(4);
    text_start = . ;
    *(.text*)
    . = ALIGN(4);
  } > sdram AT> flash : text
  .data : {
    . = ALIGN(4);
    *(.sdata*)
    *(.data*)
      . = ALIGN(4);
  } > sdram AT> flash : data
  .rodata : {
    *(.srodata*)
    *(.rodata*)
    . = ALIGN(4);
  } > sdram AT > flash : rodata
  .bss : {    	
    *(.bss*)
    *(.sbss*)
    *(.scommon)
    data_end = .;
  } > sdram AT> flash 
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  text_load_start = LOADADDR(.text);
  _size = data_end - text_start; 
  _heap_start = ALIGN (0x1000);
  _stack_top = ORIGIN(sram) + 0x200;
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_pointer = .;
  end = .;
  _end = .;
}