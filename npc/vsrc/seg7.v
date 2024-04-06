module seg7(num,seg_out);

input [2:0]num;
output [6:0]seg_out;

always @(*) begin
    case (num)
    4'd0:seg_out = 7'h3f;
    4'd1:seg_out = 7'h06;
    4'd2:seg_out = 7'h5b;
    4'd3:seg_out = 7'h4f;
    4'd4:seg_out = 7'h66;
    4'd5:seg_out = 7'h6d;
    4'd6:seg_out = 7'h7d;
    4'd7:seg_out = 7'h07;
    4'd8:seg_out = 7'h7f;
    4'd9:seg_out = 7'h6f;
    default: 
    endcase
end




endmodule