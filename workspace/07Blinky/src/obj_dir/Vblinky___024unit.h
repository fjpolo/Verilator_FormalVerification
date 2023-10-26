// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vblinky.h for the primary calling header

#ifndef _VBLINKY___024UNIT_H_
#define _VBLINKY___024UNIT_H_  // guard

#include "verilated.h"

//==========

class Vblinky__Syms;
class Vblinky_VerilatedVcd;


//----------

VL_MODULE(Vblinky___024unit) {
  public:
    
    // INTERNAL VARIABLES
  private:
    Vblinky__Syms* __VlSymsp;  // Symbol table
  public:
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vblinky___024unit);  ///< Copying not allowed
  public:
    Vblinky___024unit(const char* name = "TOP");
    ~Vblinky___024unit();
    
    // INTERNAL METHODS
    void __Vconfigure(Vblinky__Syms* symsp, bool first);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
