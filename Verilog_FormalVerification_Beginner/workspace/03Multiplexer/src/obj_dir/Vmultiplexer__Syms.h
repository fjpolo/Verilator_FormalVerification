// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VMULTIPLEXER__SYMS_H_
#define _VMULTIPLEXER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vmultiplexer.h"

// SYMS CLASS
class Vmultiplexer__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vmultiplexer*                  TOPp;
    
    // CREATORS
    Vmultiplexer__Syms(Vmultiplexer* topp, const char* namep);
    ~Vmultiplexer__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
