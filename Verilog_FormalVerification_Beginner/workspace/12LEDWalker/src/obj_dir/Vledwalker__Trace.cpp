// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vledwalker__Syms.h"


//======================

void Vledwalker::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vledwalker* t = (Vledwalker*)userthis;
    Vledwalker__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vledwalker::traceChgThis(Vledwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 1U))))) {
            vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
        }
        vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vledwalker::traceChgThis__2(Vledwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBus(c+1,(vlTOPp->ledwalker__DOT__led_index),4);
        vcdp->chgBus(c+9,(vlTOPp->ledwalker__DOT__wait_counter),32);
        vcdp->chgBit(c+17,(vlTOPp->ledwalker__DOT__stb));
    }
}

void Vledwalker::traceChgThis__3(Vledwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+25,(vlTOPp->i_clk));
        vcdp->chgBus(c+33,(vlTOPp->o_led),8);
    }
}
