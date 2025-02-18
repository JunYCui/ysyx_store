#include "npc_init.h"
#include "nvboard.h"
#include "npc_common.h"
#include "npc_memory.h"
#include "npc_cpu_exec.h"
#include "npc_sdb.h"
#include "npc_define.h"


void nvboard_bind_all_pins(VysyxSoCFull* top);

#define FLASH_OFFSET 0X30000000
extern "C" int npc_pmem_read(int addr);

extern "C" void flash_read(int32_t addr, int32_t *data) { 
    *data = npc_pmem_read(addr+FLASH_OFFSET);
    return;
}
extern "C" void mrom_read(int32_t addr, int32_t *data) {
   // printf("addr = %x\n",addr);
    *data = npc_pmem_read(addr);
    return ;
}

// 实例化一个 VerilatedVcdC 类型的对象 m_trace，用于波形跟踪
VerilatedVcdC *m_trace = new VerilatedVcdC;

// contextp用来保存仿真的时间
VerilatedContext *contextp = new VerilatedContext;

// 构建一个名为top的仿真模型
VysyxSoCFull *top = new VysyxSoCFull{contextp};


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

void new_wave(void)
{
    static uint32_t count;
    char str[30];
    count ++;
    if(count > 10){
        sprintf(str,"wave%d.vcd",count-10);
        remove(str);
    }
    sprintf(str,"wave%d.vcd",count);
    m_trace->open((const char*)str);
}

void wave_record(void)
{
    //将所有跟踪的信号值写入波形转储文件
    if(~top->externalPins_uart_tx)
 //   printf("tx = %d \n",top->externalPins_uart_tx);
    nvboard_update();
    m_trace->dump(sim_time);
    sim_time++; // 模拟时钟边沿数加1
#ifdef WAVE_TRACE
    if(sim_time%1000000 == 0)
    {
        m_trace->flush();
        m_trace->close();
        new_wave();
    }
#endif
}

int main(int argc,char* argv[])
{
    unsigned char valid;
    Verilated::commandArgs(argc, argv);
    init_monitor(argc, argv);
#ifdef WAVE_TRACE
    Verilated::traceEverOn(true);

    nvboard_bind_all_pins(top);
    nvboard_init();
    // 将 m_trace 与 top 进行关联，其中5表示波形的采样深度为5级以下
    top->trace(m_trace, 5);
    new_wave();
#endif
    for( int i=0;i<10;i++)
    cpu_reset();
        
    svSetScope(svGetScopeFromName("TOP.ysyxSoCFull.asic.cpu.cpu"));
    while(!valid)
    {
        for(int i=0;i<2;i++)
        {
            top->clock ^=1;
            top->eval();
            wave_record();
        }
        Getvalid(&valid);
    }

    sdb_mainloop();
    
    m_trace->close();

}