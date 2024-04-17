// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vhelloworld__Syms.h"


//======================

void Vhelloworld::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vhelloworld* t = (Vhelloworld*)userthis;
    Vhelloworld__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
        t->traceChgThis(vlSymsp, vcdp, code);
    }
}

//======================


void Vhelloworld::traceChgThis(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY((1U & (vlTOPp->__Vm_traceActivity 
                               | (vlTOPp->__Vm_traceActivity 
                                  >> 1U))))) {
            vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
        }
        if (VL_UNLIKELY((2U & vlTOPp->__Vm_traceActivity))) {
            vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
        }
        vlTOPp->traceChgThis__4(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vhelloworld::traceChgThis__2(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+1,(vlTOPp->helloworld__DOT__tx_restart));
        vcdp->chgBus(c+9,(vlTOPp->helloworld__DOT__hz_counter),28);
        vcdp->chgBit(c+17,(vlTOPp->helloworld__DOT__tx_busy));
        vcdp->chgBit(c+25,(vlTOPp->helloworld__DOT__tx_stb));
        vcdp->chgBus(c+33,(vlTOPp->helloworld__DOT__tx_index),4);
        vcdp->chgBus(c+41,(vlTOPp->helloworld__DOT__transmitter__DOT__counter),24);
        vcdp->chgBus(c+49,(vlTOPp->helloworld__DOT__transmitter__DOT__state),4);
        vcdp->chgBus(c+57,(vlTOPp->helloworld__DOT__transmitter__DOT__lcl_data),9);
        vcdp->chgBit(c+65,(vlTOPp->helloworld__DOT__transmitter__DOT__baud_stb));
    }
}

void Vhelloworld::traceChgThis__3(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBus(c+73,(vlTOPp->helloworld__DOT__tx_data),8);
    }
}

void Vhelloworld::traceChgThis__4(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->chgBit(c+81,(vlTOPp->i_clk));
        vcdp->chgBit(c+89,(vlTOPp->o_uart_tx));
        vcdp->chgBus(c+97,(vlTOPp->o_setup),32);
    }
}
