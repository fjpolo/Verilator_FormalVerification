////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	sfifo.v
//
// Project:	Verilog Tutorial Example file
//
// Purpose:	A synchronous data FIFO.
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
//
// Written and distributed by Gisselquist Technology, LLC
//
// This program is hereby granted to the public domain.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.
//
////////////////////////////////////////////////////////////////////////////////
//
//
`default_nettype	none
//
module sfifo(i_clk, i_wr, i_data, o_full, o_fill, i_rd, o_data, o_empty);
	parameter	BW=8;	// Byte/data width
	parameter 	LGFLEN=4;
	//
	//
	input	wire			i_clk;
	//
	// Write interface
	input	wire			i_wr;
	input	wire [(BW-1):0]	i_data;
	output	reg 			o_full;
	output	reg [LGFLEN:0]	o_fill;
	//
	// Read interface
	input	wire			i_rd;
	output	reg [(BW-1):0]	o_data;
	output	reg				o_empty;	// True if FIFO is empty
	// Define FIFO in memory
	reg	[(BW-1):0]		fifo_mem[0:(1<<LGFLEN)-1];
	// Memory pointers: N+1 bits to hold N values
	reg	[LGFLEN:0]		wr_addr, rd_addr;
	reg	[LGFLEN-1:0]	rd_next;


	wire	w_wr = (i_wr && !o_full);
	wire	w_rd = (i_rd && !o_empty);

	//
	// Write a new value into our FIFO
	//
	initial	wr_addr = 0;
	always @(posedge i_clk)
	if (w_wr)
		wr_addr <= wr_addr + 1'b1;

	always @(posedge i_clk)
	if (w_wr)
		fifo_mem[wr_addr[(LGFLEN-1):0]] <= i_data;

	//
	// Read a value back out of it
	//
	initial	rd_addr = 0;
	always @(posedge i_clk)
	if (w_rd)
		rd_addr <= rd_addr + 1;

	always @(*)
		o_data = fifo_mem[rd_addr[LGFLEN-1:0]];

	//
	// Return some metrics of the FIFO, it's current fill level,
	// whether or not it is full, and likewise whether or not it is
	// empty
	//
	always @(*)
		o_fill = wr_addr - rd_addr;	// Number of values FIFO can hold
	always @(*)
		o_full = o_fill == { 1'b1, {(LGFLEN){1'b0}} };	// Is it full?
	always @(*)
		o_empty = (o_fill  == 0);	// Is it empty?


	// Next address
	always @(*)
		rd_next = rd_addr[LGFLEN-1:0] + 1;


	// Make Verilator happy
	// verilator lint_off UNUSED
	wire	[LGFLEN-1:0]	unused;
	assign	unused = rd_next;
	// verilator lint_on  UNUSED

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//
//
// FORMAL METHODS
//
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
`ifdef	FORMAL

