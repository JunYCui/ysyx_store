module mux4_1(a,b,c,d,s0,s1,led);

input [1:0] a,b,c,d; 
input s0,s1;

output [1:0]led;

assign led = (~s0&~s1&a)|(s0&~s1&b)|(~s0&s1&c)|(s0&s1&d);


endmodule
