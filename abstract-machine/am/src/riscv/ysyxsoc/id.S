.align 3
.globl id_display
id_display:
  addi sp,sp,-12
  csrr a0, mvendorid
  csrr a1, marchid
  sw   ra, 8(sp)
  jal display