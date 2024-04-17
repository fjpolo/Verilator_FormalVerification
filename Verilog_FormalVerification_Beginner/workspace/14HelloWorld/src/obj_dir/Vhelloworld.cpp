// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vhelloworld.h for the primary calling header

#include "Vhelloworld.h"
#include "Vhelloworld__Syms.h"

//==========
CData/*7:0*/ Vhelloworld::__Vtable1_helloworld__DOT__tx_data[16];

VL_CTOR_IMP(Vhelloworld) {
    Vhelloworld__Syms* __restrict vlSymsp = __VlSymsp = new Vhelloworld__Syms(this, name());
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vhelloworld::__Vconfigure(Vhelloworld__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vhelloworld::~Vhelloworld() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vhelloworld::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vhelloworld::eval\n"); );
    Vhelloworld__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("helloworld.v", 36, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vhelloworld::_eval_initial_loop(Vhelloworld__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("helloworld.v", 36, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vhelloworld::_initial__TOP__1(Vhelloworld__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_initial__TOP__1\n"); );
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_setup = 0x364U;
    vlTOPp->helloworld__DOT__tx_restart = 0U;
    vlTOPp->helloworld__DOT__tx_stb = 0U;
    vlTOPp->helloworld__DOT__tx_busy = 0U;
    vlTOPp->helloworld__DOT__transmitter__DOT__state = 0xfU;
    vlTOPp->helloworld__DOT__transmitter__DOT__baud_stb = 1U;
    vlTOPp->helloworld__DOT__transmitter__DOT__counter = 0U;
    vlTOPp->helloworld__DOT__transmitter__DOT__lcl_data = 0x1ffU;
    vlTOPp->helloworld__DOT__hz_counter = 0x16U;
    vlTOPp->helloworld__DOT__tx_index = 0U;
}

VL_INLINE_OPT void Vhelloworld::_sequent__TOP__2(Vhelloworld__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_sequent__TOP__2\n"); );
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*3:0*/ __Vtableidx1;
    CData/*3:0*/ __Vdly__helloworld__DOT__tx_index;
    CData/*0:0*/ __Vdly__helloworld__DOT__tx_stb;
    CData/*0:0*/ __Vdly__helloworld__DOT__tx_busy;
    CData/*3:0*/ __Vdly__helloworld__DOT__transmitter__DOT__state;
    CData/*0:0*/ __Vdly__helloworld__DOT__transmitter__DOT__baud_stb;
    SData/*8:0*/ __Vdly__helloworld__DOT__transmitter__DOT__lcl_data;
    IData/*27:0*/ __Vdly__helloworld__DOT__hz_counter;
    IData/*23:0*/ __Vdly__helloworld__DOT__transmitter__DOT__counter;
    // Body
    __Vdly__helloworld__DOT__hz_counter = vlTOPp->helloworld__DOT__hz_counter;
    __Vdly__helloworld__DOT__tx_index = vlTOPp->helloworld__DOT__tx_index;
    __Vdly__helloworld__DOT__transmitter__DOT__state 
        = vlTOPp->helloworld__DOT__transmitter__DOT__state;
    __Vdly__helloworld__DOT__tx_busy = vlTOPp->helloworld__DOT__tx_busy;
    __Vdly__helloworld__DOT__transmitter__DOT__baud_stb 
        = vlTOPp->helloworld__DOT__transmitter__DOT__baud_stb;
    __Vdly__helloworld__DOT__transmitter__DOT__counter 
        = vlTOPp->helloworld__DOT__transmitter__DOT__counter;
    __Vdly__helloworld__DOT__tx_stb = vlTOPp->helloworld__DOT__tx_stb;
    __Vdly__helloworld__DOT__transmitter__DOT__lcl_data 
        = vlTOPp->helloworld__DOT__transmitter__DOT__lcl_data;
    __Vdly__helloworld__DOT__hz_counter = ((0U == vlTOPp->helloworld__DOT__hz_counter)
                                            ? 0x5f5e0ffU
                                            : (0xfffffffU 
                                               & (vlTOPp->helloworld__DOT__hz_counter 
                                                  - (IData)(1U))));
    if (((IData)(vlTOPp->helloworld__DOT__tx_stb) & 
         (~ (IData)(vlTOPp->helloworld__DOT__tx_busy)))) {
        __Vdly__helloworld__DOT__tx_index = (0xfU & 
                                             ((IData)(1U) 
                                              + (IData)(vlTOPp->helloworld__DOT__tx_index)));
    }
    if (((IData)(vlTOPp->helloworld__DOT__tx_stb) & 
         (~ (IData)(vlTOPp->helloworld__DOT__tx_busy)))) {
        __Vdly__helloworld__DOT__tx_busy = 1U;
        __Vdly__helloworld__DOT__transmitter__DOT__state = 0U;
    } else {
        if (vlTOPp->helloworld__DOT__transmitter__DOT__baud_stb) {
            if ((0xfU == (IData)(vlTOPp->helloworld__DOT__transmitter__DOT__state))) {
                __Vdly__helloworld__DOT__tx_busy = 0U;
                __Vdly__helloworld__DOT__transmitter__DOT__state = 0xfU;
            } else {
                if ((8U > (IData)(vlTOPp->helloworld__DOT__transmitter__DOT__state))) {
                    __Vdly__helloworld__DOT__transmitter__DOT__state 
                        = (0xfU & ((IData)(1U) + (IData)(vlTOPp->helloworld__DOT__transmitter__DOT__state)));
                    __Vdly__helloworld__DOT__tx_busy = 1U;
                } else {
                    __Vdly__helloworld__DOT__tx_busy = 1U;
                    __Vdly__helloworld__DOT__transmitter__DOT__state = 0xfU;
                }
            }
        }
    }
    if (((IData)(vlTOPp->helloworld__DOT__tx_stb) & 
         (~ (IData)(vlTOPp->helloworld__DOT__tx_busy)))) {
        __Vdly__helloworld__DOT__transmitter__DOT__counter = 0x363U;
        __Vdly__helloworld__DOT__transmitter__DOT__baud_stb = 0U;
    } else {
        if (vlTOPp->helloworld__DOT__transmitter__DOT__baud_stb) {
            if ((0xfU != (IData)(vlTOPp->helloworld__DOT__transmitter__DOT__state))) {
                __Vdly__helloworld__DOT__transmitter__DOT__counter = 0x363U;
                __Vdly__helloworld__DOT__transmitter__DOT__baud_stb = 0U;
            }
        } else {
            __Vdly__helloworld__DOT__transmitter__DOT__baud_stb 
                = (1U == vlTOPp->helloworld__DOT__transmitter__DOT__counter);
            __Vdly__helloworld__DOT__transmitter__DOT__counter 
                = (0xffffffU & (vlTOPp->helloworld__DOT__transmitter__DOT__counter 
                                - (IData)(1U)));
        }
    }
    if (vlTOPp->helloworld__DOT__tx_restart) {
        __Vdly__helloworld__DOT__tx_stb = 1U;
    } else {
        if ((((IData)(vlTOPp->helloworld__DOT__tx_stb) 
              & (~ (IData)(vlTOPp->helloworld__DOT__tx_busy))) 
             & (0xfU == (IData)(vlTOPp->helloworld__DOT__tx_index)))) {
            __Vdly__helloworld__DOT__tx_stb = 0U;
        }
    }
    if (((IData)(vlTOPp->helloworld__DOT__tx_stb) & 
         (~ (IData)(vlTOPp->helloworld__DOT__tx_busy)))) {
        __Vdly__helloworld__DOT__transmitter__DOT__lcl_data 
            = ((IData)(vlTOPp->helloworld__DOT__tx_data) 
               << 1U);
    } else {
        if (vlTOPp->helloworld__DOT__transmitter__DOT__baud_stb) {
            __Vdly__helloworld__DOT__transmitter__DOT__lcl_data 
                = (0x100U | (0xffU & ((IData)(vlTOPp->helloworld__DOT__transmitter__DOT__lcl_data) 
                                      >> 1U)));
        }
    }
    vlTOPp->helloworld__DOT__transmitter__DOT__counter 
        = __Vdly__helloworld__DOT__transmitter__DOT__counter;
    vlTOPp->helloworld__DOT__transmitter__DOT__state 
        = __Vdly__helloworld__DOT__transmitter__DOT__state;
    vlTOPp->helloworld__DOT__transmitter__DOT__baud_stb 
        = __Vdly__helloworld__DOT__transmitter__DOT__baud_stb;
    vlTOPp->helloworld__DOT__tx_stb = __Vdly__helloworld__DOT__tx_stb;
    vlTOPp->helloworld__DOT__tx_busy = __Vdly__helloworld__DOT__tx_busy;
    vlTOPp->helloworld__DOT__transmitter__DOT__lcl_data 
        = __Vdly__helloworld__DOT__transmitter__DOT__lcl_data;
    vlTOPp->helloworld__DOT__tx_restart = (1U == vlTOPp->helloworld__DOT__hz_counter);
    vlTOPp->o_uart_tx = (1U & (IData)(vlTOPp->helloworld__DOT__transmitter__DOT__lcl_data));
    __Vtableidx1 = vlTOPp->helloworld__DOT__tx_index;
    vlTOPp->helloworld__DOT__tx_data = vlTOPp->__Vtable1_helloworld__DOT__tx_data
        [__Vtableidx1];
    vlTOPp->helloworld__DOT__hz_counter = __Vdly__helloworld__DOT__hz_counter;
    vlTOPp->helloworld__DOT__tx_index = __Vdly__helloworld__DOT__tx_index;
}

void Vhelloworld::_settle__TOP__3(Vhelloworld__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_settle__TOP__3\n"); );
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->o_uart_tx = (1U & (IData)(vlTOPp->helloworld__DOT__transmitter__DOT__lcl_data));
}

void Vhelloworld::_eval(Vhelloworld__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_eval\n"); );
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->i_clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__i_clk)))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
        vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    }
    // Final
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vhelloworld::_eval_initial(Vhelloworld__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_eval_initial\n"); );
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vm_traceActivity = (1U | vlTOPp->__Vm_traceActivity);
    vlTOPp->__Vclklast__TOP__i_clk = vlTOPp->i_clk;
}

void Vhelloworld::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::final\n"); );
    // Variables
    Vhelloworld__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vhelloworld::_eval_settle(Vhelloworld__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_eval_settle\n"); );
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__3(vlSymsp);
}

VL_INLINE_OPT QData Vhelloworld::_change_request(Vhelloworld__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_change_request\n"); );
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vhelloworld::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((i_clk & 0xfeU))) {
        Verilated::overWidthError("i_clk");}
}
#endif  // VL_DEBUG

void Vhelloworld::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vhelloworld::_ctor_var_reset\n"); );
    // Body
    i_clk = VL_RAND_RESET_I(1);
    o_uart_tx = VL_RAND_RESET_I(1);
    o_setup = VL_RAND_RESET_I(32);
    helloworld__DOT__tx_restart = VL_RAND_RESET_I(1);
    helloworld__DOT__hz_counter = VL_RAND_RESET_I(28);
    helloworld__DOT__tx_busy = VL_RAND_RESET_I(1);
    helloworld__DOT__tx_stb = VL_RAND_RESET_I(1);
    helloworld__DOT__tx_index = VL_RAND_RESET_I(4);
    helloworld__DOT__tx_data = VL_RAND_RESET_I(8);
    helloworld__DOT__transmitter__DOT__counter = VL_RAND_RESET_I(24);
    helloworld__DOT__transmitter__DOT__state = VL_RAND_RESET_I(4);
    helloworld__DOT__transmitter__DOT__lcl_data = VL_RAND_RESET_I(9);
    helloworld__DOT__transmitter__DOT__baud_stb = VL_RAND_RESET_I(1);
    __Vtable1_helloworld__DOT__tx_data[0] = 0x48U;
    __Vtable1_helloworld__DOT__tx_data[1] = 0x65U;
    __Vtable1_helloworld__DOT__tx_data[2] = 0x6cU;
    __Vtable1_helloworld__DOT__tx_data[3] = 0x6cU;
    __Vtable1_helloworld__DOT__tx_data[4] = 0x6fU;
    __Vtable1_helloworld__DOT__tx_data[5] = 0x2cU;
    __Vtable1_helloworld__DOT__tx_data[6] = 0x20U;
    __Vtable1_helloworld__DOT__tx_data[7] = 0x57U;
    __Vtable1_helloworld__DOT__tx_data[8] = 0x6fU;
    __Vtable1_helloworld__DOT__tx_data[9] = 0x72U;
    __Vtable1_helloworld__DOT__tx_data[10] = 0x6cU;
    __Vtable1_helloworld__DOT__tx_data[11] = 0x64U;
    __Vtable1_helloworld__DOT__tx_data[12] = 0x21U;
    __Vtable1_helloworld__DOT__tx_data[13] = 0x20U;
    __Vtable1_helloworld__DOT__tx_data[14] = 0xaU;
    __Vtable1_helloworld__DOT__tx_data[15] = 0xdU;
    __Vm_traceActivity = 0;
}
