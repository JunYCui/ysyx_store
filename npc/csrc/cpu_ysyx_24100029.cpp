#include "getopt.h"

#include "Vcpu_ysyx_24100029.h"
#include <verilated.h>
#include <verilated_vcd_c.h>  //VCD波形输出头文件

#include "svdpi.h"
#include "Vcpu_ysyx_24100029__Dpi.h"


#include "stdio.h"
#include "stdlib.h"
#include "assert.h"


#define CONFIG_MSIZE 0x8000000
#define CONFIG_MBASE 0x80000000
#define RESET_VECTOR CONFIG_MBASE

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int int16_t;
typedef unsigned short int uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;


uint32_t pmem_read(uint32_t addr, int len) ;
void init_monitor(int argc, char *argv[]);


static const uint32_t img [] = {
  0x00000297,  // auipc t0,0
  0x00028823,  // sb  zero,16(t0)
  0x0102c503,  // lbu a0,16(t0)
  0x00100073,  // ebreak (used as nemu_trap)
  0xdeadbeef,  // some data
};

uint8_t *pmem = NULL;
char *img_file = NULL;

static void init_mem() {
  pmem = (uint8_t*)malloc(CONFIG_MSIZE);
  assert(pmem);
}


static uint8_t* guest_to_host(uint32_t paddr) { return pmem + paddr - CONFIG_MBASE; }


static inline uint32_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    default: return 0;
  }
}

uint32_t pmem_read(uint32_t addr, int len) {
  uint32_t ret = host_read(guest_to_host(addr), len);
  return ret;
}

static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {0          , 0                , NULL,  0 },
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-bhl:d:p:e:", table, NULL)) != -1) {
    switch (o) {
      case 1: img_file = optarg; return 0;
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        printf("\n");
        exit(0);
    }
  }
  return 0;
}

static void load_img() {
  if (img_file == NULL) {
    printf("No image is given. Use the default build-in image. \n");

  }

  FILE *fp = fopen(img_file, "rb");


  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);

  printf("The image is %s, size = %ld \n", img_file, size);

  fseek(fp, 0, SEEK_SET);
  int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
  assert(ret == 1);

  fclose(fp);

}


void init_monitor(int argc, char *argv[])
{
  init_mem();

  parse_args(argc, argv);

  load_img();
}






void fi() { exit(0); }

// contextp用来保存仿真的时间
VerilatedContext *contextp = new VerilatedContext;

// 构建一个名为top的仿真模型
Vcpu_ysyx_24100029 *top = new Vcpu_ysyx_24100029{contextp};


#define MAX_SIM_TIME 100 //定义模拟的时钟边沿数（包括上下边沿）
uint64_t sim_time = 0;

int main(int argc,char* argv[])
{
        // 开启波形跟踪
    Verilated::traceEverOn(true);
    // 实例化一个 VerilatedVcdC 类型的对象 m_trace，用于波形跟踪
    VerilatedVcdC *m_trace = new VerilatedVcdC;

    init_monitor(argc, argv);
    
    // 将 m_trace 与 top 进行关联，其中5表示波形的采样深度为5级以下
    top->trace(m_trace, 5);
    m_trace->open("waveform.vcd");
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
    printf("0x%x \n",img[1]);    
    while(!sim_time < MAX_SIM_TIME)
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
    m_trace->close();
}