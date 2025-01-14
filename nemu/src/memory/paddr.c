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

#include <memory/host.h>
#include <memory/paddr.h>
#include <device/mmio.h>
#include <isa.h>

#if   defined(CONFIG_PMEM_MALLOC)
static uint8_t *rom = NULL;
#else // CONFIG_PMEM_GARRAY
static uint8_t pmem[CONFIG_MSIZE] PG_ALIGN = {};
#endif
static uint8_t *sram = NULL;

uint8_t* guest_to_host(paddr_t paddr) { return rom + paddr - CONFIG_ROM_SIZE; }
paddr_t host_to_guest(uint8_t *haddr) { return haddr - rom + CONFIG_ROM_SIZE; }
uint8_t* SRAM_guest_to_host(paddr_t paddr) { return sram + paddr - CONFIG_SRAM_SIZE; }

static word_t sram_read(paddr_t addr, int len) {
  word_t ret = host_read(SRAM_guest_to_host(addr), len);

  IFDEF(CONFIG_MTRACE,printf("The address " ANSI_FMT(FMT_WORD, ANSI_FG_BLUE)  " is read at pc = " FMT_WORD "\n",addr,cpu.pc));
  return ret;
}

static void sram_write(paddr_t addr, int len, word_t data) {
  host_write(SRAM_guest_to_host(addr), len, data);
  IFDEF(CONFIG_MTRACE,printf("The address " ANSI_FMT(FMT_WORD, ANSI_FG_BLUE) " is written at pc = " FMT_WORD "\n",addr,cpu.pc));
}

static word_t pmem_read(paddr_t addr, int len) {
  word_t ret = host_read(guest_to_host(addr), len);

  IFDEF(CONFIG_MTRACE,printf("The address " ANSI_FMT(FMT_WORD, ANSI_FG_BLUE)  " is read at pc = " FMT_WORD "\n",addr,cpu.pc));
  return ret;
}
/*
static void pmem_write(paddr_t addr, int len, word_t data) {
  host_write(guest_to_host(addr), len, data);
  IFDEF(CONFIG_MTRACE,printf("The address " ANSI_FMT(FMT_WORD, ANSI_FG_BLUE) " is written at pc = " FMT_WORD "\n",addr,cpu.pc));
}
*/
static void out_of_bound(paddr_t addr) {
  panic("address = " FMT_PADDR " is out of bound of pmem [" FMT_PADDR ", " FMT_PADDR "] at pc = " FMT_WORD,
      addr, ROM_LEFT, ROM_RIGHT, cpu.pc);
}

void init_mem() {
#if   defined(CONFIG_PMEM_MALLOC)
  rom = (uint8_t*)malloc(CONFIG_ROM_SIZE);
  sram = (uint8_t*)malloc(CONFIG_SRAM_SIZE);
  assert(rom);
#endif
  IFDEF(CONFIG_MEM_RANDOM, memset(rom, rand(), CONFIG_ROM_SIZE));
  Log("physical memory area [" FMT_PADDR ", " FMT_PADDR "]", ROM_LEFT, ROM_RIGHT);
}

word_t paddr_read(paddr_t addr, int len) {
  if (likely(in_rom(addr))) return pmem_read(addr, len);
  else if(likely(in_sram(addr))) return sram_read(addr, len);
  IFDEF(CONFIG_DEVICE, return mmio_read(addr, len));
  out_of_bound(addr);
  return 0;
}

void paddr_write(paddr_t addr, int len, word_t data) {
  if (likely(in_rom(addr))) { printf("rom can't write! \n");assert(0); return; }
  else if(likely(in_sram(addr))) return sram_write(addr,len,data);
  IFDEF(CONFIG_DEVICE, mmio_write(addr, len, data); return);
  out_of_bound(addr);
}
