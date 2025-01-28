ENTRY(_start)
PHDRS { text PT_LOAD; data PT_LOAD;bootloader PT_LOAD; }

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
  . = ORIGIN(sram);
  .text : {
  *(.text*)
  } > sram AT>flash : text
  .rodata : {
    *(.rodata*)
  } > sram AT>flash
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
  } > sram AT>flash
  data_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.text) + SIZEOF(.rodata) ;
  data_load_start = LOADADDR(.text);
  _heap_start = ALIGN(4) ;
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}