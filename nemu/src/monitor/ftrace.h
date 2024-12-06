<<<<<<< HEAD
#ifndef __FTRACE_H__
#define __FTRACE_H__
=======
#ifndef __NPC_FTRACE_H__
#define __NPC_FTRACE_H__
>>>>>>> 3e8efcc

#include "common.h"
#include "elf.h"

#define FUNC_MAXNUM 100

typedef struct{
    Elf32_Addr addr;
    Elf32_Word size;
    char name[50];
    bool state;
}FUNC_TR;


#endif