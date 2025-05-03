// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb___024root.h"

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___eval_initial__TOP(Vysyx_24100029_IFU_tb___024root* vlSelf);
VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__0(Vysyx_24100029_IFU_tb___024root* vlSelf);
VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__1(Vysyx_24100029_IFU_tb___024root* vlSelf);
VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2(Vysyx_24100029_IFU_tb___024root* vlSelf);
VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__3(Vysyx_24100029_IFU_tb___024root* vlSelf);
VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__4(Vysyx_24100029_IFU_tb___024root* vlSelf);

void Vysyx_24100029_IFU_tb___024root___eval_initial(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP(vlSelf);
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2(vlSelf);
    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__3(vlSelf);
    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__4(vlSelf);
}

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__0(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ ysyx_24100029_IFU_tb__DOT__unnamedblk1_1__DOT____Vrepeat0;
    ysyx_24100029_IFU_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    // Body
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__clock = 0U;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset = 1U;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__icache_clr = 0U;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__clr = 0U;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__dnpc = 0U;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__dnpc_valid = 0U;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__ready = 0xfU;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__count = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x2710ULL, 
                                         nullptr, "/home/cjy/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.sv", 
                                         64);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x2710ULL, 
                                         nullptr, "/home/cjy/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.sv", 
                                         65);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    ysyx_24100029_IFU_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0x64U;
    while (VL_LTS_III(32, 0U, ysyx_24100029_IFU_tb__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        if (VL_UNLIKELY((((3U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                          & ((2U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                             & ((1U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                                & (0U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)))))))) {
            VL_WRITEF_NX("--------- epoch: %3# ---------\ninst1_o = %x pc = %x \ninst2_o = %x pc = %x \ninst3_o = %x pc = %x \ninst4_o = %x pc = %x \n",0,
                         8,vlSelfRef.ysyx_24100029_IFU_tb__DOT__count,
                         32,vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                         [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr],
                         32,vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                         [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr],
                         32,vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                         [(0xfU & ((IData)(1U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))],
                         32,vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                         [(0xfU & ((IData)(1U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))],
                         32,vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                         [(0xfU & ((IData)(2U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))],
                         32,vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                         [(0xfU & ((IData)(2U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))],
                         32,vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                         [(0xfU & ((IData)(3U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))],
                         32,vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                         [(0xfU & ((IData)(3U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))]);
            vlSelfRef.ysyx_24100029_IFU_tb__DOT__count 
                = (0xffU & ((IData)(1U) + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__count)));
        }
        co_await vlSelfRef.__VdlySched.delay(0x2710ULL, 
                                             nullptr, 
                                             "/home/cjy/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.sv", 
                                             75);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        ysyx_24100029_IFU_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (ysyx_24100029_IFU_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    VL_FINISH_MT("/home/cjy/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.sv", 78, "");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
}

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__1(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VdlySched.delay(0x1388ULL, 
                                             nullptr, 
                                             "/home/cjy/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.sv", 
                                             82);
        vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__clock__v0 
            = (1U & (~ (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__clock)));
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__clock__v0 = 1U;
    }
}

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_5__1(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_5__1\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "/home/cjy/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.sv", 
                                         130);
    vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3 
        = vlSelfRef.__Vintraval_heaba0568__0;
    vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3 = 1U;
}

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_4__1(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_4__1\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "/home/cjy/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.sv", 
                                         135);
    vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2 
        = vlSelfRef.__Vintraval_ha605b9ab__0;
    vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2 = 1U;
}

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_3__1(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__2____Vfork_3__1\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "/home/cjy/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.sv", 
                                         133);
    vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1 
        = vlSelfRef.__Vintraval_hd0c4e517__0;
    vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1 = 1U;
}

VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__3____Vfork_2__1(Vysyx_24100029_IFU_tb___024root* vlSelf);

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__3(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__3\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VtrigSched_h4530d8dd__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge ysyx_24100029_IFU_tb.clock)", 
                                                             "/home/cjy/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.sv", 
                                                             112);
        if (vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset) {
            vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v0 = 1U;
        } else if ((0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))) {
            vlSelfRef.__Vintraval_hccf7d6cc__0 = (3U 
                                                  & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                     >> 4U));
            Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__3____Vfork_2__1(vlSelf);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__3____Vfork_2__1(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__3____Vfork_2__1\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "/home/cjy/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.sv", 
                                         114);
    vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1 
        = vlSelfRef.__Vintraval_hccf7d6cc__0;
    vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1 = 1U;
}

VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_1__1(Vysyx_24100029_IFU_tb___024root* vlSelf);

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__4(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__4\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (1U) {
        co_await vlSelfRef.__VtrigSched_h4530d8dd__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge ysyx_24100029_IFU_tb.clock)", 
                                                             "/home/cjy/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.sv", 
                                                             107);
        if (vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset) {
            vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v0 = 1U;
        } else if ((0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))) {
            vlSelfRef.__Vintraval_h8b266596__0 = (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                                                  [
                                                  (3U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 4U))][0U] 
                                                  & ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 6U) 
                                                     == 
                                                     (0x3ffffffU 
                                                      & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                                                         [
                                                         (3U 
                                                          & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                             >> 4U))][0U] 
                                                         >> 1U))));
            Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_1__1(vlSelf);
        }
    }
}

