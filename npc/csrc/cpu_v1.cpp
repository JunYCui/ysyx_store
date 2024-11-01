#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Vswitch.h"
#include <verilated.h>

#define CONFIG_MSIZE 0x8000000 
#define CONFIG_MBASE 0x80000000

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;

static unsigned char pmem[CONFIG_MSIZE] ={
    0x11


};

uint8_t * guest_to_host(uint32_t paddr) { return pmem + paddr - CONFIG_MBASE; }

static uint32_t pmem_read(uint32_t addr) {
  uint32_t ret = *guest_to_host(addr);
  return ret;
}


void nvboard_bind_all_pins(TOP_NAME* top);

int main(int argc,char** argv )
{
    // bind all pins
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    while(1)
    {
    dut.eval();
    nvboard_update();
    }
    nvboard_quit();
}