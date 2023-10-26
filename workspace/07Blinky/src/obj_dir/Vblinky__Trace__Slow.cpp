// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vblinky__Syms.h"


//======================

void Vblinky::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback(&Vblinky::traceInit, &Vblinky::traceFull, &Vblinky::traceChg, this);
}
void Vblinky::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vblinky* t = (Vblinky*)userthis;
    Vblinky__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vcdp->scopeEscape(' ');
    t->traceInitThis(vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vblinky::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vblinky* t = (Vblinky*)userthis;
    Vblinky__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis(vlSymsp, vcdp, code);
}

//======================


void Vblinky::traceInitThis(Vblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
        vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vblinky::traceFullThis(Vblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vblinky::traceInitThis__1(Vblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->declBit(c+9,"i_clk", false,-1);
        vcdp->declBit(c+17,"o_led", false,-1);
        vcdp->declBit(c+9,"blinky i_clk", false,-1);
        vcdp->declBit(c+17,"blinky o_led", false,-1);
        vcdp->declBus(c+1,"blinky counter", false,-1, 11,0);
    }
}

void Vblinky::traceFullThis__1(Vblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->fullBus(c+1,(vlTOPp->blinky__DOT__counter),12);
        vcdp->fullBit(c+9,(vlTOPp->i_clk));
        vcdp->fullBit(c+17,(vlTOPp->o_led));
    }
}
