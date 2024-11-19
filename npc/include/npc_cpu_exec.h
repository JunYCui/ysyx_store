#ifndef __NPC_CPU_EXEC_H__
#define __NPC_CPU_EXEC_H__

#include "npc_memory.h"

void cpu_exec(unsigned int n);

typedef struct 
{
  uint32_t pc;
  uint32_t inst;
}Decode;

#endif