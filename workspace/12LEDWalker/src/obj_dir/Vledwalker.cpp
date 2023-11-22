// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vledwalker.h for the primary calling header

#include "Vledwalker.h"
#include "Vledwalker__Syms.h"

//==========
CData/*7:0*/ Vledwalker::__Vtable1_o_led[16];

VL_CTOR_IMP(Vledwalker) {
    Vledwalker__Syms* __restrict vlSymsp = __VlSymsp = new Vledwalker__Syms(this, name());
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vledwalker::__Vconfigure(Vledwalker__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vledwalker::~Vledwalker() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vledwalker::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vledwalker::eval\n"); );
    Vledwalker__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("ledwalker.v", 32, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vledwalker::_eval_initial_loop(Vledwalker__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("ledwalker.v", 32, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vledwalker::_initial__TOP__1(Vledwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::_initial__TOP__1\n"); );
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_led = 1U;
    vlTOPp->ledwalker__DOT__led_index = 0U;
    vlTOPp->ledwalker__DOT__stb = 0U;
    vlTOPp->ledwalker__DOT__wait_counter = 0x3e7U;
}

VL_INLINE_OPT void Vledwalker::_sequent__TOP__2(Vledwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::_sequent__TOP__2\n"); );
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*3:0*/ __Vtableidx1;
    IData/*31:0*/ __Vdly__ledwalker__DOT__wait_counter;
    // Body
    __Vdly__ledwalker__DOT__wait_counter = vlTOPp->ledwalker__DOT__wait_counter;
    __Vdly__ledwalker__DOT__wait_counter = ((0U == vlTOPp->ledwalker__DOT__wait_counter)
                                             ? 0x3e7U
                                             : (vlTOPp->ledwalker__DOT__wait_counter 
                                                - (IData)(1U)));
    __Vtableidx1 = vlTOPp->ledwalker__DOT__led_index;
    vlTOPp->o_led = vlTOPp->__Vtable1_o_led[__Vtableidx1];
    if (vlTOPp->ledwalker__DOT__stb) {
        vlTOPp->ledwalker__DOT__led_index = ((0xcU 
                                              < (IData)(vlTOPp->ledwalker__DOT__led_index))
                                              ? 0U : 
                                             (0xfU 
                                              & ((IData)(1U) 
                                                 + (IData)(vlTOPp->ledwalker__DOT__led_index))));
    }
    vlTOPp->ledwalker__DOT__stb = (0U == vlTOPp->ledwalker__DOT__wait_counter);
    vlTOPp->ledwalker__DOT__wait_counter = __Vdly__ledwalker__DOT__wait_counter;
}

void Vledwalker::_eval(Vledwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::_eval\n"); );
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk)))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
        vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    }
    // Final
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vledwalker::_eval_initial(Vledwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::_eval_initial\n"); );
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vm_traceActivity = (1U | vlTOPp->__Vm_traceActivity);
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vledwalker::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::final\n"); );
    // Variables
    Vledwalker__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vledwalker::_eval_settle(Vledwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::_eval_settle\n"); );
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

VL_INLINE_OPT QData Vledwalker::_change_request(Vledwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::_change_request\n"); );
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vledwalker::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_clk & 0xfeU))) {
        Verilated::overWidthError("i_clk");}
}
#endif  // VL_DEBUG

void Vledwalker::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vledwalker::_ctor_var_reset\n"); );
    // Body
    i_clk = VL_RAND_RESET_I(1);
    o_led = VL_RAND_RESET_I(8);
    ledwalker__DOT__led_index = VL_RAND_RESET_I(4);
    ledwalker__DOT__wait_counter = VL_RAND_RESET_I(32);
    ledwalker__DOT__stb = VL_RAND_RESET_I(1);
    __Vtable1_o_led[0] = 1U;
    __Vtable1_o_led[1] = 2U;
    __Vtable1_o_led[2] = 4U;
    __Vtable1_o_led[3] = 8U;
    __Vtable1_o_led[4] = 0x10U;
    __Vtable1_o_led[5] = 0x20U;
    __Vtable1_o_led[6] = 0x40U;
    __Vtable1_o_led[7] = 0x80U;
    __Vtable1_o_led[8] = 0x40U;
    __Vtable1_o_led[9] = 0x20U;
    __Vtable1_o_led[10] = 0x10U;
    __Vtable1_o_led[11] = 8U;
    __Vtable1_o_led[12] = 4U;
    __Vtable1_o_led[13] = 2U;
    __Vtable1_o_led[14] = 1U;
    __Vtable1_o_led[15] = 1U;
    __Vm_traceActivity = 0;
}
