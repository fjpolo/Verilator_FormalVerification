#include <stdio.h>
#include <stdlib.h>
#include "Vmaskbus.h"
#include "verilated.h"

int main(int argc, char **argv) {
	// Call commandArgs first!
	Verilated::commandArgs(argc, argv);

	// Instantiate our design
	Vmaskbus *tb = new Vmaskbus;

	tb->i_sw = 0;
	for(int k=0; k<20; k++) {
		// We'll set the switch input
		// to the LSB of our counter
		tb->i_sw = k&0x3f;

		tb->eval();

		// Now let's print our results
		printf("k = %2d, ", k);
		printf("sw = %3x, ", tb->i_sw);
		printf("led = %3x\n", tb->o_led);
	}
}
