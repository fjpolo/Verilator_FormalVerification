// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VHELLOWORLD_H_
#define _VHELLOWORLD_H_  // guard

#include "verilated.h"

//==========

class Vhelloworld__Syms;
class Vhelloworld_VerilatedVcd;


//----------

VL_MODULE(Vhelloworld) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(i_clk,0,0);
    VL_OUT8(o_uart_tx,0,0);
    VL_OUT(o_setup,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*0:0*/ helloworld__DOT__tx_restart;
    CData/*0:0*/ helloworld__DOT__tx_busy;
    CData/*0:0*/ helloworld__DOT__tx_stb;
    CData/*3:0*/ helloworld__DOT__tx_index;
    CData/*7:0*/ helloworld__DOT__tx_data;
    CData/*3:0*/ helloworld__DOT__transmitter__DOT__state;
    CData/*0:0*/ helloworld__DOT__transmitter__DOT__baud_stb;
    SData/*8:0*/ helloworld__DOT__transmitter__DOT__lcl_data;
    IData/*27:0*/ helloworld__DOT__hz_counter;
    IData/*23:0*/ helloworld__DOT__transmitter__DOT__counter;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__i_clk;
    IData/*31:0*/ __Vm_traceActivity;
    static CData/*7:0*/ __Vtable1_helloworld__DOT__tx_data[16];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vhelloworld__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vhelloworld);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vhelloworld(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vhelloworld();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vhelloworld__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vhelloworld__Syms* symsp, bool first);
  private:
    static QData _change_request(Vhelloworld__Syms* __restrict vlSymsp);
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vhelloworld__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vhelloworld__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vhelloworld__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vhelloworld__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__2(Vhelloworld__Syms* __restrict vlSymsp);
    static void _settle__TOP__3(Vhelloworld__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void traceChgThis(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__2(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__3(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__4(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceFullThis(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceFullThis__1(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis__1(Vhelloworld__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
