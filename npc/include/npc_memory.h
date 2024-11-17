#ifndef __NPC_MEMORY_H__
#define __NPC_MEMORY_H__

#include "npc_common.h"

uint8_t* guest_to_host(uint32_t paddr) ;
uint32_t pmem_read(uint32_t addr, int len) ;

#endif