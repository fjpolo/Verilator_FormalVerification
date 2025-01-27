// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vapb_slave__pch.h"

//============================================================
// Constructors

Vapb_slave::Vapb_slave(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vapb_slave__Syms(contextp(), _vcname__, this)}
    , i_clk{vlSymsp->TOP.i_clk}
    , i_reset_n{vlSymsp->TOP.i_reset_n}
    , i_paddr{vlSymsp->TOP.i_paddr}
    , i_pwrite{vlSymsp->TOP.i_pwrite}
    , i_psel{vlSymsp->TOP.i_psel}
    , i_penable{vlSymsp->TOP.i_penable}
    , o_pslverr{vlSymsp->TOP.o_pslverr}
    , o_pready{vlSymsp->TOP.o_pready}
    , o_hw_ctl{vlSymsp->TOP.o_hw_ctl}
    , i_hw_sts{vlSymsp->TOP.i_hw_sts}
    , i_pwdata{vlSymsp->TOP.i_pwdata}
    , o_prdata{vlSymsp->TOP.o_prdata}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vapb_slave::Vapb_slave(const char* _vcname__)
    : Vapb_slave(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vapb_slave::~Vapb_slave() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vapb_slave___024root___eval_debug_assertions(Vapb_slave___024root* vlSelf);
#endif  // VL_DEBUG
void Vapb_slave___024root___eval_static(Vapb_slave___024root* vlSelf);
void Vapb_slave___024root___eval_initial(Vapb_slave___024root* vlSelf);
void Vapb_slave___024root___eval_settle(Vapb_slave___024root* vlSelf);
void Vapb_slave___024root___eval(Vapb_slave___024root* vlSelf);

void Vapb_slave::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vapb_slave::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vapb_slave___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vapb_slave___024root___eval_static(&(vlSymsp->TOP));
        Vapb_slave___024root___eval_initial(&(vlSymsp->TOP));
        Vapb_slave___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vapb_slave___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vapb_slave::eventsPending() { return false; }

uint64_t Vapb_slave::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vapb_slave::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vapb_slave___024root___eval_final(Vapb_slave___024root* vlSelf);

VL_ATTR_COLD void Vapb_slave::final() {
    Vapb_slave___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vapb_slave::hierName() const { return vlSymsp->name(); }
const char* Vapb_slave::modelName() const { return "Vapb_slave"; }
unsigned Vapb_slave::threads() const { return 1; }
void Vapb_slave::prepareClone() const { contextp()->prepareClone(); }
void Vapb_slave::atClone() const {
    contextp()->threadPoolpOnClone();
}
