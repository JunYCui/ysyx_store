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
  _stack_top = ORIGIN(psram);
  _stack_pointer = . + LENGTH(psram);
  end = .;
  _end = .;
  _heap_start = ALIGN(0x1000);
}