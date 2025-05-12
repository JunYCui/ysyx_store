#include <npc_map.h>

#define NR_MAP 16

static IOMap maps[NR_MAP] = {};
static int nr_map = 0;

/* device interface */
void add_mmio_map(const char *name, paddr_t addr, void *space, uint32_t len) {
  assert(nr_map < NR_MAP);
  paddr_t left = addr, right = addr + len - 1;
  maps[nr_map] = (IOMap){ .name = name, .low = addr, .high = addr + len - 1,
    .space = space, };

  nr_map ++;
}
