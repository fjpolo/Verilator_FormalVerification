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

module apb_master(
    input   wire    [0:0]   i_clk,
    input   wire    [0:0]   i_reset_n,
    input   wire    [7:0]   i_addr,
    input   wire    [7:0]   i_data,
    input   wire    [0:0]   i_we,       // Write enable
    input   wire    [0:0]   i_new_data,
    output  wire    [0:0]   o_error,
    output  wire    [7:0]   o_data,


    // APB
    output  reg     [7:0]   o_paddr,
    output  reg     [0:0]   o_psel,
    output  reg     [0:0]   o_penable,
    output  reg     [0:0]   o_pwrite,
    output  reg     [7:0]   o_pwdata,
    input   wire    [0:0]   i_pready,
    input   wire    [0:0]   i_pslverr,
    input   wire    [7:0]   i_prdata
);
    localparam [1:0] idle = 0, setup = 1, enable = 2;

    reg [1:0] state, nstate;

    // reset decoder
    always@(posedge i_clk) begin
        if(i_reset_n == 1'b0)
            state <= idle;
        else
            state <= nstate;
        end
    // state decoder
    always@(*)begin
        case(state)
            idle:begin
                if (i_new_data)
                    nstate = idle;
                else
                    nstate = setup;
            end
            setup: begin
                    nstate = enable; 
                end
            enable: begin
                if(i_new_data ) begin
                        if(i_pready == 1'b1)
                            nstate = setup;
                        else
                            nstate = enable;
                    end
                else begin
                        nstate = idle;
                    end
                
                end
            default : nstate = idle; 
        endcase
        
    end

    //address decoding
    always@(posedge i_clk) begin
        if(!i_reset_n) begin
            o_psel <= 1'b0;
        end else if (nstate == idle) begin
            o_psel <= 1'b0;
        end else if ((nstate == enable)||(nstate == setup)) begin
            o_psel <= 1'b1;
        end  else begin
            o_psel <= 1'b0;
        end     
    end

    // error handling
    assign o_error = i_pslverr;

    // output logic
    always@(posedge i_clk) begin
        if(!i_reset_n) begin
            o_penable <= 1'b0;
            o_paddr   <= 8'h0;
            o_pwdata  <= 8'h00;
            o_pwrite  <= 1'b0;
        end else if (nstate == idle) begin
            o_penable <= 1'b0;
            o_paddr   <= 8'h0;
            o_pwdata  <= 8'h00;
            o_pwrite  <= 1'b0;
        end else if (nstate == setup) begin
            o_penable <= 1'b0;
            o_paddr   <= i_addr;
            o_pwrite  <= i_we;
            if(i_we == 1'b1)
            o_pwdata <= i_data;
        end else if (nstate == enable) begin
            o_penable <= 1'b1;
        end
    end

    assign o_data = ((o_psel)&&(o_penable)&& (!i_we)) ? i_prdata : 8'h00;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//
//  Formal properties
//
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
`ifdef	FORMAL
    `ifdef	APB_MASTER
        `define	ASSUME	assume
        `define	ASSERT	assert
    `else
        `define	ASSUME	assert
        `define	ASSERT	assume
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

        always @(posedge i_clk)
        if(!f_past_valid)
            assume($past(!i_reset_n));

    always @(posedge i_clk)
        if($past(!i_reset_n))
            assume(!f_past_valid);

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


`endif // FORMAL

endmodule
