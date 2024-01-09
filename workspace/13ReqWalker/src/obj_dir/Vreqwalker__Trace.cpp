// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vreqwalker__Syms.h"


//======================

void Vreqwalker::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vreqwalker* t = (Vreqwalker*)userthis;
    Vreqwalker__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vreqwalker::traceChgThis(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

void Vreqwalker::traceChgThis__2(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+1,((0U != (IData)(vlTOPp->reqwalker__DOT__state))));
        vcdp->chgBus(c+9,(vlTOPp->reqwalker__DOT__state),4);
    }
}

void Vreqwalker::traceChgThis__3(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+17,(vlTOPp->i_clk));
        vcdp->chgBit(c+25,(vlTOPp->i_cyc));
        vcdp->chgBit(c+33,(vlTOPp->i_stb));
        vcdp->chgBit(c+41,(vlTOPp->i_we));
        vcdp->chgBit(c+49,(vlTOPp->i_addr));
        vcdp->chgBus(c+57,(vlTOPp->i_data),32);
        vcdp->chgBit(c+65,(vlTOPp->o_stall));
        vcdp->chgBit(c+73,(vlTOPp->o_ack));
        vcdp->chgBus(c+81,(vlTOPp->o_data),32);
        vcdp->chgBus(c+89,(vlTOPp->o_led),6);
        vcdp->chgQuad(c+97,((((QData)((IData)(vlTOPp->i_cyc)) 
                              << 0x21U) | (((QData)((IData)(vlTOPp->i_addr)) 
                                            << 0x20U) 
                                           | (QData)((IData)(vlTOPp->i_data))))),34);
    }
}
