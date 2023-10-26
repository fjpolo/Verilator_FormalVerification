// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vonehzblinky__Syms.h"


//======================

void Vonehzblinky::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback(&Vonehzblinky::traceInit, &Vonehzblinky::traceFull, &Vonehzblinky::traceChg, this);
}
void Vonehzblinky::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vonehzblinky* t = (Vonehzblinky*)userthis;
    Vonehzblinky__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vcdp->scopeEscape(' ');
    t->traceInitThis(vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vonehzblinky::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vonehzblinky* t = (Vonehzblinky*)userthis;
    Vonehzblinky__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis(vlSymsp, vcdp, code);
}

//======================


void Vonehzblinky::traceInitThis(Vonehzblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
        vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vonehzblinky::traceFullThis(Vonehzblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vonehzblinky::traceInitThis__1(Vonehzblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->declBit(c+9,"i_clk", false,-1);
        vcdp->declBit(c+17,"o_led", false,-1);
        vcdp->declBit(c+9,"onehzblinky i_clk", false,-1);
        vcdp->declBit(c+17,"onehzblinky o_led", false,-1);
        vcdp->declBus(c+25,"onehzblinky CLOCK_RATE_HZ", false,-1, 31,0);
        vcdp->declBus(c+33,"onehzblinky INCREMENT", false,-1, 31,0);
        vcdp->declBus(c+1,"onehzblinky counter", false,-1, 31,0);
    }
}

void Vonehzblinky::traceFullThis__1(Vonehzblinky__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vonehzblinky* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->fullBus(c+1,(vlTOPp->onehzblinky__DOT__counter),32);
        vcdp->fullBit(c+9,(vlTOPp->i_clk));
        vcdp->fullBit(c+17,(vlTOPp->o_led));
        vcdp->fullBus(c+25,(0x5f5e100U),32);
        vcdp->fullBus(c+33,(0x2aU),32);
    }
}
