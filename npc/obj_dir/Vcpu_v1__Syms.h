// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VCPU_V1__SYMS_H_
#define VERILATED_VCPU_V1__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vcpu_v1.h"

// INCLUDE MODULE CLASSES
#include "Vcpu_v1___024root.h"
#include "Vcpu_v1___024unit.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class Vcpu_v1__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vcpu_v1* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vcpu_v1___024root              TOP;
    Vcpu_v1___024unit              TOP____024unit;

    // CONSTRUCTORS
    Vcpu_v1__Syms(VerilatedContext* contextp, const char* namep, Vcpu_v1* modelp);
    ~Vcpu_v1__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
