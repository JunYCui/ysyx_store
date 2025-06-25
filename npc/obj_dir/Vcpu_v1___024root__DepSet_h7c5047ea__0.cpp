// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcpu_v1.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vcpu_v1__Syms.h"
#include "Vcpu_v1___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__ico(Vcpu_v1___024root* vlSelf);
#endif  // VL_DEBUG

void Vcpu_v1___024root___eval_triggers__ico(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.at(0U) = (0U == vlSelf->__VicoIterCount);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcpu_v1___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

void Vcpu_v1___024unit____Vdpiimwrap_fi_TOP____024unit();

VL_INLINE_OPT void Vcpu_v1___024root___ico_sequent__TOP__0(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___ico_sequent__TOP__0\n"); );
    // Body
    if ((0x100073U == vlSelf->inst)) {
        Vcpu_v1___024unit____Vdpiimwrap_fi_TOP____024unit();
    }
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__hit 
        = ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list
           [0U]);
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list
              [1U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
           [0U]);
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
              [1U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
              [2U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
              [3U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
              [4U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
              [5U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
              [6U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
              [7U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit) 
           | ((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
              [8U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[3U] 
        = (0x500000000ULL | (QData)((IData)((vlSelf->inst 
                                             >> 0xcU))));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[4U] 
        = (0x200000000ULL | (QData)((IData)((vlSelf->inst 
                                             >> 0x14U))));
    vlSelf->cpu_v1__DOT__rs2_value = vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf
        [(0x1fU & (vlSelf->inst >> 0x14U))];
    vlSelf->rs1_bo = vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf
        [(0x1fU & (vlSelf->inst >> 0xfU))];
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list[1U] 
        = vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf
        [(0x1fU & (vlSelf->inst >> 0x14U))];
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[3U] 
        = (vlSelf->inst >> 0xcU);
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[4U] 
        = (vlSelf->inst >> 0x14U);
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((- (IData)(((0x7fU & vlSelf->inst) == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                       [0U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
           [0U]);
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                          [1U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
              [1U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                          [2U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
              [2U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                          [3U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
              [3U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                          [4U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
              [4U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                          [5U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
              [5U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                          [6U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
              [6U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                          [7U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
              [7U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((0x7fU & vlSelf->inst) == 
                          vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list
                          [8U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list
              [8U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type = vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out;
    vlSelf->__VdfgTmp_h5152c62b__0 = ((0xfe0U & (vlSelf->inst 
                                                 >> 0x14U)) 
                                      | (0x1fU & (vlSelf->inst 
                                                  >> 7U)));
    vlSelf->__VdfgTmp_hfb3d7b8b__0 = ((0x80000U & (vlSelf->inst 
                                                   >> 0xcU)) 
                                      | ((0x7f800U 
                                          & (vlSelf->inst 
                                             >> 1U)) 
                                         | ((0x400U 
                                             & (vlSelf->inst 
                                                >> 0xaU)) 
                                            | (0x3ffU 
                                               & (vlSelf->inst 
                                                  >> 0x15U)))));
    vlSelf->__VdfgTmp_hac3a854f__0 = ((0x800U & (vlSelf->inst 
                                                 >> 0x14U)) 
                                      | ((0x400U & 
                                          (vlSelf->inst 
                                           << 3U)) 
                                         | ((0x3f0U 
                                             & (vlSelf->inst 
                                                >> 0x15U)) 
                                            | (0xfU 
                                               & (vlSelf->inst 
                                                  >> 8U)))));
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list[1U] 
        = (0x3300000000ULL | (QData)((IData)(vlSelf->cpu_v1__DOT__rs2_value)));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
           == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
           [0U]);
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit) 
           | ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
              == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
              [1U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit) 
           | ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
              == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
              [2U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit) 
           | ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
              == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
              [3U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit) 
           | ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
              == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
              [4U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit 
        = ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit) 
           | ((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
              == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
              [5U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[0U] 
        = (0x300000000ULL | (QData)((IData)(vlSelf->__VdfgTmp_h5152c62b__0)));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[0U] 
        = vlSelf->__VdfgTmp_h5152c62b__0;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[2U] 
        = (0x600000000ULL | (QData)((IData)(vlSelf->__VdfgTmp_hfb3d7b8b__0)));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[2U] 
        = vlSelf->__VdfgTmp_hfb3d7b8b__0;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[1U] 
        = (0x400000000ULL | (QData)((IData)(vlSelf->__VdfgTmp_hac3a854f__0)));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[1U] 
        = vlSelf->__VdfgTmp_hac3a854f__0;
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
        = ((- (IData)(((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
                       == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
                       [0U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list
           [0U]);
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
        = (vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
           | ((- (IData)(((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
                          == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
                          [1U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list
              [1U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
        = (vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
           | ((- (IData)(((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
                          == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
                          [2U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list
              [2U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
        = (vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
           | ((- (IData)(((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
                          == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
                          [3U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list
              [3U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
        = (vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
           | ((- (IData)(((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
                          == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
                          [4U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list
              [4U]));
    vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
        = (vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out 
           | ((- (IData)(((IData)(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type) 
                          == vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list
                          [5U]))) & vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list
              [5U]));
    vlSelf->cpu_v1__DOT__imm = vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out;
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list[0U] 
        = (0x1300000000ULL | (QData)((IData)((((- (IData)(
                                                          (1U 
                                                           & (vlSelf->cpu_v1__DOT__imm 
                                                              >> 0xbU)))) 
                                               << 0xcU) 
                                              | (0xfffU 
                                                 & vlSelf->cpu_v1__DOT__imm)))));
    vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list[0U] 
        = (((- (IData)((1U & (vlSelf->cpu_v1__DOT__imm 
                              >> 0xbU)))) << 0xcU) 
           | (0xfffU & vlSelf->cpu_v1__DOT__imm));
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

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_v1___024root___dump_triggers__act(Vcpu_v1___024root* vlSelf);
#endif  // VL_DEBUG

void Vcpu_v1___024root___eval_triggers__act(Vcpu_v1___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.at(0U) = ((IData)(vlSelf->clk) 
                                      & (~ (IData)(vlSelf->__Vtrigrprev__TOP__clk)));
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcpu_v1___024root___dump_triggers__act(vlSelf);
    }
#endif
}