VL_INLINE_OPT VlCoroutine Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_1__1(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP__Vtiming__4____Vfork_1__1\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x3e8ULL, 
                                         nullptr, "/home/cjy/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.sv", 
                                         109);
    vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1 
        = vlSelfRef.__Vintraval_h8b266596__0;
    vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1 = 1U;
}

void Vysyx_24100029_IFU_tb___024root___act_sequent__TOP__0(Vysyx_24100029_IFU_tb___024root* vlSelf);

void Vysyx_24100029_IFU_tb___024root___eval_act(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_act\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        Vysyx_24100029_IFU_tb___024root___act_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
}

VL_INLINE_OPT void Vysyx_24100029_IFU_tb___024root___act_sequent__TOP__0(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___act_sequent__TOP__0\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__ready) 
           & ((((3U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                << 3U) | ((2U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                          << 2U)) | (((1U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                                      << 1U) | (0U 
                                                < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_output 
        = (7U & ((3U & ((1U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren)) 
                        + VL_SHIFTR_III(2,2,32, (3U 
                                                 & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren)), 1U))) 
                 + (3U & ((1U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                 >> 2U)) + VL_SHIFTR_III(2,2,32, 
                                                         (3U 
                                                          & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                                             >> 2U)), 1U)))));
}

VL_INLINE_OPT void Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__2(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__2\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__clock__v0) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__clock__v0 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__clock 
            = vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__clock__v0;
    }
}

VL_INLINE_OPT void Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__3(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___nba_sequent__TOP__3\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v0) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v0 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r = 0U;
    }
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r 
            = vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1;
    }
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v0) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v0 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r = 0U;
    }
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r 
            = vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1;
    }
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v0) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v0 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state = 0U;
    }
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state 
            = vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1;
    }
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state 
            = vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2;
    }
    if (vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3) {
        vlSelfRef.__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3 = 0U;
        vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state 
            = vlSelfRef.__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3;
    }
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rvalid 
        = (3U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_arready 
        = (0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state));
}

