module mux4_1(a,b,c,d,s,led);

input [1:0]a,b,c,d; 
input [1:0]s;

output [1:0]led;

MuxKey #(4,2,2) inst(
    led,
    s,
    {
    2'b00, a,
    2'b01, b,
    2'b10, c,
    2,b11, d
    }
);


endmodule
