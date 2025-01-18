ENTRY(_start)
PHDRS { text PT_LOAD; data PT_LOAD; }

MEMORY{
  mrom(rx) : ORIGIN = 0x20000000, LENGTH = 4K
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}


SECTIONS {
  . = ORIGIN(mrom);
  .text : {
   *(entry)
   *(.text*)
  } > mrom AT>mrom : text
  .rodata : {
    *(.rodata*)
  } > mrom AT>mrom
  .data : {
    data_start = . ;
    *(.data*)
    *(.sdata*)
  } > sram AT>mrom : data
  .bss : {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sram AT>mrom
  data_size = SIZEOF(.data);
  data_load_start = LOADADDR(.data);
  . = ORIGIN(sram)+LENGTH(sram);
  _stack_top = .;
  _stack_pointer = .;
  end = .;
  _end = .;
  _heap_start = ORIGIN(sram);
}