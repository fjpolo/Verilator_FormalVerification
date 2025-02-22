import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, Timer
from cocotb.result import TestSuccess, TestFailure
import random

# Helper function to generate random data
def random_data():
    return random.randint(0, 0xFFFFFFFF)

@cocotb.test()
async def test_apb_master(dut):
    # Start a clock
    clock = Clock(dut.i_clk, 10, units="ns")
    cocotb.start_soon(clock.start())

    # Initialize signals
    dut.i_reset_n.value = 0
    dut.i_start.value = 0
    dut.i_addr.value = 0
    dut.i_write.value = 0
    dut.i_wdata.value = 0

    # Reset the module
    await FallingEdge(dut.i_clk)
    dut.i_reset_n.value = 1
    await RisingEdge(dut.i_clk)

    # Test multiple transactions
    for _ in range(10):  # Run 10 random transactions
        # Randomize inputs
        addr = random_data() & 0xFFFF  # 16-bit address
        write = random.choice([0, 1])  # Random write/read
        wdata = random_data() if write else 0

        # Start a transaction
        dut.i_start.value = 1
        dut.i_addr.value = addr
        dut.i_write.value = write
        dut.i_wdata.value = wdata

        await RisingEdge(dut.i_clk)
        dut.i_start.value = 0

        # Wait for PENABLE to be asserted
        while dut.PENABLE.value != 1:
            await RisingEdge(dut.i_clk)

        # Simulate slave response
        dut.PREADY.value = 1
        dut.PRDATA.value = random_data()  # Random read data
        dut.PSLVERR.value = random.choice([0, 1])  # Random slave error

        # Wait for transaction to complete
        while dut.o_done.value != 1:
            await RisingEdge(dut.i_clk)

        # Verify outputs
        if write:
            print(f"Write transaction: addr={hex(addr)}, data={hex(wdata)}")
        else:
            print(f"Read transaction: addr={hex(addr)}, rdata={hex(dut.o_rdata.value)}, slverr={dut.o_slverr.value}")
            assert dut.o_rdata.value == dut.PRDATA.value, "Read data mismatch"
            assert dut.o_slverr.value == dut.PSLVERR.value, "Slave error mismatch"

        # Add random delay between transactions
        await Timer(random.randint(1, 10), units="ns")

    # End the test
    raise TestSuccess("All transactions completed successfully!")