`default_nettype none

module apb_master_tb;
  // Clock and reset
  reg i_clk;
  reg i_reset_n;

  // APB master signals
  wire [31:0] PADDR;
  wire PWRITE;
  wire [31:0] PWDATA;
  wire PSELx;
  wire PENABLE;
  reg [31:0] PRDATA;
  reg PREADY;
  reg PSLVERR;

  // Control signals
  reg i_start;
  reg [31:0] i_addr;
  reg [31:0] i_wdata;
  reg i_write;
  wire o_done;
  wire [31:0] o_rdata;
  wire o_slverr;

  // Instantiate the APB master
  apb_master master (
    .i_clk(i_clk),
    .i_reset_n(i_reset_n),
    .PADDR(PADDR),
    .PWRITE(PWRITE),
    .PWDATA(PWDATA),
    .PSELx(PSELx),
    .PENABLE(PENABLE),
    .PRDATA(PRDATA),
    .PREADY(PREADY),
    .PSLVERR(PSLVERR),
    .i_start(i_start),
    .i_addr(i_addr),
    .i_wdata(i_wdata),
    .i_write(i_write),
    .o_done(o_done),
    .o_rdata(o_rdata),
    .o_slverr(o_slverr)
  );

  initial begin  
    $dumpfile("apb_master.vcd");
    $dumpvars(0,apb_master_tb);
  end 

  // Clock generation
  initial begin
    i_clk = 0;
    forever #5 i_clk = ~i_clk; // 10ns clock period
  end

  // Reset generation
  initial begin
    i_reset_n = 0;
    #20 i_reset_n = 1; // Assert reset for 20ns, then deassert
  end

  // Test sequence
  initial begin
    // Initialize signals
    i_start = 0;
    i_addr = 32'h0;
    i_wdata = 32'h0;
    i_write = 0;
    PRDATA = 32'h0;
    PREADY = 0;
    PSLVERR = 0;

    // Wait for reset to complete
    #30;

    // Test 1: Write transaction
    i_start = 1;
    i_addr = 32'h1000;
    i_wdata = 32'hDEADBEEF;
    i_write = 1;
    #10;
    i_start = 0;

    // Simulate slave response with wait cycles
    #20;
    PREADY = 1;
    #10;
    PREADY = 0;

    // Check if the i_write transaction completed successfully
    if (!o_done) begin
      $display("ERROR: Write transaction did not complete");
      $finish(1); // Exit with non-zero status
    end

    // Test 2: Read transaction
    i_start = 1;
    i_addr = 32'h1000;
    i_write = 0;
    #10;
    i_start = 0;

    // Simulate slave response with wait cycles
    #20;
    PRDATA = 32'hDEADBEEF;
    PREADY = 1;
    #10;
    PREADY = 0;

    // Check if the read transaction completed successfully
    if (!o_done) begin
      $display("ERROR: Read transaction did not complete");
      $finish(1); // Exit with non-zero status
    end

    // Check if the read data matches the expected value
    if (o_rdata !== 32'hDEADBEEF) begin
      $display("ERROR: Read data mismatch (expected DEADBEEF, got %h)", o_rdata);
      $finish(1); // Exit with non-zero status
    end

    // Test 3: Back-to-back transactions
    i_start = 1;
    i_addr = 32'h2000;
    i_wdata = 32'hCAFEBABE;
    i_write = 1;
    #10;
    i_start = 0;

    // Simulate slave response with wait cycles
    #20;
    PREADY = 1;
    #10;
    PREADY = 0;

    // Check if the i_write transaction completed successfully
    if (!o_done) begin
      $display("ERROR: Back-to-back i_write transaction did not complete");
      $finish(1); // Exit with non-zero status
    end

    i_start = 1;
    i_addr = 32'h2000;
    i_write = 0;
    #10;
    i_start = 0;

    // Simulate slave response with wait cycles
    #20;
    PRDATA = 32'hCAFEBABE;
    PREADY = 1;
    #10;
    PREADY = 0;

    // Check if the read transaction completed successfully
    if (!o_done) begin
      $display("ERROR: Back-to-back read transaction did not complete");
      $finish(1); // Exit with non-zero status
    end

    // Check if the read data matches the expected value
    if (o_rdata !== 32'hCAFEBABE) begin
      $display("ERROR: Back-to-back read data mismatch (expected CAFEBABE, got %h)", o_rdata);
      $finish(1); // Exit with non-zero status
    end

    // Test 4: Error condition
    i_start = 1;
    i_addr = 32'h3000;
    i_wdata = 32'hBADF00D;
    i_write = 1;
    #10;
    i_start = 0;

    // Simulate slave error response
    #20;
    PSLVERR = 1;
    PREADY = 1;
    #10;
    PSLVERR = 0;
    PREADY = 0;

    // Check if the error condition was handled correctly
    if (!o_done) begin
      $display("ERROR: Error condition not handled correctly");
      $finish(1); // Exit with non-zero status
    end

    // End simulation
    $display("PASS: Testbench passed");
    $finish(0); // Exit with zero status
  end
endmodule