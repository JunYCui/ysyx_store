ENTRY(_start)
PHDRS { text PT_LOAD; fsbl PT_LOAD; ssbl PT_LOAD ; data PT_LOAD;  rodata PT_LOAD; extra PT_LOAD; };

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
  .data :  {
    data_start = .;
    *(.data*)
    *(.sdata*)
  } > sdram AT>flash : data
  .extra : {
    *(.bss.extra)
    *(.data.extra)
  } > sdram AT>flash : extra
  .bss : {    	
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sdram AT>flash
  .rela : {
    *(.rela*)
  } 
  _ssbl_loadstart = LOADADDR(.ssbl);
  _ssbl_size = SIZEOF(.ssbl);
  text_load_start = LOADADDR(.text);
  data_load_start = LOADADDR(.data);
  _size2 = SIZEOF(.data);
  _size1 = rodata_end - text_start; 
  _heap_start = ORIGIN(sram);
  . = ORIGIN(sram) + LENGTH(sram);
  _stack_top = . ;
  _stack_pointer = .;
  end = .;
  _end = .;
}