/*
 *  Copyright (C) 2020  Claire Wolf <claire@yosyshq.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

module testbench (
		input 	wire 	[0:0]	i_clk,        // APB clock
		input 	wire 	[0:0]	i_reset_n,    // APB reset (active low)
		input 	wire 	[0:0]	start,      // Start signal to initiate a transaction
		input 	wire 	[31:0] 	addr,   	// Address for the transaction
		input 	wire 	[31:0] 	wdata,  	// Write data (for write transactions)
		input 	wire 	[31:0] 	addr,     	// Address for the transaction
		input 	wire 	[0:0]  	start,    	// Start signal to initiate a transaction
		input 	wire 	[0:0]  	write,    	// Write/read control (1 = write, 0 = read)
		output 	wire 	[0:0]  	done,     	// Transaction completion signal
		output 	wire 	[31:0] 	rdata,    	// Read data (for read transactions)
		output 	wire 	[0:0]  	slverr,   	// Slave error
		output  wire    [31:0]  PADDR,      // APB address
		output  wire    [0:0]   PWRITE,     // APB write/read control (1 = write, 0 = read)
		output  wire    [31:0]  PWDATA,     // APB write data
		output  wire    [0:0]   PSELx,      // APB slave select
		output  wire    [0:0]   PENABLE,    // APB enable
		input   wire    [31:0]  PRDATA,     // APB read data
		input   wire    [0:0]   PREADY,     // APB ready signal from slave
		input   wire    [0:0]   PSLVERR     // APB slave error signal
	  );  
		// Instantiate the APB master
		apb_master master (
		  .i_clk(i_clk),
		  .i_reset_n(i_reset_n),
		  .PADDR(PADDR),
		  .PWRITE(PWRITE),
		  .PWDATA(PWDATA),
		  .PSELx(PSELx),
		  .PENABLE(PENABLE),
		  .PRDATA(rdata),         // PRDATA is driven by the slave (not used here)
		  .PREADY(PREADY),
		  .PSLVERR(PSLVERR),
		  .i_start(start),
		  .i_addr(addr),
		  .i_wdata(wdata),
		  .i_write(write),
		  .o_done(done),
		  .o_rdata(rdata),
		  .o_slverr(slverr)
		);

		// f_past_valid register
		reg	f_past_valid;
		initial	f_past_valid = 0;
		always @(posedge i_clk)
			f_past_valid <= 1'b1;

		// Property: All outputs should be in a known state after reset
		always @(posedge i_clk) begin
			if ((!$past(i_reset_n))&&(i_reset_n)) begin
				assert(PADDR == 'h0);
				assert(PWDATA == 'h0);
				assert(!PWRITE);
				assert(!PSELx);
				assert(!PENABLE);
			end
		end

		// Property: After reset, the master and slave should be ready to accept new transactions
		always @(posedge i_clk) begin
			if ($rose(i_reset_n))
			  assert (!PSELx && !PENABLE);
		end

		//
		// 1. Basic APB Protocol Properties
		//
		// These properties ensure the master and slave adhere to the fundamental APB protocol rules.
		//

		// a. Signal Stability During Transfer
		//  -  Property: During a transfer (PSELx is high), the address (PADDR) and control signals 
		//    (PWRITE, PENABLE) must remain stable.
		always @(posedge i_clk) begin
			if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
				if ((PSELx)&&($past(PSELx))) begin
					assert (PADDR   == $past(PADDR));
					assert (PSELx   == $past(PSELx));
					assert (PWRITE  == $past(PWRITE));
					assert (PENABLE);
				end
		end
	
		// b. PENABLE Timing
		//  - Property: PENABLE must only be high in the second cycle of a transfer.
		always @(posedge i_clk) begin
			if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
				if ((PSELx)&&($past(PSELx))&&(!$past(PENABLE)))
					assert (PENABLE);
		end
	
		// c. Transfer Completion
		//  - Property: After PENABLE is high, the transfer completes, and PSELx and 
		//  PENABLE must deassert in the next cycle.
		always @(posedge i_clk) begin
			if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
				if (($past(PSELx))&&($past(PENABLE))&&($past(PREADY)))
					assert ((!PSELx)&&!(PENABLE));
		end

		//
		// 2. Read/Write Transaction Properties
		// These properties ensure the master and slave handle read and write transactions correctly.
		//

		// a. Write Transaction
		//  - Property: During a write transaction (PWRITE is high), 
		//  the master must drive PWDATA when PENABLE is high.
		always @(posedge i_clk) begin
			if ((PSELx)&&(PWRITE)&&(PENABLE))
				if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
					assert(PWDATA == $past(PWDATA));
		end   
	
		// b. Read Transaction
		//  - Property: During a read transaction (PWRITE is low), 
		//  the slave must drive PRDATA with the correct data when 
		//  PENABLE is high.
		always @(posedge i_clk) begin
			if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n)) 
				if (($past(PSELx))&&(!$past(PWRITE))&&($past(PENABLE))&&($past(PREADY)))
					assert (o_rdata == $past(PRDATA));
		end

		//
		// 3. Error Handling Properties
		// These properties ensure the master and slave handle error conditions correctly.
		//
		always @(*)
			assert(o_slverr == PSLVERR);

		//
		// 4. Timing and Performance Properties
		// These properties ensure the master and slave meet timing requirements.
		//

		// // a. PREADY Assertion
		// //  - Property: The slave must assert PREADY within a specified number of 
		// //  cycles after PSELx is asserted.
		// always @(posedge PCLK) begin
		//     if (PSELx)
		//       assert (##[1:MAX_LATENCY] PREADY);
		// end
		
		// // b. Back-to-Back Transfers
		// //  - Property: The master and slave should handle back-to-back transfers without 
		// //  violating the protocol.
		// always @(posedge PCLK) begin
		//     if ((PSELx)&&(PENABLE))
		//       assert (##1 (PSELx)&&(!PENABLE) ##1 (PSELx)&&(PENABLE));
		// end

endmodule