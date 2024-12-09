#include <am.h>
#include <nemu.h>
#include <stdint.h>
#include <stdio.h>
#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint32_t wh = inl(VGACTL_ADDR);
  uint16_t h = wh&0xffff;
  uint16_t w = wh>>16;
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
  if (!ctl->sync && (w == 0 || h == 0)) return;
  uint32_t *pix = ctl->pixels;
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  uint32_t wh = inl(VGACTL_ADDR);
  uint16_t sw = wh>>16;
    for (int i = y; i < y+h; i++) {
      for (int j = x; j < x+w; j++) {
        fb[sw*i+j] = pix[k++]; 
    }
  }
    if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
