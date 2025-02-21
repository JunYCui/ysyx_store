#include <am.h>
#include <riscv/riscv.h>
#include "stdint.h"
#define KBR_ADDR 0x10011000
uint8_t reg[10];
uint8_t ex_reg[10];
uint8_t table[] ={
  0x00,
  0x76, 0x05, 0x06, 0x04, 0x0C, 0x03, 0x0B, 0x83, 0x0A, 0x01, 0x09, 0x78, 0x07, // ESCAPE, F1-F12
  0x0E, 0x16, 0x1E, 0x26, 0x25, 0x2E, 0x36, 0x3D, 0x3E, 0x46, 0x45, 0x4E, 0x55, 0x66, // GRAVE, 1-0, MINUS, EQUALS, BACKSPACE
  0x0D, 0x15, 0x1D, 0x24, 0x2D, 0x2C, 0x35, 0x3C, 0x43, 0x44, 0x4D, 0x54, 0x5B, 0x5D, // TAB, Q-P, LEFTBRACKET, RIGHTBRACKET, BACKSLASH
  0x58, 0x1C, 0x1B, 0x23, 0x2B, 0x34, 0x33, 0x3B, 0x42, 0x4B, 0x4C, 0x52, 0x5A, // CAPSLOCK, A-L, SEMICOLON, APOSTROPHE, RETURN
  0x12, 0x1A, 0x22, 0x21, 0x2A, 0x32, 0x31, 0x3A, 0x41, 0x49, 0x4A, 0x59, // LSHIFT, Z-M, COMMA, PERIOD, SLASH, RSHIFT
  0x14, 0x00, 0x11, 0x29//
};
int search_id(int code){
  uint8_t id;
  for(id =0;id<sizeof(table);id++)
  {
    if(table[id] == code)
        return id;
  }
  return 0;
}

int ex_search_id(int code){
  switch (code)
  {
  case 0x1f: return 68;// APPS
  case 0x11: return 71;// RALT
  case 0x14: return 72;// RCTRL
  case 0x75: return 73;// UP
  case 0x72: return 74;// DOWN
  case 0x6B: return 75;// LEFT
  case 0x74: return 76;// RIGHT
  case 0x70: return 77;// INSERT
  case 0x71: return 78;// DELETE
  case 0x6C: return 79;// HOME
  case 0x69: return 80;// END
  case 0x7D: return 81;// PAGEUP
  case 0x7A: return 82;// PAGEDOWN
  default: return 0;
  }
}

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint8_t code = inb(KBR_ADDR);
  static uint8_t count;
  static uint8_t ex_count;
  int i;
  if(code == 0xf0){
    code = inb(KBR_ADDR);
    kbd->keydown = false;
    kbd->keycode = search_id(code);
    for(i=0;i<count;i++){
      if(code == reg[i])
          break;
    }
    for(int j=i+1;j<count;j++){
        reg[j-1] = reg[j];
    }
    count --;
  }
  else if(code == 0xe0)
  {
    code = inb(KBR_ADDR);
    if(code == 0xf0){
      code = inb(KBR_ADDR);
      kbd->keydown = false;
      kbd->keycode = ex_search_id(code);
      for(i=0;i<ex_count;i++){
        if(code == ex_reg[i])
            break;
      }
      for(int j=i+1;j<ex_count;j++){
          ex_reg[j-1] = ex_reg[j];
      }
      ex_count --;
    }
    else {
      for(i=0;i<ex_count;i++){
        if(code == ex_reg[i])
            break;
      }
    if(i == ex_count){
      ex_reg[ex_count++] = code;
      kbd->keycode = ex_search_id(code);
      kbd->keydown = true;
    }
    }
  }
  else if(code !=0){
    for(i=0;i<count;i++){
        if(code == reg[i])
          break;
    }
    if(i == count){
      reg[count++] = code;
      kbd->keycode = search_id(code);
      kbd->keydown = true;
    }
    else 
      kbd->keycode = AM_KEY_NONE;
  }
  else 
    kbd->keycode = AM_KEY_NONE;
}
