`timescale 1ns / 1ps
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE     
// VSCODE plug-in version: Verilog-Hdl-Format-3.5.20250220
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            IMECAS
// All rights reserved     
// File name:              
// Last modified Date:     2025/03/01 14:47:29
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Cui Junyan
// Created date:           2025/03/01 14:47:29
// mail      :             1354315077@qq.com 
// Version:                V1.0
// TEXT NAME:              sram.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/SRAM/sram.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//
/* function test */
import "DPI-C" function int npc_pmem_read(int addr);
import "DPI-C" function void npc_pmem_write(int addr, int wdata,byte wmask);

module sram(
    input                                  clock                      ,
    input                                  reset                      ,

    output                                 logic                             awready,
    input                                  logic                             awvalid,
    input                                  logic         [  31: 0]           awaddr,
    input                                  logic         [   3: 0]           awid,
    input                                  logic         [   7: 0]           awlen,
    input                                  logic         [   2: 0]           awsize,
    input                                  logic         [   1: 0]           awburst,

    output                                 logic                             wready,
    input                                  logic                             wvalid,
    input                                  logic         [  31: 0]           wdata,
    input                                  logic         [   3: 0]           wstrb,
    input                                  logic                             wlast,

    input                                  logic                            bready,
    output                                 logic                            bvalid,
    output                                 logic        [   1: 0]           bresp,
    output                                 logic        [   3: 0]           bid,
    
    output                                 logic                            arready,
    input                                  logic                            arvalid,
    input                                  logic        [  31: 0]           araddr,
    input                                  logic        [   3: 0]           arid,
    input                                  logic        [   7: 0]           arlen,
    input                                  logic        [   2: 0]           arsize,
    input                                  logic        [   1: 0]           arburst,
    
    input                                  logic                            rready,
    output                                 logic                            rvalid,
    output                                 logic        [   1: 0]           rresp,
    output                                 logic        [  31: 0]           rdata,
    output                                 logic                            rlast,
    output                                 logic        [   3: 0]           rid 

);
    localparam                          idle                       = 2'b00 ;
    localparam                          write                      = 2'b01 ;
    localparam                          addr                       = 2'b10 ;

    reg                [   1: 0]        state                       ;
    wire               [   7: 0]        wmask                       ;
    assign                              arready                     = (state == idle);
    assign                              awready                     = (state == idle);
    assign                              wready                      = (state == idle);
    assign                              wmask                       = {4'b0,awsize,1'b0};
    assign                              bresp                       = 0;
    assign                              bid                         = 0;
    assign                              rid                         = 0;
    assign                              rresp                       = 0;

    always @(posedge clock or posedge reset) begin
        if(reset)
            state <= idle;
        else begin
            case(state)
            idle:begin
                if(arready & arvalid)
                    state <= addr;
                else if(awready & awvalid & wready & wvalid)
                    state <= write;
                else
                    state <= idle;
            end
            addr: state <= idle;
            write: state <= idle;
            default:state <= idle;
            endcase
        end
    end

    always @(posedge clock or posedge reset) begin
        if(reset)begin
            rlast <= 1'b0;
            rvalid <= 1'b0;
            rdata <= 0;
        end
        if(state == idle & arready & arvalid)begin
            rlast <= 1'b1;
            rvalid <= 1'b1;
            rdata <= npc_pmem_read(araddr);
        end
        else begin
            rlast <= 1'b0;
            rvalid <= 1'b0;
            rdata <= 0;
        end
    end
    always @(posedge clock or posedge reset) begin
        if(reset)begin
            bvalid <= 0;
        end
        else if(state == idle & awready & awvalid & wready & wvalid)begin
            bvalid <= 1'b1;
            npc_pmem_write(awaddr,wdata,wmask);
        end
        else
            bvalid <= 1'b0;
    end




                                                                   
endmodule
