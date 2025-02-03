// -----------------------------------------------------------------------------
// Module: APB_slave
// Description: A formally verified APB slave module with wait cycles
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

module apb_slave_wait #(
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

	//
	reg [3:0] wait_counter;
	initial wait_counter = 0;
	localparam READ_WRITE_CYCLE_DELAY = 8;
	always @(posedge i_clk) begin
		if(!i_reset_n)
			wait_counter <= 4'h0;
		else
			if(PSELx)
				wait_counter <= wait_counter + 1;
	end
  
	// Internal memory (example: 32-bit registers)
	reg [31:0] memory [0:(MEMORY_LENGTH-1)]; // MEMORY_LENGTH x 32-bit memory
  
	// State encoding
	typedef enum logic [1:0] {
	  IDLE,
	  SETUP,
	  ACCESS
	} state_t;
  
	state_t state;

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
			  memory[PADDR[7:0]] <= PWDATA; // Write to memory (example: 8-bit address)
			  PSLVERR <= 1'b0;              // No error
			end else begin
			  // Read transaction
				if(wait_counter == 7) begin
					PRDATA <= memory[PADDR[7:0]]; // Read from memory (example: 8-bit address)
					PREADY <= 1'b1; // Assert PREADY
					PSLVERR <= !address_is_valid;
					state <= IDLE;  // Return to IDLE
				end else begin
					state <= ACCESS;  // Return to IDLE
				end
			end
		  end
		  default: ;
		endcase
	  end
	end

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//
//  Formal properties
//
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
`ifdef	FORMAL
// Change direction of assumes
`define	ASSERT	assert
`ifdef	APB_SLAVE_WAIT
`define	ASSUME	assume
`else
`define	ASSUME	assert
`endif

	////////////////////////////////////////////////////
	//
	// f_past_valid register
	//
	////////////////////////////////////////////////////
	reg	f_past_valid;
	initial	f_past_valid = 0;
	always @(posedge i_clk)
		f_past_valid <= 1'b1;

	////////////////////////////////////////////////////
	//
	// Reset
	//
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	//
	// BMC
	//
	////////////////////////////////////////////////////

	////////////////////////////////////////////////////
	//
	// Contract
	//
	////////////////////////////////////////////////////   

	//
	// 1. Basic APB Protocol Properties
	// These properties ensure the master and slave adhere to the fundamental APB protocol rules.
	//
	
	// a. Signal Stability During Transfer
	// 	- Property: During a transfer (PSELx is high), the address (PADDR) and control signals 
	//	(PWRITE, PENABLE) must remain stable.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
		if (PSELx) begin
			`ASSUME(PADDR == $past(PADDR));
			`ASSUME(PWRITE == $past(PWRITE));
			`ASSUME(PENABLE == $past(PENABLE));
		end
	end
	
	// b. PENABLE Timing
	// 	-	Property: PENABLE must only be high in the second cycle of a transfer.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
			if ((PSELx)&&(!$past(PENABLE)))
				`ASSUME(PENABLE);
	end

	// c. Transfer Completion
	// 	- Property: After PENABLE is high, the transfer completes, and PSELx and PENABLE must deassert in the next cycle.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
		if (($past(PSELx))&&($past(PENABLE))&&($past(PREADY)))
		`ASSUME((!PSELx)&&(!PENABLE));
	end
	
	//
	// 2. Read/Write Transaction Properties
	// These properties ensure the master and slave handle read and write transactions correctly.
	//
	
	// a. Write Transaction
	// 	- Property: During a write transaction (PWRITE is high), the master must drive PWDATA when PENABLE is high.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
			if (($past(PSELx))&&(PWRITE)&&(!$past(PENABLE))&&(PREADY))
				assert(memory[PADDR[7:0]] == $past(PWDATA));
	end
	
	// b. Read Transaction
	// 	- Property: During a read transaction (PWRITE is low), the slave must drive PRDATA with the correct data when PENABLE is high.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
		if (($past(PSELx))&&(!PWRITE)&&(!$past(PENABLE))&&(PREADY))
		assert(PRDATA == $past(memory[PADDR[7:0]]));
	end

	//
	// 3. Error Handling Properties
	// These properties ensure the master and slave handle error conditions correctly.
	//

	// a. Invalid Address
	// 	- Property: If the address (PADDR) is invalid, the slave should not respond or should signal an error.
	always @(posedge i_clk) begin
		if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
			if (($past(PSELx))&&(PENABLE)&&(!$past(address_is_valid))&&($past(state) == ACCESS)&&(PREADY))
				assert (PSLVERR);
	end

	//
	// 4. Timing and Performance Properties
	// These properties ensure the master and slave meet timing requirements.
	//

	// // a. PREADY Assertion
	// // 	- Property: The slave must assert PREADY within a specified number of cycles after PSELx is asserted.
	// always @(posedge PCLK) begin
	// if (PSELx) begin
	// 	assert (##[1:MAX_LATENCY] PREADY);
	// end
	// end

	// // b. Back-to-Back Transfers
	// // 	- Property: The master and slave should handle back-to-back transfers without violating the protocol.
	// always @(posedge PCLK) begin
	// if (PSELx && PENABLE) begin
	// 	assert (##1 PSELx && !PENABLE ##1 PSELx && PENABLE);
	// end
	// end

	//
	// 5. Reset Behavior
	// These properties ensure the master and slave behave correctly during and after reset.
	//

	// a. Reset State
	// 	- Property: All outputs should be in a known state during reset.
	always @(posedge i_clk) begin
		if (!$past(i_reset_n))
			assert ((PREADY == 0)&&(PSLVERR == 0)&&(PRDATA == 'h0));
	end

	////////////////////////////////////////////////////
	//
	// Induction
	//
	////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////
	//
	// Cover
	//
	////////////////////////////////////////////////////     

	// Read/Write Transactions
	always @(posedge i_clk) begin
		cover (PSELx && PWRITE && PENABLE); // Write transaction
		cover (PSELx && !PWRITE && PENABLE); // Read transaction
	end

	// Error Conditions
	always @(posedge i_clk)
		cover (PSLVERR); // Slave error

	// // Write Transaction with Extended Wait States
	// //	- Cover: A write transaction completes successfully after PREADY takes more than two cycles to assert.
	// always @(posedge i_clk)
	// 	cover (PSELx && PWRITE && PENABLE && !PREADY ##READ_WRITE_CYCLE_DELAY PREADY); // READ_WRITE_CYCLE_DELAY cycles wait

	// // Read Transaction with Extended Wait States
	// // 	- Cover: A read transaction completes successfully after PREADY takes more than two cycles to assert.
	// always @(posedge i_clk)
	// 	cover (PSELx && !PWRITE && PENABLE && !PREADY ##READ_WRITE_CYCLE_DELAY PREADY); // READ_WRITE_CYCLE_DELAY cycles wait

	// Write Transaction with Wait Cycles
	//	- Cover: A write transaction completes successfully after PREADY is delayed.
	always @(posedge i_clk)
	  if (PSELx && PWRITE && PENABLE && PREADY && (wait_counter > 0))
		cover (1); // Write transaction with wait cycles

	// Read Transaction with Wait Cycles
	// 	- Cover: A read transaction completes successfully after PREADY is delayed.
	always @(posedge i_clk)
	if (PSELx && !PWRITE && PENABLE && PREADY && (wait_counter > 0))
		cover (1); // Read transaction with wait cycles

	// Maximum Wait Cycles
	// 	- Cover: A transaction completes successfully after the maximum allowed wait cycles.
	always @(posedge i_clk)
	if (PSELx && PENABLE && PREADY && (wait_counter == (READ_WRITE_CYCLE_DELAY - 1)))
		cover (1); // Transaction with maximum wait cycles

`endif // FORMAL

endmodule
