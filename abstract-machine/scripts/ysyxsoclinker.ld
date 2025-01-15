ENTRY(_start)

MEMORY{
  mrom(rx) : ORIGIN = 0x20000000, LENGTH = 4K
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}


SECTIONS {
  . = ORIGIN(mrom);
  .text : {
   *(entry)
   *(.text*)
  } > mrom AT>mrom
  .rodata : {
    *(.rodata*)
  } > mrom AT>mrom
  .data : {
    *(.data)
  } > sram AT>mrom
  data_size = SIZEOF(.data) ;
  data_load_start = LOADADDR(.data);
  .bss : {    	
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > mrom AT>mrom
  _stack_top = ORIGIN(sram)+LENGTH(sram);
  _stack_pointer =ORIGIN(sram)+LENGTH(sram);
  end = .;
  _end = .;
  _heap_start = ORIGIN(sram);
}