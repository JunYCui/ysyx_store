#include "Vswitch.h"
#include <verilated.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "verilated_vcd_c.h" //vcd_simulator



int main(int argc, char** argv, char** env) {

    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vswitch* top = new Vswitch{contextp};
    //wave
    VerilatedVcdC* tfp = new VerilatedVcdC;
    contextp->traceEverOn(true);
    top->trace(tfp, 0); //
    tfp->open("wave.vcd"); //设置输出的文件wave.vcd
    int time=1000;
  while(time--) {
      int a = rand()&1;
      int b = rand()&1;
      top->a =a;
      top->b =b;
      top->eval();
    tfp->dump(contextp->time()); //dump wave
    contextp->timeInc(1); //推动仿真时间
  }

  delete top;
  tfp->close();
  delete contextp;
  return 0;

}