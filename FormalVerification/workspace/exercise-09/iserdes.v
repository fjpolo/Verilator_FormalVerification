/*******************************************************************************
/*
/* Filename: 	iserdes.v
/*
/* Project:	A set of Yosys Formal Verification exercises
/*
/* Purpose:	An example input SERDES operator
/*
/* Assume:
/*	1. Two clocks, where one clock (i_fast_clk) is exactly WIDTH
/*		times faster than (i_slow_clk), and where
/*
/*	2. i_slow_clk and i_fast_clk share a positive edge transition
/*
/* To prove:
/*
/*	1. That the output returned on the positive edge of the slow clock,
/*		is the input that was received
/*
/*	2. That the slow clock outputs are stable, over the slow clock
/*
/*
/* Creator:	Dan Gisselquist, Ph.D.
/*		Gisselquist Technology, LLC
/*
/*******************************************************************************
/*
/* Copyright (C) 2018-2021, Gisselquist Technology, LLC
/*
/* This program is free software (firmware): you can redistribute it and/or
/* modify it under the terms of the GNU General Public License as published
/* by the Free Software Foundation, either version 3 of the License, or (at
/* your option) any later version.
/*
/* This program is distributed in the hope that it will be useful, but WITHOUT
/* ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
/* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
/* for more details.
/*
/* You should have received a copy of the GNU General Public License along
/* with this program.  (It's in the $(ROOT)/doc directory.  Run make with no
/* target there if the PDF file isn't present.)  If not, see
/* <http://www.gnu.org/licenses/> for a copy.
/*
/* License:	GPL, v3, as defined and found on www.gnu.org,
/*
/*		http://www.gnu.org/licenses/gpl.html
/*
/******************************************************************************/
`default_nettype	none

module iserdes #(
		parameter					WIDTH=10,
		parameter	[(WIDTH-1):0]	RESET_VALUE = 0
	) (
		input	wire				i_slow_clk, i_fast_clk,
									i_areset_n,
		input	wire				i_pin,
		output	reg	[(WIDTH-1):0]	o_word
	);
	parameter 	[0:0]	F_OPT_CLK2FFLOGIC = 1'b1;

	reg	[WIDTH-1:0]	r_word;


	//
	// The basic input SERDESE operator
	//
	always @(posedge i_fast_clk, negedge i_areset_n)
		if (!i_areset_n)
			r_word <= RESET_VALUE;
		else
			r_word <= { r_word[(WIDTH-2):0], i_pin };

	always @(posedge i_slow_clk, negedge i_areset_n)
		if (!i_areset_n)
			o_word <= RESET_VALUE;
		else
			o_word <= { r_word[(WIDTH-2):0], i_pin };

`ifdef	FORMAL

	`ifdef	SERDES_STANDALONE
	`define	ASSUME	assume
	`else
	`define	ASSUME	assert
	`endif

	generate if(F_OPT_CLK2FFLOGIC) begin
		(* gclk *) wire gbl_clk;
		
		reg	f_past_valid;
		initial	f_past_valid = 1'b0;
		always @(posedge gbl_clk)
			f_past_valid <= 1'b1;

			// Reset
			always @(posedge gbl_clk)
				if((f_past_valid)&&($fell(i_areset_n)))
					assert(o_word == RESET_VALUE);

			// 1. Assume that two clocks, where one clock (i_fast_clk) is exactly WIDTH times faster than (i_slow_clk)
			always @(posedge gbl_clk) begin
				if(f_past_valid)
					`ASSUME(i_fast_clk == i_slow_clk);
			end
			// 2. Assume that i_slow_clk and i_fast_clk share a positive edge transition
			always @(posedge gbl_clk) begin
				if(f_past_valid)
					`ASSUME(i_fast_clk == $past(i_slow_clk, WIDTH));
			end
		// 1. Prove that the output returned on the positive edge of the slow clock, is the input that was received
		always @(posedge gbl_clk)
			if((f_past_valid)&&($rose(i_slow_clk))&&($rose(i_fast_clk))&&($past(i_pin))&&(i_areset_n)) begin
				`ASSUME($stable(i_slow_clk));
				assert(o_word == { $past(r_word[(WIDTH-2):0]), $past(i_pin) });
			end
		// 2. Prove that the slow clock outputs are stable, over the slow clock
		always @(posedge gbl_clk)
			if((f_past_valid)&&(!$rose(i_slow_clk))&&(i_areset_n))
				assert($stable(o_word));

		end
	endgenerate




`endif // FORMAL
endmodule
