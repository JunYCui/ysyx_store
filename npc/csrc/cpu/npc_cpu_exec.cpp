#include "npc_cpu_exec.h"
#include "npc_memory.h"

extern Vcpu_ysyx_24100029 *top; 

void cpu_exec(int n)
{
    for(int i=0;i<n;i++)
    {
    top->clk ^=1;
    if(top->clk == 0)
    {   
    printf("npc = 0x%x\n",top->pc);
    top->inst = pmem_read(top->pc,4);  
    }
    top->eval();

    }
}