// -----------------------------------------------------------------------------
// Module: APB_slave
// Description: A formally verified APB slave module
// 
// Author:       fjpolo
// Date:         27.01.2025
// Email:        fjpolo@gmail.com
// Github:       @fjpolo
// 
// License: 
// This code is released under the following terms:
// - You are free to use, modify, and distribute this code for any purpose.
// - You must retain this header in all copies or substantial portions of the code.
// 
// Disclaimer:
// This code is provided "as is," without warranty of any kind, express or implied,
// including but not limited to the warranties of merchantability, fitness for a
// particular purpose, and non-infringement. In no event shall the author be liable
// for any claim, damages, or other liability, whether in an action of contract, tort,
// or otherwise, arising from, out of, or in connection with the code or the use
// or other dealings in the code.
// -----------------------------------------------------------------------------
`default_nettype none

module apb_slave #(
	parameter MEMORY_LENGTH = 8
)(
	input 	wire 	[0:0]	i_clk,      // APB clock
	input 	wire 	[0:0]	i_reset_n,  // APB reset (active low)
	input 	wire 	[31:0] 	PADDR,  	// APB address
	input 	wire 	[0:0]	PWRITE,    	// APB write/read control (1 = write, 0 = read)
	input 	wire 	[31:0] 	PWDATA, 	// APB write data
	input 	wire 	[0:0]	PSELx,      // APB slave select
	input 	wire 	[0:0]	PENABLE,   	// APB enable
	output 	reg 	[31:0] 	PRDATA, 	// APB read data
	output 	reg 	[0:0]	PREADY,     // APB ready signal
	output 	reg 	[0:0]	PSLVERR     // APB slave error signal
  );
  
	// Internal reg_file (example: 32-bit registers)
	reg [31:0] reg_file_0;
	reg [31:0] reg_file_1;
	reg [31:0] reg_file_2;
	reg [31:0] reg_file_3;
	reg [31:0] reg_file_4;
	reg [31:0] reg_file_5;
	reg [31:0] reg_file_6;
	reg [31:0] reg_file_7;
	initial reg_file_0 = 'h0;
	initial reg_file_1 = 'h0;
	initial reg_file_2 = 'h0;
	initial reg_file_3 = 'h0;
	initial reg_file_4 = 'h0;
	initial reg_file_5 = 'h0;
	initial reg_file_6 = 'h0;
	initial reg_file_7 = 'h0;
	wire [2:0] reg_file_addr = PADDR[2:0];
  
	// State encoding
    localparam IDLE = 0;
    localparam SETUP = 1;
    localparam ACCESS = 2;
    
    reg [1:0] state;

	wire address_is_valid = (PADDR < MEMORY_LENGTH);
  
	// Initialize state and outputs
	initial begin
	  state = IDLE;
	  PRDATA = 32'h0;
	  PREADY = 1'b0;
	  PSLVERR = 1'b0;
	end
  
	// APB slave FSM
	always @(posedge i_clk) begin
	  if (!i_reset_n) begin
		// Reset state
		state <= IDLE;
		PRDATA <= 32'h0;
		PREADY <= 1'b0;
		PSLVERR <= 1'b0;
		// Register File
		reg_file_0 <= 'h0;
		reg_file_1 <= 'h0;
		reg_file_2 <= 'h0;
		reg_file_3 <= 'h0;
		reg_file_4 <= 'h0;
		reg_file_5 <= 'h0;
		reg_file_6 <= 'h0;
		reg_file_7 <= 'h0;
	  end else begin
		case (state)
		  IDLE: begin
			// Wait for PSELx
			if (PSELx) begin
			  state <= SETUP;
			end
		  end
  
		  SETUP: begin
			// Wait for PENABLE
			if (PENABLE) begin
			  state <= ACCESS;
			end
		  end
  
		  ACCESS: begin
			// Handle read/write transaction
			if (PWRITE) begin
			  // Write transaction
			  if(address_is_valid) begin
			  	//reg_file[reg_file_addr] <= PWDATA; // Write to reg_file (example: 8-bit address)
				case(reg_file_addr)
				0: reg_file_0 <= PWDATA;
				1: reg_file_1 <= PWDATA;
				2: reg_file_2 <= PWDATA;
				3: reg_file_3 <= PWDATA;
				4: reg_file_4 <= PWDATA;
				5: reg_file_5 <= PWDATA;
				6: reg_file_6 <= PWDATA;
				7: reg_file_7 <= PWDATA;
				default: ;
				endcase
			  	PSLVERR <= 1'b0;    
			  end else
				PSLVERR <= 1'b1;           // No error
			end else begin
			  // Read transaction
			  if(address_is_valid) begin
			  	// PRDATA <= reg_file[reg_file_addr]; // Read from reg_file (example: 8-bit address)
				case(reg_file_addr)
				0: PRDATA <= reg_file_0;
				1: PRDATA <= reg_file_1;
				2: PRDATA <= reg_file_2;
				3: PRDATA <= reg_file_3;
				4: PRDATA <= reg_file_4;
				5: PRDATA <= reg_file_5;
				6: PRDATA <= reg_file_6;
				7: PRDATA <= reg_file_7;
				default: ;
				endcase
			  	PSLVERR <= 1'b0;              // No error
			  end else
				PSLVERR <= 1'b1;              // No error
			end
			PREADY <= 1'b1; // Assert PREADY
			state <= IDLE;  // Return to IDLE
		  end
		  default: ;
		endcase
	  end
	end

endmodule
