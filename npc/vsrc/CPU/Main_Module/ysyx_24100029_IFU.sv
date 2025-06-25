`timescale 1ns / 1ps
`include "../define/para.sv"
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
    localparam FIFO_DATA_WIDTH = 32+32+32+1,
    parameter ResetValue = 32'h30000000
) (
    input        clock,
    input        reset,
    input [31:0] dnpc,
    input        dnpc_flag,
    input        icache_clr,
    input        stall,

    output [31:0] ifu_inst,
    output [31:0] ifu_pc,
    output [31:0] ifu_pred_pc,
    output  ifu_pred_res,

    input  ready,
    output valid,

    axi4_if.master icache_axi,

    input        br_valid,
    input        br_is_taken,
    input [31:0] br_pc,
    input [ 1:0] br_pc_type,
    input [31:0] br_npc,


`ifdef Performance_Count
    output [31:0] pred_error,
    output [31:0] fetch_inst,
    output [31:0] flash_hit,
    flash_miss,
    sdram_hit,
    sdram_miss,
`endif
    output        req
);






`ifdef Performance_Count
  reg [31:0] valid_count;
  always @(posedge clock) begin
    if (reset) fetch_inst <= 0;
    else if (pc_update) fetch_inst <= fetch_inst + 1;
  end
  always @(posedge clock) begin
      if(reset) pred_error <= 0;
      else if(dnpc_flag) pred_error <= pred_error + 1;
  end

  always @(posedge clock ) begin
    if (reset) valid_count <= 0;
    else if (~valid) begin
      valid_count <= valid_count + 1;
      assert (valid_count < 1000);
    end else valid_count <= 0;
  end

`endif

  wire pred_res_i;
  wire [31:0]pred_pc_i;
  wire [31:0] npc;
  wire pc_update;
  wire cpu_valid_i;
  wire cpu_ready_o;
  wire cpu_valid_o;
  wire [31:0]pred_pc_o;
  wire [31:0]cpu_pc_o;
  wire pred_res_o;
  wire [31:0]cpu_inst_o;
  wire cpu_ready_i;

  wire [FIFO_DATA_WIDTH-1:0]data_in;
  wire [FIFO_DATA_WIDTH-1:0]data_out;
  wire wr_en,rd_en;
  wire full,empty;

  reg [31:0]pc;



  always @(posedge clock) begin
    if (reset) pc <= ResetValue;
    else if (dnpc_flag) pc <= dnpc;
    else if (cpu_valid_i & cpu_ready_o) pc <= npc;
  end





  assign pc_update  = cpu_valid_i & cpu_ready_o;
  assign req        = icache_axi.arvalid;
  assign pred_pc_i  = npc;
  assign wr_en = cpu_valid_o & cpu_ready_i;
  assign rd_en = ready & valid & ~stall;
  assign valid = ~empty;
  assign cpu_ready_i = ~full;
  assign cpu_valid_i = 1'b1; 
  assign data_in = {pred_pc_o,cpu_pc_o,cpu_inst_o,pred_res_o};
  assign {ifu_pred_pc,ifu_pc,ifu_inst,ifu_pred_res} = data_out;

  ysyx_24100029_BPU #(
      .BHR_WIDTH(3)
  ) u_BPU (
      .clock      (clock),
      .reset      (reset),
      .br_valid   (br_valid),
      .br_is_taken(br_is_taken),
      .br_pc      (br_pc),
      .br_pc_type (br_pc_type),
      .br_npc     (br_npc),
      .pc         (pc),
      .pc_update  (pc_update),
      .npc        (npc),
      .pred_res   (pred_res_i)
  );


  ysyx_24100029_icache u_ysyx_24100029_icache (
      .clock      (clock),
      .reset      (reset),
      .clr        (icache_clr),
      .flush      (dnpc_flag),
`ifdef Performance_Count
      .flash_hit  (flash_hit),
      .flash_miss (flash_miss),
      .sdram_hit  (sdram_hit),
      .sdram_miss (sdram_miss),
`endif

      .cpu_valid_i(cpu_valid_i),
      .pred_res_i(pred_res_i),
      .pred_pc_i(pred_pc_i),
      .cpu_pc_i (pc),
      .cpu_ready_o(cpu_ready_o),
      
      .cpu_valid_o(cpu_valid_o), 
      .pred_pc_o(pred_pc_o),
      .cpu_pc_o(cpu_pc_o),
      .pred_res_o(pred_res_o),
      .cpu_inst_o(cpu_inst_o),
      .cpu_ready_i(cpu_ready_i),

      .icache_awready(icache_axi.awready),
      .icache_awvalid(icache_axi.awvalid),
      .icache_awaddr (icache_axi.awaddr),
      .icache_awid   (icache_axi.awid),
      .icache_awlen  (icache_axi.awlen),
      .icache_awsize (icache_axi.awsize),
      .icache_awburst(icache_axi.awburst),
      .icache_wready (icache_axi.wready),
      .icache_wvalid (icache_axi.wvalid),
      .icache_wdata  (icache_axi.wdata),
      .icache_wstrb  (icache_axi.wstrb),
      .icache_wlast  (icache_axi.wlast),
      .icache_bready (icache_axi.bready),
      .icache_bvalid (icache_axi.bvalid),
      .icache_bresp  (icache_axi.bresp),
      .icache_bid    (icache_axi.bid),
      .icache_arready(icache_axi.arready),
      .icache_arvalid(icache_axi.arvalid),
      .icache_araddr (icache_axi.araddr),
      .icache_arid   (icache_axi.arid),
      .icache_arlen  (icache_axi.arlen),
      .icache_arsize (icache_axi.arsize),
      .icache_arburst(icache_axi.arburst),
      .icache_rready (icache_axi.rready),
      .icache_rvalid (icache_axi.rvalid),
      .icache_rresp  (icache_axi.rresp),
      .icache_rdata  (icache_axi.rdata),
      .icache_rlast  (icache_axi.rlast),
      .icache_rid    (icache_axi.rid)
  );



fifo #(
  .DATA_WIDTH 	(32+32+32+1  ),
  .FIFO_DEPTH 	(2  ))
u_fifo(
  .clk      	(clock       ),
  .rst      	(reset       ),
  .clr      	(dnpc_flag   ),
  .wr_en    	(wr_en       ),
  .data_in  	(data_in     ),
  .rd_en    	(rd_en     ),
  .data_out 	(data_out  ),
  .full     	(full      ),
  .empty    	(empty     )
);





endmodule

