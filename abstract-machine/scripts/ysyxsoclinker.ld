ENTRY(_start)
PHDRS { text PT_LOAD; data PT_LOAD;}

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
  psram(rwx) :ORIGIN = 0x80000000, LENGTH = 4M
}


SECTIONS {
  . = ORIGIN(flash);
  .bootloader : {
    *(entry)
    *(.text.memcpy)
    *(.text.uart_init)
    *(.text._trm_init)
  } >flash AT>flash 
  . = ORIGIN(psram);
  .text : {
    data_start = . ;
  *(.text*)
  } > psram AT>flash : text
  .data : {
    *(.data)
    *(.sdata)
  } > psram AT>flash : data
  .rodata : {
    *(.rodata*)
    *(.srodata*)
  } > psram AT>flash 
  .bss : {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > psram AT>flash
  .rela : {
    *(.rela*)
  } > flash AT> flash 
  data_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.text) + SIZEOF(.rodata) ;
  data_load_start = LOADADDR(.text);
  _heap_start = ORIGIN(sram) ;
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}