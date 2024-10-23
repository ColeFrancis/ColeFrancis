`timescale 1ns / 1ps

module multiplier #(
    parameter N = 4
    )(
    input [N-1:0] a, b,
    output [2*N-1:0] p
    );
    
    wire [N-1:0] inA [N:0];
    wire [N-1:0] inB [N-1:0];
    
    assign inA[0] = 0;
    
    genvar i;
    generate
        for (i=0; i<N; i=i+1) begin
            assign inB[i] = a & {N{b[i]}}; // If a is 0, inB = 0, if a = 1, inB = b
            
            adder #(N) add_inst (inA[i], inB[i], {inA[i+1], p[i]});
        end
    endgenerate
    
    assign p[2*N-1:N] = inA[N];
    
endmodule

module adder #(
    parameter N = 8
    )(
    input [N-1:0] a, b,
    output [N:0] s
    );
    
    assign s = a + b;

endmodule

