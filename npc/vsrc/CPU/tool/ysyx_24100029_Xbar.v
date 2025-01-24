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

module ysyx_24100029_Xbar(

    input                                  reset                      ,
    input                                  clock                      ,

    input              [32-1: 0]           araddr                     ,
    input                                  arvalid                    ,
    output reg                             arready                    ,
    input              [   3: 0]           arid                       ,
    input              [   7: 0]           arlen                      ,
    input              [   2: 0]           arsize                     ,
    input              [   1: 0]           arburst                    ,

    input                                  rready                     ,
    output reg         [32-1: 0]           rdata                      ,
    output reg         [   1: 0]           rresp                      ,
    output reg                             rvalid                     ,
    output reg                             rlast                      ,
    output reg         [   3: 0]           rid                        ,

    input              [32-1: 0]           awaddr                     ,
    input                                  awvalid                    ,
    output reg                             awready                    ,
    input              [   3: 0]           awid                       ,
    input              [   7: 0]           awlen                      ,
    input              [   2: 0]           awsize                     ,
    input              [   1: 0]           awburst                    ,

    input              [32-1: 0]           wdata                      ,
    input              [   3: 0]           wstrb                      ,
    input                                  wvalid                     ,
    output reg                             wready                     ,
    input                                  wlast                      ,
    
    output reg         [   1: 0]           bresp                      ,
    output reg                             bvalid                     ,
    input                                  bready                     ,
    output reg         [   3: 0]           bid                        ,

    input                                  CLNT_awready               ,
    output reg                             CLNT_awvalid               ,
    output reg         [  31: 0]           CLNT_awaddr                ,
    output reg         [   3: 0]           CLNT_awid                  ,
    output reg         [   7: 0]           CLNT_awlen                 ,
    output reg         [   2: 0]           CLNT_awsize                ,
    output reg         [   1: 0]           CLNT_awburst               ,

    input                                  CLNT_wready                ,
    output reg                             CLNT_wvalid                ,
    output reg         [  31: 0]           CLNT_wdata                 ,
    output reg         [   3: 0]           CLNT_wstrb                 ,
    output reg                             CLNT_wlast                 ,

    output reg                             CLNT_bready                ,
    input                                  CLNT_bvalid                ,
    input              [   1: 0]           CLNT_bresp                 ,
    input              [   3: 0]           CLNT_bid                   ,
    
    input                                  CLNT_arready               ,
    output reg                             CLNT_arvalid               ,
    output reg         [  31: 0]           CLNT_araddr                ,
    output reg         [   3: 0]           CLNT_arid                  ,
    output reg         [   7: 0]           CLNT_arlen                 ,
    output reg         [   2: 0]           CLNT_arsize                ,
    output reg         [   1: 0]           CLNT_arburst               ,
    
    output reg                             CLNT_rready                ,
    input                                  CLNT_rvalid                ,
    input              [   1: 0]           CLNT_rresp                 ,
    input              [  31: 0]           CLNT_rdata                 ,
    input                                  CLNT_rlast                 ,
    input              [   3: 0]           CLNT_rid                   ,

    input                                  SOC_awready                ,
    output reg                             SOC_awvalid                ,
    output reg         [  31: 0]           SOC_awaddr                 ,
    output reg         [   3: 0]           SOC_awid                   ,
    output reg         [   7: 0]           SOC_awlen                  ,
    output reg         [   2: 0]           SOC_awsize                 ,
    output reg         [   1: 0]           SOC_awburst                ,

    input                                  SOC_wready                 ,
    output reg                             SOC_wvalid                 ,
    output reg         [  31: 0]           SOC_wdata                  ,
    output reg         [   3: 0]           SOC_wstrb                  ,
    output reg                             SOC_wlast                  ,

    output reg                             SOC_bready                 ,
    input                                  SOC_bvalid                 ,
    input              [   1: 0]           SOC_bresp                  ,
    input              [   3: 0]           SOC_bid                    ,

    input                                  SOC_arready                ,
    output reg                             SOC_arvalid                ,
    output reg         [  31: 0]           SOC_araddr                 ,
    output reg         [   3: 0]           SOC_arid                   ,
    output reg         [   7: 0]           SOC_arlen                  ,
    output reg         [   2: 0]           SOC_arsize                 ,
    output reg         [   1: 0]           SOC_arburst                ,

    output reg                             SOC_rready                 ,
    input                                  SOC_rvalid                 ,
    input              [   1: 0]           SOC_rresp                  ,
    input              [  31: 0]           SOC_rdata                  ,
    input                                  SOC_rlast                  ,
    input              [   3: 0]           SOC_rid                     
);


    always @(*) begin
        if(araddr[31:24] == 8'h02 )begin
            awready = CLNT_awready ;
            CLNT_awvalid = awvalid ;
            CLNT_awaddr  = awaddr  ;
            CLNT_awid    = awid    ;
            CLNT_awlen   = awlen   ;
            CLNT_awsize  = awsize  ;
            CLNT_awburst = awburst ;
            wready  = CLNT_wready  ;
            CLNT_wvalid  = wvalid  ;
            CLNT_wdata   = wdata   ;
            CLNT_wstrb   = wstrb   ;
            CLNT_wlast   = wlast   ;
            CLNT_bready  = bready  ;
            bvalid  = CLNT_bvalid  ;
            bresp   = CLNT_bresp   ;
            bid     = CLNT_bid     ;
            arready = CLNT_arready ;
            CLNT_arvalid = arvalid ;
            CLNT_araddr  = araddr  ;
            CLNT_arid    = arid    ;
            CLNT_arlen   = arlen   ;
            CLNT_arsize  = arsize  ;
            CLNT_arburst = arburst ;
            CLNT_rready  = rready  ;
            rvalid  = CLNT_rvalid  ;
            rresp   = CLNT_rresp   ;
            rdata   = CLNT_rdata   ;
            rlast   = CLNT_rlast   ;
            rid     = CLNT_rid     ;

            SOC_arvalid = 0     ;
            SOC_araddr  = 0     ;
            SOC_arid    = 0     ;
            SOC_arlen   = 0     ;
            SOC_arsize  = 0     ;
            SOC_arburst = 0     ;
            SOC_rready  = 0     ;
            SOC_wvalid = 0      ;
            SOC_wdata  = 0      ;
            SOC_wstrb  = 0      ;
            SOC_wlast  = 0      ;
            SOC_bready = 0      ;
            SOC_awvalid = 0     ;
            SOC_awaddr  = 0     ;
            SOC_awid    = 0     ;
            SOC_awlen   = 0     ;
            SOC_awsize  = 0     ;
            SOC_awburst = 0     ;
            SOC_arvalid = 0     ;
            SOC_araddr  = 0     ;
            SOC_arid    = 0     ;
            SOC_arlen   = 0     ;
            SOC_arsize  = 0     ;
            SOC_arburst = 0     ;
            SOC_rready  = 0     ;


        end
    else begin
            awready = SOC_awready  ;
            SOC_awvalid = awvalid ;
            SOC_awaddr  = awaddr  ;
            SOC_awid    = awid    ;
            SOC_awlen   = awlen   ;
            SOC_awsize  = awsize  ;
            SOC_awburst = awburst ;

            wready  = SOC_wready  ;
            SOC_wvalid  = wvalid  ;
            SOC_wdata   = wdata   ;
            SOC_wstrb   = wstrb   ;
            SOC_wlast   = wlast   ;
            SOC_bready  = bready  ;

            bvalid  = SOC_bvalid  ;
            bresp   = SOC_bresp   ;
            bid     = SOC_bid     ;
            arready = SOC_arready ;
            SOC_arvalid = arvalid ;
            SOC_araddr  = araddr  ;
            SOC_arid    = arid    ;
            SOC_arlen   = arlen   ;
            SOC_arsize  = arsize  ;
            SOC_arburst = arburst ;
            SOC_rready  = rready  ;

            rvalid  = SOC_rvalid  ;
            rresp   = SOC_rresp   ;
            rdata   = SOC_rdata   ;
            rlast   = SOC_rlast   ;
            rid     = SOC_rid     ;

            CLNT_arvalid = 0;
            CLNT_araddr  = 0;
            CLNT_arid    = 0;
            CLNT_arlen   = 0;
            CLNT_arsize  = 0;
            CLNT_arburst = 0;
            CLNT_rready  = 0;

            CLNT_wvalid = 0          ;
            CLNT_wdata  = 0          ;
            CLNT_wstrb  = 0          ;
            CLNT_wlast  = 0          ;
            CLNT_bready = 0          ;

            CLNT_awvalid = 0        ;
            CLNT_awaddr  = 0        ;
            CLNT_awid    = 0        ;
            CLNT_awlen   = 0        ;
            CLNT_awsize  = 0        ;
            CLNT_awburst = 0        ;


            CLNT_arvalid = 0          ;
            CLNT_araddr  = 0          ;
            CLNT_arid    = 0          ;
            CLNT_arlen   = 0          ;
            CLNT_arsize  = 0          ;
            CLNT_arburst = 0          ;
            CLNT_rready  = 0          ;
    end
    end
    

    
endmodule
