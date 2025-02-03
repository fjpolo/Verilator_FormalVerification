// -----------------------------------------------------------------------------
// Module: APB_master
// Description: A formally verified APB master module
// 
// Author:       fjpolo
// Date:         27.01.2025
// Email:        fjpolo@gmail.com
// Github:       @fjpolo
//
// Based on: https://github.com/iammituraj/apb/blob/main/apb_master.sv
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

module apb_master #(
    // Configurable Parameters
    parameter MAX_LATENCY = 16
)
(
    input   wire    [0:0]   i_clk,      // APB clock
    input   wire    [0:0]   i_reset_n,  // APB reset (active low)
    input   wire    [31:0]  i_addr,     // Address for the transaction
    input   wire    [0:0]   i_start,    // Start signal to initiate a transaction
    input   wire    [0:0]   i_write,    // Write/read control (1 = write, 0 = read)
    input   wire    [31:0]  i_wdata,    // Write data (for write transactions)
    output  reg     [0:0]   o_done,     // Transaction completion signal
    output  reg     [31:0]  o_rdata,    // Read data (for read transactions)
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
    typedef enum logic [1:0] {
      IDLE,
      SETUP,
      ACCESS
    } state_t;
  
    state_t state;
  
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
    end
  
    // APB master FSM
    always @(posedge i_clk or negedge i_reset_n) begin
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
              state <= IDLE;
            end
            // Else, wait for PREADY (wait state)
          end
        endcase
      end
    end

    // ToDo: Modify for forbidden addresses
    assign PSLVERR = (i_addr == 'hCACA);


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
`ifdef	APB_MASTER
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

    // Property: All outputs should be in a known state after reset
    always @(posedge i_clk) begin
        if (!$past(i_reset_n))
            assert ((PADDR == 0)&&(PWDATA == 0)&&(PWRITE == 0)&&(PSELx == 0)&&(PENABLE == 0));
    end

    // Property: After reset, the master and slave should be ready to accept new transactions
    always @(posedge i_clk) begin
        if ($rose(i_reset_n))
          assert (!PSELx && !PENABLE);
    end

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
    //
    // These properties ensure the master and slave adhere to the fundamental APB protocol rules.
    //

    // a. Signal Stability During Transfer
    //  -  Property: During a transfer (PSELx is high), the address (PADDR) and control signals 
    //    (PWRITE, PENABLE) must remain stable.
    always @(posedge i_clk) begin
        if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n)&&($past(state == ACCESS)))
            if (PSELx) begin
                assert (PADDR   == $past(PADDR));
                assert (PSELx   == $past(PSELx));
                assert (PWRITE  == $past(PWRITE));
                assert (PENABLE == $past(PENABLE));
            end
    end
    // b. PENABLE Timing
    //  - Property: PENABLE must only be high in the second cycle of a transfer.
    always @(posedge i_clk) begin
        if($past(f_past_valid)&&(f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
            if ((PSELx)&&(!$past(PENABLE))&&($past(state == ACCESS)))
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
        if (($past(PSELx))&&(!$past(PWRITE))&&($past(PENABLE))&&($past(PREADY))&&($past(state) == ACCESS))
        assert (o_rdata == $past(PRDATA));
    end
    
    //
    // 3. Error Handling Properties
    // These properties ensure the master and slave handle error conditions correctly.
    //

    //
    // 4. Timing and Performance Properties
    // These properties ensure the master and slave meet timing requirements.
    //

    // ToDo: Add functionality and FV
    // // a. PREADY Assertion
    // //  - Property: The slave must assert PREADY within a specified number of 
    // //  cycles after PSELx is asserted.
    // always @(posedge PCLK) begin
    //     if (PSELx)
    //       assert (##[1:MAX_LATENCY] PREADY);
    // end
    
    // ToDo: Add functionality and FV
    // // b. Back-to-Back Transfers
    // //  - Property: The master and slave should handle back-to-back transfers without 
    // //  violating the protocol.
    // always @(posedge PCLK) begin
    //     if ((PSELx)&&(PENABLE))
    //       assert (##1 (PSELx)&&(!PENABLE) ##1 (PSELx)&&(PENABLE));
    // end


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
        cover ((PSELx)&&(PWRITE)&&(PENABLE));   // Write transaction
        cover ((PSELx)&&(!PWRITE)&&(PENABLE));  // Read transaction
    end
            
`endif // FORMAL

endmodule
