// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcpu_v1.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vcpu_v1___024root.h"

VL_ATTR_COLD void Vcpu_v1___024root___eval_static(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vcpu_v1___024root___eval_initial__TOP(Vcpu_v1___024root* vlSelf);

VL_ATTR_COLD void Vcpu_v1___024root___eval_initial(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_initial\n"); );
    // Body
    Vcpu_v1___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
}

VL_ATTR_COLD void Vcpu_v1___024root___eval_initial__TOP(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list[0U] = 0x13U;
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list[1U] = 0x33U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[0U] = 3U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[1U] = 4U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[2U] = 6U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[3U] = 5U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[4U] = 2U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[5U] = 1U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[5U] = 0U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[5U] = 0x100000000ULL;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[0U] = 0x17U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[1U] = 0x37U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[2U] = 0x67U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[3U] = 0x6fU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[4U] = 0x13U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[5U] = 3U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[6U] = 0x23U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[7U] = 0x63U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[8U] = 0x33U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[0U] = 5U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[1U] = 5U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[2U] = 6U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[3U] = 6U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[4U] = 2U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[5U] = 2U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[6U] = 3U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[7U] = 4U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[8U] = 1U;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[0U] = 0xbdU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[1U] = 0x1bdU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[2U] = 0x33eU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[3U] = 0x37eU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[4U] = 0x9aU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[5U] = 0x1aU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[6U] = 0x11bU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[7U] = 0x31cU;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[8U] = 0x199U;
}

VL_ATTR_COLD void Vcpu_v1___024root___eval_final(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vcpu_v1___024root___eval_triggers__stl(Vcpu_v1___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__stl(Vcpu_v1___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___eval_stl(Vcpu_v1___024root* vlSelf);

VL_ATTR_COLD void Vcpu_v1___024root___eval_settle(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        Vcpu_v1___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                Vcpu_v1___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("vsrc/cpu_v1.v", 4, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            Vcpu_v1___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__stl(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

void Vcpu_v1___024root___ico_sequent__TOP__0(Vcpu_v1___024root* vlSelf);

VL_ATTR_COLD void Vcpu_v1___024root___eval_stl(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        Vcpu_v1___024root___ico_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__ico(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VicoTriggered.at(0U)) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__act(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__nba(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcpu_v1___024root___ctor_var_reset(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->inst = VL_RAND_RESET_I(32);
    vlSelf->pc = VL_RAND_RESET_I(32);
    vlSelf->rs1_bo = VL_RAND_RESET_I(32);
    vlSelf->cpu_v1__DOT__imm = VL_RAND_RESET_I(32);
    vlSelf->cpu_v1__DOT__rs2_value = VL_RAND_RESET_I(32);
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2 = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list[__Vi0] = VL_RAND_RESET_Q(39);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list[__Vi0] = VL_RAND_RESET_I(7);
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__lut_out = VL_RAND_RESET_I(32);
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__hit = VL_RAND_RESET_I(1);
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type = VL_RAND_RESET_I(3);
    for (int __Vi0 = 0; __Vi0 < 9; ++__Vi0) {
        vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[__Vi0] = VL_RAND_RESET_I(10);
    }
    for (int __Vi0 = 0; __Vi0 < 9; ++__Vi0) {
        vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[__Vi0] = VL_RAND_RESET_I(7);
    }
    for (int __Vi0 = 0; __Vi0 < 9; ++__Vi0) {
        vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[__Vi0] = VL_RAND_RESET_I(3);
    }
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out = VL_RAND_RESET_I(3);
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 6; ++__Vi0) {
        vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[__Vi0] = VL_RAND_RESET_Q(35);
    }
    for (int __Vi0 = 0; __Vi0 < 6; ++__Vi0) {
        vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[__Vi0] = VL_RAND_RESET_I(3);
    }
    for (int __Vi0 = 0; __Vi0 < 6; ++__Vi0) {
        vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out = VL_RAND_RESET_I(32);
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit = VL_RAND_RESET_I(1);
    vlSelf->__VdfgTmp_h5152c62b__0 = 0;
    vlSelf->__VdfgTmp_hac3a854f__0 = 0;
    vlSelf->__VdfgTmp_hfb3d7b8b__0 = 0;
    vlSelf->__Vtrigrprev__TOP__clk = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
