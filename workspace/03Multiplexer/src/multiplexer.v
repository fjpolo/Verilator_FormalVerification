// Avoid misspelled identifiers becoming wires
`default_nettype none

module multiplexer ( 
                    input wire i_a, i_b, i_sel, 
                    output wire o_out
                );
    assign o_out = (i_sel) ? i_a : i_b;
endmodule