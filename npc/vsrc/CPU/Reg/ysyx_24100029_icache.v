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
`include "../define/para.v"
module ysyx_24100029_icache #(
    OFFSET_WIDTH = 2,
    INDEX_WIDTH = 3 ,
    ADDR_WIDTH = 32,
    DATA_WIDTH = 32
)
(
    input                                  clock                      ,
    input                                  reset                      ,

`ifdef Performance_Count
    output reg         [  31: 0]           flash_hit,flash_miss,sdram_hit,sdram_miss,
`endif
    output                                 ifu_awready                ,
    input                                  ifu_awvalid                ,
    input              [  31: 0]           ifu_awaddr                 ,
    input              [   3: 0]           ifu_awid                   ,
    input              [   7: 0]           ifu_awlen                  ,
    input              [   2: 0]           ifu_awsize                 ,
    input              [   1: 0]           ifu_awburst                ,

    output                                 ifu_wready                 ,
    input                                  ifu_wvalid                 ,
    input              [  31: 0]           ifu_wdata                  ,
    input              [   3: 0]           ifu_wstrb                  ,
    input                                  ifu_wlast                  ,

    input                                  ifu_bready                 ,
    output                                 ifu_bvalid                 ,
    output             [   1: 0]           ifu_bresp                  ,
    output             [   3: 0]           ifu_bid                    ,

    output                                 ifu_arready                ,
    input                                  ifu_arvalid                ,
    input              [  31: 0]           ifu_araddr                 ,
    input              [   3: 0]           ifu_arid                   ,
    input              [   7: 0]           ifu_arlen                  ,
    input              [   2: 0]           ifu_arsize                 ,
    input              [   1: 0]           ifu_arburst                ,

    input                                  ifu_rready                 ,
    output                                 ifu_rvalid                 ,
    output             [   1: 0]           ifu_rresp                  ,
    output             [  31: 0]           ifu_rdata                  ,
    output                                 ifu_rlast                  ,
    output             [   3: 0]           ifu_rid                    ,

    input                                  icache_awready             ,
    output                                 icache_awvalid             ,
    output             [  31: 0]           icache_awaddr              ,
    output             [   3: 0]           icache_awid                ,
    output             [   7: 0]           icache_awlen               ,
    output             [   2: 0]           icache_awsize              ,
    output             [   1: 0]           icache_awburst             ,

    input                                  icache_wready              ,
    output                                 icache_wvalid              ,
    output             [  31: 0]           icache_wdata               ,
    output             [   3: 0]           icache_wstrb               ,
    output                                 icache_wlast               ,

    output                                 icache_bready              ,
    input                                  icache_bvalid              ,
    input              [   1: 0]           icache_bresp               ,
    input              [   3: 0]           icache_bid                 ,

    input                                  icache_arready             ,
    output reg                             icache_arvalid             ,
    output             [  31: 0]           icache_araddr              ,
    output             [   3: 0]           icache_arid                ,
    output             [   7: 0]           icache_arlen               ,
    output             [   2: 0]           icache_arsize              ,
    output             [   1: 0]           icache_arburst             ,

    output                                 icache_rready              ,
    input                                  icache_rvalid              ,
    input              [   1: 0]           icache_rresp               ,
    input              [  31: 0]           icache_rdata               ,
    input                                  icache_rlast               ,
    input              [   3: 0]           icache_rid                  

);
   `ifdef Performance_Count
        always @(posedge clock or posedge reset) begin
            if(reset)begin
                flash_hit <= 0;
                flash_miss <= 0;
                sdram_hit <= 0;
                sdram_miss <= 0;
            end
            else if(ifu_araddr[31:28] == 4'h3)begin
                if(state == MISS & icache_rvalid)
                    flash_miss <= flash_miss + 1;
                else
                    flash_miss <= flash_miss;
                if(state == HIT)
                    flash_hit <= flash_hit + 1;
                else
                    flash_hit <= flash_hit;
            end
            else if(ifu_araddr[31:28] == 4'ha || ifu_araddr[31:28] == 4'hb)begin
                if(state == MISS & icache_rvalid)
                    sdram_miss <= sdram_miss + 1;
                else
                    sdram_miss <= sdram_miss;
                if(state == HIT)
                    sdram_hit <= sdram_hit + 1;
                else
                    sdram_hit <= sdram_hit;
            end
        end
   
   
   
   `endif

    localparam                          IDLE                       = 2'b00 ;
    localparam                          ADDR                       = 2'b01 ;
    localparam                          MISS                       = 2'b10 ;
    localparam                          HIT                        = 2'b11 ;
    
    localparam                          TAG_WIDTH                  = ADDR_WIDTH - OFFSET_WIDTH - INDEX_WIDTH;
    localparam                          VALID_WIDTH                = 1     ;
    localparam                          CACHE_WIDTH                = DATA_WIDTH + TAG_WIDTH + VALID_WIDTH; 

    wire               [VALID_WIDTH-1: 0]        valid                       ;
    wire               [INDEX_WIDTH-1: 0]        index                       ;
    wire               [TAG_WIDTH-1: 0]        tag                         ;
    wire               [DATA_WIDTH-1: 0]        rdata                       ;
    wire                                hit                         ;
    wire                                mux_flag                    ;

    reg                [CACHE_WIDTH-1: 0]        icache[2**INDEX_WIDTH-1:0]  ;
    reg                [   1: 0]        state                       ;
    reg                                 arvalid                     ;

    assign                              rdata                       = icache[index][CACHE_WIDTH-1:VALID_WIDTH+TAG_WIDTH];
    assign                              tag                         = icache[index][VALID_WIDTH+TAG_WIDTH-1:VALID_WIDTH];
    assign                              valid                       = icache[index][VALID_WIDTH-1:0];
    assign                              index                       = ifu_araddr[OFFSET_WIDTH+INDEX_WIDTH-1:OFFSET_WIDTH];
   
    assign                              icache_rready               = 1'b1;
    assign                              icache_arid                 = 0;
    assign                              icache_arlen                = 0;// 0+1 = 1 transfer once
    assign                              icache_arsize               = 3'b010;// transfer 4 bytes once
    assign                              icache_arburst              = 2'b00;// FIXED Burst
    assign                              icache_awvalid              = 0;
    assign                              icache_awaddr               = 0;
    assign                              icache_awid                 = 0;
    assign                              icache_awlen                = 0;
    assign                              icache_awsize               = 0;
    assign                              icache_awburst              = 0;

    assign                              icache_wvalid               = 0;
    assign                              icache_wdata                = 0;
    assign                              icache_wstrb                = 0;
    assign                              icache_wlast                = 0;

    assign                              icache_bready               = 0;
    assign                              icache_araddr               = ifu_araddr;


    assign                              ifu_rresp                   = 2'b00;
    assign                              ifu_rlast                   = mux_flag? icache_rlast:ifu_rvalid;
    assign                              ifu_rid                     = 0;


    assign                              ifu_awready                 = 0;
    assign                              ifu_wready                  = 0;
    assign                              ifu_bvalid                  = 0;
    assign                              ifu_bresp                   = 0;
    assign                              ifu_bid                     = 0;
    assign                              ifu_arready                 = mux_flag? icache_arready:(state == IDLE);
    assign                              ifu_rdata                   = mux_flag? icache_rdata:(state == MISS)? icache_rdata:rdata;
    assign                              ifu_rvalid                  = mux_flag? icache_rvalid: (state == HIT) | ((state == MISS) & icache_rvalid);
    assign                              icache_arvalid              = mux_flag? ifu_arvalid:arvalid;
    assign                              hit                         = valid & (ifu_araddr[ADDR_WIDTH-1:OFFSET_WIDTH+INDEX_WIDTH] == tag) & ifu_rready;
    assign                              mux_flag                    = (ifu_araddr[31:24] == 8'h0f);

    always @(posedge clock or posedge reset) begin
        if(reset)
            state <= IDLE;
        else begin
            case(state)
                IDLE:begin
                    if(ifu_arvalid & ifu_arready&~mux_flag)
                        state <= ADDR;
                    else begin
                        state <= IDLE;
                    end
                    end
                ADDR:begin
                    if(hit)
                        state <= HIT;
                    else
                        state <= MISS;
                end
                HIT:state <= IDLE;
                MISS:begin
                    if(icache_rvalid)
                        state <= IDLE;
                    else
                        state <= MISS;
                end
                default:state <= IDLE;
            endcase
        end
    end

always @(posedge clock or posedge reset) begin
    if(reset)
        arvalid <= 1'b0;
    else if(state == ADDR & ~hit)
        arvalid <= 1'b1;
    else if(arvalid & icache_arready)
        arvalid <= 1'b0;
end

always @(posedge clock) begin
    if(state == MISS & icache_rvalid)
        icache[index] <= {icache_rdata,ifu_araddr[ADDR_WIDTH-1:OFFSET_WIDTH+INDEX_WIDTH],1'b1};
end

endmodule
