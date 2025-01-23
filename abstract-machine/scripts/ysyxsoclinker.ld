ENTRY(_start)
PHDRS { text PT_LOAD; data PT_LOAD; bss PT_LOAD; }

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
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
  } > sram AT>flash : data
  .bss : {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sram AT>flash : bss
  data_size = SIZEOF(.data) + SIZEOF(.bss);
  data_load_start = LOADADDR(.data);
  . = ORIGIN(sram)+LENGTH(sram);
  _stack_top = .;
  _stack_pointer = .;
  end = .;
  _end = .;
  _heap_start = ORIGIN(sram);
}