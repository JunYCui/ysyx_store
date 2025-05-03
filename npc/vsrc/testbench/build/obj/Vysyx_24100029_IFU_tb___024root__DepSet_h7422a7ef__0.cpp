// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb__Syms.h"
#include "Vysyx_24100029_IFU_tb___024root.h"

VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_3__1(Vysyx_24100029_IFU_tb___024root* vlSelf);
VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_4__1(Vysyx_24100029_IFU_tb___024root* vlSelf);
VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_5__1(Vysyx_24100029_IFU_tb___024root* vlSelf);

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VtrigSched_h4530d8dd__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge ysyx_24100029_IFU_tb.clock)", 
                                                             "/home/cjy/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.sv", 
                                                             119);
        if (vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset) {
            vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v0 = 1U;
        } else if ((2U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))) {
                if (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rready) 
                     & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rvalid))) {
                    vlSelfRef.__Vintraval_hd0c4e517__0 = 0U;
                    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_3__1(vlSelf);
                }
            } else {
                vlSelfRef.__Vintraval_ha605b9ab__0 
                    = (((IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rlast) 
                        & (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid))
                        ? 3U : 2U);
                Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_4__1(vlSelf);
            }
        } else {
            vlSelfRef.__Vintraval_heaba0568__0 = ((1U 
                                                   & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))
                                                   ? 
                                                  ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r)
                                                    ? 3U
                                                    : 2U)
                                                   : 
                                                  ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_arready)
                                                    ? 1U
                                                    : 0U));
            Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_5__1(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___dump_triggers__act(Vysyx_24100029_IFU_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vysyx_24100029_IFU_tb___024root___eval_triggers__act(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_triggers__act\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.setBit(0U, ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__clock) 
                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__ysyx_24100029_IFU_tb__DOT__clock__0))));
    vlSelfRef.__VactTriggered.setBit(1U, vlSelfRef.__VdlySched.awaitingCurrentTime());
    vlSelfRef.__Vtrigprevexpr___TOP__ysyx_24100029_IFU_tb__DOT__clock__0 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vysyx_24100029_IFU_tb___024root___dump_triggers__act(vlSelf);
    }
#endif
}

void Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__0(Vysyx_24100029_IFU_tb___024root* vlSelf);
void Vysyx_24100029_IFU_tb_axi4_if___nba_sequent__TOP__ysyx_24100029_IFU_tb__DOT__bus__0(Vysyx_24100029_IFU_tb_axi4_if* vlSelf);
void Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__1(Vysyx_24100029_IFU_tb___024root* vlSelf);
void Vysyx_24100029_IFU_tb_axi4_if___nba_sequent__TOP__ysyx_24100029_IFU_tb__DOT__bus__1(Vysyx_24100029_IFU_tb_axi4_if* vlSelf);
void Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__2(Vysyx_24100029_IFU_tb___024root* vlSelf);
void Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__3(Vysyx_24100029_IFU_tb___024root* vlSelf);
void Vysyx_24100029_IFU_tb___024root___nba_comb__TOP__0(Vysyx_24100029_IFU_tb___024root* vlSelf);

