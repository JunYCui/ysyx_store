`timescale 1ns / 1ps
`include "../define/para.v"
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
    parameter                           ResetValue                 = 32'h30000000
)
(
    input                               clock                      ,
    input                               reset                      ,
    input              [  31: 0]        dnpc                       ,
    input                               dnpc_flag                  ,
    input                               icache_clr                 ,

    output             [  31: 0]        snpc                       ,
    output reg         [  31: 0]        pc                         ,
    output             [  31: 0]        inst                       ,

    input                               ready                      ,
    output reg                          valid                      ,

    input                               awready                    ,
    output                              awvalid                    ,
    output             [  31: 0]        awaddr                     ,
    output             [   3: 0]        awid                       ,
    output             [   7: 0]        awlen                      ,
    output             [   2: 0]        awsize                     ,
    output             [   1: 0]        awburst                    ,

    input                               wready                     ,
    output                              wvalid                     ,
    output             [  31: 0]        wdata                      ,
    output             [   3: 0]        wstrb                      ,
    output                              wlast                      ,

    output                              bready                     ,
    input                               bvalid                     ,
    input              [   1: 0]        bresp                      ,
    input              [   3: 0]        bid                        ,

    input                               arready                    ,
    output                              arvalid                    ,
    output             [  31: 0]        araddr                     ,
    output             [   3: 0]        arid                       ,
    output             [   7: 0]        arlen                      ,
    output             [   2: 0]        arsize                     ,
    output             [   1: 0]        arburst                    ,

    output                              rready                     ,
    input                               rvalid                     ,
    input              [   1: 0]        rresp                      ,
    input              [  31: 0]        rdata                      ,
    input                               rlast                      ,
    input              [   3: 0]        rid                        ,

`ifdef Performance_Count
    output             [  31: 0]        fetch_inst                 ,
    output             [  31: 0]        flash_hit,flash_miss,sdram_hit,sdram_miss,
`endif
    output                              req                         
);


/****************icache****************/
    wire                                ifu_awready                 ;
    reg                                 ifu_awvalid                 ;
    reg                [  31: 0]        ifu_awaddr                  ;
    reg                [   3: 0]        ifu_awid                    ;
    reg                [   7: 0]        ifu_awlen                   ;
    reg                [   2: 0]        ifu_awsize                  ;
    reg                [   1: 0]        ifu_awburst                 ;
    wire                                ifu_wready                  ;
    reg                                 ifu_wvalid                  ;
    reg                [  31: 0]        ifu_wdata                   ;
    reg                [   3: 0]        ifu_wstrb                   ;
    reg                                 ifu_wlast                   ;
    reg                                 ifu_bready                  ;
    wire                                ifu_bvalid                  ;
    wire               [   1: 0]        ifu_bresp                   ;
    wire               [   3: 0]        ifu_bid                     ;
    wire                                ifu_arready                 ;
    reg                                 ifu_arvalid                 ;
    reg                [  31: 0]        ifu_araddr                  ;
    reg                [   3: 0]        ifu_arid                    ;
    reg                [   7: 0]        ifu_arlen                   ;
    reg                [   2: 0]        ifu_arsize                  ;
    reg                [   1: 0]        ifu_arburst                 ;
    reg                                 ifu_rready                  ;
    wire                                ifu_rvalid                  ;
    wire               [   1: 0]        ifu_rresp                   ;
    wire               [  31: 0]        ifu_rdata                   ;
    wire                                ifu_rlast                   ;
    wire               [   3: 0]        ifu_rid                     ;

    wire                                clr                         ;

/************ Axi4 bus ***********/
    assign                              ifu_araddr                  = pc;
    assign                              ifu_arid                    = 0;
    assign                              ifu_arlen                   = 0;// 0+1 = 1 transfer once
    assign                              ifu_arsize                  = 3'b010;// transfer 4 bytes once
    assign                              ifu_arburst                 = 2'b00;// FIXED Burst

    assign                              ifu_awvalid                 = 0;
    assign                              ifu_awaddr                  = 0;
    assign                              ifu_awid                    = 0;
    assign                              ifu_awlen                   = 0;
    assign                              ifu_awsize                  = 0;
    assign                              ifu_awburst                 = 0;

    assign                              ifu_wvalid                  = 0;
    assign                              ifu_wdata                   = 0;
    assign                              ifu_wstrb                   = 0;
    assign                              ifu_wlast                   = 0;

    assign                              ifu_bready                  = 0;

    assign                              ifu_rready                  = 1'b1;
    assign                              snpc                        = pc + 4;

/************ Axi4 bus ***********/

