ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; data PT_LOAD;ssbl PT_LOAD ;data_extra PT_LOAD;};

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
<<<<<<< HEAD
  } > sram : ssbl
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  .text : AT(ALIGN(LOADADDR(.ssbl )+SIZEOF(.ssbl),0x04)) {
    data_start = . ;
  *(.text*)
  } > psram : text
  .rodata : AT(ALIGN(LOADADDR(.text )+SIZEOF(.text),0x04)) {
    *(.rodata*)
    *(.srodata*)
  } > psram : rodata
  .data.extra : AT(ALIGN(LOADADDR(.rodata )+SIZEOF(.rodata),0x04)) {
    *(FSymTab)
    *(.data*)
=======
  } > sram AT> flash : ssbl
  .text : {
    text_start = . ;
    *(.text*)
    . = ALIGN(8);
  } > sdram AT> flash : text
  .data : {
>>>>>>> SDRAM
    *(.sdata*)
    *(.data*)
<<<<<<< HEAD
    *(.sdata*)
  } > psram : data
  .bss : AT(ALIGN(LOADADDR(.rodata )+SIZEOF(.rodata),0x04)) {    	
    _bss_start = .;
=======
      . = ALIGN(8);
  } > sdram AT> flash : data
  .bss : {    	
>>>>>>> SDRAM
    *(.bss*)
    *(.sbss*)
    *(.scommon)
      . = ALIGN(8);
  } > sdram AT> flash 
  .rodata : {
    *(.srodata*)
    *(.rodata*)
    . = ALIGN(8);
    data_end = .;
  } > sdram AT > flash 
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  text_load_start = LOADADDR(.text);
  _size = data_end - text_start; 
  _heap_start = ALIGN (0x1000);
  _stack_top = ORIGIN(psram);
  . = ORIGIN(psram) + LENGTH(psram);
  _stack_pointer = .;
  end = .;
  _end = .;
}