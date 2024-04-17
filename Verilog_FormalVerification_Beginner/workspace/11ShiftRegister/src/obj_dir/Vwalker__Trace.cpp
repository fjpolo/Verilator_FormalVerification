// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vwalker__Syms.h"


//======================

void Vwalker::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vwalker* t = (Vwalker*)userthis;
    Vwalker__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vwalker::traceChgThis(Vwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY((2U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
        }
        vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vwalker::traceChgThis__2(Vwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBus(c+1,(vlTOPp->walker__DOT__counter),13);
    }
}

void Vwalker::traceChgThis__3(Vwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+9,(vlTOPp->i_clk));
        vcdp->chgBit(c+17,(vlTOPp->o_led));
    }
}
