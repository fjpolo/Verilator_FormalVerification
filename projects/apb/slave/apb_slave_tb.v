`default_nettype none
`timescale 1ns / 1ps

module apb_slave_tb;
// Clock and reset
reg PCLK;
reg PRESETn;

// APB slave signals
reg [31:0] PADDR;
reg PWRITE;
reg [31:0] PWDATA;
reg PSELx;
reg PENABLE;
wire [31:0] PRDATA;
wire PREADY;
wire PSLVERR;

// Instantiate the APB slave
apb_slave slave (
  .i_clk(PCLK),
  .i_reset_n(PRESETn),
  .PADDR(PADDR),
  .PWRITE(PWRITE),
  .PWDATA(PWDATA),
  .PSELx(PSELx),
  .PENABLE(PENABLE),
  .PRDATA(PRDATA),
  .PREADY(PREADY),
  .PSLVERR(PSLVERR)
);

// Internal reg_file for verification (if the slave has a reg_file)
reg [31:0] expected_reg_file [0:255]; // 256 x 32-bit reg_file

// Clock generation
initial begin
  PCLK = 0;
  forever #5 PCLK = ~PCLK; // 10ns clock period
end

// Reset generation
initial begin
  PRESETn = 0;
  #20 PRESETn = 1; // Assert reset for 20ns, then deassert
end

// VCD dumping for waveform analysis
initial begin
  $dumpfile("apb_slave_tb.vcd");
  $dumpvars(0, apb_slave_tb);
end

// Test sequence
initial begin
  // Initialize signals
  PADDR = 32'h0;
  PWRITE = 0;
  PWDATA = 32'h0;
  PSELx = 0;
  PENABLE = 0;

  // Wait for reset to complete
  #30;

  // Test 1: Write transaction (no wait states)
  PSELx = 1;
  PADDR = 32'h1;
  PWDATA = 32'hDEADBEEF;
  PWRITE = 1;
  #10;
  PENABLE = 1;
  #10;

  // Check if PREADY is asserted
  if (!PREADY) begin
    $display("ERROR: PREADY not asserted during write transaction");
    $finish(1);
  end

  // Check if data was written to the slave's reg_file
  if (slave.reg_file_1 !== PWDATA) begin // Adjust if your slave uses a different reg_file model
    $display("ERROR: Write data mismatch (expected %h, got %h)", PWDATA, slave.reg_file_1);
    $finish(1);
  end

  // End write transaction
  PSELx = 0;
  PENABLE = 0;
  #10;

  // Test 2: Read transaction (no wait states)
  PSELx = 1;
  PADDR = 32'h10;
  PWRITE = 0;
  #10;
  PENABLE = 1;
  #10;

  // Check if PREADY is asserted
  if (!PREADY) begin
    $display("ERROR: PREADY not asserted during read transaction");
    $finish(1);
  end

  // Check if read data matches written data
  if (PRDATA !== 32'hDEADBEEF) begin
    $display("ERROR: Read data mismatch (expected DEADBEEF, got %h)", PRDATA);
    $finish(1);
  end

  // End read transaction
  PSELx = 0;
  PENABLE = 0;
  #10;

  // Test 3: Write transaction with wait states
  PSELx = 1;
  PADDR = 32'h20;
  PWDATA = 32'hCAFEBABE;
  PWRITE = 1;
  #10;
  PENABLE = 1;
  #10;

  // Simulate wait states (slave delays PREADY)
  #20;
  if (PREADY) begin
    $display("ERROR: PREADY asserted too early during write with wait states");
    $finish(1);
  end

  // Slave asserts PREADY after delay
  #20;
  if (!PREADY) begin
    $display("ERROR: PREADY not asserted after wait states");
    $finish(1);
  end

  // End write transaction
  PSELx = 0;
  PENABLE = 0;
  #10;

  // Test 4: Error condition (invalid address)
  PSELx = 1;
  PADDR = 32'hFFFF_FFFF; // Invalid address
  PWRITE = 1;
  #10;
  PENABLE = 1;
  #10;

  // Check if PSLVERR is asserted
  if (!PSLVERR) begin
    $display("ERROR: PSLVERR not asserted for invalid address");
    $finish(1);
  end

  // End error transaction
  PSELx = 0;
  PENABLE = 0;
  #10;

  // Test passed
  $display("Testbench passed");
  $finish(0);
end
endmodule