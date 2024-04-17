// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VSERIALTESTER_H_
#define _VSERIALTESTER_H_  // guard

#include "verilated.h"

//==========

class Vserialtester__Syms;

//----------

VL_MODULE(Vserialtester) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(uart_rx,0,0);
    VL_OUT8(uart_tx,0,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vserialtester__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vserialtester);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vserialtester(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vserialtester();
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vserialtester__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vserialtester__Syms* symsp, bool first);
  private:
    static QData _change_request(Vserialtester__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vserialtester__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vserialtester__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vserialtester__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vserialtester__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
