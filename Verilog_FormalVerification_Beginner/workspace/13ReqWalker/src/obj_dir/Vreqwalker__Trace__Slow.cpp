// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vreqwalker__Syms.h"


//======================

void Vreqwalker::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback(&Vreqwalker::traceInit, &Vreqwalker::traceFull, &Vreqwalker::traceChg, this);
}
void Vreqwalker::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vreqwalker* t = (Vreqwalker*)userthis;
    Vreqwalker__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vcdp->scopeEscape(' ');
    t->traceInitThis(vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vreqwalker::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vreqwalker* t = (Vreqwalker*)userthis;
    Vreqwalker__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis(vlSymsp, vcdp, code);
}

//======================


void Vreqwalker::traceInitThis(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
        vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vreqwalker::traceFullThis(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vreqwalker::traceInitThis__1(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->declBit(c+17,"i_clk", false,-1);
        vcdp->declBit(c+25,"i_cyc", false,-1);
        vcdp->declBit(c+33,"i_stb", false,-1);
        vcdp->declBit(c+41,"i_we", false,-1);
        vcdp->declBit(c+49,"i_addr", false,-1);
        vcdp->declBus(c+57,"i_data", false,-1, 31,0);
        vcdp->declBit(c+65,"o_stall", false,-1);
        vcdp->declBit(c+73,"o_ack", false,-1);
        vcdp->declBus(c+81,"o_data", false,-1, 31,0);
        vcdp->declBus(c+89,"o_led", false,-1, 5,0);
        vcdp->declBit(c+17,"reqwalker i_clk", false,-1);
        vcdp->declBit(c+25,"reqwalker i_cyc", false,-1);
        vcdp->declBit(c+33,"reqwalker i_stb", false,-1);
        vcdp->declBit(c+41,"reqwalker i_we", false,-1);
        vcdp->declBit(c+49,"reqwalker i_addr", false,-1);
        vcdp->declBus(c+57,"reqwalker i_data", false,-1, 31,0);
        vcdp->declBit(c+65,"reqwalker o_stall", false,-1);
        vcdp->declBit(c+73,"reqwalker o_ack", false,-1);
        vcdp->declBus(c+81,"reqwalker o_data", false,-1, 31,0);
        vcdp->declBus(c+89,"reqwalker o_led", false,-1, 5,0);
        vcdp->declBit(c+1,"reqwalker busy", false,-1);
        vcdp->declBus(c+9,"reqwalker state", false,-1, 3,0);
        vcdp->declQuad(c+97,"reqwalker unused", false,-1, 33,0);
    }
}

void Vreqwalker::traceFullThis__1(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vreqwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->fullBit(c+1,((0U != (IData)(vlTOPp->reqwalker__DOT__state))));
        vcdp->fullBus(c+9,(vlTOPp->reqwalker__DOT__state),4);
        vcdp->fullBit(c+17,(vlTOPp->i_clk));
        vcdp->fullBit(c+25,(vlTOPp->i_cyc));
        vcdp->fullBit(c+33,(vlTOPp->i_stb));
        vcdp->fullBit(c+41,(vlTOPp->i_we));
        vcdp->fullBit(c+49,(vlTOPp->i_addr));
        vcdp->fullBus(c+57,(vlTOPp->i_data),32);
        vcdp->fullBit(c+65,(vlTOPp->o_stall));
        vcdp->fullBit(c+73,(vlTOPp->o_ack));
        vcdp->fullBus(c+81,(vlTOPp->o_data),32);
        vcdp->fullBus(c+89,(vlTOPp->o_led),6);
        vcdp->fullQuad(c+97,((((QData)((IData)(vlTOPp->i_cyc)) 
                               << 0x21U) | (((QData)((IData)(vlTOPp->i_addr)) 
                                             << 0x20U) 
                                            | (QData)((IData)(vlTOPp->i_data))))),34);
    }
}
