// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vreqwalker.h for the primary calling header

#include "Vreqwalker.h"
#include "Vreqwalker__Syms.h"

//==========
CData/*5:0*/ Vreqwalker::__Vtable1_o_led[16];

VL_CTOR_IMP(Vreqwalker) {
    Vreqwalker__Syms* __restrict vlSymsp = __VlSymsp = new Vreqwalker__Syms(this, name());
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vreqwalker::__Vconfigure(Vreqwalker__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vreqwalker::~Vreqwalker() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vreqwalker::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vreqwalker::eval\n"); );
    Vreqwalker__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("reqwalker.v", 30, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vreqwalker::_eval_initial_loop(Vreqwalker__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("reqwalker.v", 30, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vreqwalker::_initial__TOP__1(Vreqwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_initial__TOP__1\n"); );
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_ack = 0U;
    vlTOPp->o_led = 0U;
    vlTOPp->reqwalker__DOT__state = 0U;
}

VL_INLINE_OPT void Vreqwalker::_sequent__TOP__2(Vreqwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_sequent__TOP__2\n"); );
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*3:0*/ __Vdly__reqwalker__DOT__state;
    // Body
    __Vdly__reqwalker__DOT__state = vlTOPp->reqwalker__DOT__state;
    vlTOPp->o_ack = ((IData)(vlTOPp->i_stb) & (~ (IData)(vlTOPp->o_stall)));
    if ((((IData)(vlTOPp->i_stb) & (IData)(vlTOPp->i_we)) 
         & (~ (IData)(vlTOPp->o_stall)))) {
        __Vdly__reqwalker__DOT__state = 1U;
    } else {
        if ((0xbU <= (IData)(vlTOPp->reqwalker__DOT__state))) {
            __Vdly__reqwalker__DOT__state = 0U;
        } else {
            if ((0U != (IData)(vlTOPp->reqwalker__DOT__state))) {
                __Vdly__reqwalker__DOT__state = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->reqwalker__DOT__state)));
            }
        }
    }
    vlTOPp->reqwalker__DOT__state = __Vdly__reqwalker__DOT__state;
    vlTOPp->o_data = vlTOPp->reqwalker__DOT__state;
    vlTOPp->__Vtableidx1 = vlTOPp->reqwalker__DOT__state;
    if (vlTOPp->__Vtablechg1[vlTOPp->__Vtableidx1]) {
        vlTOPp->o_led = vlTOPp->__Vtable1_o_led[vlTOPp->__Vtableidx1];
    }
}

void Vreqwalker::_settle__TOP__3(Vreqwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_settle__TOP__3\n"); );
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_data = vlTOPp->reqwalker__DOT__state;
    vlTOPp->o_stall = ((0U != (IData)(vlTOPp->reqwalker__DOT__state)) 
                       & (IData)(vlTOPp->i_we));
    vlTOPp->__Vtableidx1 = vlTOPp->reqwalker__DOT__state;
    if (vlTOPp->__Vtablechg1[vlTOPp->__Vtableidx1]) {
        vlTOPp->o_led = vlTOPp->__Vtable1_o_led[vlTOPp->__Vtableidx1];
    }
}

VL_INLINE_OPT void Vreqwalker::_combo__TOP__4(Vreqwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_combo__TOP__4\n"); );
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_stall = ((0U != (IData)(vlTOPp->reqwalker__DOT__state)) 
                       & (IData)(vlTOPp->i_we));
}

void Vreqwalker::_eval(Vreqwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_eval\n"); );
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk)))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
        vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    }
    vlTOPp->_combo__TOP__4(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vreqwalker::_eval_initial(Vreqwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_eval_initial\n"); );
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vm_traceActivity = (1U | vlTOPp->__Vm_traceActivity);
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vreqwalker::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::final\n"); );
    // Variables
    Vreqwalker__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vreqwalker::_eval_settle(Vreqwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_eval_settle\n"); );
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__3(vlSymsp);
}

VL_INLINE_OPT QData Vreqwalker::_change_request(Vreqwalker__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_change_request\n"); );
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vreqwalker::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_clk & 0xfeU))) {
        Verilated::overWidthError("i_clk");}
    if (VL_UNLIKELY((i_cyc & 0xfeU))) {
        Verilated::overWidthError("i_cyc");}
    if (VL_UNLIKELY((i_stb & 0xfeU))) {
        Verilated::overWidthError("i_stb");}
    if (VL_UNLIKELY((i_we & 0xfeU))) {
        Verilated::overWidthError("i_we");}
    if (VL_UNLIKELY((i_addr & 0xfeU))) {
        Verilated::overWidthError("i_addr");}
}
#endif  // VL_DEBUG

void Vreqwalker::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vreqwalker::_ctor_var_reset\n"); );
    // Body
    i_clk = VL_RAND_RESET_I(1);
    i_cyc = VL_RAND_RESET_I(1);
    i_stb = VL_RAND_RESET_I(1);
    i_we = VL_RAND_RESET_I(1);
    i_addr = VL_RAND_RESET_I(1);
    i_data = VL_RAND_RESET_I(32);
    o_stall = VL_RAND_RESET_I(1);
    o_ack = VL_RAND_RESET_I(1);
    o_data = VL_RAND_RESET_I(32);
    o_led = VL_RAND_RESET_I(6);
    reqwalker__DOT__state = VL_RAND_RESET_I(4);
    __Vtableidx1 = 0;
    __Vtablechg1[0] = 0U;
    __Vtablechg1[1] = 1U;
    __Vtablechg1[2] = 1U;
    __Vtablechg1[3] = 1U;
    __Vtablechg1[4] = 1U;
    __Vtablechg1[5] = 1U;
    __Vtablechg1[6] = 1U;
    __Vtablechg1[7] = 1U;
    __Vtablechg1[8] = 1U;
    __Vtablechg1[9] = 1U;
    __Vtablechg1[10] = 1U;
    __Vtablechg1[11] = 1U;
    __Vtablechg1[12] = 0U;
    __Vtablechg1[13] = 0U;
    __Vtablechg1[14] = 0U;
    __Vtablechg1[15] = 0U;
    __Vtable1_o_led[0] = 0U;
    __Vtable1_o_led[1] = 1U;
    __Vtable1_o_led[2] = 2U;
    __Vtable1_o_led[3] = 4U;
    __Vtable1_o_led[4] = 8U;
    __Vtable1_o_led[5] = 0x10U;
    __Vtable1_o_led[6] = 0x20U;
    __Vtable1_o_led[7] = 0x10U;
    __Vtable1_o_led[8] = 8U;
    __Vtable1_o_led[9] = 4U;
    __Vtable1_o_led[10] = 2U;
    __Vtable1_o_led[11] = 1U;
    __Vtable1_o_led[12] = 0U;
    __Vtable1_o_led[13] = 0U;
    __Vtable1_o_led[14] = 0U;
    __Vtable1_o_led[15] = 0U;
    __Vm_traceActivity = 0;
}
