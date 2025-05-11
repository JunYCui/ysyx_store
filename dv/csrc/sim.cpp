#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include"VSimTop.h"
#include <verilated.h>
#include <verilated_vcd_c.h>  //VCD波形输出头文件

#define MAX_SIM_TIME 10000 //定义模拟的时钟边沿数（包括上下边沿）

// contextp用来保存仿真的时间
    VerilatedContext *contextp = new VerilatedContext;

// 构建一个名为top的仿真模型
    VSimTop *top = new VSimTop{contextp};

vluint64_t sim_time = 0;


int main(int argc,char** argv ) {
    // 开启波形跟踪
    Verilated::traceEverOn(true);
    // 实例化一个 VerilatedVcdC 类型的对象 m_trace，用于波形跟踪
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    // 将 m_trace 与 top 进行关联，其中5表示波形的采样深度为5级以下
    top->trace(m_trace, 5);
    m_trace->open("wave/waveform.vcd");
    while (!contextp->gotFinish())
    {
        top->eval();
        m_trace->dump(contextp->time());
        contextp->timeInc(1);
    }
    m_trace->close();

}