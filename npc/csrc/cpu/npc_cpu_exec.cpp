#include "npc_cpu_exec.h"
#include "npc_isa.h"
#include "npc_macro.h"
#include "npc_define.h"

extern "C" void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
extern void ReadReg(int reg_num, svBitVecVal* reg_value);
void difftest_step(vaddr_t pc, vaddr_t npc);
void ftrace_exe(Decode* s);
void difftest_skip_ref();
/* DPI-C*/
extern void GetInst(svBitVecVal* inst_exec);

extern NPCState npc_state;
extern VerilatedVcdC *m_trace ;
extern uint64_t sim_time;
extern uint8_t skip_flag;

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
extern Vcpu_ysyx_24100029 *top; 

static void itrace(Decode *s)
{
    char str[50];
    char str1[50];
    static char inst_old[50];
    static char rd_old[20];
    char* rs2;
    char *rs1; 
    char* inst;
    char* rd;

    disassemble(str, sizeof(str),s->pc, (uint8_t *)&s->inst, 4);
    strcpy(str1,str);
    inst = strtok(str,"\t");
    if(strcmp(inst,"c.unimp") == 0)
    {
        return;
    }
        printf("0x%x: %x \t %s  \n",s->pc,s->inst,str1);
    rd = strtok(NULL,",");
        if(rd != NULL)
    rs1 = strtok(NULL,",");
        if(rs1 != NULL)
    rs2 = strtok(NULL," ");

    if(strcmp(inst,"jal") == 0 || strcmp(inst,"jalr") == 0 || inst[0] == 'b')
    {
        skip_flag = 2;
        cpu.pc = top->IDU_pc;
    }
    if(rs1 != NULL)
    {
        if(inst_old[0]== 'l' && (strcmp(rs1,rd_old) == 0))
      {
        skip_flag = 1;
      }
    }
    else if(rs2 != NULL)
    {
        if(inst_old[0]== 'l' && (strcmp(rs2,rd_old) == 0))
      {
        skip_flag = 1;
        assert(0);
      }
    }

    strcpy(inst_old,inst);
    strcpy(rd_old, rd);
}

static void exec_once()
{
    for(int i=0;i<2;i++)
    {
    top->clk ^=1;
    top->eval();
    wave_record();
    }


}


static void trace_and_difftest(Decode *s)
{
    Cpu_Wp();
#ifdef ITARCE
    //if(g_print_step)
    itrace(s);
#endif
#ifdef FTRACE
    //ftrace_exe(s);
#endif
#ifdef DIFFTEST
    difftest_step(s->pc,s->dnpc);
#endif 
}


void cpu_exec(uint32_t n)
{
    g_print_step = (n < MAX_INST_TO_PRINT);
    switch (npc_state.state) {
    case NPC_END: case NPC_ABORT:
      printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
      return;
    default: npc_state.state = NPC_RUNNING;
  }
    for(int i=0;i<n;i++)
    {
        s.pc=top->pc;
        s.dnpc=top->dnpc;
        s.snpc=top->snpc;
    svSetScope(svGetScopeFromName("TOP.cpu_ysyx_24100029"));
        GetInst(&s.inst);
        if(skip_flag-- > 0)
        {
            difftest_skip_ref();
        }    
        exec_once();
   // printf("top->pc = 0x%x, top->dnpc = 0x%x, top->snpc = 0x%x \n",top->pc,top->dnpc,top->snpc);
        cpu.pc = top->pc;
    svSetScope(svGetScopeFromName("TOP.cpu_ysyx_24100029.IDU_Inst0.Reg_Stack_inst0.Reg_inst"));
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