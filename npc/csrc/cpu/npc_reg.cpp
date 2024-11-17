#include "npc_common.h"
extern void ReadReg(int reg_num, svBitVecVal* reg_value);

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};


void isa_reg_display() 
{
  uint16_t i;
  uint32_t regvalue;
  
  for(i = 0;i<32;i++)
  {
  ReadReg(i,&regvalue);
  printf("%s: \t 0x%-10x \t %-10d \n",regs[i],regvalue,regvalue);
  }
}


