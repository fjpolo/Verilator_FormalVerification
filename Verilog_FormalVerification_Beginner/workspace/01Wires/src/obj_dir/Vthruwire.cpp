// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vthruwire.h for the primary calling header

#include "Vthruwire.h"
#include "Vthruwire__Syms.h"

//==========

VL_CTOR_IMP(Vthruwire) {
    Vthruwire__Syms* __restrict vlSymsp = __VlSymsp = new Vthruwire__Syms(this, name());
    Vthruwire* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vthruwire::__Vconfigure(Vthruwire__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vthruwire::~Vthruwire() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vthruwire::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vthruwire::eval\n"); );
    Vthruwire__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vthruwire* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("thruwire.v", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vthruwire::_eval_initial_loop(Vthruwire__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("thruwire.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vthruwire::_combo__TOP__1(Vthruwire__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vthruwire::_combo__TOP__1\n"); );
    Vthruwire* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_led = vlTOPp->i_sw;
}

void Vthruwire::_eval(Vthruwire__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vthruwire::_eval\n"); );
    Vthruwire* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vthruwire::_eval_initial(Vthruwire__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vthruwire::_eval_initial\n"); );
    Vthruwire* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vthruwire::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vthruwire::final\n"); );
    // Variables
    Vthruwire__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vthruwire* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vthruwire::_eval_settle(Vthruwire__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vthruwire::_eval_settle\n"); );
    Vthruwire* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vthruwire::_change_request(Vthruwire__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vthruwire::_change_request\n"); );
    Vthruwire* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vthruwire::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vthruwire::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_sw & 0xfeU))) {
        Verilated::overWidthError("i_sw");}
}
#endif  // VL_DEBUG

void Vthruwire::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vthruwire::_ctor_var_reset\n"); );
    // Body
    i_sw = VL_RAND_RESET_I(1);
    o_led = VL_RAND_RESET_I(1);
}
