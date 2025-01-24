.section entry, "ax"
.globl _start
.type _start, @function

_start:
  mv s0, zero
  la sp, _stack_pointer
  csrr a0, mvendorid
  csrr a1, marchid
  jal display
  jal _trm_init
