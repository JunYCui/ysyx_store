#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Vtop.h"
#include <verilated.h>

#include "nvboard.h"


static TOP_NAME dut;

static void single_cycle() {
  dut.clk = 0; dut.eval();
  dut.clk = 1; dut.eval();
}


void nvboard_bind_all_pins(TOP_NAME* top);

int main(int argc,char** argv )
{
    // bind all pins
    nvboard_bind_all_pins(&dut);
    nvboard_init();
    while(1)
    {
    single_cycle();
    nvboard_update();
    }
}