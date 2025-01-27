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
   *(.text*)
  } > flash AT>flash : text
  .rodata : {
    *(.rodata*)
  } > flash AT>flash
  .data : {
    data_start = . ;
    *(.data*)
    *(.sdata*)
  } > psram AT>flash : data
  .bss : {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > psram AT>flash : bss
  data_size = SIZEOF(.data) + SIZEOF(.bss);
  data_load_start = LOADADDR(.data);
  _heap_start = . ;
  . = ORIGIN(psram) + LENGTH(psram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}