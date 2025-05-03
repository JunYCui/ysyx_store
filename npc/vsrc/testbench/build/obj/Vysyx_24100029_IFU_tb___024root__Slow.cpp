// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb__Syms.h"
#include "Vysyx_24100029_IFU_tb___024root.h"

void Vysyx_24100029_IFU_tb___024root___ctor_var_reset(Vysyx_24100029_IFU_tb___024root* vlSelf);

Vysyx_24100029_IFU_tb___024root::Vysyx_24100029_IFU_tb___024root(Vysyx_24100029_IFU_tb__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , __VdlySched{*symsp->_vm_contextp__}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vysyx_24100029_IFU_tb___024root___ctor_var_reset(this);
}

void Vysyx_24100029_IFU_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vysyx_24100029_IFU_tb___024root::~Vysyx_24100029_IFU_tb___024root() {
}
