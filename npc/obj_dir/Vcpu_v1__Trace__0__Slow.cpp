// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcpu_v1__Syms.h"


VL_ATTR_COLD void Vcpu_v1___024root__trace_init_sub__TOP__0(Vcpu_v1___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+108,"clk", false,-1);
    tracep->declBit(c+109,"rst", false,-1);
    tracep->declBus(c+110,"inst", false,-1, 31,0);
    tracep->declBus(c+111,"pc", false,-1, 31,0);
    tracep->declBus(c+112,"rs1_bo", false,-1, 31,0);
    tracep->pushNamePrefix("cpu_v1 ");
    tracep->declBit(c+108,"clk", false,-1);
    tracep->declBit(c+109,"rst", false,-1);
    tracep->declBus(c+110,"inst", false,-1, 31,0);
    tracep->declBus(c+111,"pc", false,-1, 31,0);
    tracep->declBus(c+112,"rs1_bo", false,-1, 31,0);
    tracep->declBus(c+131,"PC_MAX", false,-1, 31,0);
    tracep->declBus(c+113,"rs1", false,-1, 4,0);
    tracep->declBus(c+114,"rs2", false,-1, 4,0);
    tracep->declBus(c+115,"rd", false,-1, 4,0);
    tracep->declBus(c+36,"imm", false,-1, 31,0);
    tracep->declBus(c+116,"funct3", false,-1, 2,0);
    tracep->declBus(c+117,"opcode", false,-1, 6,0);
    tracep->declBus(c+112,"rs1_value", false,-1, 31,0);
    tracep->declBus(c+63,"rs2_value", false,-1, 31,0);
    tracep->declBus(c+118,"rd_value", false,-1, 31,0);
    tracep->pushNamePrefix("EXU_inst0 ");
    tracep->declBit(c+108,"clk", false,-1);
    tracep->declBit(c+109,"rst", false,-1);
    tracep->declBus(c+116,"funct3", false,-1, 2,0);
    tracep->declBus(c+117,"opcode", false,-1, 6,0);
    tracep->declBus(c+36,"imm", false,-1, 31,0);
    tracep->declBus(c+112,"rs1_value", false,-1, 31,0);
    tracep->declBus(c+63,"rs2_value", false,-1, 31,0);
    tracep->declBus(c+118,"rd_value", false,-1, 31,0);
    tracep->declBus(c+132,"i2_NR_KEY", false,-1, 31,0);
    tracep->declBus(c+133,"i2_KEY_LEN", false,-1, 31,0);
    tracep->declBus(c+134,"i2_DATA_LEN", false,-1, 31,0);
    tracep->declBus(c+112,"add_1", false,-1, 31,0);
    tracep->declBus(c+64,"add_2", false,-1, 31,0);
    tracep->declBus(c+118,"ALU_res", false,-1, 31,0);
    tracep->declBus(c+36,"imm_12u", false,-1, 31,0);
    tracep->declBus(c+37,"imm_12i", false,-1, 31,0);
    tracep->declBit(c+119,"overflow", false,-1);
    tracep->declBit(c+120,"compare", false,-1);
    tracep->pushNamePrefix("ALU_i0 ");
    tracep->declBus(c+135,"BW", false,-1, 5,0);
    tracep->declBus(c+112,"d1", false,-1, 31,0);
    tracep->declBus(c+64,"d2", false,-1, 31,0);
    tracep->declBus(c+116,"choice", false,-1, 2,0);
    tracep->declBus(c+118,"res", false,-1, 31,0);
    tracep->declBit(c+119,"overflow", false,-1);
    tracep->declBit(c+120,"compare", false,-1);
    tracep->declBit(c+121,"choose_add_sub", false,-1);
    tracep->declBit(c+122,"add_of", false,-1);
    tracep->declBus(c+65,"result", false,-1, 31,0);
    tracep->pushNamePrefix("add_inst0 ");
    tracep->declBus(c+135,"BW", false,-1, 5,0);
    tracep->declBit(c+121,"choose_add_sub", false,-1);
    tracep->declBus(c+112,"add_1", false,-1, 31,0);
    tracep->declBus(c+64,"add_2", false,-1, 31,0);
    tracep->declBus(c+65,"result", false,-1, 31,0);
    tracep->declBit(c+122,"overflow", false,-1);
    tracep->declBus(c+123,"add_3", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("i0 ");
    tracep->declBus(c+132,"NR_KEY", false,-1, 31,0);
    tracep->declBus(c+133,"KEY_LEN", false,-1, 31,0);
    tracep->declBus(c+134,"DATA_LEN", false,-1, 31,0);
    tracep->declBus(c+136,"HAS_DEFAULT", false,-1, 31,0);
    tracep->declBus(c+64,"out", false,-1, 31,0);
    tracep->declBus(c+117,"key", false,-1, 6,0);
    tracep->declBus(c+137,"default_out", false,-1, 31,0);
    tracep->declArray(c+66,"lut", false,-1, 77,0);
    tracep->declBus(c+138,"PAIR_LEN", false,-1, 31,0);
    for (int i = 0; i < 2; ++i) {
        tracep->declQuad(c+69+i*2,"pair_list", true,(i+0), 38,0);
    }
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+1+i*1,"key_list", true,(i+0), 6,0);
    }
    for (int i = 0; i < 2; ++i) {
        tracep->declBus(c+73+i*1,"data_list", true,(i+0), 31,0);
    }
    tracep->declBus(c+75,"lut_out", false,-1, 31,0);
    tracep->declBit(c+38,"hit", false,-1);
    tracep->declBus(c+139,"i", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("sext_i12 ");
    tracep->declBus(c+140,"DATA_WIDTH", false,-1, 31,0);
    tracep->declBus(c+134,"OUT_WIDTH", false,-1, 31,0);
    tracep->declBus(c+39,"data", false,-1, 11,0);
    tracep->declBus(c+37,"sext_data", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("IDU_inst0 ");
    tracep->declBus(c+110,"inst", false,-1, 31,0);
    tracep->declBus(c+113,"rs1", false,-1, 4,0);
    tracep->declBus(c+114,"rs2", false,-1, 4,0);
    tracep->declBus(c+115,"rd", false,-1, 4,0);
    tracep->declBus(c+36,"imm", false,-1, 31,0);
    tracep->declBus(c+116,"funct3", false,-1, 2,0);
    tracep->declBus(c+117,"opcode", false,-1, 6,0);
    tracep->declBus(c+40,"Type", false,-1, 2,0);
    tracep->pushNamePrefix("i0 ");
    tracep->declBus(c+141,"NR_KEY", false,-1, 31,0);
    tracep->declBus(c+133,"KEY_LEN", false,-1, 31,0);
    tracep->declBus(c+142,"DATA_LEN", false,-1, 31,0);
    tracep->declBus(c+136,"HAS_DEFAULT", false,-1, 31,0);
    tracep->declBus(c+40,"out", false,-1, 2,0);
    tracep->declBus(c+117,"key", false,-1, 6,0);
    tracep->declBus(c+143,"default_out", false,-1, 2,0);
    tracep->declArray(c+144,"lut", false,-1, 89,0);
    tracep->declBus(c+147,"PAIR_LEN", false,-1, 31,0);
    for (int i = 0; i < 9; ++i) {
        tracep->declBus(c+3+i*1,"pair_list", true,(i+0), 9,0);
    }
    for (int i = 0; i < 9; ++i) {
        tracep->declBus(c+12+i*1,"key_list", true,(i+0), 6,0);
    }
    for (int i = 0; i < 9; ++i) {
        tracep->declBus(c+21+i*1,"data_list", true,(i+0), 2,0);
    }
    tracep->declBus(c+41,"lut_out", false,-1, 2,0);
    tracep->declBit(c+42,"hit", false,-1);
    tracep->declBus(c+148,"i", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("i1 ");
    tracep->declBus(c+149,"NR_KEY", false,-1, 31,0);
    tracep->declBus(c+142,"KEY_LEN", false,-1, 31,0);
    tracep->declBus(c+134,"DATA_LEN", false,-1, 31,0);
    tracep->declBus(c+136,"HAS_DEFAULT", false,-1, 31,0);
    tracep->declBus(c+36,"out", false,-1, 31,0);
    tracep->declBus(c+40,"key", false,-1, 2,0);
    tracep->declBus(c+137,"default_out", false,-1, 31,0);
    tracep->declArray(c+124,"lut", false,-1, 209,0);
    tracep->declBus(c+150,"PAIR_LEN", false,-1, 31,0);
    for (int i = 0; i < 6; ++i) {
        tracep->declQuad(c+43+i*2,"pair_list", true,(i+0), 34,0);
    }
    for (int i = 0; i < 6; ++i) {
        tracep->declBus(c+30+i*1,"key_list", true,(i+0), 2,0);
    }
    for (int i = 0; i < 6; ++i) {
        tracep->declBus(c+55+i*1,"data_list", true,(i+0), 31,0);
    }
    tracep->declBus(c+61,"lut_out", false,-1, 31,0);
    tracep->declBit(c+62,"hit", false,-1);
    tracep->declBus(c+151,"i", false,-1, 31,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("Reg_Stack_inst0 ");
    tracep->declBit(c+109,"rst", false,-1);
    tracep->declBit(c+108,"clk", false,-1);
    tracep->declBus(c+113,"rs1", false,-1, 4,0);
    tracep->declBus(c+114,"rs2", false,-1, 4,0);
    tracep->declBus(c+115,"rd", false,-1, 4,0);
    tracep->declBus(c+118,"rd_value", false,-1, 31,0);
    tracep->declBit(c+109,"wen", false,-1);
    tracep->declBus(c+112,"rs1_value", false,-1, 31,0);
    tracep->declBus(c+63,"rs2_value", false,-1, 31,0);
    tracep->pushNamePrefix("io ");
    tracep->declBus(c+152,"ADDR_WIDTH", false,-1, 31,0);
    tracep->declBus(c+134,"DATA_WIDTH", false,-1, 31,0);
    tracep->declBit(c+108,"clk", false,-1);
    tracep->declBus(c+118,"wdata", false,-1, 31,0);
    tracep->declBus(c+115,"waddr", false,-1, 4,0);
    tracep->declBit(c+109,"wen", false,-1);
    tracep->declBit(c+109,"rst", false,-1);
    tracep->declBus(c+113,"rs1_addr", false,-1, 4,0);
    tracep->declBus(c+114,"rs2_addr", false,-1, 4,0);
    tracep->declBus(c+112,"rs1_value", false,-1, 31,0);
    tracep->declBus(c+63,"rs2_value", false,-1, 31,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+76+i*1,"rf", true,(i+0), 31,0);
    }
    tracep->popNamePrefix(3);
}

VL_ATTR_COLD void Vcpu_v1___024root__trace_init_sub__TOP____024unit__0(Vcpu_v1___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_init_sub__TOP____024unit__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBus(c+141,"i0_NR_KEY", false,-1, 31,0);
    tracep->declBus(c+133,"i0_KEY_LEN", false,-1, 31,0);
    tracep->declBus(c+142,"i0_DATA_LEN", false,-1, 31,0);
    tracep->declBus(c+149,"i1_NR_KEY", false,-1, 31,0);
    tracep->declBus(c+142,"i1_KEY_LEN", false,-1, 31,0);
    tracep->declBus(c+134,"i1_DATA_LEN", false,-1, 31,0);
}

VL_ATTR_COLD void Vcpu_v1___024root__trace_init_top(Vcpu_v1___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_init_top\n"); );
    // Body
    Vcpu_v1___024root__trace_init_sub__TOP__0(vlSelf, tracep);
    tracep->pushNamePrefix("$unit ");
    Vcpu_v1___024root__trace_init_sub__TOP____024unit__0(vlSelf, tracep);
    tracep->popNamePrefix(1);
}

VL_ATTR_COLD void Vcpu_v1___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vcpu_v1___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vcpu_v1___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vcpu_v1___024root__trace_register(Vcpu_v1___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vcpu_v1___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vcpu_v1___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vcpu_v1___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vcpu_v1___024root__trace_full_sub_0(Vcpu_v1___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vcpu_v1___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_full_top_0\n"); );
    // Init
    Vcpu_v1___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcpu_v1___024root*>(voidSelf);
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vcpu_v1___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vcpu_v1___024root__trace_full_sub_0(Vcpu_v1___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_v1___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    VlWide<3>/*95:0*/ __Vtemp_h2be1ccb4__0;
    VlWide<7>/*223:0*/ __Vtemp_h775f2483__0;
    VlWide<3>/*95:0*/ __Vtemp_hf1926d6b__0;
    // Body
    bufp->fullCData(oldp+1,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list[0]),7);
    bufp->fullCData(oldp+2,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__key_list[1]),7);
    bufp->fullSData(oldp+3,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[0]),10);
    bufp->fullSData(oldp+4,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[1]),10);
    bufp->fullSData(oldp+5,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[2]),10);
    bufp->fullSData(oldp+6,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[3]),10);
    bufp->fullSData(oldp+7,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[4]),10);
    bufp->fullSData(oldp+8,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[5]),10);
    bufp->fullSData(oldp+9,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[6]),10);
    bufp->fullSData(oldp+10,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[7]),10);
    bufp->fullSData(oldp+11,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__pair_list[8]),10);
    bufp->fullCData(oldp+12,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[0]),7);
    bufp->fullCData(oldp+13,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[1]),7);
    bufp->fullCData(oldp+14,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[2]),7);
    bufp->fullCData(oldp+15,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[3]),7);
    bufp->fullCData(oldp+16,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[4]),7);
    bufp->fullCData(oldp+17,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[5]),7);
    bufp->fullCData(oldp+18,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[6]),7);
    bufp->fullCData(oldp+19,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[7]),7);
    bufp->fullCData(oldp+20,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__key_list[8]),7);
    bufp->fullCData(oldp+21,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[0]),3);
    bufp->fullCData(oldp+22,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[1]),3);
    bufp->fullCData(oldp+23,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[2]),3);
    bufp->fullCData(oldp+24,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[3]),3);
    bufp->fullCData(oldp+25,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[4]),3);
    bufp->fullCData(oldp+26,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[5]),3);
    bufp->fullCData(oldp+27,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[6]),3);
    bufp->fullCData(oldp+28,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[7]),3);
    bufp->fullCData(oldp+29,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__data_list[8]),3);
    bufp->fullCData(oldp+30,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[0]),3);
    bufp->fullCData(oldp+31,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[1]),3);
    bufp->fullCData(oldp+32,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[2]),3);
    bufp->fullCData(oldp+33,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[3]),3);
    bufp->fullCData(oldp+34,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[4]),3);
    bufp->fullCData(oldp+35,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__key_list[5]),3);
    bufp->fullIData(oldp+36,(vlSelf->cpu_v1__DOT__imm),32);
    bufp->fullIData(oldp+37,((((- (IData)((1U & (vlSelf->cpu_v1__DOT__imm 
                                                 >> 0xbU)))) 
                               << 0xcU) | (0xfffU & vlSelf->cpu_v1__DOT__imm))),32);
    bufp->fullBit(oldp+38,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__hit));
    bufp->fullSData(oldp+39,((0xfffU & vlSelf->cpu_v1__DOT__imm)),12);
    bufp->fullCData(oldp+40,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__Type),3);
    bufp->fullCData(oldp+41,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__lut_out),3);
    bufp->fullBit(oldp+42,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i0__DOT__hit));
    bufp->fullQData(oldp+43,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[0]),35);
    bufp->fullQData(oldp+45,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[1]),35);
    bufp->fullQData(oldp+47,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[2]),35);
    bufp->fullQData(oldp+49,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[3]),35);
    bufp->fullQData(oldp+51,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[4]),35);
    bufp->fullQData(oldp+53,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__pair_list[5]),35);
    bufp->fullIData(oldp+55,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[0]),32);
    bufp->fullIData(oldp+56,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[1]),32);
    bufp->fullIData(oldp+57,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[2]),32);
    bufp->fullIData(oldp+58,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[3]),32);
    bufp->fullIData(oldp+59,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[4]),32);
    bufp->fullIData(oldp+60,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__data_list[5]),32);
    bufp->fullIData(oldp+61,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__lut_out),32);
    bufp->fullBit(oldp+62,(vlSelf->cpu_v1__DOT__IDU_inst0__DOT__i1__DOT__hit));
    bufp->fullIData(oldp+63,(vlSelf->cpu_v1__DOT__rs2_value),32);
    bufp->fullIData(oldp+64,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2),32);
    bufp->fullIData(oldp+65,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result),32);
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
                                 << 7U) | (IData)((
                                                   (0x1300000000ULL 
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
    bufp->fullWData(oldp+66,(__Vtemp_h2be1ccb4__0),78);
    bufp->fullQData(oldp+69,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list[0]),39);
    bufp->fullQData(oldp+71,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__pair_list[1]),39);
    bufp->fullIData(oldp+73,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list[0]),32);
    bufp->fullIData(oldp+74,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__data_list[1]),32);
    bufp->fullIData(oldp+75,(vlSelf->cpu_v1__DOT__EXU_inst0__DOT__i0__DOT__lut_out),32);
    bufp->fullIData(oldp+76,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[0]),32);
    bufp->fullIData(oldp+77,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[1]),32);
    bufp->fullIData(oldp+78,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[2]),32);
    bufp->fullIData(oldp+79,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[3]),32);
    bufp->fullIData(oldp+80,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[4]),32);
    bufp->fullIData(oldp+81,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[5]),32);
    bufp->fullIData(oldp+82,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[6]),32);
    bufp->fullIData(oldp+83,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[7]),32);
    bufp->fullIData(oldp+84,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[8]),32);
    bufp->fullIData(oldp+85,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[9]),32);
    bufp->fullIData(oldp+86,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[10]),32);
    bufp->fullIData(oldp+87,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[11]),32);
    bufp->fullIData(oldp+88,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[12]),32);
    bufp->fullIData(oldp+89,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[13]),32);
    bufp->fullIData(oldp+90,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[14]),32);
    bufp->fullIData(oldp+91,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[15]),32);
    bufp->fullIData(oldp+92,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[16]),32);
    bufp->fullIData(oldp+93,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[17]),32);
    bufp->fullIData(oldp+94,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[18]),32);
    bufp->fullIData(oldp+95,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[19]),32);
    bufp->fullIData(oldp+96,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[20]),32);
    bufp->fullIData(oldp+97,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[21]),32);
    bufp->fullIData(oldp+98,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[22]),32);
    bufp->fullIData(oldp+99,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[23]),32);
    bufp->fullIData(oldp+100,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[24]),32);
    bufp->fullIData(oldp+101,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[25]),32);
    bufp->fullIData(oldp+102,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[26]),32);
    bufp->fullIData(oldp+103,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[27]),32);
    bufp->fullIData(oldp+104,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[28]),32);
    bufp->fullIData(oldp+105,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[29]),32);
    bufp->fullIData(oldp+106,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[30]),32);
    bufp->fullIData(oldp+107,(vlSelf->cpu_v1__DOT__Reg_Stack_inst0__DOT__io__DOT__rf[31]),32);
    bufp->fullBit(oldp+108,(vlSelf->clk));
    bufp->fullBit(oldp+109,(vlSelf->rst));
    bufp->fullIData(oldp+110,(vlSelf->inst),32);
    bufp->fullIData(oldp+111,(vlSelf->pc),32);
    bufp->fullIData(oldp+112,(vlSelf->rs1_bo),32);
    bufp->fullCData(oldp+113,((0x1fU & (vlSelf->inst 
                                        >> 0xfU))),5);
    bufp->fullCData(oldp+114,((0x1fU & (vlSelf->inst 
                                        >> 0x14U))),5);
    bufp->fullCData(oldp+115,((0x1fU & (vlSelf->inst 
                                        >> 7U))),5);
    bufp->fullCData(oldp+116,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->fullCData(oldp+117,((0x7fU & vlSelf->inst)),7);
    bufp->fullIData(oldp+118,(((0x4000U & vlSelf->inst)
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
    bufp->fullBit(oldp+119,((IData)(((0U == (0x6000U 
                                             & vlSelf->inst)) 
                                     & (((vlSelf->rs1_bo 
                                          >> 0x1fU) 
                                         == (((1U & 
                                               ((0x4000U 
                                                 & vlSelf->inst)
                                                 ? 
                                                (vlSelf->inst 
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
    bufp->fullBit(oldp+120,((1U & (IData)(((0x6000U 
                                            == (0x6000U 
                                                & vlSelf->inst)) 
                                           & ((0x1000U 
                                               & vlSelf->inst)
                                               ? (0U 
                                                  == 
                                                  (0xfU 
                                                   & vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result))
                                               : ((
                                                   (1U 
                                                    & (vlSelf->rs1_bo 
                                                       >> 3U)) 
                                                   == 
                                                   (1U 
                                                    & (vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2 
                                                       >> 3U))) 
                                                  | (vlSelf->rs1_bo 
                                                     >> 3U))))))));
    bufp->fullBit(oldp+121,((1U & ((0x4000U & vlSelf->inst)
                                    ? (vlSelf->inst 
                                       >> 0xdU) : (IData)(
                                                          (0x1000U 
                                                           == 
                                                           (0x3000U 
                                                            & vlSelf->inst)))))));
    bufp->fullBit(oldp+122,((((vlSelf->rs1_bo >> 0x1fU) 
                              == (((1U & ((0x4000U 
                                           & vlSelf->inst)
                                           ? (vlSelf->inst 
                                              >> 0xdU)
                                           : (IData)(
                                                     (0x1000U 
                                                      == 
                                                      (0x3000U 
                                                       & vlSelf->inst)))))
                                    ? ((IData)(1U) 
                                       + (~ vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2))
                                    : vlSelf->cpu_v1__DOT__EXU_inst0__DOT__add_2) 
                                  >> 0x1fU)) & ((vlSelf->cpu_v1__DOT__EXU_inst0__DOT__ALU_i0__DOT__result 
                                                 >> 0x1fU) 
                                                != 
                                                (vlSelf->rs1_bo 
                                                 >> 0x1fU)))));
    bufp->fullIData(oldp+123,(((1U & ((0x4000U & vlSelf->inst)
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
    bufp->fullWData(oldp+124,(__Vtemp_h775f2483__0),210);
    bufp->fullIData(oldp+131,(0x80000005U),32);
    bufp->fullIData(oldp+132,(2U),32);
    bufp->fullIData(oldp+133,(7U),32);
    bufp->fullIData(oldp+134,(0x20U),32);
    bufp->fullCData(oldp+135,(0x20U),6);
    bufp->fullIData(oldp+136,(0U),32);
    bufp->fullIData(oldp+137,(0U),32);
    bufp->fullIData(oldp+138,(0x27U),32);
    bufp->fullIData(oldp+139,(2U),32);
    bufp->fullIData(oldp+140,(0xcU),32);
    bufp->fullIData(oldp+141,(9U),32);
    bufp->fullIData(oldp+142,(3U),32);
    bufp->fullCData(oldp+143,(0U),3);
    __Vtemp_hf1926d6b__0[0U] = 0xb3e6f4bdU;
    __Vtemp_hf1926d6b__0[1U] = 0xb0689adfU;
    __Vtemp_hf1926d6b__0[2U] = 0x199c711U;
    bufp->fullWData(oldp+144,(__Vtemp_hf1926d6b__0),90);
    bufp->fullIData(oldp+147,(0xaU),32);
    bufp->fullIData(oldp+148,(9U),32);
    bufp->fullIData(oldp+149,(6U),32);
    bufp->fullIData(oldp+150,(0x23U),32);
    bufp->fullIData(oldp+151,(6U),32);
    bufp->fullIData(oldp+152,(5U),32);
}
