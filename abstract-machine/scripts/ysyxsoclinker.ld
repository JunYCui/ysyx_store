ENTRY(_start)
PHDRS { text PT_LOAD; bootloader PT_LOAD; data PT_LOAD;rodata PT_LOAD; bss PT_LOAD;}

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
  .text : AT(ALIGN(LOADADDR(.bootloader)+SIZEOF(.bootloader),0x04)) {
    data_start = . ;
  *(.text*)
  } > psram : text
  .data : AT(ALIGN(LOADADDR(.text )+SIZEOF(.text),0x04)) {
    *(.data*)
    *(.sdata*)
  } > psram  : data
  .rodata : AT(ALIGN(LOADADDR(.data )+SIZEOF(.data),0x04)) {
    *(.rodata*)
    *(.srodata*)
  } > psram : rodata
  .bss : AT(ALIGN(LOADADDR(.rodata )+SIZEOF(.rodata),0x04)) {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > psram : bss
  data_size = SIZEOF(.data) + SIZEOF(.bss) + SIZEOF(.text) + SIZEOF(.rodata) ;
  data_load_start = LOADADDR(.text);
  _heap_start = ALIGN(4) ;
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}