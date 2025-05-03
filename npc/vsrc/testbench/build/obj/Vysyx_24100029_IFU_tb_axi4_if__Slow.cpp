// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb__Syms.h"
#include "Vysyx_24100029_IFU_tb_axi4_if.h"

void Vysyx_24100029_IFU_tb_axi4_if___ctor_var_reset(Vysyx_24100029_IFU_tb_axi4_if* vlSelf);

Vysyx_24100029_IFU_tb_axi4_if::Vysyx_24100029_IFU_tb_axi4_if(Vysyx_24100029_IFU_tb__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vysyx_24100029_IFU_tb_axi4_if___ctor_var_reset(this);
}

void Vysyx_24100029_IFU_tb_axi4_if::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vysyx_24100029_IFU_tb_axi4_if::~Vysyx_24100029_IFU_tb_axi4_if() {
}
