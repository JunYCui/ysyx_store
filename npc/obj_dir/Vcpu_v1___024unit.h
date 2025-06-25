// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcpu_v1.h for the primary calling header

#ifndef VERILATED_VCPU_V1___024UNIT_H_
#define VERILATED_VCPU_V1___024UNIT_H_  // guard

#include "verilated.h"

class Vcpu_v1__Syms;

class Vcpu_v1___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vcpu_v1__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcpu_v1___024unit(Vcpu_v1__Syms* symsp, const char* v__name);
    ~Vcpu_v1___024unit();
    VL_UNCOPYABLE(Vcpu_v1___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
