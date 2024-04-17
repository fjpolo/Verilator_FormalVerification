////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	dimmer.cpp
//
// Project:	Verilog Tutorial Example file
//
// Purpose:	Main Verilator simulation script for the dimmer design
//
//	In this script, we toggle the input, and (hopefully) watch the output
//	toggle.
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
//
// Written and distributed by Gisselquist Technology, LLC
//
// This program is hereby granted to the public domain.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.
//
////////////////////////////////////////////////////////////////////////////////
//
//
#include <stdio.h>
#include <stdlib.h>
#include "Vdimmer.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

void tick(int tick_count, Vdimmer *tb, VerilatedVcdC* tfp){
    // The following eval () looks
    // redundant ... many of hours
    // of debugging reveal its not
    tb->eval();
    // dump 2nS before the tick
    if(tfp)
        tfp->dump(tick_count * 10 - 2);
    tb->i_clk = 1;
    tb->eval();
    // tick every 10nS
    if(tfp)
        tfp->dump(tick_count * 10);
    tb->i_clk= 0;
    tb->eval();
    // trailing edge dump
    if(tfp){
        tfp->dump(tick_count * 10 + 5);
        tfp->flush();
    }
}

int main(int argc, char **argv) {
    int last_led;
    unsigned tick_count = 0;

    // Call commandArgs
    Verilated::commandArgs(argc, argv);

    // Instantiate design
    Vdimmer *tb = new Vdimmer;

    // Generate a trace
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    tb->trace(tfp, 99);
    tfp ->open("dimmertrace.vcd ");

    last_led = tb->o_led;
    for(int k=0; k<(1<<20); k++){
        // Tick()
        tick(++tick_count, tb, tfp);

        // Print the LEDs value @changes
        if(last_led != tb->o_led) {
            printf("k = %7d, ", k);
            printf("led  = %d\n", tb-> o_led);
        }
        last_led = tb->o_led ;
    }
}
