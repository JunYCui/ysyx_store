// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcpu_v1.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vcpu_v1__Syms.h"
#include "Vcpu_v1___024root.h"

void Vcpu_v1___024root___ctor_var_reset(Vcpu_v1___024root* vlSelf);

Vcpu_v1___024root::Vcpu_v1___024root(Vcpu_v1__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vcpu_v1___024root___ctor_var_reset(this);
}

void Vcpu_v1___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vcpu_v1___024root::~Vcpu_v1___024root() {
}
