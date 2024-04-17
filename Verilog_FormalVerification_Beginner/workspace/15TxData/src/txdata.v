/********************************************************************************
/*
/* Filename: 	txdata.v
/*
/* Project:	Verilog Tutorial Example file
/*
/* Purpose:	To transmit a given number, in 0x%08x format, out the serial
/*		port.
/*
/* Be aware: I have left bugs left within this design, and kept the formal
/* verification from being complete.  The purpose of this file is not to give
/* you the solution, but to give you enough of it that you don't need to spend
/* all your time writing.
/*
/* Creator:	Dan Gisselquist, Ph.D.
/*		Gisselquist Technology, LLC
/*
/********************************************************************************
/*
/* Written and distributed by Gisselquist Technology, LLC
/*
/* This program is hereby granted to the public domain.
/*
/* This program is distributed in the hope that it will be useful, but WITHOUT
/* ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
/* FITNESS FOR A PARTICULAR PURPOSE.
/*
/*******************************************************************************/
`default_nettype	none

module	txdata(
				input	wire			i_clk,
				input	wire			i_reset,
				input	wire			i_stb,
				input	wire	[31:0]	i_data,
				output	wire			o_busy,
				output	wire			o_uart_tx
			  );
	parameter	UART_SETUP = 868;

	reg	[31:0]	sreg;
	reg	[7:0]	hex, tx_data;
	reg	[3:0]	state;
	reg			tx_stb;

	wire		tx_busy;

	// FSM
	initial	tx_stb = 1'b0;
	initial	state  = 0;
	always @(posedge i_clk) begin
		if (i_reset) begin
			state      <= 0;
			tx_stb     <= 1'b0;
		end else if (!o_busy) begin
			// state <= 0;
			if (i_stb) begin
				state <= 1;
				tx_stb <= 1;
			end
		end else if ( (tx_stb) && (!tx_busy) ) begin
			state <= state + 1;
			if (state >= 4'hD) begin
				tx_stb <= 1'b0;
				state <= 0;
			end
		end
	end

	// sreg
	// 
	// The outgoing data is just a shift register
	initial	sreg = 0;
	always @(posedge i_clk) begin
		if (!o_busy) // && (i_stb)
			sreg <= i_data;
		else if ((!tx_busy)&&(state > 4'h1))
			sreg <= { sreg[27:0], 4'h0 };
	end

	// Convert ASCII to hex
	always @(posedge i_clk) begin
		case(sreg[31:28])
			4'h0: hex <= "0";	// Values in "" specify literal
			4'h1: hex <= "1";	// 8bit values with an ASCII encoding
			4'h2: hex <= "2";
			4'h3: hex <= "3";
			4'h4: hex <= "4";
			4'h5: hex <= "5";
			4'h6: hex <= "6";
			4'h7: hex <= "7";
			4'h8: hex <= "8";
			4'h9: hex <= "9";
			4'ha: hex <= "a";	// Strings work similarly
			4'hb: hex <= "b";	// with the only difference
			4'hc: hex <= "c";	// being that string
			4'hd: hex <= "d";	// literals may be much
			4'he: hex <= "e";	// longer than 8bits
			4'hf: hex <= "f";	// Ex: A >= "1234"
			default: begin end
		endcase
	end

	// Transmit a byte 
	always @(posedge i_clk) begin
		if (!tx_busy) begin
			case(state)
				4'h1: tx_data <= "0";		// These are the values
				4'h2: tx_data <= "x";		// We'll want to output
				4'h3: tx_data <= hex;		// at each state
				4'h4: tx_data <= hex;
				4'h5: tx_data <= hex;
				4'h6: tx_data <= hex;
				4'h7: tx_data <= hex;
				4'h8: tx_data <= hex;
				4'h9: tx_data <= hex;
				4'ha: tx_data <= hex;
				4'hb: tx_data <= "\r";		// Carriage return
				4'hc: tx_data <= "\n";		// Line feed
				default: tx_data <= "Q"; 	// A bad value	
			endcase
		end
	end

	// o_busy
	always @(posedge i_clk) begin
		if( (!i_stb) && !(tx_busy) && (f_minbusy[0] == 0) ) begin
			o_busy <= 1'b0;
		end
	end

//
// Formal Verification
//
`ifndef	FORMAL
	txuart	#(UART_SETUP[23:0])
		txuarti(i_clk, tx_stb, tx_data, o_uart_tx, tx_busy);
`else
	(* anyseq *) wire serial_busy, serial_out;
	assign	o_uart_tx = serial_out;
	assign	tx_busy = serial_busy;
`endif

