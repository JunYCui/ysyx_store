/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#ifndef __MEMORY_PADDR_H__
#define __MEMORY_PADDR_H__

#include <common.h>

#define FLASH_LEFT  ((paddr_t)CONFIG_FLASH_BASE)
#define FLASH_RIGHT ((paddr_t)CONFIG_FLASH_BASE + CONFIG_FLASH_SIZE - 1)
#define SRAM_LEFT  ((paddr_t)CONFIG_SRAM_BASE)
#define SRAM_RIGHT ((paddr_t)CONFIG_SRAM_BASE + CONFIG_SRAM_SIZE - 1)
#define SDRAM_LEFT  ((paddr_t)CONFIG_SDRAM_BASE)
#define SDRAM_RIGHT ((paddr_t)CONFIG_SDRAM_BASE + CONFIG_SDRAM_SIZE - 1)
#define PSRAM_LEFT  ((paddr_t)CONFIG_PSRAM_BASE)
#define PSRAM_RIGHT ((paddr_t)CONFIG_PSRAM_BASE + CONFIG_PSRAM_SIZE - 1)

#define RESET_VECTOR (FLASH_LEFT + CONFIG_PC_RESET_OFFSET)

/* convert the guest physical address in the guest program to host virtual address in NEMU */
uint8_t* guest_to_host(paddr_t paddr);
/* convert the host virtual address in NEMU to guest physical address in the guest program */
paddr_t host_to_guest(uint8_t *haddr);

static inline bool in_flash(paddr_t addr) {
  return addr - CONFIG_FLASH_BASE < CONFIG_FLASH_SIZE;
}

static inline bool in_sram(paddr_t addr){
  return addr - CONFIG_SRAM_BASE < CONFIG_SRAM_SIZE;
}
static inline bool in_sdram(paddr_t addr){
  return addr - CONFIG_SDRAM_BASE < CONFIG_SDRAM_SIZE;
}
static inline bool in_psram(paddr_t addr){
  return addr - CONFIG_PSRAM_BASE < CONFIG_PSRAM_SIZE;
}


word_t paddr_read(paddr_t addr, int len);
void paddr_write(paddr_t addr, int len, word_t data);

#endif
