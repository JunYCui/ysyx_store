#include "stdint.h"
#define SCREEN_W 640
#define SCREEN_H 480
#define FB_ADDR  0x21000000
void main(void){
   int16_t w_init = SCREEN_W;
   int16_t h_init = SCREEN_H;
   int i;
   uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
   while(1)
   {
   for (i = 0; i < w_init * h_init; i ++) if(i<240*640)
        fb[i] = 255;
   else 
        fb[i] = 255*255;
   }
}