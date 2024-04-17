// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vwalker.h for the primary calling header

#include "Vwalker.h"
#include "Vwalker__Syms.h"

//==========

VL_CTOR_IMP(Vwalker) {
    Vwalker__Syms* __restrict vlSymsp = __VlSymsp = new Vwalker__Syms(this, name());
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vwalker::__Vconfigure(Vwalker__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vwalker::~Vwalker() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vwalker::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vwalker::eval\n"); );
    Vwalker__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("walker.v", 4, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vwalker::_eval_initial_loop(Vwalker__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
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
            VL_FATAL_MT("walker.v", 4, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vwalker::_sequent__TOP__1(Vwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::_sequent__TOP__1\n"); );
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->walker__DOT__counter = (0x1fffU & ((IData)(1U) 
                                               + (IData)(vlTOPp->walker__DOT__counter)));
    vlTOPp->o_led = ((0xffU & (IData)(vlTOPp->walker__DOT__counter)) 
                     < (0xffU & ((IData)(vlTOPp->walker__DOT__counter) 
                                 >> 5U)));
}

void Vwalker::_settle__TOP__2(Vwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::_settle__TOP__2\n"); );
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_led = ((0xffU & (IData)(vlTOPp->walker__DOT__counter)) 
                     < (0xffU & ((IData)(vlTOPp->walker__DOT__counter) 
                                 >> 5U)));
}

void Vwalker::_eval(Vwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::_eval\n"); );
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
        vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    }
    // Final
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vwalker::_eval_initial(Vwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::_eval_initial\n"); );
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vwalker::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::final\n"); );
    // Variables
    Vwalker__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vwalker::_eval_settle(Vwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::_eval_settle\n"); );
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

VL_INLINE_OPT QData Vwalker::_change_request(Vwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::_change_request\n"); );
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vwalker::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_clk & 0xfeU))) {
        Verilated::overWidthError("i_clk");}
}
#endif  // VL_DEBUG

void Vwalker::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vwalker::_ctor_var_reset\n"); );
    // Body
    i_clk = VL_RAND_RESET_I(1);
    o_led = VL_RAND_RESET_I(1);
    walker__DOT__counter = VL_RAND_RESET_I(13);
    __Vm_traceActivity = 0;
}
