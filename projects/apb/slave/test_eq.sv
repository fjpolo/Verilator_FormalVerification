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
    input wire clk,
    input wire reset_n,
    
    output wire [31:0] ref_PADDR,
    output wire ref_PWRITE,
    output wire [31:0] ref_PWDATA,
    output wire ref_PSELx,
    output wire ref_PENABLE,
    input wire [31:0] ref_PRDATA, // Read data from slave
    output wire ref_PREADY,
    output wire uut_PREADY,

    output wire [31:0] uut_PADDR,
    output wire uut_PWRITE,
    output wire [31:0] uut_PWDATA,
    output wire uut_PSELx,
    output wire uut_PENABLE,
    input wire [31:0] uut_PRDATA, // Read data from slave
    output wire ref_PSLVERR,
    output wire uut_PSLVERR
 );

    apb_slave ref (
        .i_clk(clk),
        .i_reset_n(reset_n),
        .PADDR(ref_PADDR),
        .PWRITE(ref_PWRITE),
        .PWDATA(ref_PWDATA),
        .PSELx(ref_PSELx),
        .PENABLE(ref_PENABLE),
        .PRDATA(ref_PRDATA),
        .PREADY(ref_PREADY),
        .PSLVERR(ref_PSLVERR),
        .mutsel(1'b0)
    );

    apb_slave uut (
        .i_clk(clk),
        .i_reset_n(reset_n),
        .PREADY(uut_PREADY),
        .PSLVERR(uut_PSLVERR),
        .PADDR(uut_PADDR),
        .PWRITE(uut_PWRITE),
        .PWDATA(uut_PWDATA),
        .PSELx(uut_PSELx),
        .PENABLE(uut_PENABLE),
        .mutsel(1'b1)
    );
  //
    always @(posedge i_clk) begin
      if (!i_reset_n) begin
        // Reset state assertions (for outputs)
        assert (PRDATA == 32'h0);
        assert (PREADY == 1'b0);
        assert (PSLVERR == 1'b0);
      end else begin
        // Read transaction assertions
        if (PSELx && PENABLE && !PWRITE) begin
          if (PREADY) begin
            if (PADDR < MEMORY_LENGTH) begin
              assert (PRDATA == memory[PADDR[2:0]]);  // Correct data
              assert (PSLVERR == 1'b0); //No error
            end else begin
              assert (PSLVERR == 1'b1); // Address error
            end
          end
        end
    
        // Write transaction assertions
        if (PSELx && PENABLE && PWRITE) begin
          if (PREADY) begin
            if (PADDR < MEMORY_LENGTH) begin
              // No direct assertion here, as the write happens in the FSM.
              assert (PSLVERR == 1'b0); //No error
            end else begin
              assert (PSLVERR == 1'b1); // Address error
            end
          end
        end
    
        // PREADY should be asserted eventually
        if (PSELx && PENABLE) begin
          assert ($past(PSELx) && $past(PENABLE) && !PREADY || PREADY); // PREADY eventually
        end
    
        // PRDATA stability during wait states
        if (PSELx && PENABLE && !PREADY) begin
          assert (PRDATA == $past(PRDATA));
        end
    
        // PSLVERR deasserted when idle
        if (!PSELx) begin
          assert (ref_PSLVERR == uut_PSLVERR == 1'b0);
        end
      end
    end


endmodule