VL_INLINE_OPT void Vysyx_24100029_IFU_tb___024root___nba_comb__TOP__0(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___nba_comb__TOP__0\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__ready) 
           & ((((3U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                << 3U) | ((2U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                          << 2U)) | (((1U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                                      << 1U) | (0U 
                                                < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[0U] 
        = ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
            [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][1U] 
            << 5U) | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                      [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][0U] 
                      >> 0x1bU));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[1U] 
        = ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
            [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][2U] 
            << 5U) | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                      [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][1U] 
                      >> 0x1bU));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[2U] 
        = ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
            [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][3U] 
            << 5U) | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                      [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][2U] 
                      >> 0x1bU));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[3U] 
        = ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
            [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][4U] 
            << 5U) | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                      [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][3U] 
                      >> 0x1bU));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[4U] 
        = ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
            [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][5U] 
            << 5U) | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                      [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][4U] 
                      >> 0x1bU));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[5U] 
        = ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
            [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][6U] 
            << 5U) | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                      [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][5U] 
                      >> 0x1bU));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[6U] 
        = ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
            [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][7U] 
            << 5U) | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                      [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][6U] 
                      >> 0x1bU));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[7U] 
        = ((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
            [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][8U] 
            << 5U) | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                      [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r][7U] 
                      >> 0x1bU));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low 
        = ((3U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state)) 
           & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rready));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_output 
        = (7U & ((3U & ((1U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren)) 
                        + VL_SHIFTR_III(2,2,32, (3U 
                                                 & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren)), 1U))) 
                 + (3U & ((1U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                 >> 2U)) + VL_SHIFTR_III(2,2,32, 
                                                         (3U 
                                                          & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                                             >> 2U)), 1U)))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[0U] 
        = (((0U == (0x1fU & VL_SHIFTL_III(8,8,32, ((IData)(8U) 
                                                   - 
                                                   (0xfU 
                                                    & ((IData)(8U) 
                                                       - 
                                                       (7U 
                                                        & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                           >> 2U))))), 5U)))
             ? 0U : (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
                     (((IData)(0x1fU) + (0xffU & VL_SHIFTL_III(8,8,32, 
                                                               ((IData)(8U) 
                                                                - 
                                                                (0xfU 
                                                                 & ((IData)(8U) 
                                                                    - 
                                                                    (7U 
                                                                     & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                        >> 2U))))), 5U))) 
                      >> 5U)] << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                         ((IData)(8U) 
                                                          - 
                                                          (0xfU 
                                                           & ((IData)(8U) 
                                                              - 
                                                              (7U 
                                                               & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                  >> 2U))))), 5U))))) 
           | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
              (7U & (VL_SHIFTL_III(8,8,32, ((IData)(8U) 
                                            - (0xfU 
                                               & ((IData)(8U) 
                                                  - 
                                                  (7U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 2U))))), 5U) 
                     >> 5U))] >> (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                        ((IData)(8U) 
                                                         - 
                                                         (0xfU 
                                                          & ((IData)(8U) 
                                                             - 
                                                             (7U 
                                                              & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                 >> 2U))))), 5U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[1U] 
        = (((0U == (0x1fU & VL_SHIFTL_III(8,8,32, ((IData)(9U) 
                                                   - 
                                                   (0xfU 
                                                    & ((IData)(8U) 
                                                       - 
                                                       (7U 
                                                        & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                           >> 2U))))), 5U)))
             ? 0U : (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
                     (((IData)(0x1fU) + (0xffU & VL_SHIFTL_III(8,8,32, 
                                                               ((IData)(9U) 
                                                                - 
                                                                (0xfU 
                                                                 & ((IData)(8U) 
                                                                    - 
                                                                    (7U 
                                                                     & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                        >> 2U))))), 5U))) 
                      >> 5U)] << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                         ((IData)(9U) 
                                                          - 
                                                          (0xfU 
                                                           & ((IData)(8U) 
                                                              - 
                                                              (7U 
                                                               & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                  >> 2U))))), 5U))))) 
           | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
              (7U & (VL_SHIFTL_III(8,8,32, ((IData)(9U) 
                                            - (0xfU 
                                               & ((IData)(8U) 
                                                  - 
                                                  (7U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 2U))))), 5U) 
                     >> 5U))] >> (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                        ((IData)(9U) 
                                                         - 
                                                         (0xfU 
                                                          & ((IData)(8U) 
                                                             - 
                                                             (7U 
                                                              & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                 >> 2U))))), 5U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[2U] 
        = (((0U == (0x1fU & VL_SHIFTL_III(8,8,32, ((IData)(0xaU) 
                                                   - 
                                                   (0xfU 
                                                    & ((IData)(8U) 
                                                       - 
                                                       (7U 
                                                        & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                           >> 2U))))), 5U)))
             ? 0U : (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
                     (((IData)(0x1fU) + (0xffU & VL_SHIFTL_III(8,8,32, 
                                                               ((IData)(0xaU) 
                                                                - 
                                                                (0xfU 
                                                                 & ((IData)(8U) 
                                                                    - 
                                                                    (7U 
                                                                     & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                        >> 2U))))), 5U))) 
                      >> 5U)] << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                         ((IData)(0xaU) 
                                                          - 
                                                          (0xfU 
                                                           & ((IData)(8U) 
                                                              - 
                                                              (7U 
                                                               & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                  >> 2U))))), 5U))))) 
           | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
              (7U & (VL_SHIFTL_III(8,8,32, ((IData)(0xaU) 
                                            - (0xfU 
                                               & ((IData)(8U) 
                                                  - 
                                                  (7U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 2U))))), 5U) 
                     >> 5U))] >> (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                        ((IData)(0xaU) 
                                                         - 
                                                         (0xfU 
                                                          & ((IData)(8U) 
                                                             - 
                                                             (7U 
                                                              & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                 >> 2U))))), 5U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[3U] 
        = (((0U == (0x1fU & VL_SHIFTL_III(8,8,32, ((IData)(0xbU) 
                                                   - 
                                                   (0xfU 
                                                    & ((IData)(8U) 
                                                       - 
                                                       (7U 
                                                        & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                           >> 2U))))), 5U)))
             ? 0U : (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
                     (((IData)(0x1fU) + (0xffU & VL_SHIFTL_III(8,8,32, 
                                                               ((IData)(0xbU) 
                                                                - 
                                                                (0xfU 
                                                                 & ((IData)(8U) 
                                                                    - 
                                                                    (7U 
                                                                     & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                        >> 2U))))), 5U))) 
                      >> 5U)] << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                         ((IData)(0xbU) 
                                                          - 
                                                          (0xfU 
                                                           & ((IData)(8U) 
                                                              - 
                                                              (7U 
                                                               & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                  >> 2U))))), 5U))))) 
           | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
              (7U & (VL_SHIFTL_III(8,8,32, ((IData)(0xbU) 
                                            - (0xfU 
                                               & ((IData)(8U) 
                                                  - 
                                                  (7U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 2U))))), 5U) 
                     >> 5U))] >> (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                        ((IData)(0xbU) 
                                                         - 
                                                         (0xfU 
                                                          & ((IData)(8U) 
                                                             - 
                                                             (7U 
                                                              & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                 >> 2U))))), 5U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[4U] 
        = (((0U == (0x1fU & VL_SHIFTL_III(8,8,32, ((IData)(0xcU) 
                                                   - 
                                                   (0xfU 
                                                    & ((IData)(8U) 
                                                       - 
                                                       (7U 
                                                        & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                           >> 2U))))), 5U)))
             ? 0U : (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
                     (((IData)(0x1fU) + (0xffU & VL_SHIFTL_III(8,8,32, 
                                                               ((IData)(0xcU) 
                                                                - 
                                                                (0xfU 
                                                                 & ((IData)(8U) 
                                                                    - 
                                                                    (7U 
                                                                     & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                        >> 2U))))), 5U))) 
                      >> 5U)] << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                         ((IData)(0xcU) 
                                                          - 
                                                          (0xfU 
                                                           & ((IData)(8U) 
                                                              - 
                                                              (7U 
                                                               & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                  >> 2U))))), 5U))))) 
           | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
              (7U & (VL_SHIFTL_III(8,8,32, ((IData)(0xcU) 
                                            - (0xfU 
                                               & ((IData)(8U) 
                                                  - 
                                                  (7U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 2U))))), 5U) 
                     >> 5U))] >> (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                        ((IData)(0xcU) 
                                                         - 
                                                         (0xfU 
                                                          & ((IData)(8U) 
                                                             - 
                                                             (7U 
                                                              & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                 >> 2U))))), 5U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[5U] 
        = (((0U == (0x1fU & VL_SHIFTL_III(8,8,32, ((IData)(0xdU) 
                                                   - 
                                                   (0xfU 
                                                    & ((IData)(8U) 
                                                       - 
                                                       (7U 
                                                        & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                           >> 2U))))), 5U)))
             ? 0U : (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
                     (((IData)(0x1fU) + (0xffU & VL_SHIFTL_III(8,8,32, 
                                                               ((IData)(0xdU) 
                                                                - 
                                                                (0xfU 
                                                                 & ((IData)(8U) 
                                                                    - 
                                                                    (7U 
                                                                     & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                        >> 2U))))), 5U))) 
                      >> 5U)] << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                         ((IData)(0xdU) 
                                                          - 
                                                          (0xfU 
                                                           & ((IData)(8U) 
                                                              - 
                                                              (7U 
                                                               & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                  >> 2U))))), 5U))))) 
           | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
              (7U & (VL_SHIFTL_III(8,8,32, ((IData)(0xdU) 
                                            - (0xfU 
                                               & ((IData)(8U) 
                                                  - 
                                                  (7U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 2U))))), 5U) 
                     >> 5U))] >> (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                        ((IData)(0xdU) 
                                                         - 
                                                         (0xfU 
                                                          & ((IData)(8U) 
                                                             - 
                                                             (7U 
                                                              & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                 >> 2U))))), 5U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[6U] 
        = (((0U == (0x1fU & VL_SHIFTL_III(8,8,32, ((IData)(0xeU) 
                                                   - 
                                                   (0xfU 
                                                    & ((IData)(8U) 
                                                       - 
                                                       (7U 
                                                        & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                           >> 2U))))), 5U)))
             ? 0U : (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
                     (((IData)(0x1fU) + (0xffU & VL_SHIFTL_III(8,8,32, 
                                                               ((IData)(0xeU) 
                                                                - 
                                                                (0xfU 
                                                                 & ((IData)(8U) 
                                                                    - 
                                                                    (7U 
                                                                     & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                        >> 2U))))), 5U))) 
                      >> 5U)] << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                         ((IData)(0xeU) 
                                                          - 
                                                          (0xfU 
                                                           & ((IData)(8U) 
                                                              - 
                                                              (7U 
                                                               & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                  >> 2U))))), 5U))))) 
           | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
              (7U & (VL_SHIFTL_III(8,8,32, ((IData)(0xeU) 
                                            - (0xfU 
                                               & ((IData)(8U) 
                                                  - 
                                                  (7U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 2U))))), 5U) 
                     >> 5U))] >> (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                        ((IData)(0xeU) 
                                                         - 
                                                         (0xfU 
                                                          & ((IData)(8U) 
                                                             - 
                                                             (7U 
                                                              & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                 >> 2U))))), 5U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[7U] 
        = (((0U == (0x1fU & VL_SHIFTL_III(8,8,32, ((IData)(0xfU) 
                                                   - 
                                                   (0xfU 
                                                    & ((IData)(8U) 
                                                       - 
                                                       (7U 
                                                        & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                           >> 2U))))), 5U)))
             ? 0U : (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
                     (((IData)(0x1fU) + (0xffU & VL_SHIFTL_III(8,8,32, 
                                                               ((IData)(0xfU) 
                                                                - 
                                                                (0xfU 
                                                                 & ((IData)(8U) 
                                                                    - 
                                                                    (7U 
                                                                     & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                        >> 2U))))), 5U))) 
                      >> 5U)] << ((IData)(0x20U) - 
                                  (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                         ((IData)(0xfU) 
                                                          - 
                                                          (0xfU 
                                                           & ((IData)(8U) 
                                                              - 
                                                              (7U 
                                                               & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                  >> 2U))))), 5U))))) 
           | (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst[
              (7U & (VL_SHIFTL_III(8,8,32, ((IData)(0xfU) 
                                            - (0xfU 
                                               & ((IData)(8U) 
                                                  - 
                                                  (7U 
                                                   & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                      >> 2U))))), 5U) 
                     >> 5U))] >> (0x1fU & VL_SHIFTL_III(8,8,32, 
                                                        ((IData)(0xfU) 
                                                         - 
                                                         (0xfU 
                                                          & ((IData)(8U) 
                                                             - 
                                                             (7U 
                                                              & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                 >> 2U))))), 5U))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in 
        = ((((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
             & (1U < (0xfU & ((IData)(8U) - (7U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                   >> 2U)))))) 
            << 1U) | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
           & (2U < (0xfU & ((IData)(8U) - (7U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                 >> 2U))))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
           & (3U < (0xfU & ((IData)(8U) - (7U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                 >> 2U))))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
           & (4U < (0xfU & ((IData)(8U) - (7U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                 >> 2U))))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
           & (5U < (0xfU & ((IData)(8U) - (7U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                 >> 2U))))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
           & (6U < (0xfU & ((IData)(8U) - (7U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                 >> 2U))))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
           & (7U < (0xfU & ((IData)(8U) - (7U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                 >> 2U))))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen 
        = (((((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
              << 7U) | ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                        << 6U)) | (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high) 
                                    << 5U) | ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
                                              << 4U))) 
           | (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
               << 3U) | (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                          << 2U) | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in))));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_input 
        = (0xfU & ((7U & ((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
                                 + VL_SHIFTR_III(2,2,32, (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in), 1U))) 
                          + (3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                                   + VL_SHIFTR_III(2,2,32, 
                                                   (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                                     << 1U) 
                                                    | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low)), 1U))))) 
                   + (7U & ((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
                                   + VL_SHIFTR_III(2,2,32, 
                                                   (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high) 
                                                     << 1U) 
                                                    | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low)), 1U))) 
                            + (3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                                     + VL_SHIFTR_III(2,2,32, 
                                                     (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                                       << 1U) 
                                                      | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low)), 1U)))))));
}

