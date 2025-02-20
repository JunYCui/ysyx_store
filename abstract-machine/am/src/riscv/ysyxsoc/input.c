#include <am.h>
#include <riscv/riscv.h>
#include "stdint.h"
#define KBR_ADDR 0x10011000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint8_t code = inb(KBR_ADDR);
  kbd->keydown = (code == 0xf0)? true : false;
  kbd->keycode = (code == 0xf0)? inb(KBR_ADDR):code;
}
