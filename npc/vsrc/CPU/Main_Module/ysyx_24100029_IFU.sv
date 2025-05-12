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
    input        icache_clr,

    output [          31:0] inst1_o,
    output [          31:0] inst2_o,
    output [          31:0] inst3_o,
    output [          31:0] inst4_o,
    output [ADDR_WIDTH-1:0] pc1_o,
    output [ADDR_WIDTH-1:0] pc2_o,
    output [ADDR_WIDTH-1:0] pc3_o,
    output [ADDR_WIDTH-1:0] pc4_o,
    output                  pred_res1_o,
    output                  pred_res2_o,
    output                  pred_res3_o,
    output                  pred_res4_o,
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
    output        req,

    output       br_ready,
    input        br_valid,

    input        br_error,
    input        br_is_taken,
    input [31:0] br_pc,
    input [ 1:0] br_pc_type,
    input [31:0] br_npc
);

  localparam FETCH_NUM = Issue_Num;
  localparam IDLE = 1'b0;
  localparam WORK = 1'b1;

  logic [  ADDR_WIDTH-1:0] pc;
  logic [  ADDR_WIDTH-1:0] pc_i             [FETCH_NUM-1:0];
  logic [            31:0] inst_i           [FETCH_NUM-1:0];
  logic [   FETCH_NUM-1:0] pred_res_i;
  logic [   Issue_Num-1:0] inst_wen;
  logic [  $clog2(Issue_Num+1)-1:0] inst_wen_count;

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


  // output declaration of module Br_Pred
  logic [            31:0] npc;
  logic                    npc_valid;
  logic [   FETCH_NUM-1:0] inst_keilled;
  logic [   FETCH_NUM-1:0] pred_res;





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

  generate
    for (i = 0; i < FETCH_NUM; i++) begin
      always_comb begin
        if (i == 0) begin
          inst_wen[i] = icache_rvalid & icache_rready & ~inst_keilled[i];
        end else begin
          inst_wen[i] = icache_rvalid & icache_rready & ~inst_keilled[i] & (inst_fetch_count > i[3:0]);
        end
      end
      assign pc_i[i]   = pc + 4 * i;
      assign inst_i[i] = icache_inst[(FETCH_NUM+i-inst_fetch_count)*32+:32];
    end
  endgenerate


  always @(posedge clock) begin
    if (reset) pc <= ResetValue;
    else if (br_valid & br_ready & br_error) pc <= br_npc;
    else if (pc_update & npc_valid) pc <= npc;
  end

  always @(posedge clock) begin
      if(reset)
        icache_arvalid <= 1'b1;
      else if(icache_arvalid & icache_arready) 
        icache_arvalid <= 1'b0;
      else if(pc_update)
        icache_arvalid <= 1'b1;
  end



  assign br_ready = pc_update ;
  assign pred_res_i = pred_res ;
  assign req = ifu_axi.arvalid;
  assign icache_rready = (inst_count + inst_fetch_count) < 33;
  assign inst_fetch_count = FETCH_NUM - pc[2+:$clog2(FETCH_NUM)];
  assign inst_buffer_clr = br_valid & br_ready & br_error;

  assign pc_update = icache_rvalid & icache_rready;
  assign icache_addr = pc;
  assign valid[0] = inst_count > 0;
  assign valid[1] = inst_count > 1;
  assign valid[2] = inst_count > 2;
  assign valid[3] = inst_count > 3;
  assign inst_ren = ready & valid;








  Br_Pred #(
      .BHR_WIDTH(3)
  ) u_Br_Pred (
      .clock      (clock),
      .reset      (reset),

      .br_valid   (br_valid),
      .br_ready   (br_ready),
      .br_is_taken(br_is_taken),
      .br_pc      (br_pc),
      .br_pc_type (br_pc_type),
      .br_npc     (br_npc),

      .killed   (inst_keilled),
      .pc       (pc),
      .pc_update(pc_update),
      .pred_res (pred_res),
      .npc      (npc),
      .npc_valid(npc_valid)
  );






  Inst_Buffer #(
      .DATA_WIDTH(32),
      .ADDR_WIDTH(ADDR_WIDTH),
      .Depth     (16),
      .Fetch_NUM (FETCH_NUM)
  ) u_Inst_Buffer (
      .clk(clock),
      .rst(reset),
      .clr(inst_buffer_clr),

      .inst_i    (inst_i),
      .pc_i      (pc_i),
      .pred_res_i(pred_res_i),
      .inst_wen  (inst_wen),

      .inst_ren   (inst_ren),
      .inst1_o    (inst1_o),
      .inst2_o    (inst2_o),
      .inst3_o    (inst3_o),
      .inst4_o    (inst4_o),
      .pc1_o      (pc1_o),
      .pc2_o      (pc2_o),
      .pc3_o      (pc3_o),
      .pc4_o      (pc4_o),
      .pred_res1_o(pred_res1_o),
      .pred_res2_o(pred_res2_o),
      .pred_res3_o(pred_res3_o),
      .pred_res4_o(pred_res4_o),
      .inst_count (inst_count)

  );






  ysyx_24100029_icache #(
      .INST_WIDTH(FETCH_NUM * 32)
  ) u_ysyx_24100029_icache (
      .clock(clock),
      .reset(reset),
      .clr  (icache_clr),

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

