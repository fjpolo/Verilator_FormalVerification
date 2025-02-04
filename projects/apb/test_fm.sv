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
		input 	wire 	[0:0]	clk,        // APB clock
		input 	wire 	[0:0]	reset_n,    // APB reset (active low)
		input 	wire 	[0:0]	start,      // Start signal to initiate a transaction
		input 	wire 	[31:0] 	addr,   	// Address for the transaction
		input 	wire 	[31:0] 	wdata,  	// Write data (for write transactions)
		input 	wire 	[31:0] 	addr,     	// Address for the transaction
		input 	wire 	[0:0]  	start,    	// Start signal to initiate a transaction
		input 	wire 	[0:0]  	write,    	// Write/read control (1 = write, 0 = read)
		output 	reg 	[0:0]  	done,     	// Transaction completion signal
		output 	reg 	[31:0] 	rdata,    	// Read data (for read transactions)
		output 	reg 	[0:0]  	slverr,   	// Slave error
		output  reg     [31:0]  PADDR,      // APB address
		output  reg     [0:0]   PWRITE,     // APB write/read control (1 = write, 0 = read)
		output  reg     [31:0]  PWDATA,     // APB write data
		output  reg     [0:0]   PSELx,      // APB slave select
		output  reg     [0:0]   PENABLE,    // APB enable
		input   wire    [31:0]  PRDATA,     // APB read data
		input   wire    [0:0]   PREADY,     // APB ready signal from slave
		input   wire    [0:0]   PSLVERR     // APB slave error signal
	  );  
		// Instantiate the APB master
		apb_master master (
		  .i_clk(clk),
		  .i_reset_n(reset_n),
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
	  
		// Assumptions and assertions
		always @(posedge PCLK) begin
		  if (!PRESETn) begin
			// Reset state assumptions
			assume (PADDR == 32'h0);
			assume (PWRITE == 1'b0);
			assume (PWDATA == 32'h0);
			assume (PSELx == 1'b0);
			assume (PENABLE == 1'b0);
			assume (done == 1'b0);
		  end else begin
			// Protocol assumptions
			assume (PREADY == 0 || PREADY == 1); // PREADY is always 0 or 1
			assume (PSLVERR == 0 || PSLVERR == 1); // PSLVERR is always 0 or 1
	  
			// Write transaction assertions
			if (write && start) begin
			  assume (PADDR == addr); // Address is stable during write
			  assume (PWDATA == wdata); // Write data is stable during write
			  assume (PSELx == 1'b1); // PSELx is asserted during write
			  assume (PENABLE == 1'b0); // PENABLE is not asserted in the first cycle
	  
			  // Check that PENABLE is asserted in the second cycle
			  if ($past(PSELx) && !$past(PENABLE)) begin
				assert (PENABLE == 1'b1);
			  end
	  
			  // Check that the transaction completes when PREADY is asserted
			  if (PENABLE && PREADY) begin
				assert (done == 1'b1);
			  end
			end
	  
			// Read transaction assertions
			if (!write && start) begin
			  assume (PADDR == addr); // Address is stable during read
			  assume (PSELx == 1'b1); // PSELx is asserted during read
			  assume (PENABLE == 1'b0); // PENABLE is not asserted in the first cycle
	  
			  // Check that PENABLE is asserted in the second cycle
			  if ($past(PSELx) && !$past(PENABLE)) begin
				assert (PENABLE == 1'b1);
			  end
	  
			  // Check that the transaction completes when PREADY is asserted
			  if (PENABLE && PREADY) begin
				assert (done == 1'b1);
			  end
			end
	  
			// Wait state assertions
			if (PSELx && PENABLE && !PREADY) begin
			  // Signals must remain stable during wait states
			  assert (PADDR == $past(PADDR));
			  assert (PWRITE == $past(PWRITE));
			  assert (PWDATA == $past(PWDATA));
			  assert (PSELx == $past(PSELx));
			  assert (PENABLE == $past(PENABLE));
			end
		  end
		end
	  endmodule