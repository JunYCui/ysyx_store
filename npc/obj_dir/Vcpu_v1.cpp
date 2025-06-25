// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcpu_v1.h"
#include "Vcpu_v1__Syms.h"
#include "verilated_vcd_c.h"
#include "verilated_dpi.h"

//============================================================
// Constructors

Vcpu_v1::Vcpu_v1(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcpu_v1__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , inst{vlSymsp->TOP.inst}
    , pc{vlSymsp->TOP.pc}
    , rs1_bo{vlSymsp->TOP.rs1_bo}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
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
    vlSymsp->__Vm_activity = true;
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
std::unique_ptr<VerilatedTraceConfig> Vcpu_v1::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vcpu_v1___024root__trace_init_top(Vcpu_v1___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vcpu_v1___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcpu_v1___024root*>(voidSelf);
    Vcpu_v1__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->scopeEscape(' ');
    tracep->pushNamePrefix(std::string{vlSymsp->name()} + ' ');
    Vcpu_v1___024root__trace_init_top(vlSelf, tracep);
    tracep->popNamePrefix();
    tracep->scopeEscape('.');
}

VL_ATTR_COLD void Vcpu_v1___024root__trace_register(Vcpu_v1___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vcpu_v1::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vcpu_v1::trace()' shall not be called after 'VerilatedVcdC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vcpu_v1___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
