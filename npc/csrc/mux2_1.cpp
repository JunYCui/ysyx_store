#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Vmux2_1.h"
#include <verilated.h>

#include "nvboard.h"

static TOP_NAME dut;
void nvboard_bind_all_pins(TOP_NAME* top);

int main(int argc,char** argv )
{
    // bind all pins
    nvboard_bind_all_pins(&dut);
    nvboard_init();

    while(1)
    {
    dut.eval();
    
    nvboard_update();
    }
}