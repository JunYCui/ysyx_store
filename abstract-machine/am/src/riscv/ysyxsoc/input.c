#include <am.h>
#include <riscv/riscv.h>
#include "stdint.h"
#define KBR_ADDR 0x10011000
uint8_t reg[10];
void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint8_t code = inb(KBR_ADDR);
  static uint8_t count;
  int i;
  if(code == 0xf0){
    code = inb(KBR_ADDR);
    kbd->keydown = false;
    kbd->keycode = code;
    for(i=0;i<count;i++){
      if(code == reg[i])
        break;
    }
    for(int j=i+1;j<count;j++){
        reg[j-1] = reg[j];
    }
    count --;
  }
  else if(code !=0){
    for(i=0;i<count;i++){
        if(code == reg[i])
          break;
    }
    if(i == count){
      reg[count++] = code;
      kbd->keycode = code;
      kbd->keydown = true;
    }
    else 
      kbd->keycode = AM_KEY_NONE;
  }
  else 
    kbd->keycode = AM_KEY_NONE;
}
