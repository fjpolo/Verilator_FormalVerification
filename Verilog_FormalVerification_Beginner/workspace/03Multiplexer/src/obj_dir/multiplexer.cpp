#include <stdio.h>
#include <stdlib.h>
#include "Vmultiplexer.h"
#include "verilated.h"

int main(int argc, char **argv) {
	// Call commandArgs first!
	Verilated::commandArgs(argc, argv);

	// Instantiate our design
	Vmultiplexer *tb = new Vmultiplexer;

	tb->i_a = 0x00;
	tb->i_b = 0x00;
	tb->i_sel = 0x00;
	for(int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			for(int k=0; k<2; k++) {
				tb->i_a = i;
				tb->i_b = j;
				tb->i_sel = k;

				tb->eval();

				// Now let's print our results
				printf("k = %2d, ", k);
				printf("i_a = %3x, ", tb->i_a);
				printf("i_b = %3x, ", tb->i_b);
				printf("i_sel = %3x, ", tb->i_sel);
				printf("out = %3x\n", tb->o_out);
			}
		}
	}
}
