#include "npc_common.h"
extern void ReadReg(int reg_num, svBitVecVal* reg_value);

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};
const char* reg_name(int idx) {
  return regs[idx];
}

void isa_reg_display() 
{
  uint16_t i;
  uint32_t regvalue;
#ifdef __YSYXSOC__
    svSetScope(svGetScopeFromName("TOP.ysyxSoCFull.asic.cpu.cpu.IDU_Inst0.Reg_Stack_inst0.Reg_inst"));
#else 
    svSetScope(svGetScopeFromName("TOP.ysyx_24100029.IDU_Inst0.Reg_Stack_inst0.Reg_inst"));
#endif
    for(i = 0;i<32;i++)
  {
  ReadReg(i,&regvalue);
  printf("%s: \t 0x%-10x \t %-10d \n",regs[i],regvalue,regvalue);
  }
}

word_t isa_reg_str2val(const char *s, bool *success) 
{
  uint16_t i;
  uint32_t regvalue;
  *success = false;
    svSetScope(svGetScopeFromName("TOP.cpu_ysyx_24100029.IDU_Inst0.Reg_Stack_inst0.Reg_inst"));
  for(i = 0;i<32;i++)
  {
    if(strcmp(s,regs[i])== 0 )
    {
      *success = true;
      ReadReg(i,&regvalue);
      return regvalue;
    }
  }
  return 0;
}
