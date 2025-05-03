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
// Last modified Date:     2025/02/26 20:11:32
// Last Version:           V1.0
// Descriptions:
//----------------------------------------------------------------------------------------
// Created by:             Cui Junyan
// Created date:           2025/02/26 20:11:32
// mail      :             1354315077@qq.com
// Version:                V1.0
// TEXT NAME:              ysyx_24100029_icache.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/CPU/Reg/ysyx_24100029_icache.v
// Descriptions:
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//
`include "../define/interface.sv"
module ysyx_24100029_icache #(
    CacheLine_Width = 0,
    OFFSET_WIDTH = 4,
    INDEX_WIDTH = 2,
    ADDR_WIDTH = 32,
    INST_WIDTH = 256
) (
    input clock,
    input reset,
    input clr,

`ifdef Performance_Count
    output logic [31:0] flash_hit,
    flash_miss,
    sdram_hit,
    sdram_miss,
`endif

    input  [ADDR_WIDTH-1:0] addr,
    input                   arvalid,
    output                  arready,

    input                   rready,
    output [INST_WIDTH-1:0] inst,
    output                  rvalid,

    axi4_if.master icache_axi

);

`ifdef Performance_Count
  always @(posedge clock or posedge reset) begin
    if (reset) begin
      flash_hit  <= 0;
      flash_miss <= 0;
      sdram_hit  <= 0;
      sdram_miss <= 0;
    end else if (addr[31:28] == 4'h3) begin
      if (state == MISS & icache_rvalid) flash_miss <= flash_miss + 1;
      else flash_miss <= flash_miss;
      if (state == HIT) flash_hit <= flash_hit + 1;
      else flash_hit <= flash_hit;
    end else if (addr[31:28] == 4'ha || addr[31:28] == 4'hb) begin
      if (state == MISS & icache_rvalid) sdram_miss <= sdram_miss + 1;
      else sdram_miss <= sdram_miss;
      if (state == HIT) sdram_hit <= sdram_hit + 1;
      else sdram_hit <= sdram_hit;
    end
  end



`endif

  `define IS_CacheLine_Width_0 CacheLine_Width==0

  localparam IDLE = 2'b00;
  localparam ADDR = 2'b01;
  localparam MISS = 2'b10;
  localparam HIT = 2'b11;

  localparam TAG_WIDTH = ADDR_WIDTH - OFFSET_WIDTH - INDEX_WIDTH - CacheLine_Width;
  localparam VALID_WIDTH = 1;
  localparam CACHE_WIDTH = INST_WIDTH * (2 ** CacheLine_Width) + TAG_WIDTH + VALID_WIDTH;

  logic [                                 VALID_WIDTH-1:0] valid;
  logic [                                   TAG_WIDTH-1:0] tag;
  logic [`IS_CacheLine_Width_0? 0 : CacheLine_Width-1 : 0] block_choice;
  logic [               INST_WIDTH*2**CacheLine_Width-1:0] block_data;
  logic                                                    hit;
  logic [                                 INDEX_WIDTH-1:0] index;

  logic [                                 CACHE_WIDTH-1:0] icache       [2**INDEX_WIDTH-1:0];
  logic [                                             1:0] state;
  logic [                                             7:0] count;
  logic                                                    hit_r;
  logic [                                 INDEX_WIDTH-1:0] index_r;
  /* verilator lint_off SELRANGE */
  /* verilator lint_off WIDTHTRUNC */

  always @(posedge clock) begin
    if (reset) hit_r <= 0;
    else if (arvalid & arready) hit_r <= #1 valid & hit;
  end

  always @(posedge clock) begin
    if (reset) index_r <= 0;
    else if (arvalid & arready) index_r <= #1 index;
  end



  always @(posedge clock) begin
    if (reset) state <= IDLE;
    else begin
      case (state)
        IDLE: begin
          if (arvalid & arready) state <= #1 ADDR;
          else begin
            state <= #1 IDLE;
          end
        end
        ADDR: begin
          if (hit_r) state <= #1 HIT;
          else state <= #1 MISS;
        end
        HIT: if (rready & rvalid) state <= #1 IDLE;
        MISS: begin
          if (icache_axi.rlast & icache_axi.rvalid) state <= #1 HIT;
          else state <= #1 MISS;
        end
        default: state <= IDLE;
      endcase
    end
  end

  always @(posedge clock) begin
    if (reset) icache_axi.arvalid <= 1'b0;
    else if (state == ADDR & ~hit_r) icache_axi.arvalid <= 1'b1;
    else if (icache_axi.arvalid & icache_axi.arready) icache_axi.arvalid <= 1'b0;
  end

  always @(posedge clock) begin
    if (reset) count <= 0;
    else if (state == ADDR & ~hit_r) count <= 0;
    else if (icache_axi.rvalid) count <= count + 1;
  end

  integer i;

  always @(posedge clock) begin
    if (clr) begin
      for (i = 0; i < 2 ** INDEX_WIDTH; i++) icache[i][0] <= 1'b0;
    end else if (arvalid & arready)
      icache[index][TAG_WIDTH+VALID_WIDTH-1:0] <= {
        addr[ADDR_WIDTH-1:OFFSET_WIDTH+INDEX_WIDTH+CacheLine_Width], 1'b1
      };
    else if (icache_axi.rvalid)
      icache[index_r][TAG_WIDTH+VALID_WIDTH+32*count+:32] <= icache_axi.rdata;
  end




  assign arready = state == IDLE;


  assign                              block_choice                = `IS_CacheLine_Width_0? 0 : addr[CacheLine_Width+OFFSET_WIDTH-1:OFFSET_WIDTH];
  assign block_data = icache[index_r][CACHE_WIDTH-1:VALID_WIDTH+TAG_WIDTH];
  assign inst = block_data[INST_WIDTH*block_choice+:INST_WIDTH];
  assign tag = icache[index][VALID_WIDTH+TAG_WIDTH-1:VALID_WIDTH];
  assign valid = icache[index][VALID_WIDTH-1:0];
  assign rvalid = state == HIT;


  assign hit = (addr[ADDR_WIDTH-1:OFFSET_WIDTH+INDEX_WIDTH+CacheLine_Width] == tag);
  assign index = addr[OFFSET_WIDTH+CacheLine_Width+INDEX_WIDTH-1:OFFSET_WIDTH+CacheLine_Width];


  assign icache_axi.rready = state == MISS;
  assign icache_axi.arid = 0;
  assign icache_axi.arlen = 2 ** CacheLine_Width * INST_WIDTH / 32 - 1;  // 0+1 = 1 transfer once
  assign icache_axi.arsize = 3'b010;  // transfer 4 bytes once
  assign icache_axi.arburst = 2'b01;  // INCR
  assign icache_axi.awvalid = 0;
  assign icache_axi.awaddr = 0;
  assign icache_axi.awid = 0;
  assign icache_axi.awlen = 0;
  assign icache_axi.awsize = 0;
  assign icache_axi.awburst = 0;

  assign icache_axi.wvalid = 0;
  assign icache_axi.wdata = 0;
  assign icache_axi.wstrb = 0;
  assign icache_axi.wlast = 0;

  assign icache_axi.bready = 0;
  assign icache_axi.araddr = {
    addr[ADDR_WIDTH-1:CacheLine_Width+OFFSET_WIDTH], {(CacheLine_Width + OFFSET_WIDTH) {1'b0}}
  };






endmodule
