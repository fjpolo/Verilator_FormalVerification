// Avoid misspelled identifiers becoming wires
`default_nettype none

module dimmer( 
                input wire i_clk, 
                output wire o_led 
             );
    parameter WIDTH = 27;

    reg [WIDTH:0]counter;

    always @(posedge i_clk) begin
        counter <= counter + 1;        
    end

    assign o_led = (counter[7:0] < counter[WIDTH:WIDTH-7]);
endmodule