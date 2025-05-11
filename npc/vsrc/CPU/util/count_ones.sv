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

module count_ones #(
    DATA_WIDTH = 8
) (
    input  [          DATA_WIDTH-1:0] data_in,
    output [$clog2(DATA_WIDTH+1)-1:0] count_out
);


  generate
    if (DATA_WIDTH == 1) begin : COUNT
      // 基本情况：1位输入
      assign count_out = data_in;
    end else begin : recursive
      // 递归情况：分成两部分
      wire [$clog2(DATA_WIDTH/2+1)-1:0] count_low;
      wire [$clog2(DATA_WIDTH-DATA_WIDTH/2+1)-1:0] count_high;

      count_ones #(
          .DATA_WIDTH(DATA_WIDTH / 2)
      ) low (
          .data_in  (data_in[DATA_WIDTH/2-1:0]),
          .count_out(count_low)
      );

      count_ones #(
          .DATA_WIDTH(DATA_WIDTH - DATA_WIDTH / 2)
      ) high (
          .data_in  (data_in[DATA_WIDTH-1:DATA_WIDTH/2]),
          .count_out(count_high)
      );

      assign count_out = count_low + count_high;
    end
  endgenerate



endmodule
