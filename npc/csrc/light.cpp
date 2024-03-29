#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Vlight.h"
#include <verilated.h>

#include "nvboard.h"


static TOP_NAME dut;

static void single_cycle() {
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
}

static void reset(int n) {
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}


void nvboard_bind_all_pins(TOP_NAME* top);

int main(int argc,char** argv )
{
    // bind all pins
    nvboard_bind_all_pins(&dut);
    nvboard_init();
    reset(10);
    while(1)
    {
    single_cycle();
    nvboard_update();
    }
}