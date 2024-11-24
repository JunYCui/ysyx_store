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
// Last modified Date:     2024/11/24 14:30:53
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Cui Junyan
// Created date:           2024/11/24 14:30:53
// mail      :             1354315077@qq.com 
// Version:                V1.0
// TEXT NAME:              IFU.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/IFU.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module IFU(
    input              [  31: 0] pc                         ,
    input                        valid                      ,
    output reg         [  31: 0] inst                        
);



MEM MEM_inst(
    .valid                       (valid                     ),
    .raddr                       (pc                        ),
    .wdata                       (32'd0                     ),
    .funct3                      (3'b010                    ),
    .waddr                       (32'd0                     ),
    .wen                         (1'd0                      ),
    .rd_data                     (inst                      ) 
);
                                                                   
endmodule

