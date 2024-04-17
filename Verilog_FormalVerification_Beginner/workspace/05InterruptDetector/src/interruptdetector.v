// Avoid misspelled identifiers becoming wires
`default_nettype none

module interruptdetector ( 
                    input wire [7:0] i_irq_source,
                    output wire o_irq
                );
    assign o_irq = |i_irq_source ;
endmodule