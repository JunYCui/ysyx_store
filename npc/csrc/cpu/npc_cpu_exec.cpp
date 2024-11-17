#include "npc_cpu_exec.h"
#include "npc_memory.h"

extern VerilatedVcdC *m_trace ;
extern uint64_t sim_time;
static void wave_record(void)
{
    //将所有跟踪的信号值写入波形转储文件
    m_trace->dump(sim_time);
    sim_time++; // 模拟时钟边沿数加1
}
extern Vcpu_ysyx_24100029 *top; 

void cpu_exec(uint32_t n)
{
    for(int i=0;i<n;i++)
    {
    top->clk ^=1;
    if(top->clk == 0)
    {   
    top->inst = pmem_read(top->pc,4);  
    }
    top->eval();
    wave_record();
    }
}