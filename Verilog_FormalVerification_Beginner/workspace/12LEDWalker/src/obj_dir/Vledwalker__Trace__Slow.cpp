// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vledwalker__Syms.h"


//======================

void Vledwalker::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback(&Vledwalker::traceInit, &Vledwalker::traceFull, &Vledwalker::traceChg, this);
}
void Vledwalker::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vledwalker* t = (Vledwalker*)userthis;
    Vledwalker__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vcdp->scopeEscape(' ');
    t->traceInitThis(vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vledwalker::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vledwalker* t = (Vledwalker*)userthis;
    Vledwalker__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis(vlSymsp, vcdp, code);
}

//======================


void Vledwalker::traceInitThis(Vledwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
        vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vledwalker::traceFullThis(Vledwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vledwalker::traceInitThis__1(Vledwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->declBit(c+25,"i_clk", false,-1);
        vcdp->declBus(c+33,"o_led", false,-1, 7,0);
        vcdp->declBit(c+25,"ledwalker i_clk", false,-1);
        vcdp->declBus(c+33,"ledwalker o_led", false,-1, 7,0);
        vcdp->declBus(c+41,"ledwalker CLK_RATE_HZ", false,-1, 31,0);
        vcdp->declBus(c+1,"ledwalker led_index", false,-1, 3,0);
        vcdp->declBus(c+9,"ledwalker wait_counter", false,-1, 31,0);
        vcdp->declBit(c+17,"ledwalker stb", false,-1);
    }
}

void Vledwalker::traceFullThis__1(Vledwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vledwalker* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->fullBus(c+1,(vlTOPp->ledwalker__DOT__led_index),4);
        vcdp->fullBus(c+9,(vlTOPp->ledwalker__DOT__wait_counter),32);
        vcdp->fullBit(c+17,(vlTOPp->ledwalker__DOT__stb));
        vcdp->fullBit(c+25,(vlTOPp->i_clk));
        vcdp->fullBus(c+33,(vlTOPp->o_led),8);
        vcdp->fullBus(c+41,(0x3e8U),32);
    }
}
