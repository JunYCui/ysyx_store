// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#ifndef VERILATED_VYSYX_24100029_IFU_TB___024UNIT_H_
#define VERILATED_VYSYX_24100029_IFU_TB___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vysyx_24100029_IFU_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vysyx_24100029_IFU_tb___024unit final : public VerilatedModule {
  public:

    // INTERNAL VARIABLES
    Vysyx_24100029_IFU_tb__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vysyx_24100029_IFU_tb___024unit(Vysyx_24100029_IFU_tb__Syms* symsp, const char* v__name);
    ~Vysyx_24100029_IFU_tb___024unit();
    VL_UNCOPYABLE(Vysyx_24100029_IFU_tb___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
