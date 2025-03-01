#include "npc_memory.h"
#include "npc_define.h"
#include "npc_device.h"
  uint64_t npc_time;
  extern uint8_t* pmem;
  extern uint32_t *vmem ;
  uint8_t* guest_to_host(uint32_t paddr) { return pmem + paddr - CONFIG_MBASE; }
  uint64_t get_time() ;
  void vga_update_screen();
  uint32_t screen_size();
  uint16_t height,weight;
  bool vga_flag;
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
  int paddr = addr & ~0x03u;
  int data;
  if(addr == RTC_ADDR)
  {
    data = (uint32_t)get_time();
    return data;
  }
  else if(addr == RTC_ADDR + 4)
  {
    data = (uint32_t)(get_time()>>32);
    return data;
  }
#ifdef MTRACE
  printf("Read addr 0x%x \n",paddr);
#endif 
   data = *(int*)guest_to_host(paddr);   
  return data;
}

extern "C" void npc_pmem_write(int addr, int wdata, char wmask)
{
  uint32_t pc;
  int paddr = addr ;
  int data = wdata;
  if(addr == UART_ADDR)
  {
    putc(wdata, stderr);
    return;
  }
  else if(addr >=FB_ADDR && addr <FB_ADDR + screen_size())
  {
    vmem[(addr-FB_ADDR)/4] = wdata;
    return;
  }
  else if(addr == VGA_ADDR)
  {

    height = wdata&0xffff;
    weight = wdata>>16;
    return;
  }
  else if(addr == VGA_ADDR +4)
  {
    vga_flag  = wdata;
    if(vga_flag == 1)
    {
      vga_update_screen();
      vga_flag = 0;
    }
    return;
  }
    switch (wmask)
  {
    case 1: *(uint8_t   *)guest_to_host(paddr) = data&(0x000000ff) ; break;
    case 2: *(uint16_t  *)guest_to_host(paddr) = data&(0x0000ffff) ; break;
    case 4: *(uint32_t  *)guest_to_host(paddr) = data&(0xffffffff) ; break;
    default:break; 
    svSetScope(svGetScopeFromName("TOP.ysyx_24100029"));
    GetPC(&pc);
    printf("wmask      =    %d  pc  = 0x%x \n",wmask,pc);
    assert(0);
  }
    return;
}




