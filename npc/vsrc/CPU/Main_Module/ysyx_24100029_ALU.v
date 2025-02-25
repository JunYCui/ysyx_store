`include "../define/para.v"
//`include "/home/cjy/ysyx-workbench/npc/vsrc/CPU/define/para.v"
`timescale 1ns / 1ps
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE      
// VSCODE plug-in version: Verilog-Hdl-Format-2.8.20240817
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            IMECAS
// All rights reserved     
// File name:              
// Last modified Date:     2025/01/20 23:28:53
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Cui Junyan
// Created date:           2025/01/20 23:28:53
// mail      :             1354315077@qq.com
// Version:                V1.0
// TEXT NAME:              ysyx_24100029_ALU.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/CPU/Main_Module/ysyx_24100029_ALU.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//
module ysyx_24100029_ALU
#(
    parameter                    BW                        = 32    
)
(
    input              [BW-1: 0] d1                         ,
    input              [BW-1: 0] d2                         ,
    input              [   3: 0] choice                     , 
    output reg         [BW-1: 0] res                        ,
    output reg                   overflow                    
);
    reg                          choose_add_sub             ;
    wire                         add_of                     ;
    wire               [BW-1: 0] result                     ;

always@(*)
    begin
    case(choice)
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
        /* verilator lint_off WIDTHEXPAND */
            res = ~d1 + 1'b1;
        /* verilator lint_on WIDTHEXPAND */
            choose_add_sub = 1'b0;
            overflow = 1'b0;
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
    `alu_signed_comparator_ysyx_24100029:begin                            // 比较大小
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
    `alu_unsigned_comparator_ysyx_24100029:begin
                choose_add_sub = 1'b0;
                overflow = 1'b0;
                if(d1 < d2)
                    res = 1;
                else 
                    res = 0;
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
            res = d1<<d2[4:0];
    end
    `alu_srl_ysyx_24100029:begin                                    //逻辑右移
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            res = {{{BW{1'b0}},d1}>>d2[4:0]}[31:0];
    end
    `alu_sra_ysyx_24100029:begin                                    //算术右移
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            res = {{{BW{d1[BW-1]}},d1}>>d2[4:0]}[31:0];
    end
    default:begin
            overflow = 1'b0;
            choose_add_sub = 1'b0;
            res = 0;
    end
    endcase
    
end

ysyx_24100029_add
#(
    .BW                          (BW                        ) 
)add_inst0
(
    .choose_add_sub              (choose_add_sub            ),
    .add_1                       (d1                        ),
    .add_2                       (d2                        ),
    .result                      (result                    ),
    .overflow                    (add_of                    ) 
);


endmodule

