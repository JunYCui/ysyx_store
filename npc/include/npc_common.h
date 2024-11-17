#ifndef  __NPC_COMMON_H__
#define  __NPC_COMMON_H__

#include <stdint.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "getopt.h"
#include "Vcpu_ysyx_24100029.h"
#include <verilated.h>
#include <verilated_vcd_c.h>  //VCD波形输出头文件
#include "svdpi.h"
#include "Vcpu_ysyx_24100029__Dpi.h"

#define CONFIG_MSIZE 0x8000000
#define CONFIG_MBASE 0x80000000
#define RESET_VECTOR CONFIG_MBASE

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef uint32_t word_t;
typedef uint32_t paddr_t;

#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))



#endif