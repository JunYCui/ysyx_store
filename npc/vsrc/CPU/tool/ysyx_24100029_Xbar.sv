`timescale 1ns / 1ps
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE      
// VSCODE plug-in version: Verilog-Hdl-Format-3.3.20250120
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            IMECAS
// All rights reserved     
// File name:              
// Last modified Date:     2025/01/24 15:21:55
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Cui Junyan
// Created date:           2025/01/24 15:21:55
// mail      :             1354315077@qq.com 
// Version:                V1.0
// TEXT NAME:              ysyx_24100029_Xbar.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/CPU/tool/ysyx_24100029_Xbar.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module ysyx_24100029_Xbar (
    input  logic [31:0] cpu_addr,
    input  logic [ 1:0] cpu_opcode,
    input  logic [31:0] cpu_wdata,
    input  logic [ 3:0] cpu_wstrb,
    input  logic [ 2:0] cpu_size,
    output logic [31:0] cpu_rdata,
    output logic        cpu_resp,


    output logic [ 2:0] clint_size,
    output logic [31:0] clint_addr,
    output logic [ 1:0] clint_opcode,
    output logic [31:0] clint_wdata,
    output logic [ 3:0] clint_wstrb,
    input  logic [31:0] clint_rdata,
    input  logic        clint_resp,

    output logic [ 2:0] mem_size,
    output logic [31:0] mem_addr,
    output logic [ 1:0] mem_opcode,
    output logic [31:0] mem_wdata,
    output logic [ 3:0] mem_wstrb,
    input  logic [31:0] mem_rdata,
    input  logic        mem_resp

);

  always @(*) begin
    if (cpu_addr[31:24] == 8'h02) begin
      clint_size   = cpu_size;
      clint_addr   = cpu_addr;
      clint_opcode = cpu_opcode;
      clint_wdata  = cpu_wdata;
      clint_wstrb  = cpu_wstrb;
      cpu_rdata    = clint_rdata;
      cpu_resp     = clint_resp;
      mem_size     = 0;
      mem_addr     = 0;
      mem_opcode   = 0;
      mem_wdata    = 0;
      mem_wstrb    = 0;
    end else begin

      clint_size   = 0;
      clint_addr   = 0;
      clint_opcode = 0;
      clint_wdata  = 0;
      clint_wstrb  = 0;
      cpu_rdata    = mem_rdata;
      cpu_resp     = mem_resp;
      mem_size     = cpu_size;
      mem_addr     = cpu_addr;
      mem_opcode   = cpu_opcode;
      mem_wdata    = cpu_wdata;
      mem_wstrb    = cpu_wstrb;
    end
  end



endmodule
