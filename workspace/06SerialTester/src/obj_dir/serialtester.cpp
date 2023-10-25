////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	serialtester.cpp
//
// Project:	Verilog Tutorial Example file
//
// Purpose:	Main Verilator simulation script for the serialtester design
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
#include "Vserialtester.h"
#include "verilated.h"

int main(int argc, char **argv) {
    // Call commandArgs
    Verilated::commandArgs(argc, argv);

    // Instantiate design
    Vserialtester *tb = new Vserialtester;

    // Run design 20 timesteps
    char symbol = 'a';
    for(int k=0; k<8; k++){

        tb->uart_rx = symbol >> k & 0x01;

        tb->eval();

        // Print results
        printf("k = %2d, ", k);
        printf("uart_rx = %d, ", tb -> uart_rx );
        printf("uart_tx  = %d\n", tb -> uart_tx );
    }
}
