// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_24100029_IFU_tb.h for the primary calling header

#include "Vysyx_24100029_IFU_tb__pch.h"
#include "Vysyx_24100029_IFU_tb__Syms.h"
#include "Vysyx_24100029_IFU_tb___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___dump_triggers__stl(Vysyx_24100029_IFU_tb___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___eval_triggers__stl(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___eval_triggers__stl\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.setBit(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vysyx_24100029_IFU_tb___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vysyx_24100029_IFU_tb___024root___stl_sequent__TOP__0(Vysyx_24100029_IFU_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_24100029_IFU_tb___024root___stl_sequent__TOP__0\n"); );
    Vysyx_24100029_IFU_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.arready 
        = (0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state));
    vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rvalid 
        = ((1U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)) 
           | (2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rvalid 
        = (3U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state));
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
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_arready 
        = (0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state));
    vlSymsp->TOP__ysyx_24100029_IFU_tb__DOT__bus.rlast 
        = (((1U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state)) 
            | (2U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__state))) 
           & (0U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_mem__DOT__len)));
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_ren 
        = ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__ready) 
           & ((((3U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                << 3U) | ((2U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                          << 2U)) | (((1U < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)) 
                                      << 1U) | (0U 
                                                < (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count)))));
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
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rready 
        = (0x21U > ((IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__inst_count) 
                    + (0xfU & ((IData)(8U) - (7U & 
                                              (vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__pc 
                                               >> 2U))))));
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
    vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_Inst_Buffer__DOT__u_count_ones__DOT__recursive__DOT__low__DOT__recursive__DOT__low__DOT__recursive__DOT__count_low 
        = ((3U == (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__u_ysyx_24100029_icache__DOT__state)) 
           & (IData)(vlSelfRef.ysyx_24100029_IFU_tb__DOT__u_ysyx_24100029_IFU__DOT__icache_rready));
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
