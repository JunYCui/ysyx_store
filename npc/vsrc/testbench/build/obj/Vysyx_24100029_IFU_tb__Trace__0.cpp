// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vysyx_24100029_IFU_tb__Syms.h"


void Vysyx_24100029_IFU_tb___024root__trace_chg_0_sub_0(Vysyx_24100029_IFU_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vysyx_24100029_IFU_tb___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root__trace_chg_0\n"); );
    // Init
    Vysyx_24100029_IFU_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_24100029_IFU_tb___024root*>(voidSelf);
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vysyx_24100029_IFU_tb___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vysyx_24100029_IFU_tb___024root__trace_chg_0_sub_0(Vysyx_24100029_IFU_tb___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root__trace_chg_0_sub_0\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity
                      [2U])))) {
        bufp->chgBit(oldp+0,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__reset));
        bufp->chgIData(oldp+1,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__dnpc),32);
        bufp->chgBit(oldp+2,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__dnpc_valid));
        bufp->chgBit(oldp+3,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__icache_clr));
        bufp->chgBit(oldp+4,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__clr));
        bufp->chgCData(oldp+5,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__ready),4);
        bufp->chgCData(oldp+6,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__count),8);
    }
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[3U] 
                      | vlSelfRef.__Vm_traceActivity
                      [5U])))) {
        bufp->chgCData(oldp+7,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren),4);
        bufp->chgCData(oldp+8,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_output),3);
        bufp->chgCData(oldp+9,((3U & ((1U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren)) 
                                      + VL_SHIFTR_III(2,2,32, 
                                                      (3U 
                                                       & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren)), 1U)))),2);
        bufp->chgCData(oldp+10,((3U & ((1U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                              >> 2U)) 
                                       + VL_SHIFTR_III(2,2,32, 
                                                       (3U 
                                                        & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                                           >> 2U)), 1U)))),2);
        bufp->chgCData(oldp+11,((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                       >> 2U))),2);
        bufp->chgBit(oldp+12,((1U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                     >> 2U))));
        bufp->chgBit(oldp+13,((1U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                     >> 3U))));
        bufp->chgCData(oldp+14,((3U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren))),2);
        bufp->chgBit(oldp+15,((1U & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren))));
        bufp->chgBit(oldp+16,((1U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren) 
                                     >> 1U))));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[4U]))) {
        bufp->chgIData(oldp+17,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                                [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr]),32);
        bufp->chgIData(oldp+18,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                                [vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr]),32);
        bufp->chgIData(oldp+19,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                                [(0xfU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))]),32);
        bufp->chgIData(oldp+20,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                                [(0xfU & ((IData)(1U) 
                                          + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))]),32);
        bufp->chgIData(oldp+21,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                                [(0xfU & ((IData)(2U) 
                                          + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))]),32);
        bufp->chgIData(oldp+22,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                                [(0xfU & ((IData)(2U) 
                                          + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))]),32);
        bufp->chgIData(oldp+23,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo
                                [(0xfU & ((IData)(3U) 
                                          + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))]),32);
        bufp->chgIData(oldp+24,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo
                                [(0xfU & ((IData)(3U) 
                                          + (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr)))]),32);
        bufp->chgBit(oldp+25,(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arvalid));
        bufp->chgCData(oldp+26,(((((3U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                                   << 3U) | ((2U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                                             << 2U)) 
                                 | (((1U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                                     << 1U) | (0U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count))))),4);
        bufp->chgCData(oldp+27,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state),2);
        bufp->chgCData(oldp+28,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len),8);
        bufp->chgCData(oldp+29,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__size),3);
        bufp->chgIData(oldp+30,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr),32);
        bufp->chgCData(oldp+31,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__burst),2);
        bufp->chgIData(oldp+32,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc),32);
        bufp->chgIData(oldp+33,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[0]),32);
        bufp->chgIData(oldp+34,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[1]),32);
        bufp->chgIData(oldp+35,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[2]),32);
        bufp->chgIData(oldp+36,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[3]),32);
        bufp->chgIData(oldp+37,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[4]),32);
        bufp->chgIData(oldp+38,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[5]),32);
        bufp->chgIData(oldp+39,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[6]),32);
        bufp->chgIData(oldp+40,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc_i[7]),32);
        bufp->chgBit(oldp+41,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rready));
        bufp->chgCData(oldp+42,((0xfU & ((IData)(8U) 
                                         - (7U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                  >> 2U))))),4);
        bufp->chgCData(oldp+43,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count),4);
        bufp->chgCData(oldp+44,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__w_ptr),4);
        bufp->chgCData(oldp+45,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__r_ptr),4);
        bufp->chgIData(oldp+46,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[0]),32);
        bufp->chgIData(oldp+47,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[1]),32);
        bufp->chgIData(oldp+48,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[2]),32);
        bufp->chgIData(oldp+49,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[3]),32);
        bufp->chgIData(oldp+50,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[4]),32);
        bufp->chgIData(oldp+51,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[5]),32);
        bufp->chgIData(oldp+52,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[6]),32);
        bufp->chgIData(oldp+53,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[7]),32);
        bufp->chgIData(oldp+54,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[8]),32);
        bufp->chgIData(oldp+55,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[9]),32);
        bufp->chgIData(oldp+56,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[10]),32);
        bufp->chgIData(oldp+57,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[11]),32);
        bufp->chgIData(oldp+58,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[12]),32);
        bufp->chgIData(oldp+59,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[13]),32);
        bufp->chgIData(oldp+60,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[14]),32);
        bufp->chgIData(oldp+61,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__fifo[15]),32);
        bufp->chgIData(oldp+62,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[0]),32);
        bufp->chgIData(oldp+63,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[1]),32);
        bufp->chgIData(oldp+64,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[2]),32);
        bufp->chgIData(oldp+65,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[3]),32);
        bufp->chgIData(oldp+66,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[4]),32);
        bufp->chgIData(oldp+67,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[5]),32);
        bufp->chgIData(oldp+68,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[6]),32);
        bufp->chgIData(oldp+69,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[7]),32);
        bufp->chgIData(oldp+70,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[8]),32);
        bufp->chgIData(oldp+71,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[9]),32);
        bufp->chgIData(oldp+72,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[10]),32);
        bufp->chgIData(oldp+73,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[11]),32);
        bufp->chgIData(oldp+74,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[12]),32);
        bufp->chgIData(oldp+75,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[13]),32);
        bufp->chgIData(oldp+76,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[14]),32);
        bufp->chgIData(oldp+77,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__pc_fifo[15]),32);
        bufp->chgIData(oldp+78,((IData)((0x7ffffffffffffffULL 
                                         & ((0U == 
                                             (0x1fU 
                                              & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc))
                                             ? (0x20ULL 
                                                + (QData)((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc)))
                                             : ((QData)((IData)(
                                                                (0x7ffffffU 
                                                                 & ((IData)(1U) 
                                                                    + 
                                                                    (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                                     >> 5U))))) 
                                                << 0x20U))))),32);
        bufp->chgBit(oldp+79,((1U & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                               [(3U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                       >> 4U))][0U])));
        bufp->chgIData(oldp+80,((0x3ffffffU & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                                               [(3U 
                                                 & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                    >> 4U))][0U] 
                                               >> 1U))),26);
        bufp->chgBit(oldp+81,(((vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                >> 6U) == (0x3ffffffU 
                                           & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache
                                              [(3U 
                                                & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                   >> 4U))][0U] 
                                              >> 1U)))));
        bufp->chgCData(oldp+82,((3U & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                       >> 4U))),2);
        bufp->chgWData(oldp+83,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[0]),283);
        bufp->chgWData(oldp+92,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[1]),283);
        bufp->chgWData(oldp+101,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[2]),283);
        bufp->chgWData(oldp+110,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__icache[3]),283);
        bufp->chgCData(oldp+119,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__count),8);
        bufp->chgIData(oldp+120,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__i),32);
        bufp->chgIData(oldp+121,((0xfffffff0U & vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc)),32);
        bufp->chgBit(oldp+122,((0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state))));
        bufp->chgBit(oldp+123,(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rlast));
        bufp->chgBit(oldp+124,(vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[5U]))) {
        bufp->chgIData(oldp+125,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[0]),32);
        bufp->chgIData(oldp+126,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[1]),32);
        bufp->chgIData(oldp+127,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[2]),32);
        bufp->chgIData(oldp+128,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[3]),32);
        bufp->chgIData(oldp+129,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[4]),32);
        bufp->chgIData(oldp+130,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[5]),32);
        bufp->chgIData(oldp+131,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[6]),32);
        bufp->chgIData(oldp+132,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_i[7]),32);
        bufp->chgCData(oldp+133,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_wen),8);
        bufp->chgBit(oldp+134,((0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))));
        bufp->chgWData(oldp+135,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_inst),256);
        bufp->chgBit(oldp+143,((3U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))));
        bufp->chgBit(oldp+144,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low));
        bufp->chgCData(oldp+145,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__count_input),4);
        bufp->chgCData(oldp+146,((7U & ((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
                                               + VL_SHIFTR_III(2,2,32, (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in), 1U))) 
                                        + (3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                                                 + 
                                                 VL_SHIFTR_III(2,2,32, 
                                                               (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                                                 << 1U) 
                                                                | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low)), 1U)))))),3);
        bufp->chgCData(oldp+147,((7U & ((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
                                               + VL_SHIFTR_III(2,2,32, 
                                                               (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high) 
                                                                 << 1U) 
                                                                | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low)), 1U))) 
                                        + (3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                                                 + 
                                                 VL_SHIFTR_III(2,2,32, 
                                                               (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                                                 << 1U) 
                                                                | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low)), 1U)))))),3);
        bufp->chgCData(oldp+148,(((((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                    << 3U) | ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                                              << 2U)) 
                                  | (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high) 
                                      << 1U) | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low)))),4);
        bufp->chgCData(oldp+149,((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
                                        + VL_SHIFTR_III(2,2,32, 
                                                        (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high) 
                                                          << 1U) 
                                                         | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low)), 1U)))),2);
        bufp->chgCData(oldp+150,((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                                        + VL_SHIFTR_III(2,2,32, 
                                                        (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                                          << 1U) 
                                                         | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low)), 1U)))),2);
        bufp->chgCData(oldp+151,((((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                   << 1U) | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low))),2);
        bufp->chgBit(oldp+152,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low));
        bufp->chgBit(oldp+153,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high));
        bufp->chgCData(oldp+154,((((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high) 
                                   << 1U) | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low))),2);
        bufp->chgBit(oldp+155,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low));
        bufp->chgBit(oldp+156,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__high__DOT__recursive__DOT__low__DOT__recursive__DOT__count_high));
        bufp->chgCData(oldp+157,((((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                   << 3U) | (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                                              << 2U) 
                                             | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in)))),4);
        bufp->chgCData(oldp+158,((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
                                        + VL_SHIFTR_III(2,2,32, (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in), 1U)))),2);
        bufp->chgCData(oldp+159,((3U & ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low) 
                                        + VL_SHIFTR_III(2,2,32, 
                                                        (((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                                          << 1U) 
                                                         | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low)), 1U)))),2);
        bufp->chgCData(oldp+160,((((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high) 
                                   << 1U) | (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low))),2);
        bufp->chgBit(oldp+161,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_low));
        bufp->chgBit(oldp+162,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__high__DOT__recursive__DOT__count_high));
        bufp->chgCData(oldp+163,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT____Vcellinp__recursive__DOT__low__data_in),2);
        bufp->chgCData(oldp+164,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state),2);
        bufp->chgBit(oldp+165,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__hit_r));
        bufp->chgCData(oldp+166,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__index_r),2);
        bufp->chgBit(oldp+167,((2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state))));
    }
    bufp->chgBit(oldp+168,(vlSelfRef.ysyx_24100029_IFU_tb__DOT__clock));
    bufp->chgBit(oldp+169,(((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low) 
                            & (1U < (0xfU & ((IData)(8U) 
                                             - (7U 
                                                & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                                   >> 2U))))))));
    bufp->chgIData(oldp+170,(((8U == (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
                                      >> 0x1cU)) ? 
                              vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__rom
                              [(0xffU & (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__addr 
                                         >> 2U))] : 0U)),32);
}

void Vysyx_24100029_IFU_tb___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root__trace_cleanup\n"); );
    // Init
    Vysyx_24100029_IFU_tb___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_24100029_IFU_tb___024root*>(voidSelf);
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[4U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[5U] = 0U;
}
