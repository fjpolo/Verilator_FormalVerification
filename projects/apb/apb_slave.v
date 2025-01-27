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

module apb_slave(
    input  wire i_clk,
    input  wire i_reset_n,
    input  wire i_paddr,
    input  wire i_psel,
    input  wire i_penable,
    input  wire i_pwrite,
    input  wire i_pwdata,
    output wire o_pready,
    output wire o_pslverr,
    output wire o_prdata
);


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//
//  Formal properties
//
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

`ifdef	FORMAL
`ifdef	APB_SLAVE
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
	initial	f_past_valid_gbl = 0;
	always @($posedge i_clk)
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