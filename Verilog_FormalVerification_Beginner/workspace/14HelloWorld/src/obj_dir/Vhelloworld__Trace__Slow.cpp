// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vhelloworld__Syms.h"


//======================

void Vhelloworld::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback(&Vhelloworld::traceInit, &Vhelloworld::traceFull, &Vhelloworld::traceChg, this);
}
void Vhelloworld::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    Vhelloworld* t = (Vhelloworld*)userthis;
    Vhelloworld__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vcdp->scopeEscape(' ');
    t->traceInitThis(vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void Vhelloworld::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    Vhelloworld* t = (Vhelloworld*)userthis;
    Vhelloworld__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis(vlSymsp, vcdp, code);
}

//======================


void Vhelloworld::traceInitThis(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
        vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void Vhelloworld::traceFullThis(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void Vhelloworld::traceInitThis__1(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->declBit(c+81,"i_clk", false,-1);
        vcdp->declBit(c+89,"o_uart_tx", false,-1);
        vcdp->declBus(c+97,"o_setup", false,-1, 31,0);
        vcdp->declBus(c+105,"helloworld CLOCK_RATE_HZ", false,-1, 31,0);
        vcdp->declBus(c+113,"helloworld BAUD_RATE", false,-1, 31,0);
        vcdp->declBit(c+81,"helloworld i_clk", false,-1);
        vcdp->declBit(c+89,"helloworld o_uart_tx", false,-1);
        vcdp->declBus(c+121,"helloworld INITIAL_UART_SETUP", false,-1, 31,0);
        vcdp->declBus(c+97,"helloworld o_setup", false,-1, 31,0);
        vcdp->declBit(c+1,"helloworld tx_restart", false,-1);
        vcdp->declBus(c+9,"helloworld hz_counter", false,-1, 27,0);
        vcdp->declBit(c+17,"helloworld tx_busy", false,-1);
        vcdp->declBit(c+25,"helloworld tx_stb", false,-1);
        vcdp->declBus(c+33,"helloworld tx_index", false,-1, 3,0);
        vcdp->declBus(c+73,"helloworld tx_data", false,-1, 7,0);
        vcdp->declBus(c+129,"helloworld transmitter CLOCKS_PER_BAUD", false,-1, 23,0);
        vcdp->declBit(c+81,"helloworld transmitter i_clk", false,-1);
        vcdp->declBit(c+25,"helloworld transmitter i_wr", false,-1);
        vcdp->declBus(c+73,"helloworld transmitter i_data", false,-1, 7,0);
        vcdp->declBit(c+89,"helloworld transmitter o_uart_tx", false,-1);
        vcdp->declBit(c+17,"helloworld transmitter o_busy", false,-1);
        vcdp->declBus(c+137,"helloworld transmitter START", false,-1, 3,0);
        vcdp->declBus(c+145,"helloworld transmitter BIT_ZERO", false,-1, 3,0);
        vcdp->declBus(c+153,"helloworld transmitter BIT_ONE", false,-1, 3,0);
        vcdp->declBus(c+161,"helloworld transmitter BIT_TWO", false,-1, 3,0);
        vcdp->declBus(c+169,"helloworld transmitter BIT_THREE", false,-1, 3,0);
        vcdp->declBus(c+177,"helloworld transmitter BIT_FOUR", false,-1, 3,0);
        vcdp->declBus(c+185,"helloworld transmitter BIT_FIVE", false,-1, 3,0);
        vcdp->declBus(c+193,"helloworld transmitter BIT_SIX", false,-1, 3,0);
        vcdp->declBus(c+201,"helloworld transmitter BIT_SEVEN", false,-1, 3,0);
        vcdp->declBus(c+201,"helloworld transmitter LAST", false,-1, 3,0);
        vcdp->declBus(c+209,"helloworld transmitter IDLE", false,-1, 3,0);
        vcdp->declBus(c+41,"helloworld transmitter counter", false,-1, 23,0);
        vcdp->declBus(c+49,"helloworld transmitter state", false,-1, 3,0);
        vcdp->declBus(c+57,"helloworld transmitter lcl_data", false,-1, 8,0);
        vcdp->declBit(c+65,"helloworld transmitter baud_stb", false,-1);
    }
}

void Vhelloworld::traceFullThis__1(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    Vhelloworld* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c = code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
        vcdp->fullBit(c+1,(vlTOPp->helloworld__DOT__tx_restart));
        vcdp->fullBus(c+9,(vlTOPp->helloworld__DOT__hz_counter),28);
        vcdp->fullBit(c+17,(vlTOPp->helloworld__DOT__tx_busy));
        vcdp->fullBit(c+25,(vlTOPp->helloworld__DOT__tx_stb));
        vcdp->fullBus(c+33,(vlTOPp->helloworld__DOT__tx_index),4);
        vcdp->fullBus(c+41,(vlTOPp->helloworld__DOT__transmitter__DOT__counter),24);
        vcdp->fullBus(c+49,(vlTOPp->helloworld__DOT__transmitter__DOT__state),4);
        vcdp->fullBus(c+57,(vlTOPp->helloworld__DOT__transmitter__DOT__lcl_data),9);
        vcdp->fullBit(c+65,(vlTOPp->helloworld__DOT__transmitter__DOT__baud_stb));
        vcdp->fullBus(c+73,(vlTOPp->helloworld__DOT__tx_data),8);
        vcdp->fullBit(c+81,(vlTOPp->i_clk));
        vcdp->fullBit(c+89,(vlTOPp->o_uart_tx));
        vcdp->fullBus(c+97,(vlTOPp->o_setup),32);
        vcdp->fullBus(c+105,(0x5f5e100U),32);
        vcdp->fullBus(c+113,(0x1c200U),32);
        vcdp->fullBus(c+121,(0x364U),32);
        vcdp->fullBus(c+129,(0x364U),24);
        vcdp->fullBus(c+137,(0U),4);
        vcdp->fullBus(c+145,(1U),4);
        vcdp->fullBus(c+153,(2U),4);
        vcdp->fullBus(c+161,(3U),4);
        vcdp->fullBus(c+169,(4U),4);
        vcdp->fullBus(c+177,(5U),4);
        vcdp->fullBus(c+185,(6U),4);
        vcdp->fullBus(c+193,(7U),4);
        vcdp->fullBus(c+201,(8U),4);
        vcdp->fullBus(c+209,(0xfU),4);
    }
}
