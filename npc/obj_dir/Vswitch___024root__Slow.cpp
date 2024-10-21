// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vswitch.h for the primary calling header

#include "verilated.h"

#include "Vswitch__Syms.h"
#include "Vswitch___024root.h"

void Vswitch___024root___ctor_var_reset(Vswitch___024root* vlSelf);

Vswitch___024root::Vswitch___024root(Vswitch__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vswitch___024root___ctor_var_reset(this);
}

void Vswitch___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vswitch___024root::~Vswitch___024root() {
}
