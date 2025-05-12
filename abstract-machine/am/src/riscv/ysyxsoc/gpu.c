#include <am.h>
#include <stdint.h>
#include <stdio.h>
#include <riscv/riscv.h>

#define SCREEN_W 640
#define SCREEN_H 480
#define FB_ADDR  0x21000000

uint16_t w_init;
uint16_t h_init;

void __am_gpu_init() {
  w_init = SCREEN_W;
  h_init = SCREEN_H;
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint16_t h = h_init;
  uint16_t w = w_init;
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = w, .height = h,
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl){
   int x = ctl->x;
   int y = ctl->y;
   int w = ctl->w; 
   int h = ctl->h;
   int k=0;

  uint32_t *pix = ctl->pixels;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  uint16_t sw = w_init;
    for (int i = y; i < y+h; i++) {
      for (int j = x; j < x+w; j++) {
        fb[sw*i+j] = pix[k++]; 
    }
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}