`timescale 1ns / 1ps
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

module ysyx_24100029_IFU(
    input                        clock                      ,
    input                        reset                      ,
    input              [  31: 0] dnpc                       ,
    input                        dnpc_flag                  ,
    input                        pipe_stop                  ,

    output reg         [  31: 0] pc                         ,
    output reg         [  31: 0] inst                       ,

    input                        ready                      ,
    output reg                   valid                      ,

    input                        awready                    ,
    output                       awvalid                    ,
    output             [  31: 0] awaddr                     ,
    output             [   3: 0] awid                       ,
    output             [   7: 0] awlen                      ,
    output             [   2: 0] awsize                     ,
    output             [   1: 0] awburst                    ,

    input                        wready                     ,
    output                       wvalid                     ,
    output             [  31: 0] wdata                      ,
    output             [   3: 0] wstrb                      ,
    output                       wlast                      ,

    output                       bready                     ,
    input                        bvalid                     ,
    input              [   1: 0] bresp                      ,
    input              [   3: 0] bid                        ,

    input                        arready                    ,
    output                       arvalid                    ,
    output             [  31: 0] araddr                     ,
    output             [   3: 0] arid                       ,
    output             [   7: 0] arlen                      ,
    output             [   2: 0] arsize                     ,
    output             [   1: 0] arburst                    ,

    output                       rready                     ,
    input                        rvalid                     ,
    input              [   1: 0] rresp                      ,
    input              [  31: 0] rdata                      ,
    input                        rlast                      ,
    input              [   3: 0] rid                        ,

    output                       req                         
);

    reg                          dnpc_flag_reg              ;
    reg                          pipe_stop_reg              ;
    reg                [  31: 0] dnpc_reg                   ;

/************ Axi4 bus ***********/
    assign                       araddr                    = pc;
    assign                       arid                      = 0;
    assign                       arlen                     = 0;// 0+1 = 1 transfer once
    assign                       arsize                    = 3'b010;// transfer 4 bytes once
    assign                       arburst                   = 2'b00;// FIXED Burst

    assign                       awvalid                   = 0;
    assign                       awaddr                    = 0;
    assign                       awid                      = 0;
    assign                       awlen                     = 0;
    assign                       awsize                    = 0;
    assign                       awburst                   = 0;

    assign                       wvalid                    = 0;
    assign                       wdata                     = 0;
    assign                       wstrb                     = 0;
    assign                       wlast                     = 0;

    assign                       bready                    = 0;

    assign                       rready                    = 1'b1;

  //  check_rresp: assert(rresp != 2'b00) ; 
    localparam  ResetValue= 32'h30000000;

    assert property(@(posedge clock) rdata!=0) 
    else begin
    $finish;
    $error("read inst error!");
    end
/************ Axi4 bus ***********/
always @(posedge clock) begin
    if(reset)begin
        valid <= 1'b0;
        inst <= 0;
    end
    else if(rvalid)begin
        valid <= 1'b1;
        inst <= rdata;
    end
    else if(valid & ready)begin
        valid <= 1'b0;
        inst <= 0;
    end

end


always @(posedge clock) begin
    if(reset)begin
        dnpc_flag_reg <= 0;
        pipe_stop_reg <= 0;
        dnpc_reg <=0;
    end
    else if((~ready | ~valid) & (~dnpc_flag_reg & ~pipe_stop_reg) )begin
        dnpc_flag_reg <= dnpc_flag;
        pipe_stop_reg <= pipe_stop;
        dnpc_reg <= dnpc;
    end
    else if(ready & valid)begin
        dnpc_reg <= 0;
        dnpc_flag_reg <= 0;
        pipe_stop_reg <= 0;
    end

end

always @(posedge clock) begin
    if(reset)
        arvalid <= 1'b1;
    else if((pipe_stop| pipe_stop_reg) &valid&ready)
        arvalid <= 1'b1;
    else if(dnpc_flag_reg & valid &ready)
        arvalid <= 1'b1;
    else if(dnpc_flag&valid&ready)
        arvalid <= 1'b1;
    else if(valid & ready)
        arvalid <= 1'b1;
    else if(arvalid & arready)
        arvalid <= 1'b0;
end

always @(posedge clock) begin
        if(reset)
            pc <= ResetValue;   
        else if((pipe_stop| pipe_stop_reg) &valid&ready)
            pc <= pc ;
        else if(dnpc_flag_reg & valid &ready)
            pc <= dnpc_reg;
        else if(dnpc_flag&valid&ready)
            pc <= dnpc;
        else if(valid & ready)
            pc <= pc + 4;
end

    assign                       req                       = 1'b1;


endmodule

