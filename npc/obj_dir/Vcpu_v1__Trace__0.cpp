// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcpu_v1__Syms.h"


void Vcpu_v1___024root__trace_chg_sub_0(Vcpu_v1___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vcpu_v1___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_chg_top_0\n"); );
    // Init
    Vcpu_v1___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcpu_v1___024root*>(voidSelf);
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vcpu_v1___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vcpu_v1___024root__trace_chg_sub_0(Vcpu_v1___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    VlWide<3>/*95:0*/ __Vtemp_h2be1ccb4__0;
    VlWide<7>/*223:0*/ __Vtemp_h775f2483__0;
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[0U])) {
        bufp->chgCData(oldp+0,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list[0]),7);
        bufp->chgCData(oldp+1,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list[1]),7);
        bufp->chgSData(oldp+2,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[0]),10);
        bufp->chgSData(oldp+3,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[1]),10);
        bufp->chgSData(oldp+4,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[2]),10);
        bufp->chgSData(oldp+5,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[3]),10);
        bufp->chgSData(oldp+6,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[4]),10);
        bufp->chgSData(oldp+7,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[5]),10);
        bufp->chgSData(oldp+8,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[6]),10);
        bufp->chgSData(oldp+9,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[7]),10);
        bufp->chgSData(oldp+10,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[8]),10);
        bufp->chgCData(oldp+11,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[0]),7);
        bufp->chgCData(oldp+12,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[1]),7);
        bufp->chgCData(oldp+13,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[2]),7);
        bufp->chgCData(oldp+14,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[3]),7);
        bufp->chgCData(oldp+15,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[4]),7);
        bufp->chgCData(oldp+16,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[5]),7);
        bufp->chgCData(oldp+17,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[6]),7);
        bufp->chgCData(oldp+18,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[7]),7);
        bufp->chgCData(oldp+19,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[8]),7);
        bufp->chgCData(oldp+20,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[0]),3);
        bufp->chgCData(oldp+21,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[1]),3);
        bufp->chgCData(oldp+22,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[2]),3);
        bufp->chgCData(oldp+23,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[3]),3);
        bufp->chgCData(oldp+24,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[4]),3);
        bufp->chgCData(oldp+25,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[5]),3);
        bufp->chgCData(oldp+26,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[6]),3);
        bufp->chgCData(oldp+27,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[7]),3);
        bufp->chgCData(oldp+28,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[8]),3);
        bufp->chgCData(oldp+29,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[0]),3);
        bufp->chgCData(oldp+30,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[1]),3);
        bufp->chgCData(oldp+31,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[2]),3);
        bufp->chgCData(oldp+32,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[3]),3);
        bufp->chgCData(oldp+33,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[4]),3);
        bufp->chgCData(oldp+34,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[5]),3);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgIData(oldp+35,(vlSelf->cpu_v1__DOT__imm),32);
        bufp->chgIData(oldp+36,((((- (IData)((1U & 
                                              (vlSelf->cpu_v1__DOT__imm 
                                               >> 0xbU)))) 
                                  << 0xcU) | (0xfffU 
                                              & vlSelf->cpu_v1__DOT__imm))),32);
        bufp->chgBit(oldp+37,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__hit));
        bufp->chgSData(oldp+38,((0xfffU & vlSelf->cpu_v1__DOT__imm)),12);
        bufp->chgCData(oldp+39,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type),3);
        bufp->chgCData(oldp+40,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out),3);
        bufp->chgBit(oldp+41,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit));
        bufp->chgQData(oldp+42,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[0]),35);
        bufp->chgQData(oldp+44,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[1]),35);
        bufp->chgQData(oldp+46,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[2]),35);
        bufp->chgQData(oldp+48,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[3]),35);
        bufp->chgQData(oldp+50,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[4]),35);
        bufp->chgQData(oldp+52,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[5]),35);
        bufp->chgIData(oldp+54,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[0]),32);
        bufp->chgIData(oldp+55,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[1]),32);
        bufp->chgIData(oldp+56,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[2]),32);
        bufp->chgIData(oldp+57,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[3]),32);
        bufp->chgIData(oldp+58,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[4]),32);
        bufp->chgIData(oldp+59,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[5]),32);
        bufp->chgIData(oldp+60,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out),32);
        bufp->chgBit(oldp+61,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit));
    }
    if (VL_UNLIKELY((vlSelf->__Vm_traceActivity[1U] 
                     | vlSelf->__Vm_traceActivity[2U]))) {
        bufp->chgIData(oldp+62,(vlSelf->cpu_v1__DOT__rs2_value),32);
        bufp->chgIData(oldp+63,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2),32);
        bufp->chgIData(oldp+64,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result),32);
        __Vtemp_h2be1ccb4__0[0U] = (IData)((0x1300000000ULL 
                                            | (QData)((IData)(
                                                              (((- (IData)(
                                                                           (1U 
                                                                            & (vlSelf->cpu_v1__DOT__imm 
                                                                               >> 0xbU)))) 
                                                                << 0xcU) 
                                                               | (0xfffU 
                                                                  & vlSelf->cpu_v1__DOT__imm))))));
        __Vtemp_h2be1ccb4__0[1U] = ((vlSelf->cpu_v1__DOT__rs2_value 
                                     << 7U) | (IData)(
                                                      ((0x1300000000ULL 
                                                        | (QData)((IData)(
                                                                          (((- (IData)(
                                                                                (1U 
                                                                                & (vlSelf->cpu_v1__DOT__imm 
                                                                                >> 0xbU)))) 
                                                                            << 0xcU) 
                                                                           | (0xfffU 
                                                                              & vlSelf->cpu_v1__DOT__imm))))) 
                                                       >> 0x20U)));
        __Vtemp_h2be1ccb4__0[2U] = (0x1980U | (vlSelf->cpu_v1__DOT__rs2_value 
                                               >> 0x19U));
        bufp->chgWData(oldp+65,(__Vtemp_h2be1ccb4__0),78);
        bufp->chgQData(oldp+68,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list[0]),39);
        bufp->chgQData(oldp+70,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list[1]),39);
        bufp->chgIData(oldp+72,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list[0]),32);
        bufp->chgIData(oldp+73,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list[1]),32);
        bufp->chgIData(oldp+74,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__lut_out),32);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgIData(oldp+75,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[0]),32);
        bufp->chgIData(oldp+76,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[1]),32);
        bufp->chgIData(oldp+77,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[2]),32);
        bufp->chgIData(oldp+78,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[3]),32);
        bufp->chgIData(oldp+79,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[4]),32);
        bufp->chgIData(oldp+80,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[5]),32);
        bufp->chgIData(oldp+81,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[6]),32);
        bufp->chgIData(oldp+82,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[7]),32);
        bufp->chgIData(oldp+83,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[8]),32);
        bufp->chgIData(oldp+84,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[9]),32);
        bufp->chgIData(oldp+85,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[10]),32);
        bufp->chgIData(oldp+86,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[11]),32);
        bufp->chgIData(oldp+87,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[12]),32);
        bufp->chgIData(oldp+88,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[13]),32);
        bufp->chgIData(oldp+89,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[14]),32);
        bufp->chgIData(oldp+90,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[15]),32);
        bufp->chgIData(oldp+91,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[16]),32);
        bufp->chgIData(oldp+92,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[17]),32);
        bufp->chgIData(oldp+93,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[18]),32);
        bufp->chgIData(oldp+94,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[19]),32);
        bufp->chgIData(oldp+95,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[20]),32);
        bufp->chgIData(oldp+96,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[21]),32);
        bufp->chgIData(oldp+97,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[22]),32);
        bufp->chgIData(oldp+98,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[23]),32);
        bufp->chgIData(oldp+99,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[24]),32);
        bufp->chgIData(oldp+100,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[25]),32);
        bufp->chgIData(oldp+101,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[26]),32);
        bufp->chgIData(oldp+102,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[27]),32);
        bufp->chgIData(oldp+103,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[28]),32);
        bufp->chgIData(oldp+104,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[29]),32);
        bufp->chgIData(oldp+105,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[30]),32);
        bufp->chgIData(oldp+106,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[31]),32);
    }
    bufp->chgBit(oldp+107,(vlSelf->clk));
    bufp->chgBit(oldp+108,(vlSelf->rst));
    bufp->chgIData(oldp+109,(vlSelf->inst),32);
    bufp->chgIData(oldp+110,(vlSelf->pc),32);
    bufp->chgIData(oldp+111,(vlSelf->rs1_bo),32);
    bufp->chgCData(oldp+112,((0x1fU & (vlSelf->inst 
                                       >> 0xfU))),5);
    bufp->chgCData(oldp+113,((0x1fU & (vlSelf->inst 
                                       >> 0x14U))),5);
    bufp->chgCData(oldp+114,((0x1fU & (vlSelf->inst 
                                       >> 7U))),5);
    bufp->chgCData(oldp+115,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->chgCData(oldp+116,((0x7fU & vlSelf->inst)),7);
    bufp->chgIData(oldp+117,(((0x4000U & vlSelf->inst)
                               ? ((0x2000U & vlSelf->inst)
                                   ? 0U : ((0x1000U 
                                            & vlSelf->inst)
                                            ? (vlSelf->rs1_bo 
                                               ^ vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2)
                                            : (vlSelf->rs1_bo 
                                               | vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2)))
                               : ((0x2000U & vlSelf->inst)
                                   ? ((0x1000U & vlSelf->inst)
                                       ? (vlSelf->rs1_bo 
                                          & vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2)
                                       : ((IData)(1U) 
                                          + (~ vlSelf->rs1_bo)))
                                   : vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result))),32);
    bufp->chgBit(oldp+118,((IData)(((0U == (0x6000U 
                                            & vlSelf->inst)) 
                                    & (((vlSelf->rs1_bo 
                                         >> 0x1fU) 
                                        == (((1U & 
                                              ((0x4000U 
                                                & vlSelf->inst)
                                                ? (vlSelf->inst 
                                                   >> 0xdU)
                                                : (IData)(
                                                          (0x1000U 
                                                           == 
                                                           (0x3000U 
                                                            & vlSelf->inst)))))
                                              ? ((IData)(1U) 
                                                 + 
                                                 (~ vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2))
                                              : vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2) 
                                            >> 0x1fU)) 
                                       & ((vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result 
                                           >> 0x1fU) 
                                          != (vlSelf->rs1_bo 
                                              >> 0x1fU)))))));
    bufp->chgBit(oldp+119,((1U & (IData)(((0x6000U 
                                           == (0x6000U 
                                               & vlSelf->inst)) 
                                          & ((0x1000U 
                                              & vlSelf->inst)
                                              ? (0U 
                                                 == 
                                                 (0xfU 
                                                  & vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result))
                                              : (((1U 
                                                   & (vlSelf->rs1_bo 
                                                      >> 3U)) 
                                                  == 
                                                  (1U 
                                                   & (vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2 
                                                      >> 3U))) 
                                                 | (vlSelf->rs1_bo 
                                                    >> 3U))))))));
    bufp->chgBit(oldp+120,((1U & ((0x4000U & vlSelf->inst)
                                   ? (vlSelf->inst 
                                      >> 0xdU) : (IData)(
                                                         (0x1000U 
                                                          == 
                                                          (0x3000U 
                                                           & vlSelf->inst)))))));
    bufp->chgBit(oldp+121,((((vlSelf->rs1_bo >> 0x1fU) 
                             == (((1U & ((0x4000U & vlSelf->inst)
                                          ? (vlSelf->inst 
                                             >> 0xdU)
                                          : (IData)(
                                                    (0x1000U 
                                                     == 
                                                     (0x3000U 
                                                      & vlSelf->inst)))))
                                   ? ((IData)(1U) + 
                                      (~ vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2))
                                   : vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2) 
                                 >> 0x1fU)) & ((vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result 
                                                >> 0x1fU) 
                                               != (vlSelf->rs1_bo 
                                                   >> 0x1fU)))));
    bufp->chgIData(oldp+122,(((1U & ((0x4000U & vlSelf->inst)
                                      ? (vlSelf->inst 
                                         >> 0xdU) : (IData)(
                                                            (0x1000U 
                                                             == 
                                                             (0x3000U 
                                                              & vlSelf->inst)))))
                               ? ((IData)(1U) + (~ vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2))
                               : vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2)),32);
    __Vtemp_h775f2483__0[0U] = (IData)((0x300000000ULL 
                                        | (((QData)((IData)(
                                                            (vlSelf->inst 
                                                             >> 0x1fU))) 
                                            << 0x2eU) 
                                           | (((QData)((IData)(
                                                               (1U 
                                                                & (vlSelf->inst 
                                                                   >> 7U)))) 
                                               << 0x2dU) 
                                              | (((QData)((IData)(
                                                                  (0x3fU 
                                                                   & (vlSelf->inst 
                                                                      >> 0x19U)))) 
                                                  << 0x27U) 
                                                 | (((QData)((IData)(
                                                                     (0xfU 
                                                                      & (vlSelf->inst 
                                                                         >> 8U)))) 
                                                     << 0x23U) 
                                                    | (QData)((IData)(vlSelf->__VdfgTmp_h5152c62b__0))))))));
    __Vtemp_h775f2483__0[1U] = (IData)(((0x300000000ULL 
                                         | (((QData)((IData)(
                                                             (vlSelf->inst 
                                                              >> 0x1fU))) 
                                             << 0x2eU) 
                                            | (((QData)((IData)(
                                                                (1U 
                                                                 & (vlSelf->inst 
                                                                    >> 7U)))) 
                                                << 0x2dU) 
                                               | (((QData)((IData)(
                                                                   (0x3fU 
                                                                    & (vlSelf->inst 
                                                                       >> 0x19U)))) 
                                                   << 0x27U) 
                                                  | (((QData)((IData)(
                                                                      (0xfU 
                                                                       & (vlSelf->inst 
                                                                          >> 8U)))) 
                                                      << 0x23U) 
                                                     | (QData)((IData)(vlSelf->__VdfgTmp_h5152c62b__0))))))) 
                                        >> 0x20U));
    __Vtemp_h775f2483__0[2U] = (0x20U | ((0x2000000U 
                                          & (vlSelf->inst 
                                             >> 6U)) 
                                         | ((0x1fe0000U 
                                             & (vlSelf->inst 
                                                << 5U)) 
                                            | ((0x10000U 
                                                & (vlSelf->inst 
                                                   >> 4U)) 
                                               | (0xffc0U 
                                                  & (vlSelf->inst 
                                                     >> 0xfU))))));
    __Vtemp_h775f2483__0[3U] = (0x180U | (0x1ffffe00U 
                                          & (vlSelf->inst 
                                             >> 3U)));
    __Vtemp_h775f2483__0[4U] = (0xa00U | (0xfff000U 
                                          & (vlSelf->inst 
                                             >> 8U)));
    __Vtemp_h775f2483__0[5U] = 0x2000U;
    __Vtemp_h775f2483__0[6U] = 0x8000U;
    bufp->chgWData(oldp+123,(__Vtemp_h775f2483__0),210);
}

void Vcpu_v1___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_cleanup\n"); );
    // Init
    Vcpu_v1___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcpu_v1___024root*>(voidSelf);
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
