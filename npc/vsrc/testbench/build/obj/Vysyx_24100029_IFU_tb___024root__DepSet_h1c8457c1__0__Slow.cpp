// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb___024root.h"

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___eval_static(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_static\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__ysyx_24100029_IFU_tb__DOT__clock__0 
        = vlSelfRef.ysyx_24100029_IFU_tb__DOT__clock;
}

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___eval_initial__TOP(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_initial__TOP\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<3>/*95:0*/ __Vtemp_1;
    // Body
    __Vtemp_1[0U] = 0x2e686578U;
    __Vtemp_1[1U] = 0x2f726f6dU;
    __Vtemp_1[2U] = 0x64617461U;
    VL_READMEM_N(true, 32, 256, 0, VL_CVT_PACK_STR_NW(3, __Vtemp_1)
                 ,  &(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__rom)
                 , 0, ~0ULL);
}

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___eval_final(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_final\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___dump_triggers__stl(Vysyx_24100029_IFU_tb___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vysyx_24100029_IFU_tb___024root___eval_phase__stl(Vysyx_24100029_IFU_tb___024root* vlSelf);

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___eval_settle(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_settle\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vysyx_24100029_IFU_tb___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("/home/cjy/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.sv", 27, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vysyx_24100029_IFU_tb___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___dump_triggers__stl(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___dump_triggers__stl\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___stl_sequent__TOP__0(Vysyx_24100029_IFU_tb___024root* vlSelf);
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root____Vm_traceActivitySetAll(Vysyx_24100029_IFU_tb___024root* vlSelf);

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___eval_stl(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_stl\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vysyx_24100029_IFU_tb___024root___stl_sequent__TOP__0(vlSelf);
        Vysyx_24100029_IFU_tb___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___eval_triggers__stl(Vysyx_24100029_IFU_tb___024root* vlSelf);

VL_ATTR_COLD bool Vysyx_24100029_IFU_tb___024root___eval_phase__stl(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_phase__stl\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vysyx_24100029_IFU_tb___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vysyx_24100029_IFU_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___dump_triggers__act(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___dump_triggers__act\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge ysyx_24100029_IFU_tb.clock)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___dump_triggers__nba(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___dump_triggers__nba\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge ysyx_24100029_IFU_tb.clock)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root____Vm_traceActivitySetAll(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root____Vm_traceActivitySetAll\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    vlSelfRef.__Vm_traceActivity[3U] = 1U;
    vlSelfRef.__Vm_traceActivity[4U] = 1U;
    vlSelfRef.__Vm_traceActivity[5U] = 1U;
}

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___ctor_var_reset(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___ctor_var_reset\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->ysyx_24100029_IFU_tb__DOT__clock = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__reset = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__dnpc = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__dnpc_valid = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__icache_clr = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__inst_ren = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__clr = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__inst_count = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__ready = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__count = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state = 0;
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        vlSelf->ysyx_24100029_IFU_tb__DOT__u_mem__DOT__rom[__Vi0] = 0;
    }
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_mem__DOT__size = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_mem__DOT__burst = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc = 0;
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[__Vi0] = 0;
    }
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_arready = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rready = 0;
    VL_ZERO_RESET_W(256, vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst);
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rvalid = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_npc_generate__DOT__snpc = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr = 0;
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 16; ++__Vi0) {
        vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[__Vi0] = 0;
    }
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_input = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_output = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high = 0;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        VL_ZERO_RESET_W(283, vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[__Vi0]);
    }
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__i = 0;
    vlSelf->ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT____Vlvbound_h03165672__0 = 0;
    vlSelf->__Vintraval_h8b266596__0 = 0;
    vlSelf->__Vintraval_hccf7d6cc__0 = 0;
    vlSelf->__Vintraval_hd0c4e517__0 = 0;
    vlSelf->__Vintraval_ha605b9ab__0 = 0;
    vlSelf->__Vintraval_heaba0568__0 = 0;
    vlSelf->__Vdly__ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state = 0;
    vlSelf->__VdlyVal__ysyx_24100029_IFU_tb__DOT__clock__v0 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__clock__v0 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v0 = 0;
    vlSelf->__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v1 = 0;
    vlSelf->__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v2 = 0;
    vlSelf->__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state__v3 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v0 = 0;
    vlSelf->__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r__v1 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v0 = 0;
    vlSelf->__VdlyVal__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1 = 0;
    vlSelf->__VdlySet__ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r__v1 = 0;
    vlSelf->__Vtrigprevexpr___TOP__ysyx_24100029_IFU_tb__DOT__clock__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 6; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
