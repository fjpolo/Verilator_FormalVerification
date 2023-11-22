// Avoid misspelled identifiers becoming wires
`default_nettype none

module onehzblinky( 
                input wire i_clk, 
                output wire o_led 
             );
    parameter WIDTH = 27;
    parameter CLOCK_RATE_HZ = 100_000_000;
    parameter [31:0] INCREMENT = (1<<30)/(CLOCK_RATE_HZ/4);

    reg [31:0]counter;
    
    initial counter = 0;

    always @(posedge i_clk) begin
        counter <= counter + INCREMENT;        
    end

    assign o_led = &counter[31];
endmodule