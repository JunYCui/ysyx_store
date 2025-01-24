.align 3
.globl id_display
id_display:
  csrr a0, mvendorid
  csrr a1, marchid
  jal display