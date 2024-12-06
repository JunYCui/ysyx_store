<<<<<<< HEAD

module ALU
#(
    parameter BW = 4
)
(
    input [BW-1:0] d1,
    input [BW-1:0] d2,
    input [2:0] choice,
    output reg [BW-1:0] res,
    output reg overflow,
    output reg compare
);
    reg choose_add_sub;
    wire add_of;
    wire[BW-1:0] result;
=======
`include "para.v"

module ALU
#(
    parameter                    BW                        = 2    
)
(
    input              [BW-1: 0] d1                         ,
    input              [BW-1: 0] d2                         ,
    input              [   3: 0] choice                     ,
    input                        comp_flag                  , 
    output reg         [BW-1: 0] res                        ,
    output reg                   overflow                    
);
    reg                          choose_add_sub             ;
    wire                         add_of                     ;
    wire               [BW-1: 0] result                     ;
>>>>>>> 3e8efcc

always@(*)
    begin
    case(choice)
<<<<<<< HEAD
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
=======
    `alu_add_ysyx_24100029: begin                                   //加法
            choose_add_sub = 1'b0;
            overflow = add_of;
            res =result;
            end
    `alu_sub_ysyx_24100029: begin                                   //减法
            choose_add_sub = 1'b1;
            overflow = add_of;
            res =result;
            end
    `alu_not_ysyx_24100029: begin                                   //取反
>>>>>>> 3e8efcc
        /* verilator lint_off WIDTHEXPAND */
            res = ~d1 + 1'b1;
        /* verilator lint_on WIDTHEXPAND */
            choose_add_sub = 1'b0;
            overflow = 1'b0;
<<<<<<< HEAD
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
            res = 0;
            overflow = 1'b0;
            end
    3'b111:begin 
            choose_add_sub = 1'b1;
            if(result[3:0] == 4'd0)
                compare = 1'b1;
            else 
                compare = 1'b0;
            res = 0;
            overflow = 1'b0;
            end
=======
            end
    `alu_and_ysyx_24100029: begin                                    //与
            res = d1 & d2;
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            end
    `alu_or_ysyx_24100029: begin                                   //或
            res = d1 | d2;
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            end
    `alu_xor_ysyx_24100029: begin                                   //异或
            res = d1 ^ d2;
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            end
    `alu_comparator_ysyx_24100029:begin                            // 比较大小
            if(comp_flag == 1'b0)begin
                choose_add_sub = 1'b1;
                if(d1[BW-1] != d2[BW-1])
                    begin
                        if(d1[BW-1] == 1'b1)
                            res = 1;
                        else
                            res = 0;
                    end
                else
                    begin
                        if(result[BW-1] == 1'b1)
                            res = 1;
                        else
                            res = 0;
                    end
                overflow = 1'b0;
            end
            else begin
                choose_add_sub = 1'b0;
                overflow = 1'b0;
                if(d1 < d2)
                    res = 1;
                else 
                    res = 0;
            end 

            end
    `alu_equal_ysyx_24100029:begin                                  //是否相等
            choose_add_sub = 1'b1;
            if(result != 0)
                res =  1;
            else
                res =  0;
            overflow = 1'b0;
            end
    `alu_sll_ysyx_24100029:begin                                    //逻辑左移
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            res = d1<<d2;
    end
    `alu_srl_ysyx_24100029:begin                                    //逻辑右移
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            res = {{{BW{1'b0}},d1}>>d2};
    end
    `alu_sra_ysyx_24100029:begin                                    //算术右移
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            res = {{{BW{d1[BW-1]}},d1}>>d2};
    end
    default:begin
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            res = 0;
    end
>>>>>>> 3e8efcc
    endcase
    
end

<<<<<<< HEAD
add 
#(
    .BW(BW)
)add_inst0
(
   .choose_add_sub(choose_add_sub),
   .add_1(d1),
   .add_2(d2),
   .result(result),
   .overflow(add_of)    
=======
add
#(
    .BW                          (BW                        ) 
)add_inst0
(
    .choose_add_sub              (choose_add_sub            ),
    .add_1                       (d1                        ),
    .add_2                       (d2                        ),
    .result                      (result                    ),
    .overflow                    (add_of                    ) 
>>>>>>> 3e8efcc
);


endmodule

