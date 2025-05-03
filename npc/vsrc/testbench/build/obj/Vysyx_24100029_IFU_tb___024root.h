// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#ifndef VERILATED_VYSYX_24100029_IFU_TB___024ROOT_H_
#define VERILATED_VYSYX_24100029_IFU_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"
class Vysyx_24100029_IFU_tb_axi4_if;


class Vysyx_24100029_IFU_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vysyx_24100029_IFU_tb___024root final : public VerilatedModule {
  public:
    // CELLS
    Vysyx_24100029_IFU_tb_axi4_if* __PVT__ysyx_24100029_IFU_tb__DOT__bus;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__clock;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__reset;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__dnpc_valid;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__icache_clr;
        CData/*3:0*/ ysyx_24100029_IFU_tb__DOT__inst_ren;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__clr;
        CData/*3:0*/ ysyx_24100029_IFU_tb__DOT__inst_count;
        CData/*3:0*/ ysyx_24100029_IFU_tb__DOT__ready;
        CData/*7:0*/ ysyx_24100029_IFU_tb__DOT__count;
        CData/*1:0*/ ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state;
        CData/*7:0*/ ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len;
        CData/*2:0*/ ysyx_24100029_IFU_tb__DOT__u_mem__DOT__size;
        CData/*1:0*/ ysyx_24100029_IFU_tb__DOT__u_mem__DOT__burst;
        CData/*7:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_arready;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rready;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rvalid;
        CData/*3:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count;
        CData/*3:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren;
        CData/*3:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr;
        CData/*3:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr;
        CData/*3:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_input;
        CData/*2:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_output;
        CData/*1:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high;
        CData/*1:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state;
        CData/*7:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count;
        CData/*0:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r;
        CData/*1:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r;
        CData/*0:0*/ __Vintraval_h8b266596__0;
        CData/*1:0*/ __Vintraval_hccf7d6cc__0;
        CData/*1:0*/ __Vintraval_hd0c4e517__0;
        CData/*1:0*/ __Vintraval_ha605b9ab__0;
        CData/*1:0*/ __Vintraval_heaba0568__0;
        CData/*1:0*/ __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state;
        CData/*0:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__clock__v0;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__clock__v0;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v0;
        CData/*1:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1;
        CData/*1:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2;
        CData/*1:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v0;
        CData/*1:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v0;
        CData/*0:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1;
        CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__ysyx_24100029_IFU_tb__DOT__clock__0;
        CData/*0:0*/ __VactContinue;
        IData/*31:0*/ ysyx_24100029_IFU_tb__DOT__dnpc;
        IData/*31:0*/ ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr;
        IData/*31:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc;
        VlWide<8>/*255:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst;
        IData/*31:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_npc_generate__DOT__snpc;
    };
    struct {
        IData/*31:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__i;
        IData/*31:0*/ ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT____Vlvbound_h03165672__0;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<IData/*31:0*/, 256> ysyx_24100029_IFU_tb__DOT__u_mem__DOT__rom;
        VlUnpacked<IData/*31:0*/, 8> ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i;
        VlUnpacked<IData/*31:0*/, 8> ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i;
        VlUnpacked<IData/*31:0*/, 16> ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo;
        VlUnpacked<IData/*31:0*/, 16> ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo;
        VlUnpacked<VlWide<9>/*282:0*/, 4> ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache;
        VlUnpacked<CData/*0:0*/, 6> __Vm_traceActivity;
    };
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h4530d8dd__0;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vysyx_24100029_IFU_tb__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vysyx_24100029_IFU_tb___024root(Vysyx_24100029_IFU_tb__Syms* symsp, const char* v__name);
    ~Vysyx_24100029_IFU_tb___024root();
    VL_UNCOPYABLE(Vysyx_24100029_IFU_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
