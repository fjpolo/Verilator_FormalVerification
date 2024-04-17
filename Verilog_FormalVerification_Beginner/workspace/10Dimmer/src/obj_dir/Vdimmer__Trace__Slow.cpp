// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdimmer__Syms.h"


//======================

void Vdimmer::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback(&Vdimmer::traceInit, &Vdimmer::traceFull, &Vdimmer::traceChg, this);
}
void Vdimmer::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vdimmer* t = (Vdimmer*)userthis;
    Vdimmer__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vcdp->scopeEscape(' ');
    t->traceInitThis(vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vdimmer::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vdimmer* t = (Vdimmer*)userthis;
    Vdimmer__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis(vlSymsp, vcdp, code);
}

//======================


void Vdimmer::traceInitThis(Vdimmer__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vdimmer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
        vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vdimmer::traceFullThis(Vdimmer__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vdimmer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vdimmer::traceInitThis__1(Vdimmer__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vdimmer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->declBit(c+9,"i_clk", false,-1);
        vcdp->declBit(c+17,"o_led", false,-1);
        vcdp->declBit(c+9,"dimmer i_clk", false,-1);
        vcdp->declBit(c+17,"dimmer o_led", false,-1);
        vcdp->declBus(c+1,"dimmer counter", false,-1, 12,0);
    }
}

void Vdimmer::traceFullThis__1(Vdimmer__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vdimmer* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->fullBus(c+1,(vlTOPp->dimmer__DOT__counter),13);
        vcdp->fullBit(c+9,(vlTOPp->i_clk));
        vcdp->fullBit(c+17,(vlTOPp->o_led));
    }
}
