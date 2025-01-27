ENTRY(_start)
PHDRS { text PT_LOAD; data PT_LOAD; bss PT_LOAD; }

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
  psram(rwx) :ORIGIN = 0x80000000, LENGTH = 4M
}


SECTIONS {
  . = ORIGIN(flash);
  .text : {
    *(entry)     
    data_start = . ;
   *(.text*)
  } > sram AT>flash : text
  .rodata : {
    *(.rodata*)
  } > sram AT>flash
  .data : {
    *(.data*)
    *(.sdata*)
  } > psram AT>flash : data
  .bss : {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > psram AT>flash : bss
  data_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.text) + SIZEOF(.rodata) ;
  data_load_start = LOADADDR(.text);
  _heap_start = ALIGN(4) ;
  . = ORIGIN(psram) + LENGTH(psram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}