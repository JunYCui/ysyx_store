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
// Last modified Date:     2025/05/02 15:03:21
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Please Write You Name 
// Created date:           2025/05/02 15:03:21
// mail      :             Please Write mail 
// Version:                V1.0
// TEXT NAME:              npc_generate.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/CPU/util/npc_generate.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module npc_generate #(
    parameter                           ResetValue                 = 32'h8000_0000,
    parameter                           Issue_Num                  = 4     
)
(
    input                               clock                      ,
    input                               reset                      ,
    input              [  31: 0]        dnpc                       ,
    input                               dnpc_valid                 ,

    input               pc_update,
    output reg         [  31: 0]        pc                          

);

    wire               [  31: 0]        snpc                        ;

    always @(posedge clock) begin
        if(reset)
            pc <= ResetValue;
        else if(dnpc_valid)
            pc <= dnpc;
        else if(pc_update)
            pc <= snpc;
    end

    // snpc = pc 对于 Issue_Num 的向上取余
    assign                              snpc                        = (pc[$clog2(4*Issue_Num)-1:0] == 0)? pc + 4*Issue_Num : {{pc[31:$clog2(4*Issue_Num)]+1'd1},{4*Issue_Num{1'b0}}};


endmodule

