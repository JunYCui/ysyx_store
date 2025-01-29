ENTRY(_start)
PHDRS { text PT_LOAD; data PT_LOAD;bootloader PT_LOAD;rodata PT_LOAD; }

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
  psram(rwx) :ORIGIN = 0x80000000, LENGTH = 4M
}


SECTIONS {
  . = ORIGIN(flash);
  .bootloader : {
    *(entry)
    *(.text.uart_init)
    *(.text.memcpy)
    *(.text._trm_init)
  } >flash AT>flash : bootloader
  . = ORIGIN(psram);
  .text : {
    data_start = . ;
  *(.text*)
  } > psram AT>flash : text
  .data : {
    *(.data*)
    *(.sdata*)
  } > psram AT>flash : data
  .rodata : {
    *(.rodata*)
  } > psram AT>flash : rodata
  .bss : {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > psram AT>flash
  data_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.text) + SIZEOF(.rodata) ;
  data_load_start = LOADADDR(.text);
  _heap_start = ALIGN(4) ;
  . = ORIGIN(psram) + LENGTH(psram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}