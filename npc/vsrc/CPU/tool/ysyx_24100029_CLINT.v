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
    input                                  reset                      ,
    input                                  clock                      ,

    input              [32-1: 0]           araddr                     ,
    input                                  arvalid                    ,
    output reg                             arready                    ,
    input              [   3: 0]           arid                       ,
    input              [   7: 0]           arlen                      ,
    input              [   2: 0]           arsize                     ,
    input              [   1: 0]           arburst                    ,

    input                                  rready                     ,
    output reg         [32-1: 0]           rdata                      ,
    output reg         [   1: 0]           rresp                      ,
    output reg                             rvalid                     ,
    output reg                             rlast                      ,
    output reg         [   3: 0]           rid                        ,

    input              [32-1: 0]           awaddr                     ,
    input                                  awvalid                    ,
    output                                 awready                    ,
    input              [   3: 0]           awid                       ,
    input              [   7: 0]           awlen                      ,
    input              [   2: 0]           awsize                     ,
    input              [   1: 0]           awburst                    ,

    input              [32-1: 0]           wdata                      ,
    input              [   3: 0]           wstrb                      ,
    input                                  wvalid                     ,
    output                                 wready                     ,
    input                                  wlast                      ,
    
    output             [   1: 0]           bresp                      ,
    output                                 bvalid                     ,
    input                                  bready                     ,
    output             [   3: 0]           bid                         
);
    reg                [  31: 0]        clk_count_low               ;
    reg                [  31: 0]        clk_count_high              ;

    initial begin
        $monitor("clk_count_low = %b \n",clk_count_low);
    end

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

    assign                              arready                     = 1;
    assign                              rresp                       = 0;
    assign                              rvalid                      = (arready & arvalid);
    assign                              rdata                       = (araddr == 32'h2000004)            ? 
                                                                    clk_count_high:(araddr == 32'h2000000)?
                                                                    clk_count_low:0;

endmodule


