// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VREQWALKER_H_
#define _VREQWALKER_H_  // guard

#include "verilated.h"

//==========

class Vreqwalker__Syms;
class Vreqwalker_VerilatedVcd;


//----------

VL_MODULE(Vreqwalker) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(i_clk,0,0);
    VL_IN8(i_cyc,0,0);
    VL_IN8(i_stb,0,0);
    VL_IN8(i_we,0,0);
    VL_IN8(i_addr,0,0);
    VL_OUT8(o_stall,0,0);
    VL_OUT8(o_ack,0,0);
    VL_OUT8(o_led,5,0);
    VL_IN(i_data,31,0);
    VL_OUT(o_data,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*3:0*/ reqwalker__DOT__state;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*3:0*/ __Vtableidx1;
    CData/*0:0*/ __Vclklast__TOP__i_clk;
    IData/*31:0*/ __Vm_traceActivity;
    CData/*0:0*/ __Vtablechg1[16];
    static CData/*5:0*/ __Vtable1_o_led[16];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vreqwalker__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vreqwalker);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vreqwalker(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vreqwalker();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vreqwalker__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vreqwalker__Syms* symsp, bool first);
  private:
    static QData _change_request(Vreqwalker__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__4(Vreqwalker__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vreqwalker__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vreqwalker__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vreqwalker__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vreqwalker__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__2(Vreqwalker__Syms* __restrict vlSymsp);
    static void _settle__TOP__3(Vreqwalker__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void traceChgThis(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__2(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__3(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceFullThis(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceFullThis__1(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInitThis__1(Vreqwalker__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) VL_ATTR_COLD;
    static void traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard