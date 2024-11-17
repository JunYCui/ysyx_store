#ifndef  __COMMON_H__
#define  __COMMON_H__


#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "getopt.h"

#define CONFIG_MSIZE 0x8000000
#define CONFIG_MBASE 0x80000000
#define RESET_VECTOR CONFIG_MBASE

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;


#endif