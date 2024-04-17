`ifndef VERILATOR
module testbench;
  reg [4095:0] vcdfile;
  reg clock;
`else
module testbench(input clock, output reg genclock);
  initial genclock = 1;
`endif
  reg genclock = 1;
  reg [31:0] cycle = 0;
  reg [31:0] PI_i_data;
  reg [0:0] PI_i_we;
  reg [0:0] PI_i_stb;
  reg [0:0] PI_i_addr;
  reg [0:0] PI_i_clk;
  reg [0:0] PI_i_cyc;
  reqwalker UUT (
    .i_data(PI_i_data),
    .i_we(PI_i_we),
    .i_stb(PI_i_stb),
    .i_addr(PI_i_addr),
    .i_clk(PI_i_clk),
    .i_cyc(PI_i_cyc)
  );
`ifndef VERILATOR
  initial begin
    if ($value$plusargs("vcd=%s", vcdfile)) begin
      $dumpfile(vcdfile);
      $dumpvars(0, testbench);
    end
    #5 clock = 0;
    while (genclock) begin
      #5 clock = 0;
      #5 clock = 1;
    end
  end
`endif
  initial begin
`ifndef VERILATOR
    #1;
`endif
    // UUT.$auto$async2sync.\cc:205:execute$713  = 6'b000000;
    // UUT.$formal$reqwalker.\v:127$33_EN  = 1'b0;
    // UUT.$formal$reqwalker.\v:163$48_EN  = 1'b0;
    // UUT.$formal$reqwalker.\v:169$50_EN  = 1'b0;
    // UUT.$formal$reqwalker.\v:201$60_EN  = 1'b0;
    // UUT.$formal$reqwalker.\v:205$61_EN  = 1'b0;
    UUT._witness_.anyinit_procdff_643 = 1'b0;
    UUT._witness_.anyinit_procdff_644 = 1'b0;
    UUT._witness_.anyinit_procdff_646 = 1'b0;
    UUT._witness_.anyinit_procdff_647 = 1'b0;
    UUT._witness_.anyinit_procdff_648 = 1'b0;
    UUT._witness_.anyinit_procdff_650 = 1'b0;
    UUT._witness_.anyinit_procdff_651 = 1'b0;
    UUT._witness_.anyinit_procdff_652 = 1'b1;
    UUT._witness_.anyinit_procdff_653 = 1'b1;
    UUT._witness_.anyinit_procdff_654 = 32'b10000000000000000000000000000000;
    UUT._witness_.anyinit_procdff_663 = 1'b0;
    UUT._witness_.anyinit_procdff_666 = 1'b0;
    UUT._witness_.anyinit_procdff_667 = 1'b0;
    UUT._witness_.anyinit_procdff_669 = 1'b0;
    UUT._witness_.anyinit_procdff_670 = 1'b0;
    UUT._witness_.anyinit_procdff_671 = 4'b0000;
    UUT._witness_.anyinit_procdff_672 = 1'b0;
    UUT._witness_.anyinit_procdff_674 = 1'b0;
    UUT._witness_.anyinit_procdff_675 = 1'b0;
    UUT._witness_.anyinit_procdff_676 = 1'b0;
    UUT._witness_.anyinit_procdff_677 = 1'b0;
    UUT._witness_.anyinit_procdff_679 = 1'b0;
    UUT._witness_.anyinit_procdff_681 = 1'b0;
    UUT._witness_.anyinit_procdff_682 = 1'b0;
    UUT._witness_.anyinit_procdff_683 = 1'b0;
    UUT._witness_.anyinit_procdff_685 = 1'b0;
    UUT._witness_.anyinit_procdff_686 = 1'b0;
    UUT._witness_.anyinit_procdff_687 = 1'b1;
    UUT._witness_.anyinit_procdff_688 = 1'b1;
    UUT._witness_.anyinit_procdff_689 = 32'b10000000000000000000000000000000;
    UUT._witness_.anyinit_procdff_698 = 1'b0;
    UUT.f_past_valid = 1'b0;
    UUT.o_ack = 1'b0;
    UUT.state = 4'b0000;

    // state 0
    PI_i_data = 32'b00000000000000000000000000000000;
    PI_i_we = 1'b0;
    PI_i_stb = 1'b0;
    PI_i_addr = 1'b0;
    PI_i_clk = 1'b0;
    PI_i_cyc = 1'b0;
  end
  always @(posedge clock) begin
    // state 1
    if (cycle == 0) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b1;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b1;
    end

    // state 2
    if (cycle == 1) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b0;
      PI_i_stb <= 1'b1;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b1;
    end

    // state 3
    if (cycle == 2) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b0;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b0;
    end

    // state 4
    if (cycle == 3) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b0;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b0;
    end

    // state 5
    if (cycle == 4) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b0;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b0;
    end

    // state 6
    if (cycle == 5) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b0;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b0;
    end

    // state 7
    if (cycle == 6) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b0;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b0;
    end

    // state 8
    if (cycle == 7) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b0;
      PI_i_stb <= 1'b0;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b0;
    end

    // state 9
    if (cycle == 8) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b0;
      PI_i_stb <= 1'b1;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b1;
    end

    // state 10
    if (cycle == 9) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b0;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b0;
    end

    // state 11
    if (cycle == 10) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b0;
      PI_i_stb <= 1'b1;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b1;
    end

    // state 12
    if (cycle == 11) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b1;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b1;
    end

    // state 13
    if (cycle == 12) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b1;
      PI_i_stb <= 1'b1;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b1;
    end

    // state 14
    if (cycle == 13) begin
      PI_i_data <= 32'b00000000000000000000000000000000;
      PI_i_we <= 1'b0;
      PI_i_stb <= 1'b0;
      PI_i_addr <= 1'b0;
      PI_i_clk <= 1'b0;
      PI_i_cyc <= 1'b0;
    end

    genclock <= cycle < 14;
    cycle <= cycle + 1;
  end
endmodule
