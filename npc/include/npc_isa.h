#ifndef __NPC_ISA_H__
#define __NPC_ISA_H__

#include "npc_common.h"
enum {NPC_STOP, NPC_RUNNING, NPC_END, NPC_QUIT,NPC_ABORT};

typedef struct {
  int state;
  paddr_t halt_pc;
  uint32_t halt_ret;
} NPCState;

typedef struct {
  word_t gpr[32];
  word_t pc;
} CPU_state;


#endif