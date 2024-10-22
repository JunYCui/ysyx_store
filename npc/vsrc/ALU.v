module ALU(
    input [3:0] d1,
    input [3:0] d2,
    input [2:0] choice,
    output reg [3:0] res,
    output reg overflow,
    output reg compare
);
    reg choose_add_sub;
    wire add_of;
    wire[3:0] result;

always@(*)
    begin
    case(choice)
    3'b000: begin  //加法
            choose_add_sub = 1'b0;
            overflow = add_of;
            compare  = 1'b0;
            res =result;
            end
    3'b001: begin //减法
            choose_add_sub = 1'b1;
            overflow = add_of;
            compare  = 1'b0;
            res =result;
            end
    3'b010: begin //取反
        /* verilator lint_off WIDTHEXPAND */
            res = ~d1;
        /* verilator lint_on WIDTHEXPAND */
            choose_add_sub = 1'b0;
            overflow = 1'b0;
            compare  = 1'b0;    
            end
    3'b011: begin //与
            res = d1 & d2;
            overflow = 1'b0;
            compare  = 1'b0; 
            choose_add_sub = 1'b0;
            end
    3'b100: begin //或
            res = d1 | d2;
            overflow = 1'b0;
            compare  = 1'b0;    
            choose_add_sub = 1'b0;      
            end
    3'b101: begin //异或
            res = d1 ^ d2;
            overflow = 1'b0;
            compare  = 1'b0;  
            choose_add_sub = 1'b0;               
            end
    3'b110:begin // 比较大小
            choose_add_sub = 1'b1;
            if(d1[3] != d2[3])
                begin
                    if(d1[3] == 1'b1)
                        compare = 1'b1;
                    else 
                        compare = 1'b0;
                end
            else 
                begin
                    if(result[3] == 1'b1)
                        compare = 1'b1;
                    else 
                        compare = 1'b1;
                end
            res = 4'b0;
            overflow = 1'b0;
            end
    3'b111:begin 
            choose_add_sub = 1'b1;
            if(result[3:0] == 4'd0)
                compare = 1'b1;
            else 
                compare = 1'b0;
            res = 4'b0;
            overflow = 1'b0;
            end
    endcase
    
end

add 
#(
    .BW(4'd4)
)add_inst0
(
   .choose_add_sub(choose_add_sub),
   .add_1(d1),
   .add_2(d2),
   .result(result),
   .overflow(add_of)    
);


endmodule

