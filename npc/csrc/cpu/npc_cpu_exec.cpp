#include "npc_cpu_exec.h"
#include "npc_memory.h"
#include "npc_isa.h"

extern void GetInst(svBitVecVal* inst_exec);

extern NPCState npc_state;
extern VerilatedVcdC *m_trace ;
extern uint64_t sim_time;

typedef struct 
{
    uint32_t pc;
    uint32_t inst;
}Decode;

Decode *s;

void Cpu_Wp(void);
static void wave_record(void)
{
    //将所有跟踪的信号值写入波形转储文件
    m_trace->dump(sim_time);
    sim_time++; // 模拟时钟边沿数加1
}
extern Vcpu_ysyx_24100029 *top; 

static void itrace()
{
    svSetScope(svGetScopeFromName("TOP.cpu_ysyx_24100029"));
    uint32_t inst;
    GetInst(&inst);
    printf("0x%x: %x \n",top->pc,inst);
}

static void exec_once()
{
    for(int i=0;i<2;i++)
    {
    top->clk ^=1;
    if(top->clk == 0)
    {   
    itrace();
    top->inst = paddr_read(top->pc,4);  
    }
    top->eval();
    wave_record();
    }
}


static void trace_and_difftest()
{
    Cpu_Wp();
}


void cpu_exec(uint32_t n)
{
    switch (npc_state.state) {
    case NPC_END: case NPC_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: npc_state.state = NPC_RUNNING;
  }
    for(int i=0;i<n;i++)
    {
        s->pc = top ->pc;
        exec_once();
        trace_and_difftest();
        if(npc_state.state !=NPC_RUNNING)
            break;
    }

}