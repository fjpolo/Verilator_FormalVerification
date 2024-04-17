// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vonehzblinky.h for the primary calling header

#include "Vonehzblinky.h"
#include "Vonehzblinky__Syms.h"

//==========

VL_CTOR_IMP(Vonehzblinky) {
    Vonehzblinky__Syms* __restrict vlSymsp = __VlSymsp = new Vonehzblinky__Syms(this, name());
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vonehzblinky::__Vconfigure(Vonehzblinky__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vonehzblinky::~Vonehzblinky() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vonehzblinky::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vonehzblinky::eval\n"); );
    Vonehzblinky__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("onehzblinky.v", 4, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vonehzblinky::_eval_initial_loop(Vonehzblinky__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("onehzblinky.v", 4, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vonehzblinky::_sequent__TOP__1(Vonehzblinky__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_sequent__TOP__1\n"); );
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->onehzblinky__DOT__counter = ((IData)(0x2aU) 
                                         + vlTOPp->onehzblinky__DOT__counter);
    vlTOPp->o_led = (1U & (vlTOPp->onehzblinky__DOT__counter 
                           >> 0x1fU));
}

void Vonehzblinky::_initial__TOP__2(Vonehzblinky__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_initial__TOP__2\n"); );
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->onehzblinky__DOT__counter = 0U;
}

void Vonehzblinky::_settle__TOP__3(Vonehzblinky__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_settle__TOP__3\n"); );
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_led = (1U & (vlTOPp->onehzblinky__DOT__counter 
                           >> 0x1fU));
}

void Vonehzblinky::_eval(Vonehzblinky__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_eval\n"); );
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
        vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    }
    // Final
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vonehzblinky::_eval_initial(Vonehzblinky__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_eval_initial\n"); );
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
    vlTOPp->_initial__TOP__2(vlSymsp);
    vlTOPp->__Vm_traceActivity = (1U | vlTOPp->__Vm_traceActivity);
}

void Vonehzblinky::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::final\n"); );
    // Variables
    Vonehzblinky__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vonehzblinky::_eval_settle(Vonehzblinky__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_eval_settle\n"); );
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__3(vlSymsp);
}

VL_INLINE_OPT QData Vonehzblinky::_change_request(Vonehzblinky__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_change_request\n"); );
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vonehzblinky::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_clk & 0xfeU))) {
        Verilated::overWidthError("i_clk");}
}
#endif  // VL_DEBUG

void Vonehzblinky::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vonehzblinky::_ctor_var_reset\n"); );
    // Body
    i_clk = VL_RAND_RESET_I(1);
    o_led = VL_RAND_RESET_I(1);
    onehzblinky__DOT__counter = VL_RAND_RESET_I(32);
    __Vm_traceActivity = 0;
}
