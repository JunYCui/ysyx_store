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
// Last modified Date:     2025/05/01 15:39:51
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Please Write You Name 
// Created date:           2025/05/01 15:39:51
// mail      :             Please Write mail 
// Version:                V1.0
// TEXT NAME:              count_ones.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/CPU/util/count_ones.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module count_ones(
    input              [   3: 0]        data_in                    ,
    output             [   2: 0]        count_out                   
);


    wire               [   1: 0]        low_bits                    ;
    wire               [   1: 0]        high_bits                   ;
    wire               [   1: 0]        count_low                   ;
    wire               [   1: 0]        count_high                  ;
// 分步计算低2位和高2位的1的个数，再相加
    assign                              low_bits                    = data_in[1:0];
    assign                              high_bits                   = data_in[3:2];
    assign                              count_low                   = low_bits[1] + low_bits[0];
    assign                              count_high                  = high_bits[1] + high_bits[0];
    assign                              count_out                   = count_high + count_low;

endmodule
