// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vparitycheck.h for the primary calling header

#include "Vparitycheck.h"
#include "Vparitycheck__Syms.h"

//==========

VL_CTOR_IMP(Vparitycheck) {
    Vparitycheck__Syms* __restrict vlSymsp = __VlSymsp = new Vparitycheck__Syms(this, name());
    Vparitycheck* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vparitycheck::__Vconfigure(Vparitycheck__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vparitycheck::~Vparitycheck() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vparitycheck::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vparitycheck::eval\n"); );
    Vparitycheck__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vparitycheck* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("paritycheck.v", 4, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vparitycheck::_eval_initial_loop(Vparitycheck__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("paritycheck.v", 4, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vparitycheck::_combo__TOP__1(Vparitycheck__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vparitycheck::_combo__TOP__1\n"); );
    Vparitycheck* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_parity = (1U & VL_REDXOR_32((IData)(vlTOPp->i_word)));
}

void Vparitycheck::_eval(Vparitycheck__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vparitycheck::_eval\n"); );
    Vparitycheck* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vparitycheck::_eval_initial(Vparitycheck__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vparitycheck::_eval_initial\n"); );
    Vparitycheck* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vparitycheck::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vparitycheck::final\n"); );
    // Variables
    Vparitycheck__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vparitycheck* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vparitycheck::_eval_settle(Vparitycheck__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vparitycheck::_eval_settle\n"); );
    Vparitycheck* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vparitycheck::_change_request(Vparitycheck__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vparitycheck::_change_request\n"); );
    Vparitycheck* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vparitycheck::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vparitycheck::_eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG

void Vparitycheck::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vparitycheck::_ctor_var_reset\n"); );
    // Body
    i_word = VL_RAND_RESET_I(8);
    o_parity = VL_RAND_RESET_I(1);
}
