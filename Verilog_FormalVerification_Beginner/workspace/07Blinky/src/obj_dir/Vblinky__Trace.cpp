// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vblinky__Syms.h"


//======================

void Vblinky::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vblinky* t = (Vblinky*)userthis;
    Vblinky__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vblinky::traceChgThis(Vblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vblinky::traceChgThis__2(Vblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBus(c+1,(vlTOPp->blinky__DOT__counter),12);
    }
}

void Vblinky::traceChgThis__3(Vblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+9,(vlTOPp->i_clk));
        vcdp->chgBit(c+17,(vlTOPp->o_led));
    }
}
