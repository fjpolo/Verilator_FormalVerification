// -----------------------------------------------------------------------------
// Module: APB_master
// Description: A formally verified APB master module
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

`timescale 1ns/1ps

module apb_master(
    input   wire    [0:0]   i_clk,      // APB clock
    input   wire    [0:0]   i_reset_n,  // APB reset (active low)
    input   wire    [31:0]  i_addr,     // Address for the transaction
    input   wire    [0:0]   i_start,    // Start signal to initiate a transaction
    input   wire    [0:0]   i_write,    // Write/read control (1 = write, 0 = read)
    input   wire    [31:0]  i_wdata,    // Write data (for write transactions)
    output  reg     [0:0]   o_done,     // Transaction completion signal
    output  reg     [31:0]  o_rdata,    // Read data (for read transactions)
    output  reg     [0:0]   o_slverr,   // Slave error
    output  reg     [31:0]  PADDR,      // APB address
    output  reg     [0:0]   PWRITE,     // APB write/read control (1 = write, 0 = read)
    output  reg     [31:0]  PWDATA,     // APB write data
    output  reg     [0:0]   PSELx,      // APB slave select
    output  reg     [0:0]   PENABLE,    // APB enable
    input   wire    [31:0]  PRDATA,     // APB read data
    input   wire    [0:0]   PREADY,     // APB ready signal from slave
    input   wire    [0:0]   PSLVERR     // APB slave error signal
  );
  

    // State encoding
    localparam IDLE = 0;
    localparam SETUP = 1;
    localparam ACCESS = 2;
    
    reg [1:0] state;
  
    // Initialize state and outputs
    initial begin
      state = IDLE;
      PADDR = 32'h0;
      PWRITE = 1'b0;
      PWDATA = 32'h0;
      PSELx = 1'b0;
      PENABLE = 1'b0;
      o_done = 1'b0;
      o_rdata = 32'h0;
      o_slverr = 1'b0;
    end
  
    // APB master FSM
    always @(posedge i_clk) begin
      if (!i_reset_n) begin
        // Reset state
        state <= IDLE;
        PADDR <= 32'h0;
        PWRITE <= 1'b0;
        PWDATA <= 32'h0;
        PSELx <= 1'b0;
        PENABLE <= 1'b0;
        o_done <= 1'b0;
        o_rdata <= 32'h0;
        o_slverr <= 1'b0;
      end else begin
        case (state)
          IDLE: begin
            // Wait for start signal
            if (i_start) begin
              PADDR <= i_addr;
              PWRITE <= i_write;
              PWDATA <= i_wdata;
              PSELx <= 1'b1;
              PENABLE <= 1'b0;
              state <= SETUP;
            end
          end
  
          SETUP: begin
            // Assert PENABLE in the next cycle
            PENABLE <= 1'b1;
            state <= ACCESS;
          end
  
          ACCESS: begin
            if (PREADY) begin
              // Transaction complete
              PSELx <= 1'b0;
              PENABLE <= 1'b0;
              o_done <= 1'b1;
              o_rdata <= PRDATA; // Capture read data
              o_slverr <= PSLVERR;
              state <= IDLE;
            end
            // Else, wait for PREADY (wait state)
          end

          default: ;
        endcase
      end
    end
endmodule
