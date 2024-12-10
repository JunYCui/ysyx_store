#include <npc_common.h>
#include <npc_memory.h>
#include <npc_device.h>
uint8_t* new_space(int size) ;

#define SCREEN_W 400
#define SCREEN_H 300

static uint32_t screen_width() {
  return SCREEN_W;
}

static uint32_t screen_height() {
  return SCREEN_H;
}

uint32_t screen_size() {
  return screen_width() * screen_height() * sizeof(uint32_t);
}

#include <SDL2/SDL.h>

static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

uint32_t *vmem = NULL;


void init_screen() {
  SDL_Window *window = NULL;
  char title[128];
  sprintf(title, "NPC-NEMU");
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(
      SCREEN_W * 2,
      SCREEN_H * 2,
      0, &window, &renderer);
  SDL_SetWindowTitle(window, title);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STATIC, SCREEN_W, SCREEN_H);
  SDL_RenderPresent(renderer);

  vmem = (uint32_t*)new_space(screen_size());
  memset(vmem,0,screen_size());
}

inline void update_screen() {
  SDL_UpdateTexture(texture, NULL, vmem, SCREEN_W * sizeof(uint32_t));
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void vga_update_screen() {
  update_screen();
}
