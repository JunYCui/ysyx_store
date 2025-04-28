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
    parameter                           Depth                      = 16    
)
(
    input                               clk                        ,
    input                               rst                        ,
    input              [DATA_WIDTH-1: 0]        inst                       ,
    input                               w_en  ,                      
    output                              r_en 
);
                                                                   
                                                                   
endmodule