// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcpu_v1.h for the primary calling header

#ifndef VERILATED_VCPU_V1___024ROOT_H_
#define VERILATED_VCPU_V1___024ROOT_H_  // guard

#include "verilated.h"

class Vcpu_v1__Syms;

class Vcpu_v1___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __VactContinue;
    VL_IN(inst,31,0);
    VL_OUT(pc,31,0);
    VL_OUT(inst_out,31,0);
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vcpu_v1__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vcpu_v1___024root(Vcpu_v1__Syms* symsp, const char* v__name);
    ~Vcpu_v1___024root();
    VL_UNCOPYABLE(Vcpu_v1___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
