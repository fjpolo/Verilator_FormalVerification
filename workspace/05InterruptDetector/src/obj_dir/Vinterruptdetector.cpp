// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vinterruptdetector.h for the primary calling header

#include "Vinterruptdetector.h"
#include "Vinterruptdetector__Syms.h"

//==========

VL_CTOR_IMP(Vinterruptdetector) {
    Vinterruptdetector__Syms* __restrict vlSymsp = __VlSymsp = new Vinterruptdetector__Syms(this, name());
    Vinterruptdetector* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vinterruptdetector::__Vconfigure(Vinterruptdetector__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vinterruptdetector::~Vinterruptdetector() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vinterruptdetector::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vinterruptdetector::eval\n"); );
    Vinterruptdetector__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vinterruptdetector* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("interruptdetector.v", 4, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vinterruptdetector::_eval_initial_loop(Vinterruptdetector__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("interruptdetector.v", 4, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vinterruptdetector::_combo__TOP__1(Vinterruptdetector__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterruptdetector::_combo__TOP__1\n"); );
    Vinterruptdetector* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_irq = (0U != (IData)(vlTOPp->i_irq_source));
}

void Vinterruptdetector::_eval(Vinterruptdetector__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterruptdetector::_eval\n"); );
    Vinterruptdetector* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

void Vinterruptdetector::_eval_initial(Vinterruptdetector__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterruptdetector::_eval_initial\n"); );
    Vinterruptdetector* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vinterruptdetector::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterruptdetector::final\n"); );
    // Variables
    Vinterruptdetector__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vinterruptdetector* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vinterruptdetector::_eval_settle(Vinterruptdetector__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterruptdetector::_eval_settle\n"); );
    Vinterruptdetector* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
}

VL_INLINE_OPT QData Vinterruptdetector::_change_request(Vinterruptdetector__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterruptdetector::_change_request\n"); );
    Vinterruptdetector* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vinterruptdetector::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterruptdetector::_eval_debug_assertions\n"); );
}
#endif  // VL_DEBUG

void Vinterruptdetector::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterruptdetector::_ctor_var_reset\n"); );
    // Body
    i_irq_source = VL_RAND_RESET_I(8);
    o_irq = VL_RAND_RESET_I(1);
}
