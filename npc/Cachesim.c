#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "errno.h"
#include <string.h>

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
  uint32_t tag:32;
}icache[2^CACHE_INDEX_WIDTH];

uint32_t flash_hit = 0; 
uint32_t flash_miss = 0; 
uint32_t sdram_hit = 0; 
uint32_t sdram_miss = 0; 
void Cache_decode(uint32_t pc)
{
  uint8_t index = (pc >> 2) & 7;
  uint32_t tag = pc;
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
// 解析单行内容
int parse_line(const char *line,uint32_t *pc, int *count) {
  // 查找关键词位置（假设格式："pc=0x80000000, count=1"）
  char *pc_start = strstr(line, "pc");
  char *count_start = strstr(line, "count");
  if (!pc_start || !count_start) return 0;  // 格式错误

  // 提取pc值（支持16进制）
  if (sscanf(pc_start + 3, "%x", pc) != 1) return 0;  // 跳过"pc="
  // 提取count值（十进制）
  if (sscanf(count_start + 8, "%d", count) != 1) return 0; // 跳过"count="

  return 1;  // 解析成功
}

int main(void)
{
  FILE *fp = fopen("nemu-log.txt", "r");
  if (!fp) {
      fprintf(stderr, "Error opening file: %s\n", strerror(errno));
      return 1;
  }
  char line[1024];
  while (fgets(line, sizeof(line), fp)) {  // 逐行读取
      uint32_t pc;
      int count;
      //parse_line(line, &pc, &count);
      pc = 0x0f000030;
      count = 5;
      for(int i=0;i<count;i++)
      {
        Cache_decode(pc);
        pc = pc + 4;
      }
  }
  fclose(fp);
    printf("sdram hit =%u sdram miss =%u\n",sdram_hit,sdram_miss);
    printf("flash hit =%u flash miss =%u\n",flash_hit,flash_miss);
    return 0;
}