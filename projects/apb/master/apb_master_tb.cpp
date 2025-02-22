#include "Vapb_master.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "ERROR: " << message << " at cycle " << cycle << std::endl; \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

int main(int argc, char** argv) {
    // Initialize random seed
    std::srand(std::time(nullptr));

    // Initialize Verilator
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true); // Enable waveform tracing

    // Create an instance of the module
    Vapb_master* top = new Vapb_master;

    // Create a VCD trace file
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99); // Trace 99 levels of hierarchy
    tfp->open("apb_master_sim.vcd");

    // Initialize signals
    top->i_clk = 0;
    top->i_reset_n = 0;
    top->i_addr = 0;
    top->i_start = 0;
    top->i_write = 0;
    top->i_wdata = 0;

    // Simulation variables
    int cycle = 0;
    bool transaction_active = false;
    uint32_t expected_rdata = 0;
    bool expected_slverr = false;

    std::cout << "Starting simulation..." << std::endl;

    // Simulation loop
    for (cycle = 0; cycle < 1000; cycle++) {
        // Toggle clock
        top->i_clk = !top->i_clk;

        // Release reset after a few cycles
        if (cycle == 5) {
            top->i_reset_n = 1;
            std::cout << "Reset released at cycle " << cycle << std::endl;
        }

        // Start a transaction randomly
        if (!transaction_active && (std::rand() % 10 == 0)) {
            top->i_start = 1;
            top->i_addr = std::rand() & 0xFFFF; // Random address
            top->i_write = std::rand() % 2;     // Random write/read
            top->i_wdata = std::rand();         // Random write data
            transaction_active = true;

            if (top->i_write) {
                std::cout << "Starting WRITE transaction: addr=" << std::hex << top->i_addr
                          << ", data=" << top->i_wdata << std::endl;
            } else {
                std::cout << "Starting READ transaction: addr=" << std::hex << top->i_addr << std::endl;
            }
        } else {
            top->i_start = 0;
        }

        // Simulate slave response
        if (transaction_active && top->PENABLE) {
            if (top->PREADY) {
                // Transaction complete
                transaction_active = false;
                top->PRDATA = std::rand(); // Random read data
                top->PSLVERR = std::rand() % 2; // Random slave error

                std::cout << "Transaction complete: rdata=" << std::hex << top->PRDATA
                          << ", slverr=" << top->PSLVERR << std::endl;

                // Verify outputs
                ASSERT(top->o_done == 1, "o_done not asserted");
                ASSERT(top->o_rdata == top->PRDATA, "o_rdata mismatch");
                ASSERT(top->o_slverr == top->PSLVERR, "o_slverr mismatch");
            }
        }

        // Evaluate the module
        top->eval();

        // Dump waveform data
        tfp->dump(cycle);
    }

    // Clean up
    tfp->close();
    delete top;
    delete tfp;

    std::cout << "PASS: Simulation completed successfully!" << std::endl;
    return 0;
}