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
    parameter DW = 32 ,                     // Data width
    parameter AW = 8  ,                     // Address width; max. 32 as per APB spec
 
    // Derived Parameters
    localparam SW = 4,                      //  int'($ceil(DW/8)),      // Strobe width
    localparam CW = 1 + SW + DW + AW ,      // Command width  {pwrite, pstrb, pwdata, paddr}  
    localparam RW = 1 + DW                  // Response width {pslverr, prdata}
 )
 (
    input   logic    [0:0]       i_clk,
    input   logic    [0:0]       i_reset_n,
   
    // Command & Response Interface
   input    logic   [CW-1:0]    i_cmd,      // Command
   input    logic   [0:0]       i_valid,    // Valid
   output   logic   [RW-1:0]    o_resp,     // Response
   output   logic   [0:0]       o_ready,    // Ready


    // APB Interface
   output   logic   [AW-1:0]    o_paddr,    // Address 
   output   logic   [0:0]       o_pwrite,   // Write enable
   output   logic   [0:0]       o_psel,     // Select
   output   logic   [0:0]       o_penable,  // Enable
   output   logic   [DW-1:0]    o_pwdata,   // Write data
   output   logic   [SW-1:0]    o_pstrb,    // Write strobe
   input    logic   [DW-1:0]    i_prdata,   // Read data
   input    logic   [0:0]       i_pslverr,  // Slave error
   input    logic   [0:0]       i_pready    // Ready
);
// States
typedef enum logic [1:0]
{
   IDLE   = 2'b00 ,   
   ACCESS = 2'b10
}  state_t ;
// State register, next state 
state_t state_ff, nxt_state ;

// Command timing
// ==============
// 1. Command valid can be asserted anytime.
// 2. Once asserted, command valid should remain asserted until ready is asserted
// 3. Command should be stable while valid is high and should not change value until ready is asserted
//
// i_clk   __/``\__/``\__/``\__/``\__/``\__/``\__/``\
// i_cmd  ______xx______/```C0`````\/```C1`````\__xx
//                      \__________/\__________/
// i_valid______________/```````````````````````\___
// o_ready____________________/`````\_____/`````\___
// o_resp ______xx________________________/``R1`\_xx

// FSM
always_ff @(posedge i_clk) begin
   if (!i_reset_n) begin
      state_ff <= IDLE ;
   end
   else begin
      state_ff <= nxt_state ;
   end
end
always_comb begin
   case (state_ff)
      IDLE    : nxt_state = state_t'((i_valid)? ACCESS : IDLE)   ;
      ACCESS  : nxt_state = state_t'((!i_pready)? ACCESS : IDLE) ;
      default : nxt_state = state_ff ;
   endcase
end

// APB Interface outputs
assign o_paddr   = i_cmd[0+:AW] ;
assign o_psel    = (state_ff == IDLE && i_valid);
assign o_penable = (state_ff == ACCESS);

// Outputs to Command Interface
assign o_resp  = {i_pslverr, i_prdata} ;
assign o_ready = o_penable & i_pready ;

always @(posedge i_clk)
    if(!i_reset_n)
        o_pwrite  <= 1'b0;
    else if(state_ff == IDLE)
        o_pwrite  <= i_cmd[CW-1];
        
always @(posedge i_clk)
    if(!i_reset_n)
        o_pwdata  <= 'h00;
    else if(state_ff == IDLE)
        o_pwdata  <= i_cmd[AW+:DW];

always @(posedge i_clk)
    if(!i_reset_n)
        o_pstrb  <= 'h00;
    else if(state_ff == IDLE)
        o_pstrb  <= i_cmd[(CW-2)-:SW];



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
    always @(posedge i_clk)
        if(!f_past_valid)
            assume($past(!i_reset_n));

    always @(posedge i_clk)
        if($past(!i_reset_n))
            assume(!f_past_valid);

    // One clock after reset, state must be idle
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(!i_reset_n)))
            assert(state_ff == IDLE); 
    end
    // One clock after reset, o_psel must be low
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(!i_reset_n)))
            assert(o_psel == 'h0); 
    end
    // One clock after reset, o_penable must be low
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(!i_reset_n)))
            assert(o_penable == 'h0); 
    end
    // One clock after reset, o_paddr must be low
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(!i_reset_n)))
            assert(o_paddr == 'h00); 
    end
    // One clock after reset, o_pwdata must be low
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(!i_reset_n)))
            assert(o_pwdata == 'h00);  
    end
    // One clock after reset, o_pwrite must be low
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(!i_reset_n)))
            assert(o_pwrite == 'h0); 
    end

    ////////////////////////////////////////////////////
	//
	// BMC
	//
	////////////////////////////////////////////////////

    // If i_cmd[CW-1] == 1, o_pwrite should be high 
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(i_reset_n))&&($past(state_ff) == IDLE))
            assert(o_pwrite == ($past(i_cmd[CW-1]) == 1'b1)); 
    end

    ////////////////////////////////////////////////////
	//
	// Contract
	//
	////////////////////////////////////////////////////   
    
    // o_penable is high only on ACCESS state 
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
            assert(o_penable == (state_ff == ACCESS)); 
    end 
    // Data response: If i_pready -> o_resp  = {i_pslverr, i_prdata}
    always @(posedge i_clk) begin
        if((f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
            if(i_pready)
                assert(o_resp == {i_pslverr, i_prdata}); 
    end 
    // Master should wait for slave when writing
    // The following signals remain unchanged while PREADY remains LOW:
    //      • Address signal, PADDR
    //      • Direction signal, PWRITE
    //      • Select signal, PSELx
    //      • Enable signal, PENABLE
    //      • Write data signal, PWDATA
    //      • Write strobe signal, PSTRB
    always @(posedge i_clk)
        if((f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
            if((!$past(i_pready))&&(!i_pready)&&($past(state_ff) == ACCESS)) begin
                `ASSUME($stable(o_paddr));  // 🆗
                assert($stable(o_pwrite));  // 🆗
                assert($stable(o_psel));    // 🆗
                assert($stable(o_penable)); // 🆗
                assert($stable(o_pwdata));  // 🆗
                assert($stable(o_pstrb));   // 🆗
            end
    // Master should wait for slave when reading
    // The following signals remain unchanged while PREADY remains LOW:
    //        • Address signal, PADDR
    //        • Direction signal, PWRITE
    //        • Select signal, PSEL
    //        • Enable signal, PENABLE
    always @(posedge i_clk)
        if((f_past_valid)&&($past(i_reset_n))&&(i_reset_n))
            if((!$past(i_pready))&&(!i_pready)&&($past(state_ff) == ACCESS)) begin
                `ASSUME($stable(o_paddr));  // 🆗
                assert($stable(o_pwrite));  // 🆗
                assert($stable(o_psel));    // 🆗
                assert($stable(o_penable)); // 🆗
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

`endif // FORMAL

endmodule
