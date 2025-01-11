#include "npc_init.h"
#include "npc_common.h"
#include "npc_memory.h"
#include "npc_cpu_exec.h"
#include "npc_sdb.h"
#define MROM_OFFSET 0x60000000

extern "C" int npc_pmem_read(int addr);

extern "C" void flash_read(int32_t addr, int32_t *data) { assert(0); }
extern "C" void mrom_read(int32_t addr, int32_t *data) {
    *data = npc_pmem_read(addr+MROM_OFFSET);
    printf("addr = 0x%x inst = %x \n",addr,data);
    return ;
}

// 实例化一个 VerilatedVcdC 类型的对象 m_trace，用于波形跟踪
VerilatedVcdC *m_trace = new VerilatedVcdC;

// contextp用来保存仿真的时间
VerilatedContext *contextp = new VerilatedContext;

// 构建一个名为top的仿真模型
VysyxSoCFull *top = new VysyxSoCFull{contextp};


#define MAX_SIM_TIME 100 //定义模拟的时钟边沿数（包括上下边沿）
uint64_t sim_time = 0;



void fi(int val) { exit(val); }

void cpu_reset(void)
{
    top->clock = 0;
    top->reset = 1;
    top->eval();
    m_trace->dump(sim_time);
    sim_time++;
    top->clock = 1;
    top->eval();
    m_trace->dump(sim_time);
    sim_time++;
    top->reset = 0;
    top->clock = 0;
    top->eval();
    m_trace->dump(sim_time);
    sim_time++;
}

void wave_record(void)
{
    //将所有跟踪的信号值写入波形转储文件
    m_trace->dump(sim_time);
    sim_time++; // 模拟时钟边沿数加1
}

int main(int argc,char* argv[])
{
    int valid;
    Verilated::commandArgs(argc, argv);
    // 开启波形跟踪
    Verilated::traceEverOn(true);

    init_monitor(argc, argv);
    
    // 将 m_trace 与 top 进行关联，其中5表示波形的采样深度为5级以下
    top->trace(m_trace, 5);
    m_trace->open("waveform.vcd");

    cpu_reset();
    //valid = top->WBU_valid;
/*
    while(!valid)
    {
    for(int i=0;i<2;i++)
    {
    top->clk ^=1;
    top->eval();
    wave_record();
    }
    valid = top->WBU_valid;
    }
   */
    sdb_mainloop();
    
    m_trace->close();

}