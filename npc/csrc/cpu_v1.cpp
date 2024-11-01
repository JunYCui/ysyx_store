#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Vcpu_v1.h"
#include <verilated.h>

#define CONFIG_MSIZE 0x8000000 
#define CONFIG_MBASE 0x80000000

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;

#define PG_ALIGN __attribute((aligned(4096)))

static unsigned char pmem[CONFIG_MSIZE]PG_ALIGN ={
    0x11111111,
    

};


static inline uint32_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
  }
}

uint8_t * guest_to_host(uint32_t paddr) { return pmem + paddr - CONFIG_MBASE; }

static uint32_t pmem_read(uint32_t addr, int len) {
  uint32_t ret = host_read(guest_to_host(addr), len);
  return ret;
}

// contextp用来保存仿真的时间
VerilatedContext *contextp = new VerilatedContext;

// 构建一个名为top的仿真模型
Vcpu_v1 *top = new Vcpu_v1{contextp};


int main(int argc,char** argv )
{
    // bind all pins

    while(!contextp->gotFinish())
    {
    top->eval();
    top->inst = pmem_read(top->pc, 4);
    printf(" %x ", top->inst);
    }
}