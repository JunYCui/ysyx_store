// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb.h"
#include "Vysyx_24100029_IFU_tb___024root.h"
#include "Vysyx_24100029_IFU_tb___024unit.h"
#include "Vysyx_24100029_IFU_tb_axi4_if.h"

// FUNCTIONS
Vysyx_24100029_IFU_tb__Syms::~Vysyx_24100029_IFU_tb__Syms()
{
}

Vysyx_24100029_IFU_tb__Syms::Vysyx_24100029_IFU_tb__Syms(VerilatedContext* contextp, const char* namep, Vysyx_24100029_IFU_tb* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
    , TOP__ysyx_24100029_IFU_tb__DOT__bus{this, Verilated::catName(namep, "ysyx_24100029_IFU_tb.bus")}
{
        // Check resources
        Verilated::stackCheck(276);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.__PVT__ysyx_24100029_IFU_tb__DOT__bus = &TOP__ysyx_24100029_IFU_tb__DOT__bus;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP__ysyx_24100029_IFU_tb__DOT__bus.__Vconfigure(true);
}
