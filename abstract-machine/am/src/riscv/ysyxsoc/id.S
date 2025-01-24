.align 3
.globl id_display
id_display:
  addi sp,sp,-12
  sw   ra, 8(sp)
  csrr a0, mvendorid
  csrr a1, marchid
  jal display
  lw   ra, 8(sp)
  ret