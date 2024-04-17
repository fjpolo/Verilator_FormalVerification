// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmaskbus.h for the primary calling header

#include "Vmaskbus.h"
#include "Vmaskbus__Syms.h"

//==========

VL_CTOR_IMP(Vmaskbus) {
    Vmaskbus__Syms* __restrict vlSymsp = __VlSymsp = new Vmaskbus__Syms(this, name());
    Vmaskbus* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vmaskbus::__Vconfigure(Vmaskbus__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vmaskbus::~Vmaskbus() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vmaskbus::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmaskbus::eval\n"); );
    Vmaskbus__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vmaskbus* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("maskbus.v", 4, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vmaskbus::_eval_initial_loop(Vmaskbus__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("maskbus.v", 4, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vmaskbus::_combo__TOP__1(Vmaskbus__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmaskbus::_combo__TOP__1\n"); );
    Vmaskbus* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_led = (0x33U ^ (IData)(vlTOPp->i_sw));
}

void Vmaskbus::_eval(Vmaskbus__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmaskbus::_eval\n"); );
    Vmaskbus* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vmaskbus::_eval_initial(Vmaskbus__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmaskbus::_eval_initial\n"); );
    Vmaskbus* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vmaskbus::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmaskbus::final\n"); );
    // Variables
    Vmaskbus__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vmaskbus* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vmaskbus::_eval_settle(Vmaskbus__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmaskbus::_eval_settle\n"); );
    Vmaskbus* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vmaskbus::_change_request(Vmaskbus__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmaskbus::_change_request\n"); );
    Vmaskbus* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vmaskbus::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmaskbus::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_sw & 0xc0U))) {
        Verilated::overWidthError("i_sw");}
}
#endif  // VL_DEBUG

void Vmaskbus::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmaskbus::_ctor_var_reset\n"); );
    // Body
    i_sw = VL_RAND_RESET_I(6);
    o_led = VL_RAND_RESET_I(6);
}
