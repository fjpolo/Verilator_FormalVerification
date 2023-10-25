// Avoid misspelled identifiers becoming wires
`default_nettype none

module paritycheck ( 
                    input wire [7:0] i_word ,
                    output wire o_parity
                );
    assign o_parity = ^i_word;
endmodule