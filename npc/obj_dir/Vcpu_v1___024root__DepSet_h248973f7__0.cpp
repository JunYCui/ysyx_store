// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcpu_v1.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vcpu_v1___024root.h"

void Vcpu_v1___024root___ico_sequent__TOP__0(Vcpu_v1___024root* vlSelf);

void Vcpu_v1___024root___eval_ico(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vcpu_v1___024root___ico_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

void Vcpu_v1___024root___eval_act(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vcpu_v1___024root___nba_sequent__TOP__0(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*4:0*/ __Vdlyvdim0__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0;
    __Vdlyvdim0__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0 = 0;
    IData/*31:0*/ __Vdlyvval__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0;
    __Vdlyvval__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0 = 0;
    CData/*0:0*/ __Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0;
    __Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0 = 0;
    CData/*0:0*/ __Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v1;
    __Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v1 = 0;
    // Body
    __Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v1 = 0U;
    __Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0 = 0U;
    if (vlSelf->rst) {
        vlSelf->pc = ((0x80000005U == vlSelf->pc) ? 0x80000000U
                       : ((IData)(1U) + vlSelf->pc));
        __Vdlyvval__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0 
            = ((0x4000U & vlSelf->inst) ? ((0x2000U 
                                            & vlSelf->inst)
                                            ? 0U : 
                                           ((0x1000U 
                                             & vlSelf->inst)
                                             ? (vlSelf->rs1_bo 
                                                ^ vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2)
                                             : (vlSelf->rs1_bo 
                                                | vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2)))
                : ((0x2000U & vlSelf->inst) ? ((0x1000U 
                                                & vlSelf->inst)
                                                ? (vlSelf->rs1_bo 
                                                   & vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2)
                                                : ((IData)(1U) 
                                                   + 
                                                   (~ vlSelf->rs1_bo)))
                    : vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result));
        __Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0 = 1U;
        __Vdlyvdim0__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0 
            = (0x1fU & (vlSelf->inst >> 7U));
    } else {
        vlSelf->pc = 0x80000000U;
    }
    if ((1U & (~ (IData)(vlSelf->rst)))) {
        __Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v1 = 1U;
    }
    if (__Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0) {
        vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[__Vdlyvdim0__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0] 
            = __Vdlyvval__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v0;
    }
    if (__Vdlyvset__cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf__v1) {
        vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[0U] = 0U;
    }
    vlSelf->cpu_v1__DOT__rs2_value = vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf
        [(0x1fU & (vlSelf->inst >> 0x14U))];
    vlSelf->rs1_bo = vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf
        [(0x1fU & (vlSelf->inst >> 0xfU))];
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list[1U] 
        = vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf
        [(0x1fU & (vlSelf->inst >> 0x14U))];
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list[1U] 
        = (0x3300000000ULL | (QData)((IData)(vlSelf->cpu_v1__DOT__rs2_value)));
}

VL_INLINE_OPT void Vcpu_v1___024root___nba_sequent__TOP__1(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___nba_sequent__TOP__1\n"); );
    // Body
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__lut_out 
        = ((- (IData)(((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list
                       [0U]))) & vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list
           [0U]);
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__lut_out 
        = (vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__lut_out 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list
                          [1U]))) & vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list
              [1U]));
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2 = vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__lut_out;
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result 
        = (vlSelf->rs1_bo + ((1U & ((0x4000U & vlSelf->inst)
                                     ? (vlSelf->inst 
                                        >> 0xdU) : (IData)(
                                                           (0x1000U 
                                                            == 
                                                            (0x3000U 
                                                             & vlSelf->inst)))))
                              ? ((IData)(1U) + (~ vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2))
                              : vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2));
}

void Vcpu_v1___024root___eval_nba(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vcpu_v1___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        Vcpu_v1___024root___nba_sequent__TOP__1(vlSelf);
    }
}

void Vcpu_v1___024root___eval_triggers__ico(Vcpu_v1___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__ico(Vcpu_v1___024root* vlSelf);
#endif  // VL_DEBUG
void Vcpu_v1___024root___eval_triggers__act(Vcpu_v1___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__act(Vcpu_v1___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__nba(Vcpu_v1___024root* vlSelf);
#endif  // VL_DEBUG

void Vcpu_v1___024root___eval(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vcpu_v1___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vcpu_v1___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("vsrc/cpu_v1.v", 4, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vcpu_v1___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vcpu_v1___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vcpu_v1___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("vsrc/cpu_v1.v", 4, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vcpu_v1___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vcpu_v1___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("vsrc/cpu_v1.v", 4, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vcpu_v1___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vcpu_v1___024root___eval_debug_assertions(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
