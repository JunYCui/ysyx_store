#include "npc_cpu_exec.h"
#include "npc_isa.h"
#include "npc_macro.h"
#include "npc_define.h"

extern "C" void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
extern "C" int npc_pmem_read(int addr);
extern void ReadReg(int reg_num, svBitVecVal* reg_value);
void difftest_step(vaddr_t pc, vaddr_t npc);
void ftrace_exe(Decode* s);
void difftest_skip_ref();
/* DPI-C*/
extern void GetInst(svBitVecVal* inst_exec);

extern NPCState npc_state;
extern VerilatedVcdC *m_trace ;
extern uint64_t sim_time;

CPU_state cpu={};

Decode s;

uint8_t g_print_step;


void Cpu_Wp(void);
static void wave_record(void)
{
    //将所有跟踪的信号值写入波形转储文件
    m_trace->dump(sim_time);
    sim_time++; // 模拟时钟边沿数加1
}
extern VysyxSoCFull *top; 

static void itrace(Decode *s)
{
    char str[50];
    char *inst;

    disassemble(str, sizeof(str),s->pc, (uint8_t *)&s->inst, 4);
    printf("0x%x: %x \t %s  \n",s->pc,s->inst,str);
}

static void exec_once()
{
    for(int i=0;i<2;i++)
    {
    top->clock ^=1;
    top->eval();
    wave_record();
    }
}


static void trace_and_difftest(Decode *s)
{
    Cpu_Wp();
#ifdef ITARCE
    if(g_print_step)
    itrace(s);
#endif
#ifdef FTRACE
    ftrace_exe(s);
#endif
#ifdef DIFFTEST
    difftest_step(s->pc,s->dnpc);
#endif 
}


void cpu_exec(uint32_t n)
{
    uint8_t skip_dif;
    unsigned char valid =1;
    g_print_step = (n < MAX_INST_TO_PRINT);
    switch (npc_state.state) {
    case NPC_END: case NPC_ABORT:
    printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
    return;
    default: npc_state.state = NPC_RUNNING;
}
    for(int i=0;i<n;i++)
    {
    svSetScope(svGetScopeFromName("TOP.ysyxSoCFull.asic.cpu.cpu"));
        GetPC(&s.pc);
        Getskip_flag(&skip_dif);
        cpu.pc = s.pc;
     //   s.inst = npc_pmem_read(s.pc);
        if(skip_dif != 0)
        {
            difftest_skip_ref();
        }
        exec_once();
        Getvalid(&valid);
        GetPC(&cpu.pc);
        while(!valid)
        {
            exec_once();
            GetPC(&cpu.pc);
            Getvalid(&valid);
        }
    svSetScope(svGetScopeFromName("TOP.ysyxSoCFull.asic.cpu.cpu.IDU_Inst0.Reg_Stack_inst0.Reg_inst"));
        for(int j=0;j<32;j++)
        {
            ReadReg(j,&cpu.gpr[j]);
        }
        trace_and_difftest(&s);
        if(npc_state.state !=NPC_RUNNING)
            break;
    }

}
    
void npc_cpu_init()
{
    cpu.gpr[0] = 0;
    cpu.pc = RESET_VECTOR;
}