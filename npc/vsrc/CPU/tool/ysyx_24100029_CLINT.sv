`timescale 1ns / 1ps
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE     
// VSCODE plug-in version: Verilog-Hdl-Format-2.8.20240817
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            Please Write Company name
// All rights reserved     
// File name:              
// Last modified Date:     2024/11/24 10:25:51
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Please Write You Name 
// Created date:           2024/11/24 10:25:51
// mail      :             Please Write mail 
// Version:                V1.0
// TEXT NAME:              MEM.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/MEM.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//

/* verilator lint_off UNUSEDSIGNAL */
/* verilator lint_off UNDRIVEN */
module ysyx_24100029_CLINT
(
    input                               reset                      ,
    input                               clock                      ,

    input    logic          [  31: 0]        addr                   ,
    input    logic          [   1: 0]        opcode                 ,
    input    logic          [  31: 0]        wdata                  ,
    input    logic          [   3: 0]        wstrb                  ,
    output   logic          [  31: 0]        rdata                  ,
    output   logic                           resp                                         
);
    reg                [  31: 0]        clk_count_low               ;
    reg                [  31: 0]        clk_count_high              ;



    always @(posedge clock) begin
        if(reset)
            clk_count_low <= 0;
        else if(clk_count_low == ~32'h0)
            clk_count_low <= 0;
        else
            clk_count_low <= clk_count_low + 1;
    end
    always @(posedge clock) begin
        if(reset)
            clk_count_high <= 0;
        else if(clk_count_low == ~32'h0)
            clk_count_high <= clk_count_high + 1;
        else
            clk_count_high <= clk_count_high;
    end

    always @(posedge clock) begin
        if(reset)
            resp <= 0;
        else if(opcode == 2'd1)
            resp <= 1;
    end


    assign                              rdata                       = (addr[3:0] == 4'h4)            ? 
                                                                    clk_count_high:(addr[3:0] == 4'h0)?
                                                                    clk_count_low:0;




endmodule


