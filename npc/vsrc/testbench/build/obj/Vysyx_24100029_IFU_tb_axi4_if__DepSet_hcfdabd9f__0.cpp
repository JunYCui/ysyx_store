// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb_axi4_if.h"

VL_INLINE_OPT void Vysyx_24100029_IFU_tb_axi4_if___nba_sequent__TOP__ysyx_24100029_IFU_tb__DOT__bus__0(Vysyx_24100029_IFU_tb_axi4_if* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vysyx_24100029_IFU_tb_axi4_if___nba_sequent__TOP__ysyx_24100029_IFU_tb__DOT__bus__0\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vdly__arvalid = vlSelfRef.arvalid;
}

VL_INLINE_OPT void Vysyx_24100029_IFU_tb_axi4_if___nba_sequent__TOP__ysyx_24100029_IFU_tb__DOT__bus__1(Vysyx_24100029_IFU_tb_axi4_if* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vysyx_24100029_IFU_tb_axi4_if___nba_sequent__TOP__ysyx_24100029_IFU_tb__DOT__bus__1\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.arvalid = vlSelfRef.__Vdly__arvalid;
}

std::string VL_TO_STRING(const Vysyx_24100029_IFU_tb_axi4_if* obj) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vysyx_24100029_IFU_tb_axi4_if::VL_TO_STRING\n"); );
    // Body
    return (obj ? obj->name() : "null");
}
