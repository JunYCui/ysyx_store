ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; data PT_LOAD;data_extra PT_LOAD ; ssbl PT_LOAD ; rodata PT_LOAD; bss PT_LOAD;};

MEMORY{
  flash(rx) : ORIGIN = 0x30000000, LENGTH = 16M
  sdram(rwx) : ORIGIN = 0xa0000000, LENGTH = 32M
  psram(rwx) :ORIGIN = 0x80000000, LENGTH = 4M
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}


SECTIONS {
  . = ORIGIN(flash);
  .fsbl : {
    *(entry)
    *(.fsbl*)
  } >flash AT>flash : fsbl
  .ssbl :  {
    _ssbl_start = .;
    *(.ssbl*)
  } > sram AT>flash : ssbl
  .text :  {
    text_start = . ;
    *(.text*)
  } > sdram AT>flash : text
  .rodata :  {
    *(.srodata*)
    *(.rodata*)
    rodata_end = .;
  } > sdram AT>flash : rodata
  .data.extra : {
    data_start = .;
    *(FSymTab*)
  } > sdram AT>flash : data_extra
  .data :  {
    *(.data*)
    *(.sdata*)
  } > sdram AT>flash : data
  .bss : {    	
    *(.bss*)
    *(.sbss*)
    *(.scommon)
    bss_end = .;
  } > sdram AT>flash : bss 
  .rela : {
    *(.rela*)
  } > sdram AT>flash
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  text_load_start = LOADADDR(.text);
  data_load_start = LOADADDR(.data.extra);
  _size2 = bss_end - data_start ;
  _size1 = rodata_end - text_start; 
  _heap_start = ORIGIN(sram);
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}