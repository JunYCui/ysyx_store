#ifndef __NPC_MEMORY_H__
#define __NPC_MEMORY_H__

#include "npc_common.h"

#if !defined(likely)
#define likely(cond)   __builtin_expect(cond, 1)
#define unlikely(cond) __builtin_expect(cond, 0)
#endif




uint8_t* guest_to_host(uint32_t paddr) ;
word_t paddr_read(paddr_t addr, int len);

static inline bool in_pmem(paddr_t addr) {
  return addr - CONFIG_MBASE < CONFIG_MSIZE;
}

#endif