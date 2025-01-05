`timescale 1ns / 1ps
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE     
// VSCODE plug-in version: Verilog-Hdl-Format-2.8.20240817
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            Please Write Company name
// All rights reserved     
// File name:              
// Last modified Date:     2024/11/24 10:25:51
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Please Write You Name 
// Created date:           2024/11/24 10:25:51
// mail      :             Please Write mail 
// Version:                V1.0
// TEXT NAME:              MEM.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/MEM.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//
import "DPI-C" function int npc_pmem_read(input int raddr);
import "DPI-C" function void npc_pmem_write(input int waddr, input int wdata, input byte wmask);

/* verilator lint_off UNUSEDSIGNAL */
/* verilator lint_off UNDRIVEN */
module SRAM
#(
    parameter                    DATA_WIDTH                = 32    ,
    parameter                    ADDR_WIDTH                = 32    
)
(
    input                        rst_n                      ,
    input                        clk                        ,
  
    input              [ADDR_WIDTH-1: 0]araddr              ,
    input                        arvalid                    ,
    output reg                   arready                    ,

    input                        rready                     ,
    output reg         [DATA_WIDTH-1: 0]rdata               ,
    output reg                   rresp                      ,
    output                       rvalid                     ,

    input              [ADDR_WIDTH-1: 0]awaddr              ,
    input                        awvalid                    ,
    output                       awready                    ,

    input              [DATA_WIDTH-1: 0]wdata               ,
    input              [   7: 0] wstrb                      ,
    input                        wvalid                     ,
    output                       wready                     ,

    output                       bresp                      ,
    output                       bvalid                     ,
    input                        bready                      
);

    reg                          read_state                 ;
    reg                          write_state                ;
    reg                          read_state_next            ;
    reg                          write_state_next           ;

    always @(posedge clk) begin
        if(!rst_n)
            read_state <= `wait_arv_ysyx_24100029;
        else
            read_state <= read_state_next;
    end

    always @(*) begin
        case(read_state)
        `wait_arv_ysyx_24100029:begin
            if(arvalid & rready)begin
                read_state_next = `wait_rdv_ysyx_24100029;
                arready = 1'b1;
            end
            else begin
                read_state_next = `wait_arv_ysyx_24100029;
                arready = 1'b1;
            end
        end
        `wait_rdv_ysyx_24100029:begin
                read_state_next = `wait_arv_ysyx_24100029;
                arready = 1'b0;
        end
    endcase
    end


    always @(posedge clk) begin
        if(!rst_n)begin
            rdata <= 0;
            rresp <= 0;
            rvalid <= 1'b0;
        end
        else if(rready && arvalid &&read_state == `wait_arv_ysyx_24100029)begin
            rdata  <= npc_pmem_read(araddr);
            rvalid <= 1'b1;
            rresp  <= 0;
        end
        else begin
            rvalid <= 1'b0;
            rresp <= 0;
            rdata <= rdata;
        end
    end
    always @(posedge clk) begin
        if(!rst_n)
            write_state <= `wait_awv_ysyx_24100029;
        else
            write_state <= write_state_next;
    end

    assign                       write_state_next          = `wait_awv_ysyx_24100029;

    always @(*) begin
            awready = 1'b1;
            wready  = 1'b1;
            bvalid  = 1'b1;
            bresp = 1'b0;
        if(write_state == `wait_awv_ysyx_24100029 && wvalid && awvalid)begin
            npc_pmem_write(awaddr,wdata,wstrb);
            bresp = 1'b1;
        end
    end



endmodule


