// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdimmer__Syms.h"


//======================

void Vdimmer::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vdimmer* t = (Vdimmer*)userthis;
    Vdimmer__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vdimmer::traceChgThis(Vdimmer__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vdimmer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vdimmer::traceChgThis__2(Vdimmer__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vdimmer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBus(c+1,(vlTOPp->dimmer__DOT__counter),13);
    }
}

void Vdimmer::traceChgThis__3(Vdimmer__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vdimmer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+9,(vlTOPp->i_clk));
        vcdp->chgBit(c+17,(vlTOPp->o_led));
    }
}
