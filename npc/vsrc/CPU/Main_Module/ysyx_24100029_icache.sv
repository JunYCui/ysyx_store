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
`include "../define/para.sv"
`include "../define/interface.sv"
module ysyx_24100029_icache #(
    CacheLine_Width = 2,
    OFFSET_WIDTH = 2,
    INDEX_WIDTH = 2,
    ADDR_WIDTH = 32,
    DATA_WIDTH = 32
) (
    input             clock,
    input             reset,
    input             clr,
    input             flush,
`ifdef Performance_Count
    output reg [31:0] flash_hit,
    flash_miss,
    sdram_hit,
    sdram_miss,
`endif
    input  cpu_valid_i,
    input  [31:0]cpu_pc_i,
    input  [31:0]pred_pc_i,
    input   pred_res_i,
    output cpu_ready_o,

    input   cpu_ready_i,
    output logic [31:0]cpu_inst_o,
    output logic [31:0]cpu_pc_o,
    output logic [31:0]pred_pc_o,
    output logic pred_res_o,
    output cpu_valid_o,


    input         icache_awready,
    output        icache_awvalid,
    output [31:0] icache_awaddr,
    output [ 3:0] icache_awid,
    output [ 7:0] icache_awlen,
    output [ 2:0] icache_awsize,
    output [ 1:0] icache_awburst,

    input         icache_wready,
    output        icache_wvalid,
    output [31:0] icache_wdata,
    output [ 3:0] icache_wstrb,
    output        icache_wlast,

    output       icache_bready,
    input        icache_bvalid,
    input  [1:0] icache_bresp,
    input  [3:0] icache_bid,

    input             icache_arready,
    output reg        icache_arvalid,
    output     [31:0] icache_araddr,
    output     [ 3:0] icache_arid,
    output     [ 7:0] icache_arlen,
    output     [ 2:0] icache_arsize,
    output     [ 1:0] icache_arburst,

    output        icache_rready,
    input         icache_rvalid,
    input  [ 1:0] icache_rresp,
    input  [31:0] icache_rdata,
    input         icache_rlast,
    input  [ 3:0] icache_rid

);
`ifdef Performance_Count
  always @(posedge clock) begin
    if (reset) begin
      flash_hit  <= 0;
      flash_miss <= 0;
      sdram_hit  <= 0;
      sdram_miss <= 0;
    end else if (cpu_pc_i[31:28] == 4'h3) begin
      if (state == MISS & icache_rvalid) flash_miss <= flash_miss + 1;
      else flash_miss <= flash_miss;
      if ((state == ADDR) & hit ) flash_hit <= flash_hit + 1;
      else flash_hit <= flash_hit;
    end else if (cpu_pc_i[31:28] == 4'ha || cpu_pc_i[31:28] == 4'hb) begin
      if (state == MISS & icache_rvalid) sdram_miss <= sdram_miss + 1;
      else sdram_miss <= sdram_miss;
      if ((state == ADDR) & hit ) sdram_hit <= sdram_hit + 1;
      else sdram_hit <= sdram_hit;
    end
  end



`endif

  `define IS_CacheLine_Width_0 CacheLine_Width==0

  localparam IDLE = 2'b00;
  localparam ADDR = 2'b01;
  localparam MISS = 2'b10;
  localparam DIRECT = 2'b11;


  localparam TAG_WIDTH = ADDR_WIDTH - OFFSET_WIDTH - INDEX_WIDTH - CacheLine_Width;
  localparam VALID_WIDTH = 1;
  localparam CACHE_WIDTH = DATA_WIDTH * (2 ** CacheLine_Width) + TAG_WIDTH + VALID_WIDTH;

  wire [                                 VALID_WIDTH-1:0] icache_valid;
  wire [                                 INDEX_WIDTH-1:0] index;
  wire [                                   TAG_WIDTH-1:0] icache_tag;
  wire [                                  DATA_WIDTH-1:0] rdata;
  wire                                                    hit;
  wire                                                    mux_flag;
  wire [`IS_CacheLine_Width_0? 0 : CacheLine_Width-1 : 0] block_choice;
  wire [                       32*2**CacheLine_Width-1:0] block_data;
    wire                                data_choice                 ;

  reg  [                                 CACHE_WIDTH-1:0] icache         [2**INDEX_WIDTH-1:0];
  reg  [                                             1:0] state;
  reg  [                               CacheLine_Width:0] count;
  reg  [                                 INDEX_WIDTH-1:0] index_r;
  reg  [                                   TAG_WIDTH-1:0] cpu_tag_r;
  reg  [                             CacheLine_Width-1:0] block_choice_r;
  reg flush_r;

  always @(posedge clock) begin
    if (reset) begin
      index_r   <= 0;
      cpu_tag_r <= 0;
      block_choice_r <= 0;
      pred_pc_o <= 0;
      pred_res_o <= 0;
    end else if (cpu_valid_i & cpu_ready_o & ~flush) begin
      index_r   <= index;
      cpu_tag_r <= cpu_pc_i[ADDR_WIDTH-1:OFFSET_WIDTH+INDEX_WIDTH+CacheLine_Width];
      block_choice_r <= block_choice;
      pred_pc_o <= pred_pc_i;
      pred_res_o <= pred_res_i;
    end
  end

  always @(posedge clock) begin
      if(reset)
        flush_r <= 1'b0;
      else begin
        case(state)
        MISS:if(icache_rlast & icache_rvalid & icache_rready) flush_r <= 1'b0;
        else flush_r <= flush_r? flush_r: flush;
        DIRECT:if(icache_rlast & icache_rvalid & icache_rready) flush_r <= 1'b0;
        else flush_r <= flush_r? flush_r: flush;
        default:flush_r <= 1'b0;
        endcase
      end
  end




  always @(posedge clock) begin
    if (reset) state <= IDLE;
    else begin
      case (state)
        IDLE: begin
          if (cpu_valid_i & cpu_ready_o & ~flush) state <= mux_flag? ADDR:DIRECT;
          else begin
            state <= IDLE;
          end
        end
        ADDR: begin
          if (flush | hit&cpu_ready_i) state <=  IDLE;
          else if (hit&~cpu_ready_i) state <= ADDR ;
          else if (icache_arready & icache_arvalid) state <= MISS;
        end
        MISS: begin
          if (icache_rlast & icache_rvalid & icache_rready) state <= (cpu_ready_i|flush|flush_r)? IDLE:ADDR ;
          else state <= MISS;
        end
        DIRECT:begin
          state <= icache_rvalid & icache_rready & icache_rlast? IDLE:DIRECT;
        end
        default: state <= IDLE;
      endcase
    end
  end


  always @(posedge clock) begin
    if (reset) count <= 0;
    else if (state == IDLE) count <= 0;
    else if (icache_rvalid) count <= count + 1;
  end

  integer i;

  always @(posedge clock) begin
    if (clr) begin
      for (i = 0; i < 2 ** INDEX_WIDTH; i++) icache[i][0] <= 1'b0;
    end else if (state == MISS)begin
      icache[index_r][TAG_WIDTH+VALID_WIDTH-1:0] <= {cpu_tag_r, 1'b1};
      if(icache_rvalid &  icache_rready) icache[index_r][TAG_WIDTH+VALID_WIDTH+32*count+:32] <= icache_rdata;
    end
  end

  assign block_choice = `IS_CacheLine_Width_0? 0 : cpu_pc_i[CacheLine_Width+OFFSET_WIDTH-1:OFFSET_WIDTH];
  assign block_data = icache[index_r][CACHE_WIDTH-1:VALID_WIDTH+TAG_WIDTH];
  assign rdata = block_data[32*block_choice_r+:32];
  assign icache_tag = icache[index_r][VALID_WIDTH+TAG_WIDTH-1:VALID_WIDTH];
  assign icache_valid = icache[index_r][VALID_WIDTH-1:0];
  assign index = cpu_pc_i[OFFSET_WIDTH+CacheLine_Width+INDEX_WIDTH-1:OFFSET_WIDTH+CacheLine_Width];

  assign icache_rready = state == DIRECT ? cpu_ready_i : 1'b1;
  assign icache_arid = 0;
  assign icache_arlen = state == ADDR ? 2 ** CacheLine_Width - 1 : 0;  // 0+1 = 1 transfer once
  assign icache_arsize = 3'b010;  // transfer 4 bytes once
  assign icache_arburst = state == ADDR  ? 2'b01:2'b00;  // INCR Burst
  assign icache_awvalid = 0;
  assign icache_awaddr = 0;
  assign icache_awid = 0;
  assign icache_awlen = 0;
  assign icache_awsize = 0;
  assign icache_awburst = 0;

  assign icache_wvalid = 0;
  assign icache_wdata = 0;
  assign icache_wstrb = 0;
  assign icache_wlast = 0;

  assign icache_bready = 0;
  assign icache_araddr = state == ADDR ? {cpu_tag_r,index_r,{(CacheLine_Width+OFFSET_WIDTH){1'b0}}}:cpu_pc_i;


  assign icache_arvalid = ((state == IDLE & cpu_valid_i & ~mux_flag)| (state == ADDR & ~hit))&~flush;
  assign cpu_ready_o = mux_flag?  state == IDLE: icache_arready ;


  assign data_choice = `IS_CacheLine_Width_0? 1 : (block_choice_r == {CacheLine_Width{1'b1}}) ; 
  assign cpu_inst_o   = state == DIRECT? icache_rdata:(state == MISS & data_choice )? icache_rdata:rdata;
  assign cpu_valid_o  = state == DIRECT? icache_rvalid: ((state == ADDR)&hit&~flush) | ((state == MISS || state == DIRECT ) & icache_rvalid & icache_rlast &~(flush | flush_r) );
  assign cpu_pc_o = {cpu_tag_r,index_r,block_choice_r,{OFFSET_WIDTH{1'b0}}};
  assign hit = icache_valid & (cpu_tag_r == icache_tag) ;
  assign mux_flag = ~(cpu_pc_i[31:28] == 4'ha);  // sram addr 







endmodule