`ifdef Performance_Count
    reg                [  31: 0]        valid_count                 ;
    always @(posedge clock) begin
        if(reset)
            fetch_inst <= 0;
        else if(ifu_rvalid)
            fetch_inst <= fetch_inst + 1;
    end

    always @(posedge clock or posedge reset) begin
        if(reset)
            valid_count <= 0;
        else if(~valid)begin
            valid_count <= valid_count + 1;
            assert(valid_count < 1000);
        end
        else
            valid_count <= 0;
    end

`endif



always @(posedge clock) begin
    if(reset)begin
        valid <= 1'b0;
        inst <= 0;
    end
    else if(ifu_rvalid)begin
        valid <= 1'b1;
        inst <= ifu_rdata;
    end
    else if(valid & ready)begin
        valid <= 1'b0;
        inst <= 0;
    end

end
always @(posedge clock) begin
    if(reset)
        ifu_arvalid <= 1'b1;
    else if(valid & ready)
        ifu_arvalid <= 1'b1;
    else if(ifu_arvalid & ifu_arready)
        ifu_arvalid <= 1'b0;
end

always @(posedge clock) begin
        if(reset)
            pc <= ResetValue;
        else if(dnpc_flag&valid&ready)
            pc <= dnpc;
        else if(valid & ready)
            pc <= snpc;
end


    assign                              req                         = arvalid;


ysyx_24100029_icache u_ysyx_24100029_icache(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .clr                                ((icache_clr&ifu_rvalid)   ),
    `ifdef Performance_Count
    .flash_hit                          (flash_hit                 ),
    .flash_miss                         (flash_miss                ),
    .sdram_hit                          (sdram_hit                 ),
    .sdram_miss                         (sdram_miss                ),
    `endif
    .ifu_awready                        (ifu_awready               ),
    .ifu_awvalid                        (ifu_awvalid               ),
    .ifu_awaddr                         (ifu_awaddr                ),
    .ifu_awid                           (ifu_awid                  ),
    .ifu_awlen                          (ifu_awlen                 ),
    .ifu_awsize                         (ifu_awsize                ),
    .ifu_awburst                        (ifu_awburst               ),
    .ifu_wready                         (ifu_wready                ),
    .ifu_wvalid                         (ifu_wvalid                ),
    .ifu_wdata                          (ifu_wdata                 ),
    .ifu_wstrb                          (ifu_wstrb                 ),
    .ifu_wlast                          (ifu_wlast                 ),
    .ifu_bready                         (ifu_bready                ),
    .ifu_bvalid                         (ifu_bvalid                ),
    .ifu_bresp                          (ifu_bresp                 ),
    .ifu_bid                            (ifu_bid                   ),
    .ifu_arready                        (ifu_arready               ),
    .ifu_arvalid                        (ifu_arvalid               ),
    .ifu_araddr                         (ifu_araddr                ),
    .ifu_arid                           (ifu_arid                  ),
    .ifu_arlen                          (ifu_arlen                 ),
    .ifu_arsize                         (ifu_arsize                ),
    .ifu_arburst                        (ifu_arburst               ),
    .ifu_rready                         (ifu_rready                ),
    .ifu_rvalid                         (ifu_rvalid                ),
    .ifu_rresp                          (ifu_rresp                 ),
    .ifu_rdata                          (ifu_rdata                 ),
    .ifu_rlast                          (ifu_rlast                 ),
    .ifu_rid                            (ifu_rid                   ),

    .icache_awready                     (awready                   ),
    .icache_awvalid                     (awvalid                   ),
    .icache_awaddr                      (awaddr                    ),
    .icache_awid                        (awid                      ),
    .icache_awlen                       (awlen                     ),
    .icache_awsize                      (awsize                    ),
    .icache_awburst                     (awburst                   ),
    .icache_wready                      (wready                    ),
    .icache_wvalid                      (wvalid                    ),
    .icache_wdata                       (wdata                     ),
    .icache_wstrb                       (wstrb                     ),
    .icache_wlast                       (wlast                     ),
    .icache_bready                      (bready                    ),
    .icache_bvalid                      (bvalid                    ),
    .icache_bresp                       (bresp                     ),
    .icache_bid                         (bid                       ),
    .icache_arready                     (arready                   ),
    .icache_arvalid                     (arvalid                   ),
    .icache_araddr                      (araddr                    ),
    .icache_arid                        (arid                      ),
    .icache_arlen                       (arlen                     ),
    .icache_arsize                      (arsize                    ),
    .icache_arburst                     (arburst                   ),
    .icache_rready                      (rready                    ),
    .icache_rvalid                      (rvalid                    ),
    .icache_rresp                       (rresp                     ),
    .icache_rdata                       (rdata                     ),
    .icache_rlast                       (rlast                     ),
    .icache_rid                         (rid                       ) 
);



endmodule

