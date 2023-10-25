// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmultiplexer.h for the primary calling header

#include "Vmultiplexer.h"
#include "Vmultiplexer__Syms.h"

//==========

VL_CTOR_IMP(Vmultiplexer) {
    Vmultiplexer__Syms* __restrict vlSymsp = __VlSymsp = new Vmultiplexer__Syms(this, name());
    Vmultiplexer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vmultiplexer::__Vconfigure(Vmultiplexer__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vmultiplexer::~Vmultiplexer() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vmultiplexer::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmultiplexer::eval\n"); );
    Vmultiplexer__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vmultiplexer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("multiplexer.v", 4, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vmultiplexer::_eval_initial_loop(Vmultiplexer__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("multiplexer.v", 4, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vmultiplexer::_combo__TOP__1(Vmultiplexer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmultiplexer::_combo__TOP__1\n"); );
    Vmultiplexer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_out = ((IData)(vlTOPp->i_sel) ? (IData)(vlTOPp->i_a)
                      : (IData)(vlTOPp->i_b));
}

void Vmultiplexer::_eval(Vmultiplexer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmultiplexer::_eval\n"); );
    Vmultiplexer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vmultiplexer::_eval_initial(Vmultiplexer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmultiplexer::_eval_initial\n"); );
    Vmultiplexer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vmultiplexer::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmultiplexer::final\n"); );
    // Variables
    Vmultiplexer__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vmultiplexer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vmultiplexer::_eval_settle(Vmultiplexer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmultiplexer::_eval_settle\n"); );
    Vmultiplexer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vmultiplexer::_change_request(Vmultiplexer__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmultiplexer::_change_request\n"); );
    Vmultiplexer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vmultiplexer::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmultiplexer::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_a & 0xfeU))) {
        Verilated::overWidthError("i_a");}
    if (VL_UNLIKELY((i_b & 0xfeU))) {
        Verilated::overWidthError("i_b");}
    if (VL_UNLIKELY((i_sel & 0xfeU))) {
        Verilated::overWidthError("i_sel");}
}
#endif  // VL_DEBUG

void Vmultiplexer::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmultiplexer::_ctor_var_reset\n"); );
    // Body
    i_a = VL_RAND_RESET_I(1);
    i_b = VL_RAND_RESET_I(1);
    i_sel = VL_RAND_RESET_I(1);
    o_out = VL_RAND_RESET_I(1);
}
