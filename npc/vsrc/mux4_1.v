module mux4_1
(
    input [1:0]din0,
    input [1:0]din1,
    input [1:0]din2,
    input [1:0]din3,
    input [1:0]s0,

    output reg [1:0]out
);
    always@(*)
    begin
        case(s0)
        2'b00:out = din0; 
        2'b01:out = din1;
        2'b10:out = din2;
        2'b11:out = din3;
        endcase 
    end




endmodule
