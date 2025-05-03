// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#ifndef VERILATED_VYSYX_24100029_IFU_TB_AXI4_IF_H_
#define VERILATED_VYSYX_24100029_IFU_TB_AXI4_IF_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vysyx_24100029_IFU_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vysyx_24100029_IFU_tb_axi4_if final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ __PVT__awready;
    CData/*0:0*/ __PVT__wready;
    CData/*0:0*/ __PVT__bid;
    CData/*1:0*/ __PVT__bresp;
    CData/*0:0*/ __PVT__bvalid;
    CData/*0:0*/ arvalid;
    CData/*0:0*/ arready;
    CData/*0:0*/ __PVT__rid;
    CData/*1:0*/ __PVT__rresp;
    CData/*0:0*/ rlast;
    CData/*0:0*/ rvalid;
    CData/*0:0*/ __Vdly__arvalid;

    // INTERNAL VARIABLES
    Vysyx_24100029_IFU_tb__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vysyx_24100029_IFU_tb_axi4_if(Vysyx_24100029_IFU_tb__Syms* symsp, const char* v__name);
    ~Vysyx_24100029_IFU_tb_axi4_if();
    VL_UNCOPYABLE(Vysyx_24100029_IFU_tb_axi4_if);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};

std::string VL_TO_STRING(const Vysyx_24100029_IFU_tb_axi4_if* obj);

#endif  // guard
