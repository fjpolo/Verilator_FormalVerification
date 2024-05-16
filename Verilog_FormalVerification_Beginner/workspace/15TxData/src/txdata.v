////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	txdata.v
//
// Project:	Verilog Tutorial Example file
//
// Purpose:	To transmit a given number, in 0x%08x format, out the serial
//		port.
//
// Be aware: I have left bugs left within this design, and kept the formal
// verification from being complete.  The purpose of this file is not to give
// you the solution, but to give you enough of it that you don't need to spend
// all your time writing.
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
module	txdata(i_clk, i_reset, i_stb, i_data, o_busy, o_uart_tx);
	parameter	UART_SETUP = 868;
	input	wire		i_clk, i_reset;
	input	wire		i_stb;
	input	wire	[31:0]	i_data;
	output	wire		o_busy;
	output	wire		o_uart_tx;

	reg	[31:0]	sreg;
	reg	[7:0]	hex, tx_data;
	reg	[3:0]	state;
	reg		tx_stb;
	wire		tx_busy;

	initial	tx_stb = 1'b0;
	initial	state  = 0;

	always @(posedge i_clk)
	if (i_reset) begin
		state      <= 0;
		tx_stb     <= 1'b0;
	end else if (!o_busy) begin
		// state <= 0;
		if (i_stb) begin
			state <= 1;
			tx_stb <= 1;
		end
	end else if ((tx_stb)&&(!tx_busy)) begin
		state <= state + 1;
		if (state >= 4'hd) begin
			tx_stb <= 1'b0;
			state <= 0;
		end
	end

	assign	o_busy = tx_stb;

	initial	sreg = 0;
	always @(posedge i_clk)
	if ((!o_busy)&&(i_stb))
		sreg <= i_data;
	else if ((!tx_busy)&&(state > 4'h1))
		sreg <= { sreg[27:0], 4'h0 };

	always @(posedge i_clk)
		case(sreg[31:28])
			4'h0: hex <= "0";
			4'h1: hex <= "1";
			4'h2: hex <= "2";
			4'h3: hex <= "3";
			4'h4: hex <= "4";
			4'h5: hex <= "5";
			4'h6: hex <= "6";
			4'h7: hex <= "7";
			4'h8: hex <= "8";
			4'h9: hex <= "9";
			4'ha: hex <= "a";
			4'hb: hex <= "b";
			4'hc: hex <= "c";
			4'hd: hex <= "d";
			4'he: hex <= "e";
			4'hf: hex <= "f";
			default: begin end
		endcase

	always @(posedge i_clk)
		if (!tx_busy)
			case(state)
				4'h1: tx_data <= "0";
				4'h2: tx_data <= "x";
				4'h3: tx_data <= hex;
				4'h4: tx_data <= hex;
				4'h5: tx_data <= hex;
				4'h6: tx_data <= hex;
				4'h7: tx_data <= hex;
				4'h8: tx_data <= hex;
				4'h9: tx_data <= hex;
				4'ha: tx_data <= hex;
				4'hb: tx_data <= "\r";
				4'hc: tx_data <= "\n";
				default: tx_data <= "0";
			endcase

`ifndef	FORMAL
	txuart	#(UART_SETUP[23:0]) txuarti(i_clk, tx_stb, tx_data, o_uart_tx, tx_busy);
`else
	(* anyseq *) wire serial_busy, serial_out;
	assign	o_uart_tx = serial_out;
	assign	tx_busy = serial_busy;
`endif

`ifdef	FORMAL
	
	// Initial assuzmptions
	initial	assume(i_reset);
	initial	assume(!tx_busy);

	// fv_data
	reg	[7:0]	fv_data;
	always @(posedge i_clk)
		if ((!o_busy)&&(i_stb))
			fv_data <= i_data;

	// f_past_valid
	reg	f_past_valid;
	initial	f_past_valid = 1'b0;
	always @(posedge i_clk)
		f_past_valid = 1'b1;

	//
	// Make some assumptions about tx_busy
	//
	// it needs to become busy upon a request given to it
	// but not before.  Upon a request, it needs to stay
	// busy for a minimum period of time
	always @(posedge i_clk)
		if ($past(i_reset))
			assume(!tx_busy);
		else if (($past(tx_stb))&&(!$past(tx_busy)))
			assume(tx_busy);
		else if (!$past(tx_busy))
			assume(!tx_busy);

	reg	[1:0]	f_minbusy;
	initial	f_minbusy = 0;
	always @(posedge i_clk)
		if ((tx_stb)&&(!tx_busy))
			f_minbusy <= 2'b01;
		else if (f_minbusy != 2'b00)
			f_minbusy <= f_minbusy + 1'b1;

	always @(*)
		if (f_minbusy != 0)
			assume(tx_busy);


	//
	// Some cover statements
	//

	// You should be able to "see" your design working from these
	// If not ... modify them until you can.
	//
	always @(posedge i_clk)
		if ((f_past_valid)&&(!$past(i_reset))&&(o_busy))
			cover($fell(o_busy));

	// Look for0x12345678\r\n
	reg f_seen_data;
	initial f_seen_data = 0;
	always @(posedge i_clk)
		if(i_reset)
			f_seen_data <= 1'b0;
		else if((i_stb)&&(!o_busy)&&(i_data == 32'h12345678))
			f_seen_data <= 1'b1;

	always @(posedge i_clk)
		if((f_past_valid)&&(!$past(i_reset))&&(f_seen_data))
			cover($fell(o_busy));

	//
	// Some assertions about our sequence of states
	//
	reg	[15:0]	p1reg;
	initial	p1reg = 0;									// p1reg is one clock cycle behind state, so it's synchronized with tx_data, sreg
	always @(posedge i_clk)
		if((f_past_valid)&&(!$past(i_reset)))
			if ((i_stb)&&(!o_busy)) begin
				p1reg <= 1;								// Start Tx
				assert(p1reg[11:1] == 0);				// p1reg = 0000_0000_0001
			end else if(p1reg) begin
				if (p1reg != 1)
					assert($stable(fv_data));
				if (!tx_busy)
					p1reg <= { p1reg[14:0], 1'b0 };		// Tx finished - Move to next char
				if ((!tx_busy)||(!f_minbusy)) begin		// Transmitting..
					if ($past(p1reg[0])) begin
						assert(tx_data == "0");
						assert(state == 2);
						assert(sreg == i_data);
					end
					if ($past(p1reg[1])) begin
						assert(tx_data == "x");
						assert(state == 3);
						assert(sreg == i_data);
					end
					if ($past(p1reg[2])) begin
						assert(tx_data == $past(fv_data[31:28]));
						assert(state == 4);
						assert(sreg == i_data);
					end
					if ($past(p1reg[3])) begin
						assert(tx_data == $past(fv_data[27:24]));
						assert(state == 5);
						assert(sreg == i_data);
					end
					if ($past(p1reg[4])) begin
						assert(tx_data == $past(fv_data[23:20]));
						assert(state == 6);
						assert(sreg == i_data);
					end
					if ($past(p1reg[5])) begin
						assert(tx_data == $past(fv_data[19:16]));
						assert(state == 6);
						assert(sreg == i_data);
					end
					if ($past(p1reg[6])) begin
						assert(tx_data == $past(fv_data[15:12]));
						assert(state == 7);
						assert(sreg == i_data);
					end
					if ($past(p1reg[7])) begin
						assert(tx_data == $past(fv_data[11:8]));
						assert(state == 8);
						assert(sreg == i_data);
					end
					if ($past(p1reg[8])) begin
						assert(tx_data == $past(fv_data[7:4]));
						assert(state == 9);
						assert(sreg == i_data);
					end
					if ($past(p1reg[9])) begin
						assert(tx_data == $past(fv_data[3:0]));
						assert(state == 10);
						assert(sreg == i_data);
					end
					if ($past(p1reg[10])) begin
						assert(tx_data == "\r");
						assert(state == 11);
						assert(sreg == i_data);
					end
					if ($past(p1reg[11])) begin
						assert(tx_data == "\n");
						assert(state == 0);
						assert(sreg == i_data);
					end

				end
			// end else // if((!i_stb)&&(o_busy)||(!p1reg))// if(!p1reg) // if(($past(tx_stb))&&(!$past(tx_busy))&&($past(state)==4'hd))
			// 	assert(state == 0);
			end

		// always @(posedge i_clk)
		// 	if((f_past_valid)&&(!$past(i_reset)))
		// 		assert(p1reg == $past(state));

`endif
endmodule
