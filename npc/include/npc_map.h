#ifndef __NPC_MAP_H__
#define __NPC_MAP_H__
#include <npc_common.h>
uint8_t* new_space(int size);
void add_mmio_map(const char *name, paddr_t addr,
        void *space, uint32_t len);
typedef struct {
  const char *name;
  // we treat ioaddr_t as paddr_t here
  uint32_t low;
  uint32_t high;
  void *space;
} IOMap;


#endif