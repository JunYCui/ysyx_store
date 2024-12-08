#include "npc_memory.h"
#include "npc_define.h"
#include "npc_device.h"
extern uint8_t* pmem;

uint8_t* guest_to_host(uint32_t paddr) { return pmem + paddr - CONFIG_MBASE; }
uint64_t get_time() ;

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
  uint64_t time;
  int data;
 if(paddr == RTC_ADDR + 4)
  {
    time = get_time(); 
    npc_pmem_write(RTC_ADDR,time&0xffffffff,4);
    npc_pmem_write(RTC_ADDR+4,time>>32,4);
  }
  data = *(int*)guest_to_host(paddr);  
#ifdef MTRACE
  printf("addr 0x%x:\t0x%x      \n",paddr,data);
#endif  
  return data;
}

extern "C" void npc_pmem_write(int addr, int wdata, char wmask)
{

  int paddr = addr;
  int data = wdata;
  if(addr == UART_ADDR)
  {
    printf("%c",wdata);
    return;
  }
  switch (wmask)
  {
    case 1: *(uint8_t  *)guest_to_host(paddr)  = data&(0x000000ff) ; break;
    case 2: *(uint16_t  *)guest_to_host(paddr) = data&(0x0000ffff) ; break;
    case 4: *(uint32_t  *)guest_to_host(paddr) = data&(0xffffffff) ; break;
    default: 
    printf("wmask      =    %d \n",wmask);
    assert(0);
  }
  #ifdef MTRACE
    printf("addr 0x%x:\t0x%x is written ! wmask = %d  \n",paddr,data,wmask);
  #endif
    return;
}




