#include <stdio.h>
#include <stdlib.h>
#include "Vparitycheck.h"
#include "verilated.h"

int main(int argc, char **argv) {
	// Call commandArgs first!
	Verilated::commandArgs(argc, argv);

	// Instantiate our design
	Vparitycheck *tb = new Vparitycheck;

	tb->i_word = 0x00;
	for(int i=0; i<256; i++) {
		tb->i_word++;

		tb->eval();

		// Now let's print our results
		printf("i = %2d, ", i);
		printf("i_word = %4x, ", tb->i_word);
		printf("o_parity = %8x\n", tb->o_parity);
	}
}
