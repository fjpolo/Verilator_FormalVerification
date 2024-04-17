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
  reg [0:0] PI_i_clk;
  reg [7:0] PI_i_data;
  reg [0:0] PI_i_wr;
  txuart UUT (
    .i_clk(PI_i_clk),
    .i_data(PI_i_data),
    .i_wr(PI_i_wr)
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
    // UUT.$formal$txuart.\v:227$25_EN  = 1'b0;
    // UUT.$formal$txuart.\v:230$26_EN  = 1'b0;
    // UUT.$formal$txuart.\v:236$27_EN  = 1'b0;
    // UUT.$formal$txuart.\v:242$28_EN  = 1'b0;
    // UUT.$formal$txuart.\v:243$29_EN  = 1'b0;
    // UUT.$formal$txuart.\v:244$30_EN  = 1'b0;
    // UUT.$formal$txuart.\v:245$31_EN  = 1'b0;
    // UUT.$formal$txuart.\v:246$32_EN  = 1'b0;
    // UUT.$formal$txuart.\v:247$33_EN  = 1'b0;
    // UUT.$formal$txuart.\v:248$34_EN  = 1'b0;
    // UUT.$formal$txuart.\v:249$35_EN  = 1'b0;
    // UUT.$formal$txuart.\v:250$36_EN  = 1'b0;
    // UUT.$formal$txuart.\v:251$37_EN  = 1'b0;
    // UUT.$formal$txuart.\v:252$38_EN  = 1'b0;
    // UUT.$formal$txuart.\v:278$41_EN  = 1'b0;
    // UUT.$formal$txuart.\v:287$43_EN  = 1'b0;
    // UUT.$formal$txuart.\v:295$46_EN  = 1'b0;
    // UUT.$formal$txuart.\v:315$48_EN  = 1'b0;
    // UUT.$formal$txuart.\v:316$49_EN  = 1'b0;
    // UUT.$formal$txuart.\v:318$50_EN  = 1'b0;
    UUT._witness_.anyinit_procdff_600 = 1'b0;
    UUT._witness_.anyinit_procdff_601 = 8'b00000000;
    UUT._witness_.anyinit_procdff_602 = 1'b0;
    UUT._witness_.anyinit_procdff_604 = 1'b0;
    UUT._witness_.anyinit_procdff_606 = 1'b0;
    UUT._witness_.anyinit_procdff_608 = 1'b0;
    UUT._witness_.anyinit_procdff_610 = 1'b0;
    UUT._witness_.anyinit_procdff_612 = 1'b0;
    UUT._witness_.anyinit_procdff_614 = 1'b0;
    UUT._witness_.anyinit_procdff_615 = 24'b000000000000000000000000;
    UUT._witness_.anyinit_procdff_616 = 1'b0;
    UUT._witness_.anyinit_procdff_618 = 1'b0;
    UUT._witness_.anyinit_procdff_620 = 1'b0;
    UUT._witness_.anyinit_procdff_621 = 8'b10000000;
    UUT._witness_.anyinit_procdff_624 = 1'b0;
    UUT._witness_.anyinit_procdff_626 = 1'b0;
    UUT._witness_.anyinit_procdff_628 = 1'b0;
    UUT._witness_.anyinit_procdff_630 = 1'b0;
    UUT._witness_.anyinit_procdff_632 = 1'b0;
    UUT._witness_.anyinit_procdff_634 = 1'b0;
    UUT._witness_.anyinit_procdff_636 = 1'b0;
    UUT._witness_.anyinit_procdff_638 = 1'b0;
    UUT._witness_.anyinit_procdff_640 = 1'b0;
    UUT._witness_.anyinit_procdff_642 = 1'b0;
    UUT._witness_.anyinit_procdff_644 = 1'b0;
    UUT._witness_.anyinit_procdff_646 = 1'b0;
    UUT._witness_.anyinit_procdff_647 = 1'b0;
    UUT._witness_.anyinit_procdff_648 = 8'b00000000;
    UUT._witness_.anyinit_procdff_649 = 1'b0;
    UUT._witness_.anyinit_procdff_651 = 1'b0;
    UUT._witness_.anyinit_procdff_652 = 1'b0;
    UUT._witness_.anyinit_procdff_653 = 8'b00000000;
    UUT._witness_.anyinit_procdff_654 = 1'b0;
    UUT._witness_.anyinit_procdff_655 = 8'b00000000;
    UUT._witness_.anyinit_procdff_656 = 1'b0;
    UUT._witness_.anyinit_procdff_658 = 1'b0;
    UUT._witness_.anyinit_procdff_661 = 1'b0;
    UUT._witness_.anyinit_procdff_662 = 1'b0;
    UUT._witness_.anyinit_procdff_663 = 1'b1;
    UUT._witness_.anyinit_procdff_664 = 8'b10000000;
    UUT.baud_stb = 1'b0;
    UUT.counter = 24'b000000000000000000000100;
    UUT.f_past_valid = 1'b0;
    UUT.fv_data = 8'b00011001;
    UUT.lcl_data = 9'b011111110;
    UUT.o_busy = 1'b1;
    UUT.state = 4'b1000;

    // state 0
    PI_i_clk = 1'b0;
    PI_i_data = 8'b00000000;
    PI_i_wr = 1'b0;
  end
  always @(posedge clock) begin
    // state 1
    if (cycle == 0) begin
      PI_i_clk <= 1'b0;
      PI_i_data <= 8'b10000000;
      PI_i_wr <= 1'b0;
    end

    // state 2
    if (cycle == 1) begin
      PI_i_clk <= 1'b0;
      PI_i_data <= 8'b00000000;
      PI_i_wr <= 1'b0;
    end

    // state 3
    if (cycle == 2) begin
      PI_i_clk <= 1'b0;
      PI_i_data <= 8'b01111111;
      PI_i_wr <= 1'b0;
    end

    // state 4
    if (cycle == 3) begin
      PI_i_clk <= 1'b0;
      PI_i_data <= 8'b11111111;
      PI_i_wr <= 1'b1;
    end

    // state 5
    if (cycle == 4) begin
      PI_i_clk <= 1'b0;
      PI_i_data <= 8'b11111111;
      PI_i_wr <= 1'b1;
    end

    genclock <= cycle < 5;
    cycle <= cycle + 1;
  end
endmodule
