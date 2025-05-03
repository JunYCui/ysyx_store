// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb_axi4_if.h"

VL_ATTR_COLD void Vysyx_24100029_IFU_tb_axi4_if___ctor_var_reset(Vysyx_24100029_IFU_tb_axi4_if* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+            Vysyx_24100029_IFU_tb_axi4_if___ctor_var_reset\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT__awready = 0;
    vlSelf->__PVT__wready = 0;
    vlSelf->__PVT__bid = 0;
    vlSelf->__PVT__bresp = 0;
    vlSelf->__PVT__bvalid = 0;
    vlSelf->arvalid = 0;
    vlSelf->arready = 0;
    vlSelf->__PVT__rid = 0;
    vlSelf->__PVT__rresp = 0;
    vlSelf->rlast = 0;
    vlSelf->rvalid = 0;
    vlSelf->__Vdly__arvalid = 0;
}
