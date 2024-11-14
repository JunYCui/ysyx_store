#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Vcpu_v1.h"
#include <verilated.h>
#include <verilated_vcd_c.h>  //VCD波形输出头文件

#include "svdpi.h"
#include "Vcpu_v1__Dpi.h"


#define CONFIG_MSIZE 0x8000000 
#define CONFIG_MBASE 0x80000000
#define RESET_VECTOR CONFIG_MBASE

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;

static char *img_file = NULL;

/* verilator lint_off EOFNEWLINE */
static uint32_t img[]={
    0x00100293,    // addi $t0, $zero, 1
    0x00128293,    // addi $to  $t0  , 1   
    0x00128293,    // addi $to  $t0  , 1   
    0x00128293,    // addi $to  $t0  , 1   
    0x00128293,    // addi $to  $t0  , 1
    0x00100073     // ebreak
};

uint32_t * guest_to_host(uint32_t paddr) { return img + paddr - CONFIG_MBASE; }



void fi() { exit(0); }


static uint32_t pmem_read(uint32_t addr) {
  uint32_t ret = *guest_to_host(addr);
  return ret;
}


// contextp用来保存仿真的时间
VerilatedContext *contextp = new VerilatedContext;

// 构建一个名为top的仿真模型
Vcpu_v1 *top = new Vcpu_v1{contextp};


#define MAX_SIM_TIME 100 //定义模拟的时钟边沿数（包括上下边沿）
vluint64_t sim_time = 0;

int main(int argc,char* argv[])
{
        // 开启波形跟踪
    Verilated::traceEverOn(true);
    // 实例化一个 VerilatedVcdC 类型的对象 m_trace，用于波形跟踪
    VerilatedVcdC *m_trace = new VerilatedVcdC;
    // 将 m_trace 与 top 进行关联，其中5表示波形的采样深度为5级以下

  printf(" %ld ",sizeof(img) );
    top->trace(m_trace, 5);
    m_trace->open("waveform.vcd");
    top->clk = 0;
    top->rst = 0;
    top->eval();
    top->clk = 1;
    top->eval();
    top->rst = 1;
    top->clk = 0;
    top->eval();
    while(!sim_time < MAX_SIM_TIME)
    {
    top->clk ^=1;
    if(top->clk == 0)
    {
    top->inst = pmem_read(top->pc);  
    
    }
    top->eval();
    //将所有跟踪的信号值写入波形转储文件
    m_trace->dump(sim_time);
    sim_time++; // 模拟时钟边沿数加1
    }
    m_trace->close();
}