// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcpu_v1.h"
#include "Vcpu_v1__Syms.h"

//============================================================
// Constructors

Vcpu_v1::Vcpu_v1(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcpu_v1__Syms(contextp(), _vcname__, this)}
    , inst{vlSymsp->TOP.inst}
    , pc{vlSymsp->TOP.pc}
    , inst_out{vlSymsp->TOP.inst_out}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vcpu_v1::Vcpu_v1(const char* _vcname__)
    : Vcpu_v1(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcpu_v1::~Vcpu_v1() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcpu_v1___024root___eval_debug_assertions(Vcpu_v1___024root* vlSelf);
#endif  // VL_DEBUG
void Vcpu_v1___024root___eval_static(Vcpu_v1___024root* vlSelf);
void Vcpu_v1___024root___eval_initial(Vcpu_v1___024root* vlSelf);
void Vcpu_v1___024root___eval_settle(Vcpu_v1___024root* vlSelf);
void Vcpu_v1___024root___eval(Vcpu_v1___024root* vlSelf);

void Vcpu_v1::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcpu_v1::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcpu_v1___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vcpu_v1___024root___eval_static(&(vlSymsp->TOP));
        Vcpu_v1___024root___eval_initial(&(vlSymsp->TOP));
        Vcpu_v1___024root___eval_settle(&(vlSymsp->TOP));
    }
    // MTask 0 start
    VL_DEBUG_IF(VL_DBG_MSGF("MTask0 starting\n"););
    Verilated::mtaskId(0);
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vcpu_v1___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vcpu_v1::eventsPending() { return false; }

uint64_t Vcpu_v1::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vcpu_v1::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vcpu_v1___024root___eval_final(Vcpu_v1___024root* vlSelf);

VL_ATTR_COLD void Vcpu_v1::final() {
    Vcpu_v1___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcpu_v1::hierName() const { return vlSymsp->name(); }
const char* Vcpu_v1::modelName() const { return "Vcpu_v1"; }
unsigned Vcpu_v1::threads() const { return 1; }
