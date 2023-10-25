// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VINTERRUPTDETECTOR__SYMS_H_
#define _VINTERRUPTDETECTOR__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODULE CLASSES
#include "Vinterruptdetector.h"

// SYMS CLASS
class Vinterruptdetector__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vinterruptdetector*            TOPp;
    
    // CREATORS
    Vinterruptdetector__Syms(Vinterruptdetector* topp, const char* namep);
    ~Vinterruptdetector__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