void Vysyx_24100029_IFU_tb___024root___eval_nba(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_nba\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[4U] = 1U;
        Vysyx_24100029_IFU_tb_axi4_if___nba_sequent__TOP__ysyx_24100029_IFU_tb__DOT__bus__0((&vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus));
        Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__1(vlSelf);
        Vysyx_24100029_IFU_tb_axi4_if___nba_sequent__TOP__ysyx_24100029_IFU_tb__DOT__bus__1((&vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus));
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__3(vlSelf);
        vlSelfRef.__Vm_traceActivity[5U] = 1U;
        Vysyx_24100029_IFU_tb___024root___nba_comb__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*1:0*/, 256> Vysyx_24100029_IFU_tb__ConstPool__TABLE_h1c5fe291_0;

VL_INLINE_OPT void Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__0(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__0\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*7:0*/ __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len = 0;
    IData/*31:0*/ __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr = 0;
    CData/*3:0*/ __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr = 0;
    CData/*3:0*/ __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr = 0;
    CData/*3:0*/ __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count = 0;
    CData/*7:0*/ __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7 = 0;
    CData/*3:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v0;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v0 = 0;
    IData/*26:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4 = 0;
    CData/*1:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4 = 0;
    IData/*31:0*/ __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5;
    __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 = 0;
    SData/*8:0*/ __VdlyLsb__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5;
    __VdlyLsb__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 = 0;
    CData/*1:0*/ __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5;
    __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 = 0;
    CData/*0:0*/ __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 = 0;
    // Body
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7 = 0U;
    vlSelfRef.__Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count;
    __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v0 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4 = 0U;
    __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 = 0U;
    if (vlSelfRef.ysyx_24100029_IFU_tb__DOT__clr) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__i = 4U;
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v0 = 1U;
    } else if ((0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))) {
        __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4 
            = (1U | (0x7fffffeU & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                   >> 5U)));
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4 
            = (3U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                     >> 4U));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4 = 1U;
    } else if (vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT____Vlvbound_h03165672__0 
            = ((8U == (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
                       >> 0x1cU)) ? vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__rom
               [(0xffU & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
                          >> 2U))] : 0U);
        if ((0x11aU >= (0x1ffU & ((IData)(0x1bU) + 
                                  VL_SHIFTL_III(9,32,32, (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count), 5U))))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT____Vlvbound_h03165672__0;
            __VdlyLsb__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 
                = (0x1ffU & ((IData)(0x1bU) + VL_SHIFTL_III(9,32,32, (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count), 5U)));
            __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r;
            __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5 = 1U;
        }
    }
    if (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset) 
         | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__dnpc_valid))) {
        __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr = 0U;
        __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr = 0U;
        __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count = 0U;
    } else {
        if ((0U != (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren))) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr 
                = (0xfU & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr) 
                           + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_output)));
        }
        if ((0U != (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr 
                = (0xfU & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr) 
                           + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_input)));
        }
        if (((0U != (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen)) 
             | (0U != (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren)))) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count 
                = (0xfU & (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count) 
                            + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_input)) 
                           - (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_output)));
        }
    }
    if (vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset) {
        __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count = 0U;
        __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len = 0U;
        __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__burst = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__size = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc = 0x80000000U;
    } else {
        if (((1U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state)) 
             & (~ (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r)))) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count = 0U;
        } else if (vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count 
                = (0xffU & ((IData)(1U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count)));
        }
        if (((((0U != (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)) 
               & (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid)) 
              & (2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))) 
             & (~ (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rlast)))) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len 
                = (0xffU & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len) 
                            - (IData)(1U)));
        } else if (((IData)((0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state))) 
                    & (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arvalid))) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len = 7U;
        }
        if (((((1U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__burst)) 
               & (0U != (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state))) 
              & (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid)) 
             & (2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state)))) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
                = (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
                   + VL_POWSS_III(32,32,3, (IData)(2U), (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__size), 1,0));
        } else if (((IData)((0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state))) 
                    & (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arvalid))) {
            __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
                = (0xfffffff0U & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc);
        }
        if ((1U & (~ ((((0U != (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)) 
                        & (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid)) 
                       & (2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))) 
                      & (~ (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rlast)))))) {
            if (((IData)((0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state))) 
                 & (IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arvalid))) {
                vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__burst = 1U;
                vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__size = 2U;
            }
        }
        if (vlSelfRef.ysyx_24100029_IFU_tb__DOT__dnpc_valid) {
            vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__dnpc;
        } else if (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) {
            vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_npc_generate__DOT__snpc;
        }
    }
    if ((0U != (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
        if ((1U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i
                [0U];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i
                [0U];
        } else {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr];
        }
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0 
            = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr;
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0 = 1U;
        if ((2U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i
                [1U];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i
                [1U];
        } else {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                [(0xfU & ((IData)(1U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                [(0xfU & ((IData)(1U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
        }
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1 
            = (0xfU & ((IData)(1U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1 = 1U;
        if ((4U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i
                [2U];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i
                [2U];
        } else {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                [(0xfU & ((IData)(2U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                [(0xfU & ((IData)(2U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
        }
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2 
            = (0xfU & ((IData)(2U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2 = 1U;
        if ((8U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i
                [3U];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i
                [3U];
        } else {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                [(0xfU & ((IData)(3U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                [(0xfU & ((IData)(3U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
        }
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3 
            = (0xfU & ((IData)(3U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3 = 1U;
        if ((0x10U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i
                [4U];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i
                [4U];
        } else {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                [(0xfU & ((IData)(4U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                [(0xfU & ((IData)(4U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
        }
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4 
            = (0xfU & ((IData)(4U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4 = 1U;
        if ((0x20U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i
                [5U];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i
                [5U];
        } else {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                [(0xfU & ((IData)(5U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                [(0xfU & ((IData)(5U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
        }
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5 
            = (0xfU & ((IData)(5U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5 = 1U;
        if ((0x40U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i
                [6U];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i
                [6U];
        } else {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                [(0xfU & ((IData)(6U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                [(0xfU & ((IData)(6U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
        }
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6 
            = (0xfU & ((IData)(6U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6 = 1U;
        if ((0x80U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen))) {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i
                [7U];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i
                [7U];
        } else {
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                [(0xfU & ((IData)(7U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
            __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7 
                = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                [(0xfU & ((IData)(7U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)))];
        }
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7 
            = (0xfU & ((IData)(7U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7 = 1U;
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0 
            = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr;
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0 = 1U;
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1 
            = (0xfU & ((IData)(1U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1 = 1U;
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2 
            = (0xfU & ((IData)(2U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2 = 1U;
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3 
            = (0xfU & ((IData)(3U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3 = 1U;
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4 
            = (0xfU & ((IData)(4U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4 = 1U;
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5 
            = (0xfU & ((IData)(5U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5 = 1U;
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6 
            = (0xfU & ((IData)(6U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6 = 1U;
        __VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7 
            = (0xfU & ((IData)(7U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr)));
        __VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7 = 1U;
    }
    __Vtableidx1 = (((((IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rlast) 
                       << 7U) | ((IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid) 
                                 << 6U)) | (((2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state)) 
                                             << 5U) 
                                            | ((IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arvalid) 
                                               << 4U))) 
                    | (((IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arready) 
                        << 3U) | (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state) 
                                   << 1U) | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset))));
    vlSelfRef.__Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state 
        = Vysyx_24100029_IFU_tb__ConstPool__TABLE_h1c5fe291_0
        [__Vtableidx1];
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr 
        = __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len 
        = __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len;
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v0;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v1;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v2;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v3;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v4;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v5;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v6;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo__v7;
    }
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr 
        = __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr;
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v0;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v1;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v2;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v3;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v4;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v5;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v6;
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7] 
            = __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo__v7;
    }
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count 
        = __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
        = __Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count 
        = __Vdly__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count;
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v0) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[0U][0U] 
            = (0xfffffffeU & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
               [0U][0U]);
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[1U][0U] 
            = (0xfffffffeU & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
               [1U][0U]);
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[2U][0U] 
            = (0xfffffffeU & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
               [2U][0U]);
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[3U][0U] 
            = (0xfffffffeU & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
               [3U][0U]);
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4) {
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4][0U] 
            = ((0xf8000000U & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                [__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4][0U]) 
               | __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v4);
    }
    if (__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5) {
        VL_ASSIGNSEL_WI(283,32,(IData)(__VdlyLsb__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5), 
                        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                        [__VdlyDim0__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5], __VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache__v5);
    }
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_npc_generate__DOT__snpc 
        = (IData)((0x7ffffffffffffffULL & ((0U == (0x1fU 
                                                   & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc))
                                            ? (0x20ULL 
                                               + (QData)((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc)))
                                            : ((QData)((IData)(
                                                               (0x7ffffffU 
                                                                & ((IData)(1U) 
                                                                   + 
                                                                   (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                    >> 5U))))) 
                                               << 0x20U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[0U] 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[1U] 
        = ((IData)(4U) + vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc);
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[2U] 
        = ((IData)(8U) + vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc);
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[3U] 
        = ((IData)(0xcU) + vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc);
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[4U] 
        = ((IData)(0x10U) + vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc);
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[5U] 
        = ((IData)(0x14U) + vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc);
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[6U] 
        = ((IData)(0x18U) + vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc);
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[7U] 
        = ((IData)(0x1cU) + vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc);
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rready 
        = (0x21U > ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count) 
                    + (0xfU & ((IData)(8U) - (7U & 
                                              (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                               >> 2U))))));
}

VL_INLINE_OPT void Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__1(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__1\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset) {
        vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.__Vdly__arvalid = 0U;
    } else if (((1U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state)) 
                & (~ (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r)))) {
        vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.__Vdly__arvalid = 1U;
    } else if (((IData)(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arvalid) 
                & (0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)))) {
        vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.__Vdly__arvalid = 0U;
    }
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state 
        = vlSelfRef.__Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state;
    vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arready 
        = (0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state));
    vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid 
        = ((1U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)) 
           | (2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)));
    vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rlast 
        = (((1U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)) 
            | (2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state))) 
           & (0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len)));
}
