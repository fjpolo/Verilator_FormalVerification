// Avoid misspelled identifiers becoming wires
`default_nettype none

module serialtester ( 
                    uart_rx , uart_tx 
                );

    input wire uart_rx ;
    output wire uart_tx ;
    assign uart_tx = uart_rx ;
endmodule