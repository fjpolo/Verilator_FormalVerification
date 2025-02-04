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
  reg start;
  reg [31:0] addr;
  reg [31:0] wdata;
  reg write;
  wire done;
  wire [31:0] rdata;

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
    .i_start(start),
    .i_addr(addr),
    .i_wdata(wdata),
    .i_write(write),
    .o_done(done),
    .o_rdata(rdata),
    .o_slverr()
  );

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
    start = 0;
    addr = 32'h0;
    wdata = 32'h0;
    write = 0;
    PRDATA = 32'h0;
    PREADY = 0;
    PSLVERR = 0;

    // Wait for reset to complete
    #30;

    // Start a write transaction
    start = 1;
    addr = 32'h1000;
    wdata = 32'hDEADBEEF;
    write = 1;
    #10;
    start = 0;

    // Simulate slave response with wait cycles
    #20;
    PREADY = 1;
    #10;
    PREADY = 0;

    // Check if the write transaction completed successfully
    if (!done) begin
      $display("ERROR: Write transaction did not complete");
      $finish(1); // Exit with non-zero status
    end

    // Start a read transaction
    start = 1;
    addr = 32'h1000;
    write = 0;
    #10;
    start = 0;

    // Simulate slave response with wait cycles
    #20;
    PRDATA = 32'hDEADBEEF;
    PREADY = 1;
    #10;
    PREADY = 0;

    // Check if the read transaction completed successfully
    if (!done) begin
      $display("ERROR: Read transaction did not complete");
      $finish(1); // Exit with non-zero status
    end

    // Check if the read data matches the expected value
    if (rdata !== 32'hDEADBEEF) begin
      $display("ERROR: Read data mismatch (expected DEADBEEF, got %h)", rdata);
      $finish(1); // Exit with non-zero status
    end

    // End simulation
    $display("PASS");
    $finish(0); // Exit with zero status
  end
endmodule