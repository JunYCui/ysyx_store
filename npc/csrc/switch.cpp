#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Vswitch.h"
#include <verilated.h>

#include "verilated_vcd_c.h"

#include "nvboard.h"

static TOP_NAME dut;
void nvboard_bind_all_pins(TOP_NAME* top);

int main(int argc,char** argv )
{
    VerilatedContext *contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vswitch* top = new Vswitch{contextp};
    
    // bind all pins
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    while(1)
    {
    dut.eval();
    nvboard_update();
    }
}