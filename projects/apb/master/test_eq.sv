/*
 *  Copyright (C) 2024 fjpolo <fjpolo@gmail.com>
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

module miter (
		input wire clk,          // APB clock
		input wire reset_n,       // APB reset (active low)
		input wire start,         // Start signal to initiate a transaction
		input wire [31:0] addr,   // Address for the transaction
		input wire [31:0] wdata,  // Write data (for write transactions)
		input wire write,         // Write/read control (1 = write, 0 = read)
		input wire PREADY,        // APB ready signal from slave
		input wire PSLVERR        // APB slave error signal
	  );
		// Reference APB master signals
		wire [31:0] ref_PADDR;
		wire ref_PWRITE;
		wire [31:0] ref_PWDATA;
		wire ref_PSELx;
		wire ref_PENABLE;
		wire ref_done;
		wire [31:0] ref_rdata;
		wire ref_slverr;
		
		// Unit under test (UUT) APB master signals
		wire [31:0] uut_PADDR;
		wire uut_PWRITE;
		wire [31:0] uut_PWDATA;
		wire uut_PSELx;
		wire uut_PENABLE;
		wire uut_done;
		wire [31:0] uut_rdata;
		wire uut_slverr;
	  
		// Instantiate the reference APB master
		apb_master ref (
		  .i_clk(clk),
		  .i_reset_n(reset_n),
		  .PADDR(ref_PADDR),
		  .PWRITE(ref_PWRITE),
		  .PWDATA(ref_PWDATA),
		  .PSELx(ref_PSELx),
		  .PENABLE(ref_PENABLE),
		  .PRDATA(ref_rdata), // PRDATA is driven by the slave (not used here)
		  .PREADY(PREADY),
		  .PSLVERR(PSLVERR),
		  .i_start(start),
		  .i_addr(addr),
		  .i_wdata(wdata),
		  .i_write(write),
		  .o_done(ref_done),
		  .o_rdata(ref_rdata),
		  .o_slverr(ref_slverr),
		  .mutsel(1'b0)
		);
	  
		// Instantiate the unit under test (UUT) APB master
		apb_master uut (
		  .i_clk(clk),
		  .i_reset_n(reset_n),
		  .PADDR(uut_PADDR),
		  .PWRITE(uut_PWRITE),
		  .PWDATA(uut_PWDATA),
		  .PSELx(uut_PSELx),
		  .PENABLE(uut_PENABLE),
		  .PRDATA(uut_rdata), // PRDATA is driven by the slave (not used here)
		  .PREADY(PREADY),
		  .PSLVERR(PSLVERR),
		  .i_start(start),
		  .i_addr(addr),
		  .i_wdata(wdata),
		  .i_write(write),
		  .o_done(uut_done),
		  .o_rdata(uut_rdata),
		  .o_slverr(uut_slverr),
		  .mutsel(1'b1)
		);
	  
		// Assumptions and assertions
		always @(posedge clk) begin
		  if (!reset_n) begin
			// Reset state assumptions
			assume (ref_PADDR == 32'h0);
			assume (ref_PWRITE == 1'b0);
			assume (ref_PWDATA == 32'h0);
			assume (ref_PSELx == 1'b0);
			assume (ref_PENABLE == 1'b0);
			assume (ref_done == 1'b0);
			assume (ref_slverr == 1'b0);
	  
			assume (uut_PADDR == 32'h0);
			assume (uut_PWRITE == 1'b0);
			assume (uut_PWDATA == 32'h0);
			assume (uut_PSELx == 1'b0);
			assume (uut_PENABLE == 1'b0);
			assume (uut_done == 1'b0);
			assume (uut_slverr == 1'b0);
		  end else begin
			// Protocol assumptions
			assume (PREADY == 0 || PREADY == 1); // PREADY is always 0 or 1
			assume (PSLVERR == 0 || PSLVERR == 1); // PSLVERR is always 0 or 1
	  
			// Write transaction assertions
			if (write && start) begin
			  assume (ref_PADDR == addr); // Address is stable during write
			  assume (ref_PWDATA == wdata); // Write data is stable during write
			  assume (ref_PSELx == 1'b1); // PSELx is asserted during write
			  assume (ref_PENABLE == 1'b0); // PENABLE is not asserted in the first cycle
	  
			  assume (uut_PADDR == addr); // Address is stable during write
			  assume (uut_PWDATA == wdata); // Write data is stable during write
			  assume (uut_PSELx == 1'b1); // PSELx is asserted during write
			  assume (uut_PENABLE == 1'b0); // PENABLE is not asserted in the first cycle
	  
			  // Check that PENABLE is asserted in the second cycle
			  if ($past(ref_PSELx) && !$past(ref_PENABLE)) begin
				assert (ref_PENABLE == 1'b1);
			  end
			  if ($past(uut_PSELx) && !$past(uut_PENABLE)) begin
				assert (uut_PENABLE == 1'b1);
			  end
	  
			  // Check that the transaction completes when PREADY is asserted
			  if (ref_PENABLE && PREADY) begin
				assert (ref_done == 1'b1);
				assert (ref_slverr == uut_slverr);
			end
			if (uut_PENABLE && PREADY) begin
				assert (uut_done == 1'b1);
				assert (ref_slverr == uut_slverr);
			  end
			end
	  
			// Read transaction assertions
			if (!write && start) begin
			  assume (ref_PADDR == addr); // Address is stable during read
			  assume (ref_PSELx == 1'b1); // PSELx is asserted during read
			  assume (ref_PENABLE == 1'b0); // PENABLE is not asserted in the first cycle
	  
			  assume (uut_PADDR == addr); // Address is stable during read
			  assume (uut_PSELx == 1'b1); // PSELx is asserted during read
			  assume (uut_PENABLE == 1'b0); // PENABLE is not asserted in the first cycle
	  
			  // Check that PENABLE is asserted in the second cycle
			  if ($past(ref_PSELx) && !$past(ref_PENABLE)) begin
				assert (ref_PENABLE == 1'b1);
			  end
			  if ($past(uut_PSELx) && !$past(uut_PENABLE)) begin
				assert (uut_PENABLE == 1'b1);
			  end
	  
			  // Check that the transaction completes when PREADY is asserted
			  if (ref_PENABLE && PREADY) begin
				assert (ref_done == 1'b1);
			  end
			  if (uut_PENABLE && PREADY) begin
				assert (uut_done == 1'b1);
			  end
			end
	  
			// Wait state assertions
			if (ref_PSELx && ref_PENABLE && !PREADY) begin
			  // Signals must remain stable during wait states
			  assert (ref_PADDR == $past(ref_PADDR));
			  assert (ref_PWRITE == $past(ref_PWRITE));
			  assert (ref_PWDATA == $past(ref_PWDATA));
			  assert (ref_PSELx == $past(ref_PSELx));
			  assert (ref_PENABLE == $past(ref_PENABLE));
			end
			if (uut_PSELx && uut_PENABLE && !PREADY) begin
			  // Signals must remain stable during wait states
			  assert (uut_PADDR == $past(uut_PADDR));
			  assert (uut_PWRITE == $past(uut_PWRITE));
			  assert (uut_PWDATA == $past(uut_PWDATA));
			  assert (uut_PSELx == $past(uut_PSELx));
			  assert (uut_PENABLE == $past(uut_PENABLE));
			end
	  
			// Compare outputs of reference and UUT
			assert (ref_PADDR == uut_PADDR);
			assert (ref_PWRITE == uut_PWRITE);
			assert (ref_PWDATA == uut_PWDATA);
			assert (ref_PSELx == uut_PSELx);
			assert (ref_PENABLE == uut_PENABLE);
			assert (ref_done == uut_done);
			assert (ref_rdata == uut_rdata);
		  end
		end
	  endmodule
