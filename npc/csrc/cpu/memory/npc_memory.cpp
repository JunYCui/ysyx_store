#include "npc_memory.h"

extern uint8_t* pmem;

uint8_t* guest_to_host(uint32_t paddr) { return pmem + paddr - CONFIG_MBASE; }


static inline uint32_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    default: return 0;
  }
}

static uint32_t pmem_read(uint32_t addr, int len) {
  uint32_t ret = host_read(guest_to_host(addr), len);
  return ret;
}


word_t paddr_read(paddr_t addr, int len) {
  if (likely(in_pmem(addr))) return pmem_read(addr, len);
  printf("******* 0x%x is out of boudary ******** \n",addr);
  return 0;
}

extern "C" int npc_pmem_read(int addr)
{
  int paddr = addr&(~0x03u);
  
  return *(int*)guest_to_host(paddr);
}

extern "C" void npc_pmem_write(int addr, int wdata, char wmask)
{

  int paddr = addr&(~0x03u);
  printf("  addr0x%x: 0x%x is written!    \n",paddr,wdata);
  switch (wmask)
  {
    case 1: *(int  *)guest_to_host(paddr) = wdata & (0xff); return;
    case 2: *(int  *)guest_to_host(paddr) = wdata & (0xffff); return;
    case 4: *(int  *)guest_to_host(paddr) = wdata & (0xffffffff); return;
  }

}




