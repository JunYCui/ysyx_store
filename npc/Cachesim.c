#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"

#define CONFIG_FLASH_BASE 0x30000000
#define CONFIG_FLASH_SIZE 0x1000000
#define CONFIG_SDRAM_BASE 0xa0000000
#define CONFIG_SDRAM_SIZE 0x10000000

#define CACHE_INDEX_WIDTH 3
#define CACHE_OFFSET_WIDTH 2

static inline bool in_flash(uint32_t addr) {
    return addr - CONFIG_FLASH_BASE < CONFIG_FLASH_SIZE;
}

static inline bool in_sdram(uint32_t addr){
    return addr - CONFIG_SDRAM_BASE < CONFIG_SDRAM_SIZE;
  }

struct cache {
  uint8_t valid:1;
  uint32_t tag:32-CACHE_INDEX_WIDTH-CACHE_OFFSET_WIDTH;
}icache[2^CACHE_INDEX_WIDTH];

uint64_t flash_hit; 
uint64_t flash_miss; 
uint64_t sdram_hit; 
uint64_t sdram_miss; 
void Cache_decode(uint32_t pc)
{
  uint8_t index = (pc >> 2) & 7;
  uint32_t tag = pc >> 5;
  if(in_flash(pc))
  {
    if(icache[index].valid && icache[index].tag == tag)
    {
      flash_hit++;
    }
    else {
      icache[index].valid = 1;
      icache[index].tag = tag;
      flash_miss++;
    }
  }
  else if(in_sdram(pc))
  {
    if(icache[index].valid && icache[index].tag == tag)
    {
      sdram_hit++;
    }
    else {
      icache[index].valid = 1;
      icache[index].tag = tag;
      sdram_miss++;
    }
  }
  else
    return;
}
int main(void)
{
    return;
}