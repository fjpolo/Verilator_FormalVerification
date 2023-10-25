// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vserialtester.h for the primary calling header

#include "Vserialtester.h"
#include "Vserialtester__Syms.h"

//==========

VL_CTOR_IMP(Vserialtester) {
    Vserialtester__Syms* __restrict vlSymsp = __VlSymsp = new Vserialtester__Syms(this, name());
    Vserialtester* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vserialtester::__Vconfigure(Vserialtester__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vserialtester::~Vserialtester() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vserialtester::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vserialtester::eval\n"); );
    Vserialtester__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vserialtester* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("serialtester.v", 4, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vserialtester::_eval_initial_loop(Vserialtester__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("serialtester.v", 4, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vserialtester::_combo__TOP__1(Vserialtester__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vserialtester::_combo__TOP__1\n"); );
    Vserialtester* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->uart_tx = vlTOPp->uart_rx;
}

void Vserialtester::_eval(Vserialtester__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vserialtester::_eval\n"); );
    Vserialtester* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vserialtester::_eval_initial(Vserialtester__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vserialtester::_eval_initial\n"); );
    Vserialtester* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vserialtester::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vserialtester::final\n"); );
    // Variables
    Vserialtester__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vserialtester* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vserialtester::_eval_settle(Vserialtester__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vserialtester::_eval_settle\n"); );
    Vserialtester* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vserialtester::_change_request(Vserialtester__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vserialtester::_change_request\n"); );
    Vserialtester* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vserialtester::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vserialtester::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((uart_rx & 0xfeU))) {
        Verilated::overWidthError("uart_rx");}
}
#endif  // VL_DEBUG

void Vserialtester::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vserialtester::_ctor_var_reset\n"); );
    // Body
    uart_rx = VL_RAND_RESET_I(1);
    uart_tx = VL_RAND_RESET_I(1);
}
