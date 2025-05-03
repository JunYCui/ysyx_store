`timescale 1ns / 1ps
`include "../define/para.v"
`include "../define/interface.sv"
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
module ysyx_24100029_IFU #(
    parameter ResetValue = 32'h30000000,
    parameter Issue_Num  = 4,
    parameter ADDR_WIDTH = 32
) (
    input        clock,
    input        reset,
    input [31:0] dnpc,
    input        dnpc_valid,
    input        icache_clr,
    input        clr,

    output [          31:0] inst1_o,
    output [          31:0] inst2_o,
    output [          31:0] inst3_o,
    output [          31:0] inst4_o,
    output [ADDR_WIDTH-1:0] pc1_o,
    output [ADDR_WIDTH-1:0] pc2_o,
    output [ADDR_WIDTH-1:0] pc3_o,
    output [ADDR_WIDTH-1:0] pc4_o,
    output [           3:0] valid,
    input  [           3:0] ready,


    axi4_if.master ifu_axi,


`ifdef Performance_Count
    output [31:0] fetch_inst,
    output [31:0] flash_hit,
    flash_miss,
    sdram_hit,
    sdram_miss,
`endif
    output        req
);

  localparam FETCH_NUM = Issue_Num * 2;

  logic [  ADDR_WIDTH-1:0] pc;
  logic [  ADDR_WIDTH-1:0] pc_i             [FETCH_NUM-1:0];
  logic [            31:0] inst_i           [FETCH_NUM-1:0];
  logic [             7:0] inst_wen;

  logic [            31:0] icache_addr;
  logic                    icache_arvalid;
  logic                    icache_arready;
  logic                    icache_rready;
  logic [FETCH_NUM*32-1:0] icache_inst;
  logic                    icache_rvalid;

  logic                    pc_update;
  logic [             3:0] inst_fetch_count;
  logic                    inst_buffer_clr;
  logic [             3:0] inst_count;
  logic [             3:0] inst_ren;

`ifdef Performance_Count
  reg [31:0] valid_count;
  always @(posedge clock) begin
    if (reset) fetch_inst <= 0;
    else if (ifu_rvalid) fetch_inst <= fetch_inst + 1;
  end

  always @(posedge clock or posedge reset) begin
    if (reset) valid_count <= 0;
    else if (~valid) begin
      valid_count <= valid_count + 1;
      assert (valid_count < 1000);
    end else valid_count <= 0;
  end

`endif

  genvar i;

  assign req = ifu_axi.arvalid;

  generate
    for (i = 0; i < 8; i++) begin
    always_comb begin
      if (i == 0) begin
        inst_wen[i] = icache_rvalid & icache_rready;
      end
      else begin
        inst_wen[i] = icache_rvalid & icache_rready & (inst_fetch_count > i[3:0]);
      end
    end
      assign pc_i[i] = pc + 4 * i;
      assign inst_i[i] = icache_inst[(FETCH_NUM+i-inst_fetch_count)*32+:32];
    end
  endgenerate



  assign icache_rready = (inst_count + inst_fetch_count) < 33;
  assign inst_fetch_count = FETCH_NUM - pc[2+:$clog2(FETCH_NUM)];
  assign inst_buffer_clr = dnpc_valid;

  assign pc_update = icache_rvalid & icache_rready;
  assign icache_arvalid = 1'b1;
  assign icache_addr = pc;
  assign valid[0] = inst_count > 0;
  assign valid[1] = inst_count > 1;
  assign valid[2] = inst_count > 2;
  assign valid[3] = inst_count > 3;
  assign inst_ren = ready & valid;

  npc_generate #(
      .ResetValue(ResetValue),
      .Fetch_Num (FETCH_NUM)
  ) u_npc_generate (
      .clock     (clock),
      .reset     (reset),
      .dnpc      (dnpc),
      .dnpc_valid(dnpc_valid),
      .pc_update (pc_update),
      .pc        (pc)
  );




  Inst_Buffer #(
      .DATA_WIDTH(32),
      .ADDR_WIDTH(ADDR_WIDTH),
      .Depth     (16)
  ) u_Inst_Buffer (
      .clk(clock),
      .rst(reset),
      .clr(inst_buffer_clr),

      .inst_i  (inst_i),
      .pc_i    (pc_i),
      .inst_wen(inst_wen),

      .inst_ren  (inst_ren),
      .inst1_o   (inst1_o),
      .inst2_o   (inst2_o),
      .inst3_o   (inst3_o),
      .inst4_o   (inst4_o),
      .pc1_o     (pc1_o),
      .pc2_o     (pc2_o),
      .pc3_o     (pc3_o),
      .pc4_o     (pc4_o),
      .inst_count(inst_count)

  );






  ysyx_24100029_icache #(
      .INST_WIDTH(FETCH_NUM * 32)
  ) u_ysyx_24100029_icache (
      .clock(clock),
      .reset(reset),
      .clr  (clr),

      .addr   (icache_addr),
      .arvalid(icache_arvalid),
      .arready(icache_arready),
      .rready (icache_rready),
      .inst   (icache_inst),
      .rvalid (icache_rvalid),

`ifdef Performance_Count
      .flash_hit (flash_hit),
      .flash_miss(flash_miss),
      .sdram_hit (sdram_hit),
      .sdram_miss(sdram_miss),
`endif
      .icache_axi(ifu_axi)
  );



endmodule

