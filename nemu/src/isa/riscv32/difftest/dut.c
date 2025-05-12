/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"
#include <isa-def.h>
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  for(int i=0;i<MUXDEF(CONFIG_RVE, 16, 32);i++)
  {
    if(ref_r->gpr[i] != gpr(i))
    {
      printf(" \n 0x%x: %s value is error! \n",pc,reg_name(i));
      printf("ref value:%d \t dut value:%d \n",ref_r->gpr[i] ,gpr(i) );
      return false;
    }
  }
  if(ref_r->pc != cpu.pc)
  {
    printf("\n 0x%x: pc value is error \n",pc);
    printf("ref value:0x%x \t dut value:0x%x \n",ref_r->pc ,cpu.pc );
    return false;
  }
  if(ref_r->csr[MCAUSE] != cpu.csr[MCAUSE])
  {
    printf("\n 0x%x: mcause value is error \n",pc);
    printf("ref value:0x%x \t dut value:0x%x \n",ref_r->csr[MCAUSE] ,cpu.csr[MCAUSE] );
    return false;
  }
  if(ref_r->csr[MEPC] != cpu.csr[MEPC])
  {
    printf("\n 0x%x: mepc value is error \n",pc);
    printf("ref value:0x%x \t dut value:0x%x \n",ref_r->csr[MEPC] ,cpu.csr[MEPC] );
    return false;
  }
  return true;
}

void isa_difftest_attach() {
}