//
// Assumptions about our input(s)
//
//
`ifdef	SFIFO
`define	ASSUME	assume
`else
`define	ASSUME	assert
`endif

	reg	f_past_valid;

	//
	// Assertions about our outputs
	//
	//



	wire	[LGFLEN:0]	f_fill, f_next, f_empty;
	assign	f_fill = wr_addr - rd_addr;
	assign	f_empty = (wr_addr == rd_addr);
	assign	f_next = rd_addr + 1'b1;

	always @(*) begin
		// Fill can never exceed 2^N elements
		assert(f_fill <= { 1'b1, {(LGFLEN){1'b0}}});
		// o_fill should never be different than the internal f_fill
		assert(o_fill == f_fill);
		// Check o_full
		assert(o_full  == (f_fill == {1'b1, {(LGFLEN){1'b0}}}));
		// Check o_empty
		assert(o_empty == (f_fill == 0));
		// Check next_read
		assert(rd_next == f_next[LGFLEN-1:0]);
	end

	// Check output data to be valid
	always @(*)
		assert(fifo_mem[rd_addr] == o_data);


	////////////////////////////////////////////////////////////////////////
	//
	// Formal contract:
	//
	// If you write two values in succession, you should be able to read
	// those same two values in succession some time later.
	//
	////////////////////////////////////////////////////////////////////////
	//
	//
	(* anyconst *)	reg	[LGFLEN:0]	f_first_addr;
					reg	[LGFLEN:0]	f_second_addr;
	(* anyconst *)	reg	[BW-1:0]	f_first_data, f_second_data;

	always @(*)
		f_second_addr = f_first_addr + 1;

	reg	f_first_addr_in_fifo,  f_first_in_fifo;
	reg	f_second_addr_in_fifo, f_second_in_fifo;
	reg	[LGFLEN:0]	f_distance_to_first, f_distance_to_second;

	// Handle f_distance_to_first
	always @(*) begin
		// Unwrap by subtracting the distance to the read address 
		f_distance_to_first = (f_first_addr - rd_addr);
		f_first_addr_in_fifo = 0;
		// Check the distance into the FIFO against fill level
		// if ((!o_empty)&&(f_fill != 0)&&(f_distance_to_first < f_fill))
		if ((!o_empty)&&(f_distance_to_first < f_fill))
			f_first_addr_in_fifo = 1;
		else
			f_first_addr_in_fifo = 0;
	end

	// Handle f_distance_to_second
	always @(*) begin
		f_distance_to_second = (f_second_addr - rd_addr);
		// if ((f_fill != 0) && (f_distance_to_second < f_fill))
		if ((!o_empty)&&(f_distance_to_second < f_fill))
			f_second_addr_in_fifo = 1;
		else
			f_second_addr_in_fifo = 0;
	end

	//
	//  State Transitions
	//
	reg	[1:0]	f_state;
	initial	f_state = 2'b0;
	always @(posedge i_clk)
		case(f_state)
		2'h0: if((w_wr)&&(wr_addr == f_first_addr)&&(i_data == f_first_data))
				// Wrote first value
				f_state <= 2'h1;
		2'h1: if((w_rd)&&(rd_addr == f_first_addr))
				// Test sprung early
				f_state <= 2'h0;
			else if(w_wr)
				f_state <= ((i_data == f_second_data) ? 3'h2 : 2'h0);
		2'h2: if((i_rd)&&(rd_addr == f_first_addr))
				f_state <= 2'h3;
		2'h3: if(i_rd)
				f_state <= 2'h0;
		endcase

	// If we are in state one:
	// 	– The first address must point to something within the FIFO
	// 	– The memory at that location must be our special value
	// 	– The write address must point to the second special address
	always @(*)
		if (f_state == 2'b01) begin
			assert(f_first_addr_in_fifo);
			assert(fifo_mem[f_first_addr] == f_first_data);
			// Wait at the second address to write the second element
			assert(wr_addr == f_second_addr);
		end

	// If we are in state two:
	// 	– 	Both the first and second addresses must point to valid locations within the FIFO
	// 	– 	The values at both locations must match our special values
	always @(*)
		if (f_state == 2'b10) begin
			// First value must be in the FIFO
			assert(f_first_addr_in_fifo);
			assert(fifo_mem[f_first_addr] == f_first_data);
			// Second value too
			assert(f_second_addr_in_fifo);
			assert(fifo_mem[f_second_addr] == f_second_data);
			// Prove that if there's a read, first value is returned
			if ((i_rd)&&(rd_addr == f_first_addr))
				assert(o_data == f_first_data);
		end

	// If we are in state three:
	//	- Second address must point to valid location within FIFO
	//	- Memory at the location must match second special value
	always @(*)
		if (f_state == 2'b11) begin
			// Second value must be in the FIFO
			assert(f_second_addr_in_fifo);
			assert(fifo_mem[f_second_addr] == f_second_data);
			// Prove that if there's a read, second value is returned
			assert(o_data == f_second_data);
		end


	////////////////////////////////////////////////////////////////////////
	//
	//	Cover properties
	//
	////////////////////////////////////////////////////////////////////////
	//
	//
	reg	f_was_full;
	initial	f_was_full = 0;
	
	// Aux reg
	always @(posedge i_clk)
		if (o_full)
			f_was_full <= 1;

	// Cover that FIFO gets empty
	always @(posedge i_clk)
		cover($fell(f_empty));
	always @(posedge i_clk)
		cover($fell(o_empty));

	// Cover Full to Empty transition
	always @(posedge i_clk)
		cover((f_was_full)&&(f_empty));

	// Cover full to not full to full
	always @(posedge i_clk)
		cover($past(o_full,2)&&(!$past(o_full))&&(o_full));

	// Cover empty to not empty to empty
	always @(posedge i_clk)
	if (f_past_valid)
		cover($past(o_empty,2)&&(!$past(o_empty))&& o_empty);

`endif // FORMAL
endmodule
