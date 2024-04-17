// Avoid misspelled identifiers becoming wires
`default_nettype none
//
module maskbus(i_sw, o_led);
	input	wire	[5:0]	i_sw;
	output	wire	[5:0]	o_led;

	wire	[5:0]	w_internal;

	assign	w_internal = 6'b110011;
	assign	o_led = i_sw ^ w_internal;
endmodule