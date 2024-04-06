module seg7(num,seg_out);

input [2:0]num;
output reg [7:0]seg_out;
/* verilator lint_off WIDTHEXPAND */
always @(*) begin
    case (num)
    4'd0:seg_out = 8'b00000011;
    4'd1:seg_out = 8'b10011111;
    4'd2:seg_out = 8'b00100101;
    4'd3:seg_out = 8'b00001101;
    4'd4:seg_out = 8'b10011001;
    4'd5:seg_out = 8'b01001001;
    4'd6:seg_out = 8'b01000001;
    4'd7:seg_out = 8'b00011111;
    4'd8:seg_out = 8'b00000001;
    4'd9:seg_out = 8'b00001001;
    default: seg_out = 8'b00000000;
    endcase
end
/* verilator lint_on WIDTHEXPAND */



endmodule