void Vysyx_24100029_IFU_tb___024root___timing_resume(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___timing_resume\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VtrigSched_h4530d8dd__0.resume(
                                                   "@(posedge ysyx_24100029_IFU_tb.clock)");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vysyx_24100029_IFU_tb___024root___timing_commit(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___timing_commit\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((! (1ULL & vlSelfRef.__VactTriggered.word(0U)))) {
        vlSelfRef.__VtrigSched_h4530d8dd__0.commit(
                                                   "@(posedge ysyx_24100029_IFU_tb.clock)");
    }
}

void Vysyx_24100029_IFU_tb___024root___eval_triggers__act(Vysyx_24100029_IFU_tb___024root* vlSelf);

bool Vysyx_24100029_IFU_tb___024root___eval_phase__act(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_phase__act\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vysyx_24100029_IFU_tb___024root___eval_triggers__act(vlSelf);
    Vysyx_24100029_IFU_tb___024root___timing_commit(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vysyx_24100029_IFU_tb___024root___timing_resume(vlSelf);
        Vysyx_24100029_IFU_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

void Vysyx_24100029_IFU_tb___024root___eval_nba(Vysyx_24100029_IFU_tb___024root* vlSelf);

bool Vysyx_24100029_IFU_tb___024root___eval_phase__nba(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_phase__nba\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vysyx_24100029_IFU_tb___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___dump_triggers__nba(Vysyx_24100029_IFU_tb___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___dump_triggers__act(Vysyx_24100029_IFU_tb___024root* vlSelf);
#endif  // VL_DEBUG

void Vysyx_24100029_IFU_tb___024root___eval(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vysyx_24100029_IFU_tb___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/home/cjy/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.sv", 27, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vysyx_24100029_IFU_tb___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/home/cjy/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.sv", 27, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vysyx_24100029_IFU_tb___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vysyx_24100029_IFU_tb___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vysyx_24100029_IFU_tb___024root___eval_debug_assertions(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_debug_assertions\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
