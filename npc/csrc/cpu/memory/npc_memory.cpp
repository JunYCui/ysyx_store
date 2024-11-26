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
  int paddr = addr;
  int data = *(int*)guest_to_host(paddr);  
  //printf("addr 0x%x:\t0x%x      \n",paddr,data);
  return data;
}

extern "C" void npc_pmem_write(int addr, int wdata, char wmask)
{

  int paddr = addr;
  int data;
  switch (wmask)
  {
    case 1: data = wdata & (0xff); break;
    case 2: data = wdata & (0xffff); break;
    case 4: data = wdata & (0xffffffff); break;
    default: 
    printf("wmask      =    %d \n",wmask);
    assert(0);
  }
  printf("addr 0x%x:\t0x%x is written !   \n",paddr,data);
  *(int  *)guest_to_host(paddr) = data;
  return;
}




