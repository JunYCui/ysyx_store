#ifndef __NPC_CPU_EXEC_H__
#define __NPC_CPU_EXEC_H__

#include "npc_memory.h"

void cpu_exec(unsigned int n);

typedef struct 
{
  uint32_t pc;
  uint32_t dnpc;
  uint32_t snpc;
  uint32_t inst;
}Decode;

#define MAX_INST_TO_PRINT 10

#endif