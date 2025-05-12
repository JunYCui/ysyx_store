#ifndef __NPC_FTRACE_H__
#define __NPC_FTRACE_H__

#include "npc_common.h"
#include "elf.h"

#define FUNC_MAXNUM 1000

typedef struct{
    Elf32_Addr addr;
    Elf32_Word size;
    char name[100];
    bool state;
}FUNC_TR;


#endif