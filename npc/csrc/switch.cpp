#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "Vswitch.h"
#include <verilated.h>

#include "verilated_vcd_c.h"

//#include "nvboard.h"

//static Vswitch dut;

int main(int argc,char** argv )
{
    VerilatedContext *contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vswitch* top = new Vswitch{contextp};
    
    // bind all pins
   // nvboard_bind_all_pins(&dut);
    //nvboard_init();
    
    //wave trace
    VerilatedVcdC *tfp = new VerilatedVcdC;
    contextp->traceEverOn(true);
    top->trace(tfp,0);
    tfp->open("wave.vcd");

    while(!contextp->gotFinish()){    
    int a = rand() & 1;
    int b = rand() & 1;
    top->a = a;
    top->b = b;
    top->eval();
   // nvboard_update();
   // single_cycle();
    tfp->dump(contextp->time());
    contextp->timeInc(1);
    printf("a = %d, b = %d, f= %d \n ",a,b,top->f);
    assert(top->f == (a^b));
    }
   // nvboard_quit();
    delete top;
    tfp->close();
    delete contextp;
    return 0;
}