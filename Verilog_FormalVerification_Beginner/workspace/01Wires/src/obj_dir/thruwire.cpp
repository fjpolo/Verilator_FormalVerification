////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	thruwire.cpp
//
// Project:	Verilog Tutorial Example file
//
// Purpose:	Main Verilator simulation script for the thruwire design
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
#include "Vthruwire.h"
#include "verilated.h"

int main(int argc, char **argv) {
    // Call commandArgs
    Verilated::commandArgs(argc, argv);

    // Instantiate design
    Vthruwire *tb = new Vthruwire;

    // Run design 20 timesteps
    for(int k=0; k<20; k++){
        // We ’ll set the switch input
        // to the LSB of our step
        tb->i_sw = k & 0x01;
        tb->eval();

        // Print results
        printf("k = %2d, ", k);
        printf("sw = %d, ", tb -> i_sw );
        printf("led  = %d\n", tb -> o_led );
    }
}
