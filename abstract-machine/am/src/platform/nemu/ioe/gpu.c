#include <am.h>
#include <nemu.h>
#include <stdint.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

#define screen_weight 400
#define screen_height 300

void __am_gpu_init() {
  int i;
  int w = 400;  // TODO: get the correct width
  int h = 300;  // TODO: get the correct height
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < w * h; i ++) fb[i] = i/2;
  outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint16_t h = inl(VGACTL_ADDR)&0xffff;
  uint16_t w = inl(VGACTL_ADDR)>>16;
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = w, .height = h,
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl){
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  int x=ctl->x;
  int y=ctl->y;
  int*pix = ctl->pixels;
  int w=ctl->w;
  int h=ctl->h;
  int k=0;
  if (ctl->sync) {
    for(int i=y;i<y+h;i++)
      for(int j=x;i<x+w;j++)
        fb[i*screen_weight+j] = pix[k++];
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
