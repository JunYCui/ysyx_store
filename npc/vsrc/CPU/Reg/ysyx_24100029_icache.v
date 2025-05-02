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
module ysyx_24100029_icache #(
    CacheLine_Width = 0,
    OFFSET_WIDTH = 4,
    INDEX_WIDTH = 2,
    ADDR_WIDTH = 32 ,
    INST_WIDTH = 128
)
(
    input                               clock                      ,
    input                               reset                      ,
    input                               clr                        ,

`ifdef Performance_Count
    output reg         [  31: 0]        flash_hit,flash_miss,sdram_hit,sdram_miss,
`endif

    input              [ADDR_WIDTH-1: 0]        addr                       ,
    input                               arvalid                    ,
    output                              arready                    ,
    
    input                               rready                     ,
    output             [INST_WIDTH-1: 0]        inst                       ,
    output                              rvalid                     ,

    input                               icache_awready             ,
    output                              icache_awvalid             ,
    output             [ADDR_WIDTH-1: 0]        icache_awaddr              ,
    output             [   3: 0]        icache_awid                ,
    output             [   7: 0]        icache_awlen               ,
    output             [   2: 0]        icache_awsize              ,
    output             [   1: 0]        icache_awburst             ,

    input                               icache_wready              ,
    output                              icache_wvalid              ,
    output             [  31: 0]        icache_wdata               ,
    output             [   3: 0]        icache_wstrb               ,
    output                              icache_wlast               ,

    output                              icache_bready              ,
    input                               icache_bvalid              ,
    input              [   1: 0]        icache_bresp               ,
    input              [   3: 0]        icache_bid                 ,

    input                               icache_arready             ,
    output reg                          icache_arvalid             ,
    output             [ADDR_WIDTH-1: 0]        icache_araddr              ,
    output             [   3: 0]        icache_arid                ,
    output             [   7: 0]        icache_arlen               ,
    output             [   2: 0]        icache_arsize              ,
    output             [   1: 0]        icache_arburst             ,

    output                              icache_rready              ,
    input                               icache_rvalid              ,
    input              [   1: 0]        icache_rresp               ,
    input              [  31: 0]        icache_rdata               ,
    input                               icache_rlast               ,
    input              [   3: 0]        icache_rid                  

);

   `ifdef Performance_Count
        always @(posedge clock or posedge reset) begin
            if(reset)begin
                flash_hit <= 0;
                flash_miss <= 0;
                sdram_hit <= 0;
                sdram_miss <= 0;
            end
            else if(addr[31:28] == 4'h3)begin
                if(state == MISS & icache_rvalid)
                    flash_miss <= flash_miss + 1;
                else
                    flash_miss <= flash_miss;
                if(state == HIT)
                    flash_hit <= flash_hit + 1;
                else
                    flash_hit <= flash_hit;
            end
            else if(addr[31:28] == 4'ha || addr[31:28] == 4'hb)begin
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

`define IS_CacheLine_Width_0 CacheLine_Width==0

    localparam                          IDLE                       = 2'b00 ;
    localparam                          ADDR                       = 2'b01 ;
    localparam                          MISS                       = 2'b10 ;
    localparam                          HIT                        = 2'b11 ;
    
    localparam                          TAG_WIDTH                  = ADDR_WIDTH - OFFSET_WIDTH - INDEX_WIDTH - CacheLine_Width;
    localparam                          VALID_WIDTH                = 1     ;
    localparam                          CACHE_WIDTH                = INST_WIDTH*(2**CacheLine_Width) + TAG_WIDTH + VALID_WIDTH; 

    wire               [VALID_WIDTH-1: 0]        valid                       ;
    wire               [TAG_WIDTH-1: 0]        tag                         ;
    wire               [`IS_CacheLine_Width_0? 0:CacheLine_Width-1 : 0]        block_choice                ;
    wire               [INST_WIDTH*2**CacheLine_Width-1: 0]        block_data                  ;
    wire                                hit                         ;
    wire               [INDEX_WIDTH-1: 0]        index                       ;

    reg                [CACHE_WIDTH-1: 0]        icache[2**INDEX_WIDTH-1:0]  ;
    reg                [   1: 0]        state                       ;
    reg                [   7: 0]        count                       ;
    reg                                 hit_r                       ;
    reg                [INDEX_WIDTH-1: 0]        index_r                     ;
/* verilator lint_off SELRANGE */
/* verilator lint_off WIDTHTRUNC */
 
    always @(posedge clock) begin
        if(reset)
            hit_r <= 0;
        else if(arvalid & arready)
            hit_r <= #1 valid & hit;
    end

    always @(posedge clock) begin
        if(reset)
            index_r <= 0;
        else if(arvalid & arready)
            index_r <= #1 index;
    end



    always @(posedge clock) begin
        if(reset)
            state <= IDLE;
        else begin
            case(state)
                IDLE:begin
                    if(arvalid & arready)
                        state <= #1 ADDR;
                    else begin
                        state <= #1 IDLE;
                    end
                    end
                ADDR:begin
                    if(hit_r)
                        state <= #1 HIT;
                    else
                        state <= #1 MISS;
                end
                HIT:if(rready & rvalid) state <= #1 IDLE;
                MISS:begin
                    if(icache_rlast & icache_rvalid)
                        state <= #1 HIT;
                    else
                        state <= #1 MISS;
                end
                default:state <= IDLE;
            endcase
        end
    end

always @(posedge clock) begin
    if(reset)
        icache_arvalid <= 1'b0;
    else if(state == ADDR & ~hit_r)
        icache_arvalid <= 1'b1;
    else if(icache_arvalid & icache_arready)
        icache_arvalid <= 1'b0;
end

always @(posedge clock) begin
    if(reset)
        count <= 0;
    else if(state == ADDR & ~hit_r)
        count <= 0;
    else if(icache_rvalid)
        count <= count + 1;
end

    integer                             i                           ;

always @(posedge clock) begin
    if (clr) begin
        for(i=0;i<2**INDEX_WIDTH;i++)
            icache[i][0] <= 1'b0;
    end
    else if(arvalid & arready)
        icache[index][TAG_WIDTH+VALID_WIDTH-1:0] <= {addr[ADDR_WIDTH-1:OFFSET_WIDTH+INDEX_WIDTH+CacheLine_Width],1'b1};
    else if(icache_rvalid)
        icache[index_r][TAG_WIDTH + VALID_WIDTH + 32*count+:32] <= icache_rdata;
end




    assign                              arready                     = state == IDLE;


    assign                              block_choice                = `IS_CacheLine_Width_0? 0 : addr[CacheLine_Width+OFFSET_WIDTH-1:OFFSET_WIDTH];
    assign                              block_data                  = icache[index_r][CACHE_WIDTH-1:VALID_WIDTH+TAG_WIDTH];
    assign                              inst                        = block_data[INST_WIDTH*block_choice+:INST_WIDTH];
    assign                              tag                         = icache[index][VALID_WIDTH+TAG_WIDTH-1:VALID_WIDTH];
    assign                              valid                       = icache[index][VALID_WIDTH-1:0];
    assign                              rvalid                      = state == HIT;


    assign                              hit                         = (addr[ADDR_WIDTH-1:OFFSET_WIDTH+INDEX_WIDTH+CacheLine_Width] == tag);
    assign                              index                       = addr[OFFSET_WIDTH+CacheLine_Width+INDEX_WIDTH-1:OFFSET_WIDTH+CacheLine_Width];


    assign                              icache_rready               = state == MISS;
    assign                              icache_arid                 = 0;
    assign                              icache_arlen                = 2**CacheLine_Width*INST_WIDTH/32-1;// 0+1 = 1 transfer once
    assign                              icache_arsize               = 3'b010;// transfer 4 bytes once
    assign                              icache_arburst              = 2'b01;// INCR
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
    assign                              icache_araddr               = {addr[ADDR_WIDTH-1:CacheLine_Width+OFFSET_WIDTH],{(CacheLine_Width+OFFSET_WIDTH){1'b0}}};






endmodule
