#include "Vcpu_ysyx_24100029.h"
#include <verilated.h>
#include <verilated_vcd_c.h>  //VCD波形输出头文件

#include "svdpi.h"
#include "Vcpu_ysyx_24100029__Dpi.h"

#include "../include/init.h"





// contextp用来保存仿真的时间
VerilatedContext *contextp = new VerilatedContext;

// 构建一个名为top的仿真模型
Vcpu_ysyx_24100029 *top = new Vcpu_ysyx_24100029{contextp};

// 实例化一个 VerilatedVcdC 类型的对象 m_trace，用于波形跟踪
VerilatedVcdC *m_trace = new VerilatedVcdC;


#define MAX_SIM_TIME 100 //定义模拟的时钟边沿数（包括上下边沿）
uint64_t sim_time = 0;



void fi() { exit(0); }

void cpu_reset(void)
{
    top->clk = 0;
    top->rst = 0;
    top->eval();
    m_trace->dump(sim_time);
    sim_time++;
    top->clk = 1;
    top->eval();
    m_trace->dump(sim_time);
    sim_time++;
    top->rst = 1;
    top->clk = 0;
    top->inst = pmem_read(top->pc,4);  
    top->eval();
    m_trace->dump(sim_time);
    sim_time++;
}

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
 
    //将所有跟踪的信号值写入波形转储文件
    m_trace->dump(sim_time);
    sim_time++; // 模拟时钟边沿数加1
    }
}


int main(int argc,char* argv[])
{
        // 开启波形跟踪
    Verilated::traceEverOn(true);

    init_monitor(argc, argv);
    
    // 将 m_trace 与 top 进行关联，其中5表示波形的采样深度为5级以下
    top->trace(m_trace, 5);
    m_trace->open("waveform.vcd");
    cpu_reset();

    while(!sim_time < MAX_SIM_TIME)
    {
      cpu_exec(1);
    }
    m_trace->close();
}