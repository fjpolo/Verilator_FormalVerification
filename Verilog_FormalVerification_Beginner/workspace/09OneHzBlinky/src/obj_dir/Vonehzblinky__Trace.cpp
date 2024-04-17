// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vonehzblinky__Syms.h"


//======================

void Vonehzblinky::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vonehzblinky* t = (Vonehzblinky*)userthis;
    Vonehzblinky__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vonehzblinky::traceChgThis(Vonehzblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vonehzblinky::traceChgThis__2(Vonehzblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBus(c+1,(vlTOPp->onehzblinky__DOT__counter),32);
    }
}

void Vonehzblinky::traceChgThis__3(Vonehzblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+9,(vlTOPp->i_clk));
        vcdp->chgBit(c+17,(vlTOPp->o_led));
    }
}
