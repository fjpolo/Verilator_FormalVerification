// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VMULTIPLEXER_H_
#define _VMULTIPLEXER_H_  // guard

#include "verilated.h"

//==========

class Vmultiplexer__Syms;

//----------

VL_MODULE(Vmultiplexer) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(i_a,0,0);
    VL_IN8(i_b,0,0);
    VL_IN8(i_sel,0,0);
    VL_OUT8(o_out,0,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vmultiplexer__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vmultiplexer);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vmultiplexer(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vmultiplexer();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vmultiplexer__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vmultiplexer__Syms* symsp, bool first);
  private:
    static QData _change_request(Vmultiplexer__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vmultiplexer__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vmultiplexer__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vmultiplexer__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vmultiplexer__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
