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
// Last modified Date:     2025/03/01 14:47:29
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Cui Junyan
// Created date:           2025/03/01 14:47:29
// mail      :             1354315077@qq.com 
// Version:                V1.0
// TEXT NAME:              sram.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/SRAM/sram.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//
`include "../define/interface.sv"
/* function test */
import "DPI-C" function int npc_pmem_read(int addr);
import "DPI-C" function void npc_pmem_write(int addr, int wdata,byte wmask);

module sram(
    input                               clock                      ,
    input                               reset                      ,

    axi4_if.slave                        sram_axi

);

// STATE
    localparam                          IDLE                       = 2'b00;
    localparam                          WRITE                      = 2'b01;
    localparam                          READ                       = 2'b11; 
    localparam                          RESP                       = 2'b10;   

// BURST
    localparam                          INCR                       = 2'b01 ;
    localparam                          FIXED                      = 2'b00 ; 



    reg                [   1: 0]        state                       ;
    reg                [  31: 0]        axaddr                        ;
    reg                [   7: 0]        axlen                         ;
    reg                [   2: 0]        axsize                      ;
    reg                [   1: 0]        axburst                     ;
    reg                [   7: 0]        count                       ;
    reg                [   7: 0]        wmask                       ;






    always @(posedge clock) begin
        if(reset)
            axaddr <= 0;
        else begin
            if(state == IDLE)begin
                if(sram_axi.arready & sram_axi.arvalid)
                    axaddr <= sram_axi.araddr;
                else if(sram_axi.awvalid & sram_axi.awready)
                    axaddr <= sram_axi.awaddr;  
            end
            else begin
                if(axburst == FIXED)
                    axaddr <= axaddr;
                else if(axburst == INCR)
                    if((sram_axi.wvalid & sram_axi.wready) || (sram_axi.rvalid & sram_axi.rready))
                    axaddr <=  axaddr + 2**axsize;
            end

        end
    end
    always @(posedge clock) begin
        if(reset)begin
            axburst <= FIXED;
            axsize <= 0;
            axlen <= 0;
        end
        else if(state == IDLE)begin
            if(sram_axi.arready & sram_axi.arvalid)begin
                axburst <= sram_axi.arburst;
                axsize <= sram_axi.arsize;
                axlen <= sram_axi.arlen; 
            end
            else if(sram_axi.awvalid & sram_axi.awready)begin
                axburst <= sram_axi.awburst;   
                axsize <= sram_axi.awsize;
                axlen <= sram_axi.awlen; 
            end
        end 
    end

    always @(posedge clock) begin
        if(reset)
            count <= 0;
        else if((count == axlen) & ((sram_axi.rready & sram_axi.rvalid) ||  (sram_axi.wready & sram_axi.wvalid)))
            count <= 0;
        else if((sram_axi.rready & sram_axi.rvalid) ||  (sram_axi.wready & sram_axi.wvalid))begin
            count <= count + 1;
        end
    end



    always @(posedge clock) begin
        if(reset)
            state <= IDLE;
        else begin
            case(state)
            IDLE:begin
                if(sram_axi.arready & sram_axi.arvalid)
                    state <= READ;
                else if(sram_axi.awready & sram_axi.awvalid)
                    state <= WRITE;
                else
                    state <= IDLE;
            end
            WRITE: if(sram_axi.wready & sram_axi.wvalid & sram_axi.wlast)
                state <= RESP;
            else
                state <= WRITE;
            READ: if(sram_axi.rready & sram_axi.rvalid & sram_axi.rlast)
                state <= IDLE;
            else
                state <= READ;
            RESP: if(sram_axi.bready & sram_axi.bvalid)
                state <= IDLE;
            else
                state <= RESP;
            default:state <= IDLE;
            endcase
        end
    end

    always @(posedge clock) begin
        if(state == WRITE & (sram_axi.wready & sram_axi.wvalid ))
             npc_pmem_write({axaddr[31:2],2'd0},sram_axi.wdata,wmask);;
    end


    always @(posedge clock) begin
        if(state == READ & sram_axi.rready )begin
            sram_axi.rdata <= npc_pmem_read(axaddr) ; 
        end
    end

    always @(posedge clock) begin
        if(state == READ & sram_axi.rready & sram_axi.rvalid)
            sram_axi.rvalid <= 1'b0;
        else if(state == READ & sram_axi.rready )
            sram_axi.rvalid <= 1'b1 ;
    end

    assign                              sram_axi.arready                     = (state == IDLE);
    assign                              sram_axi.awready                     = (state == IDLE);
    assign                              sram_axi.wready                      = (state == WRITE);
    assign                              sram_axi.bresp                       = 0;
    assign                              sram_axi.bid                         = 0;
    assign                              sram_axi.rid                         = 0;
    assign                              sram_axi.rresp                       = 0;
    assign                              wmask                       = 2**axsize;
    assign                              sram_axi.bvalid             = state == RESP;
    assign                              sram_axi.rlast              = state == READ & count == axlen & sram_axi.rvalid;



                                                                   
endmodule
