`timescale 1ns / 1ps
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE     
// VSCODE plug-in version: Verilog-Hdl-Format-3.5.20250220
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            Please Write Company name
// All rights reserved     
// File name:              
// Last modified Date:     2025/04/21 15:12:45
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Please Write You Name 
// Created date:           2025/04/21 15:12:45
// mail      :             Please Write mail 
// Version:                V1.0
// TEXT NAME:              Inst_Buffer.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/CPU/util/Inst_Buffer.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module Inst_Buffer #(
    parameter                           DATA_WIDTH                 = 32    ,
    parameter                           ADDR_WIDTH                 = 32    ,
    parameter                           Depth                      = 16    
)
(
    input                               clk                        ,
    input                               rst                        ,
    input                               clr                        ,

    input              [DATA_WIDTH-1: 0]        inst1_i                    ,
    input              [DATA_WIDTH-1: 0]        inst2_i                    ,
    input              [DATA_WIDTH-1: 0]        inst3_i                    ,
    input              [ADDR_WIDTH-1: 0]        inst4_i                    ,
    input              [ADDR_WIDTH-1: 0]        pc1_i                      ,
    input              [ADDR_WIDTH-1: 0]        pc2_i                      ,
    input              [ADDR_WIDTH-1: 0]        pc3_i                      ,
    input              [ADDR_WIDTH-1: 0]        pc4_i                      ,
    input              [   3: 0]        inst_wen                   ,

    
    input              [   3: 0]        inst_ren                   ,
    output             [DATA_WIDTH-1: 0]        inst1_o                    ,
    output             [DATA_WIDTH-1: 0]        inst2_o                    ,
    output             [DATA_WIDTH-1: 0]        inst3_o                    ,
    output             [DATA_WIDTH-1: 0]        inst4_o                    ,

    output             [ADDR_WIDTH-1: 0]        pc1_o                      ,
    output             [ADDR_WIDTH-1: 0]        pc2_o                      ,
    output             [ADDR_WIDTH-1: 0]        pc3_o                      ,
    output             [ADDR_WIDTH-1: 0]        pc4_o                      ,


    output reg         [$clog2(Depth)-1: 0]        inst_count                  
);

    reg                [$clog2(Depth)-1: 0]        w_ptr                       ;
    reg                [$clog2(Depth)-1: 0]        r_ptr                       ;
    reg                [DATA_WIDTH-1: 0]        fifo[Depth-1:0]             ;
    reg                [ADDR_WIDTH-1: 0]        pc_fifo[Depth-1:0]          ;
   
   
    wire               [   2: 0]        count_input                 ;
    wire               [   2: 0]        count_output                ;

    always @(posedge clk)
        if(|inst_wen)begin
            fifo[w_ptr] <= (inst_wen[0])? inst1_i : fifo[w_ptr];
            fifo[w_ptr+1] <= (inst_wen[1])? inst2_i : fifo[w_ptr+1];
            fifo[w_ptr+2] <= (inst_wen[2])? inst3_i : fifo[w_ptr+2];
            fifo[w_ptr+3] <= (inst_wen[3])? inst4_i : fifo[w_ptr+3];
            pc_fifo[w_ptr] <=   (inst_wen[0])? pc1_i : pc_fifo[w_ptr];
            pc_fifo[w_ptr+1] <= (inst_wen[1])? pc2_i : pc_fifo[w_ptr+1];
            pc_fifo[w_ptr+2] <= (inst_wen[2])? pc3_i : pc_fifo[w_ptr+2];
            pc_fifo[w_ptr+3] <= (inst_wen[3])? pc4_i : pc_fifo[w_ptr+3];
        end

    always @(posedge clk) begin
        if(rst|clr)
            w_ptr <= 0;
        else if(|inst_wen)begin
            w_ptr <= w_ptr + count_input;
        end
    end

    always @(posedge clk) begin
        if(rst|clr)
            r_ptr <= 0;
        else if(|inst_ren)begin
            r_ptr <= r_ptr + count_output;
        end
    end

    always @(posedge clk) begin
        if(rst|clr)
            inst_count <= 0;
        else if(|inst_wen || |inst_ren)
            inst_count <= inst_count + count_input - count_output;
    end



    assign                              inst1_o                     = fifo[r_ptr];
    assign                              inst2_o                     = fifo[r_ptr+1];
    assign                              inst3_o                     = fifo[r_ptr+2];
    assign                              inst4_o                     = fifo[r_ptr+3];
    
    assign                              pc1_o                     = pc_fifo[r_ptr];
    assign                              pc2_o                     = pc_fifo[r_ptr+1];
    assign                              pc3_o                     = pc_fifo[r_ptr+2];
    assign                              pc4_o                     = pc_fifo[r_ptr+3];



count_ones u_count_ones(
    .data_in                            (inst_wen                  ),
    .count_out                          (count_input               ) 
);



count_ones u1_count_ones(
    .data_in                            (inst_ren                  ),
    .count_out                          (count_output              ) 
);



endmodule