//
// Formal Verification
//
`ifdef	FORMAL
	initial	assume(i_reset);

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
	initial	assume(!tx_busy);							// Starts IDLE
	always @(posedge i_clk)
		if ($past(i_reset))								// Becomes IDLE after reset
			assume(!tx_busy);
		else if (($past(tx_stb))&&(!$past(tx_busy)))	// Must become BUSY after a new request
			assume(tx_busy);
		else if (!$past(tx_busy))						// Otherwise it cannot become busy without a request
			assume(!tx_busy);

	//  We can usef_minbusy to force any transmit request to take at
	// least four cycles before dropping the busy line
	//		- f_minbusyis just a 2-bit counter
	//		- After passing 3, it waits at zero for the next byte
	reg	[1:0]	f_minbusy;
	initial	f_minbusy = 0;
	always @(posedge i_clk)
		if ( (tx_stb) && (!tx_busy) )
			f_minbusy <= 2'b01;
		else if (f_minbusy != 2'b00)
			f_minbusy <= f_minbusy + 1'b1;

	//  Since(∗anyseq∗)values act like inputs to our design,
	// constraining them by an assumption is appropriate

	always @(*)
		if (f_minbusy != 0)
			assume(tx_busy);


	//
	// Some cover statements
	//
	// You should be able to "see" your design working from these
	// If not ... modify them until you can.
	//
	// Don't forget to set the mode to cover
	// in your SBY file!
	always @(posedge i_clk)
		if (f_past_valid)
			cover($fell(o_busy));
	always @(posedge i_clk) begin
		if ( (f_past_valid) && (!$past(i_reset)) ) begin
			cover($fell(o_busy));
		end
	end

	// What if we look for 0x12345678\r\n?
	reg f_seen_data;
	initial f_seen_data = 0;
	always @(posedge i_clk) begin
		if(i_reset) begin
			f_seen_data <= 1'b0;
		end else if( (i_stb) && (!o_busy) && (i_data == 32'h12345678) ) begin
			f_seen_data = 1'b1;
		end
	end
	always @(posedge i_clk) begin
		if( (f_past_valid) && ($past(i_reset)) && (f_seen_data) ) begin
			cover($fell(o_busy));
		end
	end

	//
	// Some assertions about our sequence of states
	//
	// f_p1reg is a shift register
	//		- f_p1reg[x]is true anytime we are in stagexof our sequence
	//		- We can use this when constructing formal properties
	// 
	// Usingf_p1reg[x]we can make assertions about the different
	// states in our sequence
	//
	// f_p1reg[x]allows us to represent general sequence states
	reg	[12:0]	f_p1reg;
	initial	f_p1reg = 0;
	reg [7:0]	fv_data;
	always @(posedge i_clk) begin
		if ((i_stb)&&(!o_busy)) begin
			f_p1reg <= 1;
			assume(f_p1reg[12:0] == 0);
		end else if (f_p1reg) begin
			if (f_p1reg != 1)
				assert($stable(fv_data));
			if (!tx_busy)
				f_p1reg <= { f_p1reg[12:0], 1'b0 };
			if ((!tx_busy)||(f_minbusy==0)) begin
				if (f_p1reg[0]) begin
					assert((tx_data == "0") && (state == 4'h1));
					assert((sreg == i_data));
				end
				if(f_p1reg[1]) begin
					assert((tx_data == "x") && (state == 4'h2));
				end
				if(f_p1reg[2]) begin
					assert((tx_data == hex) && (state == 4'h3));
				end
				if(f_p1reg[4]) begin
					assert((tx_data == hex) && (state == 4'h4));
				end
				if(f_p1reg[5]) begin
					assert((tx_data == hex) && (state == 4'h5));
				end
				if(f_p1reg[6]) begin
					assert((tx_data == hex) && (state == 4'h6));
				end
				if(f_p1reg[7]) begin
					assert((tx_data == hex) && (state == 4'h7));
				end
				if(f_p1reg[8]) begin
					assert((tx_data == hex) && (state == 4'h8));
				end
				if(f_p1reg[9]) begin
					assert((tx_data == hex) && (state == 4'h9));
				end
				if(f_p1reg[10]) begin
					assert((tx_data == hex) && (state == 4'hA));
				end
				if(f_p1reg[11]) begin
					assert((tx_data == "\r") && (state == 4'hB));
				end
				if(f_p1reg[12]) begin
					assert((tx_data == "\n") && (state == 4'hB));
				end
			end
		end else
			assert(state == 0);
	end

`endif
endmodule
