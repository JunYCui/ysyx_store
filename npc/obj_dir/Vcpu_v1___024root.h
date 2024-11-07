// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcpu_v1.h for the primary calling header

#ifndef VERILATED_VCPU_V1___024ROOT_H_
#define VERILATED_VCPU_V1___024ROOT_H_  // guard

#include "verilated.h"

class Vcpu_v1__Syms;
class Vcpu_v1___024unit;


class Vcpu_v1___024root final : public VerilatedModule {
  public:
    // CELLS
    Vcpu_v1___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    CData/*0:0*/ cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__hit;
    CData/*2:0*/ cpu_v1__DOT__IDU_inst0__DOT__Type;
    CData/*2:0*/ cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out;
    CData/*0:0*/ cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit;
    CData/*0:0*/ cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit;
    CData/*0:0*/ __Vtrigrprev__TOP__clk;
    CData/*0:0*/ __VactContinue;
    SData/*11:0*/ __VdfgTmp_h5152c62b__0;
    SData/*11:0*/ __VdfgTmp_hac3a854f__0;
    VL_IN(inst,31,0);
    VL_OUT(pc,31,0);
    VL_OUT(rs1_bo,31,0);
    IData/*31:0*/ cpu_v1__DOT__imm;
    IData/*31:0*/ cpu_v1__DOT__rs2_value;
    IData/*31:0*/ cpu_v1__DOT__EXU_inst0__DOT__add_2;
    IData/*31:0*/ cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__lut_out;
    IData/*31:0*/ cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result;
    IData/*31:0*/ cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out;
    IData/*19:0*/ __VdfgTmp_hfb3d7b8b__0;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*38:0*/, 2> cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list;
    VlUnpacked<CData/*6:0*/, 2> cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list;
    VlUnpacked<IData/*31:0*/, 2> cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list;
    VlUnpacked<IData/*31:0*/, 32> cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf;
    VlUnpacked<SData/*9:0*/, 9> cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list;
    VlUnpacked<CData/*6:0*/, 9> cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list;
    VlUnpacked<CData/*2:0*/, 9> cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list;
    VlUnpacked<QData/*34:0*/, 6> cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list;
    VlUnpacked<CData/*2:0*/, 6> cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list;
    VlUnpacked<IData/*31:0*/, 6> cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list;
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

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
