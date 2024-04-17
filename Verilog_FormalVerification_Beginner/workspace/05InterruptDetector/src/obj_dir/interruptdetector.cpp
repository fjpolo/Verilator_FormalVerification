#include <stdio.h>
#include <stdlib.h>
#include "Vinterruptdetector.h"
#include "verilated.h"

int main(int argc, char **argv) {
	// Call commandArgs first!
	Verilated::commandArgs(argc, argv);

	// Instantiate our design
	Vinterruptdetector *tb = new Vinterruptdetector;

	tb->i_irq_source = 0x01;
	for(int i=0; i<8; i++) {
		tb->i_irq_source <= 1;

		tb->eval();

		// Now let's print our results
		printf("i = %2d, ", i);
		printf("i_irq_source = %4x, ", tb->i_irq_source);
		printf("o_irq = %8x\n", tb->o_irq);
	}
}
