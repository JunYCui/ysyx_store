// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VYSYX_24100029_IFU_TB__SYMS_H_
#define VERILATED_VYSYX_24100029_IFU_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vysyx_24100029_IFU_tb.h"

// INCLUDE MODULE CLASSES
#include "Vysyx_24100029_IFU_tb___024root.h"
#include "Vysyx_24100029_IFU_tb___024unit.h"
#include "Vysyx_24100029_IFU_tb_axi4_if.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vysyx_24100029_IFU_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vysyx_24100029_IFU_tb* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vysyx_24100029_IFU_tb___024root TOP;
    Vysyx_24100029_IFU_tb_axi4_if  TOP__ysyx_24100029_IFU_tb__DOT__bus;

    // CONSTRUCTORS
    Vysyx_24100029_IFU_tb__Syms(VerilatedContext* contextp, const char* namep, Vysyx_24100029_IFU_tb* modelp);
    ~Vysyx_24100029_IFU_tb__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
